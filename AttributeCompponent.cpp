#include "PreCompile.h"
#include "AttributeCompponent.h"

//Constructor/Destructor

AttributeCompponent::AttributeCompponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeCompponent::~AttributeCompponent()
{
}

//Functions

void AttributeCompponent::updateStats(const bool reset)
{
	this->hpMax		= this->vitality * 5 + this->vitality + this->strength + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->accuracy	= this->dexterity * 5 + this->dexterity / 3 + this->intelligence / 5;
	this->defence	= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck		= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeCompponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
		++this->attributePoints;
	}
}

void AttributeCompponent::gainExp(const unsigned exp)
{
	this->exp += exp;
	this->updateLevel();
}

void AttributeCompponent::update()
{
	this->updateLevel();
}

std::string AttributeCompponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
	<< "Attp: " << this->attributePoints << "\n";
	return ss.str();
}
