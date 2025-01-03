
cmake_minimum_required(VERSION 3.14)
set(PROJECT_VERSION 0.0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hw-04-sfinae VERSION ${PROJECT_VERSION})

add_executable(hw-04-sfinae main.cpp)

enable_testing()

add_executable(hw-04-tests tests.cpp)

set_target_properties(hw-04-sfinae hw-04-tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# adding googletest
set(GOOGLETEST_PATH ~/local/googletest)
set(GTEST_INCLUDE_DIR ~/local/include/)
set(GTEST_LIBRARY ~/local/lib/)
set(GTEST_MAIN_LIBRARY ~/local/lib/)
find_package(GTest REQUIRED)

include(GoogleTest)
gtest_discover_tests(hw-04-tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)

target_link_libraries(hw-04-tests
    GTest::gtest_main
)

install(TARGETS hw-04-sfinae RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT max.golovatyi@gmail.com)
include(CPack)
