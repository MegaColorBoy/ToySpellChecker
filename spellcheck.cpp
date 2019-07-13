#include "spellcheck.h"

//Constructor
SpellChecker::SpellChecker(){}

void SpellChecker::edits(string &word, Vector &result)
{
	//Deletion
	deletes(word, result);

	//Transposition
	transposes(word, result);

	//Replacement
	replaces(word, result);

	//Insertion
	inserts(word, result);
}

void SpellChecker::deletes(string &word, Vector &result)
{
	for(int i=0; i<word.size(); i++)
	{
		result.push_back(word.substr(0,i) + word.substr(i+1));
	}
}

void SpellChecker::transposes(string &word, Vector &result)
{
	for(int i=0; i<word.size()-1; i++)
	{
		result.push_back(word.substr(0,i) + word[i+1] + word[i] + word.substr(i+2));
	}
}

void SpellChecker::replaces(string &word, Vector &result)
{
	for(int i=0; i<word.size(); i++)
	{
		for(int j=0; j<alphabets.size(); j++)
		{
			char ch = alphabets[j];
			result.push_back(word.substr(0,i) + ch + word.substr(i+1));
		}
	}
}

void SpellChecker::inserts(string &word, Vector &result)
{
	for(int i=0; i<word.size()+1; i++)
	{
		for(int j=0; j<alphabets.size(); j++)
		{
			char ch = alphabets[j];
			result.push_back(word.substr(0,i) + ch + word.substr(i));
		}
	}
}

void SpellChecker::extractWords(string &filename)
{
	ifstream infile;
	infile.open(filename);
	string x;
	while(infile >> x)
	{
		x = filterAlpha(x);
		dictionary[x]++;
	}
	// print_map(dictionary);
}

string SpellChecker::filterAlpha(string &word)
{
	for(int i=0; i<word.size(); i++)
	{
		char ch = word[i];

		if(ch < 0)
		{
			word[i] = '-';
		}

		if(isalpha(ch))
		{
			word[i] = tolower(ch);
		}
	}

	return word;
}

void SpellChecker::print_vector(Vector& v)
{
	for(int i=0; i<v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
}

void SpellChecker::print_map(Dictionary& dict)
{
	// int count = 0;
	cout << "{";
	for(auto p: dict)
	{
			cout << p.first << ":" << p.second << " ";
			// count += p.second;
	}
	cout << "}" << endl;
}

void SpellChecker::known_words(Vector& results, Dictionary &candidates)
{
	Dictionary::iterator end = dictionary.end();

	for(int i=0; i<results.size(); i++)
	{
		Dictionary::iterator val = dictionary.find(results[i]);

		if(val != end)
		{
			candidates[val->first] = val->second;
		}
	}
	// print_map(candidates);
}

string SpellChecker::correct(string &word)
{
	Vector result;
	Dictionary candidates;

	string file = "big.txt";

	//1. if it's in the dictionary, display it
	if(dictionary.find(word) != dictionary.end())
	{
		return word;
	}

	extractWords(file);

	edits(word, result);
	known_words(result, candidates);

	//2. if it's a known word but one edit away
	if(candidates.size() > 0)
	{
		return max_element(candidates.begin(), candidates.end())->first;
	}

	//3. if it's a known word but two edits away
	edits2(result, candidates);

	if(candidates.size() > 0)
	{
		return max_element(candidates.begin(), candidates.end())->first;
	}

	//4. Display nothing if it doesn't exist
	return "This word doesn't exist!";
}

//3. if it's a known word but two edits away
void SpellChecker::edits2(Vector &result, Dictionary &candidates)
{
	for(int i=0; i<result.size(); i++)
	{
		Vector edit2;

		edits(result[i], edit2);
		known_words(edit2, candidates);
	}	
}