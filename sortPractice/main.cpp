#include <fstream>
#include <iostream>
using namespace std;

void initArray(char []);
void buildArray(char [], ifstream &);
void unsortArray(char []);
void mergeSortArray(char []);
void mergeSort(char [], int, int);
void mergeHelper(char [], int, int, int);
void quickSortArray(char []);
void quickSort(char[], int, int);
void partition(char[], int, int, int &);
void displayArray(char []);

const char ARRAYSIZE = 26;

void main() {


	char charArray[ARRAYSIZE];
	initArray(charArray);

	ifstream infile("alpha.txt");

	cout << "initial" << endl;
	buildArray(charArray, infile);
	cout << "unsorted" << endl;
	unsortArray(charArray);
	cout << "mergeSort" << endl;
	mergeSortArray(charArray);
	cout << "unsorted" << endl;
	unsortArray(charArray);
	cout << "quickSort" << endl;
	quickSortArray(charArray);

	//displayArray(charArray);

	system ("pause");

}

void initArray(char charArray[]) {
	for(int i = 0; i < ARRAYSIZE; i++)
		charArray[i] = NULL;
}

void buildArray(char charArray[], ifstream& infile) {
   char abc;
   for (int i = 0; i < ARRAYSIZE; i++) {
      infile >> abc;
	  charArray[i] = abc;
   }
   displayArray(charArray);
}

void unsortArray(char charArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++) {
		int random = rand() % 26;
		char temp = charArray[i];
		charArray[i] = charArray[random];
		charArray[random] = temp;
	}
	displayArray(charArray);
}

void mergeSortArray(char charArray[]) {
	mergeSort(charArray, 0, ARRAYSIZE-1);
	displayArray(charArray);
}

void mergeSort(char charArray[], int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(charArray, first, mid);
		mergeSort(charArray, mid + 1, last);
		mergeHelper(charArray, first, mid, last);
	}
}
void mergeHelper(char charArray[], int first, int mid, int last) {
	char *temp = new char[last - first + 1];
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;
	// As long as both lists still have elements, add the next.
	int index = 0;
	while ((first1 <= last1) && (first2 <= last2)) {
		if (charArray[first1] < charArray[first2]) {
			temp[index] = charArray[first1];
			first1++;
		}
		else {
			temp[index] = charArray[first2];
			first2++;
		}
		index++;
	}
	// One of the lists still has elements, so add them now.
	while (first1 <= last1) {
		temp[index] = charArray[first1];
		index++;
		first1++;
	}
	while (first2 <= last2) {
		temp[index] = charArray[first2];
		index++;
		first2++;
	}
	// Copy back into the array.
	for (int i = 0; i < last - first + 1; i++)
		charArray[i + first] = temp[i];
	delete temp;
}

void quickSortArray(char charArray[]) {
	quickSort(charArray, 0, ARRAYSIZE-1);
	displayArray(charArray);
}
void quickSort(char charArray[], int first, int last) {
	if (first < last) {
		int pivotIndex;
		// Partition the array into two sets.
		partition(charArray, first, last, pivotIndex);
		// Sort both sets recursively
		quickSort(charArray, first, pivotIndex - 1);
		quickSort(charArray, pivotIndex + 1, last);
	}
}
void partition(char charArray[], int first, int last, int &pivotIndex) {
	swap(charArray[(first+last)/2], charArray[first]);
	char pivot = charArray[first]; // select first element as pivot (bad choice?)
	int firstUnknown = first + 1; // first is the pivot
	int lastUnknown = last;
	// As long as we haven't reached the last unknown,
	// swap the element if it belongs in the second part of the array.
	while (firstUnknown <= lastUnknown) {
		if (charArray[firstUnknown] >= pivot) {
			swap(charArray[firstUnknown], charArray[lastUnknown]);
			lastUnknown--;
		}
		else
			firstUnknown++;
	}
	// Move the pivot to the spot between the partitioned sets.
	swap(charArray[first], charArray[lastUnknown]);
	pivotIndex = lastUnknown;
}

void displayArray(char charArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++) {
		cout << charArray[i] << " ";
	}
	cout << endl;
}