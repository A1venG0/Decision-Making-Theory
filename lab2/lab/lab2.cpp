#include "ContainerCollection.hpp"
#define ll long long

class Main
{
public:
	Main(int capacity = 100)
	{
		_containerCapacity = capacity;
	}

	int GetMinimumContainerCount(const std::vector<int>& cargosSizes)
	{
		return ceil(GetCargosSum(cargosSizes) / _containerCapacity);
	}

	int GetCargosSum(const std::vector<int>& cargosSizes)
	{
		int sum = 0;
		for (auto& cargoSize: cargosSizes)
		{
			sum += cargoSize;
		}
		return sum;
	}

	void NextFit(std::vector<int>& sizes, bool sort=false, bool isReversed = false)
	{	
		std::string lbl;
		std::vector<Cargo> cargos;
		if (sort)
		{
			lbl = "NFA with ordering";
			cargos = getCargosFromSizes(sizes, true);
		}
		else
		{
			lbl = "NFA without ordering";
			cargos = getCargosFromSizes(sizes);
		}
		if (isReversed)
			std::reverse(cargos.begin(), cargos.end());
		auto containers = new ContainerCollection();
		containers -> AddEmptyContainer();

		int cnt = 0;
		for (auto& cargo: cargos)
		{
			auto& lastContainer = containers -> GetLastContainer();
			if (lastContainer.GetAvailableSpace() >= cargo.GetSize())
				lastContainer.AddCargo(cargo);
			else
			{
				containers -> InitializeNewContainerWithCargo(cargo);
				cnt += containers -> GetCollectionLength();
			}
		}
		std::vector<Container> newContainers = containers -> GetContainerCollection();

		PrintContainerCollection(newContainers, lbl);
		std::cout << "computational complexity: " << cnt << '\n';
		delete containers;
	}

	void FirstFit(std::vector<int>& sizes, bool sort=false, bool isReversed=false)
	{
		int cnt = 0;
		std::vector<Cargo> cargos;
		std::string lbl;
		if (sort)
		{
			lbl = "FFA with ordering";
			cargos = getCargosFromSizes(sizes, true);
			cnt += round(cargos.size() * log(cargos.size()) * 100) / 100;
		}
		else
		{
			lbl = "FFA without ordering";
			cargos = getCargosFromSizes(sizes);
		}
		if (isReversed)
			std::reverse(cargos.begin(), cargos.end());

		auto containers = new ContainerCollection();
		containers -> AddEmptyContainer();

		for (auto& cargo : cargos)
		{
			auto& lastContainer = containers -> GetLastContainer();
			if (lastContainer.GetAvailableSpace() >= cargo.GetSize())
				lastContainer.AddCargo(cargo);
			else
			{
				auto ans = containers -> GetFirstSuitable(cargo);

				if (ans.first != nullptr)
				{
					auto firstSuitable = ans.first;
					cnt += ans.second;
					firstSuitable -> AddCargo(cargo);
				}
				else
				{
					cnt += containers -> GetCollectionLength();
					containers -> InitializeNewContainerWithCargo(cargo);
				}
			}
		}

		std::vector<Container> newContainers = containers -> GetContainerCollection();

		PrintContainerCollection(newContainers, lbl);
		std::cout << "computational complexity: " << cnt << '\n';

		delete containers;
	}

	void WorstFit(std::vector<int>& sizes, bool sort=false, bool isReversed=false)
	{
		int cnt = 0;
		std::vector<Cargo> cargos;
		std::string lbl;
		if (sort)
		{
			lbl = "WFA with ordering";
			cargos = getCargosFromSizes(sizes, true);
		}
		else
		{
			lbl = "WFA without ordering";
			cargos = getCargosFromSizes(sizes);
		}
		if (isReversed)
			std::reverse(cargos.begin(), cargos.end());
		auto containers = new ContainerCollection();
		containers -> AddEmptyContainer();
		

		for (auto& cargo : cargos)
		{
			cnt++;
			auto& lastContainer = containers -> GetLastContainer();
			if (lastContainer.GetAvailableSpace() >= cargo.GetSize())
				lastContainer.AddCargo(cargo);
			else
			{
				auto ans = containers -> GetMostEmpty();
				auto container = ans.first;
				cnt += ans.second + 1;

				if (container -> GetAvailableSpace() >= cargo.GetSize())
					container -> AddCargo(cargo);
				else
					containers -> InitializeNewContainerWithCargo(cargo);
			}
		}

		std::vector<Container> newContainers = containers -> GetContainerCollection();

		PrintContainerCollection(newContainers, lbl);
		std::cout << "computational complexity: " << cnt << '\n';

		delete containers;
	}

	void BestFit(std::vector<int>& sizes, bool sort=false, bool isReversed=false)
	{
		int cnt = 0;
		std::vector<Cargo> cargos;
		std::string lbl;
		if (sort)
		{
			lbl = "BFA with ordering";
			cargos = getCargosFromSizes(sizes, true);
		}
		else
		{
			lbl = "BFA without ordering";
			cargos = getCargosFromSizes(sizes);
		}
		if (isReversed)
			std::reverse(cargos.begin(), cargos.end());
		auto containers = new ContainerCollection();
		containers -> AddEmptyContainer();

		for (auto& cargo : cargos)
		{
			auto& container = containers -> GetLastContainer();
			cnt++;
			if (container.GetAvailableSpace() >= cargo.GetSize())
				container.AddCargo(cargo);
			else
			{
				auto ans = containers -> GetMostSuitableAndFull(cargo);
				if (ans.first != nullptr)
				{
					auto mostFullAndSuitable = ans.first;
					cnt += ans.second + 1;
					if (mostFullAndSuitable -> GetAvailableSpace() >= cargo.GetSize())
						mostFullAndSuitable -> AddCargo(cargo);
					else
						containers -> InitializeNewContainerWithCargo(cargo);
				}
				else
				{
					cnt += containers -> GetCollectionLength();
					containers -> InitializeNewContainerWithCargo(cargo);
				}
			}
		}

		std::vector<Container> newContainers = containers -> GetContainerCollection();

		PrintContainerCollection(newContainers, lbl);
		std::cout << "computational complexity: " << cnt << '\n';

		delete containers;
	}

	std::vector<Cargo> getCargosFromSizes(std::vector<int>& sizes, bool sort = false)
	{
		if (sort)
			std::sort(sizes.begin(), sizes.end());

		std::vector<Cargo> cargos;
		for (auto& size : sizes)
		{
			cargos.emplace_back(size);
		}

		return cargos;
	}

	void PrintContainerCollection(const std::vector<Container>& collection, std::string method="")
	{
		std::cout << method << '\n';
		for (auto& container : collection)
		{
			std::cout << "Container load: " << container.GetTotalSize() << " (";
			auto cargos = container.GetCollection();
			for (auto& cargo: cargos)
			{
				std::cout <<  cargo.GetSize() << " ";
			}
			std::cout << " )" << '\n';
		}

		std::cout << "Container size: " << collection.size() << '\n';
	}
	

private:
	int _containerCapacity;
};

int main()
{
	std::vector<int> sizes_one = {40, 29, 31, 17, 97, 71, 81, 75, 9, 27, 67, 56, 97, 53, 86, 65, 6, 83, 19, 24 };
	std::vector<int> sizes_two = {28, 71, 32, 29, 3, 19, 70, 68, 8, 15, 40, 49, 96, 23, 18, 45, 46, 51, 21, 55 };
	std::vector<int> sizes_three = {79, 88, 64, 28, 41, 50, 93, 51, 34, 64, 24, 14, 87, 56, 43, 91, 27, 65, 59, 36 };
	std::vector<int> sizes_four;
	for (int i = 0; i < 20; i++)
	{
		sizes_four.push_back(sizes_one[i]);
	}
	for (int i = 0; i < 20; i++)
	{
		sizes_four.push_back(sizes_two[i]);
	}
	for (int i = 0; i < 20; i++)
	{
		sizes_four.push_back(sizes_three[i]);
	}

	Main app;

	
	app.NextFit(sizes_one, false);
	app.NextFit(sizes_two, false);
	app.NextFit(sizes_three, false);
	app.NextFit(sizes_four, false);
	std::cout << "------------------" << '\n';
	app.FirstFit(sizes_one, false);
	app.FirstFit(sizes_two, false);
	app.FirstFit(sizes_three, false);
	app.FirstFit(sizes_four, false);
	std::cout << "------------------" << '\n';
	app.WorstFit(sizes_one, false);
	app.WorstFit(sizes_two, false);
	app.WorstFit(sizes_three, false);
	app.WorstFit(sizes_four, false);
	std::cout << "------------------" << '\n';
	app.BestFit(sizes_one, false);
	app.BestFit(sizes_two, false);
	app.BestFit(sizes_three, false);
	app.BestFit(sizes_four, false);
	std::cout << "------------------" << '\n';
	app.NextFit(sizes_one, true);
	app.NextFit(sizes_two, true);
	app.NextFit(sizes_three, true);
	app.NextFit(sizes_four, true);
	std::cout << "------------------" << '\n';
	app.FirstFit(sizes_one, true);
	app.FirstFit(sizes_two, true);
	app.FirstFit(sizes_three, true);
	app.FirstFit(sizes_four, true);
	std::cout << "------------------" << '\n';
	app.WorstFit(sizes_one, true);
	app.WorstFit(sizes_two, true);
	app.WorstFit(sizes_three, true);
	app.WorstFit(sizes_four, true);
	std::cout << "------------------" << '\n';
	app.BestFit(sizes_one, true);
	app.BestFit(sizes_two, true);
	app.BestFit(sizes_three, true);
	app.BestFit(sizes_four, true);
	std::cout << "------------------" << '\n';
	
	return 0;
}