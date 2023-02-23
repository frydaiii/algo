#include <vector>
#include <iostream>
#include <algorithm>

int max_distance(std::vector<int> v, int t, int s, int c, int k, int l, int d) {
    int max_dis = 0;
    if (v.size() == t) {
        // return sum of v
        for (int speed: v) {
            max_dis += speed;
        }
        return max_dis;
    }
    max_dis = std::max(max_dis, max_distance(v, t, s, c, k, l, d));
    return max_distance;
}

int main() {
    int t, s, c, k, l, d, max_distance = 0, current_power;
    std::cin >> t >> s;
    std::cin >> c >> k >> l >> d;\
    current_power = c;
    for (int i = 0; i < t; ++i) {

    }
}