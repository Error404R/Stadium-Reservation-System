#include<iostream>
#include <cstdlib> //null
#include <ctime> //time null
#include<fstream> //files
#include<time.h> // like ctime
#include<stdio.h> //scanf printf getch
#include<cmath> //pow
#include<string> //string
#include<map> //map
#include<iomanip>//hours and minutes
#include<conio.h> //getch
#include<windows.h>//date
#include <sstream>  // string streams

#define data mp[name]
#define EA Event[choice].A
#define EB Event[choice].B
#define EC Event[choice].C
#define ET Event[choice].tickets[code]
#define ll long long
int day, month;
using namespace std;
struct admin {
	string e_mail, pas;

};
struct user //user data
{
	string email, pass, date;
	string credit;
	string gender;
}; 
struct ev  //event data 
{
	string name;
	ll A[1000] = {}, B[1000] = {}, C[1000] = {};
	struct ticket
	{
		char clas;
		int seat;
		string name;
		int day;
		int month;
		int year;
	};
	map<ll, ticket>tickets;
};
map<string, admin>mp1; 
map<string, user>mp;
map<string, int>e_mail; // we use it for checking if the e-mail is taken or not 
map<int, ev>Event;
string LoginName;
int eventsnum = 0;
void wait(int);
void sign_up(string);
bool sign_in(string, int);
void preloading();
void preloading2();
void preloading3();
void reservation(int);
void Succesfully(ll[1000], int, char, int);
bool codeChecking(ll, int);
void date(ll, int);
void event_names();
void del(ll);
void userCancel();
void adminCancel();
bool unsuccesfull(int, ll[1000]);
bool signin(string, int);
void preloading4();
int main()
{
	SYSTEMTIME a; // to get the current date
	GetLocalTime(&a);
	day = a.wDay;
	month = a.wMonth;
	preloading();
	preloading2();
	preloading3();
	preloading4();

	first: // Goto statement
	system("CLS"); // to clear screen during runtime
	cout << "[U] User\n[A] Admin" << endl;
	bool login = false;
	char choice, cont;cin >> choice;
	system("CLS");
	if (choice == 'U')///user or admin
	{
		sign:
		do {
			cout << "[U] Sign UP\n[I] Sign In\n[B] Back\n[E] Exit" << endl;
			char signinup;	cin >> signinup; ///sign in or sign up

			system("CLS");
			if (signinup == 'B') goto first;
			else if (signinup == 'E') return 0;
			cout << "Name: ";
			string name;cin >> name;

			if (signinup == 'U')///sign up
				sign_up(name);
			if (signinup == 'I')///sign in
			{
				sign_in(name, 0); login = true;
			}
		
		} while (!login);
		if (login) // to choose from admin options
		{
			system("CLS");
			int option,choice;
			cout << "[1] Reserve Ticket" << endl;
			cout << "[2] Cancel Ticket" << endl;
			cout << "[3] Log Out" << endl;
			cout<< "[4] Exit" << endl;
			cin >> option;
			system("CLS");
			if(option==4)return 0;
		if(option==3) {
			login = false;
			goto sign; // to logout from the admin pannel
		}
			event_names();
			if (option == 1) {
	
			 cin >> choice;
				reservation(choice);
			}
			else if(option==2){
				
				userCancel();
			}
			
		
		}
	} 
	else
	{
		string name_of_admin;
		cout << "Name : ";
		cin >> name_of_admin;
		signin(name_of_admin, 0);login = true;
		while (true) {
			system("CLS");
			char cnt;int option;
			cout << "[1] Add Event" << endl;
			cout << "[2] Check Code" << endl;
			cout << "[3] Cancel Reservation" << endl;
			cout << "[4] Log Out" << endl;
			cout << "[5] Exit " << endl;

			cin >> option;
			system("CLS");
			if (option == 1)// add an event
			{
				int count = -1;
				for (map<int, ev>::iterator i = Event.begin();i != Event.end();i++)
					count++;
				cin.ignore();
				string x;
				getline(cin, x);
				Event[count++].name = x;
				ofstream outfile;
				outfile.open("events.txt", ios::app);
				outfile <<endl<< x << endl;

			}
			else if (option == 2)//Code Checking
			{
				do {
					event_names();
					bool valid = false;
					ll code;
					int choice;cin >> choice;
					cout << "Enter code: ";cin >> code;
					codeChecking(code, choice);

					cout << " Do You Want To Enter Another Ticket? " << endl;cin >> cnt;
				} while (cnt == 'y');
			}
			else if (option == 3) //ticket Cancelltion
			{
				event_names();
				adminCancel();
			}
			else if (option == 4) goto first;
			else return 0;
		}
	}
}
bool sign_in(string name, int c)
{
	cout << "Enter Password : ";
	char ch = _getch();
	int i = 0;
	bool verified = true;

	while (ch != '\r')
	{
		cout << '*'; // to hide the password
		if (i >= data.pass.size() || ch != data.pass[i++])          //checking the password verification
			verified = false;
		ch = _getch();
	}
	if (verified && i == data.pass.size())
	{
		cout << endl; LoginName = name; return true; // it link between current user and his data
	}
	else {

		cout << "\nThis is wrong password try again" << endl;
		c++;
		if (c >= 3) // to make a timer when we write the password 3 times wrong 
		{
			cout << " You entered wrong password for 3 times, you must wait 10 sec " << endl;
			for (char i = '9', z = 10; z > 0; z--, i--) // the time count down from 10 to 0
			{
				cout << i;
				wait(1);
				printf("\b");
			}

		}
	}
	sign_in(name, c);


}
void sign_up(string name)
{
	ofstream ofile;
	ofile.open("user data.txt", std::ios_base::app);
	while (data.pass != "") 
	{
		cout << "Sorry this username is taken try another username" << endl << "Name: "; cin >> name;
	}
	while (true)
	{

		cout << "E-mail:";
		cin >> mp[name].email;
		if (mp[name].email.find("@") != string::npos && mp[name].email.find(".com") != string::npos) // E-mail must be include  @     and     .com
			break;
		cout << "invalid E-mail please try again" << endl;

	}
	while (true) {
		cout << "Enter your e-mail: ";
		cin >> data.email;
		if (e_mail[data.email] == 0)break; // to check if the email is used before or not
		cout << "the email is already used ";
	}
	e_mail[data.email] = 1;
	cout << "Enter Password : ";
	char ch = _getch();
	while (ch != '\r') {
		cout << '*';
		data.pass += ch;       //hiding password of sign up
		ch = _getch();
	}
	cout << " \nEnter Birthdate : ";	cin >> data.date;
	cout << "Enter CreditCard Number : "; cin >> data.credit;
	cout << "Enter Gender : ";	cin >> data.gender;
	ofile << name << endl << data.email << endl << data.pass << endl << data.date << endl << data.credit << endl << data.gender << endl;

}
void preloading()
{
	ifstream infile;
	infile.open("user data.txt");
	string name;

	while (!infile.eof()) /// to enter the data of the user in the file
	{
		infile >> name;
		infile >> data.email >> data.pass >> data.date >> data.credit >> data.gender;
		e_mail[data.email] = 1;
	}
}
void preloading2()
{
	ifstream infile;
	infile.open("tickets.txt");
	while (!infile.eof())// to enter the data of the tickets in the file
	{
		int choice;
		ll code;
		infile >> choice; 
		infile >> code;
		infile >> ET.seat >> ET.clas >> ET.name >> ET.day >> ET.month >> ET.year;
		if (ET.clas == 'A')EA[ET.seat] = code;
		if (ET.clas == 'B')EB[ET.seat] = code;
		else EC[ET.seat] = code;

	}
}
void reservation(int choice) {

	char ch;
	ll code;
	int number;
	cout << "please enter which class you want (A,B or C)?" << endl; cin >> ch;
	cout << "enter the number of the seat you please" << endl; cin >> number;
	// ticket reservation
	if (ch == 'A') 
		if (EA[number] == 0) {
			Succesfully(EA, number, ch, choice); 
		}
		else
			while (!unsuccesfull(number, EA))
				number += 20;

	if (ch == 'B')
		if (EB[number] == 0) {
			Succesfully(EB, number, ch, choice);
		}
		else
			while (!unsuccesfull(number, EB))
				number += 20;
	if (ch == 'C')
		if (EC[number] == 0) {
			Succesfully(EC, number, ch, choice);
		}
		else
			while (!unsuccesfull(number, EC))
				number += 20;
	cout << "do you want another seat ?(y/n)" << endl; cin >> ch;
	if (ch == 'N' || ch == 'n')
		return;

	reservation(choice);
}
void Succesfully(ll arr[1000], int number, char ch, int choice)
{

	srand(time(0)); // to generate different number for every ticket
	ofstream outfile;
	outfile.open("tickets.txt", ios::app);
	ll code = rand() * rand(); // to generate a code for every ticket
	cout << " You have reserved this seat succesfuly " << endl;
	date(code, choice);
	cout << " your code generation is : " << code << endl;
	arr[number] = code;
	ET.seat = number;
	ET.clas = ch;
	ET.name = LoginName;
	outfile << choice <<endl<< code << endl << number << endl << ch << endl << LoginName << endl << ET.day << endl << ET.month << endl << ET.year << endl;
}
bool unsuccesfull(int num, ll arr[1000])
{

	for (int i = num + 1;i <= num + 21;i++)
	{
		if (arr[i] != 0) 
			return false;
	}
	cout << "this seat is already taken please choose another one from " << num + 1 << ":" << num + 21 << endl; // to show suggetions for near available seats
	return true;
}
void date(ll code, int choice)
{  // to generate the date of reservation in the ticket
	SYSTEMTIME a;
	GetLocalTime(&a);
	ET.day = a.wDay;
	ET.month = a.wMonth;
	ET.year = a.wYear;
	cout << " Your Date reservation is : " << ET.day << "/" << ET.month << "/" << ET.year << endl;

}
bool codeChecking(ll code, int choice)
{ // to check if the code of the ticket is true or not
	if (ET.seat != 0) {
		cout <<"Name: "<< ET.name <<endl<<"Match:"<<Event[choice].name<<endl ;
		cout <<  "Reserved Class: " << ET.clas << " Seat Number: " << ET.seat << endl;
		cout << " Your Date reservation is : " << ET.day << "/" << ET.month << "/" << ET.year << endl;
		del(code);
		return true;
	}
	cout << "Your Ticket is Invalid" << endl;
	return false;
}
void wait(int seconds)
{ 
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock()<endwait) {}
}
void preloading3()
{
	ifstream infile;
	infile.open("events.txt");
	int c = 0;
	while (!infile.eof()) // to enter new events in the file
	{		
		getline(infile , Event[c++].name);
	}
}
void event_names()
{    // to show the available events
	int count = 0;
	for (map<int, ev>::iterator i = Event.begin();i != Event.end();i++)
	{
		if (i->second.name == "")continue;
		cout << "[" << count++ << "]" << i->second.name << endl;
	}
	cout << "Please Choose an Event: ";
}
void del(ll code)
{   // to cancel a reservation
	ifstream del("tickets.txt");
	int num=0;
	string arr[1000];
	while (!del.eof())
	{
		del >> arr[num++];
	}
	
	for (int i = 0;i < num;i++)
	{
		ostringstream str;
		str << code;
		string cod = str.str();

		if (arr[i] == cod)
			arr[i] = "0";
	}
	del.close();
	ofstream in("tickets.txt");
	for (int i = 0;i < num;i++)
	{
		in << arr[i] << endl;
	}
}
void userCancel()
{
	int choice;ll code;
	cin >> choice;
	cout << "Enter the Code of The Ticket You Want to Cancel: ";
	cin >> code;
	if (Event[choice].tickets[code].name == LoginName && Event[choice].tickets[code].day == day && Event[choice].tickets[code].month == month)
		del(code); // to cancel the reserved ticket
	else {
		cout << "You Aren't Allowed To Cancel This Ticket" << endl;
	}
	cout << "Do You Want To Cancel Another Ticket? (Y/N)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'Y')
		userCancel();
	else return;

}
void adminCancel()
{
	int choice;cin >> choice;
	ll code;
	cout << "Enter the Code of The Ticket You Want to Cancel: ";
	cin >> code;
	cout << "Event: " << Event[choice].name << "\nName: " << ET.name << "\nClass: " << ET.clas << "\nSeat Number: " << ET.seat;

	cout << "\nYou're about to cancel the reservation are you sure (y/n) " << endl;
	char ticketchoice;
	cin >> ticketchoice;
	if (ticketchoice == 'Y' || ticketchoice == 'y')
		cout << "The ticket is cancelled " << endl;
	del(code);
	cout << "Do You Want To Cancel Another Ticket? (Y/N)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'Y')
		adminCancel();
	else return;
}
bool signin(string name_of_admin, int c) {
	cout << "Enter Password : ";
	char ch = _getch();
	int i = 0;
	bool verified = true;

	while (ch != '\r')
	{
		cout <<'*';
		if (i >= mp1[name_of_admin].pas.size() || ch != mp1[name_of_admin].pas[i++])          //checking the password verification
			verified = false;
		ch = _getch();
	}
	if (verified && i == mp1[name_of_admin].pas.size())
	{
		cout << endl; LoginName = name_of_admin; return true;
	}
	else {

		cout << "\nThis is wrong password try again" << endl;
		c++;
		if (c >= 3) {
			cout << " You entered wrong password for 3 times, you must wait 10 sec " << endl;
			for (char i = '9', z = 10; z > 0; z--, i--) {
				cout << i;
				wait(1);
				printf("\b");
			}

		}
	}
	signin(name_of_admin, c);




}
void preloading4(){

	ifstream infile;
	infile.open("admin.txt");
	while (!infile.eof()) // to save the data of the admin in file 
	{
		string name_of_admin;
		infile >> name_of_admin;
		mp1[name_of_admin].e_mail = name_of_admin;
		infile >> mp1[name_of_admin].pas;
	}
}