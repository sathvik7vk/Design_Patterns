//Below Singleton implementation has two static GetInstance methods : GetInstanceObject() and GetInstancePointer().
//GetInstanceObject() is C++ thread safe coding.

//KeyConcepts
/*
1. Private constructor – to prevent external instantiation. 
2. Private static instance pointer – to hold the single instance.
3. Public static function – to get the single instance.
4. Deleted copy constructor & assignment operator – to prevent copying.
*/



#include<iostream>
using namespace std;

class Singleton
{
private:
	Singleton() {}
	Singleton(const Singleton& other) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* instance;
public:
	~Singleton(){ }

	//C++11 thread safe method - Preferred 
	static Singleton& GetInstanceObject()
	{
		//This uses a function-local static object.
		//It's constructed once per program lifetime, and stored in static memory, handled automatically by the runtime.
		static Singleton obj;
		return obj;
	}


	static Singleton* GetInstancePointer()
	{
		//This uses a manually allocated (heap) object.
		//It is created and stored in a separate static pointer.
		if (instance == nullptr)
			instance =  new Singleton();

		return instance;
	}

	void Print()
	{
		cout << "Method called" << endl;
	}
};

Singleton* Singleton::instance = nullptr;

int main()
{
	Singleton& obj = Singleton::GetInstanceObject();
	obj.Print();

	Singleton* ptr = Singleton::GetInstancePointer();
	ptr->Print();

	cout << (&obj == ptr ? "Same" : "Different") << endl;	//They are different. You are creating two completely 
															//separate Singleton instances, because the two GetInstance methods manage 
															// their own storage independently:
	
	return 0;
}