FetchContent_Declare(googletest
                     GIT_REPOSITORY https://github.com/google/googletest
                     GIT_TAG        v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
function(add_test name)
    add_executable(${name}_test  ${CMAKE_CURRENT_SOURCE_DIR}/${name}_test.cpp)
    target_include_directories(global_test PUBLIC ${includeDirectories} )
    target_link_libraries(${name}_test GTest::gtest GTest::gtest_main hitherelib)
    include(GoogleTest)
    add_custom_command(TARGET ${name}_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/runtime
    $<TARGET_FILE_DIR:${name}_test>)
    gtest_discover_tests(${name}_test)
endfunction()

add_test("global")

add_test("udprecv")

add_test("udpsend")