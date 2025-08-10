
#include <iostream>
using namespace std;

// ==========================
// PRODUCT CLASS
// ==========================

// Represents the complex object we want to build
class Car
{
public:
    string engine;
    string body;
    string seats;

    void setEngine(string eng) { engine = eng; }
    void setBody(string bod) { body = bod; }
    void setSeats(string seat) { seats = seat; }

    // Display final car details
    void ShowCar()
    {
        cout << "The car is " << body
            << " having engine " << engine
            << " and has " << seats << endl;
    }
};

// ==========================
// BUILDER INTERFACE
// ==========================

// Defines the abstract steps required to build a Car
class CarBuilder
{
protected:
    Car* car; // Product being built

public:
    virtual ~CarBuilder() {} // Virtual destructor for safe cleanup

    // Pure virtual functions for each step
    virtual void createCarEngine() = 0;
    virtual void createCarBody() = 0;
    virtual void createCarSeats() = 0;

    // Return the built product
    virtual Car* getCar() = 0;
};

// ==========================
// CONCRETE BUILDER: Sports Car
// ==========================

class SportsCarBuilder : public CarBuilder
{
public:
    SportsCarBuilder()
    {
        car = new Car(); // Start building a fresh car
    }

    ~SportsCarBuilder() {}

    void createCarEngine() override
    {
        car->setEngine("Sports car engine");
    }
    void createCarBody() override
    {
        car->setBody("Sports car body");
    }
    void createCarSeats() override
    {
        car->setSeats("2 seats");
    }

    Car* getCar() override
    {
        return car;
    }
};

// ==========================
// CONCRETE BUILDER: SUV
// ==========================

class SUVCarBuilder : public CarBuilder
{
public:
    SUVCarBuilder()
    {
        car = new Car(); // Start building a fresh car
    }

    ~SUVCarBuilder() {}

    void createCarEngine() override
    {
        car->setEngine("SUV car engine");
    }
    void createCarBody() override
    {
        car->setBody("SUV car body");
    }
    void createCarSeats() override
    {
        car->setSeats("5 seats");
    }

    Car* getCar() override
    {
        return car;
    }
};

// ==========================
// DIRECTOR CLASS
// ==========================

// Orchestrates the building steps in a fixed sequence
class Director
{
private:
    CarBuilder* pBuilder; // Pointer to builder interface

public:
    // Director is initialized with a specific Builder
    Director(CarBuilder* ipBuilder) : pBuilder(ipBuilder) {}

    // Creates the product by calling builder steps
    Car* CreateCar()
    {
        pBuilder->createCarBody();
        pBuilder->createCarEngine();
        pBuilder->createCarSeats();
        return pBuilder->getCar();
    }
};

// ==========================
// MAIN FUNCTION
// ==========================

int main()
{
    // Step 1: Choose a concrete builder
    CarBuilder* pBuilder = new SUVCarBuilder();

    // Step 2: Pass it to the Director
    Director director(pBuilder);

    // Step 3: Build the product
    Car* pCar = director.CreateCar();

    // Step 4: Display the final product
    pCar->ShowCar();

    // Cleanup
    delete pCar;
    delete pBuilder;

    return 0;
}




//#include<iostream>
//using namespace std;
//
//class Car
//{
//public:
//	string engine;
//	string body;
//	string seats;
//
//	void setEngine(string eng) { engine = eng; }
//	void setBody(string bod) { body = bod; }
//	void setSeats(string seat) { seats = seat; }
//
//	void ShowCar() { cout << "The car is " << body << " " << "having engine " << engine << " has " << seats << endl; }
//};
//
//class CarBuilder
//{
//protected:
//	Car* car;
//public:
//	virtual ~CarBuilder() = 0;
//	virtual void createCarEngine() = 0;
//	virtual void createCarBody() = 0;
//	virtual void createCarSeats() = 0;
//
//	virtual Car* getCar() = 0;
//};
//
//class SportsCarBuilder :public CarBuilder
//{
//
//public:
//	SportsCarBuilder() { car = new Car(); }
//	~SportsCarBuilder(){ }
//
//	void createCarEngine()
//	{
//		car->setEngine("Sports car engine");
//	}
//	void createCarBody()
//	{
//		car->setBody("Sports car body");
//	}
//	void createCarSeats()
//	{
//		car->setSeats("2 seats");
//	}
//
//	Car* getCar() { return car; }
//};
//
//class SUVCarBuilder :public CarBuilder
//{
//private:
//	//Car* car;
//
//public:
//	SUVCarBuilder() { car = new Car(); }
//	~SUVCarBuilder() {}
//
//	void createCarEngine()
//	{
//		car->setEngine("SUV car engine");
//	}
//	void createCarBody()
//	{
//		car->setBody("SUV car body");
//	}
//	void createCarSeats()
//	{
//		car->setSeats("5 seats");
//	}
//
//	Car* getCar() { return car; }
//};
//
//class Director
//{
//private:
//	CarBuilder* pBuilder;
//public:
//	Director(CarBuilder* ipBuilder):pBuilder(ipBuilder){ }
//	Car* CreateCar()
//	{
//		pBuilder->createCarBody();
//		pBuilder->createCarEngine();
//		pBuilder->createCarSeats();
//		return pBuilder->getCar();
//	}
//};
//
//
//int main()
//{
//	CarBuilder* pBuilder = new SUVCarBuilder();
//
//	Director director(pBuilder);
//
//	Car* pCar = director.CreateCar();
//
//	pCar->ShowCar();
//
//
//	return 0;
//}