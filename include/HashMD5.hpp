#ifndef HASH_MD5_HPP
#define HASH_MD5_HPP

#include <openssl/md5.h>
#include "IHash.hpp"

class HashMD5 : public IHash
{
private:
	unsigned char* 			_digest;

public:
	HashMD5(const std::string& digest);
	HashMD5(const unsigned char* digest);
	~HashMD5();

	static HashMD5			hash(const std::string &message);
	bool 					check(const std::string &password) const;
	
	const unsigned char*	raw() const;
	const unsigned char&	operator[](const size_t n) const;
};

inline bool					operator==(const HashMD5& lhs, const HashMD5& rhs);
std::ostream&				operator<<(std::ostream &os, const HashMD5& digest);

#endif
