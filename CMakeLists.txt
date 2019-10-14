cmake_minimum_required(VERSION 3.15.4)

project(IgnisOS CXX ASM)

add_executable(${PROJECT_NAME} "")

add_subdirectory(src)
add_subdirectory(include)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        IncludeDir
        SrcDir
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        SUFFIX ".elf"
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

#target_compile_options(${PROJECT_NAME}
#    PUBLIC
#        -ffreestanding
#        -nostdlib 
#        --target=aarch64-elf
#        -march=armv8-a 
#)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/kernel8.img
    COMMENT "Building the image."
)
