#include "Environment.h"
#include "Tiger.h"

Environment::Environment(map<Species, int> _n)
{
	this->animals = std::make_shared<vector<shared_ptr<Animal>>>();
	for (auto& [species, number] : _n)
	{
		for (int i = 0; i < number; i++)
		{
			switch (species)
			{
			case Species::Tiger:
				// this->animals->push_back(std::make_shared<Tiger>(animals));
				break;
			default:
				break;
			}
		}
	}
}

shared_ptr<vector<shared_ptr<Animal>>> Environment::GetEnvironment() const
{
	return animals;
}

void Environment::Update()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);

	prev_positions->clear();
	// Don't call update in this for loop because update might cause the number of animals change.
	for (shared_ptr<Animal>& animal : *animals)
		prev_positions->push_back(animal->GetPosition());
	
	for (shared_ptr<Animal>& animal : *animals)
		animal->Update();
	
}

const shared_ptr<vector<Vector2D>> Environment::GetPrevPositions() const
{
	return prev_positions;
}

shared_ptr<Animal> Environment::GetClosetPair(const Animal& animal, Species species)
{
	Log::LogMessage("GetClosetPair is called", LogLevel::Info);
	shared_ptr<Animal> target=NULL;
	float min_distance=1e9;
	float distance;
	Vector2D position = animal.GetPosition();
	if (species != Species::NULLSPECIES) {
		for (shared_ptr<Animal>& neighbour: *animals)
			if (species==neighbour->GetSpecies())
			{
				distance=Vector2D::GetDistance(neighbour->GetPosition(),position)
			}
	}
	else {
		for (shared_ptr<Animal>& animal : *animals)
	}
		

	return NULL;
}

