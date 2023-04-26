#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const long double EPS = 1e-10;
const long long INF = 1e18;
const long double PI = acos(-1.0L);

const double TIME_LIMIT = 900;

struct TimeKeeper
{
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    int64_t time_threshold_;

public:
    // 時間制限をミリ秒単位で指定してインスタンスをつくる。
    TimeKeeper(const int64_t &time_threshold)
        : start_time_(std::chrono::high_resolution_clock::now()), time_threshold_(time_threshold) {}

    // インスタンス生成した時から指定した時間制限を超過したか判断する。
    bool isTimeOver() const
    {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() >= time_threshold_;
    }

    // 経過時間をミリ秒単位で返す
    int64_t Time() const
    {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
};

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

int N, M;
vector<Planet> planet;
vector<Planet> station;

const int A = 5;
/*Target to minimize */
ll energy = 0;

vector<pair<int, int>> ans;

vector<vector<ll>> FloydWarshall(vector<vector<ll>>& distances)
{
	const size_t v = distances.size();

	for (size_t i = 0; i < v; ++i)
	{
		for (size_t frm = 0; frm < v; ++frm)
		{
			for (size_t to = 0; to < v; ++to)
			{
				if ((distances[frm][i] < INF) && (distances[i][to] < INF))
				{
					distances[frm][to] = min(distances[frm][to], (distances[frm][i] + distances[i][to]));
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
        planet.push_back(Planet(a, b, i + 1));
    }
    return;
}

void OutputStation() {
    for(int i = 0; i < M; i++) {
        cout << station[i].a << " " << station[i].b << endl;
    }
    return;
}

void OutputWayPoint(pair<int, int> wayPoint) { cout << wayPoint.first << " " << wayPoint.second+1 << endl; }

void OutputRoute() {
    int V = (int)ans.size();
    cout << V << endl;

    for(int i = 0; i < V; i++) {
        OutputWayPoint(ans[i]);
    }

    return;
}

ll Distance(Planet pa, Planet pb)
{
	ll a = (pa.a - pb.a);
	ll b = (pa.b - pb.b);
	return a*a + b*b;
}

void Pick(int &a, int &b)
{
	while(true)
	{
		a = rand()%(ans.size() - 1);
		b = rand()%(ans.size() - 1);
		if(a > b) swap(a, b);
		if (a+1 == b || b == ans.size()-2)
		{
			continue;
		}
		return;
	}
}

void EdgeSwap(int a, int b)
{
	a++;
	while(a < b)
	{
		swap(ans[a], ans[b]);
		a++;
		b--;
	}
}

void TwoOpt(vector<vector<ll>> distances, TimeKeeper t)
{
	while (!t.isTimeOver())
	{
		int a, b;
		Pick(a, b);
		int na, nb;
		na = (a+1)%(ans.size() - 1);
		nb = (b+1)%(ans.size() - 1);
		Planet Pa = (ans[a].first == 1) ? planet[ans[a].second] : station[ans[a].second];
		Planet Pb = (ans[b].first == 1) ? planet[ans[b].second] : station[ans[b].second];
		Planet Pna = (ans[na].first == 1) ? planet[ans[na].second] : station[ans[na].second];
		Planet Pnb = (ans[nb].first == 1) ? planet[ans[nb].second] : station[ans[nb].second];

		ll beforeDist = Distance(Pa, Pna) + Distance(Pb, Pnb);
		ll afterDist = Distance(Pa, Pb) + Distance(Pna, Pnb);
		if (beforeDist > afterDist)
		{
			EdgeSwap(a, b);
		}
	}
}

void solve(TimeKeeper t) {
    for(int i = 1; i < M + 1; i++) {
        station.push_back(Planet(rand()%1000, rand()%1000, i));
    }

	vector<vector<ll>> distances(N, vector(N, INF));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			distances[i][j] = Distance(planet[i], planet[j]);
		}
	}
	FloydWarshall(distances);

	set<int> bef;
	int frmIdx = 0;
	ans.push_back(pair<int, int>(1, 0));
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

		ans.push_back(pair<int, int>(1, nxtIdx));
		frmIdx = nxtIdx;
	}
	ans.push_back(pair<int, int>(1, 0));

	TwoOpt(distances, t);

    return;
}

int main() {
	auto t = TimeKeeper(TIME_LIMIT);
	srand(time(NULL));
    Input();

    solve(t);

    OutputStation();
    OutputRoute();

    return 0;
}