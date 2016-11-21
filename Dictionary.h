#ifndef DICTIONARY_INCLUDED
#define DICTIONARY_INCLUDED

// Dictionary class for maintaining an anagram dictionary
//     Dictionary d;        // create an empty dictionary
//     d.insert("hello");   // insert "hello" into the dictionary
//     d.lookup("idte",f);  // call the function f for every anagram of "idte"
//                          //     found in the dictionary

#include <string>

class DictionaryImpl;

class Dictionary
{
  public:
    Dictionary();
    ~Dictionary();
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
  private:
    DictionaryImpl* m_impl;
      // Dictionaries can not be copied or assigned.  We enforce this
      // by declaring the copy constructor and assignment operator private and
      // not implementing them.
    Dictionary(const Dictionary&);
    Dictionary& operator=(const Dictionary&);
};

#endif // DICTIONARY_INCLUDED
