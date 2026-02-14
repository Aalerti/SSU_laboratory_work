#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

bool check_empty_vector_and_print(const std::vector<int>& vec, const std::string& error_msg = "Empty input") {
  if (vec.empty()) {
    std::copy(error_msg.begin(), error_msg.end(), std::ostream_iterator<char>(std::cout, ""));
    return true;
  }

  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

  std::string sep = "\n\n\n";
  std::copy(sep.begin(), sep.end(), std::ostream_iterator<char>(std::cout, ""));

  return false;
}


int main() {
  std::vector<int> nums;

  std::copy(std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::back_inserter(nums));

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