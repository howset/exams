#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

class bigint 
{
private:
	std::string data; //strores digits as string
public:
	bigint (void);
	bigint (unsigned long long src);
	bigint (bigint const &src);

	bigint operator+(bigint const &rhs) const; //returns new object doesn't modidy original;
	bigint &operator+=(bigint const &rhs); //modifies and return *this
	
	
	bigint& operator ++(void); // Prefix ++x: modify and return modified object
	bigint operator ++(int); // Postfix x++: return original, then modify

	 // Comparison operators - all const because they don't modify object
	bool operator < (const bigint &other) const;
	bool operator > (const bigint &other) const;
	bool operator == (const bigint &other) const;
	bool operator != (const bigint &other) const;
	bool operator <= (const bigint &other) const;
	bool operator >= (const bigint &other) const;

	// Bit shift operators
    bigint operator<<(unsigned int shift) const;    // x << n: Returns new shifted number
    bigint& operator<<=(unsigned int shift);        // x <<= n: Modifies and returns *this
    bigint operator>>(unsigned int shift) const;    // x >> n: Returns new shifted number
    bigint& operator>>=(unsigned int shift);        // x >>= n: Modifies and returns *this

	bigint operator<<(bigint shift) const;    // x << n: Returns new shifted number
    bigint& operator<<=(bigint shift);        // x <<= n: Modifies and returns *this
    bigint operator>>(const bigint shift) const;    // x >> n: Returns new shifted number
    bigint& operator>>=(const bigint shift);        // x >>= n: Modifies and returns *this

    // Subtraction (mentioned in main.cpp)
    bigint operator-(const bigint& rhs) const;  // Returns new object
	// std::string getdata()const;  

	friend std::ostream& operator << (std::ostream& os, const bigint& fp);
};


#endif