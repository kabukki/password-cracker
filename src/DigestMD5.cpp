#include <iostream>
#include <iomanip>
#include <cstring>
#include "DigestMD5.hpp"

DigestMD5::DigestMD5(const std::string &digest)
{
	_digest = new unsigned char[MD5_DIGEST_LENGTH];

	// Parse every 2 characters
	for (size_t n = 0; n + 1 < digest.length(); n += 2) {
		_digest[n / 2] = static_cast<unsigned char>(std::stoi(digest.substr(n, 2), nullptr, 16));
	}
}
DigestMD5::DigestMD5(const unsigned char* digest)
{
	_digest = new unsigned char[MD5_DIGEST_LENGTH];
	memcpy(_digest, digest, MD5_DIGEST_LENGTH);
}
DigestMD5::DigestMD5(const DigestMD5& other)
{
	_digest = new unsigned char[MD5_DIGEST_LENGTH];
	memcpy(_digest, other._digest, MD5_DIGEST_LENGTH);
}
DigestMD5::~DigestMD5()
{
	delete[] _digest;
}

/**
 * Hash a plain string to a digest
 */
DigestMD5					DigestMD5::hash(const std::string &message)
{
	unsigned char		digest[MD5_DIGEST_LENGTH];

	MD5((const unsigned char *)message.c_str(), message.length(), digest);

	return DigestMD5(digest);
}

const unsigned char*	DigestMD5::raw() const
{
	return _digest;
}

/**
 * Compare a plain string against a digest. First hashes the string, then compares the digests.
 */
bool					DigestMD5::check(const std::string &password) const
{
	DigestMD5				digest = DigestMD5::hash(password);

	return digest == *this;
}

const unsigned char&	DigestMD5::operator[](const size_t n) const
{
	return _digest[n];
}

bool					operator==(const DigestMD5& lhs, const DigestMD5& rhs)
{
	return std::memcmp(lhs.raw(), rhs.raw(), MD5_DIGEST_LENGTH) == 0;
}

std::ostream&			operator<<(std::ostream &os, const DigestMD5& digest)
{
	os << std::hex;
	for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
		os << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(digest[n]);
	}
	return os << std::dec;
};
