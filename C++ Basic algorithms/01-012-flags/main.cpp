#include <iostream>
#include <time.h>

using namespace std;

void swapTwoElemsInUArray(unsigned int* uArray, const unsigned int& index1, const unsigned int& index2)
{
    int tmp = uArray[index1];
    uArray[index1] = uArray[index2];
    uArray[index2] = tmp;
}

void printUArray(const unsigned int* uArray, const unsigned int& size)
{
    for (unsigned int i = 0;i < size;i++)
    {
        cout << uArray[i] << " ";
    } cout << endl;
}

// returns index of the last '0' in array after flag01
unsigned int flag01(unsigned int* array01, const unsigned int& size)
{
    unsigned int left = 0, right = size - 1;

    while (left < right)
    {
        while (array01[left] == 0 && left < right) left++;
        while (array01[right] == 1 && left < right) right--;
        if (left < right)
        {
            swapTwoElemsInUArray(array01, left, right);
            left++;
            right--;
        }
    }
	if (array01[0] == 1 || left != right || (left == right && array01[left] != 0)) left--;
    return left;
}

void flag012(unsigned int* array012, const unsigned int& size, int& index0, int& index2)
{
    // postitions of first 0 1 2 in array
    index0 = -1;
    int index1 = 0;
    index2 = size;

    unsigned int tmp;

    while (index1 < index2) // 011020
    {
        tmp = array012[index1];
        if (tmp == 0)
        {
            index0++;
            swapTwoElemsInUArray(array012, (unsigned int)index0, index1);
            index1++;
        }
        else if (tmp == 1) index1++;
        else
        {
            index2--;
            swapTwoElemsInUArray(array012, index1, index2);
        }
    }
}

int main()
{
    unsigned int size = 30;
    unsigned int* array01 = new unsigned int[size];
    srand(time(NULL));
    for (unsigned int i = 0;i < size;i++)
    {
        array01[i] = rand() % 2;
    }

    cout << "Array01 before flag01:" << endl;
    printUArray(array01, size);

    cout << "Array01 after flag01:" << endl;
    cout << "Index of last '0': " << flag01(array01, size) << endl;
    printUArray(array01, size);

    unsigned int* array012 = new unsigned int[size];
    for (unsigned int i = 0;i < size;i++)
    {
        array012[i] = rand() % 3;
    }

    int index0, index2;

    cout << "Array012 before flag01:" << endl;
    printUArray(array012, size);

    cout << "Array012 after flag012:" << endl;
    flag012(array012, size, index0, index2);
    cout << "Index of last '0': " << index0 << endl;
    cout << "Index of first '2': " << index2 << endl;
    printUArray(array012, size);

    getchar();
}