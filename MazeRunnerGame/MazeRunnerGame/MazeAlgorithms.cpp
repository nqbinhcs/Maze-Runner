#include "MazeAlgorithms.hpp"


// -----------------------------BFS IMPLEMENTATIONS-----------------------------

vector<shared_ptr<Room>> BFS::findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option)
{
	if (start == end)
	{
		return vector<shared_ptr<Room>>(1, start);
	}

	vector < vector< shared_ptr<Room> > > preRoom(MAX_SIZE, vector< shared_ptr<Room> >(MAX_SIZE, 0));
	vector< shared_ptr<Room> > trace;
	queue< shared_ptr<Room> > qu;

	qu.push(start);
	preRoom[start->roomPos.getX()][start->roomPos.getY()] = start;
	
	while (!qu.empty())
	{
		auto u = qu.front();
		auto uPos = u->roomPos;

		qu.pop();

		if (u == end)
			return;

		for (auto v : u->adjRooms)
		{
			auto vPos = v->roomPos;
			
			if (!preRoom[vPos.getX()][vPos.getY()])
			{
				preRoom[vPos.getX()][vPos.getY()] = u;
				qu.push(v);
			}
		}
	}

	int endX = end->roomPos.getX();
	int endY = end->roomPos.getY();
	auto curEnd = end;

	while (preRoom[endX][endY] && preRoom[endX][endY] != start)
	{
		trace.push_back(curEnd);
		curEnd = preRoom[endX][endY];
		endX = curEnd->roomPos.getX();
		endY = curEnd->roomPos.getY();
	}

	if (!trace.empty())
	{
		trace.push_back(start);
		reverse(trace.begin(), trace.end());
	}

	return trace;
}

// -----------------------------DFS IMPLEMENTATIONS-----------------------------

vector<shared_ptr<Room>> DFS::findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option)
{
	if (start == end)
	{
		return vector<shared_ptr<Room>>(1, start);
	}

	vector< shared_ptr<Room> > trace;
	vector< shared_ptr<Room> > roomStack;
	vector< vector < bool > > visited(MAX_SIZE, vector < bool >(MAX_SIZE, 0));
	shared_ptr<Room> dest = end;
	bool found = false;

	roomStack.push_back(start);
	visited[start->roomPos.getX()][start->roomPos.getY()] = true;

	while (!roomStack.empty())
	{
		auto u = roomStack.back();
		auto uPos = u->roomPos;

		roomStack.pop_back();

		if (found)
		{
			if (dest->checkConnectRoom(u))
			{
				trace.push_back(u);
				u = dest;
			}
			continue;
		}

		for (auto v : u->adjRooms)
		{
			auto vPos = v->roomPos;

			if (v == dest) 
			{
				found = true;
				break;
			}

			if (!visited[vPos.getX()][vPos.getY()])
			{
				roomStack.push_back(v);
				visited[vPos.getX()][vPos.getY()] = true;
			}
		}
	}

	if (!trace.empty())
	{
		reverse(trace.begin(), trace.end());
		trace.push_back(end);
	}

	return trace;
}

// -----------------------------DIJKSTRA IMPLEMENTATIONS------------------------

vector<shared_ptr<Room>> Dijkstra::findPath(shared_ptr<Room> start, shared_ptr<Room> end, bool option)
{
	if (start == end)
	{
		return vector<shared_ptr<Room>>(1, start);
	}

	const int inf = MAX_SIZE * MAX_SIZE + 1;
	vector< vector< int > > dist(MAX_SIZE, vector< int >(MAX_SIZE, inf));
	vector < vector< shared_ptr<Room> > >preRoom(MAX_SIZE, vector< shared_ptr<Room> >(MAX_SIZE, 0));
	vector< shared_ptr<Room> > trace;

	priority_queue<pair<int, shared_ptr<Room>>, vector<pair<int, shared_ptr<Room>>>, greater<pair<int, shared_ptr<Room>>> > pq;

	dist[start->roomPos.getX()][start->roomPos.getY()] = 0;
	preRoom[start->roomPos.getX()][start->roomPos.getY()] = start;
	pq.push({ 0, start });

	while (!pq.empty())
	{
		int curDist = pq.top().first;
		auto u = pq.top().second;
		auto uPos = u->roomPos;

		pq.pop();

		if (dist[uPos.getX()][uPos.getY()] != curDist)
			continue;

		for (auto v : u->adjRooms)
		{
			auto vPos = v->roomPos;

			if (dist[vPos.getX()][vPos.getY()] > curDist + 1)
			{
				dist[vPos.getX()][vPos.getY()] = curDist + 1;
				preRoom[vPos.getX()][vPos.getY()] = u;
				pq.push({ curDist + 1 , v });
			}
		}
	}

	int endX = end->roomPos.getX();
	int endY = end->roomPos.getY();
	auto curEnd = end;

	while (preRoom[endX][endY] && preRoom[endX][endY] != start)
	{
		trace.push_back(curEnd);
		curEnd = preRoom[endX][endY];
		endX = curEnd->roomPos.getX();
		endY = curEnd->roomPos.getY();
	}

	if (!trace.empty())
	{
		trace.push_back(start);
		reverse(trace.begin(), trace.end());
	}

	return trace;
}

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