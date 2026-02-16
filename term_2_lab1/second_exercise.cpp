#include <algorithm>
#include <iostream>
#include <vector>

bool check_empty_vector_and_print(const std::vector<int>& vec, const std::string& error_msg = "Empty input") {
  if (vec.empty()) {
    std::cout << error_msg;
    return true;
  }

  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i + 1 < vec.size()) std::cout << " ";
  }

  std::cout << "\n\n\n";

  return false;
}


int main() {
  std::vector<int> nums;

  int x;
  while (std::cin >> x) {
    nums.push_back(x);
  }

  if (check_empty_vector_and_print(nums)) return 0;


  std::vector<int> seq1(nums);
  int max_el = *std::max_element(nums.begin(), nums.end());
  std::erase(seq1, max_el);
  if (check_empty_vector_and_print(seq1, "Vector is empty after removing max elements")) return 0;


  std::vector<int> seq2(seq1);
  int min_val = *std::min_element(seq2.begin(), seq2.end());
  std::replace_if(seq2.begin(), seq2.end(),
    [](int i) {return i%2 == 0;}, min_val);
  if (check_empty_vector_and_print(seq2)) return 0;


  std::sort(seq2.begin(), seq2.end());
  seq2.erase(std::unique(seq2.begin(), seq2.end()), seq2.end());
  if (check_empty_vector_and_print(seq2,"Vector is empty after removing unique elements")) return 0;

  return 0;
}