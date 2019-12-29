//출처: 프로그래머스 코딩 테스트 연습,
// https://programmers.co.kr/learn/challenges

#include <set>
#include <string>
#include <vector>

using namespace std;

vector<int> arr[9];
bool can_mul_10(int num, int N) {
    while (num > 0) {
        if (num % 10 != N) return false;
        num /= 10;
    }
    return true;
}

int solution(int N, int number) {
    if (N == number) return 1;
    vector<set<int>> numbers_for_i(9);
    numbers_for_i[1].insert(N);
    set<int> numbers;

    numbers.insert(N);

    int i;
    for (int i = 2; i < 9; i++) {
        set<int> to_puts;
        for (int j = 1; j <= i / 2; j++) {
            for (set<int>::iterator iter_i = numbers_for_i[i - j].begin();
                 iter_i != numbers_for_i[i - j].end(); iter_i++) {
                for (set<int>::iterator iter_j = numbers_for_i[j].begin();
                     iter_j != numbers_for_i[j].end(); iter_j++) {
                    int add = *iter_i + (*iter_j);
                    int sub = *iter_i - (*iter_j);
                    int mul = *iter_i * (*iter_j);
                    int quo = *iter_i / (*iter_j);

                    if (add == number || sub == number || mul == number ||
                        quo == number)
                        return i;
                    if (add != 0) to_puts.insert(add);
                    if (sub != 0) to_puts.insert(sub);
                    if (mul != 0) to_puts.insert(mul);
                    if (quo != 0) to_puts.insert(quo);
                    if (can_mul_10(*iter_i, *iter_j) == true) {
                        int mul10 = *iter_i * 10 + *iter_j;
                        if (mul10 == number) return i;
                        to_puts.insert(mul10);
                    }
                }
            }
        }
        numbers_for_i[i].insert(to_puts.begin(), to_puts.end());
        // numbers = to_puts;
    }
    return -1;
}