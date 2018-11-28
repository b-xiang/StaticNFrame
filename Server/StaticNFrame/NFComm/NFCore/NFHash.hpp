// -------------------------------------------------------------------------
//    @FileName         :    NFHash.hpp
//    @Author           :    GaoYi
//    @Date             :    2018-05-14
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

/**
 *@brief  ������hash_combine������Ҫժ�Կ�Դ��folly����֤�ȶ��ɿ�
 */
namespace NFHash
{
	//����TARS��hash�㷨
	/////////////////////////////////////////////////
	/**
	* @file NFHash.h
	* @brief hash�㷨.
	*���Զ�������ֽ�������hash�õ��൱���ȵ�hashֵ
	*
	*
	*/
	/////////////////////////////////////////////////

	template <class _Key> struct hash { };
	template <class _Key> struct hash_new { };

	inline size_t hash_string(const char* s)
	{
		unsigned long h = 0;
		for (; *s; ++s)
			h = 5 * h + *s;

		return size_t(h);
	}

	//////////////////////////////////////////////////////////
	/**
	* @brief ��������hash_new, ������һЩ.
	*
	*���Զ�������ֽ�������hash�õ��൱���ȵ�hashֵ
	*/
	//////////////////////////////////////////////////////////
	template <>
	struct hash<std::string>
	{
		size_t operator()(const std::string &s) const
		{
			size_t h = 0, g;
			const char *arKey = s.c_str();
			size_t nKeyLength = s.length();
			const char *arEnd = arKey + nKeyLength;
			while (arKey < arEnd)
			{
				h = (h << 4) + *arKey++;
				if ((g = (h & 0xF0000000)))
				{
					h = h ^ (g >> 24);
					h = h ^ g;
				}
			}
			return h;
		}
	};

	template <>
	struct hash_new<std::string>
	{
		size_t operator()(const std::string &s) const
		{
			const char *ptr = s.c_str();
			size_t key_length = s.length();
			uint32_t value = 0;

			while (key_length--)
			{
				value += *ptr++;
				value += (value << 10);
				value ^= (value >> 6);
			}
			value += (value << 3);
			value ^= (value >> 11);
			value += (value << 15);

			return value == 0 ? 1 : value;
		}
	};

	template <>
	struct hash<char*>
	{
		size_t operator()(const char* s) const { return hash_string(s); }
	};

	template <>
	struct hash<const char*>
	{
		size_t operator()(const char* s) const { return hash_string(s); }
	};

	template <>
	struct hash<char>
	{
		size_t operator()(char x) const { return x; }
	};

	template <>
	struct hash<unsigned char>
	{
		size_t operator()(unsigned char x) const { return x; }
	};

	template <>
	struct hash<signed char>
	{
		size_t operator()(unsigned char x) const { return x; }
	};

	template <>
	struct hash<short>
	{
		size_t operator()(short x) const { return x; }
	};

	template <>
	struct hash<unsigned short>
	{
		size_t operator()(unsigned short x) const { return x; }
	};

	template <>
	struct hash<int>
	{
		size_t operator()(int x) const { return x; }
	};

	template <>
	struct hash<unsigned int>
	{
		size_t operator()(unsigned int x) const { return x; }
	};

	template <>
	struct hash<long>
	{
		size_t operator()(long x) const { return x; }
	};

	template <>
	struct hash<unsigned long>
	{
		size_t operator()(unsigned long x) const { return x; }
	};

	/**
	* @brief һ�������hash�㷨.
	*
	*���Զ�������ֽ�������hash�õ��൱���ȵ�hashֵ
	*/
	struct magic_string_hash
	{
		size_t operator()(const std::string &s) const
		{
			const char *ptr = s.c_str();
			size_t key_length = s.length();
			uint32_t value = 0;

			while (key_length--)
			{
				value += *ptr++;
				value += (value << 10);
				value ^= (value >> 6);
			}
			value += (value << 3);
			value ^= (value >> 11);
			value += (value << 15);

			return value == 0 ? 1 : value;
		}
	};

	//////////////////////////////////////////////////////////////////////////


	// This is a general-purpose way to create a single hash from multiple
	// hashable objects. hash_combine_generic takes a class Hasher implementing
	// hash<T>; hash_combine uses a default hasher StdHasher that uses std::hash.
	// hash_combine_generic hashes each argument and combines those hashes in
	// an order-dependent way to yield a new hash.

	// This is the Hash128to64 function from Google's cityhash (available
	// under the MIT License).  We use it to reduce multiple 64 bit hashes
	// into a single hash.
	inline uint64_t hash_128_to_64(
		const uint64_t upper,
		const uint64_t lower) noexcept
	{
		// Murmur-inspired hashing.
		const uint64_t kMul = 0x9ddfea08eb382d69ULL;
		uint64_t a = (lower ^ upper) * kMul;
		a ^= (a >> 47);
		uint64_t b = (upper ^ a) * kMul;
		b ^= (b >> 47);
		b *= kMul;
		return b;
	}

	// Never used, but gcc demands it.
	template <class Hasher>
	inline size_t hash_combine_generic()
	{
		return 0;
	}

	template <
		class Iter,
		class Hash = std::hash<typename std::iterator_traits<Iter>::value_type>>
	uint64_t
	hash_range(Iter begin, Iter end, uint64_t hash = 0, Hash hasher = Hash())
	{
		for (; begin != end; ++begin)
		{
			hash = hash_128_to_64(hash, hasher(*begin));
		}
		return hash;
	}

	inline uint32_t twang_32from64(uint64_t key) noexcept;

	template <class Hasher, typename T, typename... Ts>
	size_t hash_combine_generic(const T& t, const Ts&... ts)
	{
		size_t seed = Hasher::hash(t);
		if (sizeof...(ts) == 0)
		{
			return seed;
		}
		size_t remainder = hash_combine_generic<Hasher>(ts...);
		/* static */
		if (sizeof(size_t) == sizeof(uint32_t))
		{
			return twang_32from64((uint64_t(seed) << 32) | remainder);
		}
		else
		{
			return static_cast<size_t>(hash_128_to_64(seed, remainder));
		}
	}

	// Simply uses std::hash to hash.  Note that std::hash is not guaranteed
	// to be a very good hash function; provided std::hash doesn't collide on
	// the individual inputs, you are fine, but that won't be true for, say,
	// strings or pairs
	class StdHasher
	{
	public:
		// The standard requires all explicit and partial specializations of std::hash
		// supplied by either the standard library or by users to be default
		// constructible.
		template <typename T>
		static size_t hash(const T& t) noexcept(noexcept(std::hash<T>()(t)))
		{
			return std::hash<T>()(t);
		}
	};

	template <typename T, typename... Ts>
	size_t hash_combine(const T& t, const Ts&... ts)
	{
		return hash_combine_generic<StdHasher>(t, ts...);
	}

	//////////////////////////////////////////////////////////////////////

	/*
	* Thomas Wang 64 bit mix hash function
	*/

	inline uint64_t twang_mix64(uint64_t key) noexcept
	{
		key = (~key) + (key << 21); // key *= (1 << 21) - 1; key -= 1;
		key = key ^ (key >> 24);
		key = key + (key << 3) + (key << 8); // key *= 1 + (1 << 3) + (1 << 8)
		key = key ^ (key >> 14);
		key = key + (key << 2) + (key << 4); // key *= 1 + (1 << 2) + (1 << 4)
		key = key ^ (key >> 28);
		key = key + (key << 31); // key *= 1 + (1 << 31)
		return key;
	}

	/*
	* Inverse of twang_mix64
	*
	* Note that twang_unmix64 is significantly slower than twang_mix64.
	*/

	inline uint64_t twang_unmix64(uint64_t key) noexcept
	{
		// See the comments in jenkins_rev_unmix32 for an explanation as to how this
		// was generated
		key *= 4611686016279904257U;
		key ^= (key >> 28) ^ (key >> 56);
		key *= 14933078535860113213U;
		key ^= (key >> 14) ^ (key >> 28) ^ (key >> 42) ^ (key >> 56);
		key *= 15244667743933553977U;
		key ^= (key >> 24) ^ (key >> 48);
		key = (key + 1) * 9223367638806167551U;
		return key;
	}

	/*
	* Thomas Wang downscaling hash function
	*/

	inline uint32_t twang_32from64(uint64_t key) noexcept
	{
		key = (~key) + (key << 18);
		key = key ^ (key >> 31);
		key = key * 21;
		key = key ^ (key >> 11);
		key = key + (key << 6);
		key = key ^ (key >> 22);
		return static_cast<uint32_t>(key);
	}

	/*
	* Robert Jenkins' reversible 32 bit mix hash function
	*/

	inline uint32_t jenkins_rev_mix32(uint32_t key) noexcept
	{
		key += (key << 12); // key *= (1 + (1 << 12))
		key ^= (key >> 22);
		key += (key << 4); // key *= (1 + (1 << 4))
		key ^= (key >> 9);
		key += (key << 10); // key *= (1 + (1 << 10))
		key ^= (key >> 2);
		// key *= (1 + (1 << 7)) * (1 + (1 << 12))
		key += (key << 7);
		key += (key << 12);
		return key;
	}

	/*
	* Inverse of jenkins_rev_mix32
	*
	* Note that jenkinks_rev_unmix32 is significantly slower than
	* jenkins_rev_mix32.
	*/

	inline uint32_t jenkins_rev_unmix32(uint32_t key) noexcept
	{
		// These are the modular multiplicative inverses (in Z_2^32) of the
		// multiplication factors in jenkins_rev_mix32, in reverse order.  They were
		// computed using the Extended Euclidean algorithm, see
		// http://en.wikipedia.org/wiki/Modular_multiplicative_inverse
		key *= 2364026753U;

		// The inverse of a ^= (a >> n) is
		// b = a
		// for (int i = n; i < 32; i += n) {
		//   b ^= (a >> i);
		// }
		key ^= (key >> 2) ^ (key >> 4) ^ (key >> 6) ^ (key >> 8) ^ (key >> 10) ^
			(key >> 12) ^ (key >> 14) ^ (key >> 16) ^ (key >> 18) ^ (key >> 20) ^
			(key >> 22) ^ (key >> 24) ^ (key >> 26) ^ (key >> 28) ^ (key >> 30);
		key *= 3222273025U;
		key ^= (key >> 9) ^ (key >> 18) ^ (key >> 27);
		key *= 4042322161U;
		key ^= (key >> 22);
		key *= 16773121U;
		return key;
	}

	/*
	* Fowler / Noll / Vo (FNV) Hash
	*     http://www.isthe.com/chongo/tech/comp/fnv/
	*/

	const uint32_t FNV_32_HASH_START = 2166136261UL;
	const uint64_t FNV_64_HASH_START = 14695981039346656037ULL;
	const uint64_t FNVA_64_HASH_START = 14695981039346656037ULL;

	inline uint32_t fnv32(
		const char* buf,
		uint32_t hash = FNV_32_HASH_START) noexcept
	{
		// forcing signed char, since other platforms can use unsigned
		const signed char* s = reinterpret_cast<const signed char*>(buf);

		for (; *s; ++s)
		{
			hash +=
				(hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
			hash ^= *s;
		}
		return hash;
	}

	inline uint32_t fnv32_buf(
		const void* buf,
		size_t n,
		uint32_t hash = FNV_32_HASH_START) noexcept
	{
		// forcing signed char, since other platforms can use unsigned
		const signed char* char_buf = reinterpret_cast<const signed char*>(buf);

		for (size_t i = 0; i < n; ++i)
		{
			hash +=
				(hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
			hash ^= char_buf[i];
		}

		return hash;
	}

	inline uint32_t fnv32(
		const std::string& str,
		uint32_t hash = FNV_32_HASH_START) noexcept
	{
		return fnv32_buf(str.data(), str.size(), hash);
	}

	inline uint64_t fnv64(
		const char* buf,
		uint64_t hash = FNV_64_HASH_START) noexcept
	{
		// forcing signed char, since other platforms can use unsigned
		const signed char* s = reinterpret_cast<const signed char*>(buf);

		for (; *s; ++s)
		{
			hash += (hash << 1) + (hash << 4) + (hash << 5) + (hash << 7) +
				(hash << 8) + (hash << 40);
			hash ^= *s;
		}
		return hash;
	}

	inline uint64_t fnv64_buf(
		const void* buf,
		size_t n,
		uint64_t hash = FNV_64_HASH_START) noexcept
	{
		// forcing signed char, since other platforms can use unsigned
		const signed char* char_buf = reinterpret_cast<const signed char*>(buf);

		for (size_t i = 0; i < n; ++i)
		{
			hash += (hash << 1) + (hash << 4) + (hash << 5) + (hash << 7) +
				(hash << 8) + (hash << 40);
			hash ^= char_buf[i];
		}
		return hash;
	}

	inline uint64_t fnv64(
		const std::string& str,
		uint64_t hash = FNV_64_HASH_START) noexcept
	{
		return fnv64_buf(str.data(), str.size(), hash);
	}

	inline uint64_t fnva64_buf(
		const void* buf,
		size_t n,
		uint64_t hash = FNVA_64_HASH_START) noexcept
	{
		const uint8_t* char_buf = reinterpret_cast<const uint8_t*>(buf);

		for (size_t i = 0; i < n; ++i)
		{
			hash ^= char_buf[i];
			hash += (hash << 1) + (hash << 4) + (hash << 5) + (hash << 7) +
				(hash << 8) + (hash << 40);
		}
		return hash;
	}

	inline uint64_t fnva64(
		const std::string& str,
		uint64_t hash = FNVA_64_HASH_START) noexcept
	{
		return fnva64_buf(str.data(), str.size(), hash);
	}
} //namespace NFHash


