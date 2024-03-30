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
add_executable(hithere ${hitheresource} ${headers})

#add dependencies
include(FetchContent)

FetchContent_Declare(spdlog
                     GIT_REPOSITORY https://github.com/gabime/spdlog
                     GIT_TAG        v1.13.0)
FetchContent_MakeAvailable(spdlog)


FetchContent_Declare(googletest
                     GIT_REPOSITORY https://github.com/google/googletest
                     GIT_TAG        v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)






# set(PACKAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lua-5.4.6.tar.gz")
# set(EXTRACT_DIR "${CMAKE_CURRENT_BINARY_DIR}/extractdir/lua")

# file(ARCHIVE_EXTRACT
#   INPUT ${PACKAGE_PATH}
#   DESTINATION ${EXTRACT_DIR}
# )

# FetchContent_Declare(
#     lua
#     SOURCE_DIR ${EXTRACT_DIR}/lua-5.4.6
# )


# file(WRITE ${EXTRACT_DIR}/lua-5.4.6/CMakeLists.txt 
# "aux_source_directory(${EXTRACT_DIR}/lua-5.4.6/src luasource) 
#  list(REMOVE_ITEM MY_LIST \"lua.c\") 
#  list(REMOVE_ITEM MY_LIST \"luac.c\") 
#  add_library(lua \${luasource}) 
#  target_include_directories(lua PUBLIC ${EXTRACT_DIR}/lua-5.4.6/src) ")
#  FetchContent_MakeAvailable(lua)

FetchContent_Declare(
    lua
    URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
)
FetchContent_Populate(lua)
file(WRITE ${lua_SOURCE_DIR}/CMakeLists.txt 
"aux_source_directory(${lua_SOURCE_DIR}/src luasource)

 list(REMOVE_ITEM luasource \"${lua_SOURCE_DIR}/src/lua.c\") 
 list(REMOVE_ITEM luasource \"${lua_SOURCE_DIR}/src/luac.c\") 
 add_library(lua \${luasource}) 
 target_include_directories(lua PUBLIC ${lua_SOURCE_DIR}/src) ")
add_subdirectory(${lua_SOURCE_DIR} ${lua_BINARY_DIR})



FetchContent_Declare(
  sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG        v3.2.3
)

FetchContent_MakeAvailable(sol2)

#add headers
target_include_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include )

#add libdirs
target_link_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#add libs
target_link_libraries(hithere  libcurl.lib  spdlog  lua sol2)


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




#tests
set(testdir ${CMAKE_CURRENT_SOURCE_DIR}/test)
enable_testing()
add_executable(global_test  ${testdir}/global_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/global.cpp)
target_include_directories(global_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_directories(global_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(global_test GTest::gtest GTest::gtest_main libcurl.lib spdlog lua sol2)
include(GoogleTest)
gtest_discover_tests(global_test)

add_custom_command(TARGET global_test POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory 
${CMAKE_CURRENT_SOURCE_DIR}/test/testdata
$<TARGET_FILE_DIR:global_test>/test/testdata)