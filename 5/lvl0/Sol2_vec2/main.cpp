#include "vect2.hpp"
#include <iostream>
#include <cassert>

int main()
{
    std::cout << "===== VECT2 FULL TEST =====" << std::endl;

    // --- Constructors ---
    vect2 a;               // default-initialized? (undefined in C++98, but we’ll assign soon)
    vect2 b(3, 4);
    vect2 c(b);
    vect2 d = b;

    std::cout << "b = " << b << "  c(copy) = " << c << "  d(assign) = " << d << std::endl;
    assert(b == c && c == d);
    std::cout << "Constructors & copy ✅" << std::endl;

    // --- Assignment ---
    vect2 e(10, 20);
    a = e;
    std::cout << "a = " << a << std::endl;
    assert(a == vect2(10, 20));
    std::cout << "Assignment ✅" << std::endl;

    // --- Access operator [] ---
    std::cout << "a[0] = " << a[0] << ", a[1] = " << a[1] << std::endl;
    a[0] = 7;
    a[1] = 8;
    std::cout << "After modification: " << a << std::endl;
    assert(a == vect2(7, 8));
    std::cout << "Operator [] ✅" << std::endl;

    // --- Addition and subtraction ---
    vect2 v1(2, 3);
    vect2 v2(5, 7);
    vect2 sum = v1 + v2;
    vect2 diff = v2 - v1;
    std::cout << v1 << " + " << v2 << " = " << sum << std::endl;
    std::cout << v2 << " - " << v1 << " = " << diff << std::endl;
    assert(sum == vect2(7, 10));
    assert(diff == vect2(3, 4));
    std::cout << "Addition/Subtraction ✅" << std::endl;

    // --- Compound addition/subtraction ---
    vect2 comp(1, 2);
    comp += vect2(3, 4);
    assert(comp == vect2(4, 6));
    comp -= vect2(1, 1);
    assert(comp == vect2(3, 5));
    std::cout << "Compound operators += / -= ✅" << std::endl;

    // --- Scalar multiplication ---
    vect2 scale = v1 * 3;
    vect2 scale2 = 3 * v1;
    std::cout << v1 << " * 3 = " << scale << "   3 * v1 = " << scale2 << std::endl;
    assert(scale == scale2 && scale == vect2(6, 9));
    std::cout << "Scalar multiplication ✅" << std::endl;

    // --- Compound scalar multiplication ---
    vect2 mult(2, 4);
    mult *= 2;
    std::cout << "(2,4) *= 2 → " << mult << std::endl;
    assert(mult == vect2(4, 8));
    std::cout << "Compound scalar multiplication ✅" << std::endl;

    // --- Unary + and - ---
    vect2 neg = -mult;
    vect2 pos = +mult;
    std::cout << "+(4,8) = " << pos << "   -(4,8) = " << neg << std::endl;
    assert(pos == mult);
    assert(neg == vect2(-4, -8));
    std::cout << "Unary + and - ✅" << std::endl;

    // --- Increment and decrement ---
    vect2 inc(1, 1);
    std::cout << "Before: " << inc << std::endl;
    std::cout << "Postfix ++: " << (inc++) << " → now: " << inc << std::endl;
    std::cout << "Prefix ++: " << (++inc) << std::endl;
    std::cout << "Postfix --: " << (inc--) << " → now: " << inc << std::endl;
    std::cout << "Prefix --: " << (--inc) << std::endl;
    std::cout << "Increment/Decrement ✅" << std::endl;

    // --- Comparison ---
    vect2 cmp1(2, 2), cmp2(2, 2), cmp3(3, 4);
    assert(cmp1 == cmp2);
    assert(cmp1 != cmp3);
    std::cout << "Comparison operators ✅" << std::endl;

    // --- Chained operations ---
    vect2 chain(1, 1);
    chain += vect2(2, 3) -= vect2(1, 1);
    std::cout << "Chained operation result: " << chain << std::endl;
    assert(chain == vect2(2, 3));
    std::cout << "Chained ops ✅" << std::endl;

    // --- Stress test (loop incrementing) ---
    vect2 counter(0, 0);
    for (int i = 0; i < 50; ++i)
        ++counter;
    std::cout << "After 50 increments: " << counter << std::endl;
    assert(counter == vect2(50, 50));
    std::cout << "Stress test ✅" << std::endl;

    std::cout << "\nAll vect2 tests passed 🎯" << std::endl;

        // --- Advanced chained and mixed operations ---
    chain = (vect2(1, 2) + vect2(3, 4)) * 2;
    std::cout << "(1,2)+(3,4))*2 = " << chain << std::endl;
    assert(chain == vect2(8, 12));

    chain = 2 * ((vect2(5, 5) - vect2(2, 3)) * 3);
    std::cout << "2 * ((5,5)-(2,3))*3 = " << chain << std::endl;
    assert(chain == vect2(18, 12));

    chain = vect2(1, 1);
    chain += vect2(2, 3) *= 2; // compound inside compound
    std::cout << "chain += vect2(2,3)*=2 → " << chain << std::endl;
    assert(chain == vect2(5, 7));

    std::cout << "Advanced mixed/chained ops ✅" << std::endl;


    return 0;
}
