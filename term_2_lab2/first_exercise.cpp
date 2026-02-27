#include <iostream>
#include <vector>
#include <set>
# include <cmath>

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

    std::set<int> digits_in_3;
    std::set<int> digits_in_2;

    for (int num : nums) {
        int abs_num = std::abs(num); 

        int temp = abs_num;
        int digit_count = 0;
        if (temp == 0) {
            digit_count = 1;
        } else {
            while (temp > 0) {
                digit_count++;
                temp /= 10;
            }
        }

        if (digit_count == 3 || digit_count == 2) {
            temp = abs_num;
            while (temp > 0) {
                int digit = temp % 10;
                if (digit_count == 3) {
                    digits_in_3.insert(digit);
                } else {
                    digits_in_2.insert(digit);
                }
                temp /= 10;
            }
        }
    }

    if (digits_in_3.empty()) {
        std::cout << "You didn't add 3 digit numbers\n";
        return 0;
    }

    bool found = false;
    for (int digit : digits_in_3) {
        if (digits_in_2.count(digit) == 0) {
            std::cout << digit << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching digits found\n";
    }

    return 0;
}