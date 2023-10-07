#include <bits/stdc++.h>
#define ll long long

int N = 20;

void runCalculation(int* arr, std::function<bool(int, int)>func, bool* result)
{
	bool flag = true;
	int i = 0, j = 1;
	while(true)
	{
		if (func(arr[i], arr[j]))
		{
			result[j] = false;
			if (j < N - 1)
				j++;
			else
			{
				if (i < N - 2)
				{
					i++;
					j = i + 1;
				}
				else
					flag = false;
			}
		}
		else
		{
			if (func(arr[j], arr[i]))
			{
				result[i] = false;
				if (i < N - 2)
				{
					i++;
					j = i + 1;
				}
				else
					flag = false;
			}
			else
			{
				if (j < N - 1)
					j++;
				else
				{
					if (i < N - 2)
					{
						i++;
						j = i + 1;
					}
					else
						flag = false;
				}
			}
		}

		if (!flag)
			break;
	}
}

int main() {
    int rowOne[20] = {40, 29, 31, 17, 97, 71, 81, 75, 9, 27, 67, 56, 97, 53, 86, 65, 6, 83, 19, 24 };
    int rowTwo[20] = {28, 71, 32, 29, 3, 19, 70, 68, 8, 15, 40, 49, 96, 23, 18, 45, 46, 51, 21, 55 };
    int rowThree[20] = {79, 88, 64, 28, 41, 50, 93, 51, 34, 64, 24, 14, 87, 56, 43, 91, 27, 65, 59, 36 };
    int* allRows = new int[60];
    for (int i = 0; i < sizeof(rowOne) / sizeof(rowOne[0]); i++)
    {
    	allRows[i * 3] = rowOne[i];
    	allRows[i * 3 + 1] = rowTwo[i];
    	allRows[i * 3 + 2] = rowThree[i];
    }

    auto pareto = [&](int first, int second)
    {
    	return (((first / 10) > (second / 10) && (first % 10) >= (second % 10)) || 
    	((first / 10) >= (second / 10) && (first % 10) > (second % 10)));
    	
    };

    auto slayter = [&](int first, int second)
    {
    	return ((first / 10) > (second / 10) && (first % 10) > (second % 10));
    };

    bool* result = new bool[N];
    for (int i = 0; i < N; i++)
    	result[i] = true;

    
    runCalculation(rowOne, pareto, result);

    std::cout << "Indices for the first row (Pareto): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;
    runCalculation(rowOne, slayter, result);

     std::cout << "Indices for the first row (slayter): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;

    
    runCalculation(rowTwo, pareto, result);

    std::cout << "Indices for the second row (Pareto): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;
    runCalculation(rowTwo, slayter, result);
    
     std::cout << "Indices for the second row (slayter): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;

    
    runCalculation(rowThree, pareto, result);

    std::cout << "Indices for the third row (Pareto): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;
    runCalculation(rowThree, slayter, result);
    
     std::cout << "Indices for the third row (slayter): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    N = 60;
    result = new bool[N];
    for (int i = 0; i < N; i++)
    	result[i] = true;

    
    runCalculation(allRows, pareto, result);

    std::cout << "Indices for combined rows (Pareto): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < N; i++)
    	result[i] = true;
    runCalculation(allRows, slayter, result);
    
     std::cout << "Indices for combined rows (slayter): ";
    for (int i = 0; i < N; i++)
    {
    	if (result[i])
    		std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    delete[] allRows;
    delete[] result;

  return 0;
}