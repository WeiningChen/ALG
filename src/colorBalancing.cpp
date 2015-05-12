#include "colorBalancing.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <limits>

using namespace std;
Coordinate parseBlock(string);

//BoundingBox{{{
BoundingBox::BoundingBox() 
{
	Bbox_coord.x_left = numeric_limits<int>::max();
	Bbox_coord.x_right = numeric_limits<int>::min();
	Bbox_coord.y_down = numeric_limits<int>::max();
	Bbox_coord.y_up = numeric_limits<int>::min();
}

bool BoundingBox::readBlock(istream & is)
{
	string word,line;

	is>>word;
	if(word.substr(0,6)!="ALPHA="){
		cerr<<"ERROR** BoundingBox::read() : Wrong input format!! "<<endl;
		return false;
	}
	istringstream(word.substr(6))>>alpha;

	if(word.substr(0,5)!="BETA="){
		cerr<<"ERROR** BoundingBox::read() : Wrong input format!! "<<endl;
		return false;
	}
	istringstream(word.substr(5))>>beta;

	if(word.substr(0,6)!="OMEGA="){
		cerr<<"ERROR** BoundingBox::read() : Wrong input format!! "<<endl;
		return false;
	}
	istringstream(word.substr(6))>>omega;
	while(getline(is,line)){
		Coordinate temp = parseBlock(line);
		_blocks.push_back(Block(temp));

		if(Bbox_coord.x_left>temp.x_left)
			Bbox_coord.x_left = temp.x_left;

		if(Bbox_coord.y_down>temp.y_down)
			Bbox_coord.y_down = temp.y_down;

		if(Bbox_coord.x_right < temp.x_right)
			Bbox_coord.x_right = temp.x_right;

		if(Bbox_coord.y_up < temp.y_up)
			Bbox_coord.y_up = temp.y_up;
	}
}

Coordinate parseBlock(string _coordstr)
{
	string token;
	stringstream ss(_coordstr);
	Coordinate _coord;
	
	getline(ss,token,',');
	istringstream(token)>>_coord.x_left;  
	
	getline(ss,token,',');
	istringstream(token)>>_coord.y_down ;
	
	getline(ss,token,',');
	istringstream(token)>>_coord.x_right;
	
	getline(ss,token,',');
	istringstream(token)>>_coord. y_up;

	return _coord;
}

void BoundingBox::buildGroup()
{
	//Plot grid
	int grid_x_size = (Bbox_coord.x_right - Bbox_coord.x_left)/alpha + 1;
	int grid_y_size = (Bbox_coord.y_up - Bbox_coord.y_down)/beta + 1;

	Grid**  _grid = new Grid*[grid_x_size];
	for(size_t i = 0; i < grid_x_size ; ++i){
		_grid[i] = new Grid[grid_y_size];
	}
}

BoundingBox::~BoundingBox() {}
//}}} BoundingBox

//Block{{{
Block::Block() {}

Block::Block(Coordinate _coord)
{
	blockCoord = _coord;
}
int Block::area()
{
	return (blockCoord.x_right - blockCoord.x_left)*(blockCoord.y_up - blockCoord.y_down);
}

Block::~Block() {}
//}}}Block

// Group{{{
Group::Group() {}

Group::~Group() {}
//}}}Group

//Grid{{{
Grid::Grid() {}
Grid::~Grid() {}
//}}}Grid

//Window{{{
Window::Window() {}
Window::~Window(){}
//}}}Window