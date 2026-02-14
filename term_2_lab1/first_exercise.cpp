#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> nums;

  std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(),
            std::back_inserter(nums));

  if (!nums.empty()) {
    auto r_min_it = std::min_element(nums.rbegin(), nums.rend());

    nums.erase(std::prev(r_min_it.base()));
  }

  std::copy(nums.begin(), nums.end(),
            std::ostream_iterator<int>(std::cout, " "));

  return 0;
}