#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>	
using namespace std;


//Assignment 1   Name:Trevor Withers

//This program allows customers to purchase meat and other items and creates a receipt

char getValidMeat();
double determineMeatCost(char);
double getValidWeight();
double getValidCost();
double validateDouble(double, double, double, string);
void printBill(char, double, double, double, double, double);
void printEndingMsg();


int main()
{
	//Variable declarations
	char meatType;
	string choice;
	int custCount = 0;
	bool continueProgram = true;
	double meatTypeCost = 0.0, dairyCost = 0.0, miscCost = 0.0, meatWeight = 0.0, meatCost = 0.0, totalCost = 0.0;

	do //This do while statement will always allow the program to run once and then ask the user for further input
	{
		meatType = getValidMeat();

		meatTypeCost = determineMeatCost(meatType);

		meatWeight = getValidWeight();

		cout << "Enter the total cost of the dairy products (0-2000): ";

		dairyCost = getValidCost();

		cout << "Enter the total miscellaneous costs (0-2000): ";
		miscCost = getValidCost();

		meatCost = meatTypeCost * meatWeight;

		totalCost = meatCost + dairyCost + miscCost;

		printBill(meatType, meatTypeCost, meatCost, dairyCost, miscCost, totalCost);

		cout << "Press enter to handle next customer or ctrl z to close: ";
		cin.ignore(80, '\n');
		getline(cin, choice);
		custCount++;
	} while (!cin.eof());

	cout << "The total number of customers entered is: " << custCount << endl;
	printEndingMsg();

}

//This function will ask the user for a meat type and validate their answer
char getValidMeat()
{
	char validMeat;
	cout << "Please enter meat type. (Enter B:beef, C:chicken, or F:fish): ";
	cin >> validMeat;
	validMeat = toupper(validMeat);
	while (validMeat != 'B' && validMeat != 'C' && validMeat != 'F' || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Invalid entry. Please enter meat type. (Enter B:beef, C:chicken, or F:fish): ";
		cin >> validMeat;
		validMeat = toupper(validMeat);
	}
	return validMeat;
}


//This function will ask for a weight and send the data to be validated and return a valid weight
double getValidWeight()
{
	double validWeight;
	cout << "Enter total weight of meat (0.5 - 100): ";
	cin >> validWeight;

	validWeight = validateDouble(validWeight, 0.5, 100.0, "Enter total weight of meat (0.5 - 100): ");

	return validWeight;
}

//This function returns the cost of meat based on the passed meat type
double  determineMeatCost(char passedMeatType)
{
	double cost = 0.0;

	switch (passedMeatType)
	{
	case 'B':
		cost = 8.80;
		break;
	case 'F':
		cost = 5.49;
		break;
	default:
		cost = 6.59;
	}
	return cost;
}

//This function asks the user for a cost and sends the data to be validated and return the valid cost
double getValidCost()
{
	double validCost;
	cin >> validCost;

	validCost = validateDouble(validCost, 0.0, 2000.0, "Number should be between 0 and 2000: ");

	return validCost;
}

//This is a generic function to validate a double between 2 passed values and prints a desired error message
double validateDouble(double doubleToValidate, double minVal, double maxVal, string errorMsg)
{
	while (doubleToValidate < minVal || doubleToValidate > maxVal || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Invalid entry. " << errorMsg;
		cin >> doubleToValidate;
	}
	return doubleToValidate;
}

//This function creates and saves data to a receipt text file and then prints it to the console
void printBill(char passedMeatType, double passedMeatTypeCost, double passedMeatCost,
	double passedDairyCost, double passedMiscCost, double passedTotalCost)
{
	ofstream fout("receipt.txt");
	if (!fout.is_open())
	{
		cout << "File will not open. Program will now close..." << endl;
		system("pause");
		exit(-1);
	}

	string writtenMeatType;
	switch (passedMeatType)
	{
	case 'C':
		writtenMeatType = "Chicken";
		break;
	case 'F':
		writtenMeatType = "Fish";
		break;
	default:
		writtenMeatType = "Beef";
		break;
	}
	fout << fixed << setprecision(2) << endl << "--------------------------------------------" << endl
		<< "ABC Grocery Store" << endl << endl
		<< "Items bought: " << endl << endl
		<< left << setw(6) << "Meat: "
		<< right << setw(7) << writtenMeatType << left << setw(4) << " @ $" << setw(3)
		<< passedMeatTypeCost << "/kg " << right << setw(19) << passedMeatCost << endl
		<< setw(14) << "Dairy Products" << right << setw(30) << passedDairyCost << endl
		<< setw(13) << "Miscellaneous" << right << setw(31) << passedMiscCost << endl << endl
		<< right << setw(44) << passedTotalCost << endl << endl
		<< right << setw(20) << "THANK YOU!" << endl << endl
		<< "--------------------------------------------" << endl;
	system("type receipt.txt");
}

//This function lets the user know that the program has ended and waits for user input to exit
void  printEndingMsg()
{
	cout << "Program has ended..." << endl;
	system("pause");
}

/*
Please enter meat type. (Enter B:beef, C:chicken, or F:fish): b
Enter total weight of meat (0.5 - 100): 20
Enter the total cost of the dairy products (0-2000): 10
Enter the total miscellaneous costs (0-2000): 15

--------------------------------------------
ABC Grocery Store

Items bought:

Meat:    Beef @ $8.80/kg              176.00
Dairy Products                         10.00
Miscellaneous                          15.00

									  201.00

		  THANK YOU!

--------------------------------------------
Press enter to handle next customer or ctrl z to close:
Please enter meat type. (Enter B:beef, C:chicken, or F:fish): c
Enter total weight of meat (0.5 - 100): 15
Enter the total cost of the dairy products (0-2000): 12
Enter the total miscellaneous costs (0-2000): 11

--------------------------------------------
ABC Grocery Store

Items bought:

Meat: Chicken @ $6.59/kg               98.85
Dairy Products                         12.00
Miscellaneous                          11.00

									  121.85

		  THANK YOU!

--------------------------------------------
Press enter to handle next customer or ctrl z to close: ^Z
The total number of customers entered is: 2
Program has ended...
Press any key to continue . . .
*/