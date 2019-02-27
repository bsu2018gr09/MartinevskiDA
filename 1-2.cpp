/*
Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования.
Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

template <class T>
void getMemory(T*&, int);
template <class T>
void freeMemory(T*&);
int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void initArrayNumber(int*, int, int);
void inputArray(int*, int);
template <class T>
void outputArray(T*, int);
void sortArray(int*, int);
void setIntervalForRandom(int&, int&);
void putPositiveToEnd(int*, int);
void sortNegative1(int*, int); //Вариант если нолики остаются на своих местах
void sortNegative2(int*, int); //Вариант если нолики будут находиться между отрицательными и положительными
void sortNegative3(int*, int); //Вариант если нолики будут в самом начале
void specialSort1(int*, int);
void specialSort2(int*, int);
void reverseArrayOnInterval(int*, int, int, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n{ getCntOfArray() }, a, b;
	int *Array;
	getMemory(Array, n);
	setIntervalForRandom(a, b);
	initArrayRandom(Array, n, a, b);
	outputArray(Array, n);
	putPositiveToEnd(Array, n);
	outputArray(Array, n);
	sortNegative1(Array, n);   //Вариант если нолики остаются на своих местах
	outputArray(Array, n);
	freeMemory(Array);
	system("pause");
	return 0;
}

template <class T>
void getMemory(T *&Array, int n)
{
	Array = new (nothrow) T[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
}

template <class T>
void freeMemory(T*& Array)
{
	delete[] Array;
	Array = nullptr;
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

void initArrayNumber(int *Array, int n, int number)
{
	for (int i{ 0 }; i < n; ++i)
		*(Array++) = number;
}

void inputArray(int *Array, int n)
{
	cout << "Введите элементы массива: ";
	for (int i{ 0 }; i < n; ++i)
		cin >> *(Array++);
}

template <class T>
void outputArray(T *Array, int n)
{
	cout << "Элементы массива: ";
	for (int i{ 0 }; i < n; ++i)
		cout << *(Array++) << " ";
	cout << "\n";
}

void sortArray(int *Array, int n)
{
	char flag{ 0 };
	for (int i{ 0 }; i < (n - 1); ++i)
	{
		flag = 0;
		for (int j{ 0 }; j < (n - 1 - i); ++j, ++Array)
			if (*Array > *(Array + 1))
			{
				flag = 1;
				swap(*Array, *(Array + 1));
			}
		Array -= n - 1 - i;
		if (!flag)
			break;
	}
}

void setIntervalForRandom(int &a, int &b)
{
	cout << "Введите интервал для случ. чисел [a, b] : ";
	cin >> a >> b;
}

void putPositiveToEnd(int *Array, int n)
{
	int cnt;
	Array += n - 2;
	for (int i{ n - 2 }; i >= 0; --i, --Array)
		if ((*Array > 0) && (*(Array + 1) <= 0))
		{
			cnt = 1;
			while ((*(++Array) <= 0) && ((i + cnt) < n))
			{
				swap(*(Array), *(Array - 1));
				cnt++;
			}
			Array -= cnt;
		}
}

//Вариант если нолики остаются на своих местах
void sortNegative1(int *Array, int n)
{
	int k{ n };
	for (int i{ 0 }; i < n; ++i)
		if (*(Array++) > 0)
		{
			k = i;
			break;
		}
	Array -= k + 1;
	specialSort1(Array, k);
}

//Вариант если нолики будут находиться между отрицательными и положительными
void sortNegative2(int *Array, int n)
{
	int k{ n };
	for (int i{ 0 }; i < n; ++i)
		if (*(Array++) > 0)
		{
			k = i;
			break;
		}
	Array -= k + 1;
	specialSort2(Array, k);
}

//Вариант если нолики будут в самом начале
void sortNegative3(int *Array, int n)
{
	int k{ n };
	for (int i{ 0 }; i < n; ++i)
		if (*(Array++) > 0)
		{
			k = i;
			break;
		}
	Array -= k + 1;
	sortArray(Array, k);
	reverseArrayOnInterval(Array, n, 0, k - 1);
}

void reverseArrayOnInterval(int *Array, int n, int first, int last)
{
	int cnt{ (last - first + 1) / 2 };
	for (int i{ 0 }; i < cnt; ++i)
		swap(*(Array + (first + i)), *(Array + (last - i)));
}

void specialSort1(int *Array, int n)
{
	int *beginArray{ Array };
	int *pNegativeNow{ nullptr };
	int *pNegativePrevious{ nullptr };
	int cnt{ n - 1 };
	char flag{ 0 };
	for (int i{ 0 }; i < n; ++i)
	{
		flag = 0;
		pNegativeNow = nullptr;
		pNegativePrevious = nullptr;
		for (int j{ 0 }; j <= cnt; ++j, ++Array)
			if (pNegativeNow && *Array && (*Array > *pNegativeNow))
			{
				flag = 1;
				swap(*Array, *pNegativeNow);
				pNegativePrevious = pNegativeNow;
				pNegativeNow = Array;
			}
			else
				if (*Array)
				{
					pNegativePrevious = pNegativeNow;
					pNegativeNow = Array;
				}
		Array = beginArray;
		cnt = pNegativePrevious - beginArray;
		if (!flag)
			break;
	}
}

void specialSort2(int *Array, int n)
{
	char flag{ 0 };
	for (int i{ 0 }; i < (n - 1); ++i)
	{
		flag = 0;
		for (int j{ 0 }; j < (n - 1 - i); ++j, ++Array)
			if (((*Array < *(Array + 1)) && (*(Array + 1))) || ((*Array > *(Array + 1)) && (!*Array)))
			{
				flag = 1;
				swap(*Array, *(Array + 1));
			}
		Array -= n - 1 - i;
		if (!flag)
			break;
	}
}