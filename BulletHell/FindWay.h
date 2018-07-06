#pragma once
#include <vector>
#include "Enemy.h"
class FindWay
{
public:
	struct List
	{
		int position;
		int point_to_end;
		int point_to_start;
		int all_points;
		bool isStart = false;
		List* parent;
	};
	List start;
	std::vector<int> way;
	std::vector<List> closeList;
	std::vector<List> openList;
	std::vector<int> enemyPos;

	FindWay(int startpos);

	std::vector<int> FindWay::findWay(List& start, int end, std::vector<int> wall);
	
};