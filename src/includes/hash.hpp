

#ifndef HASH_HPP
#define HASH_HPP

#include <string>

typedef std::uint64_t hash_t;
typedef unsigned long long ull;

//0x100000001B3ull
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

constexpr hash_t myhash(char const* str, hash_t last_value = basis)  {
	return *str ? myhash(str + 1, (*str ^ last_value) * prime) : last_value;
}

constexpr ull operator "" _hash(char const* p, size_t) {
	return myhash(p);
}

#endif