#CMake version
cmake_minimum_required(VERSION 3.29.0)

#set language standard
set(CMAKE_CXX_STANDARD 17)

#set project name
project(hithere)

#add source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src luafilesource)

#add target
add_executable(hithere ${luafilesource})

#add headers
target_include_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include)

#add libdirs
target_link_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#link libs
target_link_libraries(hithere libcurl.lib htmlcxx.lib lualib.lib)
#copy runtime files

add_custom_command(TARGET hithere POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory 
                ${CMAKE_CURRENT_SOURCE_DIR}/runtime
                $<TARGET_FILE_DIR:hithere>)


add_custom_command(TARGET hithere POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory 
                ${CMAKE_CURRENT_SOURCE_DIR}/runtime
                ${CMAKE_CURRENT_BINARY_DIR})
# add_custom_command(TARGET hithere POST_BUILD
#                 COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                 ${CMAKE_CURRENT_SOURCE_DIR}/runtime/lua
#                 ${CMAKE_CURRENT_SOURCE_DIR}/runtime/libcurl.dll
#                 $<TARGET_FILE_DIR:hithere>)