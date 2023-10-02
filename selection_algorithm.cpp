#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// no difference from quick sort
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

// preDeclare of the function
int MedianOfMedians(vector<int>*, int, int);


// return the ith small element in A
int selection(vector<int>* A, int p, int r, int i){
    vector<int>& Avec = *A;
    // This line will make the debug process becomes easier
    //cout << "p=" << p <<" r=" <<  r <<" i=" <<  i <<endl;
    
    // for length < 5 case, insertion sort is a good way to sort
    if(r-p < 5){
        int key, tmp;
        for(int j = p+1; j <= r; j++){
            key = Avec[j];
            tmp = j - 1;
            while( tmp >= p && Avec[tmp] > key){
                Avec[tmp + 1] = Avec[tmp];
                tmp--;
            }
            Avec[tmp+1]=key;
        }
        return p+i;
    }

    // find the index of median, and swap it so that partition will use it
    int pivot = MedianOfMedians(A, p, r);
    //cout << "pivot=" << Avec[pivot] << endl;
    swap(&Avec[pivot], &Avec[r]);
    
    
    // partition
    int q = partition(A, p, r);
    // the whole array will not be sorted completely
    // but pivot will divide them into two part
    // including larger part & smaller part


    // These lines will make the debug process becomes easier
    /* for demo
    for(int d=p; d<=r;d++){
        cout << Avec[d] << ", ";
    }
    cout <<endl;
     */
    
    // follow textbook procedure
    int k = q-p; // note that i count from 0
    if(i == k) return q;
    else if(i < k) return selection(A, p, q, i);
    return selection(A, q+1, r, i-(q-p+1));
}


// return the index of median of medians
// actually, this function should be in the selection and be used recursively
int MedianOfMedians(vector<int>* A, int p, int r){
    int medianNum = (r-p+4) / 5; // e.g. r-p = 6 -> 2 medians
    int subl, subr, medianIdx;
    vector<int>& Avec = *A;
    for(int i = 0; i < medianNum ; i++){
        subl = p + i*5;
        subr = subl + 4;
        if(subr > r) subr = r; // subr is at most 5. This happens in the last subarray
        medianIdx = selection(A, subl, subr, (subr-subl)/2 ); // use <5 case in the selection to find median
        swap(&Avec[p+i], &Avec[medianIdx]); // switch the median to the front part of the array
    }
    int test = selection(A, p, p+medianNum, medianNum/2);
    //cout << test << endl;
    return test;// return the median of medians
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int key;
    ifstream input("input.txt");
    ofstream output("output.txt");
    if(!input)cout << "file not opened";
    
    vector<int> vec;
    
    int num, ith;
    input >> num >> ith;
    
    while (input >> key) {
        vec.push_back(key);
    }
    
    int result = selection(&vec, 0, num-1, ith-1); // count form 0
    //cout << vec[result] << endl;
    
    output << num << endl;
    output << ith << endl;
    output << vec[result] << endl;
    
    input.close();
    output.close();
    
    return 0;
}
