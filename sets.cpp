#include "sets.h"

Set::Set(): data(new int[INITIAL_SIZE]()), currentSize(0), maxSize(INITIAL_SIZE)
{}
Set::Set(const Set& source):
        data(new int[source.maxSize]()),currentSize(source.currentSize), maxSize(source.maxSize){
    for(int c = 0; c<currentSize ; c++){
        data[c] = source.data[c];
    }
}
Set::~Set(){
    delete[] data;
}
bool Set::add(int number){
    if(contains(number)){
        return false;
    }
    if(currentSize>=maxSize){
        expand();
    }

    data[currentSize] = number;
    currentSize++;
    return true;
}

bool Set::contains(int number) const{
    if(find(number)==NOT_FOUND){
        return false;
    }
    return true;
}

int Set::find(int number) const{
    for(int i = 0 ; i< currentSize ; i++){
        if(data[i]==number){
            return i;
        }
    }
    return NOT_FOUND;
}
void Set::expand(){
    int* newArr = new int[maxSize*EXPAND_RATE]();
    for(int i=0 ; i<currentSize ; i++){
        newArr[i]=data[i];
    }
    delete[] data;
    data = newArr;
    maxSize *= EXPAND_RATE;
}

bool Set::remove(int number){
    int index=find(number);
    if(index==NOT_FOUND){
        return false;
    }
    for (int i=index;i<currentSize-1;i++){
        data[i]=data[i+1];
    }
    currentSize--;
    return true;
}
int Set::getSize() const{
    return currentSize;
}

Set& Set::uniteWith(const Set& bride){
    int brideSize = bride.currentSize;
    for(int i=0;i<brideSize;i++){
        add(bride.data[i]);
    }
    return *this;
}

Set& Set::intersectWith(const Set& baby){
    for(int i = currentSize-1; i>=0 ;i--){
        if(!baby.contains(data[i])){
            remove(data[i]);
        }
    }
    return *this;
}

Set unionSets(const Set& setA, const Set& setB){
    Set result = setA;
    return result.uniteWith(setB);
}
Set intersection(const Set& setA, const Set& setB){
    Set result = setA;
    return result.intersectWith(setB);
}
std::string Set::toString() const{
    std::string result = "{";
    for(int i = 0 ; i<currentSize ; i++){
        result += std::to_string(data[i]);
        if(i!=currentSize-1){
            result += ", ";
        }
    }
    result += "}";
    return result;
}