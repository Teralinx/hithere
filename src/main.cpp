#include <iostream>
#include <string>
#include <curl/curl.h>
#include <htmlcxx/html/ParserDom.h>
extern "C"
{
	#include <lua/lua.h>
	#include <lua/lualib.h>
	#include <lua/lauxlib.h>
}

std::string html;
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	char* x = new char[nmemb];
	std::memcpy(x, buffer, nmemb);
	html += x;
	delete[] x;
	return nmemb;

}

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);	
	auto handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, "https://ip.tool.chinaz.com/");
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

	auto success = curl_easy_perform(handle);

	int s = html.size();

	//std::cout << html << std::endl;
	lua_State* L = luaL_newstate(); // 创建一个新的Lua状态机
	luaL_openlibs(L); // 打开Lua标准库


	// 加载Lua脚本
	if (luaL_loadfile(L, "lua/main.lua") || lua_pcall(L, 0, 0, 0)) {
		printf("Error: %s\n", lua_tostring(L, -1));
		return -1;
	}



	// 获取Lua中的函数，假设Lua脚本中有一个名为"lizi"的函数
	lua_getglobal(L, "getip");

	// 假设lizi函数接受一个参数

	lua_pushstring(L, html.c_str());

	
	if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
		printf("Error: %s\n", lua_tostring(L, -1));
		return -1;
	}


	if (lua_isstring(L, -1))
	{
		auto x = lua_tostring(L, -1);
		std::cout << x << std::endl;
		lua_settop(L, 0);
	}
	lua_close(L);
	return 0;
}


