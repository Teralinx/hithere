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
FetchContent_Declare(lua
                     GIT_REPOSITORY https://github.com/Teralinx/compilelualib
                     GIT_TAG        3.0)
FetchContent_MakeAvailable(lua)
FetchContent_Declare(spdlog
                     GIT_REPOSITORY https://github.com/gabime/spdlog
                     GIT_TAG        v1.13.0)
FetchContent_MakeAvailable(spdlog)
FetchContent_Declare(googletest
                     GIT_REPOSITORY https://github.com/google/googletest
                     GIT_TAG        v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


#add headers
target_include_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include )

#add libdirs
target_link_directories(hithere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#add libs
target_link_libraries(hithere PRIVATE libcurl.lib PRIVATE htmlcxx.lib PRIVATE lualib)


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
set(testdir ${CMAKE_CURRENT_SOURCE_DIR}/tests)
enable_testing()
add_executable(global_test  ${testdir}/global_test.cpp)
target_link_libraries(global_test  GTest::gtest_main)  
include(GoogleTest)
gtest_discover_tests(global_test)

