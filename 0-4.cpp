/*
Расположить в порядке возрастания элементы массива А(N), начиная с k-го элемента.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <algorithm>

using namespace std;

int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void outputArray(int*, int);
void sortArrayFromElement(int*, int, int);
void sortArrayFromElementMain(int*, int);

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
	initArrayRandom(Array, n, -n, n);
	outputArray(Array, n);
	sortArrayFromElementMain(Array, n);
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

void sortArrayFromElement(int *Array, int n, int k)
{
	char flag{ 0 };
	for (int i{ k }; i < (n - 1); ++i)
	{
		flag = 0;
		for (int j{ k }; j < (n - 1 - (i - k)); ++j)
			if (*(Array + j) > *(Array + (j + 1)))
			{
				flag = 1;
				swap(*(Array + j), *(Array + (j + 1)));
			}
		if (!flag)
			break;
	}
}

void sortArrayFromElementMain(int *Array, int n)
{
	int k{ 0 };
	do {
		cout << "Введите начиная с кокого элемента отсортировать массив: ";
		cin >> k;
		if ((k < 0) || (k >= n))
			cout << "Некорректное значение!\n\n";
		else
			break;
	} while (1);
	sortArrayFromElement(Array, n, k);
	outputArray(Array, n);
}