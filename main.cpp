#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const long double EPS = 1e-10;
const long long INF = 1e18;
const long double PI = acos(-1.0L);

const double TIME_LIMIT = 0.95;

struct Planet {
    int a;
    int b;
    int idx;
    Planet(int _a, int _b, int _idx) {
        a = _a;
        b = _b;
        idx = _idx;
    }
    Planet(const Planet &old) {
        a = old.a;
        b = old.b;
        idx = old.idx;
    }
};

struct Station {
    int a;
    int b;
    int idx;
    Station(int _a, int _b, int _idx) {
        a = _a;
        b = _b;
        idx = _idx;
    }
    Station(const Station &old) {
        a = old.a;
        b = old.b;
        idx = old.idx;
    }
};

int N, M;
vector<Planet> planet;
vector<Station> station;

const int A = 5;
/*Target to minimize */
ll energy = 0;
Planet startPlanet(0,0,0);

vector<pair<int, int>> ans;
vector<vector<ll>> FloydWarshall(vector<vector<ll>>& distances)
{
	const size_t v = distances.size();

	for (size_t i = 0; i < v; ++i)
	{
		for (size_t from = 0; from < v; ++from)
		{
			for (size_t to = 0; to < v; ++to)
			{
				if ((distances[from][i] < INF) && (distances[i][to] < INF))
				{
					distances[from][to] = min(distances[from][to], (distances[from][i] + distances[i][to]));
				}
			}
		}
	}

	return distances;
}

void Input() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        Planet p(a, b, i + 1);
        planet.push_back(p);
    }
    return;
}

void OutputStation() {
    for(int i = 0; i < M; i++) {
        cout << station[i].a << " " << station[i].b << endl;
    }
    return;
}

void OutputWayPoint(pair<int, int> wayPoint) { cout << wayPoint.first << " " << wayPoint.second << endl; }

void OutputRoute() {
    int V = ans.size();
    cout << V << endl;

    for(int i = 0; i < V; i++) {
        OutputWayPoint(ans[i]);
    }

    return;
}



void solve() {
    for(int i = 1; i < M + 1; i++) {
        Station s(0, 0, i);
        station.push_back(s);
    }

	vector<vector<ll>> distances(N, vector(N, INF));
	startPlanet = planet[0];
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			ll a, b;
			a = planet[i].a - planet[j].a;
			b = planet[i].b - planet[j].b;
			distances[i][j] = a*a + b*b;
		}
	}
	FloydWarshall(distances);

	set<int> bef;
	int frmIdx = 0;
	ans.push_back(pair<int, int>(1, 1));
	for(int i = 0; i < N; i++)
	{
		ll minDist = INF;
		int nxtIdx;
		bef.insert(frmIdx + 1);


		for(int toIdx = 0; toIdx < N; toIdx++)
		{
			if(bef.find(toIdx+1) != bef.end())
			{
				continue;
			}
			if(minDist > distances[frmIdx][toIdx])
			{
				minDist = distances[frmIdx][toIdx];
				nxtIdx = toIdx;
			}
		}
		ans.push_back(pair<int, int>(1, nxtIdx+1));
		frmIdx = nxtIdx;
	}
	ans.push_back(pair<int, int>(1, 1));

    return;
}

int main() {
    Input();

    solve();

    OutputStation();
    OutputRoute();

    return 0;
}