#pragma once

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>
#include <variant>
#include <vector>
#include <map>
#include <optional> 

class lua_session;

class lua_reference
{
public:
	lua_reference(lua_session *ls);
	~lua_reference();

	int get_reference() const;

private:
	lua_session *m_ls;
	int m_reference;
};

typedef std::shared_ptr<const lua_reference> lua_ref_ptr;

typedef std::variant<
	std::nullptr_t, bool, int, double, std::string, const char*, lua_ref_ptr,
	std::vector<int>, std::vector<double>, std::vector<std::string>, std::vector<lua_ref_ptr>,
	std::optional<int>, std::optional<double>, std::optional<std::string>
> lua_variant;

class lua_session
{
friend class lua_reference;

public:
	lua_session();
	lua_session(const lua_session &obj);
	~lua_session();

	static lua_session* get_session(lua_State *ls);    
	void load_file(std::string file_name); 
	void register_function(std::string function_name, lua_CFunction function); 
	int get_global_type(std::string global_name);    
	void get_function(std::string function_name); 
	void call_leave(std::string function_name, std::vector<lua_variant> parameters = std::vector<lua_variant>()); 
	lua_variant call(std::string function_name, std::vector<lua_variant> parameters = std::vector<lua_variant>()); 
	template <typename T> 
	T call(std::string function_name, std::vector<lua_variant> parameters = std::vector<lua_variant>()); 
	void call_raw(int num_args = 0, int num_results = 0);    
	void push(lua_variant value); 
	void push(std::vector<lua_variant> values); 
	lua_variant pop(); 
	template <typename T> 
	T pop(); 
	lua_variant peek(int index); 
	template <typename T> 
	T peek(int index);    
	void set_field(std::string table_name, std::string field_name, std::string value);    
	void capi_stack_dump(); 
	void call_stack_trace();

private:
	lua_State *m_l;

	void check_status(int status);

	template <typename T>
	T convert_lua_variant(lua_variant value);

	void specialize();

	static std::map<lua_State*, lua_session*> m_state_session_map;

	template <typename T> void push_vector(std::vector<T> values);
	template <typename T> void push_optional(std::optional<T> value);
};
