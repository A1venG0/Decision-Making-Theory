#include <iostream>
#include <vector>

using namespace std;

void Bord(vector<vector<char>> input)
{
	int pointsForFirstPlace = input[0].size() - 2;
	vector<int> points(input[0].size() - 1, 0);
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 1; j < input[i].size(); j++)
		{
			points[input[i][j] - 'a'] += pointsForFirstPlace - j + 1;
		}
	}
	vector<char> winner;
	int max = -1e7 - 5;
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i] > max)
		{
			winner.clear();
			max = points[i];
			winner.push_back('a' + i);
		}
		else if (points[i] == max)
			winner.push_back('a' + i);
	}
	cout << "Bord result: " << '\n';
	cout << "Winner(s): ";
	for (int i = 0; i < winner.size(); i++)
	{
		cout << winner[i] << ' ';
	}
	cout << '\n';
	cout << "Points: " << '\n';
	for (int i = 0; i < points.size(); i++)
	{
		cout << (char)('a' + i) << " : " << points[i] << '\n';
	}
}

long factorial(int n)
{
    long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

void Complende(vector<vector<char>> input)
{
	vector<int> points(input[0].size() - 1, 0);
	for (int i = 0; i < input[0].size() - 1; i++)
	{
		for (int j = 0; j < input[0].size() - 1; j++)
		{
			if (j <= i)
				continue;

			int firstElementCount = 0;
			int secondElementCount = 0;
			char firstElement = 'a' + i;
			char secondElement = 'a' + j;
			for (int k = 0; k < input.size(); k++)
			{
				for (int m = 1; m < input[k].size(); m++)
				{
					if (input[k][m] == firstElement)
					{
						firstElementCount += input[k][0] - '0';
						break;
					}
					else if (input[k][m] == secondElement)
					{
						secondElementCount += input[k][0] - '0';
						break;
					}
				}
			}
			if (firstElementCount >= secondElementCount)
				points[firstElement - 'a']++;
			else	
				points[secondElement - 'a']++;
		}
	}
	vector<char> winner;
	int max = -1e7 - 5;
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i] > max)
		{
			winner.clear();
			max = points[i];
			winner.push_back('a' + i);
		}
		else if (points[i] == max)
			winner.push_back('a' + i);
	}
	cout << "Complende result: " << '\n';
	cout << "Winner(s): ";
	for (int i = 0; i < winner.size(); i++)
	{
		cout << winner[i] << ' ';
	}
	cout << '\n';
	cout << "Points: " << '\n';
	for (int i = 0; i < points.size(); i++)
	{
		cout << (char)('a' + i) << " : " << points[i] << '\n';
	}
}

void ParallelExclusion(vector<vector<char>> input)
{
	cout << "ParallelExclusion result: " << '\n';
	vector<int> points(input[0].size() - 1, 0);
	int count = input[0].size() - 1;
	for (int i = 0; i < input[0].size() - 1; i++)
	{
		for (int j = 0; j < input[0].size() - 1; j++)
		{
			if (j <= i)
				continue;

			int firstElementCount = 0;
			int secondElementCount = 0;
			char firstElement = 'a' + i;
			char secondElement = 'a' + j;
			for (int k = 0; k < input.size(); k++)
			{
				for (int m = 1; m < input[k].size(); m++)
				{
					if (input[k][m] == firstElement)
					{
						firstElementCount += input[k][0] - '0';
						break;
					}
					else if (input[k][m] == secondElement)
					{
						secondElementCount += input[k][0] - '0';
						break;
					}
				}
			}
			if (firstElementCount >= secondElementCount)
				points[firstElement - 'a']++;
			else	
				points[secondElement - 'a']++;
		}
	}

	vector<int> nextRound;
	for (int i = 0;  i < points.size(); i++)
	{
		nextRound.push_back(i);
	}
	while (nextRound.size() != 1)
	{
		vector<int> temp;
		for (int i = 0; i < nextRound.size() - 1; i += 2)
		{
			cout << "Pair: " << (char)('a' + nextRound[i]) << ' ' << (char)('a' + nextRound[i + 1]) << ' ';
			if (points[i] >= points[i + 1])
			{
				cout << "winner: " << (char)('a' + nextRound[i]) << '\n';
				temp.push_back(i);
			}
			else
			{
				cout << "winner: " << (char)('a' + nextRound[i + 1]) << '\n';
				temp.push_back(i + 1);
			}	
				
		}
		nextRound = temp;
	}

	cout << "ParallelExclusion winner: " << (char)('a' + nextRound[0]) << '\n';
	
}



int main()
{

	vector<vector<char>> input;
	vector<char> columnOne = {'5', 'c', 'd', 'a', 'b'};
	vector<char> columnTwo = {'4', 'b', 'a', 'd', 'c'};
	vector<char> columnThree = {'2', 'a', 'b', 'c', 'd'};
	input.push_back(columnOne);
	input.push_back(columnTwo);
	input.push_back(columnThree);

	Bord(input);

	cout << "---------------------------" << '\n';
	Complende(input);
	cout << "---------------------------" << '\n';
	ParallelExclusion(input);

	return 0;
}