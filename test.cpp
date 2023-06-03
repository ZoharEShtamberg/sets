#include "sets.h"
#include <iostream>
using std::cout;
using std::endl;
int main() {
Set set1, set2;
for (int j = 0; j < 20; j += 2) {
set1.add(j);
}
for (int j = 0; j < 12; j += 3) {
set2.add(j);
}
Set unionSet = unionSets(set1,set2);
Set intersectionSet = intersection(set1,set2);
cout << set1.toString() << endl;
cout << set2.toString() << endl;
cout << unionSet.toString() << endl;
cout << intersectionSet.toString() << endl;
cout << "now using iterators" << endl;
for(Set::Iterator it = set1.begin(); it != set1.end(); ++it) {
cout << *it << endl;
}
cout << "now using range-based for loop" << endl;
for(int x: set2) {
	cout << x << endl;
}
return 0;
}