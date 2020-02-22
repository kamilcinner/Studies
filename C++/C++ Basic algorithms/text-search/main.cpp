// The author of this program is Kamil Cinner.

#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>

#define MAX(a, b) (a > b) ? a : b

using namespace std;

class Data
{
public:

	string text;
	string pattern;
	
	int text_lenght;
	int pattern_lenght;

	int* index = NULL;
	int nof_index = 0;

	int ASIZE = 255; // alphabet size

	int* bad_character_shift;
	int* good_suffix_shift;
	int* suff;

	void load()
	{
		cout << "Enter text (change spaces by '_'):" << endl;
		cin >> text;
		text_lenght = text.size();
		cout << endl << "Enter pattern to search:" << endl;
		cin >> pattern;
		pattern_lenght = pattern.size();

		bad_character_shift = new int[ASIZE];
		good_suffix_shift = new int[pattern_lenght];
		suff = new int[pattern_lenght];
	}

	void create(int input)
	{
		int* new_index = NULL;
		nof_index++;
		new_index = (int*)realloc(index, nof_index * sizeof(int));
		if (new_index != NULL)
		{
			index = new_index;
			index[nof_index - 1] = input;
		}
		else
		{
			free(index);
			free(new_index);
			for (int i = 5;i > 0;i--)
			{
				system("cls");
				cout << "Memory realocation error! Program wille be closed in ( " << i << " )";
				Sleep(1000);
			}
			exit(1);
		}
	}
};

void final(Data &D);

int main()
{
	Data main;
	main.load();

	final(main);
	
	cout << endl << endl;
	system("pause");
    return 0;
}

void naive(Data &D)
{
	int j;

	for (int i = 0;i <= D.text_lenght - D.pattern_lenght;i++)
	{
		j = 0;
		while (D.pattern[j] == D.text[i + j] && j < D.pattern_lenght) j++;
		if (j == D.pattern_lenght) D.create(i + 1);
	}
}

//prepare bad character shift table
void pre_bad_character_shift(Data &D)
{
	int i;

	for (i = 0; i < D.ASIZE; i++)
	{
		D.bad_character_shift[i] = D.pattern_lenght;
	}

	for (i = 0; i < D.pattern_lenght - 1; ++i)
	{
		D.bad_character_shift[D.pattern[i]] = D.pattern_lenght - i - 1;
	}
}

//prepare suff table
void pre_suff(Data &D)
{
	int i, j;

	D.suff[D.pattern_lenght - 1] = D.pattern_lenght;
	for (i = D.pattern_lenght - 2; i >= 0; --i)
	{
		for (j = 0; j <= i && D.pattern[i - j] == D.pattern[D.pattern_lenght - j - 1]; j++);
		D.suff[i] = j;
	}
}

//prepare good_suffix_shift table
void pre_good_suffix_shift(Data &D)
{
	int i, j;

	pre_suff(D);

	for (i = 0; i < D.pattern_lenght; i++)
	{
		D.good_suffix_shift[i] = D.pattern_lenght;
	}

	j = 0;
	for (i = D.pattern_lenght - 1; i >= 0; --i)
	{
		if (D.suff[i] == i + 1)
		{
			for (; j < D.pattern_lenght - 1 - i; ++j)
			{
				D.good_suffix_shift[j] = D.pattern_lenght - 1 - i;
			}
		}
	}

	for (i = 0; i <= D.pattern_lenght - 2; ++i)
	{
		D.good_suffix_shift[D.pattern_lenght - 1 - D.suff[i]] = D.pattern_lenght - 1 - i;
	}
}

//Boyer-Moore algorithm
void BM(Data &D)
{
	int i, j;

	pre_bad_character_shift(D);
	pre_good_suffix_shift(D);

	j = 0;
	while (j <= D.text_lenght - D.pattern_lenght)
	{
		for (i = D.pattern_lenght - 1; i >= 0 && D.pattern[i] == D.text[i + j]; --i);
		if (i < 0) {
			D.create(j + 1);
			j += D.good_suffix_shift[0];
		}
		else
			j += MAX(D.good_suffix_shift[i], D.bad_character_shift[D.text[i + j]] - D.pattern_lenght + 1 + i);
	}
}

void result(Data D)
{
	if (D.nof_index > 0)
	{
		if (D.nof_index == 1)
			cout << endl << "Found index of :" << endl;
		else
			cout << endl << "Znalezione indeksy poczatku wzorca w tekscie:" << endl;
		for (int i = 0;i < D.nof_index;i++)
			cout << D.index[i] << "  ";
	}
	else
		cout << endl << "Brak wystapien wzorca w tekscie." << endl;
}

void final(Data &D)
{
	naive(D);
	cout <<endl<< "----------------------------------------";
	cout <<endl<< "Wynik algorytmu naiwnego:" << endl;
	result(D);
	D.nof_index = 0;
	delete(D.index);
	D.index = NULL;
	BM(D);
	cout <<endl<< "----------------------------------------";
	cout <<endl<< "Wynik algorytmu BM:" << endl;
	result(D);
}