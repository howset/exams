#include <iostream>
#include <string>

int main()
{
	std::string str = "01";
	str += '0';
	str[2] += 1;
	// str[4] += 4;
	std::cout <<  str << std::endl;
}