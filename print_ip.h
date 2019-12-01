#pragma once

#include "share.h"

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <list>
#include <typeinfo>

using std::string;

template<typename Iter>
string print_ip_iterating(Iter&& it, Iter&& it_end) {
	std::stringstream res;
	if (it != it_end) {
		res << (unsigned)(unsigned char)*it++;
		for (; it != it_end; ++it) {
			res << "." << (unsigned)(unsigned char)*it;
		}
	}
	return res.str();
}

template<typename Container>
string print_ip_from_container(const Container& collect, bool b_reverse = false) {
	using Iter = decltype(collect.rbegin());
	using IterRev = decltype(collect.begin());
	if (b_reverse) {
		return print_ip_iterating<Iter>(collect.rbegin(), collect.rend());
	} else return print_ip_iterating<IterRev>(collect.begin(), collect.end());
}

template<typename T>
string print_ip_from_numeric(const T& ip) {
	using Bytes = std::array<unsigned char, sizeof(ip)>;
	union {
		Bytes bytes;
		T from;
	} res;

	res.from = ip;
	return print_ip_from_container(res.bytes, true);
}

template <class _Ty>
constexpr bool is_integral_v = std::is_integral<_Ty>::value;


template <class _Ty1, class _Ty2>
constexpr bool is_same_v = std::is_same<_Ty1, _Ty2>::value;

template<typename T>
string print_ip(const T& ip) {
	if constexpr (is_integral_v<T>) {
		return print_ip_from_numeric(ip);
	}
	else if constexpr (is_same_v<T, string>) {
		return ip;
	}
	/*std::is_integral_v*/
	else if (is_integral_v<typename T::value_type>) {
		using elem_type = typename T::value_type;
		using vec_elems = std::vector<elem_type>;
		using list_elems = std::list<elem_type>;
		if (is_same_v<T, vec_elems> || is_same_v<T, list_elems>) {
			return print_ip_from_container(ip);
		}
	}
}

