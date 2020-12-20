//
//  PriorityQueue.cpp
//  undirectedGraph
//
//  Created by Raymond Chen on 2020-04-07.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include "PriorityQueue.hpp"

//constructors
VertexSet::VertexSet(std::string const &vertexSet, double const &keyDis) {
    this->city = vertexSet;
    next = nullptr;
    this->keyDis = keyDis;
}

VertexSet::~VertexSet() {
    next = nullptr;
}
PriorityQueue::PriorityQueue(int size) {
    this->size = size;
    Hashtable.setSize(size);
}


int PriorityQueue::parent(const int &i) const {
    return (i-1)/2;
}

int PriorityQueue::left(const int &i) const {
    return 2*i+1;
}

int PriorityQueue::right(const int &i) const {
    return 2*i+2;
}

void PriorityQueue::insert(VertexSet* const v, double const d, const int &index) {
    //initalize vertex to add to pq
    Vertex vertex;
    vertex.adj = v;
    vertex.parent = "";
    vertex.d = d;
    
    this->vertex.push_back(vertex);
    
    //insert into hashtable
    Hashtable.insert(v->city,index);
    
}


bool PriorityQueue::empty() const { 
    return size==0? true:false;
}



Vertex PriorityQueue::extract_min() {
    //swap indices in hashtable
    Node* v1 = Hashtable.search(vertex[0].adj->city);
    Node* v2 = Hashtable.search(vertex[size-1].adj->city);
    
    int temp = v2->index;
    v2->index = v1->index;
    v1->index = temp;
    
    //swap values in vector of vertex
    Vertex min = vertex[0];
    vertex[0] = vertex[size-1];
    vertex[size-1] = min;
    size--;
    heapify(0);
    return min;
}

void PriorityQueue::heapify(int const &i) {
    //get left and right heaps
    
    int l = left(i);
    int r = right(i);
    
    //set smallest
    int smallest = i;
    
    if(l < size && vertex[l].d < vertex[i].d)
        smallest = l;
    
    if(r < size && vertex[r].d < vertex[smallest].d)
        smallest = r;
    
    if(smallest != i){
        //swap indices in hashtable
        Node* v1 = Hashtable.search(vertex[i].adj->city);
        Node* v2 = Hashtable.search(vertex[smallest].adj->city);
        
        int temp = v2->index;
        v2->index = v1->index;
        v1->index = temp;
        
        //swap obj stores at i and smallest
        Vertex tmp = vertex[smallest];
        vertex[smallest] = vertex[i];
        vertex[i] = tmp;
        
        //recursivly call heapify
        heapify(smallest);
    }
    
}

void PriorityQueue::build_heap() {
    for(int i = (size/2) - 1; i>=0 ;i--){
        heapify(i);
    }
}

Map& PriorityQueue::getHashTable()  {
    return this->Hashtable;
}

Vertex& PriorityQueue::getVertex(int const &i) {
    return vertex[i];
}

void PriorityQueue::modifyKey(int i) {
    while (i != 0 && vertex[parent(i)].d > vertex[i].d && i<= size){
       //swap i and parent of i
        Node* v1 = Hashtable.search(vertex[i].adj->city);
        Node* v2 = Hashtable.search(vertex[parent(i)].adj->city);
               
        int temp = v2->index;
        v2->index = v1->index;
        v1->index = temp;
        
        //swap obj stores at i and smallest
       Vertex tmp = vertex[parent(i)];
       vertex[parent(i)] = vertex[i];
       vertex[i] = tmp;
        
       i = parent(i);
    }
}

int PriorityQueue::getSize() const { 
    return this->size;
}

void Vertex::setD(const double &d) { 
    this->d = d;
}

void Vertex::setParent(std::string const &parent) {
    this->parent = parent;
}
