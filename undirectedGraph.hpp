//
//  undirectedGraph.hpp
//  undirectedGraph
//
//  Created by Raymond Chen on 2020-04-06.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#ifndef undirectedGraph_hpp
#define undirectedGraph_hpp

#include "PriorityQueue.hpp"

class undirectedGraph{
private:
    std::vector<VertexSet*> adj;
    int totalVertex;
    int totalEdges;
public:
    bool insert(std::string const &city);
    bool setDistance(std::string const &city1, std::string const &city2, double const &distance);
    int search(std::string const &city) const;
    int degree(std::string const &city) const;
    int graph_nodes() const;
    int graph_edges() const;
    double d(std::string const &city1, std::string const &city2) const;
    void clear();
    double shortest_d(std::string const &city1, std::string const &city2) const;
    double print_path(std::string const &city1, std::string const &city2) const;
    
    undirectedGraph();
    ~undirectedGraph();
};


#endif /* undirectedGraph_hpp */
