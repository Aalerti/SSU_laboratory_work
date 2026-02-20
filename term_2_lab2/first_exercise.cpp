
#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums;

    int x;
    while (std::cin >> x) {
        nums.push_back(x);
    }

    if (nums.empty()) {
        std::cout << "Vector is empty\n";
        return 1;
    }

    std::map<char, bool> ans;

    for (size_t i = 0; i < nums.size(); i++) {
        std::string curr = std::to_string(nums[i]);
        if (curr.size() == 3) {
            ans[curr[0]] = true;
            ans[curr[1]] = true;
            ans[curr[2]] = true;
        }
        if (curr.size() == 2) {
            ans[curr[0]] = false;
            ans[curr[1]] = false;
        }
    }

    if (ans.empty()) {
        std::cout << "You didn't add 3 digit numbers\n";
    }

    for (const auto &pair : ans) {
        if (pair.second) {
            std::cout << pair.first << "\n";
        }
    }
    return 0;
}
