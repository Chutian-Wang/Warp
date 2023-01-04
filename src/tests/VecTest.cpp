#include <iostream>
#include "../Vec.h"

int main() {
    Vec a(1,2,3);
    Vec b(2,3,4);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a dot b = " << dot(a, b) << std::endl;
    std::cout << "a cross b = " << cross(a, b) << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * 2.3 = " << (a * 2.3) << std::endl;
    std::cout << "a / 2.3 = " << (a / 2.3) << std::endl;
    std::cout << "2.3 * a = " << (2.3 * a) << std::endl;
    std::cout << "unit vector a = " << a.unify() << std::endl;
    std::cout << "unit vector b = " << unit(b) << std::endl;
    return 0;
}