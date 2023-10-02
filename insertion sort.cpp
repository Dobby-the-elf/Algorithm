#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// algotihm of insertion sort
void insertionSort(vector<int>* vec, int length){
    vector<int>& vecc = *vec; // dereference vec to vecc
    int key, p;

    for(int j = 2; j <= vecc[0]; j++){
        key = vecc[j];
        p = j - 1;

        while( p > 0 && vecc[p] > key){
            vecc[p + 1] = vecc[p];
            p--;
        }
        vecc[p+1]=key;
    }
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
    
    insertionSort(&vec, vec[0]);
    
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
