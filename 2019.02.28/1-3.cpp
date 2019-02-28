/*
Элементы массива А(N), значения которых – простые числа,
расположить в порядке возрастания, не нарушая порядка следования других элементов.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

template <class T>
T* getMemory(int);
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
void specialSort(int*, int);
bool isSimple(int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n{ getCntOfArray() };
	int *Array{ getMemory<int>(n) };
	inputArray(Array, n);
	specialSort(Array, n);
	outputArray(Array, n);
	freeMemory(Array);
	system("pause");
	return 0;
}

template <class T>
T* getMemory(int n)
{
	T *Array = new (nothrow) T[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
	return Array;
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

bool isSimple(int n)
{
	if (((n != 2) && (!(n % 2))) || (n < 2))
		return 0;
	for (int i{ 3 }; (i*i) < n; i += 2)
		if (!(n%i))
			return 0;
	return 1;
}

void specialSort(int *Array, int n)
{
	int *beginArray{ Array };
	int *pSimpleNow{ nullptr };
	int *pSimplePrevious{ nullptr };
	int cnt{ n - 1 };
	char flag{ 0 };
	for (int i{ 0 }; i < n; ++i)
	{
		flag = 0;
		pSimpleNow = nullptr;
		pSimplePrevious = nullptr;
		for (int j{ 0 }; j <= cnt; ++j, ++Array)
			if (pSimpleNow && isSimple(*Array) && (*Array < *pSimpleNow))
			{
				flag = 1;
				swap(*Array, *pSimpleNow);
				pSimplePrevious = pSimpleNow;
				pSimpleNow = Array;
			}
			else
				if (isSimple(*Array))
				{
					pSimplePrevious = pSimpleNow;
					pSimpleNow = Array;
				}
		Array = beginArray;
		cnt = pSimplePrevious - beginArray;
		if (!flag)
			break;
	}
}