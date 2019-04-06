/*
============================================================================
Name 	    : main.cpp
Author 	    : Aaron Shehan
Version     : 1.0.0
Copyright   : 2018
Description : This program allows the user to manage a library system.
============================================================================
*/

#include "my_header.h"

int number_of_students()
{
	string line;int count=0;
	ifstream fin;fin.open("students.txt");
	while(getline(fin, line))
	{
		++count;
	}
	return count;
}

int number_of_books()
{
	string line;int count=0;
	ifstream fin;fin.open("books.txt");
	while(getline(fin, line))
	{
		++count;
	}
	return count;
}

/*
============================================================================
Function    : search_by_author
Parameters  : NA
Return	    : NA
Description : This function allows the user to search the books.txt file for a specific author. It will take
take in partial input values and output all books that match the users input.
============================================================================
*/

void search_by_author()
{
	string bkAuthor;	// stores user input for author to be searched by
	ifstream in_stream;
	int totalBooks = number_of_books(); // variable to hold number of books in order to control loops
	Book* bkInfo;		// array of structures to for information in books.txt file
	bkInfo = new Book[totalBooks];
	int strCmp;		// used when comparing string values of user input and and books.txt file



	cout << "Enter the name of the author you would like to search for: "; cin >> bkAuthor;	
	

	in_stream.open("books.txt");	

	for (int i = 0; i < totalBooks; ++i)
		{
			getline(in_stream,bkInfo[i].author,'\t');
			getline(in_stream,bkInfo[i].title,'\t');
			in_stream >> bkInfo[i].ISBN >> bkInfo[i].EUID;
			in_stream >> bkInfo[i].borrowed.month >> bkInfo[i].borrowed.day >> bkInfo[i].borrowed.time;
		}
	in_stream.close();

	for (int i = 0; i < totalBooks; ++i)
		{
			strCmp = bkInfo[i].author.find(bkAuthor); // stores value for index of string match

			if (strCmp != string::npos) // If string match found, outputs information stored in structure array
			{
				cout << bkInfo[i].author << "\t" << bkInfo[i].title << "\t";
				cout << bkInfo[i].ISBN << "\t" << bkInfo[i].borrowed.month << "\t" ;
				cout << bkInfo[i].borrowed.day << "\t"<< bkInfo[i].borrowed.time << endl;

			}
		}		
	delete []bkInfo;
}

/*
============================================================================
Function    : search_by_title
Parameters  : NA
Return	    : NA
Description : This function allows the user to search the books.txt file for a specific book. It will take
take in partial input values and output all books that match the users input.
============================================================================
*/

void search_by_title()
{
	string bkTitle; // stores user input for title to be searched by

	ifstream in_stream;
	int totalBooks = number_of_books(); // variable to hold number of books in order to control loops
	Book* bkInfo; // array of structures to for information in books.txt file
	bkInfo = new Book[totalBooks];
	int strCmp; // used when comparing string values of user input and and books.txt file



	cout << "Enter the title of the book you would like to search for: "; cin >> bkTitle;	
	

	in_stream.open("books.txt");	

	for (int i = 0; i < totalBooks; ++i)
		{
			getline(in_stream,bkInfo[i].author,'\t');
			getline(in_stream,bkInfo[i].title,'\t');
			in_stream >> bkInfo[i].ISBN >> bkInfo[i].EUID;
			in_stream >> bkInfo[i].borrowed.month >> bkInfo[i].borrowed.day >> bkInfo[i].borrowed.time;
		}
	in_stream.close();

	for (int i = 0; i < totalBooks; ++i)
		{
			strCmp = bkInfo[i].title.find(bkTitle);

			if (strCmp != string::npos)
			{
				cout << bkInfo[i].author << "\t" << bkInfo[i].title << "\t";
				cout << bkInfo[i].ISBN << "\t" << bkInfo[i].borrowed.month << "\t" ;
				cout << bkInfo[i].borrowed.day << "\t"<< bkInfo[i].borrowed.time << endl;

			}
		}		
	delete []bkInfo;
}

/*
============================================================================
Function    : search_by_student
Parameters  : NA
Return	    : NA
Description : This function allows the user to search for an EUID. When the EUID is found it will
output the amount of books borrowed.
============================================================================
*/

void search_by_student()
{
	string stEUID; // stores user input for EUID to compare with EUIDs in students.txt file
	ifstream in_stream;
	int numStudents = number_of_students(); // for number of students in students.txt file
	int totalBooks = number_of_books(); // for number of books in books.txt file
	Book bkInfo; // structure for information in books.txt file
	Student stInfo; // structure for information in students.txt file
	int index = 0; // used to store location of EUID 
	bool nobooksBorrowed = false; // used this to know if function needs to continue, when true the function will not continue
	

	cout << "Enter EUID: "; cin >> stEUID;

	in_stream.open("students.txt");

	for (int i = 0; i < numStudents; ++i)
	{
		in_stream >> stInfo.EUID >> stInfo.numBooks;
		
		if (stInfo.EUID == stEUID) // ends loop when EUID found
		{
			break;
		}
	}
	
	in_stream.close();

	
	if (stInfo.numBooks == 0)
	{
		nobooksBorrowed = true;
		cout << "This student has not borrowed any books." << endl;
	}

	if (nobooksBorrowed == false)
	{
		stInfo.ISBN = new long int[stInfo.numBooks];
		in_stream.open("books.txt");

		for (int i = 0; i < totalBooks; ++i)
		{
			getline(in_stream,bkInfo.author,'\t');
			getline(in_stream,bkInfo.title,'\t');
			in_stream >> bkInfo.ISBN >> bkInfo.EUID;
			in_stream >> bkInfo.borrowed.month >> bkInfo.borrowed.day >> bkInfo.borrowed.time;

			if (bkInfo.EUID == stEUID)
			{
				 stInfo.ISBN[index] = bkInfo.ISBN;
				++index;
			}
		}
		
		cout << "The student has has borrowed: ";
		for (int i = 0; i < index; ++i)
		{
			cout << stInfo.ISBN[i] << endl;
		}
		in_stream.close();
		delete []stInfo.ISBN;
	}

}

/*
============================================================================
Function    : check_out
Parameters  : NA
Return	    : NA
Description : This function allows the user to enter a books ISBN number to borrow it.
This function also updates the the student.txt file by adding one to the total number
of books borrowed for the selected EUID. It also updates the books.txt file by updating 
the EUID and date for the selected book.
============================================================================
*/

void check_out()
{
	int numStudents = number_of_students(); // stores number of students in students.txt file
	int totalBooks = number_of_books(); // stores number of books in books.txt file
	Student* stInfo; // will be an array of structures containing informatin in students.txt file
	stInfo = new Student[numStudents];
	Book* bkInfo; // will be array of structures containing information in books.txt file
	bkInfo = new Book[totalBooks];
	string stEUID; // for user input for EUID
	long int bkISBN; // for user input for ISBN
	bool bookMatch = false; // when true, books.txt will be updated
	bool euidMatch = false; // true when EUID match found
	int index = -1; // index used when updating student.txt file
	int month, day, year; // used to get current date

	cout << "Enter EUID: "; cin >> stEUID;

	ifstream in_stream;
	ofstream out_stream;

	in_stream.open("students.txt");

	for (int i = 0; i < numStudents; ++i)
	{
		in_stream >> stInfo[i].EUID >> stInfo[i].numBooks;
	}
	
	in_stream.close();

	for (int i = 0; i < numStudents; ++i)
	{
		if (stInfo[i].EUID == stEUID)
		{
			euidMatch = true;
			if (stInfo[i].numBooks < 5)
			{
				index = i;
				cout << "Enter the ISBN of the book you wish to check out: "; 
				cin >> bkISBN;
				break;
			}
			else
			{
				cout << "The student has already borrowed 5 books." << endl;
				break;
			}
		}

	}

	if (euidMatch == false)
	{
		cout << "Could not find EUID." << endl;
	}


	if (euidMatch == true)
	{
		in_stream.open("books.txt");
		out_stream.open("students.txt");

		for (int i = 0; i < numStudents; ++i)
		{
			if (i != index)
			{
				out_stream << stInfo[i].EUID << "\t" << stInfo[i].numBooks;
			}
			else
			{
				out_stream << stInfo[i].EUID << "\t" << stInfo[i].numBooks + 1; 
			}
			out_stream << endl;
		}
		out_stream.close();		
		
		for (int i = 0; i < totalBooks; ++i) // gathering information from books.txt file
		{
			getline(in_stream,bkInfo[i].author,'\t');
			getline(in_stream,bkInfo[i].title,'\t');
			in_stream >> bkInfo[i].ISBN >> bkInfo[i].EUID;
			in_stream >> bkInfo[i].borrowed.month >> bkInfo[i].borrowed.day >> bkInfo[i].borrowed.time;
			
			if (bkInfo[i].ISBN == bkISBN) // finds location of ISBN match
			{
				bookMatch = true;
				index = i;
			}
		}
		in_stream.close();
	}

	if (bookMatch == true)
	{
		get_date(month, day, year);

		out_stream.open("books.txt");
		
		for (int i = 0; i < totalBooks; ++i)
		{
			if (i != index) // outputs original data
			{
				out_stream << bkInfo[i].author << "\t" << bkInfo[i].title << "\t\t\t" << bkInfo[i].ISBN << "\t" << bkInfo[i].EUID << "\t";
				out_stream << bkInfo[i].borrowed.month << "\t" << bkInfo[i].borrowed.day << "\t" << bkInfo[i].borrowed.time;
			}
			else // updates data with new EUID
			{
				out_stream << bkInfo[i].author << "\t" << bkInfo[i].title << "\t\t\t" << bkInfo[i].ISBN << "\t" << stEUID << "\t";
				out_stream << month << "\t" << day << "\t" << year;
			}
			//out_stream << endl;
		}
		out_stream.close();
	}
	delete []stInfo;
	delete []bkInfo;
}

/*
============================================================================
Function    : return_book
Parameters  : NA
Return	    : NA
Description : This function allows the user to return a book by entering its ISBN number. In doing so,
it updates the students.txt file by subtracing one from the total books borrowed for the selected EUID.
============================================================================
*/

void return_book()
{
	long int bkISBN; // user input for ISBN to compare with ISBNs in books.txt file
	int totalBooks = number_of_books(); // stores value for number of books in books.txt file
	int numStudents = number_of_students(); // value for number of students in students.txt file
	Book* bookInfo; // will be an array of structures containing information from books.txt file
	bookInfo = new Book[totalBooks];
	Student* stInfo; // will be an array of structures containg information from students.txt file
	stInfo = new Student[numStudents];
	int month = 0, day = 0, year = 0; // used to update date in books.txt file
	bool bookMatch = false; // used when book match is found to continue function
	int index; // for location of ISBN to be returned in books.txt file
	int index2; // used to find EUID match between students.txt file and books.txt file
	ifstream in_stream;
	ofstream out_stream;
	
	cout << "Enter the ISBN of the book you would like to return: "; cin >> bkISBN;

	in_stream.open("books.txt");

	for (int i = 0; i < totalBooks; ++i)
		{
			getline(in_stream,bookInfo[i].author,'\t');
			getline(in_stream,bookInfo[i].title,'\t');
			in_stream >> bookInfo[i].ISBN >> bookInfo[i].EUID;
			in_stream >> bookInfo[i].borrowed.month >> bookInfo[i].borrowed.day >> bookInfo[i].borrowed.time;
		}
	in_stream.close();

	for (int i = 0; i < totalBooks; ++i)
	{
		if (bookInfo[i].ISBN == bkISBN) // searches for ISBN match
		{
			bookMatch = true;
			index = i;
			break;
		}
	}
		
	if (bookMatch == false)
	{
		cout << "This book does not belong to the libray." << endl;
	}
	
		
	if (bookMatch == true)
	{
		out_stream.open("books.txt");

		for (int i = 0; i < totalBooks; ++i)
		{
			if (i != index)
			{
				out_stream << bookInfo[i].author << "\t" << bookInfo[i].title << "\t" << bookInfo[i].ISBN << "\t" << bookInfo[i].EUID << "\t";
				out_stream << bookInfo[i].borrowed.month << "\t" << bookInfo[i].borrowed.day << "\t" << bookInfo[i].borrowed.time;
			}
			else
			{
				out_stream << bookInfo[i].author << "\t" << bookInfo[i].title << "\t" << bookInfo[i].ISBN << "\t" << "NA" << "\t";
				out_stream << month << "\t" << day << "\t" << year;
			}
			//out_stream << endl;
		}
		out_stream.close();
	} 

	
	if (bookMatch == true)
	{

		in_stream.open("students.txt");

		for (int i = 0; i < numStudents; ++i)
		{
			in_stream >> stInfo[i].EUID >> stInfo[i].numBooks;
			
			if (stInfo[i].EUID == bookInfo[index].EUID)
			{
				index2 = i;
			}
		}

	
		in_stream.close();
		out_stream.open("students.txt");

		for (int i = 0; i < numStudents; ++i)
		{
			if (i != index2)
			{
				out_stream << stInfo[i].EUID << "\t" << stInfo[i].numBooks;
			}
			else
			{
				out_stream << bookInfo[index].EUID << "\t" << stInfo[i].numBooks - 1;
			}
			out_stream << endl;
		}
		out_stream.close();			
	} 
	delete []stInfo;
	delete []bookInfo; 

}

/*
============================================================================
Function    : enter_book
Parameters  : NA
Return	    : NA
Description : This function allows the user to add a book to the books.txt file.
============================================================================
*/

void enter_book()
{
	Book bookInfo; // structure of information in books.txt file
	ofstream out_stream;

	cout << "Enter name of author: "; getline(cin,bookInfo.author);
	cout << "Enter title of the book: "; getline(cin,bookInfo.title);
	cout << "Enter the ISBN: "; cin >> bookInfo.ISBN;

	bookInfo.EUID = "NA"; // default value
	bookInfo.borrowed.month = 0; // default value
	bookInfo.borrowed.day = 0; // default value
	bookInfo.borrowed.time = 0; // default value

	out_stream.open("books.txt",ios::app); // appends new book to books.txt file

	out_stream << bookInfo.author << "\t" << bookInfo.title << "\t\t" << bookInfo.ISBN;
	out_stream << "\t" << bookInfo.EUID << "\t" << bookInfo.borrowed.month << "\t";
	out_stream << bookInfo.borrowed.day << "\t" << bookInfo.borrowed.time << endl;

	out_stream.close();
}

void search_book()
{
	cout<<"What do you want to search with?"<<endl;
	cout<<"1. Author"<<endl;
	cout<<"2. Title"<<endl;
	cout<<"3. Student"<<endl;
	cout<<"Enter your choice:";
	int choice;
	cin>>choice;
	cin.ignore();
	bool success=false;
	do
	{
		switch(choice)
		{
		case 1:
			search_by_author();
			success=true;
			break;	
		case 2:
			search_by_title();
			success=true;
			break;
		case 3:
			search_by_student();
			success=true;
			break;
		default:
			cout<<"Wrong choice. Enter again.";
			success=false;
			break;
		}
	}while(!success);
}

int main()
{

	int choice;
	
	bool success;
	do
	{
	cout<<"1. Add"<<endl;

	cout<<"2. Check Out"<<endl;
	
	cout<<"3. Return"<<endl;
	
	cout<<"4. Search"<<endl;
	
	cout<<"Enter your choice, 0 to Quit:";
	
	
	cin>>choice;
	cin.ignore();
		do
		{
			switch(choice)
			{
			case 1:
				enter_book();
				success=true;
				break;
			case 2:
				check_out();
				success=true;
				break;
			case 3: 
				return_book();
				success=true;
				break;
			case 4: 
				search_book();
				success=true;
				break;
			default:
				cout<<"Wrong Choice. Enter again";
				success=false;
				break;
			}
		}while(!success);
	}while(choice!=0);
	return 0;
}




	
