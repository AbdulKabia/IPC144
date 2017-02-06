#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*an instance of this struct holds the weather data for a single day*/
struct DailyData {
	int day;
	int month;
	int year;
	float high;
	float low;
	float precipitation;
	char condition;
};

/*an instance of this struct holds summary information for the weather
for a given month*/
struct MonthlyStatistic {
	float minTemperature;
	float maxTemperature;
	float averageTemperature;
	float totalPrecipitation;
};
int readDailyData(FILE* fp, struct DailyData allData[]);

int getRelevantRecords(int yearWanted, const struct DailyData allData[], int sz, struct DailyData yearData[]);
void sortYearData(struct DailyData yearData[], int sz);
void getStats(int month, const struct DailyData yearData[],
	int sz, struct MonthlyStatistic* monthStats);
void printMonthlyStatistic(int month, const struct MonthlyStatistic* monthly);
void graphLine(int month, const struct MonthlyStatistic* monthly);
void printVerbose(const struct DailyData yearData[], int sz);
char symbolToDraw(char condition, float avgTemp);
float average(float first, float second);
void draw(char c, int num);


int main(void) {
	FILE* fp = fopen("historicaldata.csv", "r");
	if (!fp) {
		printf("You need to put historicaldata.csv into this directory\n");
		exit(0);
	}
	struct DailyData  allData[3000];
	struct DailyData yearData[366];
	int numTotalRecords;

	numTotalRecords = readDailyData(fp, allData);
	int year;
	int reportType;
	int i;
	struct MonthlyStatistic monthly[12];
	printf("Please enter the year for the report: ");
	scanf("%d", &year);
	printf("Please enter the type of report you wish to generate:\n");
	printf("1) summary\n");
	printf("2) detailed\n");
	scanf("%d", &reportType);
	int numDays = getRelevantRecords(year, allData, numTotalRecords, yearData);
	sortYearData(yearData, numDays);

	for (i = 0; i < 12; i++) {
		getStats(i + 1, yearData, numDays, &monthly[i]);
	}

	printf("Weather summary for %d\n", year);
	printf("|   Month   | High  |  Low  |  Avg  | Precip  |\n");
	printf("|-----------|-------|-------|-------|---------|\n");
	for (i = 0; i < 12; i++) {
		printMonthlyStatistic(i + 1, &monthly[i]);
	}
	printf("\n\n");
	printf("Precipitation Graph\n\n");
	for (i = 0; i < 12; i++) {
		graphLine(i + 1, &monthly[i]);
	}
	if (reportType == 2) {
		printf("\n\n");
		printf("Detailed report:\n");
		printVerbose(yearData, numDays);
	}
	getchar(); getchar();
	return 0;
}
int readDailyData(FILE* fp, struct DailyData allData[]) {
	int i = 0;
	while (fscanf(fp, "%d,%d,%d,%f,%f,%f,%c\n",
		&allData[i].year, &allData[i].month, &allData[i].day,
		&allData[i].high, &allData[i].low, &allData[i].precipitation,
		&allData[i].condition) == 7) {
		i++;
	}
	return i;
}
int getRelevantRecords(int yearWanted, const struct DailyData allData[],
	int sz, struct DailyData yearData[]) {
	int i, a = 0;
	//put your code here
	for (i = 0; i < sz; i++)
	{
		if (allData[i].year == yearWanted)
		{
			yearData[a].year = allData[i].year;
			yearData[a].month = allData[i].month;
			yearData[a].day = allData[i].day;
			yearData[a].high = allData[i].high;
			yearData[a].low = allData[i].low;
			yearData[a].precipitation = allData[i].precipitation;
			yearData[a].condition = allData[i].condition;

			a++;
		}
	}

	return a;
}

void sortYearData(struct DailyData yearData[], int sz) {
	//put your code here
	int a, d, month, day;
	float high, low, precip;
	char cond;

	// This will sort the information
	for (d = 0; d < sz; d++)
	{

		for (a = 0; a < sz - 1; a++)
		{
			// Check for month
			if (yearData[a].month > yearData[a + 1].month || (yearData[a].month
				== yearData[a + 1].month && yearData[a].day >
				yearData[a + 1].day))
			{
				// Swap months
				month = yearData[a].month;
				yearData[a].month = yearData[a + 1].month;
				yearData[a + 1].month = month;

				// Swap days
				day = yearData[a].day;
				yearData[a].day = yearData[a + 1].day;
				yearData[a + 1].day = day;

				// Swap highs
				high = yearData[a].high;
				yearData[a].high = yearData[a + 1].high;
				yearData[a + 1].high = high;

				// Swap lows
				low = yearData[a].low;
				yearData[a].low = yearData[a + 1].low;
				yearData[a + 1].low = low;

				// Swap precipitations
				precip = yearData[a].precipitation;
				yearData[a].precipitation = yearData[a + 1].precipitation;
				yearData[a + 1].precipitation = precip;

				// Swap conditions
				cond = yearData[a].condition;
				yearData[a].condition = yearData[a + 1].condition;
				yearData[a + 1].condition = cond;

			}
		}
	}

}

void getStats(int month, const struct DailyData yearData[],
	int sz, struct MonthlyStatistic* monthly) {
	//INCOMPLETEEEEEEE //////////
	int i;

	float max = yearData[0].high;
	float min = 0;
	float totalPrecip;


	// Will find the minimum temp in the low table
	for (int a = 0; a < sz; a++)
	{
		if (yearData[a].month == month)
		{
			min = yearData[a].low;
		}
	}

	for (i = 0; i < sz; i++)
	{
		if (yearData[i].month == month)
		{
			if (yearData[i].low < min)
			{
				min = yearData[i].low;
			}
		}
	}

	monthly->minTemperature = min;

	// Will find the maximum temp in the high table
	for (i = 0; i < sz; i++)
	{
		if (yearData[i].month == month)
		{
			if (yearData[i].high > max)
			{
				max = yearData[i].high;
			}
		}

	}
	monthly->maxTemperature = max;

	float totalMax = 0, totalMin = 0;
	int  maxCounter = 0, minCounter = 0;
	for (i = 0; i < sz; i++)
	{
		if (yearData[i].month == month)
		{
			totalMax += yearData[i].high;
			maxCounter++;
		}
	}

	for (i = 0; i < sz; i++)
	{
		if (yearData[i].month == month)
		{
			totalMin += yearData[i].low;
			minCounter++;
		}
	}

	float maxAvg, minAvg;
	maxAvg = totalMax / maxCounter;
	minAvg = totalMin / minCounter;

	float avg = average(maxAvg, minAvg);
	monthly->averageTemperature = avg;

	for (int b = 0; b < sz; b++)
	{
		if (yearData[b].month == month)
		{
			totalPrecip += yearData[b].precipitation;
		}
	}

}

void printMonthlyStatistic(int month, const struct MonthlyStatistic* monthly) {
	// Complete
	char monthsArr[12];

	switch (month)
	{
	case 1:
		strcpy(monthsArr, "January");
		break;

	case 2:
		strcpy(monthsArr, "February");
		break;

	case 3:
		strcpy(monthsArr, "March");
		break;

	case 4:
		strcpy(monthsArr, "April");
		break;

	case 5:
		strcpy(monthsArr, "May");
		break;

	case 6:
		strcpy(monthsArr, "June");
		break;

	case 7:
		strcpy(monthsArr, "July");
		break;

	case 8:
		strcpy(monthsArr, "August");
		break;

	case 9:
		strcpy(monthsArr, "September");
		break;

	case 10:
		strcpy(monthsArr, "October");
		break;

	case 11:
		strcpy(monthsArr, "November");
		break;

	case 12:
		strcpy(monthsArr, "December");
		break;

	default:
		break;
	}

	printf("| %9s | %-5.1f | %-5.1f | %-5.1f | %-5.1f |\n", monthsArr,
		monthly->maxTemperature, monthly->minTemperature,
		monthly->averageTemperature, monthly->totalPrecipitation);
}

void graphLine(int month, const struct MonthlyStatistic* monthly) {
	//put your code here
	//I DONT KNOW WHAT TO DO HERE
}

void printVerbose(const struct DailyData allData[], int sz) {
	//put your code here
	// INCOMPLETE///
	int i;
	char monthsArr[12];
	int month = 1;
	switch (month)
	{
	case 1:
		strcpy(monthsArr, "January");
		break;

	case 2:
		strcpy(monthsArr, "February");
		break;

	case 3:
		strcpy(monthsArr, "March");
		break;

	case 4:
		strcpy(monthsArr, "April");
		break;

	case 5:
		strcpy(monthsArr, "May");
		break;

	case 6:
		strcpy(monthsArr, "June");
		break;

	case 7:
		strcpy(monthsArr, "July");
		break;

	case 8:
		strcpy(monthsArr, "August");
		break;

	case 9:
		strcpy(monthsArr, "September");
		break;

	case 10:
		strcpy(monthsArr, "October");
		break;

	case 11:
		strcpy(monthsArr, "November");
		break;

	case 12:
		strcpy(monthsArr, "December");
		break;

	default:
		break;
	}

	for (i = 0; i < sz; i++)
	{
		printf("%9s %d %d: %3f", monthsArr, allData[i].day, allData[i].year, allData[i].precipitation);
		draw;
	}



}

char symbolToDraw(char condition, float avgTemp) {
	// Complete
	char ret = 'a';

	if (condition == 's')
	{
		ret = '@';
	}
	else if (condition == 'c')
	{
		ret = '~';
	}
	else if (condition == 'p' && avgTemp <= 0)
	{
		ret = '*';
	}
	else if (condition == 'p' && avgTemp > 0)
	{
		ret = ';';
	}

	return ret;
}

float average(float first, float second) {
	// Complete
	float ret;
	ret = (first + second) / 2;
	return ret;
}

void draw(char c, int num) {
	// Complete
	for (int i = 0; i < num; i++)
	{
		printf("%c", c);
	}
	printf("\n");
}
