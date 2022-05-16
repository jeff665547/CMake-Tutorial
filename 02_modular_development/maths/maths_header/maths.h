#pragma once

#include <calc_status.h>

namespace Maths{
using STATUS::calc_status;

int add(int l, int r, calc_status& cs) noexcept;
int subtract(int l, int r, calc_status& cs) noexcept;

}