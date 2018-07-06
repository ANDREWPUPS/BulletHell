#include "FindWay.h"
#include <algorithm>
#include "Enemy.h"
#include <iostream>
FindWay::FindWay(int startpos)
{
	start.position = startpos;
	start.isStart = true;
	closeList.clear();
	way.clear();
	openList.clear();
}

std::vector<int> FindWay::findWay(List& start, int end, std::vector<int> wall)
{
	closeList.push_back(start);
	if (start.position == end)
	{
		way.push_back(end);
		return way;
	}

	
	int buf[8] = { start.position - 201, start.position - 200, start.position - 199, start.position - 1, start.position + 1, start.position + 199, start.position + 200, start.position + 201 };

	for (int i = 0; i < 8; i++)
	{
		List openListBuf;

		int x = buf[i];
		openListBuf.parent = &start;
		auto findBuf = std::find_if(openList.begin(), openList.end(), [&x](List s){return s.position == x; });
		if (findBuf != openList.end())
		{
			int point_to_startBuf;
			int allBuf;
			if (abs(buf[i] - start.position) == 209 || abs(buf[i] - start.position) == 201)
				point_to_startBuf = start.point_to_start + 14;
			else
				point_to_startBuf = start.point_to_start + 10;

			allBuf = point_to_startBuf + openList[findBuf - openList.begin()].point_to_end;

			if (allBuf < openList[findBuf - openList.begin()].all_points)
			{
				openList[findBuf - openList.begin()].point_to_start = point_to_startBuf;
				openList[findBuf - openList.begin()].all_points = openList[findBuf - openList.begin()].point_to_start + openList[findBuf - openList.begin()].point_to_end;
				openList[findBuf - openList.begin()].parent = &start;
			}
		}

		else  if (std::find(wall.begin(), wall.end(), buf[i]) == wall.end() && std::find_if(closeList.begin(), closeList.end(), [&x](List s){return s.position == x; }) == closeList.end())
		{
			if (std::find(wall.begin(), wall.end(), buf[i] % 200 + (start.position / 200) * 200) == wall.end() && std::find(wall.begin(), wall.end(), start.position % 200 + (buf[i] / 200) * 200) == wall.end())
			{
				openListBuf.position = buf[i];
				openListBuf.point_to_end = (abs(buf[i] % 200 - end % 200) + abs(buf[i] / 200 - end / 200)) * 200;

				if (abs(buf[i] - start.position) == 199 || abs(buf[i] - start.position) == 201)
					openListBuf.point_to_start = openListBuf.parent->point_to_start + 14;
				else
					openListBuf.point_to_start = openListBuf.parent->point_to_start + 14;

				openListBuf.all_points = openListBuf.point_to_start + openListBuf.point_to_end;
				if (openListBuf.position == end)
				{
					closeList.push_back(openListBuf);
					List* buf = &closeList[closeList.size() - 1];
					while (buf->isStart != true) {
						way.push_back(buf->position);
						buf = buf->parent;
					}
					return way;
				}

				openList.push_back(openListBuf);
			}
		}
	}

	auto min = std::min_element(openList.begin(), openList.end(), [](List a, List b){return a.all_points < b.all_points; });
	
	List returnBuf = openList[min - openList.begin()];
	openList.erase(min);

	findWay(returnBuf, end, wall);

	return way;
}
