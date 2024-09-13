#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include<string.h>

using namespace std;

const int MAX_LOG = 16; // Enough for 2^16 > 50000

void preprocess(int n, const vector<int>& parent, vector<vector<int>>& ancestor) {
    for (int i = 0; i < n; ++i) {
        ancestor[i][0] = parent[i];
    }

    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (ancestor[i][j - 1] != -1) {
                ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
            } else {
                ancestor[i][j] = -1;
            }
        }
    }
}

int kthAncestor(int n, const vector<int>& parent, int node, int k) {
    vector<vector<int>> ancestor(n, vector<int>(MAX_LOG, -1));
    preprocess(n, parent, ancestor);

    for (int j = 0; k > 0 && node != -1; ++j) {
        if (k & 1) {
            node = ancestor[node][j];
        }
        k >>= 1;
    }

    return node;
}



class Runner
{
    int t;
    
    vector< vector<int> > allParent;
    vector< int > allNode;
    vector< int > allK;
    vector< int > allN;

public:
    
    void takeInput()
    {
        cin >> t;
        
        allParent.resize(t);
        allNode.resize(t);
        allK.resize(t);
        allN.resize(t);

        for (int i = 0; i < t; i++)
        {
            cin >> allN[i];

            allParent[i].resize(allN[i]);

            for(int j = 0; j < allN[i]; j++)
            {
                cin >> allParent[i][j];
            }
            
            cin >> allNode[i] >> allK[i];
        }

        return;
    }

    vector<int> copyArray( vector<int> &arr)
    {
        vector<int> copy;

        int n = arr.size();

        copy.resize(n);

        for(int i = 0; i < n; i++)
        {           
            copy[i] = arr[i];     
        }

        return copy;
    }

    void execute()
    {   
       for(int i = 0; i < t; i++)
       {
            vector< int> copyArr = copyArray(allParent[i]);

            kthAncestor(allN[i], copyArr, allNode[i], allK[i]);
       }
    }

    void executeAndPrintOutput()
    {
       
       for(int i = 0; i < t; i++)
       {
            vector< int> copyArr = copyArray(allParent[i]);

            int result = kthAncestor(allN[i], copyArr, allNode[i], allK[i]);

            cout << result << "\n";
       }
    }
};

int main()
{
    Runner runner;
    runner.takeInput();
    runner.executeAndPrintOutput();

    return 0;
}