#include <iostream>
#include <vector>
class Character
{
public:
	const char* name = "";
	double damage_points = 0;
	double health_points = 0;
	virtual Character* clone() const
	{
		return new Character(*this);
	}
	virtual ~Character() = default;
	virtual void deal_damage_to(Character& other) const
	{
		other.health_points -= this->damage_points;
	}
	virtual void take_damage(double points)
	{
		this->health_points -= points;
	}
	virtual void heal(double points)
	{
		this->health_points += points;
	}
	bool compare_name(const char* name) const
	{
		if (strlen(name) == strlen(this->name))
		{
			for (int i = 0; i < strlen(name); i++)
			{
				if (this->name[i] != name[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	virtual void print() const
	{
		std::cout << "Name: { " << this->name << " }";
		std::cout << "Type: { " << this->clone() << " }";
		std::cout << "HP: { " << this->health_points << " }";
		std::cout << "DMG: { " << this->damage_points << " }";
	}
};

class Knight :public Character
{
private:
	char* squireName;
public:
	Knight* clone() const override
	{
		return new Knight(*this);
	}
	void take_damage(double points) override
	{
		this->health_points -= points * 0.75;
	}
	void heal(double points) override
	{
		this->health_points += points * 1.05;
	}
	void print() const override
	{
		std::cout << "Name: { " << this->name << " }";
		std::cout << "Type: { " << "Knight and the squireName: " << this->squireName << " }";
		std::cout << "HP: { " << this->health_points << " }";
		std::cout << "DMG: { " << this->damage_points << " }";
	}
};

class Archer :public Character
{
public:
	Archer* clone() const override
	{
		return new Archer(*this);
	}
	void deal_damage_to(Character& other) const override
	{
		other.health_points -= this->damage_points * 1.33;
	}
	void take_damage(double points) override
	{
		this->health_points -= points * 1.15;
	}
	void print() const override
	{
		std::cout << "Name: { " << this->name << " }";
		std::cout << "Type: { " << "Archer " << " }";
		std::cout << "HP: { " << this->health_points << " }";
		std::cout << "DMG: { " << this->damage_points << " }";
	}
};
bool Consists(std::vector<Character> players, const char* name)
{
	for (Character ch : players)
	{
		if (ch.name == name)
		{
			return true;
		}
	}
	return false;
}

class Game
{
public:
	std::vector<Character> players;
	void add(const Character& character)
	{
		players.push_back(character);
	}
	void battle(const char* _attacker, const char* _target)
	{
		if (Consists(players, _attacker) && Consists(players, _target))
		{
			Character attacker;
			Character target;
			for (Character ch : players)
			{
				if (ch.name == _attacker)
				{
					attacker = ch;
				}
				if (ch.name == _target)
				{
					target = ch;
				}
			}
			attacker.deal_damage_to(target);
			if (target.health_points < 0)
			{
				auto it = std::find(players.begin(), players.end(),
					target);
				players.erase(it);
			}
		}
		else
		{
			std::cout << "The name doesn't exist";
		}
	}
	void heal(double amount)
	{
		for (Character ch : players)
		{
			ch.health_points += amount;
		}
	}
	void print() const
	{
		for (Character ch : players)
		{
			ch.print();
		}
	}
};

int main()
{
}