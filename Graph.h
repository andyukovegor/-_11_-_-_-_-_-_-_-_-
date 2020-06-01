#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#pragma once

using namespace sf;
using namespace std;

class Graph { //вершина топологии
public:
	int N; //идентификатор вершины
	int x, y; //координаты вершины
	CircleShape* GraphicNodes;

};


#endif // NODE_H_INCLUDED
