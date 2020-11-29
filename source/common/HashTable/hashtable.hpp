#include<bits/stdc++.h> 
#include"../components/component.hpp"

using namespace std; 

class Hash 
{ 
	int BUCKET; // No. of buckets 

	// Pointer to an array containing buckets 
	list<Component> *table; 
public: 
	Hash(int V); // Constructor 

	// inserts a key into hash table 
	void insertItem(int x , Component toAdd ); 

	// deletes a key from hash table 
	void deleteItem(int key ,Component toDelete); 

	// hash function to map values to key 
	int hashFunction(int x) { 
		return (x % BUCKET); 
	} 
    Component GetItem(int key , int id);

}; 

Hash::Hash(int b) 
{ 
	this->BUCKET = b; 
	table = new list<Component>[BUCKET]; 
} 

void Hash::insertItem(int key , Component toAdd ) 
{ 
	int index = hashFunction(key); 
	table[index].push_back(toAdd); 
} 

void Hash::deleteItem(int key , Component toDelete) 
{ 
// get the hash index of key 
    int index = hashFunction(key); 

    // find the key in (inex)th list 
    list <Component> :: iterator i; 
    for (i = table[index].begin(); i != table[index].end(); i++) { 
	    if (*i == toDelete) 
	    break; 
    } 

    // if key is found in hash table, remove it 
    if (i != table[index].end()) 
	    table[index].erase(i); 
} 

Component Hash::GetItem(int key , int id){
    // get the hash index of key 
    int index = hashFunction(key); 

    // find the key in (inex)th list 
    list <Component> :: iterator i; 
    for (i = table[index].begin(); i != table[index].end(); i++) { 
	    if (i->GetID() == id) 
            return *i ;
    } 
    return null;
}


