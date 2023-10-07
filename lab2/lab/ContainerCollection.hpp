#include "Container.hpp"

class ContainerCollection
{
public:
	int GetContainersCount();
	void InitializeNewContainerWithCargo(const Cargo& cargo);
	int GetTotalSize();
	Container& GetLastContainer();
	void AddCargoToLastContainer(const Cargo& cargo);
	void AddEmptyContainer();
	int GetCollectionLength();
	std::vector<Container> GetContainerCollection();
	std::pair<Container*, int> GetFirstSuitable(const Cargo& cargo);
	std::pair<Container*, int> GetMostEmpty();
	std::pair<Container*, int> GetMostSuitableAndFull(const Cargo& cargo);

private:
	std::vector<Container> _containers;
};