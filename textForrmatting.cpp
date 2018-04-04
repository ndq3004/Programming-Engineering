// textFormatting.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>


enum { MAX_WORD_LEN = 20 };
enum { MAX_LINE_LEN = 50 };

using namespace std;
int flag = 0;
int IsWhiteSpace(int ch) {
	return (ch == ' ' || ch == '\n' || ch == '\t');
}

void ClearLine(char *line, int &lineLen, int &numWord) {
	line[0] = '\0';
	lineLen = 0;
	numWord = 0;
}

int ReadWord(char *word, fstream &f) {
	while(!f.eof()){
        f >> word;
        break;
	}
	if(f.eof()) flag = 1;
	return strlen(word);
}

void AddWord(const char *word, char * line, int &lineLen, fstream &f) {
	if (lineLen > 0) {
		line[lineLen] = ' ';
		line[lineLen + 1] = '\0';
		lineLen++;

		}

	strcat(line, word);
	lineLen += strlen(word);

}

void WriteLine(const char *line, int lineLen, int numWords, fstream &g) {

	int extraSpaces, spacesToInsert, i, j;
	extraSpaces = MAX_LINE_LEN - lineLen;
	if(extraSpaces <= numWords)
    {
        int dem = extraSpaces;
        for (i = 0; i < lineLen; i++)
            if (line[i] != ' ')
            {
                cout << line[i];
                g.put(line[i]);
            }
            else
            {
                if(dem > 0)
                {
                    cout <<"  ";
                    g.put('  ');
                    dem--;
                }
                else{
                    cout <<" ";
                    g.put(' ');
                }
            }
    }
	else
    {
        for (i = 0; i < lineLen; i++) {

            if (line[i] != ' ')
            {

                cout << line[i];
                g.put(line[i]);
            }
            else {
                spacesToInsert = extraSpaces / (numWords - 1);
                for (j = 1; j <= spacesToInsert + 1; j++)
                {
				    cout << " ";
				    g.put(' ');
				}
                extraSpaces -= spacesToInsert;
                numWords--;
            }
        }
	}
	cout << "\n";
	g.put('\n');
}

int main() {
	fstream f;
	fstream g;
	f.open("word.txt", ios::in);
	g.open("w2.txt", ios::out);
	char WORD[MAX_WORD_LEN + 1];
	int wordLen;
	char line[MAX_LINE_LEN + 1];
	int lineLen = 0;
	int numWords = 0;
	ClearLine(line, lineLen, numWords);

	while(1) {
		wordLen = ReadWord(WORD, f);
		// flag variable check if EOF
		if (flag)
		{
		    AddWord(WORD, line, lineLen, f);
			cout << line ;
			for(int i = 0; i< strlen(line); i++) g.put(line[i]);
			break;
		}
		else
		{
			if ((wordLen + 1 + lineLen) > MAX_LINE_LEN) {
			WriteLine(line, lineLen, numWords, g);
			ClearLine(line, lineLen, numWords);
			}

		AddWord(WORD, line, lineLen, f);
		numWords++;
		}
	}//endFor
    g.close();
	f.close();
}




