#pragma once

namespace STATUS{
enum class calc_status {
    success = 0,
    positive_overflow,
    negative_overflow,
    range_error
};
}