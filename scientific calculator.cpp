//============================================================================
// Name        : scientific.cpp
// Author      : me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include<iostream>
#include<stack>
#include<string>
#include<sstream>
using namespace std;
stack<char>character;//Define the operator stack
stack<float>number; //Define the operand stack
string Get(string ex);
float Cal(string ex);
template<class Type>
Type stringToNum(const string &str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
int main()
{
	string expression;
	while (true)
	{
		cout << "expression:";
		cin >> expression;
		expression = Get(expression);
		if (expression == "null")cout << "expression error" << endl;
		else
		{
			cout << "RPN:" << expression << endl;
			cout << "Result:" << Cal(expression) << endl;
		}
	}
}
//This function converts an infix expression to a postfix expression
string Get(string ex)
{
	string result=string();
	bool flag=false;																				//Define a variable to mark whether the current value is an operand
	for(unsigned int i(0),histroy(0),length=ex.length();i<length;i++)  // loop byte by byte
		switch (ex[i])																			   //Filter is an operator or operand
		{
		case'+':																					   //If it is +
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty()&& character.top() != '(')               //When the + sign is encountered, operators with a priority not greater than the + sign should be popped out of the stack and output
			{
				result += character.top();
				character.pop();
			}
			character.push('+');																	//Put the + sign on the stack
		break;
		case'-':																					        //If it is-
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty()&& character.top() != '(')               //When encountering-sign, operators with priority no greater than-shall be popped out of the stack and output
			{
				result += character.top();
				character.pop();
			}
			character.push('-');
		break;
		case'/':
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty()&&(character.top()=='*'||character.top()=='/')) //Operators with priority not greater than / should be popped out of the stack when encountering /
			{
				result += character.top();
				character.pop();
			}
			character.push('/');
		break;
		case'*':
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty() && (character.top() == '*' || character.top() == '/'))//When encountering *, operators with priority not greater than * should be popped out of the stack
			{
				result += character.top();
				character.pop();
			}
			character.push('*');
		break;
		case '(':																						   //Encounter the opening bracket number should be directly into the stack
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			character.push('(');
		break;
		case ')':                                                                                        //When the right parenthesis is encountered, the stack should be popped sequentially until the nearest left parenthesis is matched
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty() && character.top() != '(')
			{
				result += character.top();
				character.pop();
			}
			if (character.empty())return "null";
			else if (character.top() == '(') character.pop();
		break;
		case '=':																					   //When the equal sign is encountered, the unpopulated operator is popped from the stack
			if (flag)result += ":";                                                               //Judging whether the preceding is an operand or an operator, if it is an operand, add the':' sign to the suffix expression to indicate the end of the operand
			flag = false;																			   //Set the flag variable to false
			while (!character.empty())
			{
			result += character.top();
			character.pop();
			}
		break;
		default:
			if (flag == false)histroy = i;
			result += ex[i];
			flag = true;
			break;
		}
		result += '=';
		return result;
}
float Cal(string ex)
{
	string temp;
	float front;//Previous operand
	float behind;//Post operand
	for (unsigned int i(0),histroy(0),length = ex.length(); i < length; i++)
	{
		switch (ex[i])
		{
		case'+':
			if (histroy == i)histroy = histroy + 1;
			behind = number.top();
			number.pop();
			front = number.top();
			number.pop();
			front = front + behind;
			number.push(front);
			break;
		case'-':
			if (histroy == i)histroy = histroy + 1;
			behind = number.top();
			number.pop();
			front = number.top();
			number.pop();
			front = front - behind;
			number.push(front);
			break;
		case'/':
			if (histroy == i)histroy = histroy + 1;
			behind = number.top();
			number.pop();
			front = number.top();
			number.pop();
			front = front / behind;
			number.push(front);
			break;
		case'*':
			if (histroy == i)histroy = histroy + 1;
			behind = number.top();
			number.pop();
			front = number.top();
			number.pop();
			front = front * behind;
			number.push(front);
			break;
		case':'://if:If it is, it means that an operand is over here, then the operand is intercepted into the stack
		temp = ex.substr(histroy, i-histroy);
		histroy = i+1;
		number.push(stringToNum<float>(temp));
		break;
		case'=':
		return number.top();
		default:break;
		}
	}
	return number.top();

}
