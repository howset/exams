#include "bigint.hpp"
#include <iostream>
#include <cassert>

int main()
{
    std::cout << "===== BIGINT FULL TEST =====" << std::endl;

    // --- Constructors ---
    bigint a;                        // default constructor
    bigint b(12345);                 // from unsigned int
    bigint c("67890");               // from string
    bigint d("0000123");             // with leading zeros
    bigint e("abc");                 // invalid input

    std::cout << "a = " << a << " (default)" << std::endl;
    std::cout << "b = " << b << " (from unsigned int)" << std::endl;
    std::cout << "c = " << c << " (from string)" << std::endl;
    std::cout << "d = " << d << " (leading zeros removed)" << std::endl;
    std::cout << "e = " << e << " (invalid string → 0)" << std::endl;

    assert(a == bigint("0"));
    assert(b == bigint("12345"));
    assert(c == bigint("67890"));
    assert(d == bigint("123"));
    assert(e == bigint("0"));
    std::cout << "Constructors ✅" << std::endl;

    // --- Addition ---
    bigint x("999");
    bigint y("1");
    bigint z = x + y;                // 999 + 1 = 1000
    std::cout << "999 + 1 = " << z << std::endl;
    assert(z == bigint("1000"));

    bigint s1("123456789");
    bigint s2("987654321");
    bigint s3 = s1 + s2;             // 123456789 + 987654321 = 1111111110
    std::cout << "123456789 + 987654321 = " << s3 << std::endl;
    assert(s3 == bigint("1111111110"));
    std::cout << "Addition ✅" << std::endl;

    // --- Operator += ---
    bigint addEq("50");
    addEq += bigint("25");
    std::cout << "50 += 25 → " << addEq << std::endl;
    assert(addEq == bigint("75"));
    std::cout << "Operator += ✅" << std::endl;

    // --- Comparisons ---
    bigint p("123"), q("124"), r("123");
    assert(p == r);
    assert(p != q);
    assert(p < q);
    assert(q > p);
    assert(p <= r);
    assert(q >= p);
    std::cout << "Comparisons ✅" << std::endl;

    // --- Shift operators (unsigned int) ---
    bigint sft1("123");
    bigint sft2 = sft1 << 2;         // multiply by 100
    bigint sft3 = sft1 >> 1;         // divide by 10
    std::cout << "123 << 2 = " << sft2 << std::endl;
    std::cout << "123 >> 1 = " << sft3 << std::endl;
    assert(sft2 == bigint("12300"));
    assert(sft3 == bigint("12"));
    std::cout << "Shift operators ✅" << std::endl;

    // --- Compound shifts (unsigned int) ---
    bigint shiftEq("1234");
    shiftEq <<= 2;                   // multiply by 100
    std::cout << "1234 <<= 2 → " << shiftEq << std::endl;
    shiftEq >>= 3;                   // divide by 1000
    std::cout << "then >>= 3 → " << shiftEq << std::endl;
    assert(shiftEq == bigint("123"));
    std::cout << "Compound shifts ✅" << std::endl;

    // --- Shift operators (const bigint&) ---
    bigint shBig("12345");
    bigint two("2");
    std::cout << "shBig <<= (const bigint)2 → " << (shBig <<= two) << std::endl;

    bigint shBig2("12345");
    std::cout << "shBig2 >>= (const bigint)2 → " << (shBig2 >>= two) << std::endl;
    std::cout << "Bigint shift by bigint ✅" << std::endl;

    // --- Increment operators ---
    bigint inc("9");
    std::cout << "++9 → " << ++inc << std::endl; // prefix (++9 = 10)
    assert(inc == bigint("10"));

    bigint post("19");
    bigint old = post++;
    std::cout << "post++: old=" << old << ", new=" << post << std::endl;
    assert(old == bigint("19"));
    assert(post == bigint("20"));
    std::cout << "Increment operators ✅" << std::endl;

    // --- Zero handling ---
    bigint zero("0");
    bigint sum = zero + bigint("123");
    std::cout << "0 + 123 = " << sum << std::endl;
    assert(sum == bigint("123"));
    assert((zero << 5) == bigint("0"));
    assert((zero >> 5) == bigint("0"));
    std::cout << "Zero handling ✅" << std::endl;

    // --- Leading zero cleanup ---
    bigint leading("00000123");
    bigint clean = leading + bigint("0");
    std::cout << "00000123 + 0 = " << clean << std::endl;
    assert(clean == bigint("123"));
    std::cout << "Leading zero cleanup ✅" << std::endl;

    // --- Stress test ---
    bigint counter("0");
    for (int i = 0; i < 50; i++)
        ++counter;
    std::cout << "Incremented 50 times: " << counter << std::endl;
    assert(counter == bigint("50"));
    std::cout << "Stress test ✅" << std::endl;

    std::cout << "\nAll tests passed 🎯" << std::endl;
    return 0;
}

