#!/bin/bash

./test.sh "a"
./test.sh "b"
./test.sh "*"

./test.sh "aa"
./test.sh "bb"
./test.sh "**"

./test.sh "aaa"
./test.sh "bbb"
./test.sh "***"

./test.sh "aaaa"
./test.sh "bbbb"
./test.sh "****"

./test.sh "aaaaa"
./test.sh "bbbbb"
./test.sh "*****"
