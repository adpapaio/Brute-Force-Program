//CIS 350 Assignment SEND + MORE = MONEY
//Author: Aristotelis Papaioannou
//Date Created: 2/9/2016
//Last Modification Date: 2/11/2016

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool inpChk(string);	//Prototype for Input Check function
void split(string, vector<string>&); // Prototype for split function
void charVec(string, vector<char>&); //Prototype for chararacter vector function
void assign(vector<char>&, vector<string>&, vector<char>&); //Prototype for the assign function

int main()
{
	string firstIn; //original input
	vector<string> vecInput; //vector of the inputs
	vector<char> cVec;		//Vector of the unique characters from the input
	vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; 

	cout << "Enter the input (In Capital letters): ";
	getline(cin,firstIn);	//get the whole line of the input
	
	while (inpChk(firstIn) == false)// check the input for operators
	{
		cout << "Enter the input: ";
		getline(cin, firstIn);	//get the whole line of the input
	}

	split(firstIn, vecInput);	//go to split function
	
	charVec(firstIn, cVec);		//go to charVec function

	assign(cVec, vecInput, numbers); //go to convert function
	
	system("pause");
	return 0;
}

//Name: inpChk
//Description: Make sure the user inputs valid data
//Input: string text
//Output: true/false
bool inpChk(string input)
{
	bool op = 0, equ = 0, numb = 0, upp = 1; //upp is 1 because we are expecting uppercase letters

	for (int i = 0; i < input.length(); i++) //check for invalid input
	{
		if (isalpha(input[i]))	//if the character is alpha
		{
			if (isupper(input[i]) && upp != 0)	//if it is uppercase and lowercase has not been found
				upp = 1;						//upp stays 1
			else
				upp = 0;						//upp becomes 0
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*') //check string for an operator
			op = 1;
		else if (input[i] == '=')	//check string for equal sign
			equ = 1;
		else if (isdigit(input[i]))
			numb = 1;
	}

	if (op == 1 && equ == 1 && upp == 1 && numb == 0) //if there is an operator and an equl sign return true
		return true;
	else
	{
		if (op == 0 || equ == 0)	//if it finds a missing operator or equal sign display error
			cout << "Invalid Input: Missing Operator(s)!" << endl;
		else if (upp == 0)			// if a lower case character is found
			cout << "Invlid Input: Lowercase character(s) found!" << endl;
		else if (numb == 1)
			cout << "Invalid Input: Cannot input Digit(s)!" << endl;
		
		return false;
	}
}

//Name: split
//Description: Split the input into vectors
//Input: string text, input vector
//Output: void
//Author: Aristotelis Papaioannou
//Date created: 2/9/2016
void split(string x, vector<string>& inputs)
{
	istringstream inp(x);
	char spaceChar = ' ';
	string temp1 = "";

	for (int i = 0; i < x.length(); i++)
	{
		getline(inp, temp1, spaceChar);	// seperate the inputs by a space
		inputs.push_back(temp1);		//put the temp word into the vector

		temp1 = "";
	}
}

//Name: charVec
//Description: Creates a vector of unique characters from the string
//Input: string text, char vector
//Output: void
//Author: Aristotelis Papaioannou
//Date Created: 2/9/2016
void charVec(string strIn, vector<char>& cVec)
{
	for (int i = 0; i < strIn.length(); i++)// add each character to the vector
	{
		if (strIn[i] != ' ' && isalpha(strIn[i]))
			cVec.push_back(strIn[i]);
	}
	
	sort(cVec.begin(), cVec.end()); //Sort the vector alphbetically
	cVec.erase(unique(cVec.begin(), cVec.end()), cVec.end()); //Erase the duplicates, after finding their unique duplicates/neighbors
}


//Name: assign
//Description: Assign numbers to the letters then calculate
//Input: char Vector, input Vector, numbers Vector
//Output: Solution
//Author: Aristotelis Papaioannou
//Date Created: 2/9/2016
void assign(vector<char>& cVec, vector<string>& inVec, vector<char>& numbers)
{
	string input1 = inVec[0], input2 = inVec[2], input3 = inVec[4]; //the three word inputs
	string numb1 = "", numb2 = "", numb3 = "";

	inVec.resize(5); // make sure the vector is only size 5 (word1, op1, word2, op2, word3)

	do{
		// First word assignment
		for (int i = 0; i < input1.length(); i++)
		{
			for (int j = 0; j < cVec.size(); j++)
			{
				if (input1[i] == cVec[j])	// if the character matches a uniques character in the vector
					numb1 = numb1 + numbers[j];	// numb1 equals numb1 plus the number in the same position of the numbers vector
			}
		}

		// second word assignment
		for (int i = 0; i < input2.length(); i++)
		{
			for (int j = 0; j < cVec.size(); j++)
			{
				if (input2[i] == cVec[j])
					numb2 = numb2 + numbers[j];
			}
		}

		// third word assignment
		for (int i = 0; i < input3.length(); i++)
		{
			for (int j = 0; j < cVec.size(); j++)
			{
				if (input3[i] == cVec[j])
					numb3 = numb3 + numbers[j];
			}
		}

		
		if (inVec[1] == "+") //If the operations is addition
		{
			if ((stoi(numb1) + stoi(numb2)) == stoi(numb3))
			{
				cout << "Found Solution: " << numb1 << " + " << numb2 << " = " << numb3 << endl;
				return;
			}
		}
		else if (inVec[1] == "-") // if the operation is Subtraction
		{
			if ((stoi(numb1) - stoi(numb2)) == stoi(numb3))
			{
				cout << "Found Solution: " << numb1 << " - " << numb2 << " = " << numb3 << endl;
				return;
			}
		}
		else if (inVec[1] == "*") // if the operation is Multiplication
		{
			if ((stoi(numb1) * stoi(numb2)) == stoi(numb3))
			{
				cout << "Found Solution: " << numb1 << " * " << numb2 << " = " << numb3 << endl;
				return;
			}
		}
		
		//clear the numbers
		numb1 = "";
		numb2 = "";
		numb3 = "";

	} while (next_permutation(numbers.begin(), numbers.end())); // change the permutation

	cout << "No Solution was found!" << endl; //if no solution is found
}