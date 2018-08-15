// EE120_Lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

int center;
int shift;
int set;
int final;
int n;

struct student{
	char name[20];
	char address[50];
	char id_no[10];
	bool full;
};
typedef struct student student1;

unsigned short middle(unsigned int a);
int bitcheck(int x);
int bitchange(int set, int x);
void insert(student *);
void del(student *);
void display(student *);

int main(){	
	unsigned int a = 0x12345678;
	cout << "Task #1A" << endl; //Start Task #1A
	cout << "Initial value in hex = " << hex << a << endl;
	middle(a);
	cout << "Middle value in hex = " << hex << center << endl;
	cout << endl;
	//////////////////////////////////////////////////////////
	cout << "Task #1B" << endl; //Start Task #1B
	int x;
	x = 13;
	cout << "Value of x in hex = " << x << endl;
	cout << "I am checking if the 2nd bit is set" << endl;
	bitcheck(x); //checks the 2nd bit
	if (set == 1){
		cout << "2nd bit is set" << endl;
	}
	else {
		cout << "2nd bit is not set" << endl;
		bitchange(set,x); //sets the second bit if it is not set
		cout << "New Value in hex = " << final << endl;
		cout << "Now the 2nd bit is set" << endl;
	}
	cout << endl;
	//////////////////////////////////////////////////////////
	cout << "________________________________________________" << endl;
	cout << "Task #2" << endl; //Start Task #2
	cout << endl;
	student addressbook[100];
	insert(addressbook); //gather data from console
	cout << endl;
	cout << "Summary of Information:" << endl;
	cout << "Name: " << addressbook[n].name << endl;
	cout << "Address: " << addressbook[n].address << endl;
	cout << "ID #: " << addressbook[n].id_no << endl;
	cout << "________________________________________________" << endl;
	cout << endl;
	del(addressbook); //return data from insert function is empty
	display(addressbook); // display summary of data
	cout << endl;
	system("pause");
	return 0;
}

unsigned short middle(unsigned int a){
	shift = a >> 8;
	center = 0x00FFFF & shift;
	return (center);
}

int bitcheck(int x){
	int check;
	check = x & 0x2;
	if (check != 0x2){
		set = 0;
	}
	else {
		set = 1;
	}
	return set;
}

int bitchange(int set, int x){
	final = x | 0x2;
	return final;
}

void insert(student * addressbook) {
	cout << "Choose Student Number (0-100): ";
	cin >> n;
	cout << "Type in name: ";
	cin >> addressbook[n].name;
	cout << "Type in Address: ";
	cin >> addressbook[n].address;
	cout << "Type in ID # ";
	cin >>addressbook[n].id_no;
	addressbook[n].full = true;
	return;
}

void del(student * addressbook) {
	addressbook[n].full = false;
	return;
}

void display(student * addressbook) {
	if (addressbook[n].full == false) {
		cout << "Data will now start deleting" << endl;
		cout << "..." << endl;
		cout << "..." << endl;
		cout << "..." << endl;
		cout << "Data has now been deleted" << endl;
	}
	return;
}