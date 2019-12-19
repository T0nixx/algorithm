#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned long long ULL;

ULL add_disk(ULL pole, int new_disk) {
    pole = pole << 4;
    pole |= (ULL)new_disk;
    return pole;
}
ULL add_disk(ULL pole, ULL new_disk) {
    pole = pole << 4;
    pole |= new_disk;
    return pole;
}

class State {
   public:
    vector<ULL> poles;
    bool operator<(const State& rhs) const {
        for (int i = 0; i < poles.size(); i++) {
            if (poles[i] != rhs.poles[i]) return poles[i] > rhs.poles[i];
        }
        return false;
    };
    bool operator==(const State& rhs) const {
        for (int i = 0; i < poles.size(); i++) {
            if (poles[i] != rhs.poles[i]) return false;
        }
        return true;
    };

    vector<State> get_possible_next_states() {
        vector<State> ret;
        ULL ander = (ULL)15;
        for (int i = 0; i < poles.size(); i++) {
            if (poles[i] == (ULL)0) continue;
            ULL moving_disk = (poles[i] & ander);
            for (int j = 0; j < poles.size(); j++) {
                // i == j 일때를 함께 거르기 위해 <=
                ULL top_disk = (poles[j] & ander);
                if (top_disk != 0 && top_disk <= moving_disk) continue;

                ULL changed_pole = poles[j];
                changed_pole = add_disk(changed_pole, moving_disk);

                vector<ULL> changed_poles = poles;

                changed_poles[j] = changed_pole;
                // 옮겨간 기둥의 원반 빼주기
                changed_poles[i] = poles[i] >> 4;

                ret.push_back(State(changed_poles));
            }
        }
        return ret;
    };

    State(vector<ULL>& _poles) { poles = _poles; };
    State(){};
};
int incr(int x) { return x < 0 ? x - 1 : x + 1; }
int sgn(int x) {
    if (x == 0) return x;
    return x < 0 ? -1 : 1;
}

int get_min_move(State initial, State last) {
    if (initial == last) return 0;
    map<State, int> cost;
    cost[initial] = 1;
    cost[last] = -1;
    queue<State> q;
    q.push(initial);
    q.push(last);

    while (q.empty() == false) {
        State here = q.front();
        q.pop();
        vector<State> next_states = here.get_possible_next_states();
        for (int i = 0; i < next_states.size(); i++) {
            map<State, int>::iterator it = cost.find(next_states[i]);
            if (it == cost.end()) {
                cost[next_states[i]] = incr(cost[here]);
                q.push(next_states[i]);
            } else if (sgn(it->second) != sgn(cost[here]))
                return abs(it->second) + abs(cost[here]) - 1;
        }
    }
    return -1;
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<int> outputs;

    while (current_case++ < case_count) {
        int N;
        cin >> N;
        vector<ULL> initial_poles(4, (ULL)0);
        for (int i = 0; i < 4; i++) {
            int disk_count;
            cin >> disk_count;
            for (int j = 0; j < disk_count; j++) {
                int disk;
                cin >> disk;
                initial_poles[i] = add_disk(initial_poles[i], disk);
            }
        }
        State initial(initial_poles);
        vector<ULL> last(4, 0);
        for (int i = N; i > 0; i--) last[3] = add_disk(last[3], i);

        outputs.push_back(get_min_move(initial, last));
        continue;
    }

    for (int output : outputs) cout << output << '\n';
    return 0;
}

// 시간초과가 났다. 상태를 표현할 더 효율적인 방법이 필요했다.