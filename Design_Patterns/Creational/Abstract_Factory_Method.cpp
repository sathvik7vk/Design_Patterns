#include<iostream>
using namespace std;

class Car
{
private:

public:
	Car() {}
	~Car() {}
	virtual void Run() = 0;
};

class PetrolCar :public Car
{
private:

public:
	PetrolCar() {}
	~PetrolCar() {}
	void Run() { cout << "Running using petrol" << endl; }
};

class DieselCar :public Car
{
private:

public:
	DieselCar() {}
	~DieselCar() {}
	void Run() { cout << "Running using diesel" << endl; }
};

class ElectricCar :public Car
{
private:

public:
	ElectricCar() {}
	~ElectricCar() {}
	void Run() { cout << "Running using battery" << endl; }
};

class Engine
{
private:

public:
	Engine(){ }
	virtual ~Engine(){ }
	virtual void startEngine() = 0;
};

class PetrolEngine :public Engine
{
public:
	PetrolEngine(){}
	~PetrolEngine(){ }

	void startEngine() { cout << "Petrol engine started" << endl; }
};

class DieselEngine :public Engine
{
public:
	DieselEngine() {}
	~DieselEngine() {}

	void startEngine() { cout << "Diesel engine started" << endl; }
};

class ElectricEngine :public Engine
{
public:
	ElectricEngine() {}
	~ElectricEngine() {}

	void startEngine() { cout << "Electric engine started" << endl; }
};


class CarFactory
{
private:
public:
	CarFactory() {}
	~CarFactory() {}
	virtual Car* createCar() = 0;
	virtual Engine* createEngine() = 0;
};

class PetrolCarFactory :public CarFactory
{
private:
public:
	PetrolCarFactory() {}
	~PetrolCarFactory() {}
	Car* createCar() { Car* newCar = new PetrolCar(); return newCar; }
	Engine* createEngine() { Engine* newEngine = new PetrolEngine(); return newEngine; }
};

class DieselCarFactory :public CarFactory
{
private:
public:
	DieselCarFactory() {}
	~DieselCarFactory() {}
	Car* createCar() { Car* newCar = new DieselCar(); return newCar; }
	Engine* createEngine() { Engine* newEngine = new DieselEngine(); return newEngine; }
};

class ElectricCarFactory :public CarFactory
{
private:
public:
	ElectricCarFactory() {}
	~ElectricCarFactory() {}
	Car* createCar() { Car* newCar = new ElectricCar(); return newCar; }
	Engine* createEngine() { Engine* newEngine = new ElectricEngine(); return newEngine; }
};


int main()
{
	CarFactory* pCarFactory = new ElectricCarFactory();
	Car* pCar = pCarFactory->createCar();
	Engine* pEngine = pCarFactory->createEngine();
	pCar->Run();
	pEngine->startEngine();
	delete pCarFactory;
	delete pCar;
	delete pEngine;
	return 0;
}
