#include <iostream>
#include "iseven.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " N" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    if (iseven_8(n)) {
        std::cout << n<< " is even." << std::endl;
    } else {
        std::cout << n<< " is odd." << std::endl;
    }

    return 0;
}