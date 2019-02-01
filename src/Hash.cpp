#include <openssl/md5.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Hash.hpp"

Hash::Hash () {}
Hash::~Hash () {}

void	Hash::md5(const std::string &message, Hash::md5digest &digest)
{
	MD5((const unsigned char *)message.c_str(), message.length(), digest);
}

/**
 * Parse a digest string and converts it to a md5digest
 */
void	Hash::translate(const std::string &str, Hash::md5digest &digest)
{
	// Parse every 2 characters
	for (size_t n = 0; n + 1 < str.length(); n += 2) {
		digest[n / 2] = static_cast<unsigned char>(std::stoi(str.substr(n, 2), nullptr, 16));
	}
}

bool	Hash::compareDigests(const Hash::md5digest &a, const Hash::md5digest &b)
{
	for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
		if (a[n] != b[n]) {
			return false;
		}
	}
	return true;
}

std::ostream & operator<<(std::ostream &os, const Hash::md5digest &digest)
{
	os << std::hex;
	for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
		os << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(digest[n]);
	}
	return os << std::dec;
};
