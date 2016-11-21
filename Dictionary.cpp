// Dictionary.cpp

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <algorithm>  // for swap
using namespace std;


void removeNonLetters(string& s);

class DictionaryImpl
{
public:
	DictionaryImpl();
	~DictionaryImpl();
	void insert(string word);
	void lookup(string letters, void callback(string)) const;
	int hashFunc(string &word) const;
private:
	static const int capacity = 49999; //49999:268 //30707:267 //20107:273 //10007:269

	struct BUCKET {
		string diction;
		BUCKET* next;
	};
	BUCKET* m_buckets[capacity];
};

DictionaryImpl::DictionaryImpl()
{
	for (int i = 0; i < capacity; i++)
	{
		m_buckets[i] = new BUCKET;
		m_buckets[i]->diction = "";
		m_buckets[i]->next = nullptr;
	}
}

DictionaryImpl::~DictionaryImpl()
{
	for (int i = 0; i < capacity; i++)
		delete m_buckets[i];
}

int DictionaryImpl::hashFunc(string &word) const
{
	int i, total = 0;
	string sortedWord = word;
	sort(sortedWord.begin(), sortedWord.end());

	for (i = 0; i < sortedWord.length(); i++)
		total = total + (i + sortedWord.length()) * sortedWord[i];
	total = total % capacity;
	return total; //45ns
}

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	if (word.empty())
		return;
	int bucket = hashFunc(word);
	if (m_buckets[bucket] == nullptr)
	{
		m_buckets[bucket]->diction = word;
		m_buckets[bucket]->next = nullptr;
	}
	else
	{
		BUCKET* ptr = m_buckets[bucket];
		BUCKET* n = new BUCKET;
		n->diction = word;
		n->next = nullptr;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;
	removeNonLetters(letters);
	if (letters.empty())
		return;
	sort(letters.begin(), letters.end());
	int bucket = hashFunc(letters);
	BUCKET* ptr = m_buckets[bucket];
	for (;;)
	{
		if (ptr == nullptr)
			break;
		string word = ptr->diction;
		sort(word.begin(), word.end());
		if (word == letters)
			callback(ptr->diction);
		ptr = ptr->next;
	}
}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (string::const_iterator from = s.begin(); from != s.end(); from++)
	{
		if (isalpha(*from))
		{
			*to = tolower(*from);
			to++;
		}
	}
	s.erase(to, s.end());  // chop off everything from "to" to end.
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}

