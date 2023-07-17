cmake_minimum_required(VERSION 3.0)
project(MatTerminal)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
add_library(${PROJECT_NAME} SHARED
    src/Terminal.cpp
    include/Terminal.h
    include/OperationFactory.h
    include/Operation.h
)
target_link_libraries(${PROJECT_NAME})

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME})