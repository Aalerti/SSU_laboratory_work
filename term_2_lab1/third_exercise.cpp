#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> nums;

  std::copy(std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::back_inserter(nums));

  if (nums.empty()) {
    std::string error_msg = "Empty input";
    std::copy(error_msg.begin(), error_msg.end(), std::ostream_iterator<char>(std::cout, ""));
    return 0;
  }

  double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
  double arif_mean = sum / nums.size();

  double product = std::accumulate(nums.begin(), nums.end(), 1.0, std::multiplies<double>());
  double geom_mean = std::exp(std::log(product) / nums.size());


  std::string res_arithmetic = "Arithmetic mean: " + std::to_string(arif_mean) + "\n";
  std::copy(
      res_arithmetic.begin(),
      res_arithmetic.end(),
      std::ostream_iterator<char>(std::cout, "")
  );

  std::string res_geometric = "Geometric mean: " + std::to_string(geom_mean) + "\n";
  std::copy(
      res_geometric.begin(),
      res_geometric.end(),
      std::ostream_iterator<char>(std::cout, "")
  );


  return 0;
}