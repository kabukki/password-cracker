#include <iostream>
#include <string>
#include "Cracker.hpp"
#include "Hash.hpp"

void usage(const std::string &binary)
{
	std::cerr << "Usage: " << binary << " <digest>" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	} else {
		std::string digest(argv[1]);
		Cracker cracker;

		cracker.crack(digest);

		// Hash::md5digest digest;
		// Hash::md5(std::string("coucou"), digest);
		// std::cout << digest << std::endl;
		return EXIT_SUCCESS;
	}
}
