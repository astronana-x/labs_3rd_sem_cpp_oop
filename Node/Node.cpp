#include "Node.h"

Node :: Node(String* obj, Node* next_node) : data(obj), next(next_node) {}
Node :: ~Node() {}

String* Node::get_data() const{return data;}
Node* Node:: get_next() const{return next;}
void Node:: set_next(Node* new_node){next = new_node;}

