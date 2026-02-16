#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> nums;

  int x;
  while (std::cin >> x) {
    nums.push_back(x);
  }

  if (nums.empty()) {
    std::cout << "Empty input";
    return 0;
  }

  double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
  double arif_mean = sum / nums.size();

  double product = std::accumulate(nums.begin(), nums.end(), 1.0, std::multiplies<double>());
  double geom_mean = std::exp(std::log(product) / nums.size());


  std::cout << "Arithmetic mean: " << arif_mean << "\n";
  std::cout << "Geometric mean: " << geom_mean << "\n";


  return 0;
}