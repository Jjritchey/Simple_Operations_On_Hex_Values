//Justin Ritchey - Program 4 - updated 12/8/2020 to make the output in HEX - Program will take a .txt input file with hex values with arthimatic, will convert the hex to decimals and do the math. Any multiplication, divison or powers will be done with only + or -.
//I could not figure out a way to get AAAAABBBBBCCCCCDDDDDEEEEEFFFFF(or the right hand side of the equaton) into a function variable without trying to use a third party library or making a new class. 

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isOp(char);                                           //funciton to tell if a char is a operator or not
unsigned long long int hexToDec(string, ofstream&);        //funciton convert hex to a decimal
long long int multiply(int, long long int);                //function to multiply with only using addtion
void divide(long long int,long long int, ofstream&);       //function to divide with only using subtraction
long long int power(int, int);                             //function to raise to a power only using additon
string dec_to_hex(long long int);                                 //function to translate decimal to hexadecimal



int main()
{
	string line = "";                                 //string to hold each line
	ifstream inFile;                                  //input file
	inFile.open("input.txt");
	ofstream outFile;                                 //output file
	outFile.open("outFile.txt");
	string lhs = "";                                  //will hold the string left hand side of the equation
	string rhs = "";                                  //will hold the string right hand side of the equation
	char op = NULL;                                   //will hold operator
	unsigned long long int iLhs = 0;                  //will hold the int of the left hand side
	unsigned long long int iRhs = 0;                  //will hold the int of the right hand side
	unsigned long long int final = 0;
	string finalHex = "";                                  //String to output the final value in hex
	

	

	while (getline(inFile, line))                     //loop to gather the data line by line
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (isOp(line[i]))                        //searchs the string until it find the first operator
			{
				lhs = line.substr(0, i);              //grabs the left hand side of the equarion
				op = line[i];                         //grabs the operator
				rhs = line.substr(i + 1, line.size());  //grabs the right hand side of the eqatuon

				rhs.erase(rhs.size() - 1);                //removed the = sign from the operand

				cout << lhs << "   " << op << "   " << rhs << " = ";     //echo print
				outFile << lhs << "   " << op << "   " << rhs << " = ";

				iLhs = hexToDec(lhs, outFile);                            //converting the left and right hand hex to decimals
				iRhs = hexToDec(rhs, outFile);

				switch (op)                                               //using the operator to do the arthimatic
				{
				case '+':
					final = iLhs + iRhs;
					finalHex = dec_to_hex(final);
					cout << finalHex  << "\n\n";
					outFile << finalHex << "\n\n";
					break;
				case '-':
					final = iLhs - iRhs;
					finalHex = dec_to_hex(final);
					cout << finalHex  << "\n\n";
					outFile << finalHex << "\n\n";
					break;
				case '*':
					final = multiply(iLhs, iRhs);
					finalHex = dec_to_hex(final);
					cout << finalHex  << "\n\n";
					outFile << finalHex  << "\n\n";
					break;
				case '/':
					divide(iLhs, iRhs, outFile);
					break;
				case '$':
					final = power(iLhs, iRhs);
					finalHex = dec_to_hex(final);
					cout << finalHex << "\n\n";
					outFile << finalHex  << "\n\n";
					break;
				}
			}
		}
	}
}

bool isOp(char a)
{
	if (a == '+' || a == '-' ||                         //fucntion to check for operators
		a == '*' || a == '/' || a == '$')
		return true;
	return false;
}

unsigned long long int hexToDec(string a, ofstream& out)     //function to convert from hex to decimal
{
	int base = 16;
	int powe = 0;
    unsigned long long int total = 0;
	

	for (int i = (a.size()-1); i >= 0; i--)                 //loop that starts at the last digit in the hex and converts it to decimal. moves right to left until it is finished converting
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			total += multiply(a[i] - 48, (power(base, powe)));    //if the hex digit is 0-9 this converts its ascii value to decmial
			powe++;
		}
		else                                                      //if the hex value is a letter a switch case assigns the new value and converts to decimal
		{
			switch (a[i])
			{
			case 'A':
				total += multiply(10, (power(base, powe)));
				break;
			case 'B':
				total += multiply(11, (power(base, powe)));
				break;
			case 'C':
				total += multiply(12, (power(base, powe)));
				break;
			case 'D':
				total += multiply(13, (power(base, powe)));
				break;
			case 'E':
				total += multiply(14, (power(base, powe)));
				break;
			case 'F':
				total += multiply(15, (power(base, powe)));
				break;

			}
			powe++;
		}
	}

	return total;
}

long long int multiply(int a, long long int b)                         //does multiplications with only using addition
{
	long long int temp = 0;
	for (int i = 0; i < a; i++)
	{
		temp += b;
	}
	return temp;
}

void divide(long long int a, long long int b, ofstream& out)        //does divison only using subtraction and addtion
{
    int count = 0;
	string q = "";
	string r = "";

	while (a>b)
	{
		a = a - b;
		count++;
	}
	if (a < b)
	{
		q = dec_to_hex(count);
		r = dec_to_hex(a);
		cout << "Quotient " << q << ", Remainder " << r << "\n\n";
		out << "Quotient " << q << ", Remainder " << r << "\n\n";
	}
}

long long int power(int a, int b)                               //does powers only using additon
{
	long long int temp = a;
	long long int temp2 = a;

	if (b == 0)
		return 1;
	
	for (int i = 1; i < b; i++)
	{
		for (int j = 1; j < a; j++)
		{
			temp = temp + temp2;
		}
		temp2 = temp;
	}
	return temp;
}

string dec_to_hex(long long int decimal)                                  //function to convert decmial to hexadecimal
{
	string hex = "";                                               //will hold the result in a string
	long long int hex_divide = 0;                                            //holds the decimal given by the user to convert   
	long long int r = 0;

	hex_divide = decimal;

	while (hex_divide > 0)                                         //loop to assign hex values
	{
		if (hex_divide > 16)                                       //if decimal number is over 16, will use the modulo to get remainder
		{
			r = hex_divide % 16;
		}
		else if (hex_divide < 16)                                  //if decimal is under 16 will assign decimal as remainder
		{
			r = hex_divide;
		}

		if (r == 0)                                                //loop to assign value based on the remainder varaiable       
		{
			hex = '0' + hex;
		}
		if (r == 1)
		{
			hex = '1' + hex;
		}
		if (r == 2)
		{
			hex = '2' + hex;
		}
		if (r == 3)
		{
			hex = '3' + hex;
		}
		if (r == 4)
		{
			hex = '4' + hex;
		}
		if (r == 5)
		{
			hex = '5' + hex;
		}
		if (r == 6)
		{
			hex = '6' + hex;
		}
		if (r == 7)
		{
			hex = '7' + hex;
		}
		if (r == 8)
		{
			hex = '8' + hex;
		}
		if (r == 9)
		{
			hex = '9' + hex;
		}
		if (r == 10)
		{
			hex = 'A' + hex;
		}
		if (r == 11)
		{
			hex = 'B' + hex;
		}
		if (r == 12)
		{
			hex = 'C' + hex;
		}
		if (r == 13)
		{
			hex = 'D' + hex;
		}

		if (r == 14)
		{
			hex = 'E' + hex;
		}
		if (r == 15)
		{
			hex = 'F' + hex;
		}

		hex_divide = hex_divide / 16;                //making decimal into the left over for next remainder number         
		r = hex_divide;                              //setting remainder equal to this number
	}
	return hex;
}