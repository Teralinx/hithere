#include <string>
#define QUICKLOG(msg) logerror(msg, __FILE__, __FUNCTION__, __LINE__)

/*
*@brief initlize spdlog
*/
void initlizeSpdlog();

/*
*@brief using spdlog to log the error message and function name and line number and the time
*/
void logerror(const std::string& msg, const std::string& filename, const std::string& funcname, int line);


/**
* @brief The function is for getting your public ip address. At first, it will
* load a lua file to get a web address which can privde you the public ip of you.
* Then it will use curl to access the web and get a html as a result.The last steb is
* passing the entire html you just received to lua function called getip. It will
* resole out your ip from which you passed in
*/
bool getpublicipaddress(std::string& strip);









