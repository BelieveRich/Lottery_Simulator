#include <iostream>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

// Constant Declaration
static const uint16_t NUM_MAX_PICK = 6;

// Global Variable Declaration
static uint16_t nPicks[NUM_MAX_PICK];
static uint16_t nWinNums[NUM_MAX_PICK];

// Forward Declaration
void GenerateLotteryWinNumbers();
void SortNumbers(uint16_t* nInput, uint16_t length);
bool CheckIfUserWins();

// Main Implementation
int main()
{
	cout << "===============================================================\n";
	cout << "\t\tLottery Simulator Program\n";
	cout << "\t\tAuthor: Richard Chen\tDate:2019/2/6\n";
	cout << "===============================================================\n\n\n\n";
	
	// 1. Let user enters the lottery picks
	memset(nPicks, 0, sizeof(nPicks[0]) * NUM_MAX_PICK);
	cout << "Enter your lottery picks (6 numbers from 1 ~ 49):\n";
	for (int i = 0; i < NUM_MAX_PICK; i++)
	{
		cin >> nPicks[i];
	}
	
	cout << "Your picks are:";
	for (int i = 0; i <NUM_MAX_PICK; i++)
	{
		cout << " " << nPicks[i];
	}
	
	// 2. Generate the lottery winning numbers
	GenerateLotteryWinNumbers();
	
	// 3. Determine whether your pick won or not1
	CheckIfUserWins();
	return 0;
}

// This function generates the winning lottery numbers
void GenerateLotteryWinNumbers()
{
	uint16_t nWinPick;
	srand(time(NULL));
	bool bGenerateNumAccepted = false;
	
	for (int i = 0; i < NUM_MAX_PICK; i++)
	{
		do
		{
			// Random generate win number from 1 to 49
			nWinPick = rand() % 49 + 1;
			for (int j = 0; j < NUM_MAX_PICK; j++)
			{
				if (nWinPick == nWinNums[j])
				{
					break;
				}
				if (j == NUM_MAX_PICK - 1)
				{
					bGenerateNumAccepted = true;
					nWinNums[i] = static_cast<uint16_t>(nWinPick);
				}
			}
		} while(bGenerateNumAccepted == false);
		bGenerateNumAccepted = false;
	}
	
	cout << "\nThe winning numbers are: ";
	for (int i = 0; i < NUM_MAX_PICK; i++)
	{
		cout << " " << nWinNums[i];
	}
	
	// Call sort to put numbers in orders
	SortNumbers(nWinNums, NUM_MAX_PICK);
	cout << "\nSorted winning numbers are: ";
	for (int i = 0; i < NUM_MAX_PICK; i++)
	{
		cout << " " << nWinNums[i];
	}	
}

void SortNumbers(uint16_t* nInput, uint16_t length)
{
	// 1. Sort the numbers and store in malloc 
	uint16_t* nTempArray = (uint16_t*)(malloc(sizeof(nInput[0]) * length));
	uint16_t min = UINT16_MAX;
	int16_t min_index = INT16_MAX;
	
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (nInput[j] < min)
			{
				min = nInput[j];
				min_index = j;
			}
		}
		nTempArray[i] = min;
		nInput[min_index] = UINT16_MAX;
		min = INT16_MAX;
		min_index = UINT16_MAX;
	}
	
	// 2. Save the sorted numbers into the original array
	memcpy(nInput, nTempArray, sizeof(nInput[0]) * length);
	
	// 3. Free malloc memory
	delete nTempArray;
}

bool CheckIfUserWins()
{
	bool result = false;
	int16_t nMatchedIndex[NUM_MAX_PICK];
	memset(nMatchedIndex, 0, sizeof(nMatchedIndex[0])*NUM_MAX_PICK);
	int16_t nMatchedIdxCount = 0;
	
	for (int i = 0; i < NUM_MAX_PICK; i++)
	{
		for (int j = 0; j <NUM_MAX_PICK; j++)
		{
			if (nWinNums[j] == nPicks[i])
			{
				nMatchedIndex[nMatchedIdxCount++] = i;
			}
		}
	}
	
	// Output how many numbers matched
	cout << "\nCongratulation Your number matched: " << nMatchedIdxCount << endl;
	if (nMatchedIdxCount > 0)
	{
		for (int i = 0; i < nMatchedIdxCount; i++)
		{
			cout << (i == 0?"Matching Numbers are: ":", ") << nPicks[nMatchedIndex[i]];
		}
		
		if (nMatchedIdxCount == NUM_MAX_PICK)
		{
			cout << "CONGRATULATION!! OH MY GOD!! YOU HAVE WON THE FIRST PRIZE 100MIL!!!" << endl;
			return true;
		}
	}
	return result;
}