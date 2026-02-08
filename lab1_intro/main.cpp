#include <iostream>
#include <vector>


int main() {
    std::vector<int> data(10);

    for (int i = 0; i < 10; i++) {
        data[i] = i * 2;
        std::cout << "Value: " << data[i] << std::endl;
    }

    return 0;
}