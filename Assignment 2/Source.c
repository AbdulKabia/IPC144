//Program Name: Weather Data Analysis
//By: Abdul Kabia
//Course: IPC144
//Semester: Fall
//Program Purpose: The program will ask the user for a positive number of days,
//it will then ask the user to input the highs/lows of those days, and the 
//weather condition. After which, it will calculate the average temprature of 
//that day, and at the very end, it will calculate the average of the total 
//number of days.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int getInteger(int min, int max);
void getDailyData(float* high, float* low, char * condition);
void draw(char c, int num);
float average(float first, float second);
void displayResult(int days, float allDaysAverage);
char symbolToDraw(char condition, float averageTemperature);
void garbage();

int main(void){
	system("COLOR 0D");

	int numDays;
	int i;
	float sum = 0;
	float dailyHigh;
	float dailyLow;
	char conditions;
	float dailyAvg = 0;
	//title
	printf("Weather Analyzer 2.0\n");
	printf("====================\n");
	//prompt the user for a number of days
	printf("How many days of data?\n");
	//get an integer between 1 and 14
	numDays = getInteger(1, 14);
	for (i = 0; i < numDays; i++){
		//get input from the user
		getDailyData(&dailyHigh, &dailyLow, &conditions);
		dailyAvg = average(dailyHigh, dailyLow);
		printf("Today's average temperature is: %.2f\n", dailyAvg);
		sum += dailyAvg;
		draw(symbolToDraw(conditions, dailyAvg), 20);
	}
	//remember, arguments are separated by commas
	//there are two arguments here...
	displayResult(numDays, (sum / numDays));
	return 0;
}

/*Funtion will check to see if value it's been fed is between 1-14*/
int getInteger(int min, int max){
	int a;
	int value;
	do{
		printf("Enter an integer between 1 and 14: ");
		value = scanf("%d", &a);
		garbage();
		//Checks to see if user has entered an int or anything else
		if (value == 1)
		{
			if (a > max || a < min){
				printf("Error! Try again!: \n");
			}
		}
		else
		{
			printf("That's not a number, try agian: ");
		}

	} while ((a > max || a < min) || value != 1);
	return a;
}

//Will get the day's high, low and condition from the user
void getDailyData(float* high, float* low, char * condition){

	int get;
	do	{
	printf("Enter today's high, low, and condition");
	printf("(c = cloudy, s = sunny,\n");
	printf("p = precipitation) separated by commas: ");
	
		get = scanf("%f, %f, %c", high, low, condition);
		garbage();
		//Evalutes to see if the user has entered the information as desired
		if (*low > *high || get != 3 || (*condition != 'c' && *condition != 's'
			&& *condition != 'p'))	{
			printf("Error in your submisison, try again\n");
		}
	} while (*low > *high || get != 3 || (*condition != 'c' && *condition != 's'
		&& *condition != 'p'));

}

//Draws a character a specific number of times
//Determined by the num variable
void draw(char c, int num){

	for (int i = 0; i < num; i++)
	{
		printf("%c", c);
	}
	printf("\n");
}

//Will average the value of the first and second variables
float average(float first, float second){

	float ret;
	ret = (first + second) / 2;
	return ret;
}


//Switch case that will print out based on value of days
void displayResult(int days, float allDaysAverage){

	switch (days)
	{
	case 1:
		printf("Your one day average is: %.2f", allDaysAverage);
		break;

	case 2:
		printf("Your two day average is: %.2f", allDaysAverage);
		break;

	case 3:
		printf("Your three day average is: %.2f", allDaysAverage);
		break;

	case 4:
		printf("Your four day average is: %.2f", allDaysAverage);
		break;

	case 5:
		printf("Your five day average is: %.2f", allDaysAverage);
		break;

	case 6:
		printf("Your six day average is: %.2f", allDaysAverage);
		break;

	case 7:
		printf("Your seven day average is: %.2f", allDaysAverage);
		break;

	case 8:
		printf("Your eight day average is: %.2f", allDaysAverage);
		break;

	case 9:
		printf("Your nine day average is: %.2f", allDaysAverage);
		break;

	default:
		printf("Your %d day average is: %.2f", days, allDaysAverage);
		break;
	}
	getchar(); getchar();

}

//Places a character into ret depending on the if statement
//returns ret with appropriate value
char symbolToDraw(char condition, float averageTemperature){

	char ret = 'a';

	if (condition == 's')
	{
		ret = '@';
	}
	else if (condition == 'c')
	{
		ret = '~';
	}
	else if (condition == 'p' && averageTemperature <= 0)
	{
		ret = '*';
	}
	else if (condition == 'p' && averageTemperature > 0)
	{
		ret = ';';
	}

	return ret;
}

//Will clean out buffer until it hits a '\n'
void garbage() {
	while (getchar() != '\n');
}
