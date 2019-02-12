#ifndef HASH_MD5_HPP
#define HASH_MD5_HPP

#include <openssl/md5.h>
#include "ADigest.hpp"

class DigestMD5 : public ADigest
{
public:
	DigestMD5(const std::string& digest);
	DigestMD5(const unsigned char* digest);
	DigestMD5(const DigestMD5& other);
	~DigestMD5();

	static DigestMD5		hash(const std::string &message);
	bool 					check(const std::string &password) const override;
};

#endif
