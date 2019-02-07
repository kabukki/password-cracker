#ifndef IGENERATOR_HPP
#define IGENERATOR_HPP

#include <string>
#include <memory>

class IGenerator
{
public:
	using value_type		= std::string;
	using reference			= std::string&;
	using pointer			= std::string*;
	using difference_type	= std::ptrdiff_t;
	using iterator_category	= std::input_iterator_tag;

	virtual explicit		operator bool() const = 0;
	virtual reference		operator*() = 0;
	virtual pointer			operator->() = 0;
	virtual IGenerator&		operator++() = 0;
	// virtual IGenerator		operator++(int n) = 0;

	virtual const std::string&	name() = 0;
	virtual const std::string	describe() = 0;
};

#endif
