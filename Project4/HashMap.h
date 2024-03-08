#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
using namespace std;

template <typename T>
class HashMap
{
public:
	HashMap(double max_load = 0.75); // constructor
	~HashMap(); // destructor; deletes all of the items in the hashmap
	int size() const; // return the number of associations in the hashmap
	// The insert method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts
	// a new association into the hashmap with that key/value pair. If there is
	// already an association with that key in the hashmap, then the item
	// associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
	void insert(const std::string& key, const T& value);
	// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value or modify it directly within the map.
	T* find(const std::string& key);
	// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in
	// the hashmap and map it to the default value of type T. Then it will return a
	// reference to the newly created value in the map.
	T& operator[](const std::string& key);
private:
	struct Node
	{
		std::string key;
		T value;
		Node* next;
	};
	const double MAX_LOAD_FACTOR; // greatest max load factor for hashmap
	static const int INITIAL_SIZE = 10;
	int m_numElements;
	int m_mapSize;
	vector<Node*>* m_hashmap;

	// HELPER FUNCTIONS
	double getLoadFactor() const;
	void resize_rehash();
	void deleteLinkedList(Node* head);
	Node* findNode(const std::string& key);
};

// CONSTRUCTOR
template <typename T>
HashMap<T>::HashMap(double max_load)
	: m_mapSize(INITIAL_SIZE), m_numElements(0), MAX_LOAD_FACTOR(max_load)
{
	m_hashmap = new vector<Node*>(INITIAL_SIZE, nullptr);
}

// DESTRUCTOR
template <typename T>
HashMap<T>::~HashMap()
{
	for (typename vector<Node*>::iterator p = m_hashmap->begin(); p != m_hashmap->end(); p++)
	{
		deleteLinkedList((*p));
	}
	delete m_hashmap;
}

// returns the number of associations in the hashmap
template <typename T>
int HashMap<T>::size() const
{
	return m_numElements;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value)
{
	Node* target = findNode(key);
	if (target != nullptr)
	{
		target->value = value;
	}
	else
	{
		size_t hashedKey = std::hash<std::string>()(key) % m_mapSize;
		Node* insertNode = new Node;
		insertNode->key = key;
		insertNode->value = value;

		insertNode->next = (*m_hashmap)[hashedKey];
		(*m_hashmap)[hashedKey] = insertNode;
		m_numElements++;
	}
}

template <typename T>
T* HashMap<T>::find(const std::string& key)
{
	Node* target = findNode(key);
	if (target != nullptr)
	{
		T* val = &(target->value);
		return val;
	}
	return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key)
{
	Node* target = findNode(key);
	if (target != nullptr)
	{
		return (target->value);
	}
	else
	{
		T defaultValue;
		insert(key, defaultValue); // CHANGE: DEFAULT T?
		return defaultValue;
	}
}

// HELPER FUNCTIONS
template <typename T>
double HashMap<T>::getLoadFactor() const // returns the load factor of the hashmap
{
	return (m_numElements / m_mapSize);
}

template <typename T>
void HashMap<T>::resize_rehash() // resizes the array and rehashes all items
{
	// resize the array
	int newMapSize = 2 * m_mapSize;
	vector<Node*>* resizedHM = new vector<Node*>(newMapSize, nullptr);

	// rehash all elements in original hashmap to the new hashmap
	for (typename vector<Node*>::iterator p = m_hashmap->begin(); p != m_hashmap->end(); p++)
	{
		Node* iterPtr = (*p);
		while (iterPtr != nullptr)
		{
			std::string nodeKey = iterPtr->key;
			T nodeValue = iterPtr->value;
			size_t hashedKey = std::hash<std::string>()(nodeKey) % newMapSize;

			Node* rehashNode = new Node;
			rehashNode->key = nodeKey;
			rehashNode->value = nodeValue;
			rehashNode->next = resizedHM[hashedKey];
			resizedHM[hashedKey] = rehashNode;

			Node* toBeDeleted = iterPtr;
			iterPtr = iterPtr->next;
			delete toBeDeleted;
		}
	}

	// delete the old hashmap, set m_hashmap to the new hashmap
	delete m_hashmap;
	m_hashmap = resizedHM;
	m_mapSize = newMapSize;
}

template <typename T>
void HashMap<T>::deleteLinkedList(Node* head)
{
	if (head != nullptr)
	{
		Node* toBeDeleted = head;
		head = head->next;
		delete toBeDeleted;
		deleteLinkedList(head);
	}
}

template <typename T>
typename HashMap<T>::Node* HashMap<T>::findNode(const std::string& key)
{
	size_t hashedKey = std::hash<std::string>()(key) % m_mapSize;
	for (Node* tPtr = (*m_hashmap)[hashedKey]; tPtr != nullptr; tPtr = tPtr->next)
	{
		if (key == tPtr->key)
			return tPtr;
	}
	return nullptr;
}

#endif // HASMAP_H