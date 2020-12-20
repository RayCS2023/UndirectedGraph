//
//  List.cpp
//  HashTable
//
//  Created by Raymond Chen on 2020-02-09.
//  Copyright © 2020 Raymond Chen. All rights reserved.
//

#include "List.hpp"

//Node constructor
Node::Node(const std::string &val, const int &index){
    this->val = val;
    this->index = index;
    p_next = nullptr;
    p_prev = nullptr;
}

//Node destructor
Node::~Node(){
    p_next = nullptr;
    p_prev = nullptr;
}

int Node::getIndex() const {
    return this->index;
}


//string Node::getVal() const{
//    return val;
//}
//
//unsigned long long int Node::getNumber() const{
//    return number;
//}
//
//Node *Node::getNext() const {
//    return p_next;
//}
//
//Node *Node::getPrev() const {
//    return p_prev;
//}


//List constructor
List::List(){
    count = 0;
    head = nullptr;
    tail = nullptr;
}

//List destructor
List::~List(){
    clear();
}

//Node getters
Node* List::getHead() const{
    return head;
}

Node* List::getTail() const{
    return tail;
}

//called in destructor to remove all dynamic memory
void List::clear(){
    while(!empty()){
        remove(head);
    }
}

//check if List is empty
bool List::empty() const{
    return (count==0);
}

//insert a node in list
void List::insert(Node* node){
    if(empty()){
        head = node;
        tail = node;
    }
    else{
        Node* tmp = head;
        while(tmp!= nullptr){
            tmp = tmp->p_next;
        }
        
        //insertion after tail (new tail)

        node->p_prev = tail;
        tail->p_next = node;
        tail = node;
        
//        //insertion before head (new head)
//        else if(tmp == head){
//            node->p_next = head;
//            head->p_prev = node;
//            head = node;
//        }
//        //insertion before body node
//        else{
//            tmp->p_prev->p_next = node;
//            node->p_prev = tmp->p_prev;
//            tmp->p_prev = node;
//            node->p_next = tmp;
//
//        }
    }
    count++;
}

//remove a node in List
void List::remove(Node* node){
    //only one node exist, need this case because we dont need to set up the next/prev pointers
    if(count == 1){
        delete node;
        tail = nullptr;
        head = nullptr;
    }
    //node to remove is the head
    else if(node == head){
        head = head->p_next;
        head->p_prev = nullptr;
        delete node;
    }
    //node to remove is the tail
    else if(node == tail){
        tail = tail->p_prev;
        tail->p_next = nullptr;
        delete node;
    }
    //node to remove is a body node
    else{
        node->p_prev->p_next = node->p_next;
        node->p_next->p_prev = node->p_prev;
        delete node;
    }
    count--;
}


