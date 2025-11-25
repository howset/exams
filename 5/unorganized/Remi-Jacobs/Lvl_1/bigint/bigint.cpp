#include "bigint.hpp"

	bigint::bigint (void)
	{
		this->data = "0";
	}
	bigint::bigint (unsigned long long src)
	{
		this->data = std::to_string(src);
	}
	bigint::bigint(bigint const &src)
	{
		this->data = src.data;
	}

	//returns new object doesn't modidy original;
	bigint bigint::operator+(bigint const &rhs)const
	{
		bigint result;
		std::string num1 = this->data;
		std::string num2 = rhs.data;
		std::string res;
		int carry = 0;

		while(num1.length() < num2.length())
			num1 = "0" + num1;

		while(num2.length() < num1.length())
			num2 = "0" + num2;
		for(int i = num1.length() -1; i>= 0; i--)
		{
			int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
			carry = sum / 10;
			res = char(sum % 10 + '0') + res;
		}
		if (carry)
			res = '1' + res;
		while (res.length() > 1 && res[0] == '0')
			res.erase(0,1);
		result.data = res;
		return result;

	} 
	//modifies and return *this
	bigint& bigint::operator+=(bigint const &rhs)
	{
		std::string num1 = this->data;
		std::string num2 = rhs.data;
		std::string res;
		int carry = 0;

		while(num1.length() < num2.length())
			num1 = "0" + num1;

		while(num2.length() < num1.length())
			num2 = "0" + num2;
		for(int i = num1.length() -1; i>= 0; i--)
		{
			int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
			carry = sum / 10;
			res = char(sum % 10 + '0') + res;
		}
		if (carry)
			res = '1' + res;
		while (res.length() > 1 && res[0] == '0')
			res.erase(0,1);
		this->data = res;
		return *this;

	} 
	
	// Prefix ++x: modify and return modified object
	bigint& bigint:: operator ++(void)
	{
		*this += bigint(1);
		return *this;

	} 
	// Postfix x++: return original, then modify
	bigint bigint:: operator ++(int)
	{
		bigint temp;
		temp.data = this->data;
		*this += bigint(1);
		return temp;
	}

	 // Comparison operators - all const because they don't modify object
	bool bigint::operator < (const bigint &other) const
	{
		std::string num1 = this->data;
		std::string num2 = other.data;
		while(num1.length() < num2.length())
			num1 = "0" + num1;
		while(num2.length() < num1.length())
			num2 = "0" + num2;
		return (num1 < num2);
	}

	bool bigint::operator > (const bigint &other) const
	{
		std::string num1 = this->data;
		std::string num2 = other.data;
		while(num1.length() < num2.length())
			num1 = "0" + num1;
		while(num2.length() < num1.length())
			num2 = "0" + num2;
		return (num1 > num2);
	}

	bool bigint::operator == (const bigint &other) const
	{
		std::string num1 = this->data;
		std::string num2 = other.data;
		while(num1.length() < num2.length())
			num1 = "0" + num1;
		while(num2.length() < num1.length())
			num2 = "0" + num2;
		return (num1 == num2);
	}

	bool bigint::operator != (const bigint &other) const
	{
		return !(*this == other);
	}

	bool bigint::operator <= (const bigint &other) const
	{
		return (*this < other) || (*this == other);
	}

	bool bigint::operator >= (const bigint &other) const
	{
		return (*this > other) || (*this == other);
	}

	// Bit shift operators
	// x << n: Returns new shifted number
    bigint bigint:: operator<<(unsigned int shift) const
	{
		bigint result;
		result.data = this->data;
		for(int i = shift; i > 0; i--)
			result.data += "0";
		return result;
	}
	// x <<= n: Modifies and returns *this
	bigint& bigint:: operator<<=(unsigned int shift)
	{
		*this = (*this << shift);
		return *this;
	}

	bigint bigint::operator>>(unsigned int shift) const
	{
		bigint result;
		result.data = this->data;
		if(shift >= result.data.length())
		{
			result.data = "0";
			return result;
		}

		result.data = result.data.substr(0, result.data.length() - shift);

		if(result.data.empty() || result.data == "")
			result.data = "0";

		return result;
	}
	bigint& bigint:: operator>>=(unsigned int shift)
	{
		*this = (*this >> shift);
		return *this;
	}

	bigint bigint:: operator<<(const bigint shift) const    // x << n: Returns new shifted number
	{
		bigint result;
		result.data = this->data;
		unsigned long long tmp;

		std::stringstream conv(shift.data);
		conv >> tmp;
		result <<= tmp;
		return result;
	}
    bigint& bigint:: operator<<=(const bigint shift)       // x <<= n: Modifies and returns *this
	{
		*this = (*this << shift);
		return *this;
	}


    bigint bigint:: operator>>(const bigint shift) const    // x >> n: Returns new shifted number
	{
		bigint result;
		result.data = this->data;
		unsigned long long tmp;

		std::stringstream conv(shift.data);
		conv >> tmp;
		result >>= tmp;
		return result;
	}

    bigint& bigint:: operator>>=(const bigint shift)
	{
		*this = (*this >> shift);
		return *this;
	}


    // Subtraction (mentioned in main.cpp)
    bigint bigint:: operator-(const bigint& rhs) const
	{
		bigint result;
		return result;
	}  
	// Returns new object


	std::ostream& operator << (std::ostream& os, const bigint& fp)
	{
		os << fp.data;
		return os;
	}