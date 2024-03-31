FetchContent_Declare(googletest
                     GIT_REPOSITORY https://github.com/google/googletest
                     GIT_TAG        v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(global_test  ${CMAKE_CURRENT_SOURCE_DIR}/global_test.cpp)
target_include_directories(global_test PUBLIC ${includeDirectories} )
target_link_libraries(global_test GTest::gtest GTest::gtest_main hitherelib)
include(GoogleTest)

add_custom_command(TARGET global_test POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory 
${CMAKE_CURRENT_SOURCE_DIR}/runtime
$<TARGET_FILE_DIR:global_test>)


gtest_discover_tests(global_test)