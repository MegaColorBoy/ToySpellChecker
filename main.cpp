#include "spellcheck.h"

int main()
{
	SpellChecker sc;
	
	vector<string>words; 
	words.push_back("speling");
	words.push_back("korrect");
	words.push_back("whone");
	words.push_back("orogne");

	string word;

	for(int i=0; i<words.size(); i++)
	{
		word = words[i];
		cout << "Typed: " << word << endl;
		cout << "Did you mean: " << sc.correct(word) << "?" << endl;	
	}
	
	return 0;
}

