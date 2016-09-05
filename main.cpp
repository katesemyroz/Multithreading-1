

#include <vector>
#include <iostream>
#include <ctime>
#include <thread>
using namespace std;


void countQuantityOfFirstNumbers(int *mas, int fromI, int toI, int *Sum, int MainNum)
{
	int totalSum = 0;
	for (int i = fromI; i < toI; i++)
	{
		if (mas[i] == MainNum)
			totalSum++;
	}
	*Sum = totalSum;
}


int main()
{

	srand(time(NULL));
	
	int n = 1000000;// +rand() % 500;
	int *mas = new int[n];
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 50;
		mas[i] = num;
	}
	int MainNum = mas[0];
	unsigned int start_time = clock();
	int *Sum = new int[1];

	thread t(countQuantityOfFirstNumbers, mas, 0, n, &Sum[0], MainNum);
	t.join();

	cout << "AllSum:" << Sum[0] << endl;
	
	//double EvNorma = sqrt(Sum[0]);
	//cout << "EvNorma = " << EvNorma<<endl;


	unsigned int end_time = clock();
	int search_time = end_time - start_time;
	cout << "Working time of program 2:" << search_time << endl;


	cout << "\n\t\tSECOND PART OF PROGRAME\n\n";

	//-------------------------SECOND PART OF PROGRAME---------------------//

	int streams_number;
	for (int streams_number = 1; streams_number < 4; streams_number++)
	{
		unsigned int start_time2 = clock();
		int *Sum2 = new int[streams_number];
		vector<thread*> z;
		for (int i = 0; i < streams_number; i++)
		{
			if (i != streams_number-1)
				z.push_back(new thread(countQuantityOfFirstNumbers, mas, i*(n / streams_number), i*(n / streams_number) + (n / streams_number), &Sum2[i], MainNum));
			else
				z.push_back(new thread(countQuantityOfFirstNumbers, mas, i*(n / streams_number), n, &Sum2[i], MainNum));
		}
		for (int i = 0; i < streams_number; i++)
		{
			z[i]->join();
			delete z[i];
		}
		int AllSum = 0;
		for (int i = 0; i < streams_number; i++)
			AllSum += Sum2[i];
		cout << "Allsum = " << AllSum << endl;
		//EvNorma = sqrt(AllSum);
		//cout << "EvNorma = " << EvNorma << endl;

		unsigned int end_time2 = clock();
		int search_time2 = end_time2 - start_time2;
		cout << "Working time of program 2: " << search_time2 << endl;

		float koef = (float)search_time / (float)search_time2;
		cout << "Coefficient of speed: " << koef << endl;
		cout << "\tStreams number: " << streams_number + 1 << ", number of array elements: " << n << "; \n\n";
	
	}

	return 0;
}


