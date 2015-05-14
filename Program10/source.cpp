// Author: Zachary Mollett
// Assignment Number: 10


#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Customer
{
	string last_name;
	string first_name;
	string street_addr;
	string city;
	string state;
	string zipcode;
	char status;
};

Customer make_customer_record(string a); // function prototype for creating structure from file.
void rtrim(string &s); // function prototype for clearing extra spaces at end of strings.
int print_mail_list (Customer a[], char b, int x); // function prototype for printing mailing list by status (both file and screen).
int print_mail_list_zip (Customer a[], string b, int x); // function prototype for printing mailing list by zip (both file and screen).


int main(void)
{
	int num_records = 0, check= 0, menu;
	string line, zip;
	Customer customer_list[50];
	char choice1, choice2;

	ifstream clist;
	clist.open("customer.data");
	if (clist.fail())
	{
		cout << "File open failure." << endl; // Reads out an error message if file doesn't open.
		return -1; // exits program if failed.
	}

	while (!clist.eof()) // loops until end of file.
	{
		getline(clist, line); // grabs each line
		if (line.length() > 0)
		{
			customer_list[num_records] = make_customer_record(line); // sets each index of the structure array to a temp string then returns from function with structure.
			num_records++; // increases index after each loop.
		}
	}
	clist.close(); // closes the file when done.

	do
	{
		cout << "\n";
		cout << "Available Choices:" << endl;
		cout << "   1. Display mailing list on screen" << endl;
		cout << "   2. Write mailing list to file" << endl;
		cout << "   3. Quit" << endl;
		cout << "Enter the number of your choice: ";
		cin >> menu;
		
		if (menu == 3){return 0;} // exits program when menu 3 is chosen
	
		cout << "\n";
		cout << "A customer mailing list will be generated based on zip code or customer status." << endl;
		cout << "Enter your choice of Z for zip code, or S for status: ";
		cin >> choice1;
		
		if (choice1 == 's' || choice1 == 'S') // checks for user entered s or S for status.
		{
			cout << "Customer status:" << endl;
			cout << "   N - new customer" << endl;
			cout << "   I - infrequent customer" << endl;
			cout << "   F - frequent customer" << endl;
			cout << "   B - best customer" << endl;
	
			while (check != 1) // initial value is 0 so it will guarantee to runs at least once.
			{
				cout << "Enter the customer status for which to generate a mailing list: ";
				cin >> choice2;
				if (choice2 == 'n' || choice2 == 'N') // checks for letter n or N.
				{ 
					check=1; // sets check so loop will break.
					choice2 = 'N'; // sets choice to capital since the structure from file is all caps on status.
				}
				if (choice2 == 'i' || choice2 == 'I') // checks for letter i or I.
				{ 
					check=1; // sets check so loop will break.
					choice2 = 'I'; // sets choice to capital since the structure from file is all caps on status.
				}
				if (choice2 == 'f' || choice2 == 'F') // checks for letter f or F.
				{ 
					check=1; // sets check so loop will break.
					choice2 = 'F'; // sets choice to capital since the structure from file is all caps on status.
				}
				if (choice2 == 'b' || choice2 == 'B') // checks for letter b or B.
				{ 
					check=1; // sets check so loop will break.
					choice2 = 'B'; // sets choice to capital since the structure from file is all caps on status.
				}
			}
		
			print_mail_list(customer_list, choice2, menu); // calls the function to print either to file or screen based on status and menu selection.
		}
	
		if (choice1 == 'z' || choice1 == 'Z') // checks for user entered z or Z for zipcode.
		{
			do
			{
				cout << "Enter the 5 digit zipcode for which to generate the mailing list: ";
				cin >> zip;
			} while (zip.size() != 5); // will repeat if size of the entered zip code is not 5.
			
			print_mail_list_zip(customer_list, zip, menu); // calls the function to print either to file or screen based on zipcode entered and menu selection.
		
		}
	
	} while (menu >= 1 || menu <= 3); // loops so long as menu selection is 1, 2, or 3.
	 
	return 0;
}


Customer make_customer_record(string a)
{
	Customer temp_list;
	
	temp_list.last_name.assign(a,0,14); // assigns the structure contents of last_name to the first 14 characters of the string.
	rtrim(temp_list.last_name); // clears extra space at end of string.
	temp_list.first_name.assign(a,15,14); // assigns the structure contents of first_name to the next 14 characters of the string.
	rtrim(temp_list.first_name); // clears extra space at end of string.
	temp_list.street_addr.assign(a,30,29); // assigns the structure contents of street_addr to the next 29 characters of the string.
	rtrim(temp_list.street_addr); // clears extra space at end of string.
	temp_list.city.assign(a,60,19); // assigns the structure contents of city to the next 19 characters of the string.
	rtrim(temp_list.city); // clears extra space at end of string.
	temp_list.state.assign(a,80,2); // assigns the structure contents of state to the next 2 characters of the string.
	rtrim(temp_list.state); // clears extra space at end of string.
	temp_list.zipcode.assign(a,82,5); // assigns the structure contents of zipcode to the next 5 characters of the string.
	rtrim(temp_list.zipcode); // clears extra space at end of string.
	a.copy(&temp_list.status,1,87); // assigns the structure contents of first_name to the last character of the string.
	
	return temp_list; // returns the entire structure.
}

void rtrim(string &s)
{
s.erase(s.find_last_not_of(" \n\r\t") + 1); // clears extra space at end of string.
}

int print_mail_list (Customer a[], char b, int x)
{
	
	if (x == 1) // checks for menu selection.
	{
		cout << "\n";
		cout << "The mailing list matching your selection is: " << endl;
		cout << "\n";
		for (int i = 0; i < 50; i++) // loops 50 times.
		{
			if (a[i].status == b) // checks that the user entered status matches the contents of the status char in structure.
			{
				cout << a[i].first_name << " " << a[i].last_name << ", " << a[i].street_addr << ", " << a[i].city << " " << a[i].state << " " << a[i].zipcode << endl; // prints to screen.
			}
		}
	}

	if (x == 2) // checks for menu selection.
	{
		ofstream mail;
		mail.open("mail.list");
		if(mail.fail())
		{
			return -1;
		}

		for (int i = 0; i < 50; i++) // loops 50 times.
		{
			if (a[i].status == b) // checks that the user entered status matches the contents of the status char in structure.
			{
			mail << a[i].first_name << " " << a[i].last_name << ", " << a[i].street_addr << ", " << a[i].city << " " << a[i].state << " " << a[i].zipcode << endl; // prints to file.
			}
		}
		mail.close(); // closes the file when done.
	
		cout << "Mailing list matching your selection was generated and saved in the file: mail.list." << endl;
	}	
	
	return 0;
}

int print_mail_list_zip (Customer a[], string b, int x)
{

	if (x == 1) // checks for menu selection.
	{
		cout << "\n";
		cout << "The mailing list matching your selection is: " << endl;
		cout << "\n";
		for (int i = 0; i < 50; i++) // loops 50 times.
		{
			if (b.compare(a[i].zipcode) == 0) // compares user entered zipcode to contents in string zipcode in structure, if matches will execute.
			{
				cout << a[i].first_name << " " << a[i].last_name << ", " << a[i].street_addr << ", " << a[i].city << " " << a[i].state << " " << a[i].zipcode << endl; // prints to screen.
			}
 
		}
	}

	if (x == 2) // checks for menu selection.
	{
		ofstream mail;
		mail.open("mail.list");
		if(mail.fail())
		{
			return -1;
		}

		for (int i = 0; i < 50; i++) // loops 50 times.
		{
			if (b.compare(a[i].zipcode) == 0) // compares user entered zipcode to contents in string zipcode in structure, if matches will execute.
			{
			mail << a[i].first_name << " " << a[i].last_name << ", " << a[i].street_addr << ", " << a[i].city << " " << a[i].state << " " << a[i].zipcode << endl; // prints to file.
			}
		}
		mail.close(); // closes the file when done.
	
		cout << "Mailing list matching your selection was generated and saved in the file: mail.list." << endl;
	}	
	
	return 0;
}

