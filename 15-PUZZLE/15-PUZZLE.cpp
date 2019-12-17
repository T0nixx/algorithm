// 15-PUZZLE.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int get_min_path(const vector<int>& initial, int starting_point) {
	vector<int> sorted = initial;
	sort(sorted.begin(), sorted.end());
	
	pair<vector<int>, int> start = make_pair(initial,starting_point);
	queue<pair<vector<int>, int>> q;
	map<vector<int>, int> distances;
	distances[start.first] = 0;
	q.push(start);
	int change[4] = {-4, -1, 1, 4};
	
	while (q.empty() == false) {
		pair<vector<int>,int> here = q.front();
		q.pop();

		if (here.first == sorted) return  here.second;
		int cost = distances[here.first];
		for (int i = 0; i < 4; i++) {
			int there_blank = here.second + change[i];
			if (there_blank < 0 || there_blank  > 15) continue;
			vector<int> there_puzzle = here.first;
			swap(there_puzzle[here.second], there_puzzle[there_blank]);
			if (distances.count(there_puzzle) == 0) {
				distances[there_puzzle] = cost + 1;
				q.push(make_pair(there_puzzle, there_blank));
			}
		}
	}

	return -1;
}

int sgn(int x) { if (x == 0) return 0; return x > 0 ? 1 : -1; }
int incr(int x) { if (x < 0) return x - 1; return x + 1; }

int bidirectional(const vector<int>& initial, int starting_point) {
	vector<int> sorted = initial;
	sort(sorted.begin(), sorted.end());

	if (initial == sorted) return 0;
	pair<vector<int>, int> start = make_pair(initial, starting_point);
	pair<vector<int>, int> finish = make_pair(sorted, 15);

	int change[4] = { -4, -1, 1, 4 };

	queue<pair<vector<int>, int>> q;
	map<vector<int>, int> distances;
	distances[start.first] = 1;
	distances[finish.first] = -1;
	q.push(start);
	q.push(finish);

	while (q.empty() == false) {
		pair<vector<int>, int> here = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int there_blank = here.second + change[i];
			if (there_blank < 0 || there_blank  > 15) continue;
			vector<int> there_puzzle = here.first;
			swap(there_puzzle[here.second], there_puzzle[there_blank]);
			map<vector<int>, int>::iterator it = distances.find(there_puzzle);
			if (it == distances.end()) {
				distances[there_puzzle] = incr(distances[here.first]);
				q.push(make_pair(there_puzzle, there_blank));
			}
			else if (sgn(it->second) != sgn(distances[here.first]))
				return abs(it->second) + abs(distances[here.first]) - 1;
		}
	}
	return -1;
}

int main()
{
	vector<int> initial_puzzle(16, 0);
	initial_puzzle[15] = 1;
	swap(initial_puzzle[0], initial_puzzle[15]);
	int initial_blank;

	for (int i = 0; i < 16; i++) { 
		int num;
		cin >> num;
		if (num == 16) initial_blank = i;
		initial_puzzle[i] = num;
	};
	
	int output = bidirectional(initial_puzzle, initial_blank);
	cout << output << endl;
	int output2 = get_min_path(initial_puzzle, initial_blank);
	cout << output2 << endl;

    return 0;
}

