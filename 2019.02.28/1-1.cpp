/*
Даны точки плоскости своими координатами в виде двух одномерных массивов (случайные числа).
Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.
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
int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void initArrayNumber(int*, int, int);
void inputArray(int*, int);
template <class T>
void outputArray(T*, int);
void sortArray(int*, int);
void inputLine(double&, double&, double&);
double distanceToLine(double, double, double, int, int);
void setIntervalForRandom(int&, int&);
void outputPoints(int*, int*, double*, int);
void sortPoints(int*, int*, double*, int);
void calcDistance(double*, int*, int*, int, double, double, double);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	double a, b, c;
	inputLine(a, b, c);
	int n{ getCntOfArray() }, first, last;
	int *X{ getMemory<int>(n) };
	int *Y{ getMemory<int>(n) };
	setIntervalForRandom(first,last);
	initArrayRandom(X, n, first, last);
	initArrayRandom(Y, n, first, last);
	double *Distance{ getMemory<double>(n) };
	calcDistance(Distance, X, Y, n, a, b, c);
	outputPoints(X, Y, Distance, n);
	sortPoints(X, Y, Distance, n);
	outputPoints(X, Y, Distance, n);
	freeMemory(X);
	freeMemory(Y);
	freeMemory(Distance);
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

void inputLine(double &a, double &b, double &c)
{
	do {
		cout << "Введите коэффиценты прямой ax + by + c = 0 : ";
		cin >> a >> b >> c;
		if ((fabs(a) < EPS) && (fabs(b) < EPS))
			cout << "Некорректные значения!\n\n";
		else
			break;
	} while (1);
}

double distanceToLine(double a, double b, double c, int x, int y)
{
	return (fabs((a*x) + (b*y) + c) / sqrt((a*a) + (b*b)));
}

void setIntervalForRandom(int &a, int &b)
{
	cout << "Введите интервал для случ. чисел [a, b] : ";
	cin >> a >> b;
}

void outputPoints(int *X, int *Y, double *Distance, int n)
{
	cout << fixed;
	cout << "Точки (x, y, distance) : \n";
	for (int i{ 0 }; i < n; ++i)
		cout << *(X++) << "   " << *(Y++) << "   " << setprecision(3) << *(Distance++) << "\n";
	cout << "\n";
}

void sortPoints(int *X, int *Y, double *Distance, int n)
{
	char flag{ 0 };
	for (int i{ 0 }; i < (n - 1); ++i)
	{
		flag = 0;
		for (int j{ 0 }; j < (n - 1 - i); ++j, ++X, ++Y, ++Distance)
			if ((*Distance - *(Distance + 1)) > EPS)
			{
				flag = 1;
				swap(*X, *(X + 1));
				swap(*Y, *(Y + 1));
				swap(*Distance, *(Distance + 1));
			}
		X -= n - 1 - i;
		Y -= n - 1 - i;
		Distance -= n - 1 - i;
		if (!flag)
			break;
	}
}

void calcDistance(double *Distance, int *X, int *Y, int n, double a, double b, double c)
{
	for (int i{ 0 }; i < n; ++i)
		*(Distance++) = distanceToLine(a, b, c, *(X++), *(Y++));
}