#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<int, int> get_adjacent_houses(int x, int size) {
    if (x == 0) return make_pair(size - 1, 1);
    if (x == size - 1) return make_pair(size - 2, 0);
    return make_pair(x - 1, x + 1);
}

int cache[3][1000000];

int get_max_money(vector<int>& money, int house, vector<bool>& taken,
                  int first) {
    if (house >= money.size() || taken[house] == true) return 0;
    pair<int, int> left_right = get_adjacent_houses(house, money.size());
    int left = left_right.first;
    int right = left_right.second;
    int& ret = cache[first][house];
    if (ret != -1) return ret;
    taken[left] = true;
    taken[house] = true;
    taken[right] = true;
    ret = 0;

    ret = max(ret, get_max_money(money, house + 2, taken, first));
    ret = max(ret, get_max_money(money, house + 3, taken, first));
    taken[left] = false;
    taken[house] = false;
    if (first != 0 || right != money.size() - 1) taken[right] = false;

    return ret = ret + money[house];
}

int suck_solution(vector<int> money) {
    int answer = 0;
    memset(cache, -1, sizeof(cache));

    vector<bool> taken(money.size(), false);
    int a0 = get_max_money(money, 0, taken, 0);
    int a1 = get_max_money(money, 1, taken, 1);
    int a2 = money[2];
    a2 += cache[1][4] + cache[1][5] != -2 ? max(cache[1][4], cache[1][5]) : 0;

    answer = max(a0, a1);
    answer = max(answer, a2);
    return answer;
}

int arr1[1000000];
int arr2[1000000];

int solution(vector<int> money) {
    int size = money.size();

    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));

    for (int i = 0; i < size - 1; i++) {
        arr1[i] = money[i] + (i >= 2 ? arr1[i - 2] : 0);
        if (i >= 1) arr1[i] = max(arr1[i], arr1[i - 1]);
    }

    for (int i = 1; i < size; i++) {
        arr2[i] = money[i] + (i >= 2 ? arr2[i - 2] : 0);
        if (i >= 1) arr2[i] = max(arr2[i], arr2[i - 1]);
    }

    return max(arr1[size - 2], arr2[size - 1]);
}

int main() {
    // vector<vector<int>> tri = { {2,2} };
    // vector<int> money = { 1,2,3,1,2,3,1,2 };
    vector<int> money = {1, 3, 2, 4, 5, 6, 10};

    cout << solution(money) << endl;
    return 0;
}
