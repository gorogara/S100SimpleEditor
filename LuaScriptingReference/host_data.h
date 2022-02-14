#pragma once

#include <vector>
#include <optional>

class FeatureCatalogue;
class S101Cell;

enum class spatial_type
{
	unknown,
	point,
	multi_point,
	curve,
	composite_curve,
	surface
};

struct spatial_association
{
	spatial_association() = default;

	std::string spatial_type;
	std::string spatial_id;
	std::string orientation;
	std::optional<int> scale_minimum;
	std::optional<int> scale_maximum;
};

struct point
{
	point() = default;

	std::string x;
	std::string y;
	std::optional<std::string> z;
};

struct multipoint
{
	multipoint() = default;

	std::vector<point> points;
};

struct curve_segment
{
	curve_segment() = default;

	std::vector<point> control_points;
	std::string interpolation;
};

struct curve
{
	curve() = default;

	spatial_association start_point;
	spatial_association end_point;
	std::vector<curve_segment> segments;
};

struct composite_curve
{
	composite_curve() = default;

	std::vector<spatial_association> curve_associations;
};

struct surface
{
	surface() = default;

	spatial_association exterior_ring;
	std::optional<std::vector<spatial_association>> interior_rings;
};

void hd_init(/*const char *input_schema, */S101Cell *c);
void hd_delete();

std::vector<std::string> hd_get_feature_ids();
std::string hd_get_feature_code(std::string id);
std::vector<spatial_association> hd_get_feature_spatial_associations(std::string id);
std::vector<std::string> hd_get_feature_simple_attribute_values(std::string id, std::string path, std::string attribute_code);
int hd_get_feature_complex_attribute_count(std::string id, std::string path, std::string attribute_code);

std::vector<std::string> hd_get_information_type_ids();
std::string hd_get_information_type_code(std::string id);
std::vector<std::string> hd_get_information_type_simple_attribute_values(std::string id, std::string path, std::string attribute_code);
int hd_get_information_type_complex_attribute_count(std::string id, std::string path, std::string attribute_code);

std::vector<std::string> hd_get_feature_associated_information_ids(std::string feature_id, std::string association_code, std::optional<std::string> role_code);
std::vector<std::string> hd_get_feature_associated_feature_ids(std::string feature_id, std::string association_code, std::optional<std::string> role_code);
std::vector<std::string> hd_get_spatial_associated_information_ids(std::string spatial_id, std::string association_code, std::optional<std::string> role_code);
std::vector<std::string> hd_get_spatial_associated_feature_ids(std::string spatial_id);
std::vector<std::string> hd_get_spatial_ids();
spatial_type hd_get_spatial_type(std::string spatial_id);

point hd_get_point(std::string spatial_id);
multipoint hd_get_multipoint(std::string spatial_id);
curve hd_get_curve(std::string spatial_id);
composite_curve hd_get_composite_curve(std::string spatial_id);
surface hd_get_surface(std::string spatial_id);