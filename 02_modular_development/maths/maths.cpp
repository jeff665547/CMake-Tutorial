#include "maths.h"

#include <subtract.h>
#include <add.h>


#include <limits>

int Maths::add(int l, int r, calc_status& cs) noexcept {
    return Add::add(l, r, cs);
}

int Maths::subtract(int l, int r, calc_status& cs) noexcept {
    return Subtract::subtract(l, r, cs);
}