#pragma once


#include <list>
#include <vector>
#include <utility>
#include <string>


//const int PRIME_CONST = 31;

//A hash map, also known as a hash table, is a data structure that allows efficient insertion, removal, and lookup of elements based on their keys. 
//It is a collection of key-value pairs where each key is mapped to a unique index in an array. 
//The index is computed using a hash function that takes the key as input and returns an integer value.

class hashmap
{

public:
	hashmap();


	void insert(const std::string& key, const int& val);

	const int& operator[](const std::string& key) const;
	int& operator[](const std::string& key);


	bool remove(const std::string& key);


	bool contains(const std::string& key);

private:
	const size_t maximum_size = 10000;

	size_t hash_function(const std::string& key) const;

	std::vector<std::vector<std::pair<std::string, int>>> table;
};