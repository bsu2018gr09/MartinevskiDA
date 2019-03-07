/*
В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.
*/

#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

int getCntOfArray();
void initArrayRandom(int*, int, int, int);
void initArrayNumber(int*, int, int);
void outputArray(int*, int);
void findCntRepeatElements(int*, int);

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
	findCntRepeatElements(Array, n);
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

void initArrayNumber(int *Array, int n, int number)
{
	for (int i{ 0 }; i < n; ++i)
		*(Array++) = number;
}

void outputArray(int *Array, int n)
{
	cout << "Элементы массива: ";
	for (int i{ 0 }; i < n; ++i)
		cout << *(Array++) << " ";
	cout << "\n";
}

void findCntRepeatElements(int *Array, int n)
{
	int cnt{ 11 };
	int *cntElements = new (nothrow) int[cnt];
	int *pCntElements{ cntElements };
	int cntRepeatElements{ 0 };
	if (!cntElements)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
	initArrayNumber(cntElements, cnt, 0);
	for (int i{ 0 }; i < n; ++i)
		(*(cntElements + *(Array++)))++;
	for (int i{ 0 }; i < cnt; ++i)
		cntRepeatElements += (*(pCntElements++) > 1) ? 1 : 0;
	cout << "Количество повторяющихся элементов: " << cntRepeatElements << "\n";
	delete[] cntElements;
	cntElements = nullptr;
}