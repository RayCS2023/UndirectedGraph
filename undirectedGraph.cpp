//
//  undirectedGraph.cpp
//  undirectedGraph
//
//  Created by Raymond Chen on 2020-04-06.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include "undirectedGraph.hpp"
using std::size_t;
using std::numeric_limits;

undirectedGraph::undirectedGraph() {
    totalVertex = 0;
    totalEdges = 0;
}

undirectedGraph::~undirectedGraph() {
    if(totalVertex!=0)
        clear();
}

bool undirectedGraph::insert(const std::string &city) {
    
    //check if city already exist
    for(size_t i = 0; i < adj.size(); i++){
        if(adj[i]->city == city){
            return false;
        }
    }
    
    //create the vertex with distance to itself as 0
    VertexSet *v = new VertexSet(city, 0.0);
    
    //add to vector
    adj.push_back(v);
    totalVertex++;
    
    return true;

}

bool undirectedGraph::setDistance(const std::string &city1, const std::string &city2, const double &distance) {
    
    //check if two cities are identical
    if(city1 == city2)
        return false;
    
    //check if d <= 0
    if(distance <= 0)
        return false;
    
    //store the index if the cities are found
    int index1 = search(city1);
    int index2 = search(city2);
    
    if(index1 == -1 || index2 == -1)
        return false;
    
    //used for traversing
    VertexSet *tmp1 = adj[index1];
    VertexSet *tmp2 = adj[index2];
    bool edgeExist = false;
    
    //add edge to city1's list
    while(tmp1->next != nullptr){
        
        tmp1 = tmp1->next;
        
        //if update edge required
        if(tmp1->city == city2 || tmp1->city == city1){
            tmp1->keyDis = distance;
            edgeExist = true;
            break;
        }
    }
    
    //if add edge required
    if(!edgeExist){
        tmp1->next = new VertexSet(city2, distance);
        totalEdges++;
    }
    
    //reset edgeExist to false
    edgeExist = false;
    
    //add edge to city2's list
    while(tmp2->next != nullptr){
        
        tmp2 = tmp2->next;
        
        //if update edge required
        if(tmp2->city == city2 || tmp2->city == city1){
            tmp2->keyDis = distance;
            edgeExist = true;
            break;
        }
    }
    
    //if add edge required
    if(!edgeExist){
        tmp2->next = new VertexSet(city1, distance);
    }
    
    return true;
}

int undirectedGraph::search(const std::string &city) const {
    //search through vector and return the index if found
    for(int i = 0; i < adj.size(); i++){
        if(adj[i]->city == city){
            return i;
        }
    }
    return -1;
}

int undirectedGraph::degree(const std::string &city) const {
    //search for the city and gets it index
    int index = search(city);
    
    //return failure if not found
    if(index == -1)
        return -1;
    
    //variable for traversing
    VertexSet *tmp = adj[index];
    
    //counter
    int count = 0;
    
    //increament counter if edge exist
    while(tmp->next != nullptr){
        tmp = tmp->next;
        count++;
    }
    
    return count;
}

int undirectedGraph::graph_nodes() const {
    return totalVertex;
}

int undirectedGraph::graph_edges() const {
    return totalEdges;
}

double undirectedGraph::d(const std::string &city1, const std::string &city2) const {
    
    //check if two cities are identical
    if(city1 == city2)
        return false;
    
    //store the index if the cities are found
    int index1 = search(city1);
    int index2 = search(city2);
    
    if(index1 == -1 || index2 == -1)
        return false;
    
    //node use for traversing
    VertexSet *tmp = adj[index1];
    
    while(tmp->next != nullptr){
        
        tmp = tmp->next;
        
        //return distance of edge exist
        if(tmp->city == city2 || tmp->city == city1){
            return tmp->keyDis;
        }
    }
    
    //edges will not edge at this point, return false
    return false;
    
}

void undirectedGraph::clear() {
    //loops through all vertex in the vector
    for(size_t i = 0; i < adj.size(); i++){
        VertexSet *tmp = adj[i];
        //ilterate through each list and delete allocated memory
        while(tmp != nullptr){
            VertexSet *curr = tmp;
            tmp = tmp->next;
            delete curr;
            curr = nullptr;
        }
    }
    //clear all elements in the vector
    adj.clear();
    //set default values to 0
    totalVertex = 0;
    totalEdges = 0;
}

double undirectedGraph::shortest_d(const std::string &city1, const std::string &city2) const {
    
    //check if two cities are identical
    if(city1 == city2)
        return numeric_limits<double>::infinity();
    
    //initalize priority quene
    PriorityQueue pq(totalVertex);
    
    //insert vertex in to quene
    for (int i = 0; i < adj.size(); i++){
        if(adj[i]->city == city1){
            //set distance to 0 at the starting node
            pq.insert(adj[i], 0.0,i);
        }
        else{
            pq.insert(adj[i], numeric_limits<double>::infinity(),i);
        }
    }
    
    //check if the cities exist
    if(pq.getHashTable().search(city1) == nullptr || pq.getHashTable().search(city2) == nullptr)
            return numeric_limits<double>::infinity();
    
    //call build_heap to make pq a heap
    pq.build_heap();
    while(!pq.empty()){
        //extract the first element of the PQ
        Vertex u = pq.extract_min();
        
        //if element extracted from the PQ is the destination, return
        if(u.adj->city == city2){
            return u.d;
        }
        //assign v to the nodes the u connects to
        VertexSet* v = u.adj->next;
        
        //loop through all the u's neighbours
        while(v!=nullptr){
            std::string city = v->city;
            //find the index of the neighbour in hashtable
            int i = pq.getHashTable().search(city)->getIndex();
            
            //skip if i is the index of a removed element
            if(i > pq.getSize()){
                v = v->next;
                continue;
            }
            
            //relax the edge
            if(pq.getVertex(i).d > u.d + v->keyDis){
                pq.getVertex(i).setD(u.d + v->keyDis);
                pq.getVertex(i).setParent(u.adj->city);
            }
            
            //called to maintain heap property
            pq.modifyKey(i);
            v = v->next;
        }
    }
    return numeric_limits<double>::infinity();
    
}

double undirectedGraph::print_path(const std::string &city1, const std::string &city2) const {
        //check if two cities are identical
     if(city1 == city2)
         return numeric_limits<double>::infinity();

     //initalize priority quene
     PriorityQueue pq(totalVertex);


     //insert vertex in to quene
     for (int i = 0; i < adj.size(); i++){
         if(adj[i]->city == city1){
             //set distance to 0 at the starting node
             pq.insert(adj[i], 0.0,i);
         }
         else{
             pq.insert(adj[i], numeric_limits<double>::infinity(),i);
         }
     }

     //check if the cities exist

     if(pq.getHashTable().search(city1) == nullptr || pq.getHashTable().search(city2) == nullptr)
             return numeric_limits<double>::infinity();

     //call build_heap to make pq a heap
     pq.build_heap();
     while(!pq.empty()){
         //extract the first element of the PQ
         Vertex u = pq.extract_min();
         //if element extracted from the PQ is the destination, print the path
         if(u.adj->city == city2 && u.d!=numeric_limits<double>::infinity()){
             
             //stores all the vertexs of the shortest path
             std::vector<std::string> v;
             
             //find the parent of the last removed element
             std::string tmp = u.parent;
             
             //keep reassigning tmp until we reached the start city. Add the tmp to v after every ilteration
             while(tmp != city1){
                 v.push_back(tmp);
                 int i = pq.getHashTable().search(tmp)->getIndex();
                 tmp = pq.getVertex(i).parent;
             }
             
             //print the vertexs in the vector
             std::cout << city1 << " ";
             for(int i = v.size() - 1; i>=0; i--){
                 std::cout << v[i] << " ";
             }
             std::cout << city2 << std::endl;
             
             return true;
         }
         //assign v to the nodes the u connects to
         VertexSet* v = u.adj->next;
         
         //loop through all the u's neighbours
         while(v!=nullptr){
             std::string city = v->city;
             
             //find the index of the neighbour in hashtable
             int i = pq.getHashTable().search(city)->getIndex();
             
             //skip if i is the index of a removed element
             if(i > pq.getSize()){
                 v = v->next;
                 continue;
             }
             //relax the edge
             if(pq.getVertex(i).d > u.d + v->keyDis){
                 pq.getVertex(i).setD(u.d + v->keyDis);
                 pq.getVertex(i).setParent(u.adj->city);
             }
             
             //called to maintain heap property
             pq.modifyKey(i);
             v = v->next;
         }
     }
     return numeric_limits<double>::infinity();
}
