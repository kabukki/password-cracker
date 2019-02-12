#ifndef ADIGEST_HPP
#define ADIGEST_HPP

#include <string>

class ADigest
{
protected:
	unsigned char* 			_digest;
	const size_t			_length;

public:
	ADigest(const size_t length);
	~ADigest();

	virtual bool			check(const std::string &password) const = 0;
	bool					check(const ADigest& digest) const;

	size_t					length() const;
	const unsigned char*	raw() const;
	const unsigned char&	operator[](const size_t n) const;
};

std::ostream&				operator<<(std::ostream &os, const ADigest &digest);
bool						operator==(const ADigest& lhs, const ADigest& rhs);

#endif
