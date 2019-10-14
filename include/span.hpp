#pragma once

#include <stdint.h>

namespace ig {
using size_t = uint64_t;
inline constexpr size_t dynamic_extent = SIZE_MAX;

template<typename ElementType, size_t Extent = dynamic_extent>
class span;

namespace impl {

template <typename E, size_t S>
struct span_storage {
    constexpr span_storage() noexcept = default;

    constexpr span_storage(E* ptr, size_t) noexcept : ptr{ptr} {}

    E* ptr = nullptr;
    static constexpr size_t size = S;
};

template <typename E>
struct span_storage<E, dynamic_extent> {
    constexpr span_storage() noexcept = default;

    constexpr span_storage(E* ptr, size_t size) noexcept : ptr{ptr}, size{size} {}

    E* ptr = nullptr;
    size_t size = 0;
};

template <typename T>
constexpr auto size(T const& c) { return c.size(); }

template <typename T, size_t N>
constexpr size_t size(const T (&)[N]) noexcept { return N; }

} // IMPL END
} // IG END