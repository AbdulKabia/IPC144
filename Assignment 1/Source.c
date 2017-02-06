//Program Name: Weather Data Analysis
//By: Abdul Kabia
//Course: IPC144
//Semester: Fall
//Program Purpose: The program will ask the user for a positive number of days, it will then
//ask the user to input the highs/lows of those days, and the weather condition. After which, it will
//calculate the average temprature of that day, and at the very end, it will calculate the average of the total number of days.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

//A constant variable that determines how many times a symbol is to be printed out
const int symbolCount = 20;

//This is a prototype that tells C that there will be a function below
void symbolPrint(char symbol);

int main(void)
{
	int days = 0;
	double todaysHigh = 0;
	double todaysLow = 0;
	char todaysCondition;
	double averageTemp;
	double totalAverageStorage = 0;
	double totalAverage;

	//Changes the colour of the output screen (Black bg, pink text)
	system("COLOR 0D");

	printf("Weather Analyizer\n");
	printf("========================\n\n");

	//A while loop that will keep occuring until the user
	//enters a number that isn't 0 or less than 0
	while (days <= 0)
	{
		printf("Please enter a positive number of days: ");
		scanf("%d", &days);
	}

	//A for loop that will repeat the code inside of it a number
	//of times based on the input that the user gave to the scanf
	//function above
	for (int a = 0; a < days; a++)
	{
		printf("Enter today's high: ");
		scanf("%lf", &todaysHigh);

		printf("Enter today's low: ");
		scanf("%lf", &todaysLow);
		
		printf("Enter today's conditions (s: sunny, c: cloudy, p: precipitation): ");
		scanf(" %c", &todaysCondition);

		//This will calculate the average temprature of the day
		//by adding the low and the high, and then dividing it by 2
		averageTemp = (todaysLow + todaysHigh) / 2;
		
		//This is where the average of the day will be stored
		//we will use these stored averages later
		totalAverageStorage += averageTemp;

		printf("Today's average temprature is: %.2lf\n", averageTemp);

		//A series of If statements that will print out the right symbol
		//based on the letter the user inputs
		if (todaysCondition == 's')
		{
			symbolPrint('@');
		}
		else if (todaysCondition == 'c')
		{
			symbolPrint('~');
		}
		else if (todaysCondition == 'p' && averageTemp <= 0)
		{
			symbolPrint('*');
		}
		else if (todaysCondition == 'p' && averageTemp > 0)
		{
			symbolPrint(';');
		}
	}
	//We use this to calculate the average weather for the amount of
	//days that's been entered
	totalAverage = totalAverageStorage / days;

	//I noticed the program would still print out this line even if the user
	//Didn't enter any days, so this if statements makes it so that
	//this is only printed if the user enters more than 0 days
	if (days > 0)
	{
		printf("Average for all %d days is: %.2lf degrees", days, totalAverage);
	}
	getchar(); getchar();
}

//This Function accepts one parameter, which is a symbol character
//it takes that character and prints it out a number of times
//(that number is determined by the constant variable on line 15).
void symbolPrint(char symbol)
{
	for (int i = 0; i < symbolCount; i++)
	{
		printf("%c", symbol);
	}
	printf("\n");
}
