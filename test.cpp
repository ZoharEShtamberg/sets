#include "sets.h"
#include <iostream>
using std::cout;
using std::endl;
int main() {
Set<char> set1;
Set<char> set2;
set1.add('a');
set1.add('b');
set1.add('c');
set1.add('d');
set1.add('e');
set2.add('a');
set2.add('b');
set2.add('q');
set2.add('r');
set2.add('s');
Set<char> unionSet = unionSets(set1,set2);
Set<char> intersectionSet = intersection(set1,set2);
cout << set1.toString() << endl;
cout << set2.toString() << endl;
cout << unionSet.toString() << endl;
cout << intersectionSet.toString() << endl;
cout << "now using iterators" << endl;
for(auto it = set1.begin(); it != set1.end(); ++it) {
cout << *it << endl;
}
cout << "now using range-based for loop" << endl;
for(char x: set2) {
	cout << x << endl;
}
return 0;
}