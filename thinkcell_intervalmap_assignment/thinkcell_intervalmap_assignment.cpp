#include <map>
#include <iostream>

template<typename K, typename V>
class interval_map {
private:
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(const V &val) : m_valBegin(val) {
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, and assign must do nothing.
	void assign(const K &keyBegin, const K &keyEnd, const V &val) {
		// Check for an invalid interval
		if (!(keyBegin < keyEnd)) {
			return;
		}

		// Insert the first key element if the map is empty
		if (m_map.empty() && !(m_valBegin == val)) {
			m_map[keyBegin] = val;
			return;
		}

		// Get position of the first element in the range
		auto mapItem = m_map.lower_bound(keyBegin);
		auto prevItem = mapItem;

		// Check if previous item value is the same as the current one
		if (mapItem != m_map.begin()) {
			prevItem--;
			if (prevItem->second == val) {
				mapItem = prevItem;
			}
		}
			
		// If the item was not found, then insert a new one
		if (mapItem == m_map.end()) {
			m_map[keyBegin] = val;
		}
		else {
			if (mapItem != m_map.begin() || !(m_valBegin == val)) {
				// Update first element in the range
				mapItem->second = val;
				mapItem++;
			}

			// Remove all other elements in the range (keyBegin, keyEnd)
			while ((mapItem->first < keyEnd || (mapItem == m_map.begin() && mapItem->second == m_valBegin)) && mapItem != m_map.end()) {
				mapItem = m_map.erase(mapItem);
			}
		}
	}

	// look-up of the value associated with key
	const V& operator[](const K &key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.
void IntervalMapTest() {
	interval_map<int, char> m('A');
	// Initialize the intervals
	m.m_map[1] = 'B';
	m.m_map[3] = 'A';
	m.m_map[6] = 'C';
	m.m_map[10] = 'A';

	auto printMap = [](const auto &aMap) {
		std::cout << "{";
		for (const auto &i : aMap) {
			std::cout << "{" << i.first << " : " << i.second << "} ";
		}
		std::cout << "}" << std::endl;
	};

	// Assign a new value to an interval
	m.assign(1, 3, 'B');
	printMap(m.m_map);
	m.assign(1, 6, 'D');
	printMap(m.m_map);
}

int main() {
	IntervalMapTest();

	return EXIT_SUCCESS;
}