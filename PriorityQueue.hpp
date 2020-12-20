//
//  PriorityQueue.hpp
//  undirectedGraph
//
//  Created by Raymond Chen on 2020-04-07.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include <vector>
#include <string>
#include <limits>
#include "Map.hpp"

struct VertexSet{
    std::string city;
    double keyDis;
    VertexSet *next;
    VertexSet(std::string const &vertexSet, double const &keyDis);
    ~VertexSet();
};

struct Vertex{
    VertexSet* adj;
    std::string parent;
    double d;
    void setD(double const &d);
    void setParent(std::string const &parent);
};



class PriorityQueue{
public:
    PriorityQueue(int size);
    int parent(int const &i) const;
    int left(int const &i) const;
    int right(int const &i) const;
    void insert(VertexSet* const v, double const d,const int &index);
    bool empty() const;
    Vertex extract_min();
    void heapify(int const &i);
    void build_heap();
    void modifyKey(int i);
    
    //getters
    Vertex& getVertex(int const &i);
    Map& getHashTable() ;
    int getSize() const;
private:
    int size;
    Map Hashtable;
    std::vector<Vertex> vertex;
};

#endif /* PriorityQueue_hpp */
