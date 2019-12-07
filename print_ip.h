#pragma once

#include "share.h"

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <list>
#include <tuple>
#include <sstream>

using std::string;

//// Templates utils

template <class _Ty>
constexpr bool is_integral_v = std::is_integral<_Ty>::value;

template <class _Ty1, class _Ty2>
constexpr bool is_same_v = std::is_same<_Ty1, _Ty2>::value;

template < template <typename...> class Template, typename T >
struct is_specialization_of : std::false_type {};

template < template <typename...> class Template, typename... Args >
struct is_specialization_of< Template, Template<Args...> > : std::true_type {};

template <class T>
constexpr bool is_tuple_v = is_specialization_of<std::tuple, T>::value;

template <class T>
constexpr bool is_vector_v = is_specialization_of<std::vector, T>::value;

template <class T>
constexpr bool is_list_v = is_specialization_of<std::list, T>::value;
//// Templates utils

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

template<typename ForCheck, int cur_idx, typename ...Args>
void print_ip_from_tuple_internal(const std::tuple<Args...>& ip, std::stringstream& out) {
	if constexpr (cur_idx == sizeof...(Args)) {
		return;
	}
	else {
		using CurType = decltype(std::get<cur_idx>(ip));
		using PureCurType = typename std::remove_const<typename std::remove_reference<CurType>::type>::type;
		static_assert(is_same_v<ForCheck, PureCurType>, "Bad Type: all types in tuple must be same");
		out << std::get<cur_idx>(ip);
		if constexpr (cur_idx + 1 < sizeof...(Args)) {
			out << ".";
		}
		print_ip_from_tuple_internal<ForCheck, cur_idx + 1, Args...>(ip, out);
	}
}

template<typename Arg, typename ...Args>
string print_ip_from_tuple(const std::tuple<Arg, Args...>& ip) {
	std::stringstream sout;
	print_ip_from_tuple_internal<Arg, 0, Arg, Args...>(ip, sout);
	return sout.str();
}

template<typename T>
string print_ip(const T& ip) {
	if constexpr (is_integral_v<T>) {
		return print_ip_from_numeric(ip);
	}
	else if constexpr (is_same_v<T, string>) {
		return ip;
	}
	else if constexpr (is_tuple_v<T>) {
		return print_ip_from_tuple(ip);
	}
	else if constexpr (is_list_v<T> || is_vector_v<T>) {
		if constexpr (is_integral_v<typename T::value_type>) {
			return print_ip_from_container(ip);
		}
	}
	return "";
}
