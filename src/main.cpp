#include <curl/curl.h>
#include "global.h"


int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);	
	std::string strip;
	getpublicipaddress(strip);
	return 0;
}


