#pragma once



#ifndef __ASSEMBLER__
#include <stdint.h>

extern "C" void memzero(uint64_t src, uint64_t n);

constexpr uint32_t PAGE_SHIFT =             12U;
constexpr uint32_t TABLE_SHIFT =            9U;
constexpr uint32_t SECTION_SHIFT =          PAGE_SHIFT + TABLE_SHIFT;

constexpr uint32_t PAGE_SIZE =              1U << PAGE_SHIFT;
constexpr uint32_t SECTION_SIZE =           1U << SECTION_SHIFT;

constexpr uint32_t LOW_MEMORY =             2U * SECTION_SIZE;
#else

#define PAGE_SHIFT              12
#define TABLE_SHIFT             9
#define SECTION_SHIFT           (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE               (1 << PAGE_SHIFT)
#define SECTION_SIZE            (1 << SECTION_SHIFT)

#define LOW_MEMORY              (2 * SECTION_SIZE)


#endif



