#ifndef IDIGEST_HPP
#define IDIGEST_HPP

#include <openssl/md5.h>
#include <string>

class IDigest
{
public:
	bool		check(const std::string &password) const;
};

std::ostream&	operator<<(std::ostream &os, const IDigest &digest);

#endif
