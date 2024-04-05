FetchContent_Declare(googletest
                     GIT_REPOSITORY https://github.com/google/googletest
                     GIT_TAG        v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
function(add_mytest tesrprojectname)
    add_executable(${tesrprojectname}_test  ${CMAKE_CURRENT_SOURCE_DIR}/${tesrprojectname}_test.cpp)
    target_link_libraries(${tesrprojectname}_test GTest::gtest GTest::gtest_main hitherelib)
    include(GoogleTest)
    add_custom_command(TARGET ${tesrprojectname}_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/runtime
    $<TARGET_FILE_DIR:${tesrprojectname}_test>)
   # gtest_discover_tests(${tesrprojectname}_test)
endfunction()

add_mytest("udprecv")
add_mytest("global")
add_mytest("udpsend")