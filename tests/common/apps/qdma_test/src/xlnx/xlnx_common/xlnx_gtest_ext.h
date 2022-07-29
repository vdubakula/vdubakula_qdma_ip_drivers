#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

// =========================== gtest helper functions =============================================

template<typename T>
inline std::string to_hex_string(T t) {
    std::ostringstream oss;
    oss << "0x" << std::hex << t;
    return oss.str();
}

// A predicate-formatter for asserting that two values are equal. Prints values in hex format
inline ::testing::AssertionResult hex_equal(const char* m_expr,
        const char* n_expr, uint64_t m, uint64_t n) {
    if (m == n)
        return ::testing::AssertionSuccess();

    return ::testing::AssertionFailure() << "expressions " << m_expr << " and "
            << n_expr << " are not equal:\n" << " Actual:\t" << to_hex_string(m)
            << "\n" // for some reason std::hex does not work
            << " Expected:\t" << to_hex_string(n);
}

inline void write_data_to_file(uint8_t* buffer, const size_t size,
        const char* tag = "") {
    const auto test_info =
            testing::UnitTest::GetInstance()->current_test_info();
    auto file_name_str = std::string(test_info->test_case_name()) + "_"
            + test_info->name() + tag;
    replace(file_name_str.begin(), file_name_str.end(), '/', '_'); // replace all '/' to '_'
    std::ofstream data_file(file_name_str,
            std::ios::trunc | std::ios::out | std::ios::binary);
    if (!data_file) {
        throw std::runtime_error("failed to write to file!");
    }
    copy(buffer, buffer + size, std::ostream_iterator<uint8_t>(data_file));
}

template <typename It>
static std::string print_diffs(const It& b1_begin, const It& b1_end, const It& b2_begin,
                               size_t diff_limit = 10) {

    std::ostringstream ss;
    ss << "idx\t| expected\t| actual\n" << std::hex << std::showbase;
    unsigned idx = 0;
    unsigned count = 0;
    for (auto it1 = b1_begin, it2 = b2_begin;
            it1 != b1_end && count < diff_limit;
            it1++, it2++, idx++) {
        if (*it1 != *it2) {
            ss << idx << ":\t| " << unsigned(*it1) << "\t\t| " << unsigned(*it2) << "\n";
            count++;
        }
    }
    return ss.str();
}

#define EXPECT_HEX_EQ(actual, expected) EXPECT_PRED_FORMAT2(hex_equal, (actual), (expected))
#define ASSERT_HEX_EQ(actual, expected) ASSERT_PRED_FORMAT2(hex_equal, (actual), (expected))
