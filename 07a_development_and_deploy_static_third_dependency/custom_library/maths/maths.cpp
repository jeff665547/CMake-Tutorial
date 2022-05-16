#include "maths_header/maths.h"

#include <subtract_header/subtract.h>
#include <add_header/add.h>


#include <limits>

int Maths::add(int l, int r, calc_status& cs) noexcept {
    return Add::add(l, r, cs);
}

int Maths::subtract(int l, int r, calc_status& cs) noexcept {
    return Subtract::subtract(l, r, cs);
}