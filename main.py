import random
import typing
TIME_LIMIT = 0.9
INF = 10**9
class Planet:
	def __init__(self, a, b, idx, is_station = False, frm = -1, nxt = -1) -> None:
		self.x = a
		self.y = b
		self.idx = idx
		self.is_station = is_station
		self.frm = frm
		self.nxt = nxt
	def copy(self):
		return Planet(self.x, self.y, self.idx, self.is_station, self.frm, self.nxt)
	
	def __str__(self) -> str:
		return " ".join(["1" if not self.is_station else "2", str(self.idx + 1)])

N:int = 100
M:int = 8
planet:typing.List[Planet] = []
station:typing.List[Planet] = []

A = 5

ans:typing.List[Planet] = []

def input_problem():
	global N, M, planet
	N, M = map(int,input().split())
	for i in range(N):
		a, b = map(int,input().split())
		planet.append(Planet(a, b, i))

def output_station():
	for s in station:
		print(s.x, s.y)

def output_route():
	print(len(ans))
	for v in ans:
		print(v)

def station_init():
	global station
	station.append(Planet(250, 250, 0, True))
	station.append(Planet(250, 500, 1, True))
	station.append(Planet(250, 750, 2, True))
	station.append(Planet(500, 250, 3, True))
	station.append(Planet(500, 750, 4, True))
	station.append(Planet(750, 250, 5, True))
	station.append(Planet(750, 500, 6, True))
	station.append(Planet(750, 750, 7, True))

def Dist(planet_A:Planet, planet_B:Planet, station_cnt:int = -1) -> int:
	if station_cnt == -1:
		station_cnt = 1 if planet_A.is_station else 0 + 1 if planet_B.is_station else 0

	dist:int = (
		(planet_A.x-planet_B.x)**2 + (planet_A.y - planet_B.y)**2
		)*(A**(2-station_cnt))
	return dist

def calc_distance() -> typing.List[typing.List[int]]:
	distance:typing.List[typing.List[int]] = [[INF]*(N+M) for _ in range(N+M)]
	for i in range(N+M):
		for j in range(N+M):
			station_cnt = 0
			if i == j:
				distance[i][j] = 0
			planet_A:Planet
			planet_B:Planet
			if i >= N:
				planet_A = station[i - N]
				station_cnt += 1
			else:
				planet_A = planet[i]

			if j >= N:
				planet_B = station[j - N]
				station_cnt += 1
			else:
				planet_B = planet[j]

			distance[i][j] = Dist(planet_A, planet_B, station_cnt)
	return distance


def FloydWarshall(d:typing.List[typing.List[int]]) -> typing.List[typing.List[int]]:
    """破壊的処理"""
    n = len(d)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if d[i][k] == INF or d[k][j] == INF:
                    continue
                d[i][j] = min(d[i][j], d[i][k] + d[k][j])
    # if any(d[i][i] < 0 for i in range(n)): # 負の閉路があるなら0を返す.
    #     return 0
    return d

def dijkstra():
	dikstra:int

def calc_score() -> int:
	score:int = 0
	frm_planet = planet[0]
	for to_planet in ans:
		score += Dist(frm_planet, to_planet)
		frm_planet = to_planet.copy()

	return score

def random_shufle():
	global ans
	best_score = calc_score()
	for _ in range(5_000):
		a:int = 0
		b:int = 0
		while a == b:
			a = random.randrange(0, len(ans))
			b = random.randrange(0, len(ans))

		ans[a], ans[b] = ans[b], ans[a]
		now_score = calc_score()
		if now_score >= best_score:
			ans[a], ans[b] = ans[b], ans[a]
		else:
			best_score = now_score

def solve():
	global ans
	station_init()
	# distance = FloydWarshall(calc_distance())
	ans.extend(planet[1:])
	for _ in range(5):
		ans.extend(station)
	random_shufle()
	ans = [planet[0]]+ans + [planet[0]]

if __name__ == "__main__":
	input_problem()

	solve()

	output_station()
	output_route()
