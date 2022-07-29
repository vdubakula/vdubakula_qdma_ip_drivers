#pragma once

#include <string>
#include <system_error>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <libaio.h>
#include <time.h>

#define MSEC2NSEC 1000000
// device file class for os agnostic handling of device files
class device_file {
public:

    using df_handle = int;

    enum class access {
        ro = O_RDONLY,
        wo = O_WRONLY,
        rw = O_RDWR
    };

    device_file();
    explicit device_file(const char* path, access flags = access::rw);
    explicit device_file(const std::string&  path, access flags = access::rw);

    ~device_file();

    device_file(const device_file& rhs) = delete;
    device_file& operator=(const device_file& rhs) = delete;

    // Define move constructor and move assignment
    device_file(device_file && rhs); 
    device_file& operator=(device_file&& rhs);

    void open(const char* path, access flags = access::rw);
    void open(const std::string& path, access flags = access::rw);
    void close();

    void seek(long device_offset);

    size_t read(void* buffer, size_t size);
    size_t write(void* buffer, size_t size);
    int aio_rw(io_context_t ctxt, int num_jobs, struct iocb **io_list);

    template <typename T>
    T read(long address);

    template <typename T>
    void write(long address, const T value);

    size_t ioctl(int code, void* inData = nullptr);

    df_handle get_handle();
    std::string dev_path;

private:
    df_handle h; //device file handle
};

inline device_file::device_file() : h(-1) {}

inline void device_file::open(const char* path, access flags) {
    h = ::open(path, static_cast<int>(flags));
    if (h < 0) {
        throw std::system_error(errno, std::system_category(), "Failed to open device! " + std::string(path));
    }
}

inline void device_file::open(const std::string& path, access flags) {
    h = ::open(path.c_str(), static_cast<int>(flags));
    if (h < 0) {
        throw std::system_error(errno, std::system_category(), "Failed to open device!" + std::string(path));
    }
}

inline void device_file::close() {
    if (h > -1) {
        ::close(h);
        h = -1;
    }
}

inline device_file::device_file(const char* path, access flags) {
    open(path, flags);
}

inline device_file::device_file(const std::string&  path, access flags) {
    open(path, flags);
}

inline device_file::~device_file() {
    close();
}

inline device_file::device_file(device_file && rhs)
    : h(-1) {
    *this = std::move(rhs);
}

inline device_file& device_file::operator=(device_file&& rhs) {
    if (this != &rhs) {
        h = rhs.h; //pilfer
        rhs.h = -1; //reset
    }
    return *this;
}

inline void device_file::seek(long device_offset) {
    off_t rc = ::lseek(h, device_offset, SEEK_SET);
    if (rc < 0) {
        throw std::system_error(errno, std::system_category(), "seek device failed!");
    }
}

inline size_t device_file::read(void* buffer, size_t size) {
    unsigned long num_bytes_read;
    num_bytes_read = ::read(h, buffer, size);
    if (num_bytes_read != size) {
        throw std::system_error(errno, std::system_category(), "read from device failed!");
    }
    return num_bytes_read;
}

inline int device_file::aio_rw(io_context_t ctxt, int num_jobs, struct iocb **io_list) {
    int ret = ::io_submit(ctxt, num_jobs, io_list);
    struct timespec ts_cur;
    struct io_event *events;

    if (ret != num_jobs) {
        printf("failed with %d actual %d\n", ret, num_jobs);
        throw std::system_error(errno, std::system_category(), "io not submitted");
        return ret;
    }
    ts_cur.tv_sec = 10;
    events = (struct io_event *)calloc(num_jobs, sizeof(struct io_event));
    if (io_getevents(ctxt,
                     num_jobs,
                     num_jobs,
                     events,
                     &ts_cur) != num_jobs) {
        free(events);
	throw std::system_error(errno, std::system_category(), "io timeout");
	return 0;
    }
    for (int i = 0; i < num_jobs; i++) {
        if (events[i].res2 != 0) {
		free(events);
		throw std::system_error(errno, std::system_category(), "io failed");
		return events[i].res2;
        }
    }
    free(events);

    return 0;
}

template <typename T>
T device_file::read(long address) {
    seek(address);
    T val;
    read(&val, sizeof(val));
    return val;
}

inline size_t device_file::write(void* buffer, size_t size) {
    size_t num_bytes_written = ::write(h, buffer, size);
    if (num_bytes_written != size) {
        throw std::system_error(errno, std::system_category(), "write to device failed!");
    }
    return num_bytes_written;
}

template <typename T>
void device_file::write(long address, const T value) {
    seek(address);
    write(value, sizeof(T));
}

inline size_t device_file::ioctl(int code, void* inData) {
    size_t rc = ::ioctl(h, code, inData);
    if (rc != 0) {
        throw std::system_error(errno, std::system_category(), "ioctl to device failed!");
    }
    return rc;
}

inline device_file::df_handle device_file::get_handle() {
    return h;
}
