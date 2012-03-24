#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef pair<unsigned long int*,unsigned long int> result;

result merge_and_countSplitInv(unsigned long int*B,unsigned long int*C,unsigned long int lenB,unsigned long int lenC)
{

    unsigned long int n = lenB + lenC;
    unsigned long int i = 0;
    unsigned long int j = 0;
    unsigned long int*D = new unsigned long int[n];

    unsigned long int nInv = 0;

    for (unsigned long int k=0; k!=n; k++)
    {
        if (lenB==i) // no more elements in B
        {
            //cout << "From C: " << C[j] << endl;
            D[k] = C[j];
            ++j;
        }
        else if (lenC==j) // no more elements in C
        {
            //cout << "From B: " << B[i] << endl;
            D[k] = B[i];
            ++i;
        }
        else if (B[i] < C[j])
        {
           // cout << "From B: " << B[i] << endl;
            D[k] = B[i];
            ++i;
        }
        else
        {
            //cout << "From C: " << C[j] << endl;
            D[k] = C[j];
            nInv = nInv+(lenB-i);
            ++j;
        }
    }

    return make_pair(D,nInv);

}

result sort_and_count(unsigned long int A[],unsigned long int lenA)
{
    if (lenA==1)
    {
        return make_pair(A,0);
    }
    else
    {
        unsigned long int splitIdx;
        unsigned long int lenB,lenC;
        if (lenA%2==0)
        {
            splitIdx = lenA/2;
            lenB = lenA/2;
            lenC = lenA/2;
        }
        else
        {
            splitIdx = (lenA-1)/2;
            lenB = (lenA-1)/2;
            lenC = lenB+1;
        }

        result resultLeft, resultRight, resultMerge;

        resultLeft = sort_and_count(&A[0],lenB);
        resultRight = sort_and_count(&A[splitIdx],lenC);
        resultMerge = merge_and_countSplitInv(resultLeft.first,resultRight.first,lenB,lenC);

        return make_pair(resultMerge.first,resultLeft.second+resultRight.second+resultMerge.second);

    }
}

void test(int A[], int B[])
{
    for (int k=0; k!=3;++k)
    {
        cout << A[k] << endl;
        cout << B[k] << endl;
    }
}

int main()
{
    result invResult;
    unsigned long int length = 11;

    unsigned long int C[11] = {4,6,3,1,8,5,100,33,223,14,215};
    invResult = sort_and_count(C,11);

    for (int k=0;k!=length;++k)
    {
        cout << invResult.first[k] << endl;
    }
    cout << "Number of Inversions: " << invResult.second << endl;

    unsigned long int *F;
    unsigned long int k = 0;
    int lenF=0;
    F = new unsigned long int[100000];
/*
    string lineInput;
    while (cin >> lineInput)
    {
        F[k] = atol(lineInput.c_str());
        lenF=k++;
    }

    cout << lenF << endl;
    //invResult = sort_and_count(F,5);
    //cout << "Number of Inversions: " << invResult.second << endl;*/
    ifstream infile("C:\\Documents and Settings\\c\\My Documents\\Downloads\\IntegerArray.txt");
    unsigned long int i;
    if (!infile) {
        cout << "There was a problem opening file "
             << " for reading."
             << endl;
        return 0;
    }
    cout << "Opened for reading." << endl;
    while (infile >> i) {
        F[k] = i;
        lenF=++k;
    }
    cout << lenF << endl;
    invResult = sort_and_count(F,100000);
    cout << "Number of Inversions: " << invResult.second << endl;
    invResult = sort_and_count(invResult.first,100000);
    cout << "Number of Inversions: " << invResult.second << endl;
    return 0;
}



