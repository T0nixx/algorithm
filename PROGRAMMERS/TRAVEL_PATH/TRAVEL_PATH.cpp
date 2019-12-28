//출처: 프로그래머스 코딩 테스트 연습,
//https://programmers.co.kr/learn/challenges

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
vector<int> orders;
void dfs(int index, vector<bool>& used, vector<string>& airports,
         vector<vector<string>>& tickets) {
    used[index] = true;
    airports.push_back(tickets[index][1]);

    for (int i = 0; i < tickets.size(); i++) {
        if (used[i] == false && tickets[i][0] == airports.back()) {
            dfs(i, used, airports, tickets);
            airports.pop_back();
        }
    }
    orders.push_back(index);
}

vector<string> solution(vector<vector<string>> tickets) {
    sort(tickets.begin(), tickets.end(),
         [&](vector<string>& a, vector<string>& b) { return a[1] < b[1]; });

    vector<int> firsts;
    int ticket_count = tickets.size();
    for (int i = 0; i < ticket_count; i++) {
        if (tickets[i][0] == "ICN") {
            firsts.push_back(i);
        }
    }

    for (int i = 0; i < firsts.size(); i++) {
        orders = vector<int>();
        int first = firsts[i];
        vector<bool> used(ticket_count, false);
        used[first] = true;
        vector<string> airports;
        airports.push_back("ICN");

        dfs(first, used, airports, tickets);
        if (orders.size() == tickets.size()) break;
    }
    reverse(orders.begin(), orders.end());
    vector<string> answer;
    answer.push_back("ICN");
    for (int i = 0; i < orders.size(); i++) {
        answer.push_back(tickets[orders[i]][1]);
    }
    return answer;
}
