#include "bigint.hpp"


int main()
{

    const bigint a(42);
    bigint b(21), c, d(1337), e(d);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "a+b " << a + b << std::endl;
    std::cout << "c+=a " << (c += a) << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "++b " << ++b << std::endl;
    std::cout << "b++ " << b++ << std::endl;
    std::cout << "(b << 10) + 42 " << (b << 10) + 42 << std::endl;
    std::cout << "d<<=4 " << (d <<= 4) << std::endl;
    std::cout << "d>>=(const bigint)2 " << (d >>= (const bigint)122) << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "d < a " << (d < a) << std::endl;
    std::cout << "d > a " << (d > a) << std::endl;
    std::cout << "d == a " << (d == a) << std::endl;
    std::cout << "d != a " << (d != a) << std::endl;
    std::cout << "d <= a " << (d <= a) << std::endl;
    std::cout << "d >= a " << (d >= a) << std::endl;

    // step 6: extra test from exam
    std::cout << a - a << std::endl;
    d = bigint(123566344);
    c = bigint(1234);
    std::cout << "d>>=(const bigint)2 " << (d >>= (const bigint)122) << std::endl;
    std::cout << "d>>=(const bigint)2 " << (c <<= (const bigint)122) << std::endl;

    return 0;
}