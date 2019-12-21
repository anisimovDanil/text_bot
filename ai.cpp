#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <windows.h>
#include <algorithm>

using namespace std;

void search();

//==================================================================================================================================================
//										            	МАТЕМАТИЧЕСКИЕ ИСЧИСЛЕНИЯ
//==================================================================================================================================================
bool operation(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

long prioritet(char op) {
	if (op < 0) return 3;
	else {
		if (op == '+' || op == '-')return 1;
		else if (op == '*' || op == '/')return 2;
		else if (op == '^')return 4;
		else return -1;
	}
}

void action(vector<long> &value, char op) {
	if (op < 0) {                            
		long unitar = value.back();
		value.pop_back();
		if (-op == '-')value.push_back(-unitar);
	}
	else {                              
		long right = value.back();
		value.pop_back();
		long left = value.back();
		value.pop_back();
		if (op == '+')value.push_back(left + right);
		else if (op == '-')value.push_back(left - right);
		else if (op == '*')value.push_back(left*right);
		else if (op == '/')value.push_back(left / right);
		else if (op == '^')value.push_back(pow(left, right));
	}
}

long calculus(string &Input) {
	bool unary = true;        
	vector<long>value;        
	vector<char>op;           
	for (int i = 0; i < Input.size(); i++) {
		if (Input[i] == '(') {    
			op.push_back('(');
			unary = true;
		}
		else if (Input[i] == ')') {
			while (op.back() != '(') {  
				action(value, op.back());
				op.pop_back();
			}
			op.pop_back();
			unary = false;
		}
		else if (operation(Input[i])) { 
			char zn = Input[i];
			if (unary == true)zn = -zn; 
			while (!op.empty() && prioritet(op.back()) >= prioritet(zn)) {
				action(value, op.back());     
				op.pop_back();              
			}
			op.push_back(zn);
			unary = true;
		}
		else {
			string number;      
			while (i < Input.size() && isdigit(Input[i]))number += Input[i++];
			i--;
			value.push_back(atol(number.c_str()));
			unary = false;
		}
	}
	while (!op.empty()) {     
		action(value, op.back());
		op.pop_back();
	}
	return value.back(); 
}

//==================================================================================================================================================
//										            	           ИГРУШКА
//==================================================================================================================================================

string Game() {
	int a = 0, b = 10, c = rand() % 11;
	int int_b;
	string input, answer;

	while (true)
	{
		cout << "Guess the number from 0 to 10\n";
		cout << "Input number: ";
		cin >> int_b;
		if (c == int_b)
		{
			answer = to_string(c);
			cout << "You guessed! Random number: " << answer << "\n";
			return answer;
		}
		else if (int_b < a || int_b > b) {
			cout << "invalid input\n\n";
		}
		else if (c != int_b && int_b > c)
		{
			cout << "Less\n\n";
		}
		else if (c != int_b && int_b < c)
		{
			cout << "More\n\n";
		}
	}
}

//==================================================================================================================================================
//												       ПОИСК КЛЮЧЕВЫХ СЛОВ В ВВЕДЕНОЙ СТРОКЕ
//==================================================================================================================================================
void search_keywords(string Input);
void chat(string Input);



int count_smile = 0, count_sullen = 0, smile = 0, sullen = 0;

int main() {
	string Input;
	cout << "> \b";
	getline(cin, Input);

	for (int i = 0; i < Input.length(); i++) {
		if (Input[i] == ')')
		{
			count_smile++;
			if (Input[i] == '(') count_smile = 0;
		}
		else if (Input[i] == '(')
		{
			count_sullen++;
			if (Input[i] == ')') count_sullen = 0;
		}
	}

	search_keywords(Input);
}



void search_keywords(string Input) {
	string keyword[14] = {
				"start", "play", "game",
				"haha", "hahaha", "analyze",
				"document", "stop", "exit", 
				"bye", "math", "example", 
				"exercise", "="
	};
	for (int i = 0; i < 14; i++) {
			if (Input.find("play") != -1 && Input.find("game") != -1 || Input.find("start") != -1 && Input.find("game") != -1)
			{
				int count = 0;
				while (true)
				{
					if (count == 0) {
						Game();
						count++;
						continue;
					}
					string ans;
					cout << "again? \b";
					cin >> ans;
					if (ans == "n") main();
					else Game();										
				} 
			}

			else if (Input.find("=") != -1 || (Input.find("math") != -1 && (Input.find("example") != -1 || Input.find("exercise") != -1)))
			{
				cout << "#Input your expression \n";
				cout << "> \b";
				cin >> Input;
				string x;
				if (x[0] == '-') {
				x.insert(x.begin(), '(');
				x.insert(x.end(), ')');
			}

			int size = 1 * Input.size();
			for (int i = 0; i < size; i++) {
				if (Input[i] == 'x') {
					Input.erase(i, 1);
					Input.insert(i, x);
				}
			}
			cout << "#= \b";
			cout << calculus(Input) << "\n";
			main();
		}
		else if (Input.find("analyze") != -1 && Input.find("document") != -1)
		{
			search();
		}
		else if (Input.find("stop") != -1 || Input.find("exit") != -1 || Input.find("bye") != -1) exit(0);			
		else
		{
			chat(Input);
		}
	}
}


//==================================================================================================================================================
//											        ПРОВЕРКА НА СУЩЕСТВОВАНИЕ ФАЙЛА В ДИРЕКТОРИИ
//==================================================================================================================================================

bool doesFileExist(const char *fileName)
{
	ifstream infile(fileName);
	return infile.good();
}

void chat(string Input) {
	int loop = 0;

	if (doesFileExist("ChatBotData.txt") == true) { //если файл записан в директорию, то начинается обучения чат-бота
		for (loop = 1; loop > 0; loop++) {
			string Output, Holder, DataInput, DataOutput, TEMP;
			int Index, isThereCount;
			isThereCount = 0;
			bool wasInputFound = false;

			ifstream DataFile;
			ofstream OutputDataFile;

			DataFile.open("ChatBotData.txt");

			int numberOfLines = 0;

			while (getline(DataFile, TEMP)) {
				numberOfLines++;
			}
			DataFile.close();

			DataFile.open("ChatBotData.txt");

			while (getline(DataFile, Holder)) {
				Index = Holder.find("=");//проверка в txt по "="
				DataInput = Holder.substr(0, Index);//сверка введеного слова, где Index - общее кол-во слов в txt


				if (DataInput == Input) {
					wasInputFound = true;
					DataOutput = Holder.substr(Index + 1, Holder.length());
				}
				else {
					isThereCount++;
					wasInputFound = false;
					if (isThereCount == numberOfLines) {
						string EQUATE;
						cout << Input << endl << "$$ \b";//левый cout, ибо выводит обучение
						getline(cin, EQUATE);
						OutputDataFile.open("ChatBotData.txt", ios_base::app);
						OutputDataFile << endl << Input << "=" << EQUATE;
						OutputDataFile.close();
					}
				}

				if (wasInputFound == true) {
					cout << "#" << DataOutput << endl;
				}
			}

			if (count_smile == 3 && smile == 0 && sullen != 1)
			{
				cout << "#Did you have a good day?\n";
				count_smile = 0;
				smile = 1;
			}
			else if (count_sullen == 3 && sullen == 0 && smile != 1)
			{
				cout << "#Did you have a bad day?\n";
				count_sullen = 0;
				sullen = 1;
			}
			else if (count_smile >= 1 && count_smile < 3 && smile == 0 && sullen != 1 && count_sullen > 1) {
				count_smile = 0;
				count_sullen = 1;
			}
			else if (count_sullen >= 1 && count_sullen < 3 && sullen == 1 && smile != 1  && count_smile > 1) {
				count_sullen = 0;
				count_smile = 1;
			}
			main();
		}
	}

	else {
		ofstream CreatedFile("ChatBotData.txt");
		CreatedFile << "\n" << endl;
		CreatedFile.close();
		cout << "The Data file has been created, please restart ChatBot";
	}
}



void searchname()
{
	ifstream employee("newemployee.txt");
	string name;
	string str, line;
	int age, offset;
	long int salary;

	cout << "#enter the emplyee's name:\n";
	cout << "> \b";
	cin >> str;
	while (employee >> name >> age >> salary) {
		if (str == name) {
			cout << " " << name << ' ' << age << ' ' << "$" << salary << endl;
		}
	}

	while (employee >> name) {
		if (str != name) {
			cout << "Nobody under that name exists" << endl;
		}
	}
	cout << endl;
	search();
}
void searchage()
{
	ifstream employee("newemployee.txt");
	string name;
	int age;
	int fage;
	long int salary;
	cout << "#enter the age of an employee:\n";
	cout << "> \b";
	cin >> fage;
	while (employee >> name >> age >> salary) {
		if (fage == age) {
			cout << " " << name << ' ' << age << ' ' << "$" << salary << endl;
		}
	}
	while (employee >> age) {
		if (fage != age) {
			cout << "#no employee(s) found" << endl;
		}
	}
	cout << endl;
	search();
}
void searchsalary()
{
	ifstream employee("newemployee.txt");
	string name;
	int age;
	long int salary;
	long int fsalary;
	cout << "#enter an employee's salary:\n";
	cout << "> \b";
	cin >> fsalary;
	while (employee >> name >> age >> salary) {
		if (fsalary == salary) {
			cout << " " << name << ' ' << age << ' ' << "$" << salary << endl;;
		}
	}
	while (employee >> salary) {
		if (fsalary != salary) {
			cout << "No employee(s) found" << endl;
		}
	}
	cout << endl;
	search();
}
void displayall()
{
	ifstream employee("newemployee.txt");
	int age;
	long int salary;
	string name;
	cout << "#entire employee database" << endl;
	while (employee >> name >> age >> salary) {
		cout << " " << name << ' ' << age << ' ' << "$" << salary << endl;
	}
	cout << endl;
	search();
}
void doclength()
{
	char *str = new char[1024];
	int i = 0;
	string path = "newemployee.txt";
	ifstream base(path);
	while (!base.eof())
	{
		base.getline(str, 1024, '\n');
		i++;
	}
	base.close();
	delete str;
	cout << " " << i << '\n';
	cout << endl;
	search();
}

void search()
{
	int age;
	string name;
	long double salary;
	int choice2;

	cout << "#select next item:" << endl;
	cout << "    1.Search by name" << endl;
	cout << "    2.Search by age" << endl;
	cout << "    3.Search by salary" << endl;
	cout << "    4.Display all employees" << endl;
	cout << "    5.Total number of rows" << endl;
	cout << "    6.Back" << endl;
	cout << "> \b";
	cin >> choice2;

	switch (choice2) {
	case 1:
		searchname();
		break;
	case 2:
		searchage();
		break;
	case 3:
		searchsalary();
		break;
	case 4:
		displayall();
		break;
	case 5:
		doclength();
		break;
	case 6:
		main();
		break;
	}
}