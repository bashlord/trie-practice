#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cctype>
#include "trie.h"
using namespace std;
const int MAXLINE=256;

Utils util;
Trie* trie;
void trimmer(string& s)
{
 string::size_type pos = s.find_last_not_of(' ');
 if(pos != string::npos)
 {
  if (s.length()!=pos+1)//if there are trailing whitespaces erase them
   s.erase(pos+1);
  pos = s.find_first_not_of(' ');
  if(pos!=0) //if there are leading whitespaces erase them
   s.erase(0, pos);
 }
 else s="";
}

int main(int argc, char *argv[]) {
	ifstream inFile ("words.txt");
   char oneline[MAXLINE];
   
   trie = new Trie();
   
   string input = "";
   char myChar  = {0};
   string help = "--help";
int a = 0;
   while (inFile)
   {
       inFile.getline(oneline, MAXLINE);
       //cout << oneline << endl;
       string s = oneline;
       util.insertSet(s);

       trie->addWord(s);
       //util.insert(trie, s);
   }

	cout <<  "Dictionary read, number of words: "<< util.lexSetCount() <<  "\n" <<endl;
   inFile.close();
	
	trie->initLex();
	while (true) {
   		cout << "Please enter singular word sucka: \n";
   		getline(cin, input);

   		trimmer(input);
   		if ( input == help) {
     		cout << "Hello!  You typed help, but there is no help right now since I am still\n developing. Toodles."  << endl;
   		}else if(input.size() == 0){
   			cout << "You didn't enter anything.  Cmon." << endl;
   		}else{
   			cout << "You entered " << input << endl;
   			bool b = false;
   			b = trie->search(trie,input);
   			if(b){
   				cout <<  input<< " is a valid word!" << endl;
   			}else{
   				cout <<  input<< " is not a valid word.  Go back to school." << endl;
   			}
   		}
 	}
	
	return 0;
}
