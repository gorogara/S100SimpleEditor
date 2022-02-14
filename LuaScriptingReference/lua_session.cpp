
#include "stdafx.h"
#include "lua_session.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include <assert.h>
#include <iostream>
#include <afxcmn.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib" )

using namespace std;

lua_reference::lua_reference(lua_session *ls)
{
	m_ls = ls;
	m_reference = luaL_ref(ls->m_l, LUA_REGISTRYINDEX);
}

lua_reference::~lua_reference()
{
	luaL_unref(m_ls->m_l, LUA_REGISTRYINDEX, m_reference);
}

int lua_reference::get_reference() const
{
	return m_reference;
}

map<lua_State*, lua_session*> lua_session::m_state_session_map;  
void lua_session::specialize()
{
	call<bool>("");
	call<double>("");
	call<string>("");
	call<const char*>("");
	call<lua_ref_ptr>("");

	pop<bool>();
	pop<double>();
	pop<string>();
	pop<const char*>();
	pop<lua_ref_ptr>();

	peek<bool>(0);
	peek<double>(0);
	peek<string>(0);
	peek<const char*>(0);
	peek<lua_ref_ptr>(0);
}

static int atpanic(lua_State *l)
{
	cerr << "Lua panic!\n";
	return 2;
}

lua_session::lua_session()
{
	m_l = luaL_newstate();

	luaL_openlibs(m_l);

	lua_atpanic(m_l, atpanic);

	m_state_session_map[m_l] = this;
}

lua_session::lua_session(const lua_session &obj)
{
	m_l = obj.m_l;
}


lua_session::~lua_session()
{
	lua_close(m_l);
}

void lua_session::check_status(int status)
{
	if (status != 0 && status != LUA_YIELD)
	{
		return;

		const char *message = lua_tostring(m_l, -1);

		cerr << message << "\n";

		assert(false);

		exit(3);
	}
}

template<typename T>
T lua_session::convert_lua_variant(lua_variant value)
{
	if (holds_alternative<T>(value))
		return get<T>(value);
	T temp = T();
	return temp;  

	exit(5);
}

lua_session* lua_session::get_session(lua_State *l)
{
	return m_state_session_map[l];
}   

void lua_session::load_file(string file_name)
{
	check_status(luaL_loadfile(m_l, file_name.c_str()));

	call_raw();
}

void lua_session::register_function(string function_name, lua_CFunction function)
{
	lua_pushcfunction(m_l, function);

	lua_setglobal(m_l, function_name.c_str());
}

int lua_session::get_global_type(string global_name)
{
	lua_getglobal(m_l, global_name.c_str());

	int type = lua_type(m_l, -1);

	lua_pop(m_l, 1);

	return type;
}   

void lua_session::get_function(string function_name)
{
	lua_getglobal(m_l, function_name.c_str());

	if (lua_type(m_l, -1) != LUA_TFUNCTION)
	{
		cerr << "Attempt to get a non-function  " << function_name << ".\n";

		assert(false);

		exit(4);
	}
}

void lua_session::call_leave(string function_name, vector<lua_variant> parameters)
{
	get_function(function_name);

	for (auto parameter : parameters)
		push(parameter);

	check_status(lua_pcall(m_l, (int)parameters.size(), 1, 0));
}

lua_variant lua_session::call(string function_name, vector<lua_variant> parameters)
{
 	get_function(function_name);

	for (auto parameter : parameters)
		push(parameter);

	check_status(lua_pcall(m_l, (int)parameters.size(), 1, 0));
	return pop();
}

template <typename T>
T lua_session::call(string function_name, vector<lua_variant> parameters)
{
	return convert_lua_variant<T>(call(function_name, parameters));
}

void lua_session::call_raw(int num_args, int num_results)
{
	check_status(lua_pcall(m_l, num_args, num_results, 0));
}   

template <typename T> void lua_session::push_vector(vector<T> values)
{
	lua_createtable(m_l, (int)values.size(), 0);

	int i = 0;

	for (T value : values)
	{
		push(value);

		lua_rawseti(m_l, -2, ++i);
	}
}

template <typename T> void lua_session::push_optional(optional<T> value)
{
	if (value.has_value())
		push(value.value());
	else
		lua_pushnil(m_l);
}

void lua_session::push(lua_variant value)
{
	if (holds_alternative<nullptr_t>(value))
		lua_pushnil(m_l);

	else if (holds_alternative<bool>(value))
		lua_pushboolean(m_l, get<bool>(value));

	else if (holds_alternative<int>(value))
		lua_pushnumber(m_l, get<int>(value));

	else if (holds_alternative<double>(value))
		lua_pushnumber(m_l, get<double>(value));

	else if (holds_alternative<string>(value))
		lua_pushstring(m_l, get<string>(value).c_str());

	else if (holds_alternative<const char *>(value))
		lua_pushstring(m_l, get<const char *>(value));

	else if (holds_alternative<lua_ref_ptr>(value))
	{
		auto ref = get<lua_ref_ptr>(value);

		if (ref == nullptr)
			lua_pushnil(m_l);
		else
			lua_rawgeti(m_l, LUA_REGISTRYINDEX, ref->get_reference());
	}

	else if (holds_alternative<vector<int>>(value))
		push_vector(get<vector<int>>(value));

	else if (holds_alternative<vector<double>>(value))
		push_vector(get<vector<double>>(value));

	else if (holds_alternative<vector<string>>(value))
		push_vector(get<vector<string>>(value));

	else if (holds_alternative<vector<lua_ref_ptr>>(value))
		push_vector(get<vector<lua_ref_ptr>>(value));

	else if (holds_alternative<optional<int>>(value))
		push_optional(get<optional<int>>(value));

	else if (holds_alternative<optional<double>>(value))
		push_optional(get<optional<double>>(value));

	else if (holds_alternative<optional<string>>(value))
		push_optional(get<optional<string>>(value));

	else
		assert(false);
}

void lua_session::push(vector<lua_variant> values)
{
	lua_createtable(m_l, (int)values.size(), 0);

	int i = 0;

	for (auto value : values)
	{
		push(value);

		lua_rawseti(m_l, -2, ++i);
	}
}

lua_variant lua_session::pop()
{
	lua_variant result;

	switch (lua_type(m_l, -1))
	{
		case LUA_TNIL:     result = lua_variant(); break;
		case LUA_TBOOLEAN: result = lua_variant((bool)lua_toboolean(m_l, -1)); break;
		case LUA_TNUMBER:  result = lua_variant(lua_tonumber(m_l, -1)); break;
		case LUA_TSTRING:  result = lua_variant((string)lua_tostring(m_l, -1)); break;
		case LUA_TTABLE:
		{
			lua_ref_ptr p(new lua_reference(this));
			return lua_variant(p);
		}
		case LUA_TFUNCTION:
		{
			lua_ref_ptr p(new lua_reference(this));
			return lua_variant(p);
		}
		default:
			assert(false);
			result = lua_variant();
	}

	lua_remove(m_l, -1);
	return result;
}

template <typename T>
T lua_session::pop()
{
	return convert_lua_variant<T>(pop());
}

lua_variant lua_session::peek(int index)
{
	lua_variant result;

	switch (lua_type(m_l, index))
	{
	case LUA_TNIL:     result = lua_variant(); break;
	case LUA_TBOOLEAN: result = lua_variant((bool)lua_toboolean(m_l, index)); break;
	case LUA_TNUMBER:  result = lua_variant(lua_tonumber(m_l, index)); break;
	case LUA_TSTRING:  result = lua_variant((string)lua_tostring(m_l, index)); break;

	default:
		assert(false);
		result = lua_variant();
	}

	return result;
}

template <typename T>
T lua_session::peek(int index)
{
	return convert_lua_variant<T>(peek(index));
}   

void lua_session::set_field(string table_name, string field_name, string value)
{
	lua_getglobal(m_l, table_name.c_str());

	if (lua_type(m_l, -1) != LUA_TTABLE)
	{
		cerr << "Attempt to set field on non-table global " << table_name << ".\n";

		exit(4);
	}

	lua_pushstring(m_l, value.c_str());

	lua_setfield(m_l, -2, field_name.c_str());
}   

void lua_session::capi_stack_dump()
{
	int top = lua_gettop(m_l);

	for (int i = 1; i <= top; i++)
	{
		int t = lua_type(m_l, i);

		switch (t)
		{
			case LUA_TSTRING:
				cout << lua_tostring(m_l, i) << endl;
				break;

			case LUA_TBOOLEAN:
				cout << (lua_toboolean(m_l, i) ? "true" : "false") << endl;
				break;

			case LUA_TNUMBER:
				cout << lua_tonumber(m_l, i) << endl;
				break;

			default:
				cout << lua_typename(m_l, t) << endl;
				break;
		}
	}

	cout << endl;
}
void lua_session::call_stack_trace()
{
	lua_Debug ar;

	int level = 1;

	while (lua_getstack(m_l, level++, &ar) == 1)
	{
		lua_getinfo(m_l, "nSlu", &ar);

		if (ar.name)
			cout << '\t' << ar.short_src << " (" << ar.currentline << "): " << ar.name << endl;
		else
			cout << '\t' << ar.short_src << " (" << ar.currentline << ")" << endl;


		int local = 1;
		const char *local_name;

		while (local_name = lua_getlocal(m_l, &ar, local++))
		{
			cout << "\t\t" << local_name << "=";

			auto value = this->pop();

			if (holds_alternative<nullptr_t>(value))
				cout << "nil";

			else if (holds_alternative<bool>(value))
				cout << (get<bool>(value) ? "true" : "false");

			else if (holds_alternative<int>(value))
				cout << get<int>(value);

			else if (holds_alternative<double>(value))
				cout << get<double>(value);

			else if (holds_alternative<string>(value))
				cout << "\"" << get<string>(value) << "\"";

			else if (holds_alternative<const char *>(value))
				cout << "\"" << get<const char *>(value) << "\"";

			cout << endl;
		}
	}

	cout << endl;
}
