#pragma once
#include <iostream>

class vect2
{
    private:
        int data[2];
    
    public:
        vect2(int x = 0, int y = 0);
        vect2(const vect2& other);

        vect2& operator=(const vect2& other);

        int& operator[](int index);
        const int& operator[](int index) const;

        vect2 operator+(const vect2& other) const;
        vect2 operator-(const vect2& other) const;
        vect2 operator*(int carry) const;
        vect2 operator+();
        vect2 operator-();

        vect2& operator+=(const vect2& other);
        vect2& operator-=(const vect2& other);
        vect2& operator*=(int carry);

        vect2 operator++(int);
        vect2& operator++();
        vect2 operator--(int);
        vect2& operator--();

        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;
};

std::ostream& operator<<(std::ostream& out, const vect2& v);
vect2 operator*(int carry, const vect2& v);