//Chain of responsibility

/*
* It allows you to pass request along a set of handlers.
* Upon receiving a request, each handler decides either to process the request or 
    to pass it to the next handler in the chain.

* How It Works
    The pattern organizes a set of objects (handlers) into a linear chain. 
    When a request enters the chain:

    1. Handler A checks if it can process the request.
    2. If yes, it performs the action. Depending on the implementation, it might stop there or pass it along anyway.
    3. If no, it forwards the request to Handler B.
    4. The process continues until the request is handled or it reaches the end of the chain.

*Key Components
    1. Handler Interface: Defines the method for executing the request and, optionally, for setting the next handler in the line.
    2. Base Handler: An optional class where you can put the boilerplate code for linking handlers together.
    3. Concrete Handlers: These contain the actual logic to process requests. If they can't handle a specific request, they delegate to the successor.
    4. Client: The component that composes the chain and initiates the request to the first handler.

* When to Use It
    1. Multiple candidates: When more than one object may handle a request, and the handler isn't known a priori.
    2. Dynamic chains: When the set of objects that can handle a request should be specified dynamically (at runtime).
    3. Sequential processing: When you need to execute several handlers in a particular order.

*Real-World Examples
1. Technical Support
Think of a multi-level support system.
Level 1 handles basic password resets. If the issue is a bug, they pass it to Level 2.
Level 2 handles configuration issues. If it's a deep code flaw, they pass it to Level 3 (Developers).

2. UI Event Bubbling
In many GUI frameworks, if you click a button and the button doesn't have a click listener, the event "bubbles up" to its parent container (like a Panel), then to the Frame, and finally to the Window until something handles the click.
*/

#include<iostream>
#include<string>
#include<sstream>

class StringValidatorHandler
{
    private:

    public:
    virtual ~StringValidatorHandler() = default;

    virtual void SetNext(StringValidatorHandler* ptrStringValidatorHandler) = 0;
    virtual std::string Validate(const std::string&  str) = 0;
};


class BaseValidatorHandler : public StringValidatorHandler
{
    private:
    StringValidatorHandler* next = NULL;

    public:

    void SetNext(StringValidatorHandler* ptrStringValidatorHandler)
    {
        next = ptrStringValidatorHandler;
    }

    std::string Validate(const std::string& str) override
    {
        if(this->next)
        {
            return this->next->Validate(str);
        }
        return "SUCCESS!";
    }

};

class NonEmptyValidator:public BaseValidatorHandler
{
    private:

    public:
    std::string Validate(const std::string& str) override
    {
        if(str.empty())
        {
            return "Empty string. Please enter some value";
        }
        return BaseValidatorHandler::Validate(str);
    }

};

class LongStringValidator:public BaseValidatorHandler
{
    private:
    const int max_size = 16;

    public:
    std::string Validate(const std::string& str) override
    {
        if(str.size()>=max_size)
        {
            return "Too long string!";
        }
        return BaseValidatorHandler::Validate(str);
    }

};

int main()
{
    StringValidatorHandler* mainHandler = new BaseValidatorHandler();

    NonEmptyValidator* nonEmptyString = new NonEmptyValidator();

    LongStringValidator* longString = new LongStringValidator();

    mainHandler->SetNext(nonEmptyString);
    nonEmptyString->SetNext(longString);

    //Case1
    std::string output = mainHandler->Validate("Sathvik");
    std::cout<<output;
    std::cout<<std::endl;

    //Case2
    output = mainHandler->Validate("");
    std::cout<<output;
    std::cout<<std::endl;

    //Case 3
    output = mainHandler->Validate("Sathvik Nayak Halli Sadananda Kokkarne");
    std::cout<<output;
    std::cout<<std::endl;




    return 0;
}



