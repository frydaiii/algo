#include <iostream>
#include <math.h>
#include <vector>

long find_loser(std::vector<long> cookies) {
    unsigned long number_of_boxer = cookies.size();
    if (number_of_boxer % 2 == 0) {
        // find the smallest boxer with even cookies
        long min_even = 1000000001, loser = 0;
        for (unsigned long i = 0; i < number_of_boxer; ++i) {
            if (i % 2 == 0 && cookies[i] < min_even) {
                min_even = cookies[i];
                loser = i;
            }
        }
        return loser;
    } else {
        long min_odd = 1000000001, min_even = 1000000001, loser_even_cookies = 0, loser_odd_cookies = 0;
        // find the smallest boxer with even cookies
        for (unsigned long i = 0; i < number_of_boxer; ++i) {
            if (i % 2 == 0 && cookies[i] < min_even) {
                min_even = cookies[i];
                loser_even_cookies = i;
            }
        }
        // find the smallest boxer with odd cookies
        for (unsigned long i = 0; i < number_of_boxer; ++i) {
            if (i % 2 == 1 && cookies[i] < min_odd) {
                min_odd = cookies[i];
                loser_odd_cookies = i;
            }
        }

        if (min_even <= min_odd + 1) {
            return loser_even_cookies;
        }
        return loser_odd_cookies;
    }
}

int main() {
    long number_of_test_cases;
    std::cin >> number_of_test_cases;
    for (long i = 0; i < number_of_test_cases; ++i) {
        long number_of_boxer;
        std::cin >> number_of_boxer;
        std::vector<long> cookies;
        for (long j = 0; j < number_of_boxer; ++j) {
            long boxer_cookies;
            std::cin >> boxer_cookies;
            cookies.push_back(boxer_cookies);
        }
        std::cout << find_loser(cookies) << std::endl;
    }
}