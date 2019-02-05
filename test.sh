#!/bin/bash

#
# Check that the program finds the given password
#

if [[ $# -eq 1 ]]; then
	./crack $(echo -n "$1" | md5sum | cut -d ' ' -f 1)
else
	echo "Usage: $0 <password>"
fi
