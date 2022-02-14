#pragma once
class ENC_ViewingGroup
{
public:
	ENC_ViewingGroup();
	virtual ~ENC_ViewingGroup();

public:
	static wstring chart_info_group[];
	static wstring mariner_info_group[];
	static int group_number[];

	static int reserved_chart_number[];
	static int reserved_mariner_number[];
};