#ifndef IHASH_HPP
#define IHASH_HPP

#include <openssl/md5.h>
#include <string>

class IHash
{
public:
	bool		check(const std::string &password) const;
};

std::ostream&	operator<<(std::ostream &os, const IHash &digest);

#endif
