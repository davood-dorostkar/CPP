if(BUILD_TESTING)
    add_executable(mytest main.cpp)
    target_link_libraries(mytest PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(mytest)
endif()
