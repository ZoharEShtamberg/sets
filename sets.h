#include <string>
#include <assert.h>
#ifndef SETS__H
#define SETS__H

template <class T> 
 class Set{
   public:
   Set();
   Set(const Set&);
   ~Set();
   bool add(T argument);
   bool operator+=(T argument); //like add
   bool remove(T argument);
   bool contains(T argument) const;
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
   int find(T argument) const;
   void expand();
   T* data;
   int currentSize;
   int maxSize;
   static const int INITIAL_SIZE = 10;
   static const int EXPAND_RATE = 2;
   static const int NOT_FOUND = -1;
 };
template <class T>
Set<T> unionSets(const Set<T>&, const Set<T>&); //'union' is a reserved word
template <class T>
Set<T> intersection(const Set<T>&, const Set<T>&);
template <class T>
class Set<T>::Iterator{
   public:
   int operator*() const;
   bool operator==(const Iterator&) const;
   bool operator!=(const Iterator&) const;
   Iterator& operator++(); //prefix
   Iterator operator++(int); //postfix

   private:
   friend class Set<T>;
   Iterator(const Set<T>*, int);
   const Set<T>* set;
   int index;
};
// implementation of Set<T>
template <class T>
Set<T>::Set() : data(new T[INITIAL_SIZE]()), currentSize(0), maxSize(INITIAL_SIZE)
{
}

template <class T>
Set<T>::Set(const Set<T> &source) : data(new T[source.maxSize]()), currentSize(source.currentSize), maxSize(source.maxSize)
{
	for (int c = 0; c < currentSize; c++)
	{
		data[c] = source.data[c];
	}
}

template <class T>  
Set<T>::~Set()
{
	delete[] data;
}

template <class T>
bool Set<T>::add(T argument)
{
	if (contains(argument))
	{
		return false;
	}
	if (currentSize >= maxSize)
	{
		expand();
	}

	data[currentSize] = argument;
	currentSize++;
	return true;
}

template <class T>
bool Set<T>::contains(T argument) const
{
	if (find(argument) == NOT_FOUND)
	{
		return false;
	}
	return true;
}

template <class T>	
int Set<T>::find(T argument) const
{
	for (int i = 0; i < currentSize; i++)
	{
		if (data[i] == number)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

template <class T>
void Set<T>::expand()
{
	T *newArr = new T[maxSize * EXPAND_RATE]();
	for (int i = 0; i < currentSize; i++)
	{
		newArr[i] = data[i];
	}
	delete[] data;
	data = newArr;
	maxSize *= EXPAND_RATE;
}

template <class T>
bool Set<T>::remove(T argument)
{
	int index = find(argument);
	if (index == NOT_FOUND)
	{
		return false;
	}
	for (int i = index; i < currentSize - 1; i++)
	{
		data[i] = data[i + 1];
	}
	currentSize--;
	return true;
}

template <class T>
int Set<T>::getSize() const
{
	return currentSize;
}

template <class T>
Set<T> &Set<T>::uniteWith(const Set &bride)
{
	int brideSize = bride.currentSize;
	for (int i = 0; i < brideSize; i++)
	{
		add(bride.data[i]);
	}
	return *this;
}


template <class T>
Set<T> &Set<T>::intersectWith(const Set<T> &baby)
{
	for (int i = currentSize - 1; i >= 0; i--)
	{
		if (!baby.contains(data[i]))
		{
			remove(data[i]);
		}
	}
	return *this;
}


template <class T>
Set<T> unionSets(const Set<T> &setA, const Set<T> &setB)
{
	Set result = setA;
	return result.uniteWith(setB);
}

template <class T>
Set<T> intersection(const Set<T> &setA, const Set<T> &setB)
{
	Set result = setA;
	return result.intersectWith(setB);
}



template <class T>
std::string Set<T>::toString() const
{
	std::string result = "{";
	for (int i = 0; i < currentSize; i++)
	{
		result += std::to_string(data[i]);//std::to_string(data[i]) check for T
		if (i != currentSize - 1)
		{
			result += ", ";
		}
	}
	result += "}";
	return result;
}

template <class T>
Set<T> &Set<T>::operator=(const Set<T> &source)
{
	if (this == &source)
	{
		return *this;
	}
	delete[] data;
	data = new T[source.maxSize]();
	currentSize = source.currentSize;
	maxSize = source.maxSize;
	for (int i = 0; i < currentSize; i++)
	{
		data[i] = source.data[i];
	}
	return *this;
}

template <class T>
Set<T> &Set<T>::operator+=(const Set<T> &source)
{
	return uniteWith(source);
}

template <class T>
Set<T> &Set<T>::operator^=(const Set<T> &source)
{
	return intersectWith(source);
}

template <class T>
bool Set<T>::operator+=(T argument)
{
	return add(argument);
}


template <class T>
Set<T>::Iterator Set<T>::begin() const
{
	return Iterator(this, 0);
}

template <class T>
Set<T>::Iterator Set<T>::end() const
{
	return Iterator(this, currentSize);
}


// Iterator constructor
template <class T>
Set<T>::Iterator::Iterator(const Set<T> *set, int index) : set(set), index(index) {}
// Iterator methods

template <class T>
Set<T>::Iterator &Set<T>::Iterator::operator++()
{
	index++;
	return *this;
}

template <class T>
int Set<T>::Iterator::operator*() const
{
	assert(index >= 0 && index < set->currentSize);
	return set->data[index];
}


template <class T>
bool Set<T>::Iterator::operator==(const Iterator &other) const
{
	assert(set == other.set); // make sure iterators are from same set
	return index == other.index;
}

template <class T>
bool Set<T>::Iterator::operator!=(const Iterator &other) const
{
	return !(*this == other);
}

template <class T>
Set<T>::Iterator Set<T>::Iterator::operator++(int)
{
	Iterator result = *this;
	++(*this);
	return result;
}















#endif