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
//	std::cout << (char*)buffer << std::endl;
	if ("" == html)
	{
	}
	html += (char*)buffer;
	auto x = (char*)userp;
	std::cout << size << std::endl;

//	std::cout << "1" <<std::endl;
	//lua_State* L = luaL_newstate(); // 创建一个新的Lua状态机
	//luaL_openlibs(L); // 打开Lua标准库


	//// 加载Lua脚本
	//if (luaL_loadfile(L, "lua/main.lua") || lua_pcall(L, 0, 0, 0)) {
	//	printf("Error: %s\n", lua_tostring(L, -1));
	//	return -1;
	//}



	//// 获取Lua中的函数，假设Lua脚本中有一个名为"lizi"的函数
	//lua_getglobal(L, "searchip");

	//// 假设lizi函数接受一个参数
	//lua_pushstring(L, html.c_str());

	//// 调用Lua函数
	//if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
	//	printf("Error: %s\n", lua_tostring(L, -1));
	//	return -1;
	//}
	//lua_settop(L, 0);
	//lua_getglobal(L, "getip");
	//if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
	//	printf("Error: %s\n", lua_tostring(L, -1));
	//	return -1;
	//}


	//std::string x = lua_tostring(L, -1);
	//std::cout << x << std::endl;
	// 清理Lua状态机
	//lua_close(L);

	////Parse some html code
	//htmlcxx::HTML::ParserDom parser;
	//tree<htmlcxx::HTML::Node> dom = parser.parseTree(html);

	////Print whole DOM tree
	////std::cout << dom << std::endl;

	////Dump all links in the tree
	//tree<htmlcxx::HTML::Node>::iterator it = dom.begin();
	//tree<htmlcxx::HTML::Node>::iterator end = dom.end();
	//for (; it != end; ++it)
	//{
	//	if (it->tagName() == "input")
	//	{
	//		it->parseAttributes();
	//		auto attrs = it->attributes();
	//		if (attrs.count("id") && "address" == attrs["id"] && attrs.count("value"))
	//		{
	//			
	//				std::cout <<  "IP  " << attrs["value"] << std::endl;
	//		}

	//		//std::cout << it->attributes("href");
	//	}
	//}

	////Dump all text of the document
	//it = dom.begin();
	//end = dom.end();
	//for (; it != end; ++it)
	//{
	//	if ((!it->isTag()) && (!it->isComment()))
	//	{
	//		//std::cout << it->text();
	//	}
	//}

	return nmemb;
}

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);	
	auto handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, "https://ip.tool.chinaz.com/");
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

	auto success = curl_easy_perform(handle);
//
//	int s = html.size();
//
////	std::cout << html << std::endl;
//	lua_State* L = luaL_newstate(); // 创建一个新的Lua状态机
//	luaL_openlibs(L); // 打开Lua标准库
//
//
//	// 加载Lua脚本
//	if (luaL_loadfile(L, "lua/main.lua") || lua_pcall(L, 0, 0, 0)) {
//		printf("Error: %s\n", lua_tostring(L, -1));
//		return -1;
//	}
//
//
//
//	// 获取Lua中的函数，假设Lua脚本中有一个名为"lizi"的函数
//	lua_getglobal(L, "searchip");
//
//	// 假设lizi函数接受一个参数
//	lua_pushstring(L, html.c_str());
//
//	// 调用Lua函数
//	if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
//		printf("Error: %s\n", lua_tostring(L, -1));
//		return -1;
//	}
//	lua_settop(L, 0);
//	lua_getglobal(L, "getip");
//	if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
//		printf("Error: %s\n", lua_tostring(L, -1));
//		return -1;
//	}


//	std::string x = lua_tostring(L, -1);
	//std::cout << x << std::endl;
	//清理Lua状态机
//	lua_close(L);
	return 0;
}


