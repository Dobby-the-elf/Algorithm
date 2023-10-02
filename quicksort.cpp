#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// widely used swap function
void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// the partition function of quicksort
int partition(vector<int>* vec, int p, int r){
    int i = p-1, tmp;

    vector<int>& vecc = *vec; // dereference vec to vecc

    int piv = vecc[r];
    
    for(int j = p; j < r; j++){
        if(vecc[j] <= piv){
            i++;
            swap(&vecc[i], &vecc[j]);
        }
    }
    swap(&vecc[i+1], &vecc[r]);
    return i+1;
}

// implement quicksort algorithm in the textbook
void quickSort(vector<int>* vec, int p, int r){
    if (p >= r)return;
    int q;
    q = partition(vec, p, r);
    quickSort(vec, p, q-1);
    quickSort(vec, q+1, r);
}

int main(int argc, const char * argv[]) {
    int key;
    ifstream input("input.txt");
    ofstream output("output.txt");
    if(!input)cout << "file not opened";
    
    vector<int> vec;
    
    while (input >> key) {
        vec.push_back(key);
    }
    
    clock_t tStart = clock();
    
    quickSort(&vec, 1, vec[0]);
    
    // print the time taken for runinng the algorithm
    printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    // output data
    for (int i=0 ; i <= vec[0] ; i++){
        output << vec[i] << endl;
    }
    
    input.close();
    output.close();
    
    return 0;
}
