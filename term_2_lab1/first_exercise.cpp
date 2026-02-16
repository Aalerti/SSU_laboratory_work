#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> nums;

  int x;
  while (std::cin >> x) {
    nums.push_back(x);
  }

  if (!nums.empty()) {
    auto r_min_it = std::min_element(nums.rbegin(), nums.rend());

    nums.erase(std::prev(r_min_it.base()));
  }
  else {
    std::cout << "Vector is empty!";
    return 0;
  }

  for (size_t i = 0; i < nums.size(); ++i) {
    std::cout << nums[i];
    if (i + 1 < nums.size()) std::cout << " ";
  }

  return 0;
}