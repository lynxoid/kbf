// test base bloom filter
#include "catch.hpp"

#include "BaseBloomFilter.hpp"

// define main

TEST_CASE( "testing BaseBloomFilter", "[bae_bloom_filter]" ) {
	BaseBloomFilter bf(20);
	REQUIRE(bf.get_bit_count() == 1024 * 1024 * 32 * 10);
	REQUIRE(bf.get_hash_count() == 2);
	CHECK(bf.get_inserted_count() == 0);
}