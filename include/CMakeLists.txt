cmake_minimum_required(VERSION 3.15.4)

project(IncludeDir CXX ASM)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
        mini_uart.hpp
        mm.hpp
        utils.hpp
        peripherals/base.hpp
        peripherals/gpio.hpp
        peripherals/mini_uart.hpp
        type_traits.hpp
        byte.hpp
        span.hpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)
