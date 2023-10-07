#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

class Cargo
{
public:
	Cargo(int size) : _size(size) {}

	int GetSize() const
	{
		return _size;
	}

	int GetSize()
	{
		return _size;
	}
private:
	int _size;
};