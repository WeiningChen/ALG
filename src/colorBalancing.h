#ifndef  COLOR_BALANCING_H
#define COLOR_BALANCING_H

#include <vector>
#include <iostream>


using namespace std;

class Window;
class Block;
class Group;
class Grid;

struct Coordinate
{
	int x_left;
	int x_right;
	int y_up;
	int y_down;
};

// For optimization
struct WindowsSet
{
	vector<Window*> _disjointWindows;
};


class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();
	bool readBlock(istream &);
	void buildGroup();
private:
	int alpha, beta, omega;
	vector<Window> _windows;
	vector<Block> _blocks;
	vector<Group> _group;
	Coordinate Bbox_coord;
};

class Block
{
public:
	Block();
	Block(Coordinate);
	~Block();
	int area();
private:
	Coordinate blockCoord;
	vector<Block*> adjBlocks;
	vector<Window*> windows;
};

class Group
{
public:
	Group();
	~Group();
private:
	int area;
	vector<Block*> blocks_A;
	vector<Block*> blocks_B;
	//Note: area(A) > area(B)
	vector<Window*> windows;
};

class Grid
{
public:
	Grid();
	~Grid();
private:
	Coordinate gridCoord;
	vector<Block*> blocks;
};

class Window
{
public:
	Window();
	~Window();
private:
	Coordinate windowCoord;
	vector<Group*> innerGroup;
	vector<Group*> crossGroup;
	static int omega;
};

#endif