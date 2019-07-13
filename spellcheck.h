//Spellchecker Abstract Class
#ifndef _SPELLCHECK_H_
#define _SPELLCHECK_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;

class SpellChecker
{
	private:
		string alphabets = "abcdefghijklmnopqrstuvwxyz";
		typedef std::vector<string> Vector;
		typedef std::map<string, int> Dictionary;
		Dictionary dictionary;
		
		string filterAlpha(string &word);

		void extractWords(string &filenamze);
		void known_words(Vector &results, Dictionary &candidates);
		void edits(string &word, Vector &result);
		void edits2(Vector &result, Dictionary &candidates);

		void deletes(string &word, Vector &result);
		void transposes(string &word, Vector &result);
		void replaces(string &word, Vector &result);
		void inserts(string &word, Vector &result);


	public:
		//Constructor
		SpellChecker();

		void print_vector(Vector& v);
		void print_map(Dictionary& dict);

		string correct(string &word);
};

#endif