#include "sets.h"
#include <iostream>
using std::cout;
using std::endl;
int main() {
Set<char> set1;
Set<char> set2;
for (int j = 6; j < 20; j += 2) {
set1.add((char)j);
}
for (int j = 6; j < 12; j += 3) {
set2.add((char)j);
}
Set<char> unionSet = unionSets(set1,set2);
Set<char> intersectionSet = intersection(set1,set2);
cout << set1.toString() << endl;
cout << set2.toString() << endl;
cout << unionSet.toString() << endl;
cout << intersectionSet.toString() << endl;
cout << "now using iterators" << endl;
for(Set<char>::Iterator it = set1.begin(); it != set1.end(); ++it) {
cout << *it << endl;
}
cout << "now using range-based for loop" << endl;
for(char x: set2) {
	cout << x << endl;
}
return 0;
}