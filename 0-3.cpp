/*
Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N.
Написать функцию циклического сдвига элементов массива вправо на k элементов.
*/

#include <iostream>
#include <clocale>
#include <ctime>
#include <algorithm>

using namespace std;

int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void outputArray(int*, int);
void reverseArrayOnInterval(int*, int, int, int);
void cyclicShiftRightArray(int*, int);

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
	cyclicShiftRightArray(Array, n);
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

void reverseArrayOnInterval(int *Array, int n, int first, int last)
{
	int cnt{ (last - first + 1) / 2 };
	for (int i{ 0 }; i < cnt; ++i)
		swap(*(Array + (first + i)), *(Array + (last - i)));
}

void cyclicShiftRightArray(int *Array, int n)
{
	int k{ 0 };
	do {
		cout << "Введите на сколько надо сдвинуть элемнты вправо: ";
		cin >> k;
		if (k < 0)
			cout << "Число должно быть неотрицательным!\n\n";
		else
			break;
	} while (1);
	k = k % n;
	reverseArrayOnInterval(Array, n, 0, n - 1);
	reverseArrayOnInterval(Array, n, 0, k - 1);
	reverseArrayOnInterval(Array, n, k, n - 1);
	outputArray(Array, n);
}