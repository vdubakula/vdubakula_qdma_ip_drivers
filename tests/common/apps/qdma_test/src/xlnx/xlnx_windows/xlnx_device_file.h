#pragma once

#include <iostream>
#include <string>
#include <system_error>

#include <fcntl.h>
#include <sys/types.h>

#include <errno.h>

#include <time.h>

#include <Windows.h>
#include <SetupAPI.h>
#include <INITGUID.H>

#define MSEC2NSEC 1000000
// device file class for os agnostic handling of device files

inline static std::string get_last_win_err_msg() {
    char tmp[256] = { '\0' };
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), tmp, 256, NULL);

    return{ tmp, strlen(tmp) };
}

class device_file {
public:
    HANDLE h;
    device_file();
    device_file(const std::string& path, DWORD accessFlags);
    ~device_file();

    //device_file(const device_file& rhs) = delete;
    //device_file& operator=(const device_file& rhs) = delete;

    //device_file(device_file && rhs);

    //device_file& operator=(device_file&& rhs);

    void open(const std::string& path, DWORD accessFlags);

    void close();

    template <typename T>
    void write(size_t address, const T value);

    template <typename T>
    T read(size_t address);

    void seek(long device_offset);
    size_t write(void* buffer, size_t size, bool throw_err = true);
    size_t read(void* buffer, size_t size, bool throw_err = true);

    size_t ioctl(int code, void* inData = nullptr, DWORD inSize = 0, void* outData = nullptr,
        DWORD outSize = 0, bool throw_err = true);
};

inline device_file::device_file() : h(INVALID_HANDLE_VALUE) {};

inline void device_file::open(const std::string& path, DWORD accessFlags) {
    h = CreateFile(path.c_str(), accessFlags, 0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("CreateFile control failed: " + get_last_win_err_msg());
    }
}

inline void device_file::close() {
    if (h != INVALID_HANDLE_VALUE) {
        CloseHandle(h);
        h = INVALID_HANDLE_VALUE;
    }
}

inline device_file::device_file(const std::string& path, DWORD accessFlags) : h(INVALID_HANDLE_VALUE) {
    open(path, accessFlags);
}

inline device_file::~device_file() {
    close();
}

inline void device_file::seek(long device_offset) {
    if (INVALID_SET_FILE_POINTER == SetFilePointer(h, device_offset, NULL, FILE_BEGIN)) {
        throw std::runtime_error("SetFilePointer failed: " + get_last_win_err_msg());
    }
}

inline size_t device_file::write(void* buffer, size_t size, bool throw_err) {
    unsigned long num_bytes_written;
    
    auto ret = WriteFile(h, buffer, (DWORD)size, &num_bytes_written, NULL);
    if (!ret && throw_err)
        throw std::runtime_error("Failed to write to device! " + get_last_win_err_msg());

    return num_bytes_written;
}

template <typename T>
inline void device_file::write(size_t addr, T t) {
    seek((long)addr);
    unsigned long num_bytes_written;
    if (!WriteFile(h, &t, sizeof(T), &num_bytes_written, NULL)) {
        throw std::runtime_error("Failed to write to device! " + get_last_win_err_msg());
    }
    else if (num_bytes_written != sizeof(T)) {
        throw std::runtime_error("Failed to write all bytes!");
    }
}

inline size_t device_file::read(void* buffer, size_t size, bool throw_err) {
    unsigned long num_bytes_read;

    auto ret = ReadFile(h, buffer, (DWORD)size, &num_bytes_read, NULL);
    if (!ret && throw_err)
        throw std::runtime_error("Failed to read from device! " + get_last_win_err_msg());
    return num_bytes_read;
}

template <typename T>
inline T device_file::read(size_t addr) {
    seek((long)addr);
    T buffer;
    unsigned long num_bytes_read;
    if (!ReadFile(h, &buffer, sizeof(T), &num_bytes_read, NULL)) {
        throw std::runtime_error("Failed to read from device! " + get_last_win_err_msg());
    }
    else if (num_bytes_read != sizeof(T)) {
        throw std::runtime_error("Failed to read all bytes!");
    }
    return buffer;
}

inline size_t device_file::ioctl(int code, void* inData, DWORD inSize, void* outData, DWORD outSize, bool throw_err) {

    DWORD nb = 0;
    BOOL success = DeviceIoControl(h, code, inData, inSize, outData, outSize, &nb, NULL);
    if (!success && throw_err) {
        //throw std::runtime_error("ioctl failed!\t" + get_last_win_err_msg());
		std::cerr << "ioctl failed!\t" + get_last_win_err_msg();
    }
    return success;
}
