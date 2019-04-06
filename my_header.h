#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;
void get_date(int &m, int &d, int &y);

struct Date
{
	int month;
	int day;
	int time;
};

struct Student
{
	string EUID;
	int numBooks;
	long int* ISBN;
};

struct Book
{
	string author;
	string title;
	string EUID;
	long int ISBN;
	Date borrowed;
};