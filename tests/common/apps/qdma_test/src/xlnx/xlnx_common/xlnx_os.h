#pragma once

#include <array>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <system_error>

namespace xlnx {
namespace os {

    static void* aligned_alloc(size_t size, size_t alignment);
    static void aligned_free(void* ptr);
    static std::string execute_command(const char* cmd);

} // namespace os
} // namespace xlnx

inline void* xlnx::os::aligned_alloc(size_t size, size_t align) {
#ifdef __linux__
    void * ptr = ::aligned_alloc(align, size);
    if(ptr == 0)
    {
        perror("alignment");
    }
#elif _WIN32
    void * ptr = _aligned_malloc(size, align);
#endif
    return ptr;
}

inline void xlnx::os::aligned_free(void* ptr) {
#ifdef __linux__
    free(ptr);
#elif _WIN32
    _aligned_free(ptr);
#endif
}

#ifndef _WIN32
inline std::string xlnx::os::execute_command(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::system_error(errno, std::system_category(), "popen() failed!");
    }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}
#endif