#include <iostream>
#include <iomanip>
#include <cstring>
#include "DigestMD5.hpp"

DigestMD5::DigestMD5(const std::string &digest) : ADigest(MD5_DIGEST_LENGTH)
{
	// Parse every 2 characters
	for (size_t n = 0; n + 1 < digest.length(); n += 2) {
		_digest[n / 2] = static_cast<unsigned char>(std::stoi(digest.substr(n, 2), nullptr, 16));
	}
}
DigestMD5::DigestMD5(const unsigned char* digest) : ADigest(MD5_DIGEST_LENGTH)
{
	memcpy(_digest, digest, MD5_DIGEST_LENGTH);
}
DigestMD5::DigestMD5(const DigestMD5& other) : ADigest(MD5_DIGEST_LENGTH)
{
	memcpy(_digest, other._digest, MD5_DIGEST_LENGTH);
}
DigestMD5::~DigestMD5() {}

/**
 * Hash a plain string to a digest
 */
DigestMD5					DigestMD5::hash(const std::string &message)
{
	unsigned char		digest[MD5_DIGEST_LENGTH];

	MD5((const unsigned char *)message.c_str(), message.length(), digest);

	return DigestMD5(digest);
}

/**
 * Compare a plain string against a digest. First hashes the string, then compares the digests.
 */
bool					DigestMD5::check(const std::string& password) const
{
	// return true;
	return ADigest::check(DigestMD5::hash(password));
}
