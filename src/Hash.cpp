#include <openssl/md5.h>
#include <iostream>
#include <iomanip>
#include "Hash.hpp"

Hash::Hash () {}
Hash::~Hash () {}

void	Hash::md5(const std::string &message, Hash::md5digest &digest)
{
	MD5((const unsigned char *)message.c_str(), message.length(), digest);
}

std::ostream & operator<<(std::ostream &os, const Hash::md5digest &digest) {
	os << std::hex;
	for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
		os << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(digest[n]);
	}
	return os;
};
