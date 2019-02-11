#ifndef HASH_MD5_HPP
#define HASH_MD5_HPP

#include <openssl/md5.h>
#include "IDigest.hpp"

class DigestMD5 : public IDigest
{
private:
	unsigned char* 			_digest;

public:
	DigestMD5(const std::string& digest);
	DigestMD5(const unsigned char* digest);
	DigestMD5(const DigestMD5& other);
	~DigestMD5();

	static DigestMD5		hash(const std::string &message);
	bool 					check(const std::string &password) const;
	
	const unsigned char*	raw() const;
	const unsigned char&	operator[](const size_t n) const;
};

inline bool					operator==(const DigestMD5& lhs, const DigestMD5& rhs);
std::ostream&				operator<<(std::ostream &os, const DigestMD5& digest);

#endif
