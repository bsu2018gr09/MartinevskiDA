#include <iostream>
#include <clocale>

using namespace std;

template <class T>
T* getMemory()
{
	T* item = new (nothrow) T();
	if (!item)
	{
		cout << "Ощибка выделения памяти!\n";
		system("pause");
		exit(0);
	}
	return item;
}

template <class T>
class Node
{
protected:
	T data;
	Node<T>* nextNode;
public:
	Node()
	{
		data = NULL;
		nextNode = nullptr;
	}

	Node(T newData, Node<T>* newNextNode)
	{
		data = newData;
		nextNode = newNextNode;
	}

	T getData()
	{
		return data;
	}

	Node<T>* getNextNode()
	{
		return nextNode;
	}

	void setData(T newData)
	{
		data = newData;
	}

	void setNextNode(Node<T>* newNextNode)
	{
		nextNode = newNextNode;
	}

	void setDataAndNextNode(T newData, Node<T>* newNextNode)
	{
		data = newData;
		nextNode = newNextNode;
	}
};

template <class T>
class Queue
{
public:
	int cntElements;
	Node<T>* first;
	Node<T>* last;
public:
	Queue()
	{
		cntElements = 0;
		first = nullptr;
		last = nullptr;
	}

	int getSize()
	{
		return cntElements;
	}

	bool isEmpty()
	{
		return (!cntElements);
	}

	T getFirst()
	{
		if (!cntElements)
		{
			cout << "Нет элементов в очереди!\n";
			return NULL;
		}
		return first->getData();
	}

	T getLast()
	{
		if (!cntElements)
		{
			cout << "Нет элементов в очереди!\n";
			return NULL;
		}
		return last->getData();
	}

	void push(T data)
	{
		Node<T>* tmpNode = getMemory<Node<T>>();
		tmpNode->setData(data);
		if (!cntElements)
		{
			first = tmpNode;
			last = tmpNode;
		}
		else
		{
			last->setNextNode(tmpNode);
			last = tmpNode;
		}
		tmpNode = nullptr;
		++cntElements;
	}

	void pop()
	{
		if (!cntElements)
		{
			cout << "Нет элементов в очереди!\n";
			return;
		}
		Node<T>* tmpNode = first->getNextNode();
		delete first;
		first = tmpNode;
		tmpNode = nullptr;
		if (cntElements == 1)
			last = nullptr;
		--cntElements;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Queue<int> myQueue;
	system("pause");
	return 0;
}