#include <iostream>
#include <vector>

using namespace std;

void swapTwoValuesInTwoVectors(vector<int> &A, vector<int> &B, const int &index1, const int &index2)
{
    int tmp = A[index1];
    A[index1] = A[index2];
    A[index2] = tmp;
    
    tmp = B[index1];
    B[index1] = B[index2];
    B[index2] = tmp;
}

void quicksort(vector<int> &A, vector<int> &B, unsigned int left, unsigned int right)
{
	int div = A[(left + right) / 2];
	unsigned int i, j;
	i = left;
	j = right;
	do
	{
		while (A[i] < div) i++;
		while (A[j] > div) j--;
		if (i <= j)
		{
			swapTwoValuesInTwoVectors(A, B, i, j);
			i++;
			j--;
		}
	} while (i <= j);
	if (j > left) quicksort(A, B, left, j);
	if (i < right) quicksort(A, B, i, right);
}

vector<vector<int>> glueIntervals(vector<vector<int>> intervalsSet, int &intervalsCount)
{
    vector<int> newA, newB;
    int tmpB, i, indexA = 0;
    bool gotChange = false;
    
    while (indexA < intervalsSet[0].size())
    {
        i = indexA + 1;
        tmpB = intervalsSet[1][indexA];
        while (i < intervalsSet[0].size() && intervalsSet[0][i] <= tmpB)
        {
            i++;
        }
        if (--i > indexA)
        {
            gotChange = true;
            newA.push_back(intervalsSet[0][indexA]);
            newB.push_back(intervalsSet[1][i]);
            indexA = i + 1;
            
            //cout <<endl << "got change";
        }
        else
        {
            newA.push_back(intervalsSet[0][indexA]);
            newB.push_back(intervalsSet[1][indexA]);
            indexA++;
        }
    }
    if (gotChange)
    {
        /*cout << endl << "A: ";
        for (int i = 0;i < newA.size();i++)
        {
            cout << newA[i] << ", ";
        }
        cout << endl << "B: ";
        for (int i = 0;i < newA.size();i++)
        {
            cout << newB[i] << ", ";
        }*/
        
        vector<vector<int>> newIntervalsSet;
        newIntervalsSet.push_back(newA);
        newIntervalsSet.push_back(newB);
        glueIntervals(newIntervalsSet, intervalsCount);
    }
    else
    {
        intervalsCount = intervalsSet[0].size();
        return intervalsSet;
    }
}

int solution(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    quicksort(A, B, 0, n - 1);
    
    /*cout << endl << "A: ";
    for (int i = 0;i < A.size();i++)
    {
        cout << A[i] << ", ";
    }
    cout << endl << "B: ";
    for (int i = 0;i < A.size();i++)
    {
        cout << B[i] << ", ";
    }*/
    
    vector<vector<int>> intervalsSet;
    intervalsSet.push_back(A);
    intervalsSet.push_back(B);
    
    int intervalsCount;
    glueIntervals(intervalsSet, intervalsCount);
    
    return intervalsCount;
}