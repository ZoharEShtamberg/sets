#include <string>
#include <assert.h>
#ifndef SETS__H
#define SETS__H
 class Set{
   public:
   Set();
   Set(const Set&);
   ~Set();
   bool add(int number);
   bool operator+=(int number); //like add
   bool remove(int number);
   bool contains(int number) const;
   int getSize() const; 

   Set& uniteWith(const Set&);
   Set& intersectWith(const Set&);  
   
   std::string toString() const; //for testing/debugging

   Set& operator=(const Set&);   //assignment
   Set& operator+=(const Set&);  //like uniteWith
   Set& operator^=(const Set&);  //like intersectWith

   class Iterator;
   Iterator begin() const;
   Iterator end() const;

private:
   int find(int num) const;
   void expand();
   int* data;
   int currentSize;
   int maxSize;
   static const int INITIAL_SIZE = 10;
   static const int EXPAND_RATE = 2;
   static const int NOT_FOUND = -1;
 };
Set unionSets(const Set&, const Set&); //'union' is a reserved word
Set intersection(const Set&, const Set&);
class Set::Iterator{
   public:
   int operator*() const;
   bool operator==(const Iterator&) const;
   bool operator!=(const Iterator&) const;
   Iterator& operator++(); //prefix
   Iterator operator++(int); //postfix

   private:
   friend class Set;
   Iterator(const Set*, int);
   const Set* set;
   int index;
};















#endif