// The author of this program is Kamil Cinner.
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <iomanip>

clock_t start, stop;

using namespace std;

void swapTwoElemsInArray(int* array, unsigned int& index1, unsigned int& index2)
{
    int tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}

unsigned int loadSize()
{
    int testSize;
    do
    {
        cout << "Enter the number of elements in array: ";
        cin >> testSize;
        if (testSize <= 0)
            cout << "Invalid data provided!" << endl;
    } while (testSize <= 0);

    return (unsigned int)testSize;
}

void copyArray(const int* arrayToCopy, int* arrayCopy, const unsigned int& size)
{
    for (unsigned int i = 0;i < size;i++)
    {
        arrayCopy[i] = arrayToCopy[i];
    }
}

void printArray(const int* array, const unsigned int &size)
{
    for (unsigned int i = 0;i < size;i++)
    {
        cout << array[i] << ", ";
    } cout << endl;
}

void bubbleSort(int* array, const unsigned int& size, double &time)
{
    int buf;

    start = clock();

    for (unsigned int i = 0;i < size;i++)
    {
        for (unsigned int j = 0;j < size - 1 - i;j++)
        {
            if (array[j] > array[j + 1])
            {
                buf = array[j + 1];
                array[j + 1] = array[j];
                array[j] = buf;
            }
        }
    }

    stop = clock();

    time = (double)(stop - start) / CLOCKS_PER_SEC;
}

void insertSort(int* array, const unsigned int& size, double &time)
{
    int tmp;
    int j;

    start = clock();
    
    for (unsigned int i = 1;i < size;i++)
    {
        j = i - 1;
        tmp = array[i];
        while (j >= 0 && array[j] > tmp)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = tmp;
    }

    stop = clock();

    time = (double)(stop - start) / CLOCKS_PER_SEC;
}

void selectSort(int* array, const unsigned int& size, double &time)
{
    int max;
    unsigned int maxIndex;
    
    start = clock();

    for (unsigned int i = size - 1;i > 0;i--)
    {
        max = array[0];
        maxIndex = 0;
        for (unsigned int j = 1;j <= i;j++)
        {
            if (max < array[j])
            {
                max = array[j];
                maxIndex = j;
            }
        }
        array[maxIndex] = array[i];
        array[i] = max;
    }

    stop = clock();

    time = (double)(stop - start) / CLOCKS_PER_SEC;
}

void quicksort(int* array, unsigned int left, unsigned int right)
{
	int div = array[(left + right) / 2];
	unsigned int i, j;
	i = left;
	j = right;
	do
	{
		while (array[i] < div) i++;
		while (array[j] > div) j--;
        if (j < 0) cout << "err";
		if (i <= j)
		{
			swapTwoElemsInArray(array, i, j);
			i++;
			j--;
		}
	} while (i <= j);
	if (j > left) quicksort(array, left, j);
	if (i < right) quicksort(array, i, right);
}

int main()
{
    unsigned int size = loadSize();
    
    int* array = new int[size];

    srand(time(NULL));
    for (unsigned int i = 0;i < size;i++)
    {
        array[i] = rand() % 1000 - 500;
    }

    //printArray(array, size);
    
    int* arrayCopy = new int[size];
    
    double time;

    cout << setprecision(20) << fixed;

    copyArray(array, arrayCopy, size);
    bubbleSort(arrayCopy, size, time);
    cout << "Bubble Sort time = " << time << endl << endl;

    copyArray(array, arrayCopy, size);
    insertSort(arrayCopy, size, time);
    cout << "Insert Sort time = " << time << endl << endl;

    copyArray(array, arrayCopy, size);
    selectSort(arrayCopy, size, time);
    cout << "Select Sort time = " << time << endl << endl;

    copyArray(array, arrayCopy, size);
    start = clock();
    quicksort(arrayCopy, 0, size - 1);
    stop = clock();
    time = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Quicksort time = " << time << endl << endl;

    delete [] array;
    delete [] arrayCopy;

    getchar();
    getchar();
}