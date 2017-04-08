#include "Topart.h"


int main()
{
	string path = "g:\\Kerti\\Projects\\ItechChallenge\\TopartUnitTest\\UnitTest\\test1.txt";
	Graph g;
	g.StartProgram(path);
	/*
	//Generate test data
	path = "g:\\Kerti\\Projects\\ItechChallenge\\TopartUnitTest\\UnitTest\\test3.txt";
	fstream infile;
	infile.open(path);

	//Print number of city
	int numberOfCity = 10000;
	int printedNumberOfCity = 0;
	infile << numberOfCity << endl;
	string baseCityName = "Graphi";
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	int numberOfAlphabet = 26;

		for (int i = 0; i < numberOfAlphabet; i++)
		{
			for (int j = 0; j < numberOfAlphabet; j++)
			{
				for (int k = 0; k < numberOfAlphabet; k++)
				{
					infile << baseCityName << alphabet[i] << alphabet[j] << alphabet[k] << endl;
					printedNumberOfCity++;
					if (printedNumberOfCity == numberOfCity)
						break;
				}
				if (printedNumberOfCity == numberOfCity)
					break;
			}

			if (printedNumberOfCity == numberOfCity)
				break;
		}

		for (int i = 0; i < numberOfCity; i++)
		{
			infile << (rand() % 9 + 1) * 10 << " ";
		}

		infile << endl;*/
	
	return 1;
}