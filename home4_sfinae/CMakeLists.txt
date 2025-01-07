
cmake_minimum_required(VERSION 3.14)
set(PROJECT_VERSION 0.0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(print_ip VERSION ${PROJECT_VERSION})

add_executable(print_ip main.cpp)

enable_testing()

add_executable(print_ip-tests tests.cpp)

set_target_properties(print_ip print_ip-tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)


find_package(GTest REQUIRED)

include(GoogleTest)
gtest_discover_tests(print_ip-tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)

target_link_libraries(print_ip-tests
    GTest::gtest_main
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT chichkanff@gmail.com)
include(CPack)
