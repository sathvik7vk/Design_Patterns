/*
The Prototype Design Pattern is one of the creational design patterns, and its main idea is:
	Instead of creating objects from scratch using new, create a copy (clone) of an existing object.

Why Prototype Pattern?
	1.Performance: If creating an object from scratch is expensive (e.g., involves complex initialization, reading from DB, or heavy computation), cloning an already prepared instance can be faster.
	2.Flexibility: You can create new objects without knowing their exact class type at runtime.
	3.Avoid subclass explosion: Instead of multiple constructors with lots of parameters, you can clone and modify.

Core Concepts
	1.Prototype Interface – Declares a clone() method.
	2.Concrete Prototypes – Implement the clone() method to return a copy of themselves.
	3.Client – Uses the prototype to create new objects without knowing the concrete class.

Where CAD Systems Use the Prototype Pattern
	1.Creating new geometry from existing templates
	2.Parametric feature cloning - In parametric modeling, features (extrusions, fillets, holes, chamfers, etc.) have a definition and an instance.
	3.Assembly part replication - In assembly design, if you place multiple copies of the same part (e.g., 200 identical screws), the CAD system often:
	4.UI tools for quick duplication - In tools like AutoCAD or SolidWorks, the “Mirror,” “Pattern,” “Copy,” or “Paste” commands often use an internal object cloning mechanism that mirrors the Prototype concept.


*/

#include<iostream>
#include<string>

using namespace std;

class CADShape
{
public:
	CADShape(){ }
	virtual ~CADShape(){ }

	//clone method
	virtual CADShape* clone() = 0;

	virtual void showInfo() = 0;
};

class Bolt :public CADShape
{
private:
	int size;
	string material;

public:
	//Constructor
	Bolt(int s, string m):size(s), material(m){ }
	~Bolt(){ }

	//Copy constructor
	Bolt(Bolt& other)
	{
		size = other.size;
		material = other.material;
	}
	void showInfo() { cout << "Bolt with material " << material << " and size " << size << endl; }

	//clone implementation
	CADShape* clone() override { return new Bolt(*this); }

};

class Nut :public CADShape
{
private:
	int size;
	string material;

public:
	//Constructor
	Nut(int s, string m) :size(s), material(m) {}
	~Nut() {}

	//Copy constructor
	Nut(Nut& other)
	{
		size = other.size;
		material = other.material;
	}
	void showInfo() { cout << "Nut with material " << material << " and size " << size << endl; }

	//Clone implementation
	CADShape* clone() override { return new Nut(*this); }

};

int main()
{

	Bolt bolt(10, "steel");
	Nut nut(8, "brass");

	CADShape* bolt1 = bolt.clone();
	CADShape* nut1 = nut.clone();

	CADShape* bolt2 = bolt.clone();
	CADShape* nut2 = nut.clone();

	bolt1->showInfo();
	nut1->showInfo();
	bolt2->showInfo();
	nut2->showInfo();

	delete bolt1;
	delete nut1;
	delete bolt2;
	delete nut2;

	return 0;
}