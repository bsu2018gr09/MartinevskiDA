/*
Подготовить для работы в аудитории функции для выделения памяти для двумерного массива, функции для инициализации, ввода, печати...
Прототипы функций:
void give_memory(int**&, int, int)//первый способ. Подумайте, почему обязательно надо тут &
int** give_memory(int, int)//второй способ
void init_array(int **,int,int)
void print_array(int **,int,int)
void free_array(int **,int,int)
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

template <class T>
T* getMemory(int);
template <class T>
void freeMemory(T*&);
void getCntOfArray(int&);
void initArrayRandom(int*, int, int, int);
void initArrayNumber(int*, int, int);
template <class T>
void inputArray(T*, int);
template <class T>
void outputArray(T*, int);
void sortArray(int*, int);
void setIntervalForRandom(int&, int&);
template <class T>
void getMemory(T**&, int, int);
template <class T>
T** getMemory(int, int);
template <class T>
void freeMemory(T**&, int);
void getCntOfArray(int&, int&);
template <class T>
void inputArray(T**, int, int);
template <class T>
void outputArray(T**, int, int);
void initArrayRandom(int**, int, int, int, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n, m, a, b;
	setIntervalForRandom(a, b);
	getCntOfArray(n, m);
	int** Array = getMemory<int>(n, m);
	initArrayRandom(Array, n, m, a, b);
	outputArray(Array, n, m);
	freeMemory(Array, n);
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

void getCntOfArray(int &n)
{
	do {
		cout << "Введите размер массива: ";
		cin >> n;
		if (n <= 0)
			cout << "Ошибка! Размер массива должен быть положительным числом!\n\n";
		else
			break;
	} while (1);
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

template <class T>
void inputArray(T *Array, int n)
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

template <class T>
void getMemory(T**& Array, int n, int m)
{
	Array = new (nothrow) T*[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
	for (int i{ 0 }; i < n; ++i)
		*(Array + i) = getMemory<T>(m);
}

template <class T>
T** getMemory(int n, int m)
{
	T** Array = new (nothrow) T*[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
	for (int i{ 0 }; i < n; ++i)
		*(Array + i) = getMemory<T>(m);
	return Array;
}

template <class T>
void freeMemory(T**& Array, int n)
{
	for (int i{ 0 }; i < n; ++i)
	{
		delete[] *(Array + i);
		*(Array + i) = nullptr;
	}
	delete[] Array;
	Array = nullptr;
}

void getCntOfArray(int& n, int& m)
{
	do {
		cout << "Введите размеры массива (n, m) : ";
		cin >> n >> m;
		if ((n <= 0) || (m <= 0))
			cout << "Ошибка! Размеры массива должны быть положительными числами!\n\n";
		else
			break;
	} while (1);
}

template <class T>
void inputArray(T** Array, int n, int m)
{
	cout << "Введите элементы массива: \n";
	for (int i{ 0 }; i < n; ++i, ++Array)
		for (int j{ 0 }; j < m; ++j)
			cin >> *(*Array + j);
}

template <class T>
void outputArray(T** Array, int n, int m)
{
	cout << "Элементы массива: \n";
	for (int i{ 0 }; i < n; ++i, ++Array)
		for (int j{ 0 }; j < m; ++j)
			cout << *(*Array + j) << ((j != (m - 1)) ? ' ' : '\n');
	cout << "\n";
}

void initArrayRandom(int** Array, int n, int m, int a, int b)
{
	for (int i{ 0 }; i < n; ++i, ++Array)
		initArrayRandom(*Array, m, a, b);
}