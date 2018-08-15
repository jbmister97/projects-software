// EE120_Lab_1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include <stdio.h> 
#include <iostream>
#include <fstream>

using namespace std;

void shift();
void sort(int*);

unsigned int c1, c2, c3, c4, c5, c6, c7, c8;
int main(void)
{
	ifstream dataFile; //open an output stream for the data file
	dataFile.open("dataStorage.txt"); //open the data file
	if (!dataFile) //if file cannot be opened exit the program
	{
		cerr << "ERROR file cannot be opened" << endl; //print error message
		exit(1);
	}
	int array[10];
	for (int j = 0; j <= 9; j++) {
		dataFile >> array[j];
	}
	cout << "TASK #1" << endl;
	cout << "The input integer values are: ";
	for (int k = 0; k <= 9; k++) {
		cout << array[k] << " ";
	}
	cout << endl;
	sort(array);
	cout << "Sorted Integers are: ";
	for (int l = 0; l <= 9; l++) {
		cout << array[l] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "TASK #2" << endl;
	shift();
	cout << "c1 = " << hex << c1 << endl;
	cout << "c2 = " << hex << c2 << endl;
	cout << "c3 = Complement of c1: " << hex << c3 << endl;
	cout << "c4 = c1 AND c2: " << hex << c4 << endl;
	cout << "c5 = c1 OR c2: " << hex << c5 << endl;
	cout << "c6 = c1 XOR c2: " << hex << c6 << endl;
	cout << "Left shift c6 by 2: " << c7 << endl;
	cout << "Right shift c6 by 3: " << c8 << endl;
	cout << endl;
	system("pause");
	return 0;
}

int a, b;
void sort(int * array)
{
	for (int runs = 0; runs <= 9; runs++) {
		for (int i = 0; i <= 8; i++) {
			if (array[i] > array[i + 1]) {
				a = array[i];
				b = array[i + 1];
				array[i] = b;
				array[i + 1] = a;
			}
		}
	}
}
void shift() {
	c1 = 0x7FFF;
	c2 = 0x0F;
	c3 = ~c1;
	c4 = c1 & c2;
	c5 = c1 | c2;
	c6 = c1 ^ c2;
	c7 = c6 << 2;
	c8 = c7 >> 3;
}