#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct node
{
	char data;
	int freq = 0;
	node* left;
	node* right;

	node() : data('0'), freq(0), left(NULL), right(NULL) {}
	node(char d, int f) : data(d), freq(f), left(NULL), right(NULL) {}
};

class Queue
{
	node* queueArray;
	int queueSize;
	int front;
	int rear;
	int numItems;

public:

	Queue()
	{
		queueArray = NULL;
		queueSize = 0;
		front = -1;
		rear = -1;
		numItems = 0;
	}

	Queue(int size)
	{
		queueArray = new node[size];
		queueSize = size;
		front = -1;
		rear = -1;
		numItems = 0;
	}

	void resize() {		// doubles the queue size

		node* temp = new node[queueSize];

		for (int i = 0; i < queueSize; i++)
			temp[i] = queueArray[i];

		delete[] queueArray;

		queueSize *= 2;
		queueArray = new node[queueSize];

		for (int i = 0; i < numItems; i++)
			queueArray[i] = temp[i];

		delete[] temp;
	}

	void initializeQueue(int size)
	{
		if (queueArray != NULL)
			delete[]queueArray;

		queueArray = new node[size];
		queueSize = size;
		front = -1;
		rear = -1;
		numItems = 0;
	}

	~Queue()
	{
		delete[]queueArray;
	}

	bool isFull()
	{
		if (numItems < queueSize)
			return false;
		return true;
	}

	int returnIndex(char c)
	{
		for (int i = 0; i < numItems; i++)
		{
			if (queueArray[i].data == c)
				return i;
		}

		return -1;
	}

	bool incFreq(int index)
	{
		if (queueArray != NULL and index >= 0 and index < numItems)
		{
			queueArray[index].freq++;
			return true;
		}

		return false;
	}

	void sort()
	{
		if (isEmpty())
			return;

		int i, j;
		for (i = front + 1; i < front + numItems; i++)
		{
			node temp = queueArray[i];
			for (j = i; j > 0 && temp.freq < queueArray[j - 1].freq; j--)
			{
				queueArray[j] = queueArray[j - 1];
			}
			queueArray[j] = temp;
		}
	}

	void enqueue(node dataItem)
	{
		if (front == -1)
			front = 0;

		rear = rear + 1;
		numItems++;
		queueArray[rear] = dataItem;

		if (numItems == queueSize)
			this->resize();

		sort();
	}

	node dequeue()
	{
		node temp;

		if (this->isEmpty())
		{
			cout << "Queue is empty.\n";
			return temp;
		}

		else
		{
			temp = queueArray[front];
			front++;
			numItems--;

			return temp;
		}
	}

	bool isEmpty() const
	{
		if (numItems == 0)
			return true;
		return false;
	}

	void display()
	{
		cout << " --------------------- " << endl;
		cout << " Character |    Freq " << endl;
		cout << " --------------------- " << endl;
		for (int i = front; i < front + numItems; i++)
		{
			cout << "|     " << queueArray[i].data << "    |     " << queueArray[i].freq << "    | " << endl;
			cout << " --------------------- " << endl;
		}
	}

	int numOfItems()
	{
		return numItems;
	}
};
