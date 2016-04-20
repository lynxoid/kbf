// test base bloom filter
#include "catch.hpp"

#include "BaseBloomFilter.hpp"

// define main

TEST_CASE( "testing BaseBloomFilter", "[base_bloom_filter]" ) {
	BaseBloomFilter bf(20);
	REQUIRE(bf.get_bit_count() == 1024 * 1024 * 32 * 10);
	REQUIRE(bf.get_hash_count() == 2);
	CHECK(bf.get_inserted_count() == 0);
}

TEST_CASE( "testing add BaseBloomFilter", "[base_bloom_filter]" ) {
	BaseBloomFilter bf(20);
	size_t expected_size = 1024 * 1024 * 32 * 10;
	
	bf.add(1);
	REQUIRE(bf.get_bit_count() == expected_size);
	REQUIRE(bf.get_hash_count() == 2);
	REQUIRE(bf.get_inserted_count() == 1);
}

TEST_CASE( "testing contains BaseBloomFilter", "[base_bloom_filter]" ) {
	BaseBloomFilter bf(20);
	size_t expected_size = 1024 * 1024 * 32 * 10;
	
	bf.add(1);
	REQUIRE(bf.get_bit_count() == expected_size);
	REQUIRE(bf.contains(1));
	// should not expect this collision since the BF so far is empty (except 
	// for 1 bit)
	REQUIRE(!bf.contains(0) );
}

TEST_CASE( "testing populate BaseBloomFilter", "[base_bloom_filter]" ) {
	BaseBloomFilter bf(20);
	size_t expected_size = 1024 * 1024 * 32 * 10;
	unordered_set<kmer_t> kmers;
	for (int i = 0; i < 1000; i++)
		kmers.emplace(i);

	bf.populate(kmers);
	REQUIRE(bf.get_bit_count() == expected_size);
	for (const auto & item : kmers)
		REQUIRE(bf.contains(item));
	REQUIRE(bf.get_inserted_count() == kmers.size());
}