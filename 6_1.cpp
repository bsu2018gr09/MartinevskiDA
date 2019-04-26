/**
Класс линейных уравнений с использованием динамической памяти(выбор количества неизвестных)
*/

#include <iostream>
#include <clocale>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_STRING_LEN{ 255 };
const int PRECISION_FOR_OUTPUT{ 3 };
const double EPS{ 1e-9 };

const int ERROR_NO_MEMORY{ 0 };
const int ERROR_WRONG_NAME{ 1 };
const int ERROR_DIVISION_BY_ZERO{ 2 };
const int ERROR_WRONG_STRING_MONOM{ 3 };
const int ERROR_ARRAY_OVERRUN{ 4 };
const int ERROR_WRONG_CNT{ 5 };
const int ERROR_WRONG_STRING_POLYNOMIAL{ 6 };
const int SYMBOL_OF_STRING_END{ 1 };
char* GoodSymbolsForString = " +-._abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char* GoodSymbolsForName = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char* Letters = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* Numbers = "0123456789";

template <class T>
T* getMemory(int n)
{
	T *Array = new (nothrow) T[n];
	if (!Array)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(ERROR_NO_MEMORY);
	}
	return Array;
}

template <class T>
void freeMemory(T*& Array)
{
	delete[] Array;
	Array = nullptr;
}

bool checkStringForData(char* String)
{
	char* BeginOfString{ String };
	while (strcspn(String, " ") < strlen(String))
	{
		strcpy(String, String + strspn(String, " "));
		String += strcspn(String, " ");
	}
	String = BeginOfString;
	if ((strlen(String) > 0) && ((String[0] == '+') || (String[0] == '-')))
		++String;
	int posOfPoint{ strcspn(String,".") };
	if ((posOfPoint == strlen(String)) && ((!strlen(String)) || (strspn(String, GoodSymbolsForName) < strlen(String))))
		return false;
	else
	{
		char* AfterFirsPoint{ String + posOfPoint + 1 };
		if ((posOfPoint < strlen(String)) && ((!posOfPoint) || (!strlen(AfterFirsPoint)) || (strspn(String, GoodSymbolsForName) < posOfPoint) || (strspn(AfterFirsPoint, GoodSymbolsForName) < strlen(AfterFirsPoint))
			|| (strcspn(String, Letters) < posOfPoint) || (!strcspn(AfterFirsPoint, Letters))))
			return false;
	}
	return true;
}

class Data
{
private:
	char* Name;
	double coefficient;

	void getDataFromString(char* String)
	{
		bool flag{ 0 };
		if ((String[0] == '+') || (String[0] == '-'))
		{
			if (String[0] == '-')
				flag = 1;
			++String;
		}
		int posOfPoint{ strcspn(String,".") };
		if (posOfPoint == strlen(String))
		{
			char* BeginOfLetters{ String + strspn(String,Numbers) };
			Name = getMemory<char>(strlen(BeginOfLetters) + SYMBOL_OF_STRING_END);
			strcpy(Name, BeginOfLetters);
			strcpy(BeginOfLetters, "\0");
			if (!strlen(String))
				coefficient = 1;
			else
				coefficient = atof(String);
		}
		else
		{
			char* BeginOfLetters{ String + posOfPoint + 1 + strspn(String + posOfPoint + 1,Numbers) };
			Name = getMemory<char>(strlen(BeginOfLetters) + SYMBOL_OF_STRING_END);
			strcpy(Name, BeginOfLetters);
			strcpy(BeginOfLetters, "\0");
			String[posOfPoint] = ',';
			coefficient = atof(String);
		}
		if (flag)
			coefficient *= -1;
	}

	bool checkDataName(char* Name)
	{
		if ((strlen(Name)) && ((strspn(Name, GoodSymbolsForName) < strlen(Name)) || (!strcspn(Name, Numbers))))
			return false;
		return true;
	}
public:
	~Data()
	{
		freeMemory(Name);
		//cout<<"Destructor for Data\n";
	}

	Data() : Name{ getMemory<char>(1) }, coefficient{ 0 }
	{
		//cout<<"Constructor №1 for Data\n";
	};

	Data(char* newName, double newCoefficient) : Name{ getMemory<char>(strlen(newName) + SYMBOL_OF_STRING_END) }, coefficient{ newCoefficient }
	{
		if (!checkDataName(newName))
		{
			cout << "Ошибка! Некорректное название неизвестной!\n\n";
			system("pause");
			exit(ERROR_WRONG_NAME);
		}
		strcpy(Name, newName);
		//cout<<"Constructor №2 for Data\n";
	}

	Data(const Data& newData) : Name{ getMemory<char>(strlen(newData.Name) + SYMBOL_OF_STRING_END) }, coefficient{ newData.coefficient }
	{
		strcpy(Name, newData.Name);
		//cout<<"Constructor №3 for Data\n";
	}

	Data(char* String)
	{
		char* TMPString{ getMemory<char>(strlen(String) + SYMBOL_OF_STRING_END) };
		strcpy(TMPString, String);
		if (!checkStringForData(TMPString))
		{
			cout << "Ошибка! Введен некорректный моном!\n\n";
			system("pause");
			exit(ERROR_WRONG_STRING_MONOM);
		}
		this->getDataFromString(TMPString);
		freeMemory(TMPString);
		//cout<<"Constructor №4 for Data\n";
	}

	void setString(char* String)
	{
		char* TMPString{ getMemory<char>(strlen(String) + SYMBOL_OF_STRING_END) };
		strcpy(TMPString, String);
		if (!checkStringForData(TMPString))
		{
			cout << "Ошибка! Введен некорректный моном!\n\n";
			system("pause");
			exit(ERROR_WRONG_STRING_MONOM);
		}
		freeMemory(Name);
		this->getDataFromString(TMPString);
		freeMemory(TMPString);
	}

	void setName(char* newName)
	{
		if (!checkDataName(newName))
		{
			cout << "Ошибка! Некорректное название неизвестной!\n\n";
			system("pause");
			exit(ERROR_WRONG_NAME);
		}
		freeMemory(Name);
		Name = getMemory<char>(strlen(newName) + SYMBOL_OF_STRING_END);
		strcpy(Name, newName);
	}

	void setCoefficient(double newCoefficient)
	{
		coefficient = newCoefficient;
	}

	void setNameAndCoefficient(char* newName, double newCoefficient)
	{
		if (!checkDataName(newName))
		{
			cout << "Ошибка! Некорректное название неизвестной!\n\n";
			system("pause");
			exit(ERROR_WRONG_NAME);
		}
		freeMemory(Name);
		Name = getMemory<char>(strlen(newName) + SYMBOL_OF_STRING_END);
		strcpy(Name, newName);
		coefficient = newCoefficient;
	}

	void setData(Data& newData)
	{
		if (this == &newData)
			return;
		freeMemory(Name);
		Name = getMemory<char>(strlen(newData.Name) + SYMBOL_OF_STRING_END);
		strcpy(Name, newData.Name);
		coefficient = newData.coefficient;
	}

	double getCoefficient()
	{
		return coefficient;
	}

	char* getName()
	{
		return Name;
	}

	Data& operator =(const Data& newData)
	{
		if (this == &newData)
			return *this;
		this->coefficient = newData.coefficient;
		freeMemory(this->Name);
		Name = getMemory<char>(strlen(newData.Name));
		strcpy(this->Name, newData.Name);
		return *this;
	}

	Data operator *(double coeff)
	{
		return Data(Name, coefficient*coeff);
	}

	Data operator /(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cout << "Ошибка! Деление на 0!\n\n";
			system("pause");
			exit(ERROR_DIVISION_BY_ZERO);
		}
		return Data(Name, coefficient / coeff);
	}

	Data operator +(double coeff)
	{
		return Data(Name, coefficient + coeff);
	}

	Data operator -(double coeff)
	{
		return Data(Name, coefficient - coeff);
	}

	Data operator -()
	{
		return Data(Name, -coefficient);
	}

	Data operator ++(int)
	{
		++(*this);
		return Data(Name, coefficient - 1);
	}

	Data operator --(int)
	{
		--(*this);
		return Data(Name, coefficient + 1);
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
			cout << "Ошибка! Деление на 0!\n\n";
			system("pause");
			exit(ERROR_DIVISION_BY_ZERO);
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

	friend ostream& operator <<(ostream& sstream, Data data)
	{
		cout << fixed;
		sstream << setprecision(PRECISION_FOR_OUTPUT) << data.coefficient << data.Name;
		return sstream;
	}

	friend istream& operator >>(istream& sstream, Data& data)
	{
		char* String{ getMemory<char>(MAX_STRING_LEN) };
		sstream.getline(String, MAX_STRING_LEN);
		data.setString(String);
		freeMemory(String);
		return sstream;
	}
};

class LinearPolynomial
{
private:
	int cntData;
	Data* ArrayData;

	void getLinearPolynomialFromString(char* String)
	{
		int i{ 0 };
		int posOfSign{ 0 };
		if ((strlen(String) > 0) && ((String[0] == '+') || (String[0] == '-')))
			posOfSign = strcspn(String + 1, "+-") + 1;
		else
			posOfSign = strcspn(String, "+-");
		char* TMPString{ getMemory<char>(MAX_STRING_LEN) };
		while (posOfSign < strlen(String))
		{
			strncpy(TMPString, String, posOfSign);
			TMPString[posOfSign] = '\0';
			ArrayData[i++].setString(TMPString);
			String += posOfSign;
			posOfSign = strcspn(String + 1, "+-") + 1;
		}
		strncpy(TMPString, String, posOfSign);
		TMPString[posOfSign] = '\0';
		ArrayData[i++].setString(TMPString);
		freeMemory(TMPString);
	}

	bool checkString(char* String)
	{
		if ((!strlen(String)) || (strspn(String, GoodSymbolsForString) < strlen(String)))
			return false;
		char* BeginOfString{ String };
		while (strcspn(String, " ") < strlen(String))
		{
			strcpy(String, String + strspn(String, " "));
			String += strcspn(String, " ");
		}
		String = BeginOfString;
		if ((strlen(String) > 0) && ((String[0] == '+') || (String[0] == '-')))
			++String;
		int posOfSign{ strcspn(String,"+-") };
		char* TMPString{ getMemory<char>(MAX_STRING_LEN) };
		while (posOfSign < strlen(String))
		{
			strncpy(TMPString, String, posOfSign);
			TMPString[posOfSign] = '\0';
			if (!checkStringForData(TMPString))
			{
				freeMemory(TMPString);
				return false;
			}
			++cntData;
			String += posOfSign;
			posOfSign = strcspn(String + 1, "+-") + 1;
		}
		strncpy(TMPString, String, posOfSign);
		TMPString[posOfSign] = '\0';
		if (!checkStringForData(TMPString))
		{
			freeMemory(TMPString);
			return false;
		}
		++cntData;
		freeMemory(TMPString);
		return true;
	}

	bool AnalyzeData(Data _first, Data _second)
	{
		char* firstStr{ _first.getName() };
		char* secondStr{ _second.getName() };
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

	bool stringsEqual(char* String1, char* String2)
	{
		if (strlen(String1) != strlen(String2))
			return false;
		int len{ strlen(String1) };
		for (int i{ 0 }; i < len; ++i)
			if (String1[i] != String2[i])
				return false;
		return true;
	}

	void QuickSort(int bbegin, int eend)
	{
		if (bbegin == eend)
			return;
		int _left{ bbegin }, _right{ eend }, middle{ (bbegin + eend) / 2 };
		Data tmp;
		while (_left <= _right)
		{
			while (AnalyzeData(this->ArrayData[_left], this->ArrayData[middle]))
				++_left;
			while (AnalyzeData(this->ArrayData[middle], this->ArrayData[_right]))
				--_right;
			if (_left <= _right)
			{
				tmp = this->ArrayData[_left];
				this->ArrayData[_left] = this->ArrayData[_right];
				this->ArrayData[_right] = tmp;
				++_left;
				--_right;
			}
		}
		if (_right > bbegin)
			this->QuickSort(bbegin, _right);
		if (_left < eend)
			this->QuickSort(_left, eend);
	}

	void normalize()
	{
		this->QuickSort(0, this->cntData - 1);
		int j{ 0 };
		for (int i{ 0 }; i < (this->cntData - 1); ++i)
		{
			j = i + 1;
			while ((j < this->cntData) && stringsEqual(this->ArrayData[i].getName(), this->ArrayData[j].getName()))
			{
				this->ArrayData[i] += this->ArrayData[j].getCoefficient();
				++j;
			}
			if (j != (i + 1))
			{
				if (fabs(ArrayData[i].getCoefficient()) < EPS)
					--i;
				int tmp{ j };
				for (int k{ i + 1 }; j < cntData; ++j, ++k)
					this->ArrayData[k] = this->ArrayData[j];
				this->cntData -= tmp - i - 1;
			}
			else if (fabs(this->ArrayData[i].getCoefficient()) < EPS)
			{
				for (; j < this->cntData; ++j)
					this->ArrayData[j - 1] = this->ArrayData[j];
				--i;
				--this->cntData;
			}
		}
		if (fabs(this->ArrayData[this->cntData - 1].getCoefficient()) < EPS)
			--this->cntData;
	}
public:
	~LinearPolynomial()
	{
		freeMemory(ArrayData);
		//cout<<"Destructor for LinearPolynomial\n";
	};

	LinearPolynomial() : cntData{ 0 }, ArrayData{ nullptr }
	{
		//cout<<"Constructor №1 for LinearPolynomial\n";
	}

	LinearPolynomial(const LinearPolynomial& lp) : cntData{ lp.cntData }, ArrayData{ getMemory<Data>(lp.cntData) }
	{
		for (int i{ 0 }; i < lp.cntData; ++i)
			ArrayData[i] = lp.ArrayData[i];
		//cout<<"Constructor №2 for LinearPolynomial\n";
	}

	LinearPolynomial(char* String) : cntData{ 0 }
	{
		char* TMPString{ getMemory<char>(strlen(String) + SYMBOL_OF_STRING_END) };
		strcpy(TMPString, String);
		if (!(this->checkString(TMPString)))
		{
			cout << "Ошибка! Введен некорректный полином!\n\n";
			system("pause");
			exit(ERROR_WRONG_STRING_POLYNOMIAL);
		}
		ArrayData = getMemory<Data>(cntData);
		this->getLinearPolynomialFromString(TMPString);
		this->normalize();
		freeMemory(TMPString);
		//cout<<"Constructor №3 for LinearPolynomial\n";
	}

	LinearPolynomial(Data* newArrayData, int newCntData) : cntData{ newCntData }, ArrayData{ getMemory<Data>(newCntData) }
	{
		if (newCntData < 0)
		{
			cout << "Ошибка! Некорректное значение размера массива!\n\n";
			system("pause");
			exit(ERROR_WRONG_CNT);
		}
		for (int i{ 0 }; i < newCntData; ++i)
			ArrayData[i] = newArrayData[i];
		this->normalize();
		//cout<<"Constructor №4 for LinearPolynomial\n";
	}

	int getCntData()
	{
		return cntData;
	}

	Data* getArrayData()
	{
		return ArrayData;
	}

	Data getData(int index)
	{
		if ((index >= cntData) || (index < 0))
		{
			cout << "Ошибка! Выход за границу массива!\n\n";
			system("pause");
			exit(ERROR_ARRAY_OVERRUN);
		}
		return ArrayData[index];
	}

	void setArrayDataAndCnt(Data* newArrayData, int newCntData)
	{
		if (newCntData < 0)
		{
			cout << "Ошибка! Некорректное значение размера массива!\n\n";
			system("pause");
			exit(ERROR_WRONG_CNT);
		}
		cntData = newCntData;
		freeMemory(ArrayData);
		ArrayData = getMemory<Data>(newCntData);
		for (int i{ 0 }; i < newCntData; ++i)
			ArrayData[i] = newArrayData[i];
		this->normalize();
	}

	void setLinearPolynomial(LinearPolynomial& newLP)
	{
		if (this == &newLP)
			return;
		freeMemory(ArrayData);
		ArrayData = getMemory<Data>(newLP.cntData);
		cntData = newLP.cntData;
		for (int i{ 0 }; i < newLP.cntData; ++i)
			ArrayData[i] = newLP.ArrayData[i];
	}

	void setString(char* String)
	{
		char* TMPString{ getMemory<char>(strlen(String) + SYMBOL_OF_STRING_END) };
		strcpy(TMPString, String);
		cntData = 0;
		freeMemory(ArrayData);
		if (!(this->checkString(TMPString)))
		{
			cout << "Ошибка! Введен некорректный полином!\n\n";
			system("pause");
			exit(ERROR_WRONG_STRING_POLYNOMIAL);
		}
		ArrayData = getMemory<Data>(cntData);
		this->getLinearPolynomialFromString(TMPString);
		this->normalize();
		freeMemory(TMPString);
	}

	LinearPolynomial& operator =(const LinearPolynomial& newLP)
	{
		if (this == &newLP)
			return *this;
		freeMemory(this->ArrayData);
		this->ArrayData = getMemory<Data>(newLP.cntData);
		cntData = newLP.cntData;
		for (int i{ 0 }; i < newLP.cntData; ++i)
			this->ArrayData[i] = newLP.ArrayData[i];
		return *this;
	}

	LinearPolynomial operator ++(int)
	{
		LinearPolynomial tmp{ *this };
		++(*this);
		return tmp;
	}

	LinearPolynomial operator --(int)
	{
		LinearPolynomial tmp{ *this };
		--(*this);
		return tmp;
	}

	LinearPolynomial& operator ++()
	{
		for (int i{ 0 }; i < cntData; ++i)
			++ArrayData[i];
		return *this;
	}

	LinearPolynomial& operator --()
	{
		for (int i{ 0 }; i < cntData; ++i)
			--ArrayData[i];
		return *this;
	}

	LinearPolynomial operator *(double coeff)
	{
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.ArrayData[i] *= coeff;
		return tmp;
	}

	LinearPolynomial operator /(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cout << "Ошибка! Деление на 0!\n\n";
			system("pause");
			exit(ERROR_DIVISION_BY_ZERO);
		}
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.ArrayData[i] /= coeff;
		return tmp;
	}

	LinearPolynomial operator +(double coeff)
	{
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.ArrayData[i] += coeff;
		return tmp;
	}

	LinearPolynomial operator -(double coeff)
	{
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.ArrayData[i] -= coeff;
		return tmp;
	}

	LinearPolynomial operator -()
	{
		LinearPolynomial tmp{ *this };
		for (int i{ 0 }; i < cntData; ++i)
			tmp.ArrayData[i] = -tmp.ArrayData[i];
		return tmp;
	}

	LinearPolynomial operator +(LinearPolynomial lp)
	{
		int newCnt{ this->cntData + lp.cntData };
		Data* TMPData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < this->cntData; ++i)
			TMPData[i] = this->ArrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			TMPData[this->cntData + i] = lp.ArrayData[i];
		LinearPolynomial tmp{ TMPData,newCnt };
		freeMemory(TMPData);
		return tmp;
	}

	LinearPolynomial operator -(LinearPolynomial lp)
	{
		int newCnt{ this->cntData + lp.cntData };
		Data* TMPData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < this->cntData; ++i)
			TMPData[i] = this->ArrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			TMPData[this->cntData + i] = -lp.ArrayData[i];
		LinearPolynomial tmp{ TMPData,newCnt };
		freeMemory(TMPData);
		return tmp;
	}

	LinearPolynomial& operator *=(double coeff)
	{
		for (int i{ 0 }; i < this->cntData; ++i)
			this->ArrayData[i] *= coeff;
		return *this;
	}

	LinearPolynomial& operator /=(double coeff)
	{
		if (fabs(coeff) < EPS)
		{
			cout << "Ошибка! Деление на 0!\n\n";
			system("pause");
			exit(ERROR_DIVISION_BY_ZERO);
		}
		for (int i{ 0 }; i < this->cntData; ++i)
			this->ArrayData[i] /= coeff;
		return *this;
	}

	LinearPolynomial& operator +=(double coeff)
	{
		for (int i{ 0 }; i < this->cntData; ++i)
			this->ArrayData[i] += coeff;
		return *this;
	}

	LinearPolynomial& operator -=(double coeff)
	{
		for (int i{ 0 }; i < this->cntData; ++i)
			this->ArrayData[i] -= coeff;
		return *this;
	}

	LinearPolynomial& operator +=(LinearPolynomial lp)
	{
		int newCnt{ this->cntData + lp.cntData };
		Data* TMPData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < this->cntData; ++i)
			TMPData[i] = this->ArrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			TMPData[this->cntData + i] = lp.ArrayData[i];
		this->setArrayDataAndCnt(TMPData, newCnt);
		freeMemory(TMPData);
		return *this;
	}

	LinearPolynomial& operator -=(LinearPolynomial lp)
	{
		int newCnt{ this->cntData + lp.cntData };
		Data* TMPData{ getMemory<Data>(newCnt) };
		for (int i{ 0 }; i < this->cntData; ++i)
			TMPData[i] = this->ArrayData[i];
		for (int i{ 0 }; i < lp.cntData; ++i)
			TMPData[this->cntData + i] = -lp.ArrayData[i];
		this->setArrayDataAndCnt(TMPData, newCnt);
		freeMemory(TMPData);
		return *this;
	}

	friend ostream& operator <<(ostream& sstream, LinearPolynomial lp)
	{
		for (int i{ 0 }; i < lp.cntData; ++i)
		{
			if (i && lp.ArrayData[i].getCoefficient() > EPS)
				sstream << "+";
			sstream << lp.ArrayData[i];
		}
		return sstream;
	}

	friend istream& operator >>(istream& sstream, LinearPolynomial& lp)
	{
		char* String{ getMemory<char>(MAX_STRING_LEN) };
		sstream.getline(String, MAX_STRING_LEN);
		lp.setString(String);
		freeMemory(String);
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
	LinearPolynomial* ArrayLP{ getMemory<LinearPolynomial>(3) };
	LinearPolynomial* ptr1{ &lp2 };
	cout << *ptr1 << endl;
	LinearPolynomial* ptr2 = new (nothrow) LinearPolynomial;
	if (!ptr2)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(ERROR_NO_MEMORY);
	}
	cout << *ptr2 << endl;
	for (int i{ 0 }; i < 3; ++i)
	{
		*(ArrayLP + i) = lp1 + i;
		cout << *(ArrayLP + i) << endl;
	}
	*ptr2 -= *ArrayLP;
	cout << *ptr2 << endl;
	ptr1 = ptr2;
	*ptr1 = -*ptr1;
	cout << *ptr1 << endl;
	delete ptr2;
	freeMemory(ArrayLP);
	system("pause");
	return 0;
}