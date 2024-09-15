#include <iostream>
#include <vector>
#include <random>

std::vector<int> generateRandomVector(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 99);

    std::vector<int> randomVector;
    for (int i = 0; i < length; ++i) {
        randomVector.push_back(dis(gen));
    }

    return randomVector;
}

int main() {
    int vectorLength = 10; // Change this to the desired length of the vector
    std::vector<int> randomVector = generateRandomVector(vectorLength);

    // Output the generated vector
    std::cout << "Random vector: ";
    for (int num : randomVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
