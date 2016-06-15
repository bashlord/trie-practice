#ifndef TRIE_H
#define TRIE_H
#include <set>
#include <string>
#include <ctype.h>
#include <iostream>
#include <vector>
#define OFFSET 97
#define ASCII_VALUE 97
#define OFFSET_ALPHA 65
#define MAXSIZE 26


using namespace std;


class Trie;

class TrieNode{
  public:
  
  TrieNode (char chr,bool used,bool end):chr(chr){
    END = end;
    USED = used;
    point = 0;
  }
  char chr; // character to be inserted
  Trie* point;  // Pointer to Trie
  bool END; // Boolean for for an end of character of word
  bool USED;    // Boolean flag if the word has been checked
};

class Trie{
public:
  TrieNode* nodes[(MAXSIZE*2)+1];  
  vector<string> words;
/**
 * Constructor that creates array of TrieNodes
 */  
  Trie(){
    for(int i=0;i<MAXSIZE;i++){
      nodes[i] = new TrieNode((char)i+OFFSET,false,false);
    }
    for(int i=0;i<MAXSIZE;i++){
      nodes[i+26] = new TrieNode((char)i+OFFSET_ALPHA,false,false);
    }
    nodes[MAXSIZE*2] = new TrieNode((char)45,false,false);
  }

  int getSize(){return sizeof(nodes);}
  void addWord(string str){ words.push_back(str);}


  void insert(Trie* trie,string word){
    if(word.length()==0)
        return;
  //cout << "1\n" << endl;
    int i =0;
    while(word[0] != trie->nodes[i]->chr){
        //cout << "i " << i <<  " : " << trie->nodes[i]->chr<< "--" << word[0]<<"\n"<<  endl;
        i++; 
    }


   // cout << "2\n" << endl;
    if(trie->nodes[i]->USED==false){//turns on the used flag
        trie->nodes[i]->USED=true;
        if(word.length()==1)
        trie->nodes[i]->END=true;//turns on the end word flag
        trie->nodes[i]->point = new Trie();
    }
    //cout << "3\n" << endl;
    insert(trie->nodes[i]->point,word.substr(1,word.length() ) ) ; //recurses
}

bool search(Trie* trie,string word){
  string str = word;
  bool done = false;

  
  TrieNode** nodes1 = trie->nodes;
  int off = 0;
  if((int)word[0] < 97)
    off = 29;
  else
    off = ASCII_VALUE;
  int index = word[0] - off;

  if((int)word[0] == 45){
    index = 52;
  }
  cout <<  str << index<< (int)word[0]<<"--1\n" << endl;
  while( !done ){
/* Check to see if index is marked as used */
    if( nodes1[index]->USED == true ){
/* Reached end of word and index is and END index: return true */
      if(str.length() == 1 && nodes1[index]->END == true){
        return true;
    }
/* Reached end of word and not an END index */
      else if( str.length() == 1 ){
        return false;
    }
/* Keep interating */
      nodes1 = nodes1[index]->point->nodes;
      str = str.substr(1,str.length());
      if((int)str[0] < 97)
        off = 29;
      else
        off = ASCII_VALUE;

      if((int)str[0] == 45){
        index = 52;
      }else
      index = str[0] - off;
      cout <<  str << index<< (int)str[0]<<"--2\n" << endl;
    }
    else{
      return false;
    }
  }
}


  void initLex(){
    for(std::vector<string>::iterator it=words.begin();it!=words.end();++it){
    insert(this,*it); //insert method for words
  }



  }
/**
 * Desctuctor that will delete all nodes and sub-trees
 */
  ~Trie(){
    destroy(nodes);
    //delete(nodes);
  }
  
  private:

/**
 * Deletes all nodes
 */
  static void destroy(TrieNode* nodes[MAXSIZE]){
    for(int i=0;i<MAXSIZE;i++){
      if(nodes[i]->USED==true){
    nodes[i]->USED=false;
    destroy(nodes[i]->point->nodes);
      }
      delete(nodes[i]);
    }
  }
};


class Utils{
  public:
/**
 * Method Name: insertSet
 * Description: inserts passed argument into our set
 * Param: A single string
 * Returns: None
 */  
  void insertSet(const string word);
/**
 * Method Name: insert
 * Description: Will insert passed word into passed trie
 * Param: two parameters:First is a pointer to a Trie; Second is a string.
 * Returns: None 
 */ 
  void insert(Trie* trie, string word);
/**
 * Method Name: search
 * Description: Will search for a word in a passed Trie
 * param: two parameters: One is a Trie pointer; Second is a string
 * Returns: boolean
 */  
  bool search(Trie* trie, string word);
/* Will store all valid words */  
  set<string> lexSet;

  int lexSetCount(){ return lexSet.size();}
};
#endif