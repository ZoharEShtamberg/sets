#include "sets.h"

Set::Set() : data(new int[INITIAL_SIZE]()), currentSize(0), maxSize(INITIAL_SIZE)
{
}
Set::Set(const Set &source) : data(new int[source.maxSize]()), currentSize(source.currentSize), maxSize(source.maxSize)
{
	for (int c = 0; c < currentSize; c++)
	{
		data[c] = source.data[c];
	}
}
Set::~Set()
{
	delete[] data;
}
bool Set::add(int number)
{
	if (contains(number))
	{
		return false;
	}
	if (currentSize >= maxSize)
	{
		expand();
	}

	data[currentSize] = number;
	currentSize++;
	return true;
}

bool Set::contains(int number) const
{
	if (find(number) == NOT_FOUND)
	{
		return false;
	}
	return true;
}

int Set::find(int number) const
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
void Set::expand()
{
	int *newArr = new int[maxSize * EXPAND_RATE]();
	for (int i = 0; i < currentSize; i++)
	{
		newArr[i] = data[i];
	}
	delete[] data;
	data = newArr;
	maxSize *= EXPAND_RATE;
}

bool Set::remove(int number)
{
	int index = find(number);
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
int Set::getSize() const
{
	return currentSize;
}

Set &Set::uniteWith(const Set &bride)
{
	int brideSize = bride.currentSize;
	for (int i = 0; i < brideSize; i++)
	{
		add(bride.data[i]);
	}
	return *this;
}

Set &Set::intersectWith(const Set &baby)
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

Set unionSets(const Set &setA, const Set &setB)
{
	Set result = setA;
	return result.uniteWith(setB);
}
Set intersection(const Set &setA, const Set &setB)
{
	Set result = setA;
	return result.intersectWith(setB);
}
std::string Set::toString() const
{
	std::string result = "{";
	for (int i = 0; i < currentSize; i++)
	{
		result += std::to_string(data[i]);
		if (i != currentSize - 1)
		{
			result += ", ";
		}
	}
	result += "}";
	return result;
}
Set &Set::operator=(const Set &source)
{
	if (this == &source)
	{
		return *this;
	}
	delete[] data;
	data = new int[source.maxSize]();
	currentSize = source.currentSize;
	maxSize = source.maxSize;
	for (int i = 0; i < currentSize; i++)
	{
		data[i] = source.data[i];
	}
	return *this;
}
Set &Set::operator+=(const Set &source)
{
	return uniteWith(source);
}
Set &Set::operator^=(const Set &source)
{
	return intersectWith(source);
}
bool Set::operator+=(int number)
{
	return add(number);
}

Set::Iterator Set::begin() const
{
	return Iterator(this, 0);
}
Set::Iterator Set::end() const
{
	return Iterator(this, currentSize);
}
// Iterator constructor
Set::Iterator::Iterator(const Set *set, int index) : set(set), index(index) {}
// Iterator methods

Set::Iterator &Set::Iterator::operator++()
{
	index++;
	return *this;
}

int Set::Iterator::operator*() const
{
	assert(index >= 0 && index < set->currentSize);
	return set->data[index];
}

bool Set::Iterator::operator==(const Iterator &other) const
{
	assert(set == other.set); // make sure iterators are from same set
	return index == other.index;
}
bool Set::Iterator::operator!=(const Iterator &other) const
{
	return !(*this == other);
}
Set::Iterator Set::Iterator::operator++(int)
{
	Iterator result = *this;
	++(*this);
	return result;
}