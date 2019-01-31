#ifndef HASH_HPP
#define HASH_HPP

#include <openssl/md5.h>
#include <string>

class Hash
{
public:
	typedef unsigned char md5digest[MD5_DIGEST_LENGTH];

	Hash();
	~Hash();

	static void	md5(const std::string &message, Hash::md5digest &digest);
};

std::ostream & operator<<(std::ostream &os, const Hash::md5digest &digest);

#endif
