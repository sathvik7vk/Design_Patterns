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
	PetrolCar(){}
	~PetrolCar(){}
	void Run() { cout << "Running using petrol" << endl; }
};

class DieselCar :public Car
{
private:

public:
	DieselCar(){}
	~DieselCar(){}
	void Run() { cout << "Running using diesel" << endl; }
};

class ElectricCar :public Car
{
private:

public:
	ElectricCar(){}
	~ElectricCar(){ }
	void Run() { cout << "Running using battery" << endl; }
};

class CarFactory
{
private:
public:
	CarFactory(){ }
	~CarFactory(){ }
	virtual Car* createCar() = 0;
};

class PetrolCarFactory :public CarFactory
{
private:
public:
	PetrolCarFactory(){ }
	~PetrolCarFactory(){ }
	Car* createCar() { Car* newCar = new PetrolCar(); return newCar; }
};

class DieselCarFactory :public CarFactory
{
private:
public:
	DieselCarFactory(){}
	~DieselCarFactory(){ }
	Car* createCar() { Car* newCar = new DieselCar(); return newCar; }
};

class ElectricCarFactory :public CarFactory
{
private:
public:
	ElectricCarFactory(){}
	~ElectricCarFactory(){ }
	Car* createCar() { Car* newCar = new ElectricCar(); return newCar; }
};


int main()
{
	CarFactory* pCarFactory = new ElectricCarFactory();
	Car* pCar = pCarFactory->createCar();
	pCar->Run();
	delete pCarFactory;
	delete pCar;
	return 0;
}
