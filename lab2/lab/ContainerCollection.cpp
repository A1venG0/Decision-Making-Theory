#include "ContainerCollection.hpp"


int ContainerCollection::GetContainersCount()
{
	return _containers.size();
}

void ContainerCollection::InitializeNewContainerWithCargo(const Cargo& cargo)
{
	auto container = Container(cargo);
	if (container.GetCapacity() >= cargo.GetSize())
	{
		_containers.push_back(container);
	}
}

int ContainerCollection::GetTotalSize()
{
	int totalSize = 0;
	for (auto& container : _containers)
	{
		totalSize += container.GetTotalSize();
	}
	return totalSize;
}

Container& ContainerCollection::GetLastContainer()
{
	if (!_containers.empty())
		return _containers.back();
	throw std::runtime_error("ContainerCollection is empty");
}

void ContainerCollection::AddCargoToLastContainer(const Cargo& cargo)
{
	_containers.back().AddCargo(cargo);
}

void ContainerCollection::AddEmptyContainer()
{
	auto container = Container();
	_containers.push_back(container);
}

int ContainerCollection::GetCollectionLength()
{
	return _containers.size();
}

std::vector<Container> ContainerCollection::GetContainerCollection()
{
	return _containers;
}

std::pair<Container*, int> ContainerCollection::GetFirstSuitable(const Cargo& cargo)
{
	int count = 0;
	for (auto& container : _containers)
	{
		count++;
		if (container.GetAvailableSpace() >= cargo.GetSize())
			return std::make_pair(&container, count);
	}

	return std::make_pair(nullptr, 0);
}

std::pair<Container*, int> ContainerCollection::GetMostEmpty()
{
	int count = 0;
	int mostEmptyIndex = 0;
	int mostEmptySpace = _containers.front().GetAvailableSpace();

	for (int i = 0; i < _containers.size(); i++)
	{
		count++;
		int currentSpace = _containers[i].GetAvailableSpace();

		if (currentSpace > mostEmptySpace)
		{
			mostEmptySpace = currentSpace;
			mostEmptyIndex = i;
		}
	}

	return std::make_pair(&_containers[mostEmptyIndex], count);
}

std::pair<Container*, int> ContainerCollection::GetMostSuitableAndFull(const Cargo& cargo)
{
	bool flag = false;
	int count = 0;
	auto& mostSuitable = _containers.front();
	for (auto& container : _containers)
	{
		int freeSpace = container.GetAvailableSpace();
		count += 2;
		if (freeSpace < mostSuitable.GetAvailableSpace() && freeSpace >= cargo.GetSize())
		{
			flag = true;
			mostSuitable = container;
		}
	}

	if (flag)
		return std::make_pair(&mostSuitable, count);

	return std::make_pair(nullptr, 0);
}