#include "Cargo.cpp"

class Container
{
public:
	Container(const std::vector<Cargo>& cargo, int capacity = 100) :
		_cargos(cargo), _containerCapacity(capacity) {}
	Container(const Cargo& cargo, int capacity = 100);
	Container() : _containerCapacity(100) {};

	void AddCargo(const Cargo& cargo);
	std::vector<Cargo> GetCollection() const;
	int GetAvailableSpace();
	bool IsEmpty();
	int GetTotalSize();
	int GetTotalSize() const;
	int GetCapacity();

private:
	int _containerCapacity;
	std::vector<Cargo> _cargos;
};