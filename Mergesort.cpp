#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge(vector<int>* vec, int p, int q, int r){
    int i = p; // first element of first half vector
    int j = q + 1; // first element of second half vector
    int prog = p; // progress of merge operation
    vector<int>& vecc = *vec; // dereference vec to vecc
    vector<int> tmp; // used to store temporary result
    
    for (int i=0 ; i <= vecc[0] ; i++){
        tmp.push_back(vecc[i]);
    }
    
    // while merging is not done pushes the small one into the tmp vector
    while(prog <= r){ 
        if((vecc[i] <= vecc[j] && i <= q)|| j>r ){
            tmp[prog] = vecc[i];
            i++;
        }
        else{
            tmp[prog] = vecc[j];
            j++;
        }
        prog++;
    }
    
    for(int i = p; i <= r; i++){
        vecc[i] = tmp[i];
    }
}

// inplement merge sort by doing recursively
void mergeSort(vector<int>* vec, int p, int r){
    if (p >= r)return;
    int q = (p + r)/2;
    mergeSort(vec, p, q);
    mergeSort(vec, q+1, r);
    merge(vec, p, q, r);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int key;
    ifstream input("input.txt");
    ofstream output("output.txt");
    if(!input)cout << "file not opened";
    
    vector<int> vec;
    
    while (input >> key) {
        vec.push_back(key);
    }
    
    mergeSort(&vec, 1, vec[0]);
    
    for (int i=0 ; i <= vec[0] ; i++){
        output << vec[i] << endl;
    }
    
    input.close();
    output.close();
    
    return 0;
}
