/*
В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <algorithm>

using namespace std;

int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void outputArray(int*, int);
void findMaxLengthOfEqualElements(int*, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n{ getCntOfArray() };
	int *Array = new (nothrow) int[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		return 0;
	}
	initArrayRandom(Array, n, 0, 10);
	outputArray(Array, n);
	findMaxLengthOfEqualElements(Array, n);
	delete[] Array;
	Array = nullptr;
	system("pause");
	return 0;
}

int getCntOfArray()
{
	int cnt{ 0 };
	do {
		cout << "Введите размер массива: ";
		cin >> cnt;
		if (cnt <= 0)
			cout << "Ошибка! Размер массива должен быть положительным числом!\n\n";
		else
			break;
	} while (1);
	return cnt;
}

void initArrayRandom(int *Array, int n, int a, int b)
{
	for (int i{ 0 }; i < n; ++i)
		*(Array++) = rand() % (b - a + 1) + a;
}

void outputArray(int *Array, int n)
{
	cout << "Элементы массива: ";
	for (int i{ 0 }; i < n; ++i)
		cout << *(Array++) << " ";
	cout << "\n";
}

void findMaxLengthOfEqualElements(int *Array, int n)
{
	int maxLength{ 1 }, nowLegth{ 1 };
	for (int i{ 1 }; i < n; ++i, ++Array)
		if (*Array == *(Array - 1))
			nowLegth++;
		else
		{
			maxLength = max(maxLength, nowLegth);
			nowLegth = 1;
		}
	maxLength = max(maxLength, nowLegth);
	cout << "Максимальная длинна: " << maxLength << "\n";
}