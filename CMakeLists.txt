cmake_minimum_required(VERSION 3.28)
project(project_tp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)


add_executable(project_tp test.cpp)

find_package(doctest CONFIG REQUIRED)
target_link_libraries(project_tp PRIVATE doctest::doctest)


find_package(OpenMP REQUIRED)

if (OpenMP_CXX_FOUND)
    target_compile_options(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_LIBRARIES})
else ()
    message(FATAL_ERROR "OpenMP не найден. Убедитесь, что ваш компилятор поддерживает OpenMP.")
endif()