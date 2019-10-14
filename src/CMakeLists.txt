cmake_minimum_required(VERSION 3.15.4)

project(SrcDir CXX ASM)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
        utils.S
        boot.S
        kernel.cpp
        mini_uart.cpp
        mm.S
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_options(${PROJECT_NAME}
    INTERFACE
        -nostdlib
        -m aarch64elf
        -T${CMAKE_CURRENT_LIST_DIR}/linker.ld
)

target_compile_options(${PROJECT_NAME}
    INTERFACE
        -O2
        -flto
        -ffreestanding
        -nostdlib
        -Wall
        -mgeneral-regs-only
        -fno-exceptions
        -fno-rtti
        --target=aarch64-elf
        -march=armv8-a
)
