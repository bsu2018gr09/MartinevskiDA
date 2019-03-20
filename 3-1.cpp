/**
Найти и вывести на экран все слова строки, в которых все буквы различны.
Вставить перед такими словами заданную подстроку.
**/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

int MAX_LEN{ 255 };
char Separators[] = " .,!?;:()\t";

template <class T>
T* getMemory(int);
template <class T>
void freeMemory(T*&);
bool isItWordWithDifferentLetters(char*);
void solve(char*, char*);
void strins(char*, int, char*);

int main()
{
	setlocale(LC_ALL, "Russian");
	char* Str{ getMemory<char>(MAX_LEN) };
	char* SSubStr{ getMemory<char>(MAX_LEN) };
	cout << "Введите строку:\n";
	cin.getline(Str, MAX_LEN);
	cout << "Введите подстроку:\n";
	cin.getline(SSubStr, MAX_LEN);
	solve(Str, SSubStr);
	cout << Str << "\n";
	freeMemory(Str);
	freeMemory(SSubStr);
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

void solve(char* Str, char* SSubStr)
{
	cout << "\nСлова с различными буквами:\n";
	int cnt{ 0 };
	int lenSSubStr{ (int)strlen(SSubStr) };
	char* Word{ getMemory<char>(MAX_LEN) };
	while (*Str)
	{
		Str += strspn(Str, Separators);
		cnt = strcspn(Str, Separators);
		if (!cnt)
			break;
		strncpy(Word, Str, cnt);
		Word[cnt] = '\0';
		if (isItWordWithDifferentLetters(Word))
		{
			cout << Word << "\n";
			strins(Str, 0, SSubStr);
			Str += lenSSubStr;
		}
		Str += cnt;
	}
	cout << "\n";
	freeMemory(Word);
}

void strins(char* Str, int pos, char* SSubStr)
{
	char* TMP{ getMemory<char>(MAX_LEN) };
	strcpy(TMP, SSubStr);
	strcat(TMP, Str + pos);
	strcpy(Str + pos, TMP);
	freeMemory(TMP);
}

bool isItWordWithDifferentLetters(char* Word)
{
	char* UsedLetters{ getMemory<char>(MAX_LEN) };
	char* TMP{ getMemory<char>(2) };
	TMP[1] = '\0';
	UsedLetters[0] = '\0';
	while (*Word)
	{
		if (!strchr(UsedLetters, *Word))
		{
			TMP[0] = *Word;
			strcat(UsedLetters, TMP);
		}
		else
		{
			freeMemory(UsedLetters);
			freeMemory(TMP);
			return false;
		}
		++Word;
	}
	freeMemory(UsedLetters);
	freeMemory(TMP);
	return true;
}