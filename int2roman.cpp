#include <string>

using namespace std;

#include <map>



class Solution {
public:
    string intToRoman(int num) {
        map<int, string> roman;
        roman[1] = "I";
        roman[4] = "IV";
        roman[5] = "V";
        roman[9] = "IX";
        roman[10] = "X";
        roman[40] = "XL";
        roman[50] = "L";
        roman[90] = "XC";
        roman[100] = "C";
        roman[400] = "CD";
        roman[500] = "D";
        roman[900] = "CM";
        roman[1000] = "M";

        string result;
        map<int, string>::reverse_iterator it;
        while (num > 0) {
            it = roman.rbegin();
            while (it != roman.rend()) {
                if (num >= it->first) {
                    result += it->second;
                    num -= it->first;
                    break;
                } else {
                    it++;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    int num = 1994;
    string result = s.intToRoman(num);
    printf("%s\n", result);
    return 0;
}
