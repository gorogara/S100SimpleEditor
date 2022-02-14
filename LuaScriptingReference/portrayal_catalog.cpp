#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>

#include "portrayal_catalog.h"

#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

static string pc_path;

static char *pc_data;
static xml_document<> pc_dom;

void pc_init(const char *portrayal_catalog)
{   

	ifstream pc_file(portrayal_catalog);
	stringstream pc_buffer;
	pc_buffer << pc_file.rdbuf();

	auto buf_len = strlen(pc_buffer.str().c_str()) + 1;

	pc_data = new char[buf_len];

	strcpy_s(pc_data, buf_len, pc_buffer.str().c_str());

	pc_dom.parse<0>(pc_data);

	pc_path = portrayal_catalog;

	auto last_sep = pc_path.find_last_of('\\');

	pc_path = pc_path.substr(0, last_sep);
}

vector<context_parameter> pc_get_context_parameters()
{
	vector<context_parameter> cp;

	auto parameters = pc_dom.first_node()->first_node("context");

	for (auto parameter = parameters->first_node(); parameter; parameter = parameter->next_sibling())
	{
		auto id = parameter->first_attribute("id")->value();
		auto type = string(parameter->first_node("type")->value());
		auto default_value = parameter->first_node("default")->value();

		if (type == "Boolean") type = "boolean";
		if (type == "Integer") type = "integer";
		if (type == "Double")  type = "real";
		if (type == "String")  type = "text";
		if (type == "Date")    type = "date";

		cp.push_back({ id, type, default_value });
	}

	return cp;
}

vector<string> pc_get_top_level_rules()
{
	vector<string> tlr;

	auto rule_files = pc_dom.first_node()->first_node("rules");

	for (auto rule_file = rule_files->first_node(); rule_file; rule_file = rule_file->next_sibling())
	{
		auto rule_type = string(rule_file->first_node("ruleType")->value());

		if (rule_type == "TopLevelTemplate")
			tlr.push_back(rule_file->first_node("fileName")->value());
	}

	return tlr;
}

string pc_get_rules_path()
{
	return pc_path + "\\Rules";
}
