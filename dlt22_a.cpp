#include <vector>
#include <iostream>
#include <algorithm>

int circumference(std::vector<int> edges) {
    unsigned int number_of_edges = edges.size();
    if (number_of_edges  < 3) {
        return 0;
    }
    // sort the edges
    std::sort(edges.begin(), edges.end());
    // counting sum of i edges, sum_edges[i] = sum of edges[0] to edges[i]
    std::vector<int> sum_edges(number_of_edges);
    sum_edges[0] = edges[0];
    for (unsigned int i = 1; i < number_of_edges; ++i) {
        sum_edges[i] = sum_edges[i - 1] + edges[i];
    }
    // counting the maxium circumference
    for (unsigned int i = number_of_edges - 1; i >= 2; --i) {
        if (edges[i] < sum_edges[i - 1]) {
            return sum_edges[i];
        }
    }
    return 0;
}

int main() {
    int number_of_test_cases;
    std::cin >> number_of_test_cases;
    for (int i = 0; i < number_of_test_cases; ++i) {
        int number_of_edges;
        std::cin >> number_of_edges;
        std::vector<int> edges;
        for (int j = 0; j < number_of_edges; ++j) {
            int edge;
            std::cin >> edge;
            edges.push_back(edge);
        }
        std::cout << circumference(edges) << std::endl;
    }
}