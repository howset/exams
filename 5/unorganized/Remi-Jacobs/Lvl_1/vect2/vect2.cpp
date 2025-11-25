#include "vect2.hpp"

	vect2:: vect2() : x(0), y(0)
	{
		
	} 
	vect2::vect2(int a, int b): x(a), y(b)
	{

	}
	vect2::vect2(const vect2 &src) :x(src.x), y(src.y)
	{

	}

	vect2& vect2:: operator=(const vect2& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	// Adds two vectors
	vect2 vect2:: operator+(const vect2& rhs) const
	{
		vect2 result;
		result = *this;
		result.x = result.x + rhs.x;
		result.y = result.y + rhs.y;
		return result;
	} 

	vect2& vect2:: operator+=(const vect2& rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	vect2 vect2:: operator-(const vect2& rhs) const
	{
		vect2 result;
		result = *this;
		result.x = result.x - rhs.x;
		result.y = result.y - rhs.y;
		return result;
	}
	vect2 vect2::operator-()const
	{
		vect2 result;
		result = *this;
		result.x = -result.x;
		result.y = -result.y;
		return result;
	}
	vect2& vect2:: operator-=(const vect2& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	vect2 vect2:: operator*(int multiplier) const
	{
		vect2 result;
		result = *this;
		result.x = result.x * multiplier;
		result.y = result.y * multiplier;
		return result;
	}
	vect2 operator*(int multiplier, const vect2& rhs)
	{
		vect2 result;
		result.x = multiplier * rhs.x;
		result.y = multiplier * rhs.y;
		return result;
	}
	vect2& vect2:: operator*=(int multiplier)
	{
		*this = *this * multiplier;
		return *this;
	}
	vect2& vect2:: operator++(void)
	{
		*this+=vect2(1,1);
		return *this; 
	}
	vect2 vect2:: operator++(int)
	{
		vect2 result = *this;
		*this+=vect2(1,1);
		return result;
	}
	vect2& vect2:: operator--(void)
	{
		*this-=vect2(1,1);
		return *this;
	}
	vect2 vect2:: operator--(int)
	{
		vect2 result(*this);
		*this-=(vect2(1,1));
		return result;
	}

	int& vect2:: operator[](int index)
	{
		if (index == 0)
			return this->x;
		return this->y;
	}
	const int& vect2:: operator[](int index)const
	{
		if (index == 0)
			return this->x;
		return this->y;
	}
	bool vect2:: operator == (const vect2& other) const
	{
		return (this->x == other.x && this->y == other.y);
	}

	bool vect2:: operator != (const vect2& other) const
	{
		return !(this->x == other.x && this->y == other.y);
	}

	std::ostream& operator <<(std::ostream &os, const vect2 &fp)
	{
		os << '{' << fp.x << ", " << fp.y << '}';
		return os;
	}