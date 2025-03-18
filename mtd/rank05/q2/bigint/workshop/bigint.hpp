#pragma once

#include <iostream>
#include <algorithm>
#include <string>

bool iszero(char c) {
	if (c == 48)
		return true;
	return false;
}

class bigint {
private:
	std::string n;

public:
	bigint() : n("0") {}
	bigint(size_t num) : n(std::to_string(num)) {}
	bigint(std::string s) {
		if (s.empty() || !std::all_of(s.begin(), s.end(), ::isdigit)) {
			std::cerr << "Bad input string '" << s << "', setting n to \"0\"" << std::endl;
			n = "0";
		}
		else if (std::all_of(s.begin(), s.end(), ::iszero))
			n = "0";
		else
			n = s;
	}
	bigint(const bigint& other) : n(other.n) {}
	~bigint() {}

	std::string add_strings(const std::string& s1, const std::string& s2) const {
		size_t	idx1 = s1.size(), idx2 = s2.size(), carry = 0;
		std::string	res = "";
		while (idx1 || idx2 || carry) {
			if (idx1) { carry += s1[--idx1] - '0'; }
			if (idx2) { carry += s2[--idx2] - '0'; }
			if (carry > 9) {
				res.push_back(carry - 10 + '0');
				carry = 10;
			} 
			else {
				res.push_back(carry + '0');
				carry = 0;
			}
		}
		std::reverse(res.begin(), res.end());
		return res;
	}

	bigint& operator=(const bigint& rh) {
		if (this != &rh)
			n = rh.n;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const bigint& rh) {
		os << rh.n;
		return os;
	}

	bigint operator+(const bigint& other) const {
		return bigint(add_strings(n, other.n));
	}

	bigint operator-(const bigint& other) {
		(void)other;
		return bigint();
	}

	bigint& operator+=(const bigint& other) {
		n = add_strings(n, other.n);
		return *this;
	}

	bigint& operator++(void) {
		*this += bigint(1);
		return *this;
	}

	bigint operator++(int) {
		bigint old(*this);
		++(*this);
		return old;
	}

	bigint operator<<(const size_t& num) const {
		return bigint(n + std::string(num, '0'));  // (string)n + "0000000000"
	}

	bigint& operator<<=(const size_t& num) {
		n += std::string(num, '0');
		return *this;
	}

	bigint& operator>>=(const bigint& other) {
		if (n.size() <= other.n.size())
			n = "0";
		else {
			bigint i("0");
			while (i < other) {
				n = n.substr(0, n.size() - 1);
				++i;
			}
		}
		return *this;
	}

	bool operator<(const bigint& other) const {
		return n < other.n;
	}

	bool operator>(const bigint& other) const {
		return other < *this;
	}

	bool operator<=(const bigint& other) const {
		return !(*this > other);
	}

	bool operator>=(const bigint& other) const {
		return !(*this < other);
	}

	bool operator==(const bigint& other) const {
		return n == other.n;
	}

	bool operator!=(const bigint& other) const {
		return n != other.n;
	}
};