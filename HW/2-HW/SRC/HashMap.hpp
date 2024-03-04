#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using std::string;
using std::pair;
using std::vector;
using std::cout;
using std::hash;
/*
    Instructions for HashMap.hpp:
    Hash Map - using vector of vectors

    Below are the interfaces for the classes you will implement. You may include additional functions as needed.  Note: it is your job to determine which parameters and methods should be const!

    This class will implement a custom Hash Map. You can write a hashing function of your choosing or you may use the hash function from std. Keep in mind that it should work for all data types and for large data sets.

    Function Signatures	Description

    HashMap(std::vector<T> vals, int size)	Initialize the map with a list of elements. You will also fix the size of your hash table(map) through the constructor. Note: this would be independent of the size of the list of elements you are inserting.

    int hashKey(T val)	This function should return the bucket in which the element should be inserted.

    void insertElement(T val)	Insert an element at the appropriate position in the Map.
    bool search(T val)	Returns if the element is found in the Map
    void deleteElement (T val)	Delete the element from the Map
    std::ostream& operator<<(std::ostream& os, const HashMap<U> &m);	overload the << operator for Map<T>. This should print out the contents of the Map in the format: {T, T, T, T}. You will print the elements in the order of the keys.

    

*/


template <typename T>
// This hashmap uses chaining to handle collisions
// if there is a repeated hash key, the element is added to the vector at that index, it will go in order of insertion
class HashMap {
    private:
        vector<vector<T>> map;
        int size;

    public:
        // constructor
        HashMap(std::vector<T> vals, int size) : map(size), size(size) {
            map = std::vector<vector<T>>(size);
            for (auto val : vals) {
                insertElement(val);
            }
        }
        // decunstructor
        ~HashMap() = default;
        // hashKey
        int hashKey(T val) {
            size_t hash = std::hash<T>{}(val);
            return hash % size;
        }   

        // insertElement
        void insertElement(T val) {
            int key = hashKey(val);
            map[key].push_back(val);
        }
        // search
        bool search(T val) {
            int key = hashKey(val); // Get the hash key
            // Iterate over all elements in the corresponding bucket
            for(const auto& element : map[key]) {
                // If the element matches with val, return true
                if (element == val) {
                    return true;
                }
            }

            // If no matching element is found, return false
            return false;
        }
        // deleteElement
        void deleteElement(T val) {
            int key = hashKey(val);
            // Iterate over all elements in the corresponding bucket
            for(auto it = map[key].begin(); it != map[key].end(); it++) {
                // If the element matches with val, remove it
                if (*it == val) {
                    map[key].erase(it);
                    return;
                }
            }
        }
        // overload the << operator for Map<T>
        friend std::ostream& operator<<(std::ostream& os, const HashMap<T> &m) {
            os << "{";
            for (int i = 0; i < m.size; i++) {
                for (auto val : m.map[i]) {
                    os << val << ", ";
                }
            }
            os << "}";
            return os;
        }
};



// has to add this to deal with hashing strings, used stackoverflow and chatgpt for help
template <>
inline int HashMap<std::string>::hashKey(std::string val) {
    size_t hash = std::hash<std::string>{}(val);
    return hash % size;
}





#endif // HASHMAP_HPP