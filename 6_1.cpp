/**
Класс линейных уравнений с использованием динамической памяти(выбор количества неизвестных)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

const int maxStringLen{ 255 };
const int outputPrecision{ 3 };
const double EPS{ 1e-9 };

const int ERROR_NO_MEMORY{ 0 };
const int ERROR_WRONG_CNT_MEMORY{ 1 };
const int stringEnd{ 1 };
const char stringEndSymbol{ '\0' };
const char* const symbolsString = " +-._abcdefghijklcerrcerrmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char* const symbolsName = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char* const allLetters = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* const allDigits = "0123456789";

template <class T>
T* getMemory(int n)
{
	if (n <= 0)
	{
		cerr << "Ошибка! Некорректное значение для выделения памяти\n";
		system("pause");
		exit(ERROR_WRONG_CNT_MEMORY);
	}
	T *array = new (nothrow) T[n];
	if (!array)
	{
		cerr << "Ошибка выделения памяти!\n";
		system("pause");
		exit(ERROR_NO_MEMORY);
	}
	return array;
}

template <class T>
void freeMemory(T*& array)
{
	delete[] array;
	array = nullptr;
}

bool checkStringForData(char* str)
{
	char* strBegin{ str };
	while (strcspn(str, " ") < strlen(str))
	{
		strcpy(str, str + strspn(str, " "));
		str += strcspn(str, " ");
	}
	str = strBegin;
	if ((strlen(str) > 0) && ((str[0] == '+') || (str[0] == '-')))
		++str;
	int pointPos{ strcspn(str,".") };
	if ((pointPos == strlen(str)) && ((!strlen(str)) || (strspn(str, symbolsName) < strlen(str))))
		return false;
	else
	{
		char* afterFirsPoint{ str + pointPos + 1 };
		if ((pointPos < strlen(str)) && ((!pointPos) || (!strlen(afterFirsPoint)) || (strspn(str, symbolsName) < pointPos) || (strspn(afterFirsPoint, symbolsName) < strlen(afterFirsPoint))
			|| (strcspn(str, allLetters) < pointPos) || (!strcspn(afterFirsPoint, allLetters))))
			return false;
	}
	return true;
}

bool stringsEqual(const char* string1, const char* string2)
{
	if (strlen(string1) != strlen(string2))
		return false;
	int len{ strlen(string1) };
	for (int i{ 0 }; i < len; ++i)
		if (string1[i] != string2[i])
			return false;
	return true;
}

bool checkDataName(const char* name)
{
	if ((strlen(name)) && ((strspn(name, symbolsName) < strlen(name)) || (!strcspn(name, allDigits))))
		return false;
	return true;
}

bool checkString(char* str, int& cntData)
{
	if ((!strlen(str)) || (strspn(str, symbolsString) < strlen(str)))
		return false;
	char* strBegin{ str };
	while (strcspn(str, " ") < strlen(str))
	{
		strcpy(str, str + strspn(str, " "));
		str += strcspn(str, " ");
	}
	str = strBegin;
	if ((strlen(str) > 0) && ((str[0] == '+') || (str[0] == '-')))
		++str;
	int signPos{ strcspn(str,"+-") };
	char* tmp{ getMemory<char>(maxStringLen) };
	while (signPos < strlen(str))
	{
		strncpy(tmp, str, signPos);
		tmp[signPos] = '\0';
		if (!checkStringForData(tmp))
		{
			freeMemory(tmp);
			return false;
		}
		++cntData;
		str += signPos;
		signPos = strcspn(str + 1, "+-") + 1;
	}
	strncpy(tmp, str, signPos);
	tmp[signPos] = '\0';
	if (!checkStringForData(tmp))
	{
		freeMemory(tmp);
		return false;
	}
	++cntData;
	freeMemory(tmp);
	return true;
}

class Data
{
private:
	char* name;
	double coefficient;

	void parseString(char* str)
	{
		bool flag{ 0 };
		if ((str[0] == '+') || (str[0] == '-'))
		{
			if (str[0] == '-')
				flag = 1;
			++str;
		}
		int pointPos{ strcspn(str,".") };
		if (pointPos == strlen(str))
		{
			char* lettersBegin{ str + strspn(str,allDigits) };
			name = getMemory<char>(strlen(lettersBegin) + stringEnd);
			strcpy(name, lettersBegin);
			strcpy(lettersBegin, "\0");
			if (!strlen(str))
				coefficient = 1;
			else
				coefficient = atof(str);
		}
		else
		{
			char* lettersBegin{ str + pointPos + 1 + strspn(str + pointPos + 1,allDigits) };
			name = getMemory<char>(strlen(lettersBegin) + stringEnd);
			strcpy(name, lettersBegin);
			strcpy(lettersBegin, "\0");
			str[pointPos] = ',';
			coefficient = atof(str);
		}
		if (flag)
			coefficient *= -1;
	}
public:
	~Data()
	{
		freeMemory(name);
		//cout<<"Destructor for Data\n";
	}

	Data() : name{ getMemory<char>(stringEnd) }, coefficient{ 0 }
	{
		name[0] = stringEnd;
		//cout<<"Constructor №1 for Data\n";
	};

	Data(const char* newName, double newCoefficient) : name{ getMemory<char>(strlen(newName) + stringEnd) }, coefficient{ newCoefficient }
	{
		if (!checkDataName(newName))
		{
			cerr << "Ошибка! Некорректное название неизвестной! Установлено значение по умолчанию\n\n";
			freeMemory(name);
			name = getMemory<char>(stringEnd);
			name[0] = stringEnd;
		}
		else
			strcpy(name, newName);
		//cout<<"Constructor №2 for Data\n";
	}

	Data(const Data& newData) : name{ getMemory<char>(strlen(newData.name) + stringEnd) }, coefficient{ newData.coefficient }
	{
		strcpy(name, newData.name);
		//cout<<"Constructor №3 for Data\n";
	}

	Data(const char* str) : coefficient{ 0 }
	{
		char* tmp{ getMemory<char>(strlen(str) + stringEnd) };
		strcpy(tmp, str);
		if (!checkStringForData(tmp))
		{
			cerr << "Ошибка! Введен некорректный моном! Установлено значение по умолчанию\n\n";
			name = getMemory<char>(stringEnd);
			name[0] = stringEnd;
		}
		else
			parseString(tmp);
		freeMemory(tmp);
		//cout<<"Constructor №4 for Data\n";
	}

	void setString(const char* str)
	{
		char* tmp{ getMemory<char>(strlen(str) + stringEnd) };
		strcpy(tmp, str);
		if (!checkStringForData(tmp))
			cerr << "Ошибка! Введен некорректный моном! Изменения не применены\n\n";
		else
		{
			freeMemory(name);
			parseString(tmp);
		}
		freeMemory(tmp);
	}

	void setName(const char* newName)
	{
		if (!checkDataName(newName))
			cerr << "Ошибка! Некорректное название неизвестной! Изменения не применены\n\n";
		else
		{
			freeMemory(name);
			name = getMemory<char>(strlen(newName) + stringEnd);
			strcpy(name, newName);
		}
	}

	void setCoefficient(double newCoefficient)
	{
		coefficient = newCoefficient;
	}

	void setNameAndCoefficient(const char* newName, double newCoefficient)
	{
		if (!checkDataName(newName))
			cerr << "Ошибка! Некорректное название неизвестной! Изменения не применены\n\n";
		else
		{
			freeMemory(name);
			name = getMemory<char>(strlen(newName) + stringEnd);
			strcpy(name, newName);
			coefficient = newCoefficient;
		}
	}

	void setData(const Data& newData)
	{
		if (this == &newData)
			return;
		freeMemory(name);
		name = getMemory<char>(strlen(newData.name) + stringEnd);
		strcpy(name, newData.name);
		coefficient = newData.coefficient;
	}

	double getCoefficient() const
	{
		return coefficient;
	}

	char* getName() const
	{
		return name;
	}

	Data& operator =(const Data& newData)
	{
		if (this == &newData)
			return *this;
		coefficient = newData.coefficient;
		freeMemory(name);
		name = getMemory<char>(strlen(newData.name) + ((!strlen(newData.name)) ? 1 : 0));
		strcpy(name, newData.name);
		return *this;
	}

	Data operator *(double coeff)
	{
		return Data{name, coefficient*coeff};
	}

	Data operator /(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cerr << "Ошибка! Деление на 0! Операция не выполена\n\n";
			return Data{name, coefficient};
		}
		return Data{name, coefficient / coeff};
	}

	Data operator +(double coeff)
	{
		return Data{name, coefficient + coeff};
	}

	Data operator -(double coeff)
	{
		return Data{name, coefficient - coeff};
	}

	Data operator -()
	{
		return Data{name, -coefficient};
	}

	Data operator ++(int)
	{
		++(*this);
		return Data{name, coefficient - 1};
	}

	Data operator --(int)
	{
		--(*this);
		return Data{name, coefficient + 1};
	}

	Data& operator ++()
	{
		++coefficient;
		return *this;
	}

	Data& operator --()
	{
		--coefficient;
		return *this;
	}

	Data& operator *=(double coeff)
	{
		coefficient *= coeff;
		return *this;
	}

	Data& operator /=(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cerr << "Ошибка! Деление на 0! Операция не выполена\n\n";
			return *this;
		}
		coefficient /= coeff;
		return *this;
	}

	Data& operator +=(double coeff)
	{
		coefficient += coeff;
		return *this;
	}

	Data& operator -=(double coeff)
	{
		coefficient -= coeff;
		return *this;
	}

	friend ostream& operator <<(ostream& sstream, const Data& data)
	{
		sstream << fixed;
		sstream << setprecision(outputPrecision) << data.coefficient << data.name;
		return sstream;
	}

	friend istream& operator >>(istream& sstream, Data& data)
	{
		char* str{ getMemory<char>(maxStringLen) };
		sstream.getline(str, maxStringLen);
		data.setString(str);
		freeMemory(str);
		return sstream;
	}
};

bool compareData(const Data& first, const Data& second)
{
	char* firstStr{ first.getName() };
	char* secondStr{ second.getName() };
	int lenFirst{ strlen(firstStr) }, lenSecond{ strlen(secondStr) };
	if (lenFirst < lenSecond)
		return true;
	if (lenFirst == lenSecond)
		for (int i{ 0 }; i < lenFirst; ++i)
			if (firstStr[i] < secondStr[i])
				return true;
			else if (firstStr[i] > secondStr[i])
				return false;
	return false;
}

class LinearPolynomial
{
private:
	int cntData;
	Data* arrayData;

	void parseString(char* str)
	{
		int i{ 0 };
		int signPos{ 0 };
		if ((strlen(str) > 0) && ((str[0] == '+') || (str[0] == '-')))
			signPos = strcspn(str + 1, "+-") + 1;
		else
			signPos = strcspn(str, "+-");
		char* tmp{ getMemory<char>(maxStringLen) };
		while (signPos < strlen(str))
		{
			strncpy(tmp, str, signPos);
			tmp[signPos] = '\0';
			arrayData[i++].setString(tmp);
			str += signPos;
			signPos = strcspn(str + 1, "+-") + 1;
		}
		strncpy(tmp, str, signPos);
		tmp[signPos] = '\0';
		arrayData[i++].setString(tmp);
		freeMemory(tmp);
	}

	void quickSort(int begin, int end)
	{
		if (begin == end)
			return;
		int left{ begin }, right{ end }, middle{ (begin + end) / 2 };
		Data tmp;
		while (left <= right)
		{
			while (compareData(arrayData[left], arrayData[middle]))
				++left;
			while (compareData(arrayData[middle], arrayData[right]))
				--right;
			if (left <= right)
			{
				tmp = arrayData[left];
				arrayData[left] = arrayData[right];
				arrayData[right] = tmp;
				++left;
				--right;
			}
		}
		if (right > begin)
			quickSort(begin, right);
		if (left < end)
			quickSort(left, end);
	}

	void normalize()
	{
		quickSort(0, cntData - 1);
		int j{ 0 };
		for (int i{ 0 }; i < (cntData - 1); ++i)
		{
			j = i + 1;
			while ((j < cntData) && stringsEqual(arrayData[i].getName(), arrayData[j].getName()))
			{
				arrayData[i] += arrayData[j].getCoefficient();
				++j;
			}
			if (j != (i + 1))
			{
				if (fabs(arrayData[i].getCoefficient()) < EPS)
					--i;
				int tmp{ j };
				for (int k{ i + 1 }; j < cntData; ++j, ++k)
					arrayData[k] = arrayData[j];
				cntData -= tmp - i - 1;
			}
			else if (fabs(arrayData[i].getCoefficient()) < EPS)
			{
				for (; j < cntData; ++j)
					arrayData[j - 1] = arrayData[j];
				--i;
				--cntData;
			}
		}
		if (fabs(arrayData[cntData - 1].getCoefficient()) < EPS)
			--cntData;
	}
public:
	~LinearPolynomial()
	{
		freeMemory(arrayData);
		//cout<<"Destructor for LinearPolynomial\n";
	};

	LinearPolynomial() : cntData{ 0 }, arrayData{ nullptr }
	{
		//cout<<"Constructor №1 for LinearPolynomial\n";
	}

	LinearPolynomial(const LinearPolynomial& lp) : cntData{ lp.cntData }, arrayData{ nullptr }
	{
		if (lp.cntData)
			arrayData = getMemory<Data>(lp.cntData);
		for (int i{ 0 }; i < lp.cntData; ++i)
			arrayData[i] = lp.arrayData[i];
		//cout<<"Constructor №2 for LinearPolynomial\n";
	}

	LinearPolynomial(const char* str) : cntData{ 0 }, arrayData{ nullptr }
	{
		char* tmp{ getMemory<char>(strlen(str) + stringEnd) };
		strcpy(tmp, str);
		if (!checkString(tmp, cntData))
		{
			cerr << "Ошибка! Введен некорректный полином! Установлено значение по умолчанию\n\n";
			cntData = 0;
		}
		else
		{
			arrayData = getMemory<Data>(cntData);
			parseString(tmp);
			normalize();
		}
		freeMemory(tmp);
		//cout<<"Constructor №3 for LinearPolynomial\n";
	}

	LinearPolynomial(const Data* newArrayData, int newCntData) : cntData{ newCntData }, arrayData{ nullptr }
	{
		if (newCntData <= 0)
		{
			cerr << "Ошибка! Некорректное значение размера массива! Установлено значение по умолчанию\n\n";
			cntData = 0;
		}
		else
		{
			arrayData = getMemory<Data>(newCntData);
			for (int i{ 0 }; i < newCntData; ++i)
				arrayData[i] = newArrayData[i];
			normalize();
		}
		//cout<<"Constructor №4 for LinearPolynomial\n";
	}

	int getCnt() const
	{
		return cntData;
	}

	Data getData(int index) const
	{
		if ((index >= cntData) || (index < 0))
		{
			cerr << "Ошибка! Выход за границу массива! Возвращен объект по умолчанию\n\n";
			return Data{};
		}
		return arrayData[index];
	}

	void setArrayData(const Data* newArrayData, int newCntData)
	{
		if (newCntData <= 0)
			cerr << "Ошибка! Некорректное значение размера массива! Изменения не применены\n\n";
		else
		{
			cntData = newCntData;
			freeMemory(arrayData);
			arrayData = getMemory<Data>(newCntData);
			for (int i{ 0 }; i < newCntData; ++i)
				arrayData[i] = newArrayData[i];
			normalize();
		}
	}

	void setLinearPolynomial(const LinearPolynomial& newLP)
	{
		if (this == &newLP)
			return;
		freeMemory(arrayData);
		if (newLP.cntData)
			arrayData = getMemory<Data>(newLP.cntData);
		else
			arrayData = nullptr;
		cntData = newLP.cntData;
		for (int i{ 0 }; i < newLP.cntData; ++i)
			arrayData[i] = newLP.arrayData[i];
	}

	void setString(const char* str)
	{
		char* tmp{ getMemory<char>(strlen(str) + stringEnd) };
		strcpy(tmp, str);
		int newCntData{ 0 };
		if (!checkString(tmp, newCntData))
			cerr << "Ошибка! Введен некорректный полином! Изменения не применены\n\n";
		else
		{
			freeMemory(arrayData);
			cntData = newCntData;
			arrayData = getMemory<Data>(cntData);
			parseString(tmp);
			normalize();
		}
		freeMemory(tmp);
	}

	LinearPolynomial& operator =(const LinearPolynomial& newLP)
	{
		if (this == &newLP)
			return *this;
		freeMemory(arrayData);
		if (newLP.cntData)
			arrayData = getMemory<Data>(newLP.cntData);
		else
			arrayData = nullptr;
		cntData = newLP.cntData;
		for (int i{ 0 }; i < newLP.cntData; ++i)
			arrayData[i] = newLP.arrayData[i];
		return *this;
	}

	LinearPolynomial operator *(double coeff)
	{
	   if ( fabs(coeff) < EPS )
         return LinearPolynomial{};
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.arrayData[i] *= coeff;
		return tmp;
	}

	LinearPolynomial operator /(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cerr << "Ошибка! Деление на 0! Операция не выполена\n\n";
			return LinearPolynomial{ *this };
		}
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.arrayData[i] /= coeff;
		return tmp;
	}

	LinearPolynomial operator -()
	{
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.arrayData[i] = -tmp.arrayData[i];
		return tmp;
	}

	LinearPolynomial operator +(const LinearPolynomial& lp)
	{
		if (!lp.cntData)
			return LinearPolynomial{ *this };
		int newCnt{ cntData + lp.cntData };
		Data* tmpData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < cntData; ++i)
			tmpData[i] = arrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			tmpData[cntData + i] = lp.arrayData[i];
		LinearPolynomial tmp{ tmpData,newCnt };
		freeMemory(tmpData);
		return tmp;
	}

	LinearPolynomial operator -(const LinearPolynomial& lp)
	{
		if (!lp.cntData)
			return LinearPolynomial{ *this };
		int newCnt{ cntData + lp.cntData };
		Data* tmpData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < cntData; ++i)
			tmpData[i] = arrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			tmpData[cntData + i] = -lp.arrayData[i];
		LinearPolynomial tmp{ tmpData,newCnt };
		freeMemory(tmpData);
		return tmp;
	}

	LinearPolynomial& operator *=(double coeff)
	{
	   if (fabs(coeff) < EPS)
      {
         freeMemory(arrayData);
         cntData=0;
      }
      else
         for (int i{ 0 }; i < cntData; ++i)
            arrayData[i] *= coeff;
		return *this;
	}

	LinearPolynomial& operator /=(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cerr << "Ошибка! Деление на 0! Операция не выполена\n\n";
			return *this;
		}
		for (int i{ 0 }; i < cntData; ++i)
			arrayData[i] /= coeff;
		return *this;
	}

	LinearPolynomial& operator +=(const LinearPolynomial& lp)
	{
		if (!lp.cntData)
			return *this;
		int newCnt{ cntData + lp.cntData };
		Data* tmp{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < cntData; ++i)
			tmp[i] = arrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			tmp[cntData + i] = lp.arrayData[i];
		setArrayData(tmp, newCnt);
		freeMemory(tmp);
		return *this;
	}

	LinearPolynomial& operator -=(const LinearPolynomial& lp)
	{
		if (!lp.cntData)
			return *this;
		int newCnt{ cntData + lp.cntData };
		Data* tmp{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < cntData; ++i)
			tmp[i] = arrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			tmp[cntData + i] = -lp.arrayData[i];
		setArrayData(tmp, newCnt);
		freeMemory(tmp);
		return *this;
	}

	friend ostream& operator <<(ostream& sstream, const LinearPolynomial& lp)
	{
		for (int i{ 0 }; i < lp.cntData; ++i)
		{
			if (i && lp.arrayData[i].getCoefficient() > EPS)
				sstream << "+";
			sstream << lp.arrayData[i];
		}
		return sstream;
	}

	friend istream& operator >>(istream& sstream, LinearPolynomial& lp)
	{
		char* str{ getMemory<char>(maxStringLen) };
		sstream.getline(str, maxStringLen);
		lp.setString(str);
		freeMemory(str);
		return sstream;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Ввод полинома как будто вы его пишите на бумаге. Нвпример: -a+c-d-2.4d+8\n";
	cout << "Сначала вводим коэффициент, затем название неизвестной\n";
	cout << "Ограничения на название неизвестной такие же, как на название перемнной C++\n";
	cout << "Пробелы игнорируются\n\n";
	LinearPolynomial lp1;
	cin >> lp1;
	cout << lp1 << endl;
	LinearPolynomial lp2{ lp1 };
	cout << lp2 << endl;
	lp1 += lp2;
	cout << lp1 << endl;
	LinearPolynomial* arrayLP{ getMemory<LinearPolynomial>(3) };
	LinearPolynomial* ptr1{ &lp2 };
	cout << *ptr1 << endl;
	LinearPolynomial* ptr2 = new (nothrow) LinearPolynomial;
	if (!ptr2)
	{
		cerr << "Ошибка выделения памяти!\n";
		system("pause");
		exit(ERROR_NO_MEMORY);
	}
	cout << *ptr2 << endl;
	for (int i{ 0 }; i < 3; ++i)
	{
		*(arrayLP + i) = lp1 * i;
		cout << *(arrayLP + i) << endl;
	}
	*ptr2 -= arrayLP[1];
	cout << *ptr2 << endl;
	ptr1 = ptr2;
	*ptr1 = -*ptr1;
	cout << *ptr1 << endl;
	delete ptr2;
	freeMemory(arrayLP);
	system("pause");
	return 0;
}