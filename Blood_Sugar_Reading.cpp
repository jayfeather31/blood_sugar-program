//Blood_Sugar_Reading.cpp
//Spencer Romberg
//COSC 2030 Fall 2018
//Proj 01
//October 22nd, 2018
//utilizes a variety of techniques regarding arrays to create a program that monitors blood sugar readings for fourteen days
//Additional credits will be found scattered across the code in comments where needed


#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;



int main()
{
	float sum = 0;                        //sets up a sum for an individual day
	int overflow_occurances = 0;          //sets up a way for, should the sum go past 65,535 at any point in the program for a single day, for the program to continue running
	float data_sum[14];                   //given that we only require fourteen days, we can just immediately create a 14-size data array
	int data_points[14];                  //ditto in that in only stores points rather than a sum
	int overflows[14];                    //keeps track of the addition of ALL overflows occurrances for the purposes of keeping track for a week, rather than a day
	int day = 0;                          //allows for the days to be kept track of; it starts at 0 rather than 1 because an array would start at position 0, and end at 13, rather than start at one
	int week = 1;                         //as no arrays are being used to for the week or the sum, start week at one rather than accomadating for the number zero
	float entry;
	int points = 0;                       //keeps track of any given number of points per day (to be added in an iteration with the arrays present).
	float day_max = 0;
	float day_min = 0;
	float week_max = 0;
	float week_min = 0;
	float week_sum = 0;
	float week_points = 0;
	string selection;                     //keyword for navigating UI
	cout << "Welcome to the blood sugar reading program." << endl;
	while (day < 14)
	{
		cout << "What do you wish to do? (Type help for help in entering data if this continues to show after entering.): ";
		cin >> selection;

		//interacts with the user to help with the UI
		if (selection == "help")
		{
			cout << "++++++++++++++++++  PROGRAM TUTORIAL  ++++++++++++++++++++" << endl;
			cout << "+++++ entry: add an entry to be recorded +++++++++++++++++" << endl;
			cout << "+++++ day: look at the current summary of the day ++++++++" << endl;
			cout << "+++++ week: look at the current summary of the week ++++++" << endl;
			cout << "+++++ next: move to the next day +++++++++++++++++++++++++" << endl;
		}

		//interacts with the user to help with an entry field (in addition, requiring the user to input entry every single time means that the user cannot inadvertently cause an overflow!)
		if (selection == "entry")
		{
			cout << "Enter a value to be added to your sum today: ";
			cin >> entry;

			if (entry <= 0)
			{
				cin.ignore();            
			}

			if (entry > 0)
			{
				points++;
				sum += entry;
				if (sum < 0)             //given that an overflow would, by all rights, just turn a sum negative, this is a good way to check (this, on the other hand, is to prevent DELIBERATE overflows)
				{
					overflow_occurances++;
					sum = sum * -1;
				}
				data_sum[day] = sum;
				data_points[day] = points;
				break;
			}

			if (points == 1)
			{
				day_max = entry;
				day_min = entry;
				week_max = entry;
				week_min = entry;
			}

			if (points > 1)
			{
				if (entry > day_max)
				{
					day_max = entry;
					if (entry > week_max)
					{
						week_max = entry;
					}
				}
				
				if (entry < day_min)
				{
					day_min = entry;
					if (entry < week_min)
					{
						week_min = entry;
					}
				}
			}
		}

		//interacts wtih the user to display the current summary for a day.
		if (selection == "day")
		{
			cout << "Current summary for day: " << day + 1 << endl;
			cout << "Minimum for today: " << day_min << endl;
			cout << "Maximum for today: " << day_max << endl;
			cout << "Number of points entered today: " << points << endl;
			cout << "Sum of all entries today: " << sum << endl;
			if (overflow_occurances > 0)
			{
				cout << "Sum of all entries today: " << sum << " * (3.4^(10^38) * " << overflow_occurances << endl;
			}
			
		}

		//interacts with the user to display the current summary for the week
		if (selection == "week")
		{
			week_sum = 0;
			week_points = 0;
			int week_overflow_occurances = overflow_occurances;
			cout << "Current summary for week: " << week << endl;
			cout << "Minimum for week: " << week_min << endl;
			cout << "Maximum for week: " << week_max << endl;
			if (week == 1)
			{
				if (points == 0)                                                                //slightly redundant as to what is below, but the idea is to ensure that when no data is entered for a day, week will show everything up to the current day
				{
					for (int i = 0; i < day; i++)
					{
						week_sum = week_sum + data_sum[i];
						week_points = week_points + data_points[i];
						week_overflow_occurances = week_overflow_occurances + overflows[i];
					}
				}
				if (points != 0)
				{
					for (int i = 0; i <= day; i++)
					{
						week_sum = week_sum + data_sum[i];
						week_points = week_points + data_points[i];
						week_overflow_occurances = week_overflow_occurances + overflows[i];
					}
				}
			
			}

			if (week != 1)
			{

				if (points == 0)                                                                //slightly redundant as to what is below, but the idea is to ensure that when no data is entered for a day, week will show everything up to the current day
				{
					for (int i = 7; i < day; i++)
					{
						week_sum = week_sum + data_sum[i];
						week_points = week_points + data_points[i];
						week_overflow_occurances = week_overflow_occurances + overflows[i];
					}
				}

				if (points != 0)
				{
					for (int i = 7; i <= day; i++)
					{
						week_sum = week_sum + data_sum[i];
						week_points = week_points + data_points[i];
						week_overflow_occurances = week_overflow_occurances + overflows[i];
					}
				}
				
			}

			cout << "Number of points entered this week: " << week_points << endl;
			cout << "Sum of all entries this week: " << week_sum << endl;
			
			if (week_overflow_occurances > 0)
			{
				cout << "Sum of all entries this week: " << week_sum << " * (3.4^(10^38) * " << week_overflow_occurances << endl;
			}
			
		}

		//moves to the next day
		if (selection == "next")
		{
			string confirmation;
			cout << "You are about to advance to day: " << day + 2 << ". Do you wish to proceed? (Y/N) ";     //let's be honest here, who wants to screw up by pressing the wrong command?
			cin >> confirmation;
			if (confirmation == "Y")
			{
				if (points == 0)                 //there is a possibility that no data could be entered at all; to accomadate, and to avoid a situation where junk data is printed out, IMMEDIATELY add in a zero to maintain a correct sum
				{
					data_sum[day] = 0;
					data_points[day] = 0;
				}
				day++;
				if (day > 6) //clearly, since we are only focused on either the first or second week, we NEED to reset the positions for the minimum and maximum in the week positions
				{
					week++;
					week_max = 0;
					week_min = 0;
				}
				day_max = 0;
				day_min = 0;
				points = 0;
				sum = 0;
				
			}
			else
			{
				cout << "Staying on day " << day + 1 << endl;
			}
			
		}
	}

	//prevents the program from ending upon completion
	system("pause"); 

}

