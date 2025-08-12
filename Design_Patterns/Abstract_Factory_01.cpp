#include<iostream>
using namespace std;



class Engine
{
public:
	Engine(){}
	~Engine(){ }
	virtual void startEngine() = 0;
};

class ElectricEngine :public Engine
{
public:
	ElectricEngine(){}
	~ElectricEngine(){}
	void startEngine() { cout << "Electric engine starts" << endl; }
};

class PetrolEngine :public Engine
{
public:
	PetrolEngine() {}
	virtual ~PetrolEngine() {}
	void startEngine() { cout << "Petrol engine starts" << endl; }
};

class Fuel
{
public:
	Fuel(){ }
	virtual ~Fuel(){ }
	virtual void supplyFuel() = 0;
};

class ElectricFuel :public Fuel
{
public:
	ElectricFuel(){ }
	~ElectricFuel(){ }
	void supplyFuel() { cout << "Supply electric charges to engine" << endl; }
};

class PetrolFuel :public Fuel
{
public:
	PetrolFuel() {}
	~PetrolFuel() {}
	void supplyFuel() { cout << "Supply petrol to engine" << endl; }
};

class Car
{
protected:
	Engine* pEngine;
	Fuel* pFuel;
public:
	Car(Engine* pEng, Fuel* pFul): pEngine(pEng), pFuel(pFul){}
	virtual ~Car() {}

	virtual void showCar() = 0;

	void runCar() { pEngine->startEngine(); pFuel->supplyFuel(); }
};

class ElectricCar :public Car
{
public:
	ElectricCar(Engine* pEng, Fuel* pFul) : Car(pEng, pFul) {  }
	virtual ~ElectricCar() {}

	void showCar() { cout << "Electric car display" << endl; }
};

class PetrolCar :public Car
{
public:
	PetrolCar(Engine* pEng, Fuel* pFul) :Car(pEng, pFul) {  }
	virtual ~PetrolCar() {}

	void showCar() { cout << "Petrol car display" << endl; }
};


class CarFactory
{
protected:
	Car* pCar;
public:
	CarFactory() {}
	virtual ~CarFactory() {}

	virtual Car* createCar() = 0;
};

class ElectricCarFactory:public CarFactory
{
public:
	ElectricCarFactory(){ }
	~ElectricCarFactory(){ }
	Car* createCar() { pCar = new ElectricCar(new ElectricEngine(), new ElectricFuel()); return pCar; }
};

class PetrolCarFactory :public CarFactory
{
public:
	PetrolCarFactory() {}
	~PetrolCarFactory() {}
	Car* createCar() { pCar = new PetrolCar(new PetrolEngine(), new PetrolFuel()); return pCar; }
};

int main()
{
	CarFactory* _pFactory = new ElectricCarFactory();

	Car* pCar = _pFactory->createCar();
	pCar->runCar();
	pCar->showCar();

	delete pCar;
	delete _pFactory;

	return 0;
}