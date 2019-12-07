#include "share.h"

#define BOOST_TEST_MODULE allocator_test_module

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <functional>
#include <ctime>
#include <tuple>

#include "print_ip.h"

using std::string;
using std::cout;
using std::clock;
using std::endl;

bool call_test(string name, std::function<bool(void)> fntest) {
	cout << endl << name << ":\n";

	auto startTime = clock();
	bool res = fntest();
	auto endTime = clock();

	cout << "TIME: " << endTime - startTime << "ms" << endl;
	return res;
}

bool test_print_ip__with_char() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("255") == print_ip(char(-1));
	});
}

bool test_print_ip__with_short() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("0.0") == print_ip(short(0));
		});
}

bool test_print_ip__with_int() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("127.0.0.1") == print_ip(int(2130706433));
		});
}

bool test_print_ip__with_long_long() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("123.45.67.89.101.112.131.41") == print_ip(8875824491850138409LL);
		});
}

bool test_print_ip__with_string() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("123.45.67.89") == print_ip(string("123.45.67.89"));
		});
}

bool test_print_ip__with_vector() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("123.45.67.89.101.112.131.41") == print_ip(std::vector<unsigned char>{123, 45, 67, 89, 101, 112, 131, 41});
		});
}

bool test_print_ip__with_list() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("101.112.131.41") == print_ip(std::list<int>{ 101, 112, 131, 41 });
	});
}

bool test_print_ip__with_tuple() {
	return call_test(__PRETTY_FUNCTION__, []() {
		return std::string("1.2.3.4") == print_ip(std::tuple<int, int, int, int>{ 1, 2, 3, 4 });
		});
}

//struct Init {
//	Init(std::function<void()> init_func) {
//		init_func();
//	}
//};
//#define INIT(init_func) struct Init init(init_func);


BOOST_AUTO_TEST_SUITE(allocator_test_suite)
//INIT(init_base_fixtures)

BOOST_AUTO_TEST_CASE(test_of_print_ip)
{
	BOOST_CHECK(test_print_ip__with_char());
	BOOST_CHECK(test_print_ip__with_short());
	BOOST_CHECK(test_print_ip__with_int());
	BOOST_CHECK(test_print_ip__with_long_long());
	BOOST_CHECK(test_print_ip__with_string());
	BOOST_CHECK(test_print_ip__with_vector());
	BOOST_CHECK(test_print_ip__with_list());
	BOOST_CHECK(test_print_ip__with_tuple());
}

BOOST_AUTO_TEST_SUITE_END()
