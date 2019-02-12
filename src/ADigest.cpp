#include <iostream>
#include <iomanip>
#include <cstring>
#include "ADigest.hpp"

ADigest::ADigest(const size_t length) : _length(length)
{
	_digest = new unsigned char[length];
}
ADigest::~ADigest()
{
	delete[] _digest;
}

/**
 * Compare a digest against another
 */
bool					ADigest::check(const ADigest& digest) const
{
	return std::memcmp(_digest, digest.raw(), _length) == 0;;
}

size_t					ADigest::length() const
{
	return _length;
}

const unsigned char*	ADigest::raw() const
{
	return _digest;
}

const unsigned char&	ADigest::operator[](const size_t n) const
{
	return _digest[n];
}

std::ostream&	operator<<(std::ostream &os, const ADigest &digest)
{
	os << std::hex;
	for (size_t n = 0; n < digest.length(); n++) {
		os << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(digest[n]);
	}
	os << std::dec;
	return os;
}

bool			operator==(const ADigest& lhs, const ADigest& rhs)
{
	return lhs.check(rhs);
}
