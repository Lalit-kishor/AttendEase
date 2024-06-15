// C++ Program to implement student Attendence Management 
// System 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <fstream> 
#include <iostream> 
#include <string> 

using namespace std; 

// Function prototypes 
void mainmenu(); 
void adminLogin(); 
void studentlogin(); 
void adminMenu(); 
void creatAdminAccount(); 
void createStudentFile(); 
void initilizeAdminIdPass(); 
void insertionsort(); 
int isfileexist(string); 
void markAttendence(); 
void attendenceStatus(string); 
void attendencelist(); 

// Class to handle admin actions 
class admin { 
	string username, password, rPassword; 

public: 
	void checkPasswordMatch() 
	{ 
		int passwordMatchStatus 
			= password.compare(rPassword); 
		if (passwordMatchStatus != 0) { 
			cout << "\n\t\tPasswords are not matching. "
					"Re-enter the password\n"; 
			getUserNameAndPasswordOfAdmin(); 
		} 
	} 

	// implementing password constrains 
	int passwordformat() 
	{ 
		int digit = 0, character = 0, splChar = 0, i = 0, 
			len = password.size(); 

		if (password.size() < 8) { 
			cout<<"\n\t\t\tPassword is too short\n"; 
			return 0; 
		} 
		if (password.size() > 20) { 
			cout<<"\n\t\t\tPassword is too long"; 
			return 0; 
		} 

		for (i = 0; i < len; i++) { 
			if (password[i] >= 'A' && password[i] <= 'Z') { 
				character = 1; 
			} 
			if (password[i] == '@' || password[i] == '&'
				|| password[i] == '_' || password[i] == '*'
				|| password[i] == '(' || password[i] == ')'
				|| password[i] == '#' || password[i] == '$'
				|| password[i] == '^' || password[i] == '.'
				|| password[i] == ',') { 
				splChar = 1; 
			} 
			if (isdigit(password[i])) 
				digit = 1; 
		} 
		if (digit && splChar && character) { 
			return 1; 
		} 
		else { 
			printf("\nPassword should contain at least one "
				"uppercase letter, one digit, and one "
				"special character ('@', '#', '$', '^', "
				"'&', '*', '(', ')', '.', ',')"); 
			return 0; 
		} 
	} 

	void getUserNameAndPasswordOfAdmin() 
	{ 
		cout << "\n\t\t\tEnter username: "; 
		cin >> username; 
		cout << "\n\t\t\tEnter password: "; 
		cin >> password; 
		while (!passwordformat()) { 
			cout << "\n\t\t\tEnter password: "; 
			cin >> password; 
		} 
		cout << "\n\t\t\tRe-enter password: "; 
		cin >> rPassword; 
		cout << endl; 
		checkPasswordMatch(); 
	} 

	string returnAdminUsername() { return username; } 

	string returnAdminPassword() { return password; } 
}; 

// Class to handle student actions 
class student { 
	// variable to store name and university serial number 
	string rollNo, name; 

public: 
	void readStudentData() 
	{ 
		cout << "\n\t\t\tEnter student name: "; 
		cin >> name; 
		cout << "\n\t\t\tEnter Roll No: "; 
		cin >> rollNo; 
	} 

	string getRollNo() { return rollNo; } 

	string getName() { return name; } 
}; 

// creating a file with admin credentials 
void createAdminAccount() 
{ 
	admin a; 
	a.getUserNameAndPasswordOfAdmin(); 
	string username, password; 
	username = a.returnAdminUsername(); 
	password = a.returnAdminPassword();
	
	fstream f; 
	f.open("AdminAccount.txt", ios::app); 
	
	if (!f.is_open()) {
        cerr << "Error opening file!" << endl;
    }
    
	f << username << "\t" << password << "\n";
	
	if (f.fail()) {
        cerr << "Error writing to file!" << endl;
        f.close(); // Close the file if it's open
    }
    
	f.close(); 
	cout << "\n\t\t\tAccount created successfully\n"; 
} 

// function to initialize the admin file if it does not 
// exists 
void initilizeAdminIdPass() 
{ 
	fstream f; 
	int fileStatus = isfileexist("AdminAccount.txt"); 
	if (fileStatus) { 
		f.open("AdminAccount.txt", ios::out); 
		f << "admin\tadmin\n"; 
		f.close(); 
	} 
} 

// function to help in admin in logging in 
void adminLogin() 
{ 
	initilizeAdminIdPass(); 
	int success_flag = 0; 
	cout << "\n\n------------------------ ADMIN LOGIN "
			"------------------------\n"; 
	string username, fUsername, fPassword; 
	string password; 
	cout << "\n\t\t\tEnter username : "; 
	cin >> username; 
	cout << "\n\t\t\tEnter password : "; 
	cin >> password; 
	fstream f; 
	f.open("AdminAccount.txt", ios::in); 
	while (f) { 
		f >> fUsername >> fPassword; 
		if (username.compare(fUsername) == 0 
			&& password.compare(fPassword) == 0) { 
			cout << "\n\t\t\tLogin successful!!!\n"; 
			success_flag = 1; 
			adminMenu(); 
			f.close(); 
			break; 
		} 
	} 

	// if login is failed. 
	if (success_flag == 0) { 
		f.close(); 
		cout << "\n\t\tError! Invalid Credentials. Please "
				"Try Again\n"; 
	} 
} 

// function for admin dashboard 
void adminMenu() 
{ 
	int choice; 
	for (;;) { 
		cout << "\n ------------------------ ADMIN MENU "
				"------------------------\n"; 
		cout << "\n\t\t\t1.Mark attendance\n\t\t\t2.Add "
				"students\n\t\t\t3.Create new admin "
				"account\n\t\t\t4.Student attendance "
				"list\n\t\t\t5.Main "
				"menu\n\t\t\t0.Exit\n\n\t\t\tEnter your "
				"choice..."; 
		cin >> choice; 
		switch (choice) { 
		case 0: 
			exit(0); 
		case 1: { 
			markAttendence(); 
			break; 
		} 
		case 2: { 
			createStudentFile(); 
			break; 
		} 
		case 3: { 
			createAdminAccount(); 

			break; 
		} 
		case 4: { 
			attendencelist(); 
			break; 
		} 
		case 5: { 
			mainmenu(); 
			break; 
		} 
		} 
	} 
} 

// creating a file to store student data 
void createStudentFile() 
{ 
	student s; 
	int year, month, day, pa; 
	s.readStudentData(); 
	string rollNo, name; 
	rollNo = s.getRollNo(); 
	name = s.getName(); 
	string filename = rollNo + ".txt"; 
	
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	pa = 2;
	
	if (!isfileexist(filename)) { 
		cout << "\n\t\t\tStudent already enrolled\n"; 
	} 
	else { 
		fstream seperatef, commonf, rollNof; 
		seperatef.open(filename, ios::out); 
		seperatef << rollNo << "\t" << name << "\t" << pa 
				<< "\t" << day << "\t" << month << "\t"
				<< year << "\n"; 
				
		commonf.open("studentlist.txt", ios::app); 
		commonf << rollNo << "\t" << name << "\n";
		
		rollNof.open("rollNoFile.txt", ios::app); 
		rollNof << rollNo << "\n"; 
		commonf.close(); 
		rollNof.close(); 
		seperatef.close();
		
		cout << "\n\t\tStudent successfully added to the "
				"list\n"; 
	} 
	insertionsort(); 
} 

// function to mark attendence with date 
void markAttendence() 
{ 
	string filename, rollNo, name; 
	int pa, day, month, year; 
	
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	
	cout << "\n\t\t\tEnter 1 for present and 0 for "
			"absent\n\n"; 
	fstream sfile, rollNofile; 
	sfile.open("studentlist.txt", ios::in); 

	while (sfile >> rollNo >> name) { 
		filename = rollNo + ".txt"; 
		rollNofile.open(filename, ios::app); 
		cout << "\t\tUniversity Number: " << rollNo 
			<< "\tName: " << name << "\t"; 
		cin >> pa; 
		rollNofile << rollNo << "\t" << name << "\t" << pa << "\t"
				<< day << "\t" << month << "\t" << year 
				<< "\n"; 
		rollNofile.close(); 
	} 

	cout << "\n\t\t\tAll attendance marked\n"; 
	sfile.close(); 
} 

// utility function to check whether the file with the given 
// name exists 
int isfileexist(string filename) 
{ 
	fstream f; 
	f.open(filename, ios::in); 
	if (f) { 
		f.close(); 
		return 0; 
	} 
	f.close(); 
	return 1; 
} 

// insertion sort implementation 
void insertionSortRecursive(string arr[], int n) 
{ 
	if (n <= 1) 
		return; 

	insertionSortRecursive(arr, n - 1); 
	string last = arr[n - 1]; 
	int j = n - 2; 

	while (j >= 0 && arr[j] > last) { 
		arr[j + 1] = arr[j]; 
		j--; 
	} 
	arr[j + 1] = last; 
} 

// sorting rollNo file according to university serial number 
// number 
void insertionsort() 
{ 
	int i, j, n = 0; 
	string k; 
	string rollNoarray[150]; 
	fstream rollNof; 
	rollNof.open("rollNoFile.txt"); 
	while (rollNof >> rollNoarray[n++]) 
		; 
	rollNof.close(); 
	insertionSortRecursive(rollNoarray, n); 
	rollNof.open("rollNoFile.txt"); 
	for (i = 0; i <= n; i++) { 
		rollNof << rollNoarray[i] << "\n"; 
	} 
	rollNof.close(); 
} 

// function to print attendence list 
void attendencelist() 
{ 
	string rollNo, name; 
	int totaldays = 0, p = 0, a = 0, flag = 0, pa, day, 
		month, year; 
	float per = 0.0; 
	fstream sepf, rollNof; 
	rollNof.open("rollNoFile.txt", ios::in); 
	while (rollNof >> rollNo) { 
		flag = 0; 
		p = 0; 
		a = 0; 
		per = 0; 
		totaldays = 0; 
		rollNo = rollNo + ".txt"; 
		sepf.open(rollNo, ios::in); 
		while (sepf >> rollNo >> name >> pa >> day >> month 
			>> year) { 
			if (flag == 0) { 
				cout << "\n\n\tUniversity Number:" << rollNo 
					<< "\t"
					<< "Name: " << name << endl; 
				flag = 1; 
				continue; 
			} 
			totaldays++; 
			if (pa == 1) 
				p++; 
			else
				a++; 
		} 
		sepf.close(); 
		per = ((float)p / totaldays) * 100; 
		cout << "\tPresent:" << p << "\tAbsent:" << a 
			<< "\tAttendance percentage:" << per << endl; 
	} 
	rollNof.close(); 
} 

// function to check attendence status 
void attendenceStatus(string filename) 
{ 
	fstream f, rollNofile; 
	string rollNo, name, rollNofilename; 
	int pa, day, month, year, pcount, acount, 
		totaldays = 0, p = 0, a = 0, flag = 0; 
	float per = 0.0; 

	rollNofile.open(filename, ios::in); 
	while (rollNofile >> rollNo >> name >> pa >> day >> month 
		>> year) { 
		if (flag == 0) { 
			cout << "\n\tName:" << name 
				<< "\tUniversity Number:" << rollNo << endl; 
			flag = 1; 
			continue; 
		} 
		totaldays++; 
		if (pa == 1) { 
			p++; 
			cout << "\t" << day << "-" << month << "-"
				<< year << "\tPresent\n"; 
		} 
		else { 
			a++; 
			cout << "\t" << day << "-" << month << "-"
				<< year << "\tAbsent\n"; 
		} 
	} 
	rollNofile.close(); 
	per = ((float)p / totaldays) * 100; 

	cout << "\n\n\tPresent:" << p << "\tAbsent:" << a 
		<< "\tAttendance percentage:" << per << endl 
		<< endl; 
} 

// student login page 
void studentlogin() 
{ 
	; 
	cout << "\n ------------------------ STUDENT MENU "
			"------------------------\n"; 
	string password, username, fUsername, fPassword; 
	int successf = 0; 
	cout << "\n\t\t\tEnter username : "; 
	cin >> username; 
	cout << "\n\t\t\tEnter password : "; 
	cin >> password; 
	string filename = password + ".txt"; 
	ifstream sflogin; 
	sflogin.open("studentlist.txt"); 
	while (sflogin >> fUsername) { 
		if (password.compare(fUsername) == 0 
			&& username.compare(fUsername) == 0) { 
			successf = 1; 
			attendenceStatus(filename); 
			sflogin.close(); 
			break; 
		} 
	} 
	if (successf == 0) { 
		sflogin.close(); 
		cout << "\n\t\t\t Error ! Invalid Credentials.."; 
	} 
	sflogin.close(); 
} 

// main menu 
void mainmenu() 
{ 
	int choice; 
	while (1) { 
		cout << "\n\n ------------------ Welcome to "
				"Attendence Management System "
				"------------------\n"; 
		cout << "\n\t\t\t1.Student login\n\t\t\t2.Admin "
				"login\n\t\t\t0.Exit\n\n\t\t\tEnter your "
				"choice... "; 
		cin >> choice; 
		switch (choice) { 
		case 0: 
			exit(0); 
		case 1: 
			studentlogin(); 
			break; 
		case 2: 
			adminLogin(); 
			break; 

		default: 
			cout << "Invalid Option! Pease Try Again.\n"; 
		} 
	} 
} 

// driver code 
int main() 
{ 
	mainmenu(); 
	return 0; 
}
