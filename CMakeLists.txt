cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})


# имя проекта
project(ip_filter_prj VERSION ${PROJECT_VESRION})


# пусть будет - потом добавлю автотесты
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#нет у нас такого пока - вроде не требуется
#configure_file(version.h.in version.h)


# основной исполнимый файл
add_executable(ip_filter 
main.cpp
#work_obj.cpp
)

add_library(work_lib work_obj.cpp)

add_executable(unit_tests unit_tests.cpp)


set_target_properties(ip_filter work_lib unit_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)


set_target_properties(unit_tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter PRIVATE
    work_lib
)

target_link_libraries(unit_tests
    ${Boost_LIBRARIES}
    work_lib
)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(work_lib PRIVATE
        /W4
    )
    target_compile_options(unit_tests PRIVATE
        /W4
    )



else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(work_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(unit_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


enable_testing()
add_test(unit_tests unit_tests)
