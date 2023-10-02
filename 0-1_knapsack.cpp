#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// print the complete K table
void printK(vector<vector<int> > K)
{
    for (int i = 0; i < K.size(); i++)
    {
        for (int j = 0; j < K[i].size(); j++)
        {
            cout << " " << K[i][j];
        }
        cout << endl;
    }
}

// use this function recursively to check which item is chosen
void findChosen(vector<vector<int> > K, vector<int> weight, int i, int j, vector<int> &chosen)
{
    //cout << i << " " << j << endl;
    if (i == 0)
        return;
    else if (K[i][j] > K[i - 1][j])
    {
        chosen.push_back(i);
        findChosen(K, weight, i - 1, j - weight[i - 1], chosen);
    }
    else
    {
        findChosen(K, weight, i - 1, j, chosen);
    }
}

int main(int argc, const char *argv[])
{
    int key;
    ifstream input("input.txt");
    ofstream output("output.txt");
    if (!input)
        cout << "file not opened";

    vector<int> value;
    vector<int> weight;

    int n, W, tmpA, tmpB;
    input >> n >> W;

    // read each item from file
    for (int i = 0; i < n; i++)
    {
        input >> tmpA >> tmpB;
        value.push_back(tmpA);
        weight.push_back(tmpB);
    }

    // create a 2D table K
    vector<vector<int> > K(n + 1, vector<int>(W + 1, 0));

    // implement the algorithm
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (j < weight[i - 1])
            {
                K[i][j] = K[i - 1][j];
            }
            else
            {
                K[i][j] = max(K[i - 1][j], K[i - 1][j - weight[i - 1]] + value[i - 1]);
            }
        }
    }
    // print out the result
    printK(K);

    output << "Total revenue = " << K[n][W] << endl << "Selected item : ";

    // print out each chosen item backwardly
    vector<int> chosen;
    findChosen(K, weight, n, W, chosen);
    for (int i = chosen.size() - 1; i >= 0; i--)
    {
        output << chosen[i] << " ";
    }
    output << endl;

    input.close();
    output.close();

    return 0;
}
