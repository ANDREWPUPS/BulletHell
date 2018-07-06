#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Map
{
public:
	
	int field[100];
	int  end;
	std::vector<int> wall;
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
	List* bufend;
	std::vector<int> way;
	std::vector<List> closeList;
	std::vector<List> openList;
	Map ()
	{
		std::ifstream map("mapFindWayTest.txt");

		for (int i = 0; i < 100; i++)
		{
			char c;
			map >> c;
			field[i] = c - '0';
			if (field[i] == 1)
			{
				start.position = i;
				start.point_to_end = 0;
				start.point_to_start = 0;
				start.isStart = true;
			}
			if (field[i] == 3)
				end = i;
			if (field[i] == 2)
				wall.push_back(i);
		}
	}
	
	std::vector<int> FindWay(List& start)
	{
		
		closeList.push_back(start);
		int buf[8] = { start.position - 11, start.position - 10, start.position - 9, start.position - 1, start.position + 1, start.position + 9, start.position + 10, start.position + 11 };

		for (int i = 0; i < 8; i++)
		{
			List openListBuf;
			
			int x = buf[i];
			openListBuf.parent = &start;
			auto findBuf = std::find_if(openList.begin(), openList.end(), [&x](List s){return s.position == x; });
				if (findBuf!= openList.end())
			{
				int point_to_startBuf;
				int allBuf;
				if (abs(buf[i] - start.position) == 9 || abs(buf[i] - start.position) == 11)
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
				if (std::find(wall.begin(), wall.end(), buf[i] % 10 + (start.position / 10) * 10) == wall.end() && std::find(wall.begin(), wall.end(), start.position % 10 + (buf[i] / 10) * 10) == wall.end())
				{
					openListBuf.position = buf[i];
					openListBuf.point_to_end = (abs(buf[i] % 10 - end % 10) + abs(buf[i] / 10 - end / 10)) * 10;



					if (abs(buf[i] - start.position) == 9 || abs(buf[i] - start.position) == 11)
						openListBuf.point_to_start = openListBuf.parent->point_to_start + 14;
					else
						openListBuf.point_to_start = openListBuf.parent->point_to_start + 10;

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

		auto min = std::min_element(openList.begin(), openList.end(), [](List a, List b){return a.all_points< b.all_points; });
		
		List returnBuf = openList[min - openList.begin()];
		openList.erase(min);
		
			FindWay(returnBuf);

		return way;

	}




};





int mainaaaaaaaaaaaaa()
{
	Map map;
	
	
	map.FindWay(map.start);
	for (int i = 0; i < map.way.size(); i++)
		std::cout << map.way[i] << " ";

	std::cout << "\n";
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	for (int y = 0; y < 10; y++)
	{
		
		for (int x = 0; x < 10; x++)
		{
			std::cout << map.field[y * 10 + x] << ' ';
		}
		std::cout << "\n";
	}

	int a;
	std::cin >> a;
		return 0;
}