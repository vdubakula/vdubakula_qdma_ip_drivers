#pragma once

#include <algorithm>
#include <cstring>
#include <vector>

#include "xlnx_os.h"

//======================== Bit manipulations =======================================================

static constexpr uint32_t bit(uint64_t n) {
    return (1ull << n);
}

static constexpr bool is_bit_set(uint64_t x, uint64_t n) {
    return (x & bit(n)) == bit(n);
}

static constexpr uint64_t create_mask(uint64_t n, uint64_t l) {
    return ((1ull << l) - 1ull) << n;
}

static constexpr uint32_t get_bits(uint32_t value, uint32_t bit_index, uint32_t len) {
    return ((value & create_mask(bit_index, len)) >> bit_index);
}

//======================== literal suffix operators ================================================

constexpr uint32_t operator"" _kB(const unsigned long long num) {
    return static_cast<uint32_t>(num) * 1024UL;
}

constexpr uint32_t operator"" _MB(const unsigned long long num) {
    return static_cast<uint32_t>(num) * 1024UL * 1_kB;
}

constexpr uint32_t operator"" _GB(const unsigned long long num) {
    return static_cast<uint32_t>(num) * 1024UL * 1_MB;
}

//======================== memory ==================================================================

/// allocator which uses _aligned_malloc to ensure allocations are aligned to a specified alignment.
/// is page aligned (4096 Bytes) by default.
/// can be used by std containers such as vector. e.g:
/// @code
/// - std::vector<int, aligned_allocator<int, 64>> my_aligned_vec; // vector with internal data alignment of 64 bytes.
/// - std::vector<int, aligned_allocator<int>> my_aligned_vec; // vector with internal data alignment of 4096 bytes.
template<typename T, size_t Alignment = 4096>
struct aligned_allocator {

    typedef T value_type;

    aligned_allocator() noexcept {} //default ctor not required by STL
    // A converting copy constructor:  
    template<class U> 
    aligned_allocator(const aligned_allocator<U, Alignment>&) noexcept {}

    template<class U> 
    bool operator==(const aligned_allocator<U>&) const noexcept
    {
        return true;
    }
    template<class U> 
    bool operator!=(const aligned_allocator<U>&) const noexcept
    {
        return false;
    }

    T* allocate(const std::size_t num) {
        if (num == 0) {
            return nullptr;
        }

        void* const ptr = xlnx::os::aligned_alloc(num * sizeof(T), Alignment);
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(ptr);
    }
    void deallocate(T* const p, std::size_t) {
        if (p) {
            xlnx::os::aligned_free(p);
        }
    }

    template<typename T2>
    struct rebind {
        typedef aligned_allocator<T2, Alignment> other;
    };
};

template<typename T, size_t N = 4096>
using aligned_vector = std::vector<T, aligned_allocator<T, N>>;

//======================== string manipulation =================================

inline std::vector<std::string> split(const char *str, char c = ' ') {
    std::vector<std::string> result;

    auto begin = str;
    const auto end = str + strlen(str);
    while (begin != end) {
        auto it = std::find(begin, end, c);
        result.emplace_back(begin, it);
        begin = it + 1;
    }

    return result;
}

inline std::string int_to_hex(int num) {

	std::stringstream sstream;
	sstream << std::hex << num;
	std::string num_hex = sstream.str();

	return num_hex;
}

