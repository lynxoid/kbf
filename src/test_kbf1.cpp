// test base bloom filter
#include "catch.hpp"

#include "KBF1.hpp"
#include "JellyfishUtil.h"

// define main

TEST_CASE( "testing kbf1", "[kbf1]" ) {
	KBF1 bf(20);
	size_t expected_size = 1024 * 1024 * 32 * 10;

	REQUIRE(bf.get_bit_count() == expected_size );
	REQUIRE(bf.get_hash_count() == 2);
	REQUIRE(bf.get_inserted_count() == 0);
	REQUIRE(!bf.contains(0));
}

// by design, inserting just 1 kmer into the filter should result in a false 
// negative
TEST_CASE( "testing kbf1 single insertion", "[kbf1]" ) {
	KBF1 bf(20);
	size_t expected_size = 1024 * 1024 * 32 * 10;

	bf.add(1);

	REQUIRE(bf.get_bit_count() == expected_size );
	REQUIRE(bf.get_hash_count() == 2);
	REQUIRE(bf.get_inserted_count() == 1);
	REQUIRE(!bf.contains(1));
}

TEST_CASE( "testing kbf1 extended checks", "[kbf1]" ) {
	const int k = 20;
	KBF1 bf(k);
	size_t expected_size = 1024 * 1024 * 32 * 10;

	string read = "ACGTGCTAGATGCAGTTGACGAGATCCAGACT";
	for (int i = 0; i < read.size() - k + 1; i++)
		bf.add( mer_string_to_binary(read.substr(i, k).c_str(), k) );

	REQUIRE(bf.get_bit_count() == expected_size );
	REQUIRE(bf.get_hash_count() == 2);
	REQUIRE(bf.get_inserted_count() == read.size() - k + 1);
	for (int i = 0; i < read.size() - k + 1; i++)
		REQUIRE(bf.contains( mer_string_to_binary(read.substr(i, k).c_str(), k) ) );
	REQUIRE(bf.get_extended_check_count() == 1 + read.size() - k + 1);
}

// inserting several overlapping kmers, however, ensures there are no false
// negatives and fewer false positives
TEST_CASE( "testing kbf1 multiple insertion", "[kbf1]" ) {
	const int k = 20;
	KBF1 bf(k);
	size_t expected_size = 1024 * 1024 * 32 * 10;

	string read = "ACGTGCTAGATGCAGTTGACGAGATCCAGACT";
	for (int i = 0; i < read.size() - k + 1; i++)
		bf.add( mer_string_to_binary(read.substr(i, k).c_str(), k) );

	REQUIRE(bf.get_bit_count() == expected_size );
	REQUIRE(bf.get_hash_count() == 2);
	REQUIRE(bf.get_inserted_count() == read.size() - k + 1);
	for (int i = 0; i < read.size() - k + 1; i++)
		REQUIRE(bf.contains( mer_string_to_binary(read.substr(i, k).c_str(), k) ) );
}