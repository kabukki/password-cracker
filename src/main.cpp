#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
#include "AttackBruteforce.hpp"
#include "AttackDictionary.hpp"
#include "Cracker.hpp"
#include "Logger.hpp"
#include "HashMD5.hpp"

/**
 * Getopt: https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html#Using-Getopt
 */

void usage(const std::string &binary)
{
	std::cerr << "Usage: " << binary << " [-d dictionary] [digest...]" << std::endl;
	std::cerr << "	-d	use the given dictionary as a wordlist to test against" << std::endl;
}

int							main(int argc, char **argv)
{
	Logger					logger(std::cout, "main");
	std::vector<HashMD5>	digests;
	Cracker 				cracker;
	int						c;

	// Parse arguments to add appropriate attacks
	while ((c = getopt(argc, argv, "hd:")) != -1) {
		switch (c) {
			case 'h':
				usage(argv[0]);
				return EXIT_FAILURE;
			case 'd':
				// cracker.addAttack(std::make_shared<AttackDictionary>("dictionaries/mots-8-et-moins.txt"));
				cracker.addAttack(std::make_shared<AttackDictionary>(optarg));
				break;
			default:
				return EXIT_FAILURE;
		}
	}

	// Add all hashes
	for (int n = optind; n < argc; ++n) {
		std::string strDigest(argv[n]);

		if (strDigest.length() != MD5_DIGEST_LENGTH * 2) {
			logger.error("MD5 digest is invalid.");
			return EXIT_FAILURE;
		}

		digests.push_back(HashMD5(strDigest));
	}

	// Default attacks
	cracker.addAttack(std::make_shared<AttackBruteforce>("abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", 8));

	return cracker.crack(digests) ? EXIT_SUCCESS : EXIT_FAILURE;
}
