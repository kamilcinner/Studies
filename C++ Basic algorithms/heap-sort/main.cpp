// The author of this program is Kamil Cinner.
#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

class HeapSort {
  public:

	  int arrayLenght;
	  int* arr;
	  int n;

	  void loadData() {
		  cout << "Enter the number of elements in the array: ";
		  cin >> arrayLenght;
		  arr = new int[arrayLenght];
		  cout << "Enter next elements:" << endl;
		  for (int i = 0;i < arrayLenght;i++) {
			  cout << "[" << i << "] = ";
			  cin >> arr[i];
		  }
		  n = arrayLenght;
	  }
	  void printArray() {
		  for (int i = 0;i < arrayLenght;i++) {
			  cout << arr[i] << " , ";
		  }
	  }
	  void swapp(int index1, int index2) {
		  int temp = arr[index1];
		  arr[index1] = arr[index2];
		  arr[index2] = temp;
	  }
	  void validateMaxHeap(int heapSize, int parentIndex) {
		  int maxIndex = parentIndex;
		  int leftChild = parentIndex * 2 + 1;
		  int rightChild = parentIndex * 2 + 2;

		  if (leftChild < heapSize && arr[leftChild] > arr[maxIndex]) {
			  maxIndex = leftChild;
		  }
		  if (rightChild < heapSize && arr[rightChild] > arr[maxIndex]) {
			  maxIndex = rightChild;
		  }
		  if (maxIndex != parentIndex) {
			  swapp(maxIndex, parentIndex);
			  validateMaxHeap(heapSize, maxIndex);
		  }
	  }
	  void heapSort() {
		  for (int i = n / 2 - 1;i >= 0;i--) {
			  validateMaxHeap(n, i);
		  }
		  for (int i = n - 1;i > 0;i--) {
			  swapp(0, i);
			  validateMaxHeap(--n, 0);
		  }
	  }
	  // TestStart
	  void test() {
		  arrayLenght = 100;
		  arr = new int[arrayLenght];
		  srand(time(NULL));
		  for (int i = 0;i < arrayLenght;i++) {
			  arr[i] = rand() % 20 + 1;
		  }
		  n = arrayLenght;
	  }
	  // TestEnd
};

int main() {
	HeapSort hS;
	double duration;
	clock_t start;
	//hS.loadData();
	hS.test();
	cout << "Array before Heap Sort:\n";
	hS.printArray();
	start = clock();
	hS.heapSort();
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\nArray after Heap Sort:\n";
	hS.printArray();
	cout << setprecision(30) << fixed;
	cout << endl << "Soting time = " << duration << endl;
	getchar();
}