#include <iostream>

using namespace std;

int *loadArray(unsigned int &size, int &valueSought)
{
    do
    {
        cout << "Enter the number of elements in array: ";
        cin >> size;
        if (size <= 0)
        {
            cout << "Invalid data provided!" << endl;
        }
    } while (size <= 0);

    int *array = new int[size];

    for(unsigned int i = 0;i < size;i++)
    {
        cout << "[" << i << "] = ";
        cin >> array[i];
    }

    cout << "Enter search value: ";
    cin >> valueSought;

    return array;
}

int linearSearch(const int *array, const unsigned int &size, const int &valueSought)
{
    for (unsigned int i = 0;i < size;i++)
    {
        if (array[i] == valueSought)
            return i;
    }
    return -1;
}

int binarySearch(const int *array, const unsigned int &size, const int &valueSought) // require ascending order
{
    unsigned int left = 0, right = size - 1, div;
    while (left < right)
    {
        div = (left + right) / 2;
        if (valueSought > array[div])
            left = div + 1;
        else
            right = div;
    }
    if (valueSought == array[right])
        return right;
    else
        return -1;
}

int recursiveBinarySearch(const unsigned int &left, const unsigned int &right, const int *array, const int &valueSought) // require ascending order
{
    unsigned int div;
    if (left == right)
    {
        if (valueSought == array[right])
            return right;
        else
            return -1;
    }
    else
    {
        div = (left + right) / 2;
        if (valueSought > array[div]) return recursiveBinarySearch(div + 1, right, array, valueSought);
        else return recursiveBinarySearch(left , div, array, valueSought);
    }
}

int main()
{
    unsigned int testSize;
    int testValueSought;

    int *testArray = loadArray(testSize, testValueSought);

    int lS = linearSearch(testArray, testSize, testValueSought);
    int bS = binarySearch(testArray, testSize, testValueSought);
    int rbS = recursiveBinarySearch(0, testSize - 1, testArray, testValueSought);

    cout << endl << "Linear search:" << endl;
    if (lS == -1) cout << "Value sought does not exist in array" << endl;
    else cout << "Index of value sought = " << lS << endl;

    cout << endl << "Binary search:" << endl;
    if (bS == -1) cout << "Value sought does not exist in array" << endl;
    else cout << "Index of value sought = " << bS << endl;

    cout << endl << "Recursive binary search:" << endl;
    if (rbS == -1) cout << "Value sought does not exist in array" << endl;
    else cout << "Index of value sought = " << rbS << endl;

    cout << endl;
    getchar(); getchar(); return 0;
}