#include "hashmap.h"
#include <cmath>
#include <stdexcept> 


hashmap::hashmap()
{
	this->table.resize(maximum_size);
}

void hashmap::insert(const std::string& key, const int& val)
{
    size_t index = hash_function(key);

    std::vector<std::pair<std::string, int>>& bucket = table[index];

    for (std::vector<std::pair<std::string, int>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->first == key)
        {
            it->second = val;
            return;
        }
    }

    bucket.emplace_back(key, val);
}





const int& hashmap::operator[](const std::string& key) const
{
    size_t index = hash_function(key);


    const std::vector<std::pair<std::string, int>>& bucket = table[index];

    for (std::vector<std::pair<std::string, int>>::const_iterator it = bucket.cbegin(); it != bucket.cend(); ++it)
    {
        if (it->first == key)
        {
            return it->second;
        }
    }

    throw std::out_of_range("Key not found");
}

int& hashmap::operator[](const std::string& key)
{
    size_t index = hash_function(key);

    std::vector<std::pair<std::string, int>>& bucket = table[index];

    for (std::vector<std::pair<std::string, int>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->first == key)
        {
            return it->second;
        }
    }

    throw std::out_of_range("Key not found");
}

bool hashmap::remove(const std::string& key)
{
    size_t index = hash_function(key);

    std::vector<std::pair<std::string, int>>& bucket = table[index];

    for (std::vector<std::pair<std::string, int>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->first == key)
        {
            bucket.erase(it);
            return true;
        }
    }

    return false;

}

bool hashmap::contains(const std::string& key)
{
    size_t index = hash_function(key);

    std::vector<std::pair<std::string, int>>& bucket = table[index];

    for (std::vector<std::pair<std::string, int>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->first == key)
        {
            return true;
        }
    }

    return false;
}

size_t hashmap::hash_function(const std::string& key) const
{
  /*  size_t hashCode = 0;
    for (int i = 0; i < key.length(); i++) {
        hashCode += key[i] * std::pow(PRIME_CONST, i);
    }
    return hashCode % maximum_size;*/

    const size_t FNV_offset_basis = 14695981039346656037ull;
    const size_t FNV_prime = 1099511628211ull;
    size_t hash = FNV_offset_basis;
    for (char c : key)
    {
        hash ^= static_cast<size_t>(c);
        hash *= FNV_prime;
    }
    return hash % maximum_size;
}
