
# Finding and setting the clang compiler
find_program(CMAKE_C_COMPILER clang)
find_program(CMAKE_CXX_COMPILER clang++)
find_program(CMAKE_ASM_COMPILER clang)

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "clang not found.")
endif()

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "clang++ not found.")
endif()

set(CMAKE_C_COMPILER "${CMAKE_C_COMPILER}" CACHE STRING "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "${CMAKE_CXX_COMPILER}" CACHE STRING "C++ compiler" FORCE)

# Setting up the rest of the LLVM tools
get_filename_component(__llvm_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)

set(CMAKE_AR "${__llvm_dir}/llvm-ar" CACHE FILEPATH "Archiver" FORCE)
set(CMAKE_LINKER "${__llvm_dir}/ld.lld" CACHE FILEPATH "Linker" FORCE)
set(CMAKE_NM "${__llvm_dir}/llvm-nm" CACHE FILEPATH "Symbol table dumper" FORCE)
set(CMAKE_OBJDUMP "${__llvm_dir}/llvm-objdump" CACHE FILEPATH "Objdump" FORCE)
set(CMAKE_OBJCOPY "${__llvm_dir}/llvm-objcopy" CACHE FILEPATH "Objcopy" FORCE)
set(CMAKE_RANLIB "${__llvm_dir}/llvm-ranlib" CACHE FILEPATH "Ranlib" FORCE)

unset(__llvm_dir)

#Setting up c++ runtime
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>" CACHE STRING "" FORCE)
