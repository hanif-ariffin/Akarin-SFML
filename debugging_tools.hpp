#pragma once

#include <iostream>

/*
Should probably turn this into a class
*/
struct DebuggingInformation
{
	std::string program_name = "PROGRAM_NAME";
	std::string render_time = "RENDER_TIME";
	std::string current_time = "CURRENT_TIME";
};