#CMake version
cmake_minimum_required(VERSION 3.29.0)

#set language standard
set(CMAKE_CXX_STANDARD 17)

#set project name
project(hithere)

#add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src hitheresource)
#add headers
FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
#add target
list(REMOVE_ITEM hitheresource ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_library(hitherelib ${hitheresource} ${headers})
#add dependencies
include(FetchContent)

FetchContent_Declare(spdlog
                     GIT_REPOSITORY https://github.com/gabime/spdlog
                     GIT_TAG        v1.13.0)
FetchContent_MakeAvailable(spdlog)


FetchContent_Declare(
    lua
    URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
)
FetchContent_Populate(lua)
file(WRITE ${lua_SOURCE_DIR}/CMakeLists.txt 
"aux_source_directory(${lua_SOURCE_DIR}/src luasource)
 list(REMOVE_ITEM luasource \"${lua_SOURCE_DIR}/src/lua.c\") 
 list(REMOVE_ITEM luasource \"${lua_SOURCE_DIR}/src/luac.c\") 
 add_library(lua STATIC \${luasource}) 
 target_include_directories(lua PUBLIC ${lua_SOURCE_DIR}/src) ")
add_subdirectory(${lua_SOURCE_DIR} ${lua_BINARY_DIR})



FetchContent_Declare(
  sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG        v3.2.3
)
FetchContent_MakeAvailable(sol2)



FetchContent_Declare(
  asio
  URL https://github.com/chriskohlhoff/asio/archive/asio-1-18-2.tar.gz
)
  FetchContent_Populate(asio)


set(includeDirectories $${headers} ${CMAKE_CURRENT_SOURCE_DIR}/3thlibs/curl/include ${asio_SOURCE_DIR}/asio/include)
set(linkDirectories ${CMAKE_CURRENT_SOURCE_DIR}/3thlibs/curl/lib)
set(linklibs libcurl  spdlog lua sol2 )

#add headers
target_include_directories(hitherelib PUBLIC  ${includeDirectories})

#add libdirs
target_link_directories(hitherelib PUBLIC ${linkDirectories})

#add libs
target_link_libraries(hitherelib  ${linklibs})

add_executable(hithere ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(hithere hitherelib)
#copy files of runtime to binary directory
add_custom_command(TARGET hithere POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory 
                ${CMAKE_CURRENT_SOURCE_DIR}/runtime
                $<TARGET_FILE_DIR:hithere>)

#copy files of runtime to where .exe is in
add_custom_command(TARGET hithere POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory 
                ${CMAKE_CURRENT_SOURCE_DIR}/runtime
                ${CMAKE_CURRENT_BINARY_DIR})


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)



