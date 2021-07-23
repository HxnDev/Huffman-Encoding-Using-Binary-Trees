#include "Queue.h"
#include "Tree.h"
#include "Encoding.h"

void displayBitArrays() {

	cout << " ------------------------------- " << endl;
	cout << "|  Character\t|\tCode\t|" << endl;
	cout << " ------------------------------- " << endl;

	for (int i = 0; i < uniqueChar; i++) {
		cout << "|\t" << charArray[i] << "\t|\t" << stringArray[i] << "\t|" << endl;
		cout << " ------------------------------- " << endl;
	}
	cout << endl;
}

int main()
{
	int choice = 0;
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t \t \t Welcome to Hxn's Assignment 4 Solution" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;


	readFile();
	cout << "Characters with their respective Frequency =" << endl;
	freqQueue.display();
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	constructTree();
	Bonus();
	Encode();
	formBitStrings();
	writingASCII();
	decode();

	while (choice != -1)
	{
		cout << "Following is the list of functions that can be performed using this code :" << endl << endl;
		cout << " 1: Original Size of File \n 2: No. of Unique Characters \n 3: Display Unique Characters \n 4: Display Tree 'Inorderly' \n 5: Huffman Table \n 6: 7-bit Binary Code Table \n 7: ASCII Table of 7-bit Binary Code \n 8: Display 'encoded.txt' \n 9: Display 'reconstructed.txt' \n 10: Bonus Task \n PRESS -1 TO EXIT" << endl;
		cout << "Enter your choice =";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			cout << "Total size of original.txt in bits is =" << (fileText.size() - 1) * 7 << endl;
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 2:
			cout << "Total no. of unique characters is =" << uniqueChar << endl;
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 3:
			cout << "Unique Characters are =" << endl;
			for (int i = 0; i < uniqueChar; i++)
			{
				cout << charArray[i] << " ";
			}
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;
			break;

		case 4:
			cout << "Tree after all symbols are inserted:" << endl << endl;
			tree.displayPostOrder();
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 5:
			cout << "Huffman Table = " << endl << endl;

			displayBitArrays();
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 6:
			cout << "Displaying Seven Bits Numbers " << endl << endl;
			displaysevenBit();
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 7:
			cout << "Writing ASCII values of each 7-bit Binary Code" << endl << endl;
			displayASCII();
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 8:
			cout << "Displaying encoded.txt" << endl << endl;
			displayEncoded();
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 9:
			cout << "Displaying reconstructed.txt " << endl << endl;
			displayDecoded();
			cout << endl;
			cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
			break;

		case 10:
			cout << "Displaying Menu = " << endl;
			displayReport();
			break;

		}
	}
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------THE END--------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;


}