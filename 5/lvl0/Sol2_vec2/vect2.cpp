#include "vect2.hpp"

vect2::vect2(int x, int y)
{
    data[0] = x;
    data[1] = y;
}

vect2::vect2(const vect2& other)
{
    data[0] = other.data[0];
    data[1] = other.data[1];
}

vect2& vect2::operator=(const vect2& other)
{
    if(this != &other)
    {
        data[0] = other.data[0];
        data[1] = other.data[1];
    }
    return *this;
}

int& vect2::operator[](int index)
{
    return data[index];
}

const int& vect2::operator[](int index) const
{
    return data[index];
}

vect2 vect2::operator+(const vect2& other) const
{
    return vect2(data[0] + other.data[0], data[1] + other.data[1]);
}

vect2 vect2::operator-(const vect2& other) const
{
    return vect2(data[0] - other.data[0], data[1] - other.data[1]);
}

vect2 vect2::operator*(int carry) const
{
    return vect2(data[0] * carry, data[1] * carry);
}

vect2 vect2::operator+()
{
    return vect2(+data[0], +data[1]);
}

vect2 vect2::operator-()
{
    return vect2(-data[0], -data[1]);
}

vect2& vect2::operator+=(const vect2& other)
{
    data[0] += other.data[0];
    data[1] += other.data[1];
    return *this;
}

vect2& vect2::operator-=(const vect2& other)
{
    data[0] -= other.data[0];
    data[1] -= other.data[1];
    return *this;
}

vect2& vect2::operator*=(int carry)
{
    data[0] *= carry;
    data[1] *= carry;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 res = *this;

    ++(data[0]);
    ++(data[1]);
    return res;
}

vect2& vect2::operator++()
{
    ++(data[0]);
    ++(data[1]);
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 res = *this;

    --(data[0]);
    --(data[1]);
    return res;
}

vect2& vect2::operator--()
{
    --(data[0]);
    --(data[1]);
    return *this;
}

bool vect2::operator==(const vect2& other) const
{
    return (data[0] == other.data[0] && data[1] == other.data[1]);
}

bool vect2::operator!=(const vect2& other) const
{
    return !(data[0] == other.data[0] && data[1] == other.data[1]);
}

std::ostream& operator<<(std::ostream& out, const vect2& v)
{
    out << "{" << v[0] << ", " << v[1] << "}";
    return out;
}

vect2 operator*(int carry, const vect2& v)
{
    return vect2(carry * v[0] , carry * v[1]);
}