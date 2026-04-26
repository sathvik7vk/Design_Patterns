//Bridge design pattern example in C++
/* ****************************************************************************************
 * Bridge Design Pattern (Structural Pattern)
 *
 * Intent:
 * --------
 * The Bridge pattern decouples an abstraction from its implementation so that the two
 * can vary independently. It is used to separate a class's interface from its implementation,
 * allowing both to evolve separately without affecting each other.
 * Problem Solved:
 * ----------------
 * - Tight coupling between abstraction and implementation.
 * - Difficulty in extending both abstraction and implementation independently.
 * Solution:
 * ----------
 * - Define an abstraction interface and an implementation interface.
 * - Create concrete implementations of the implementation interface.
 * - Create refined abstractions that use the implementation interface.
 * Example Mapping in this program:
 * --------------------------------
 * - Abstraction         : Shape
 * - Refined Abstraction : Circle, Square
 * - Implementor        : DrawingAPI 

 * Bridge achieves this by:
    -   Using composition over inheritance
    -   Depending on interfaces instead of concrete classes
    -   Allowing both hierarchies to vary independently
 
 */

#include <iostream>
#include <memory>

using namespace std;

class IEngine
{
    public:
    virtual void startEngine() = 0;
    virtual ~IEngine(){}
};

class ElectricEngine : public IEngine
{
    public:
    void startEngine(){ cout<<"Started electric engine"<<endl;}
};

class PetrolEngine : public IEngine
{
    public:
    void startEngine(){ cout<<"Started petrol engine"<<endl;}
};

class DieselEngine : public IEngine
{
    public:
    void startEngine(){ cout<<"Started diesel engine"<<endl;}
};


class IVehicle
{
    public:
    std::unique_ptr<IEngine> spEngine;

    public:
    IVehicle(std::unique_ptr<IEngine> pEngine):spEngine(std::move(pEngine)) { }
    virtual void driveVehicle() =0;
    virtual ~IVehicle(){};
};


class Car:public IVehicle
{
    public:
    Car(std::unique_ptr<IEngine> pEngine):IVehicle(std::move(pEngine)){}
    ~Car(){}

    void driveVehicle()
    {
        spEngine->startEngine();
        cout<<"Driving the car"<<endl;
    }
};

class Truck:public IVehicle
{
    public:
    Truck(std::unique_ptr<IEngine> pEngine):IVehicle(std::move(pEngine)){}
    ~Truck(){}

    void driveVehicle()
    {
         spEngine->startEngine();
         cout<<"Driving the truck"<<endl;
    }
};


int main()
{
    std::unique_ptr<IVehicle> pVehicle = std::make_unique<Car>(std::make_unique<PetrolEngine>());
    pVehicle->driveVehicle();

    std::unique_ptr<IVehicle> pVehicle2 = std::make_unique<Truck>(std::make_unique<ElectricEngine>());
    pVehicle2->driveVehicle();

    return 0;
}