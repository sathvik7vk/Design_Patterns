//Implementation for composite pattern
/*
The Composite Design Pattern is a structural pattern used to treat individual objects and compositions of objects uniformly. Think of it like a file system: a File is an individual object, and a Folder is a composition that can contain both Files and other Folders.

From a C++ perspective, this pattern relies heavily on polymorphism and recursion.

Key Components
Component (Interface/Abstract Class): Declares the interface for all objects in the composition.

Leaf: Represents the "primitive" objects that have no children (e.g., a File).

Composite: Stores child components and implements child-related operations (e.g., a Folder).
*/


#include<iostream>
#include<string>
#include<vector>
#include<memory>

using namespace std;

class Employee
{
    private:

    protected:
    std::string name;
    std::string position;
    double salary;

    public:
    Employee(const std::string &iName, const std::string &iPosition) : name(iName), position(iPosition), salary(0.0) {}
    virtual ~Employee()=default;
    virtual void ShowDetails() = 0;
    virtual void SetSalary(double) = 0;
    virtual double GetSalary() = 0;
};

class Developer :public Employee
{
private:


public:

    Developer(const std::string &iName, const std::string &iPosition) :Employee(iName, iPosition){}

    void SetSalary(double iSalary) override { salary = iSalary;}

    void ShowDetails() override{ cout << "Name = " << name << "  Position = " << position << endl;}

    double GetSalary() override{ return salary; }
};

class Manager :public Employee
{
private:
    std::vector<std::unique_ptr<Employee>> listOfEmployees;

public:

    Manager(const std::string &iName, const std::string &iPosition) :Employee(iName, iPosition){}

    void AddEmployee(std::unique_ptr<Employee> emp){listOfEmployees.push_back(std::move(emp));}

    void SetSalary(double iSalary) override 
    { 
        salary = iSalary;
    }

    void ShowDetails() override{
        for(const auto& emp : listOfEmployees)
            emp->ShowDetails();}

    double GetSalary() override{ 
        double totalSalary = 0;
        for(const auto& emp : listOfEmployees)
            totalSalary +=emp->GetSalary();
        return totalSalary; }
};

int main()
{
    std::unique_ptr<Manager> manager = std::make_unique<Manager>("Alice", "Project Manager");
    manager->SetSalary(100000);
    std::unique_ptr<Employee> dev1 = std::make_unique<Developer>("Bob", "Software Developer");
    dev1->SetSalary(80000);
    std::unique_ptr<Employee> dev2 = std::make_unique<Developer>("Charlie", "Software Developer");
    dev2->SetSalary(85000);
    manager->AddEmployee(std::move(dev1));
    manager->AddEmployee(std::move(dev2));
    cout << "Manager Details: " << endl;
    manager->ShowDetails();
    cout << "Total Salary: " << manager->GetSalary() << endl;

    return 0;
}