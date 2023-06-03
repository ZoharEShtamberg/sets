#include <string>
#ifndef SETS__H
#define SETS__H
 class Set{
private:
   int find(int num) const;
   void expand();
   int* data;
   int currentSize;
   int maxSize;
   static const int INITIAL_SIZE = 10;
   static const int EXPAND_RATE = 2;
   static const int NOT_FOUND = -1;
public:
   Set();
   Set(const Set&);
   ~Set();
   bool add(int number);
   bool remove(int number);
   bool contains(int number) const;
   int getSize() const;

   Set& uniteWith(const Set&);
   Set& intersectWith(const Set&);
   
   std::string toString() const;
 };
Set unionSets(const Set&, const Set&); //'union' is a reserved word
Set intersection(const Set&, const Set&);

















#endif