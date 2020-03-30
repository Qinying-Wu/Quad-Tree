#pragma once
//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 3: QuadTree
//header for quadtree and quad node object

#include<string>
#include "City.h"
using std::string;


//class for the actual node that comprises the QuadTree
class QuadNode {
public:
	QuadNode* parent; //parentnode
	QuadNode* NW; //nw node
	QuadNode* NE; //ne node
	QuadNode* SW; //sw node
	QuadNode* SE; //se node
	City city; //node data
	QuadNode(City city, QuadNode* parent, QuadNode* nw, QuadNode* ne, QuadNode* sw, QuadNode* se);
	~QuadNode();
};

class QuadTree {
public:
	void i(QuadNode** parent, QuadNode* obj); //inserts a node for a city with a set of attributes
	QuadNode* s(QuadNode* parent,double x, double y); //searches for node (x,y)
	//finds the max value for population under node (x,y) in direction d
	int q_max(QuadNode* direction,string attr);
	//finds the min value for attr under node (x,y) in direction d
	int q_min(QuadNode* direction, string attr);
	//finds the total value for attr under node (x,y) in direction d
	int q_total(QuadNode* direction, string attr);
	void clear(QuadNode** obj); //deletes all the nodes from the tree
	QuadTree(int tree_size,QuadNode* root);
	~QuadTree();
	int treeSize;
	QuadNode* root;
};


void print(QuadNode* obj); //function declaration for printing the city names