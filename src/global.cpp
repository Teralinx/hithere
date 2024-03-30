#include "global.h"
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iomanip>
#include <sol/sol.hpp>


std::shared_ptr<spdlog::logger> fileLogger;

size_t funrecvdata(const char* data, size_t size, size_t nmemb, std::string* writerData)
{
	if (writerData == NULL)
		return 0;
	writerData->append(data, nmemb);
	return nmemb;
}

void initlizeSpdlog()
{
		fileLogger = spdlog::basic_logger_mt("file_logger", "logs/log.txt");
}
void logerror(const std::string& msg, const std::string& filename, const std::string& funcname, int line)
{
	std::stringstream ss;
	ss << "time: ";
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	ss << "Error: " << msg<< " in file: " << filename  << " in function: " << funcname << " at line: " << line;
	std::cout << ss.str() << std::endl;
	fileLogger->error(ss.str());
}

bool getpublicipaddress(std::string& strip)
{
	//use sol2 to load the lua file
	sol::state lua;
	
	lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

//	lua.script(" a = 1");
	lua.script_file("lua/main.lua");
	//call lua function to get the web address
	sol::function accessWebAddr = lua["accessWebAddr"];
	std::string webaddress = accessWebAddr();
	auto handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, webaddress.c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, funrecvdata);
	std::string strReceived;
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &strReceived);
	//use curl to get the html
	auto success = curl_easy_perform(handle);

	if (success == CURLE_OK)
	{
		sol::function getip = lua["getip"];
		strip = getip(strReceived.c_str());
		
		return true;
	}
	else
	{
		QUICKLOG("Fail to get the public ip address");
	}
	curl_easy_cleanup(handle);


	return true;
}