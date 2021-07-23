#pragma once

#include "Queue.h"
#include "Vector.h"
#include "Tree.h"

char* charArray = NULL;			// to hold unique symbols
string* stringArray = NULL;		// to hold bit string of each symbol
string* sevenBitArray = NULL;	// to hold seven bit strings
string fileText;				// will hold contents of entire file
int uniqueChar = 0;
int noOf7bitString = 0;			// total number of 7 bit indexes
int encodedBits = 0;			// # of bits in encoding
string decoded;					// contents of reconstructed.txt
string display;					// contents of reconstructed.txt

Queue freqQueue;
Vector<char> vector(200);
Tree tree;

void readFile()		//Reads the file and seperates unique characters
{
	string filename = "temp.txt";

	// First file-reading to extract unique characters //

	fstream in(filename, ios::in);
	if (in)
	{
		char c;

		while (!in.eof())
		{
			c = in.get();

			if (!vector.search(c))
				vector.push_back(c);
		}

		uniqueChar = vector.size() - 1;
		in.close();
	}

	// Initializing the bit arrays and queue with number of unique characters //

	charArray = new char[uniqueChar];
	stringArray = new string[uniqueChar];
	freqQueue.initializeQueue(uniqueChar);

	// Copying unique symbols from vector to the ordered queue and the char array //

	for (int i = 0; i < uniqueChar; i++)
	{
		char c = vector[i];

		node temp(c, 0);
		freqQueue.enqueue(temp);
		charArray[i] = vector[i];
	}

	// Second file-reading to find frequency of each unique symbol //

	in.open(filename, ios::in);
	if (in)
	{
		while (!in.eof())
		{
			char c;

			while (!in.eof())
			{
				c = in.get();

				int index = freqQueue.returnIndex(c);
				freqQueue.incFreq(index);

				fileText += c; // adding each character to the string
			}
		}

		freqQueue.sort();
	}
}

void constructTree()
{
	node* tempRoot = new node;
	node left;
	node right;

	while (freqQueue.numOfItems() > 1) {

		// extracting first two nodes from the queue and copying their values to the temporary root //

		tempRoot->data = '*';
		left = freqQueue.dequeue();
		right = freqQueue.dequeue();

		tempRoot->left = new node;
		tempRoot->right = new node;
		tempRoot->left->data = left.data;
		tempRoot->left->freq = left.freq;
		tempRoot->right->data = right.data;
		tempRoot->right->freq = right.freq;

		// copying the children (if any) of the dequeued nodes //

		if (left.left != NULL)
			tempRoot->left->left = left.left;

		if (left.right != NULL)
			tempRoot->left->right = left.right;

		if (right.left != NULL)
			tempRoot->right->left = right.left;

		if (right.right != NULL)
			tempRoot->right->right = right.right;

		tempRoot->freq = left.freq + right.freq;

		// enqueueing the new tree //

		freqQueue.enqueue(*tempRoot);

		freqQueue.sort();
		//freqQueue.display();
		//cout << "Insertion Completed" << endl << endl;
	}

	// dequeuing the last node (a fully formed tree) and copying it to the main symbol tree //

	node finalNode = freqQueue.dequeue();
	tree.copyTree(&finalNode);
}


void Encode()
{
	tree.encode(uniqueChar, charArray, stringArray);
}


void displayEncoded()
{
	ifstream in("encoded.txt", ios::binary);
	string read;
	if (in)
	{
		read = in.get();
		while (!in.eof()) {
			read += in.get();
		}

		in.close();

		read[read.size() - 1] = '\0';

		cout << read << endl;
	}
}



void formBitStrings()
{
	int totalBits;
	string allBits;

	// Finding all bits of the original string //

	for (int i = 0; i < fileText.size() - 1; i++) {
		char symbol = fileText[i];

		int index = 0;

		for (int j = 0; j < uniqueChar; j++) {
			if (charArray[j] == symbol) {
				index = j;
				break;
			}
		}

		allBits += stringArray[index];
	}

	//cout << allBits << endl;
	//cout << allBits.size();

	// allocating memory for the string array which holds 7-bit strings //

	totalBits = allBits.size();
	encodedBits = totalBits;

	if (totalBits % 7 == 0)
		noOf7bitString = totalBits / 7;
	else
		noOf7bitString = (totalBits / 7) + 1;

	sevenBitArray = new string[noOf7bitString];

	// Copying bits to string array, 7 bits at each index //

	int start = 0;
	for (int i = 0; i < noOf7bitString; i++) {
		sevenBitArray[i] = allBits.substr(start, 7);
		start += 7;
	}

	// completing last string with zeroes //

	int sizeOfLastIndex = sevenBitArray[noOf7bitString - 1].size();

	if (sizeOfLastIndex < 7) {
		while (sizeOfLastIndex < 7) {
			sevenBitArray[noOf7bitString - 1] += '0';
			sizeOfLastIndex++;

		}
	}

	
}

void displaysevenBit()
{
	cout << " ------------------------------- " << endl;
	cout << "|  Index Number\t|  7-bit Binary\t|" << endl;
	cout << " ------------------------------- " << endl;

	for (int i = 0; i < noOf7bitString; i++)
	{
		cout << "|\t" << i << "\t|   " << sevenBitArray[i] << "\t|" << endl;
		cout << " ------------------------------- " << endl;
	}
}

int binaryToDecimal(string& bin)
{
	int decimal = 0;
	for (int i = 0; i < bin.size(); i++)
	{
		decimal = (decimal * 2) + bin[i] - '0';
	}

	return decimal;
}

void writingASCII()
{
	ofstream out("encoded.txt");

	for (int i = 0; i < noOf7bitString; i++) 
	{
		string sevenBits = sevenBitArray[i];
		char ch = binaryToDecimal(sevenBits);
		
		if (out)
			out << ch;
	}

	if (out)
		out.close();


}

void displayASCII()
{
	cout << " ----------------------- " << endl;
	cout << "| Index Num |   ASCII   |" << endl;
	cout << " ----------------------- " << endl;
	for (int i = 0; i < noOf7bitString; i++)
	{
		string sevenBits = sevenBitArray[i];
		char ch = binaryToDecimal(sevenBits);
		cout << "|\t" << i << "   |   " << binaryToDecimal(sevenBits) << " / " << ch << "  |" << endl;
		cout << " ----------------------- " << endl;
	}
}

string decimalToBinary(int dec)
{
	string temp, binary;

	while (dec)
	{
		temp += ('0' + (dec % 2));
		dec /= 2;
	}
	binary.append(7 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		binary += temp[i];
	}
	return binary;

}

void decode()
{
	node* current = new node;
	current = tree.root;
	ifstream in("encoded.txt", ios::binary);
	string read;
	string converted = "";
	string tamp = "";
	if (in)
	{
		read = in.get();
		while (!in.eof()) {
			read += in.get();
		}

		in.close();

		read[read.size() - 1] = '\0';

		ofstream out("reconstructed.txt");
		if (out)
		{
			for (int i = 0; i < read.size() - 1; i++)
			{
				converted += decimalToBinary(read[i]);
			}

			for (int j = 0; j < converted.size(); j++)
			{
				if (tree.root == NULL)
					return;

				if (current->left == NULL and current->right == NULL)
				{
					tamp += current->data;
					current = tree.root;
				}

				if (converted[j] == '0')
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}



			}
			//cout << tamp;
			out << tamp;
			display = tamp;
			out.close();
		}
		

	}

}

void displayDecoded()
{
	cout << display << endl;
}


void Bonus()
{

	ifstream in("reconstructed.txt");
	if (in)
	{
		while (!in.eof())
		{
			decoded += in.get();
		}
	}
	cout << endl;
}
void equal()
{
	if (fileText != display)
	{
		cout << "Original File = " << endl;
		cout << fileText << endl << endl;
		cout << "Decoded file = " << endl;
		cout << display << endl << endl;

		cout << "Both files are not exactly same " << endl << endl;
	}
	else
	{

		cout << "Original File = " << endl;
		cout << fileText << endl << endl;
		cout << "Decoded file = " << endl;
		cout << display << endl << endl;
		cout << "Both Files are exactly same " << endl << endl;
	}

	cout << endl;
}
void diffChar()
{
	string diff;
	if (fileText.size() == decoded.size())
	{
		cout << " ----------------------- " << endl;
		cout << "| Original  |   Diff   |" << endl;
		cout << " ----------------------- " << endl;

		for (int i = 0; i < decoded.size(); i++)
		{
			if (decoded[i] != fileText[i])
			{
				cout << "|\t" << fileText[i] << "   |\t " << decoded[i] << "     |" << endl;
				cout << " ----------------------- " << endl;
			}
		}
	}

	else if (fileText.size() < decoded.size())
	{
		cout << " ----------------------- " << endl;
		cout << "| Original  |   Diff   |" << endl;
		cout << " ----------------------- " << endl;

		for (int i = 0; i < fileText.size(); i++)
		{
			if (decoded[i] != fileText[i])
			{
				cout << "|\t" << fileText[i] << "   |\t " << decoded[i] << "     |" << endl;
				cout << " ----------------------- " << endl;
			}
		}

		cout << "Extra characters in decoded file:" << endl;
		int j = fileText.size();
		while (j < decoded.size())
		{
			cout << "| " << decoded[j] << " |" << endl;
			cout << " ----------------------- " << endl;
			j++;
		}
	}

	else
	{
		cout << " ----------------------- " << endl;
		cout << "| Original  |   Diff   |" << endl;
		cout << " ----------------------- " << endl;

		for (int i = 0; i < decoded.size(); i++)
		{
			if (decoded[i] != fileText[i])
			{
				cout << "|\t" << fileText[i] << "   |\t " << decoded[i] << "     |" << endl;
				cout << " ----------------------- " << endl;
			}
		}

		cout << "Extra characters in original file:" << endl;
		int j = decoded.size();
		while (j < fileText.size())
		{
			cout << "| " << fileText[j] << " |" << endl;
			cout << " ----------------------- " << endl;
			j++;
		}
	}
	cout << endl;
}

void displayReport()
{
	int choice = 0;

	while (choice != -1) {
		cout << endl;
		cout << "Select the option that you want to display = " << endl;
		cout << " 1: Files are same or not? \n 2: Size of original file \n 3: Size of encoded file \n 4: Size of reconstructed file \n 5: Display different Characters \n Press '-1' to exit" << endl << endl;
		cout << "Enter your choice = ";
		cin >> choice;

		if (choice == 1)
		{
			equal();
		}

		else if (choice == 2)
		{
			cout << "Total size of original.txt in bits is =" << (fileText.size() - 1) * 7 << endl << endl;
		}

		else if (choice == 3)
		{
			cout << "Size in bits of encoded.txt = " << noOf7bitString * 7 << endl << endl;
		}

		else if (choice == 4)
		{
			cout << "Size in bits of reconstructed.txt = " << (decoded.size() - 1) * 7 << endl << endl;
		}

		else if (choice == 5)
		{
			diffChar();
		}

	}
}
