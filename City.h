#pragma once
//Qinying Wu
//20783213
//q227wu
//ECE250
//Project 3: QuadTree
//header for city object
#include<string>
using std::string;

class City {
public:
	City();//default constructor for City()
	//object initialization for City
	City(string name, double x, double y, int p, int r, int s);
	~City(); //destructor for City()
	string name; //name of city
	double x; //longtitude
	double y; //lattitude
	int p; //population
	int r; //cost of living
	int s; //average net salary

};

