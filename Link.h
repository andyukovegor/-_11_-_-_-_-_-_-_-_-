#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED
#pragma once

using namespace sf;
using namespace std;

class Link {
public:
	int M; //идентификатор ребра
	Graph A, B; //концы ребра
	int F; //ВЕС ребра
};


#endif // LINK_H_INCLUDED
