#!/bin/bash

make

if [ "$1" = "-s" ]
	then
		pause=1
else
	pause=0
fi

test_count=1
do_test() {
	if [ $pause -eq 1 ]
		then
			clear
	fi
	printf "\e[3;35m%-40s\e[0m\e[1;32m$2\e[0;32m\n" "${test_count}: ${1}"
	eval $2
	printf "\e[0m"
	if [ ! -z "$3" ]
		then
			printf "\e[93m%-40s" ""
			printf "$3\e[33m\n" ""
			eval $3
			printf "\e[0m"
	fi
	echo
	let "test_count++"
	if [ $pause -eq 1 ]
		then
			read -n 1
	fi
}






# do_test "no args"					"./ft_ssl"
do_test "invalid cmd"				"./ft_ssl foobar"								"openssl foobar"
do_test "invalid cmd"				"./ft_ssl foobar foobar2"						"openssl foobar foobar2"

echo "====== TESTS WITH MD5 ======"

do_test "non existing file"			"./ft_ssl md5 foobar"							"md5 foobar"
do_test "file no rights"			"./ft_ssl md5 norights"							"md5 norights"
do_test "invalid option"			"./ft_ssl md5 -"								"md5 -"
do_test "invalid option"			"./ft_ssl md5 -l"								"md5 -l"
do_test "invalid option"			"./ft_ssl md5 -l file"							"md5 -l file"
do_test "invalid option"			"./ft_ssl md5 -s test -l file"					"md5 -s test -l file" 
do_test "no string after -s"		"./ft_ssl md5 -s"								"md5 -s"
do_test "empty string after -s"		"./ft_ssl md5 -s \"\""							"md5 -s \"\""
do_test "-r option"					"./ft_ssl md5 -r file"							"md5 -r file"
do_test "-r and -s options"			"./ft_ssl md5 -r -s test"						"md5 -r -s test"
do_test "-r and -s and -q options"	"./ft_ssl md5 -q -r -s test"					"md5 -q -r -s test"
do_test "-r and -q options"			"./ft_ssl md5 -q -r file"						"md5 -q -r file"
do_test "-q option"					"./ft_ssl md5 -q file"							"md5 -q file"
do_test "read from stdin"			"echo \"And above all\" | ./ft_ssl md5"			"echo \"And above all\" | md5"
do_test "read from stdin with -p"	"echo \"And above all\" | ./ft_ssl md5 -p"		"echo \"And above all\" | md5 -p"
do_test "read from stdin with -p -r" "echo \"And above all\" | ./ft_ssl md5 -p -r"	"echo \"And above all\" | md5 -p -r" # md5 error ?
do_test "read from stdin with -q -r" "echo \"Pity the living.\" | ./ft_ssl md5 -q -r" "echo \"Pity the living.\" | md5 -q -r"

do_test "file"						"./ft_ssl md5 file"								"md5 file"
do_test "file2"						"./ft_ssl md5 file2"							"md5 file2"
do_test "file3"						"./ft_ssl md5 file3"							"md5 file3"
do_test "file4"						"./ft_ssl md5 file4"							"md5 file4"
do_test "file5"						"./ft_ssl md5 file5"							"md5 file5"
do_test "file6"						"./ft_ssl md5 file6"							"md5 file6"
do_test "file7"						"./ft_ssl md5 file7"							"md5 file7"

echo "===== TESTS WITH SHA256 ====="

do_test "-r and -s options"			"./ft_ssl sha256 -r -s test"					
do_test "-r and -s and -q options"	"./ft_ssl sha256 -q -r -s test"				
do_test "-r and -q options"			"./ft_ssl sha256 -q -r file"					
do_test "-q option"					"./ft_ssl sha256 -q file"						
do_test "empty string after -s"		"./ft_ssl sha256 -s \"\""	"openssl sha256 empty"
do_test "read from stdin"			"echo \"And above all\" | ./ft_ssl sha256"
do_test "read from stdin with -p"	"echo \"And above all\" | ./ft_ssl sha256 -p"
do_test "read from stdin with -p -r" "echo \"And above all\" | ./ft_ssl sha256 -p -r"

do_test "file"						"./ft_ssl sha256 file"						"openssl sha256 file"
do_test "file2"						"./ft_ssl sha256 file2"						"openssl sha256 file2"
do_test "file3"						"./ft_ssl sha256 file3"						"openssl sha256 file3"
do_test "file4"						"./ft_ssl sha256 file4"						"openssl sha256 file4"
do_test "file5"						"./ft_ssl sha256 file5"						"openssl sha256 file5"
do_test "file6"						"./ft_ssl sha256 file6"						"openssl sha256 file6"
do_test "file7"						"./ft_ssl sha256 file7"						"openssl sha256 file7"

echo "===== TESTS WITH SHA512 ====="

do_test "file"						"./ft_ssl sha512 file"						"openssl sha512 file"
do_test "file2"						"./ft_ssl sha512 file2"						"openssl sha512 file2"
do_test "file3"						"./ft_ssl sha512 file3"						"openssl sha512 file3"
do_test "file4"						"./ft_ssl sha512 file4"						"openssl sha512 file4"
do_test "file5"						"./ft_ssl sha512 file5"						"openssl sha512 file5"
do_test "file6"						"./ft_ssl sha512 file6"						"openssl sha512 file6"
do_test "file7"						"./ft_ssl sha512 file7"						"openssl sha512 file7"
