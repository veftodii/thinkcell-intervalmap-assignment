**Task:**

Complete the function `interval_map::assign()` to assign a value to an interval [_keyBegin_, _keyEnd_) defined in a variable of type `std::map<K, V>`.
This interval is compressed so the map contains only the first element of it. If _keyBegin_ >= _keyEnd_ then this designates an empty interval and assign must do nothing.

> [!NOTE]
> This task description is approximate because the original one wasn't saved.

**Sample input:**
```
interval_map<int, char> m('A'); // Contains the field std::map<K, V> m_map;
// Initialize the intervals
m.m_map[1] = 'B';
m.m_map[3] = 'A';
m.m_map[6] = 'C';
m.m_map[10] = 'A';

// Assign a new value to an interval
m.assign(1, 3, 'B');
printMap(m.m_map);
m.assign(1, 6, 'D');
printMap(m.m_map);
```

**Sample output:**
```
{{1 : B} {3 : A} {6 : C} {10 : A}}
{{1 : D} {6 : C} {10 : A}}
```
