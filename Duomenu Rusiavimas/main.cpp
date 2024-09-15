#include <iostream>
#include <stdio.h>
#include <vector>
#include <random>
#include <omp.h>
#include "insertion_sort.h"

//generuojamas atsitiktiniu verciu vektorius
std::vector<int> generateRandomVector(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 99);

    std::vector<int> randomVector;
    for (int i = 0; i < length; ++i) {
        randomVector.push_back(dis(gen));
        //if (i%100000 == 0) std::cout << 1 << std::endl;   testavau kiek laiko uzima vektoriaus generavimas
    }
    return randomVector;
}
int main() {
    int length = 2000;
    std::vector<int> randomVector = generateRandomVector(length);

    double start_time = omp_get_wtime(); // Record start time
    // vektoriaus verciu isvedimas patikrinti ar rezultatai teisingi
    printf("random vector: ");
    for (int i = 0; i < length; i++)
        printf("%d ", randomVector[i]);
    printf("\n");

    insertion_sort(randomVector);

    printf("sorted vector: ");
    for (int i = 0; i < length; i++)
        printf("%d ", randomVector[i]);
    printf("\n");

    double end_time = omp_get_wtime(); // Record end time
     printf("vector sorted in: %f seconds", end_time - start_time);

    return 0;
}
