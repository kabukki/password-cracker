#!/bin/bash

#
# Check that the program finds the given password
#

HASHES=()

if [[ $# -ge 1 ]]; then
	for password in $@; do HASHES+=($(echo -n $password | md5sum | cut -d ' ' -f 1)); done
	./crack ${HASHES[@]}
else
	echo "Usage: $0 <password>"
fi
