#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>


class vect2
{
private:
	int x; 
	int y;
public:
	vect2(); 
	vect2(int a, int b);  // Creates vector (0,0)
	vect2(const vect2 &src);

	vect2& operator=(const vect2& rhs);
	// Adds two vectors
	vect2 operator+(const vect2& rhs) const; 

	vect2& operator+=(const vect2& rhs);
	vect2 operator-(const vect2& rhs) const;
	vect2 operator-()const;
	vect2& operator-=(const vect2& rhs);

	vect2 operator*(int multiplier) const;
	friend vect2 operator*(int multiplier, const vect2& rhs);
	vect2& operator*=(int multiplier);
	vect2& operator++(void);
	vect2 operator++(int);
	vect2& operator--(void);
	vect2 operator--(int);

	int& operator[](int index);
	const int& operator[](int index)const;
	bool operator == (const vect2& other) const;
	bool operator != (const vect2& other) const;
	friend std::ostream& operator <<(std::ostream &os, const vect2 &fp);
};

#endif
