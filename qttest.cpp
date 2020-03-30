//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 3: QuadTree
// QuadTrees.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <algorithm>
#include<iomanip>
#include "City.h"
#include "QuadTree.h"

using std::stod;
using std::stoi;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{

	QuadTree qt(0,nullptr);
	string input = "";
	while (std::getline(cin, input)) {
		std::setprecision(0);
		int space = input.find(' ');
		string command = input.substr(0, space);
		string parameter = "";
		int counter = 0;
		if (space != -1) {
			parameter = input.substr(space + 1, input.length());
		}
		if (command == "i") {
			parameter = input.substr(space + 1, input.length());
			string pars[6];
			int index = parameter.find_first_of(";");
			//iterate to get all the parameters
			while (index != -1||counter!=6) {
				pars[counter] = parameter.substr(0, index);
				parameter = parameter.substr(index + 1, parameter.length());
				index = parameter.find_first_of(";");
				++counter;
			}
			//initilaize city object
			City city=City(pars[0], stod(pars[1]), stod(pars[2]), stoi(pars[3]), stoi(pars[4]), stoi(pars[5]));
			//initialize node object
			QuadNode* qn = new QuadNode(city, nullptr, nullptr, nullptr, nullptr, nullptr);
			qt.i(&qt.root, qn);
		}
		else if (command == "s") {
			parameter = input.substr(space + 1, input.length());
			int index = parameter.find(";");
			//determine the positoin
			double x = stod(parameter.substr(0, index));
			double y = stod(parameter.substr(index + 1, parameter.length()));
			QuadNode* temp = qt.s(qt.root, x, y);
			//print "not found" if not found
			if ( temp== nullptr) {
				cout << "not found" << endl;
			}
			//print "found [city_name]" if found
			else {
				cout << "found "<<temp->city.name << endl;
			}
		}
		else if (command == "q_max"||command=="q_min"||command=="q_total") {
			parameter = input.substr(space + 1, input.length());
			string pars[4];
			int index = parameter.find_first_of(";");
			//iterate through all the parameters
			while (counter != 4 || index!=-1) {
				pars[counter] = parameter.substr(0, index);
				parameter = parameter.substr(index + 1, parameter.length());
				++counter;
				index = parameter.find_first_of(";");
			}
			//node (x,y)
			QuadNode* parent = qt.s(qt.root,stod(pars[0]), stod(pars[1]));
			//cout << parent->city.name << endl;
			QuadNode* direction = nullptr;
			if (parent != nullptr) {
				#pragma region determine direction

				if (pars[2] == "NE") {
					direction = parent->NE;
				}
				else if (pars[2] == "NW") {
					direction = parent->NW;
				}
				else if (pars[2] == "SE") {
					direction = parent->SE;
				}
				else if (pars[2] == "SW") {
					direction = parent->SW;
				}

				#pragma endregion
				if (direction == nullptr) {
					cout << "failure" << endl;
				}
				else {
					if (command == "q_max") {
						cout << "max ";
						//max population
						if (pars[3] == "p") {
							cout << qt.q_max(direction, "p") << endl;
						}
						//max cost of living
						else if (pars[3] == "r") {
							std::setprecision(2);
							cout << qt.q_max(direction, "r") << endl;
						}
						//max net salary avg		
						else if (pars[3] == "s") {
							cout << qt.q_max(direction, "s") << endl;
						}
					}
					else if (command == "q_min") {
						cout << "min ";
						//max population
						if (pars[3] == "p") {
							cout << qt.q_min(direction, "p") << endl;
						}
						//max cost of living
						else if (pars[3] == "r") {
							std::setprecision(2);
							cout << qt.q_min(direction, "r") << endl;
						}
						//max net salary avg		
						else if (pars[3] == "s") {
							cout << qt.q_min(direction, "s") << endl;
						}
					}
					else if (command == "q_total") {
						cout << "total ";
						//total population
						if (pars[3] == "p") {
							cout<<qt.q_total(direction, "p")<<endl;
						}
						//total cost of living
						else if (pars[3] == "r") {
							std::setprecision(2);
							cout<<qt.q_total(direction, "r")<<endl;
						}
						//total net salary avg		
						else if (pars[3] == "s") {
							cout<<qt.q_total(direction, "s")<<endl;
						}
					}
				}
			}
			else {
				cout << "failure" << endl; //non existant (x,y)
			}
		}
		else if (input == "print") {
			print(qt.root);
			if (qt.treeSize != 0) {
				cout << endl;
			}
			
		}
		else if (input == "clear") {
			qt.clear(&qt.root);
			cout << "success" << endl;
		}
		else if (input == "size") {
			cout<<"tree size "<<qt.treeSize << endl;
		}
	}
	return 0;
}

//default constructor for City
City::City() {
	name = "";
	x = -1;
	y = -1;
	p = -1;
	r = -1;
	s = -1;
}
//constructor for city object
City::City(string name, double x, double y, int p, int r, int s) {
	this->name = name;
	this->x = x;
	this->y = y;
	this->p = p;
	this->r = r;
	this->s = s;
}

//destructor for city object
City::~City() {};

QuadNode::QuadNode(City city, QuadNode* parent, QuadNode* nw, QuadNode* ne, QuadNode* sw, QuadNode* se) {
	this->city = city;
	this->NW = nw;
	this->NE = ne;
	this->SW = sw;
	this->SE = se;
}
QuadNode::~QuadNode() {
	parent = nullptr;
	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;
}

//constructor for QuadTree class
//tree_size for the size of the tree
//root for the root node of the tree
QuadTree::QuadTree(int tree_size, QuadNode* root) {
	this->treeSize = tree_size;
	this->root = root;
}

//destructor for QuadTree class
QuadTree::~QuadTree() {
	root = nullptr;
}

//inserts a node for a city with a set of attributes
//parent is the pointer to the parent node of the node to be inserted (if it exists)
//obj contains the information to be stored in the node
void QuadTree::i(QuadNode** parent,QuadNode* obj)
{
	//case 1: empty tree upon insertion
	if (*parent == nullptr) {
		*parent = obj;
		++treeSize; //increment the size
		cout << "success" << endl;
	}
	//case 2: if city already exists in tree
	else if (s((*parent),obj->city.x, obj->city.y) !=nullptr) {
		cout << "failure" << endl;
	}
	
	
	//case 3: non-empty tree upon insertion
	else {
		//case 3.1: If x1 >= x and y1 > y, (x1,y1) is placed in the NE child node
		if (obj->city.x >= (*parent)->city.x && obj->city.y > (*parent)->city.y) {
			i(&((*parent)->NE), obj); //keep inserting recursively
			//check if this is the last iteration
			if ((*parent)->NE == obj) {
				obj->parent = *parent;
				//cout << obj->city.name<<" inserted NE of " <<(*parent)->city.name<< endl;
			}
		}
		//case 3.2: If x1 < x and y1 >= y, (x1,y1) is placed in the NW child node. 
		else if (obj->city.x < (*parent)->city.x && obj->city.y >= (*parent)->city.y) {
			i(&((*parent)->NW), obj); //keep inserting recursively
			//check if this is the last iteration
			if ((*parent)->NW == obj) {
				obj->parent = *parent;
				//cout << obj->city.name << " inserted NW of " << (*parent)->city.name << endl;
			}
		}
		//case 3.3: If x1 <= x and y1 < y, (x1,y1) is placed in the SW child node.
		else if (obj->city.x <= (*parent)->city.x && obj->city.y < (*parent)->city.y) {
			i(&((*parent)->SW), obj); //keep searching recursively
			//check if this is the last iteration
			if ((*parent)->SW == obj) {
				obj->parent = *parent;
				//cout << obj->city.name << " inserted SW of " << (*parent)->city.name << endl;
			}
		}
		//case 3.4: If x1 > x and y1 <= y, (x1,y1) is placed in the SE child node
		else if (obj->city.x > (*parent)->city.x && obj->city.y <= (*parent)->city.y) {
			i(&((*parent)->SE), obj); //keep searching recursively
			//check if this is the last iteration
			if ((*parent)->SE == obj) {
				obj->parent = *parent;
				//cout << obj->city.name << " inserted SE of " << (*parent)->city.name << endl;
			}
		}
	}
}


//searches for node (x,y)
//current is the current node being checked for matching location
//x is  longtitude
//y is lattitude
//return the node containing the city_name if found matching entry
//return nullptr if not found matching entry
QuadNode* QuadTree::s(QuadNode* current,double x, double y) {
	//case 1: tree is empty
	if (current == nullptr) {
		return nullptr;
	}
	//case 2: found node
	else if (x == current->city.x && y == current->city.y) {
		return current;
	}
	//case 3: tree is non-empty
	else {
		//case 3.1: If x1 >= x and y1 > y, (x1,y1) is placed in the NE child node
		if (x >= current->city.x && y > current->city.y) {
			return s(current->NE, x, y); //recursively search through the NE node
		}
		//case 3.2: If x1 < x and y1 >= y, (x1,y1) is placed in the NW child node
		else if (x < current->city.x && y >= current->city.y) {
			return s(current->NW, x, y); //recursively search through the NW node
		}
		//case 3.3: If x1 <= x and y1 < y, (x1,y1) is placed in the SW child node
		else if (x <= current->city.x && y < current->city.y) {
			return s(current->SW, x, y);//recursively search through the SW node
		}
		//case 3.4: If x1 > x and y1 <= y, (x1,y1) is placed in the SE child node
		else if (x > current->city.x&& y <= current->city.y) {
			return s(current->SE, x, y);//recursively search through the SE node
		}
		//unexpected case just return nullptr
		else {
			return nullptr;
		}
	}
} 

//finds the max value for attr under node (x,y) in direction d
//QuadNode* i the directional root
//attr is attribute for finding max
//returns the maximum attribute value of the nodes in the subtree under the node direction
int QuadTree::q_max(QuadNode* direction, string attr) {
	//base case: direction do not exist
	if (direction == nullptr) {
		return 0;
	}
	//recursive case: direction exists exists
	else {
		//obtain the directional root value based on the attribute requested
		int rootVal = 0;
		if (attr == "p") {
			rootVal = direction->city.p;
		}
		else if (attr == "r") {
			rootVal = direction->city.r;
		}
		else if (attr == "s") {
			rootVal = direction->city.s;
		}
		return std::max(std::max(std::max(
			q_max(direction->NE, attr), 
			q_max(direction->NW, attr)), std::max(
			q_max(direction->SE, attr), 
			q_max(direction->SW, attr))),
			rootVal);
	}
}

//finds the min value for attr under node (x,y) in direction d
//direction is the directional root
//attr is attribute
//returns the mininum attribute value of the nodes in the subtree under the node direction
int QuadTree::q_min(QuadNode* direction, string attr){
	//base case: direction do not exist
	if (direction == nullptr) {
		return -1;
	}
	//recursive case: direction exists
	else {
		//obtain the directional root value based on the attribute requested
		int rootVal = 0;
		int neMin=0, nwMin=0, seMin=0, swMin = 0;
		if (attr == "p") {
			//determine minimum of NE node subtree
			rootVal = direction->city.p; 
			neMin = q_min(direction->NE, attr);
			neMin=neMin=neMin==-1? rootVal: neMin ;
			nwMin = q_min(direction->NW, attr);
			//determine minimum of NW node subtree
			nwMin = nwMin=nwMin==-1? rootVal: nwMin;
			//determine minimum of SE node subtree
			seMin = q_min(direction->SE, attr);
			seMin=seMin=seMin==-1? rootVal : seMin;
			//determine minimum of SW node subtree
			swMin = q_min(direction->SW, attr);
			swMin=swMin==-1? rootVal: swMin;
		}
		else if (attr == "r") {
			rootVal = direction->city.r;
			//determine minimum of NE node subtree
			neMin = q_min(direction->NE, attr);
			neMin=neMin==-1? rootVal : neMin;
			//determine minimum of NW node subtree
			nwMin = q_min(direction->NW, attr);
			nwMin=nwMin==-1? rootVal : nwMin;
			//determine minimum of SE node subtree
			seMin = q_min(direction->SE, attr);
			seMin=seMin==-1? rootVal : seMin;
			//determine minimum of SW node subtree
			swMin = q_min(direction->SW, attr);
			swMin=swMin==-1? rootVal : swMin;
		}
		else if (attr == "s") {
			rootVal = direction->city.s;
			//determine minimum of NE node subtree
			neMin = q_min(direction->NE, attr);
			neMin=neMin==-1? rootVal : neMin;
			//determine minimum of NW node subtree
			nwMin = q_min(direction->NW, attr);
			nwMin=nwMin==-1? rootVal : nwMin;
			//determine minimum of SE node subtree
			seMin = q_min(direction->SE, attr);
			seMin=seMin==-1? rootVal : seMin;
			//determine minimum of SW node subtree
			swMin = q_min(direction->SW, attr);
			swMin=swMin==-1? rootVal : swMin;
		}
		return std::min(std::min(std::min(
			neMin, 
			nwMin), std::min(
			seMin, 
			swMin)), 
			rootVal);
	}
}

//finds the total value for attr under node (x,y) in direction d
//direction is the directional root
//attr is attribute
//returns the sum of the nodes in the subtree under the node direction
int QuadTree::q_total(QuadNode* direction, string attr) {
	//base case: direction do not exist
	if (direction == nullptr) {
		return 0;
	}
	//recursive case: direction exists exists
	else {
		//obtain the directional root value based on the attribute requested
		int rootVal = 0;
		if (attr == "p") {
			rootVal = direction->city.p;
		}
		else if (attr == "r") {
			rootVal = direction->city.r;
		}
		else if (attr == "s") {
			rootVal = direction->city.s;
		}
		//sum up the total of the subtrees of directional root
		return  q_total(direction->NE, attr)+
			q_total(direction->NW, attr)+ 
			q_total(direction->SE, attr)+ 
			q_total(direction->SW, attr)+
			rootVal;
	}
}

//prints the city names in the tree using inorder traversal
//obj is the node for traversing
void print(QuadNode* obj){
	//case 0: node is empty
	if (obj==nullptr) {
		return;
	}
	//case 1: only 1 node in tree
	else if (obj != nullptr&&obj->NE==nullptr&&obj->NW==nullptr&&obj->SE==nullptr&&obj->SW==nullptr) {
		cout << obj->city.name<<" ";
	}
	//case 2: more than 1 node in tree
	else {
		if (obj->NE != nullptr) {
			print(obj->NE);
		}
		if (obj->NW != nullptr) {
			print(obj->NW);
		}
		cout << obj->city.name<<" ";
		if (obj->SW != nullptr) {
			print(obj->SW);
		}
		if (obj->SE != nullptr) {
			print(obj->SE);
		}	
	}
}

//deletes all the nodes from the tree
//obj is the pointer to the node to be deleted
void QuadTree::clear(QuadNode** obj) {
	//case 0: empty tree
	if (*obj == nullptr) {
		return;
	}
	//case 1: only root in tree
	else if ((*obj) != nullptr && (*obj)->NE == nullptr && (*obj)->NW == nullptr && (*obj)->SE == nullptr && (*obj)->SW == nullptr) {
		delete *obj;
		*obj = nullptr;
		--treeSize;
	}
	//case 2: >1 nodes in tree
	else {
		if ((*obj)->NE != nullptr) {
			clear(&((*obj)->NE));
		}
		if ((*obj)->NW != nullptr) {
			clear(&((*obj)->NW));
		}
		if ((*obj)->SE != nullptr) {
			clear(&((*obj)->SE));
		}
		if ((*obj)->SW != nullptr) {
			clear(&((*obj)->SW));
		}
		clear(obj);
	}
} 



