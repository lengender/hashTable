#ifndef _HASHFUNC_H_
#define _HASHFUNC_H_

#include<math.h>
#include<stdint.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

/*
 * 哈希函数的设定，只考虑 4 种键值类型的哈希函数
 * char, int , double , string
 */
template<class Key> struct hashFunc{};

template<> struct hashFunc < char > {
	size_t operator()(char x) const { return x; }
};

template<> struct hashFunc < int > {
	size_t operator()(int x) const { return x; }
};

template<> struct hashFunc < double > {
	size_t operator()(const double & dValue) const
	{
		int e = 0;
		double tmp = dValue;
		if (dValue<0)
		{
			tmp = -dValue;
		}
		e = ceil(log(dValue));
		return size_t((INT64_MAX + 1.0) * tmp * exp(-e));
	}
};

template<> struct hashFunc < string > {
	size_t operator()(const string & str) const
	{
		size_t h = 0; for (size_t i = 0; i<str.length(); ++i)
		{
			h = (h << 5) - h + str[i];
		}
		return h; 
	}
};

//将表格的大小设为质数，然后直接使用除留余数法求哈希值
//按照SGI STL中的原则，首先保存28个质数(逐渐呈现大约两倍的关系)，
//同时提供一个函数，用来查询在这28个质数中，最接近某数并大于某数的质数
static const int num_primes = 28;
static const unsigned long prime_list[num_primes] =
{
	53, 97, 193, 389, 769,
	1543, 3079, 6151, 12289, 24593,
	49157, 98317, 196613, 393241, 786433,
	1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457,
	1610612741, 3221225473, 4294967291
};

//找出最接近但大于的质数
inline unsigned long next_prime(unsigned long n){
	const unsigned long *first = prime_list;
	const unsigned long *last = prime_list + num_primes;
	const unsigned long *pos = lower_bound(first, last, n);

	return pos == last ? *(last - 1) : *pos;
}

#endif