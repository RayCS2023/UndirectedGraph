//
//  Map.hpp
//  HashTable
//
//  Created by Raymond Chen on 2020-02-10.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <vector>
#include "List.hpp"

class Map{
public:
    Map();
    ~Map();
    int hash(const std::string &val) const;
    bool setSize(const int &s);
    bool insert(const std::string &val,const int &index);
    Node* search(const std::string &val);
    void clear();
private:
    int size;
    std::vector<List> hashTable;
};



#endif /* Map_hpp */
