#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

// Fill-in the m,s tables
void Matrix_Chain_Order(int n, vector<int> p, vector<vector<int> > &m, vector<vector<int> > &s){
    for (int i = 1; i <= n; i++){ // all zero on diagonal
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++){ // l is length of chain
        for (int i = 1; i <= n - l + 1; i++){ // i, j are start and end
            int j = i + l - 1;
            m[i][j] = (1<<30) - 1 + (1<<30); // maximal integer(2^31-1)
            for (int k = i; k <= j - 1; k++){ // try each possible combination
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]){ // replace if it is cheaper
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Print out the optimal combination of parentesis
void Print_Optimal_Parens(vector<vector<int> > s, int i, int j, vector<char> &combo){
    if (i == j){
        combo.push_back('A');
        if (i < 10)
            combo.push_back(48 + i); // push the char of number
        else{   // if the number of matrix is greater than 10, extra space is needed
            combo.push_back(i / 10 + 48);
            combo.push_back(i % 10 + 48);
        }
    }
    else{
        combo.push_back('(');
        Print_Optimal_Parens(s, i, s[i][j], combo);
        Print_Optimal_Parens(s, s[i][j] + 1, j, combo);
        combo.push_back(')');
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int key;
    ifstream input("input.txt");
    ofstream output("output.txt");
    if(!input)cout << "file not opened";
    
    vector<int> p;
    
    while (input >> key) {
        p.push_back(key);
        cout << key << " ";
    }
    cout << endl;

    vector<char> combo;
    int n;
    n = p.size() - 1;
    vector<vector<int> > m(n + 1, vector<int>(n + 1));
    vector<vector<int> > s(n, vector<int>(n + 1));
    
    Matrix_Chain_Order(n, p, m, s);

    output << m[1][n] << endl;
    cout << m[1][n] << endl;

    Print_Optimal_Parens(s, 1, n, combo);
    
    for (int i = 0; i < combo.size(); i++){
        output << combo[i];
        cout << combo[i];
    }
    cout << endl;

    input.close();
    output.close();
    
    return 0;
}
