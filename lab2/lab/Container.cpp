#include "Container.hpp"
	
Container::Container(const Cargo& cargo, int capacity)
{
 	_cargos.push_back(cargo);
 	_containerCapacity = capacity;
}

void Container::AddCargo(const Cargo& cargo)
{
	if (GetAvailableSpace() >= _cargos.size())
		_cargos.push_back(cargo);
}

std::vector<Cargo> Container::GetCollection() const
{
	return _cargos;
}

int Container::GetAvailableSpace()
{
	return _containerCapacity - GetTotalSize();
}

bool Container::IsEmpty()
{
	return _cargos.empty();
}

int Container::GetTotalSize()
{
	int totalSize = 0;
	for (auto& cargo : _cargos)
		totalSize += cargo.GetSize();
	return totalSize;
}

int Container::GetTotalSize() const
{
	int totalSize = 0;
	for (auto& cargo : _cargos)
		totalSize += cargo.GetSize();
	return totalSize;
}

int Container::GetCapacity()
{
	return _containerCapacity;
}
