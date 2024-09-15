#ifndef INSERTION_SORT_H_INCLUDED
#define INSERTION_SORT_H_INCLUDED

#include <iostream>
#include <vector>
//iterpties (insertion) algoritmas
void insertion_sort(std::vector<int> &arr) {
    int n = arr.size();
    #pragma omp parallel for shared(arr)        //lygiagretinu algoritma
    for (int i = 1; i < n; ++i) {
        int key = arr[i];                       //tikrinamas skaicius pasirenkamas kaip raktas
        int j = i - 1;                          //pazymimas narys pries rakta

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];                //jeigu j narys didesnis uz rakta jis stumiamas i prieki
            j = j - 1;
        }
        arr[j + 1] = key;                       //atlikus paieska raktas istatomas i savo vieta
    }
}




#endif // INSERTION_SORT_H_INCLUDED
