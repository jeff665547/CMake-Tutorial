#include <iostream>
#include <limits>

#include "add.h"
#include "calc_status.h"

void add(int a, int b){
    Add::calc_status cs{};
    auto const result = Add::add(a, b, cs);
    if(cs == Add::calc_status::success){
        std::cout << a << " + " << b << " = " << result << std::endl;
    } else {
        std::cout << "Error calculating " << a << " + " << b << std::endl;
    }
}

int main(){
    const int a{42};
    const int b{102};

    add(a, b);
    add(a, std::numeric_limits<int>::max());
}