#include "MazeAlgorithms.hpp"


// -----------------------------BFS IMPLEMENTATIONS-----------------------------


// -----------------------------DFS IMPLEMENTATIONS-----------------------------



// -----------------------------DIJKSTRA IMPLEMENTATIONS------------------------


// -----------------------------A-STAR IMPLEMENTATIONS--------------------------

int AStar::calcH(shared_ptr<Room> room, shared_ptr<Room> end)
{
	return abs(room->roomPos.getX() - end->roomPos.getX()) + abs(room->roomPos.getY() - end->roomPos.getY());
}

vector<shared_ptr<Room>> AStar::findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option)
{
	int max_size = 50;
	int inf = max_size * max_size + 1;
	vector < vector < int > > F(max_size, vector < int >(max_size, inf));
	vector < vector < int > > G(max_size, vector < int >(max_size, inf));
	vector < vector < shared_ptr<Room> > > Par(max_size, vector < shared_ptr<Room> >(max_size, nullptr));
	vector < shared_ptr<Room> > result;

	priority_queue<pair<int, shared_ptr<Room>>, vector<pair<int, shared_ptr<Room>>>, greater<pair<int, shared_ptr<Room>>> > pq;

	F[start->roomPos.getX()][start->roomPos.getY()] = 0;
	G[start->roomPos.getX()][start->roomPos.getY()] = 0;


	pq.push({ 0, start });

	while (pq.size())
	{
		auto t = pq.top();
		pq.pop();

		int curF = t.first;
		shared_ptr<Room> u = t.second;

		int uX = u->roomPos.getX();
		int uY = u->roomPos.getY();

		if (F[uX][uY] < curF) continue;

		if (option) result.push_back(u);

		for (auto v : u->adjRooms)
		{
			if (u->checkConnectRoom(v))
			{
				int vX = v->roomPos.getX();
				int vY = v->roomPos.getY();

				int vG = G[uX][uY] + 1;
				int vH = calcH(v, end);

				if (F[vX][vY] > vG + vH)
				{
					F[vX][vY] = vG + vH;
					G[vX][vY] = vG;
					Par[vX][vY] = u;
					pq.push({ F[vX][vY], v });
				}
			}
		}
	}

	//Trace
	if (!option && G[end->roomPos.getX()][end->roomPos.getY()] != inf)
	{
		shared_ptr<Room> cur = end;
		do {
			result.push_back(cur);
			cur = Par[cur->roomPos.getX()][cur->roomPos.getY()];
		} while (cur);

		reverse(result.begin(), result.end());
	}

	return result;
}
