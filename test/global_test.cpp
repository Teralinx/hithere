#include "../src/global.h"
#include <gtest/gtest.h>
#include <curl/curl.h>


TEST(GETIP_TEST, NORAMAL) {

	curl_global_init(CURL_GLOBAL_ALL);	
	std::string ip;
	getpublicipaddress(ip);
}



