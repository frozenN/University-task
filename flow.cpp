#include <bits/stdc++.h> 

using namespace std;

#define n 500

bool bfs(int s, int t, int parent[], int rg[n][n])
{
	bool vis[n];
	memset(vis, 0, sizeof vis);
	queue< int > q;
	q.push(s);
	vis[s] = true;
	parent[s] = -1;
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = 0; i < n; ++i)
		{
			if(!vis[i] && rg[x][i] > 0)
			{
				q.push(i);
				parent[i] = x;
				vis[i] = true;
			}
		}
	}
	return (vis[t] == true);
}

int fordFulkerson(int g[n][n], int s, int t)
{
	int rg[n][n];
	int x;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			rg[i][j] = g[i][j];
	int parent[n];
	int max_flow = 0;
	while(bfs(s, t, parent, rg))
	{
		int path_flow = 0x3f3f3f3f;
		for(int i = t; i != s; i = parent[i])
		{
			x = parent[i];
			path_flow = min(path_flow, rg[x][i]);
		}
		for(int i = t; i != s; i = parent[i])
		{
			x = parent[i];
			rg[x][i] -= path_flow;
			rg[i][x] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

int main(){
	//freopen("tc", "r", stdin);

    int graph[n][n];
	int N, M, ct, soc;
	map< string, int > mym;

	mym["XXL"] =  1;
	mym["XL"]  =  2;
	mym["L"]   =  3;
	mym["M"]   =  4;
	mym["S"]   =  5;
	mym["XS"]  =  6;

	cin >> ct;

	while(ct--)
	{
		cin >> N >> M;
		memset(graph, 0, sizeof graph);
		soc = N / 6;

		for(int i = 1; i <= 6; ++i)
		{
			graph[0][i] = soc;
		}


		for(int i = 1; i <= M; ++i)
		{
			string a, b;
			cin >> a >> b;

			graph[ mym[a] ][6 + i  ] = 1;
			graph[ 6+i    ][ mym[a]] = 1;
			graph[ 6+i    ][ mym[b]] = 1;
			graph[ mym[b] ][6 + i  ] = 1;
			graph[ 6 + i  ][M + 7  ] = 1;
			graph[ M + 7  ][  6 + 1] = 1;
		}
		int ans = fordFulkerson(graph, 0, M+7);
	//	cout << ans << endl;
		if(ans == M )
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}	