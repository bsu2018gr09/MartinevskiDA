/*
В каждом столбце массива А(N,М) после первого отрицательного элемента
вставить максимальную цепочку из положительных элементов данного столбца.
Расположить столбцы в порядке возрастания по количеству вставленных элементов.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <cmath>
#include <algorithm>
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
int getCntDigits(int);
int getCntOutputSize(int**, int, int);
template <class T>
void outputArray(T**, int, int);
void initArrayRandom(int**, int, int, int, int);
void changeArray(int**, int, int);
template <class T>
void transposeArray(T**, T**, int, int);
int changeLine(int*, int);
void specialSort(int**, int, int*);

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
	changeArray(Array, n, m);
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
		delete[] * (Array + i);
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

int getCntDigits(int n)
{
	int ans{ 0 };
	while (n)
	{
		++ans;
		n /= 10;
	}
	return ans;
}

int getCntOutputSize(int** Array, int n, int m)
{
	char flag{ 0 };
	int ans{ 0 };
	for (int i{ 0 }; i < n; ++i, ++Array)
		for (int j{ 0 }; j < m; ++j)
		{
			if (*(*Array + j) < 0)
				flag = 1;
			ans = max(ans, getCntDigits(abs(*(*Array + j))));
		}
	ans += flag;
	return ans;
}

template <class T>
void outputArray(T** Array, int n, int m)
{
	cout << "Элементы массива: \n";
	char flag{ typeid(**Array).name() == typeid(int).name() };
	int cntOutputSize{0};
	if (flag)
		cntOutputSize = getCntOutputSize(Array, n, m);
	for (int i{ 0 }; i < n; ++i, ++Array)
		for (int j{ 0 }; j < m; ++j)
		{
			if (flag)
				cout << setw(cntOutputSize);
			cout << *(*Array + j) << ((j != (m - 1)) ? ' ' : '\n');
		}
	cout << "\n";
}

void initArrayRandom(int** Array, int n, int m, int a, int b)
{
	for (int i{ 0 }; i < n; ++i, ++Array)
		initArrayRandom(*Array, m, a, b);
}

template <class T>
void transposeArray(T** TransposeArray, T** Array, int n, int m)
{
	for (int i{ 0 }; i < m; ++i)
		for (int j{ 0 }; j < n; ++j)
			*(*(TransposeArray + i) + j) = *(*(Array + j) + i);
}

void changeArray(int** Array, int n, int m)
{
	int **TransposeArray = getMemory<int>(m, n);
	transposeArray(TransposeArray, Array, n, m);
	int *CntOfChangedElements = getMemory<int>(m);
	for (int i{ 0 }; i < m; ++i)
		*(CntOfChangedElements + i) = changeLine(*(TransposeArray + i), n);
	specialSort(TransposeArray, m, CntOfChangedElements);
	transposeArray(Array, TransposeArray, m, n);
	freeMemory(CntOfChangedElements);
	freeMemory(TransposeArray, m);
}

int changeLine(int* Array, int n)
{
	int indexOfFirstNegative{ -1 }, indexOfBeginMaxPosled{ -1 }, indexOfBeginNowPosled{ -1 }, cntOfMaxPosled{ 0 }, cntOfNowPosled{ 0 };
	for (int i{ 0 }; i < n; ++i)
	{
		if ((*(Array + i) < 0) && (indexOfFirstNegative == -1))
			indexOfFirstNegative = i;
		if (*(Array + i) > 0)
		{
			if (indexOfBeginNowPosled == -1)
				indexOfBeginNowPosled = i;
			++cntOfNowPosled;
		}
		else
		{
			if (cntOfNowPosled > cntOfMaxPosled)
			{
				cntOfMaxPosled = cntOfNowPosled;
				indexOfBeginMaxPosled = indexOfBeginNowPosled;
			}
			cntOfNowPosled = 0;
			indexOfBeginNowPosled = -1;
		}
	}
	if (cntOfNowPosled > cntOfMaxPosled)
	{
		cntOfMaxPosled = cntOfNowPosled;
		indexOfBeginMaxPosled = indexOfBeginNowPosled;
	}
	if (indexOfFirstNegative == -1)
		return 0;
	if (indexOfFirstNegative > indexOfBeginMaxPosled)
		indexOfFirstNegative -= cntOfMaxPosled;
	int *TMPArray = getMemory<int>(cntOfMaxPosled);
	for (int i{ 0 }; i < cntOfMaxPosled; ++i)
		*(TMPArray + i) = *(Array + indexOfBeginMaxPosled + i);
	for (int i{ indexOfBeginMaxPosled }; (cntOfMaxPosled + i) < n; ++i)
		*(Array + i) = *(Array + cntOfMaxPosled + i);
	for (int i{ n - 1 }; i > (indexOfFirstNegative + cntOfMaxPosled); --i)
		*(Array + i) = *(Array + i - cntOfMaxPosled);
	for (int i{ 0 }; i < cntOfMaxPosled; ++i)
		*(Array + indexOfFirstNegative + i + 1) = *(TMPArray + i);
	freeMemory(TMPArray);
	return cntOfMaxPosled;
}

void specialSort(int** Array, int n, int* CntOfChangedElements)
{
	char flag{ 0 };
	for (int i{ 0 }; i < (n - 1); ++i)
	{
		flag = 0;
		for (int j{ 0 }; j < (n - 1 - i); ++j)
			if (*(CntOfChangedElements + j) > *(CntOfChangedElements + j + 1))
			{
				swap(*(Array + j), *(Array + j + 1));
				swap(*(CntOfChangedElements + j), *(CntOfChangedElements + j + 1));
				flag = 1;
			}
		if (!flag)
			break;
	}
}