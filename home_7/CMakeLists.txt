cmake_minimum_required(VERSION 3.2)

project(Bulk)

find_package(GTest REQUIRED)

add_executable(Bulk main.cpp)
add_executable(test test.cpp)

set_target_properties(Bulk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(Bulk
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(test GTest::GTest GTest::Main)

if (MSVC)
    target_compile_options(Bulk PRIVATE
        /W4
    )
    target_compile_options(test PRIVATE
        /W4
    )
else ()
    target_compile_options(Bulk PRIVATE
        -Wall -Wextra -pedantic 
    )
    target_compile_options(test PRIVATE
        -Wall -Wextra -pedantic 
    )
endif()

install(TARGETS Bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT chichkanff@gmail.com)

include(CPack)
