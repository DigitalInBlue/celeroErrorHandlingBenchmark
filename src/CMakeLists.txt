project(benchmark)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME})

find_package(celero CONFIG REQUIRED)

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    celero
)

