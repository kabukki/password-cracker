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
	static void translate(const std::string &str, Hash::md5digest &digest);
	static bool	compareDigests(const Hash::md5digest &a, const Hash::md5digest &b);
};

std::ostream & operator<<(std::ostream &os, const Hash::md5digest &digest);

#endif
