/*
Imagine a busy airport. If every single airplane had to communicate directly with every other airplane to 
coordinate takeoffs and landings, the sky would be absolute chaos. A pilot would have to talk to dozens of 
other pilots just to change altitude.

Instead, every airplane communicates with a single central hub: the Air Traffic Control (ATC) tower. 
The tower handles the complex coordination, routes messages, and ensures order.

In software architecture, the Mediator Design Pattern is that ATC tower. It is a behavioral design pattern 
that reduces chaotic dependencies between objects by forcing them to communicate exclusively through a central 
mediator object, rather than directly with each other.

---------------------------------------------------------------------------

The Problem: Tight Coupling (The Spaghetti Web)
As software grows, you often end up with a network of objects that all need to know about each other's 
state changes. For example, in a complex UI dialog:

Checking a "Ship to different address" Checkbox must enable a hidden Form.

Clearing the text in a TextField must disable the "Submit" Button.

Clicking the "Clear All" Button must reset the Checkbox and TextField.

If these components call each other's methods directly, they become tightly coupled. You cannot easily
 reuse the checkbox or text field in another part of your app because they are hardcoded to talk to specific 
 components.
-----------------------------------------------------------------------------

The Solution: Enter the Mediator
The Mediator pattern solves this by introducing a central authority. Individual components (called Colleagues) no
 longer talk to each other. Instead, they just notify the Mediator whenever an event occurs: "Hey, I just got 
 clicked."

The Mediator contains the routing logic and decides what happens next: "Got it. Since you were clicked, I will 
tell the TextField to clear and the Button to disable."

Key Benefits:
Loose Coupling: Components don't need to know anything about the existence of other components. 
They only need to know about the Mediator.

Single Responsibility Principle: The complex communication behavior is encapsulated in one place, 
making it easier to maintain and modify.

Component Reuse: Because components are decoupled, they can be easily plucked out and reused in a completely 
different UI or system architecture.

-------------------------------------------------------------------
Structure of the Mediator Pattern
The pattern typically relies on four main participants:

Mediator (Interface): Defines the communication contract (usually a single notify or send method) that components
 use to talk to it.

Concrete Mediator: Implements the interface and coordinates the actual components. It holds references to all
 the components it manages.

Colleague Classes (Components): The individual classes that perform business logic. They hold a reference to 
 the mediator interface and communicate with it whenever their state changes.

---------------------------------------------------------------------

Imagine a busy airport. If every single airplane had to communicate directly with every other airplane to coordinate takeoffs and landings, the sky would be absolute chaos. A pilot would have to talk to dozens of other pilots just to change altitude.

Instead, every airplane communicates with a single central hub: the Air Traffic Control (ATC) tower. The tower handles the complex coordination, routes messages, and ensures order.

In software architecture, the Mediator Design Pattern is that ATC tower. It is a behavioral design pattern that reduces chaotic dependencies between objects by forcing them to communicate exclusively through a central mediator object, rather than directly with each other.

The Problem: Tight Coupling (The Spaghetti Web)
As software grows, you often end up with a network of objects that all need to know about each other's state changes. For example, in a complex UI dialog:

Checking a "Ship to different address" Checkbox must enable a hidden Form.

Clearing the text in a TextField must disable the "Submit" Button.

Clicking the "Clear All" Button must reset the Checkbox and TextField.

If these components call each other's methods directly, they become tightly coupled. You cannot easily reuse the checkbox or text field in another part of your app because they are hardcoded to talk to specific components.

The Solution: Enter the Mediator
The Mediator pattern solves this by introducing a central authority. Individual components (called Colleagues) no longer talk to each other. Instead, they just notify the Mediator whenever an event occurs: "Hey, I just got clicked."

The Mediator contains the routing logic and decides what happens next: "Got it. Since you were clicked, I will tell the TextField to clear and the Button to disable."

Key Benefits:
Loose Coupling: Components don't need to know anything about the existence of other components. They only need to know about the Mediator.

Single Responsibility Principle: The complex communication behavior is encapsulated in one place, making it easier to maintain and modify.

Component Reuse: Because components are decoupled, they can be easily plucked out and reused in a completely different UI or system architecture.

Structure of the Mediator Pattern
The pattern typically relies on four main participants:

Mediator (Interface): Defines the communication contract (usually a single notify or send method) that components use to talk to it.

Concrete Mediator: Implements the interface and coordinates the actual components. It holds references to all the components it manages.

Colleague Classes (Components): The individual classes that perform business logic. They hold a reference to the mediator interface and communicate with it whenever their state changes.

Conceptual C++ Implementation
Here is a clean, standard way to implement a UI dialog box using the Mediator pattern in C++.

C++
#include <iostream>
#include <string>
#include <memory>

class Component;

// 1. The Mediator Interface
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(Component* sender, const std::string& event) = 0;
};

// 2. Base Component (Colleague)
class Component {
protected:
    Mediator* mediator; // Reference to the central coordinator

public:
    Component(Mediator* med = nullptr) : mediator(med) {}
    void set_mediator(Mediator* med) { mediator = med; }
};

// 3. Concrete Components
class Checkbox : public Component {
private:
    bool checked = false;

public:
    void check() {
        checked = !checked;
        std::cout << "Checkbox: State changed to " << (checked ? "Checked" : "Unchecked") << ".\n";
        if (mediator) {
            mediator->notify(this, "check_changed");
        }
    }
    bool is_checked() const { return checked; }
};

class TextField : public Component {
public:
    void clear() {
        std::cout << "TextField: Cleared content.\n";
    }
    void enable(bool state) {
        std::cout << "TextField: " << (state ? "Enabled" : "Disabled") << ".\n";
    }
};

class Button : public Component {
public:
    void disable() {
        std::cout << "Button: Disabled.\n";
    }
};

// 4. Concrete Mediator
class UI_Dialog : public Mediator {
private:
    Checkbox* checkbox;
    TextField* text_field;
    Button* submit_button;

public:
    UI_Dialog(Checkbox* cb, TextField* tf, Button* btn) 
        : checkbox(cb), text_field(tf), submit_button(btn) {
        // Set this mediator for all components
        checkbox->set_mediator(this);
        text_field->set_mediator(this);
        submit_button->set_mediator(this);
    }

    // Centralized routing logic
    void notify(Component* sender, const std::string& event) override {
        if (sender == checkbox && event == "check_changed") {
            if (checkbox->is_checked()) {
                text_field->enable(true);
            } else {
                text_field->clear();
                text_field->enable(false);
                submit_button->disable();
            }
        }
    }
};

// Client Code
int main() {
    Checkbox cb;
    TextField tf;
    Button btn;

    // The mediator wires everything together behind the scenes
    UI_Dialog dialog(&cb, &tf, &btn);

    // Simulating user interactions
    std::cout << "--- User checks the box ---\n";
    cb.check(); 

    std::cout << "\n--- User unchecks the box ---\n";
    cb.check(); 

    return 0;
}
When Should You Use It?
The Dependency Tangled Web: When your classes communicate in a complex, multi-directional "many-to-many" fashion,
 making the code hard to read and debug.

Hindered Reusability: When you realize a component cannot be reused elsewhere because it is explicitly tied to
 three other classes in its current environment.

Subclass Explosion: When you find yourself creating dozens of subclasses of a component just to customize
 its behavior in different contexts. Instead, you can keep the component clean and put the custom behavior
  inside a new Mediator subclass.

The Trade-off to Keep in Mind
While the Mediator pattern is fantastic for cleaning up scattered relationships, it comes with a major warning:
 The God Object Anti-Pattern.

Because the mediator consolidates all interaction logic, if you aren't careful, it can grow infinitely. It can 
easily turn into a massive, monolithic "God Object" that knows too much and becomes incredibly hard to maintain.
 If your mediator starts handling the actual business logic of the components rather than just routing messages 
 between them, it’s time to break it down.

*/

#include<iostream>
#include<memory>
#include<string>

using namespace std;

//forward declaration
class Component;
// class CheckBox;
// class TextBox;
// class SubmitButton;

//Mediator interface
class IMediator
{
    public:
    virtual ~IMediator(){}
    virtual void notify(const std::shared_ptr<Component>& ptrComponent, const std::string& str ) = 0;
};



//Base component class
class Component
{
    private:
    //std::shared_ptr<IMediator> mediatorPtr;
    std::weak_ptr<IMediator> mediatorPtr;

    public:
    Component(const std::shared_ptr<IMediator>& ptr = nullptr):mediatorPtr(ptr){}
    virtual ~Component() = default;
    void setMediator(const std::shared_ptr<IMediator>& ptr){mediatorPtr = ptr;}

    // Helper method for child classes to send notifications safely
    void notifyMediator(const std::shared_ptr<Component>& self, const std::string& event) {
        if (auto lockedMediator = mediatorPtr.lock()) {
            lockedMediator->notify(self, event);
        }
    }
};

//Colleague classes or other component classes 

// class CheckBox:public Component
// {
//     private:
//     bool checked = false;
//     public:
//     void check()
//     {
//         checked = !checked;
//         cout << "Checkbox state toggled." << endl;
    
//     // FIX: Trigger the notification pipeline using the passed pointer
//     //notifyMediator(self, "check_changed");
//     }
//     bool isChecked() const
//     {
//         return checked;
//     }
// };

// Update CheckBox definition:
class CheckBox : public Component, public std::enable_shared_from_this<CheckBox>
{
    private:
    bool checked = false;
    
    public:
    void check()
    {
        checked = !checked;
        cout << "Checkbox state toggled. Current: " << (checked ? "Checked" : "Unchecked") << endl;
        
        // FIX: Trigger the notification pipeline!
        notifyMediator(shared_from_this(), "check_changed");
    }
    
    bool isChecked() const { return checked; }
};

class TextBox:public Component
{
    private:

    public:
    void clear()
    {
        cout<<"Text box : is cleared"<<endl;
    }

    void Activate()
    {
        cout<<"Text box is activated"<<endl;
    }
};

class SubmitButton:public Component
{
    private:    
    bool enabled = false;
    public:
    void EnableButton(){enabled = true; cout<<"Submit button enabled"<<endl;}
    void DisbaleButton(){enabled = false; cout<<"Submit button disabled"<<endl;}
};

class Mediator:public IMediator, public std::enable_shared_from_this<Mediator>
{
    private:
    std::shared_ptr<CheckBox> cbPtr;
    std::shared_ptr<TextBox> tbPtr;
    std::shared_ptr<SubmitButton> sbPtr;

    public:
    Mediator(const std::shared_ptr<CheckBox>& cbP, const  std::shared_ptr<TextBox>& tbP, const std::shared_ptr<SubmitButton>& sbP ):
    cbPtr(cbP), tbPtr(tbP), sbPtr(sbP)
    {
    }
    // FIX 1 cont.: We wire them up right after the Mediator shared_ptr is instantiated
    void initialize() {
        // shared_from_this() safely creates a shared_ptr<IMediator> pointing to this object
        cbPtr->setMediator(shared_from_this());
        tbPtr->setMediator(shared_from_this());
        sbPtr->setMediator(shared_from_this());
    }

    void notify(const std::shared_ptr<Component>& ptrComponent, const std::string& str )
    {
        // Handle events centrally
        if (ptrComponent == cbPtr && str == "check_changed") {
            if (cbPtr->isChecked()) {
                tbPtr->Activate();
                sbPtr->EnableButton();
            } else {
                tbPtr->clear();
                sbPtr->DisbaleButton();
            }
        }
    }

};


int main()
{


    // FIX 3: Allocate components as shared_ptrs so lifecycles match
    auto cb = std::make_shared<CheckBox>();
    auto tb = std::make_shared<TextBox>();
    auto sb = std::make_shared<SubmitButton>();

    // Create mediator
    auto mediator = std::make_shared<Mediator>(cb, tb, sb);
    mediator->initialize(); // Securely links everything together

    // Simulate user behavior
    cout << "--- User clicks checkbox to check it ---" << endl;
    cb->check();

    cout << "\n--- User clicks checkbox to uncheck it ---" << endl;
    cb->check();

    return 0;
}


