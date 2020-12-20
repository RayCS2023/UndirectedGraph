//
//  Map.cpp
//  HashTable
//
//  Created by Raymond Chen on 2020-02-10.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include "Map.hpp"
using std::string;
using std::to_string;

//constructor
Map::Map() {
    size = 0;
}

//destructor
Map::~Map() {
    clear();
}

//primary hash function
int Map::hash(const std::string &val) const {
    return val[val.length() - 1]%size;
}

//insert a key into Hashtable
bool Map::insert(const std::string &val,const int &index) {
    Node* found = search(val); //see if the key exist
    int k = hash(val);
    
    if(found == nullptr){ //if the key wasn't find
        Node* node = new Node(val,index); // construct a new node
        hashTable[k].insert(node); // insert into list
    }
    else{
        return false; 
    }

    return true;
}

//set the size of the hashable
bool Map::setSize(const int &s) {
    clear(); //clear all the values previously
    List t;
    size = s;
    hashTable.assign(size, t);// assign empty lists to hashtable slots
    return true;
}

//search for key in hashtable
Node* Map::search(const std::string &val) {
    int k = hash(val);
    
    Node* tmp = hashTable[k].getHead(); //get the head node of the chain
    
    //traverse the list to find the key
    while(tmp !=nullptr){
        if(tmp->val == val){
            return tmp;
            break;
        }
        tmp = tmp->p_next;
    }
    return nullptr;
}

//called in destructor to deallocate all memory used by the Lists
void Map::clear() {
    //for every slot in hashtable, find the chain and deallocate its memory
    for(int i = 0; i < hashTable.size(); i++){
        if(hashTable[i].getHead() != nullptr){
            hashTable[i].clear();
        }
    }
}










