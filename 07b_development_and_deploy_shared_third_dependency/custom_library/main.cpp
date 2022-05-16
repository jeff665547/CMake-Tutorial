#include <iostream>
#include <limits>
#include <maths_header/maths.h>
#include <calc_log.hpp>

void use_add(int a, int b){
    Maths::calc_status cs{};
    auto const result = Maths::add(a, b, cs);
    if (cs == Maths::calc_status::success){
        std::cout << a << " + " << b << " = " << result << std::endl;
    } else {
        std::cout << "This is error calculating " << a << " + " << b << std::endl;
    }
}

int main(){
    const int a{42};
    const int b{102};

    STATUS::PrintLogVersion();
    STATUS::SayHello();

    use_add(a, b);
    use_add(a, std::numeric_limits<int>::max());
}