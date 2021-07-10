#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeCompponent
{
private:
public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	//Atributes
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Constructor/Destructor
	AttributeCompponent(unsigned level);
	virtual ~AttributeCompponent();

	//Functions
	void updateStats(const bool reset);
	void updateLevel();

	void gainExp(const unsigned exp);

	void update();

	std::string debugPrint() const;
};

#endif // !ATTRIBUTECOMPONENT_H
