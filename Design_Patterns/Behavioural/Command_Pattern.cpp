/*
The Command Design Pattern is a behavioral design pattern that turns a request into a stand-alone 
object containing all information about the request.

Think of it like a waiter in a restaurant. You (the Client) give your order to the waiter (the Invoker). 
The waiter writes it down on a pad (the Command). This piece of paper is passed to the chef (the Receiver), who
actually cooks the meal. The waiter doesn't need to know how to cook; they just need to pass the paper to the 
right person.

-------------------------------------------------------------------------------------------------------
Conceptual Architecture
The pattern decouples the object that invokes the operation from the one that knows how to execute it.

Command: An interface that declares a method (usually execute()) for executing an operation.

Concrete Command: Implements execute() by invoking the corresponding operation(s) on the Receiver.

Receiver: Knows how to perform the actual work/business logic.

Invoker: Asks the command to carry out the request (e.g., a button or a menu).

Client: Creates a Concrete Command object and sets its Receiver.

------------------------------------------------------------------------------------------------------


Question: The above example is not very clear to me. There is a light which has two methods to turn it On 
and Off. We are using a command to operate these actions. why cant we just have a pointer to this class object and call On and Off?

Answer:
That is a incredibly fair question. In fact, it's the exact hurdle everyone hits when they first see this pattern.

If your program only ever needs to turn a light on and off, you are 100% correct: creating all these command classes is completely over-engineered. A direct pointer like light->turnOn() is faster, simpler, and cleaner.

The value of the Command Pattern only becomes obvious when you look at it from the perspective of the Invoker (the Remote Control or UI Button) and how your system needs to scale over time.

Here is exactly why a direct pointer falls short in complex systems:
1. The Invoker Shouldn't Know Who It's Talking To
Imagine you are designing a generic GUI framework with a Button class.

If you use direct pointers, your button needs to know exactly what class it is controlling.

Button A has a Light* pointer.

Button B has a Stereo* pointer.

Button C has a Thermostat* pointer.

Suddenly, your Button class is no longer a generic, reusable UI component. Every time you invent a new appliance, you have to modify the Button code to support that new pointer type.

With the Command Pattern, the Button only ever holds a pointer to the abstract Command interface. The button doesn't know—and doesn't care—if it's turning on a light, launching a rocket, or saving a file. It just calls command->execute().

2. Setting Up "Time-Travel" (Undo/Redo)
If your button just calls light->turnOn(), how do you implement a universal "Undo" button?

The remote control would have to keep track of every type of object it interacted with, what state it was in previously, and what function reverses it.

By wrapping the action in an object, the command carries its own reversal logic (undo()). The remote control only needs a history stack of Command pointers.


*/


#include<iostream>
#include<memory>
#include<stack>

using namespace std;

class Light
{
    private:

    public:
    Light(){}
    void turnLightOn(){cout<<"Light is turned On"<<endl;}
    void turnLightOff(){cout<<"Light is turned Off"<<endl;}
    ~Light(){}
};

class Command
{
    public:
    ~Command(){}
    virtual void execute() = 0;
    virtual void Undo() = 0;
};

//Turn On command
class TurnOnCommand:public Command
{
    private:
    std::shared_ptr<Light> m_light;

    public: 
    TurnOnCommand(std::shared_ptr<Light>& light):m_light(light){} 
    void execute()
    {
        if(m_light != nullptr)
            m_light->turnLightOn();
    }

    void Undo()
    {
        if(m_light != nullptr)
            m_light->turnLightOff();
    }
};

//Turn off command
class TurnOffCommand:public Command
{
    private:
    std::shared_ptr<Light> m_light;

    public:
    TurnOffCommand(std::shared_ptr<Light>& light):m_light(light){} 
    void execute()
    {
        if(m_light != nullptr)
            m_light->turnLightOff();
    }

    void Undo()
    {
        if(m_light != nullptr)
            m_light->turnLightOn();
    }
};

//Invoker
class Button
{
    private:
    std::shared_ptr<Command> m_command;
    std::stack<std::shared_ptr<Command>> m_CommandStack;

    
    public:
    Button(){}
    Button(const std::shared_ptr<Command>& cmd):m_command(cmd){}

    void SetCommand(const std::shared_ptr<Command>& cmd)
    {
        m_command = cmd;
    }

    void OnButtonClick()
    {
        if (m_command != nullptr)
        {
            m_command->execute();
            m_CommandStack.push(m_command);
        }
    }

    void ClickUndo()
    {
        if(!m_CommandStack.empty())
        {
            m_CommandStack.top()->Undo();
            m_CommandStack.pop();
        }
        else
        {
            cout<<"Nothing to undo"<<endl;
        }
    }

};

int main()
{
    // 1. Create the Receiver
    auto livingRoomLight = std::make_shared<Light>();

    // 2. Create the Commands
    auto lightOn = std::make_shared<TurnOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<TurnOffCommand>(livingRoomLight);

    //Create the invoker
    Button btn;
    btn.SetCommand(lightOn);
    btn.OnButtonClick();
    btn.SetCommand(lightOff);
    btn.OnButtonClick();

    btn.ClickUndo();
    btn.ClickUndo();
    btn.ClickUndo();

    return 0;
}