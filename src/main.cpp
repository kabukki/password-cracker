#include <iostream>
#include <string>
#include "AttackBruteforce.hpp"
#include "AttackDictionary.hpp"
#include "Cracker.hpp"
#include "Logger.hpp"
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
		Logger logger(std::cout);
		std::string str(argv[1]);

		if (str.length() != MD5_DIGEST_LENGTH * 2) {
			logger.error("MD5 digest is invalid.");
			return EXIT_FAILURE;
		} else {
			Cracker cracker;
			Hash::md5digest digest;

			Hash::translate(str, digest);

			// cracker.addAttack(std::make_shared<AttackDictionary>("dictionaries/mots-8-et-moins.txt"));
			// cracker.addAttack(std::make_shared<AttackDictionary>("dictionaries/rockyou.txt"));
			// cracker.addAttack(std::make_shared<AttackDictionary>("dictionaries/nul.txt"));

			cracker.addAttack(std::make_shared<AttackBruteforce>("abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", 6));
			// cracker.addAttack(std::make_shared<AttackBruteforce>("abcd", 3));

			return cracker.crack(digest) ? EXIT_SUCCESS : EXIT_FAILURE;
		}
	}
}
