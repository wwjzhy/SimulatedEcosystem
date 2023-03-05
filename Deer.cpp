#include "Deer.h"
#include "Utility.h"


Species Deer::GetSpecies()
{
	return Species::Deer;
}

void Deer::Move()
{

	MoveState state = MoveState::Walk;
	Vector2D UnitDirection;
	float Distance = 1e9;

	//probe function
	auto Nearest = [&](Species species,int sign)
	{
		shared_ptr<Animal> NearestFood = Environment::GetClosetPair(environment, *this, Species::Grass);

		float NearestDistance = Vector2D::GetDistance(NearestFood->GetPosition(), this->GetPosition());
		Vector2D NearestDirection = (NearestFood->GetPosition() - this->GetPosition()) * sign;

		if (Vector2D::GetDistance(NearestFood->GetPosition(), this->GetPosition()) <= AnimalConstants::DEER_PROBE_RADIUS)
		{
			if (Distance > NearestDistance)
			{
				Distance = NearestDistance;
				state = MoveState::Run;
				UnitDirection = NearestDirection / NearestDistance;
			}
		}
	};

	Nearest(Species::Grass,1);

	Nearest(Species::Wolf,-1);

	Nearest(Species::Tiger,-1);

	//Get velocity
	float velocity_scalar;

	if (state == MoveState::Run)
	{

		if (this->stamina >= AnimalConstants::DEER_MAX_STAMINA / 2)
		{
			velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY;
		}
		else if (this->stamina > AnimalConstants::DEER_MAX_STAMINA)
		{
			velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::DEER_MAX_STAMINA);
		}
		else
		{
			velocity_scalar = AnimalConstants::DEER_MIN_VELOCITY;
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::DEER_IDLE_PROBABILITY)
		{
			velocity_scalar = 0;
			state = MoveState::Idle;
		}
		else
		{
			velocity_scalar = AnimalConstants::DEER_MIN_VELOCITY;
			state = MoveState::Walk;
		}
	}

	//Get Direction
	this->velocity = UnitDirection * velocity_scalar;

	//update position
	this->position = this->position + this->velocity;

	//update stamina and energy
	if (state == MoveState::Idle || state == MoveState::Walk)
	{
		this->stamina = std::max(this->stamina + AnimalConstants::DEER_RECOVER_STAMINA_RATIO, AnimalConstants::DEER_MAX_STAMINA);
		this->energy = std::min(this->energy - AnimalConstants::DEER_CONSUME_ENERGY_RATIO, 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::min(this->stamina - AnimalConstants::DEER_CONSUME_STAMINA_RATIO, AnimalConstants::DEER_MIN_STAMINA);
	}

}

void Deer::Update()
{
	this->age_int += 1;

	Deer::Move();
}

void Deer::Mutate()
{
	return;
}

void Deer::Breed()
{
	return;
}

bool Deer::Eat(Animal& other)
{
	if (Species::Grass == other.GetSpecies())
	{	
		this->energy += other.GetEnergy() * AnimalConstants::DEER_ENERGY_TRANSFORMATION_RATIO;
		return true;
	}
	else
	{
		return false;
	}
}

