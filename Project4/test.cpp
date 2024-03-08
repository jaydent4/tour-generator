#include "HashMap.h"
#include <iostream>
using namespace std;

void foo()
{
	// Define a hashmap that maps strings to doubles and has a maximum
	// load factor of 0.3. It will initially have 10 buckets when empty.
	HashMap<double> nameToGPA(0.3);
	// Add new items to the hashmap. Inserting the third item will cause
	// the hashmap to increase the number of buckets (since the maximum
	// load factor is 0.3), forcing a rehash of all items.
	nameToGPA.insert("Carey", 3.5); // Carey has a 3.5 GPA
	nameToGPA.insert("David", 2.99); // David needs to up his game
	cout << nameToGPA["Carey"] << " " << nameToGPA["David"] << endl;
	// you can also use brackets like C++'s unordered_map!
	nameToGPA["Annie"] = 3.85; // Adds Annie, who has the highest GPA of all

	double* davidsGPA = nameToGPA.find("David");
	if (davidsGPA != nullptr)
		*davidsGPA = 3.1; // after a re-grade of David's exam, update 2.99 -> 3.1
	nameToGPA.insert("Carey", 4.0); // Carey deserves a 4.0

	
	// sees if linda is in the map; if not, creates a new entry for linda in map
	cout << nameToGPA["Linda"]; // prints zero
}


int main()
{
	foo();
}