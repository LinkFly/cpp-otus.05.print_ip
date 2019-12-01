#include "share.h"

#include <iostream>

#include "print_ip.h"

using std::cout;
using std::endl;

int main() {
	cout << print_ip(char(-1)) << endl;
	cout << print_ip(short(0)) << endl;
	cout << print_ip(int(2130706433)) << endl;
	cout << print_ip(8875824491850138409LL) << endl;
	cout << print_ip(string("123.45.67.89")) << endl;
	cout << print_ip(std::vector<unsigned char>{67, 89, 101, 112}) << endl;
	cout << print_ip(std::list<int>{ 101, 112, 131, 41 }) << endl;

	return 0;
}
