#pragma once

#include <vector>

struct context_parameter
{
	std::string name;
	std::string type;
	std::string default_value;
};

void pc_init(const char *portrayal_catalog);

std::vector<context_parameter> pc_get_context_parameters();

std::string pc_get_rules_path();

std::vector<std::string> pc_get_top_level_rules();
