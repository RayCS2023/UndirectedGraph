//
//  main.cpp
//  undirectedGraph
//
//  Created by Raymond Chen on 2020-04-06.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include <iostream>
#include "undirectedGraph.hpp"

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::stoi;
using std::numeric_limits;
int main(int argc, const char * argv[]) {
    
    undirectedGraph G;
    string line;

    while (!cin.eof()) {

        getline(cin, line);
        if(line == "")
            break;

        size_t space_index = line.find(" ");
        string command = line.substr(0,space_index);

        if(command == "i"){
            string info = line.substr(space_index+1);

            if(G.insert(info)){
                cout << "success" << endl;
            }
            else{
                cout << "failure" << endl;
            }
        }
        else if(command == "setd"){
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");
            size_t semi_colon_2 = info.find(";", semi_colon_1 + 1);

            string u = info.substr(0, semi_colon_1);
            string v = info.substr(semi_colon_1+1,semi_colon_2-(semi_colon_1+1));
            double w = stod(info.substr(semi_colon_2+1));

            if(G.setDistance(u, v, w)){
                cout << "success" << endl;
            }
            else{
                cout << "failure" << endl;
            }
        }
        else if(command == "s"){
            string info = line.substr(space_index+1);

            if(G.search(info) != -1){
                cout << "found " << info << endl;
            }
            else{
               cout << "not found" << endl;
            }
        }
        else if(command == "degree"){
            string info = line.substr(space_index+1);
            int deg = G.degree(info);

            if(deg != -1){
                cout << "degree of " << info << " " << deg << endl;
            }
            else{
               cout << "failure" << endl;
            }
        }
        else if(command == "graph_nodes"){
            cout << "number of nodes " << G.graph_nodes() << endl;
        }
        else if(command == "graph_edges"){
            cout << "number of edges " << G.graph_edges() << endl;
        }
        else if(command == "d"){
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");

            string u = info.substr(0, semi_colon_1);
            string v = info.substr(semi_colon_1+1);

            double d = G.d(u, v);

            if(!d){
                cout << "failure" << endl;
            }
            else{
                cout << "direct distance " << u << " to " << v << " " << d << endl;
            }
        }
        else if(command == "shortest_d"){
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");

            string u = info.substr(0, semi_colon_1);
            string v = info.substr(semi_colon_1+1);

            double shortest_d = G.shortest_d(u, v);

            if(shortest_d == numeric_limits<double>::infinity()){
                cout << "failure" << endl;
            }
            else{
                cout << "shortest distance " << u << " to " << v << " " << shortest_d << endl;
            }
        }
        else if (command == "clear"){
            G.clear();
            cout << "success" << endl;
        }
        else if(command == "print_path"){
            string info = line.substr(space_index+1);
            size_t semi_colon_1 = info.find(";");

            string u = info.substr(0, semi_colon_1);
            string v = info.substr(semi_colon_1+1);

            if(G.print_path(u, v) == numeric_limits<double>::infinity()){
                cout << "failure" << endl;
            }
        }
    }
    
    
    
    
    
    
    
    
    
//    G.insert("Toronto");
//    G.insert("Markham");
//    G.insert("Oshawa");
//    G.insert("Belleville");
//    G.insert("Kingston");
//    G.insert("Cornwall");
//    G.insert("Ottawa");
//    G.insert("Montreal");
//    G.insert("Montreal");
//
//    G.setDistance("Toronto", "Markham", 31.3);
//    G.setDistance("Toronto", "Oshawa", 59.9);
//    G.setDistance("Oshawa", "Ottawa", 409.0);
//    G.setDistance("Oshawa", "Belleville", 131.0);
//    G.setDistance("Belleville", "Kingston", 82.4);
//    G.setDistance("Kingston", "Cornwall", 184.0);
//    G.setDistance("Belleville", "Ottawa", 230.0);
//    G.setDistance("Ottawa", "Montreal", 199.0);
//    G.setDistance("Cornwall", "Montreal", 114.0);
//    G.setDistance("Markham", "Ottawa", 374.0);
//    //std::cout << G.shortest_d("Toronto", "Montreal");
//    G.print_path("Toronto", "Montreal");
//    G.clear();
    
//    cout << G.setDistance("x", "y", 374.0) << endl;
//    cout << G.setDistance("x", "Ottawa", 374.0) << endl;
//    cout << G.setDistance("Ottawa", "x", 374.0) << endl;
//    cout << G.setDistance("x", "x", 374.0) << endl;
//    cout << G.setDistance("Ottawa", "Ottawa", 374.0) << endl;
//    cout << G.setDistance("x", "Ottawa", 0) << endl;
//    cout << G.setDistance("toronto", "Ottawa", -10) << endl;
//    cout << G.setDistance("toronto", "Ottawa", 0) << endl;
    return 0;
}
