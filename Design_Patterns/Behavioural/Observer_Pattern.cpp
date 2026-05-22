/*
Observer pattern:
the Observer design pattern is like subscribing to a YouTube channel or a newsletter.

When you subscribe to a channel, you don’t constantly call the creator every day asking, "Did you post a
video yet?" Instead, you go about your life, and the moment a new video drops, the channel broadcasts a 
notification straight to you and thousands of other subscribers instantly.

In software engineering, the Observer pattern is a behavioral design pattern that defines a one-to-many 
dependency. When one object (the Subject) changes its state, all its dependents (the Observers) are 
notified and updated automatically.

Imagine you are building a financial dashboard application. You have a StockMarket class that fetches live 
stock price updates from an external API, and you have multiple components that need to display this data:
1. A LivePriceGraph that charts the stock trend.
2. A PortfolioValueViewer that updates the user's total net worth.
3. An AlertSystem that sends an email if a stock crashes.

If you don't use the Observer pattern, these components have to resort to polling—running a loop that constantly 
checks the StockMarket object: "Do you have new prices yet? How about now? How about now?" This burns massive 
amounts of CPU cycles and couples your UI components tightly to the stock market engine.

The Solution: Pub-Sub Architecture
With the Observer pattern, the relationship reverses. The components stop asking. Instead, they register 
themselves with the Subject. When the stock market gets an update, it loops through its list of subscribers 
and broadcasts the new data to them.

Key Benefits:
Decoupled Architecture: The Subject only knows that its observers implement a basic interface (usually just
an update() method). It doesn't know or care about the underlying UI logic of a graph, dashboard, or email system.

Open/Closed Principle: You can add 50 new types of subscriber components (e.g., a logging system, an SMS alert 
system) without modifying a single line of code inside the StockMarket class.

Real-time Event Handling: State changes propagate immediately across your entire system.

Structure of the Observer Pattern:
The pattern is built out of four elements:

1. Subject (Interface): Provides an interface for attaching (attach), detaching (detach), and notifying 
observers.
2. Concrete Subject: Stores the state of interest and sends a notification to its observers when the 
state changes.
3. Observer (Interface): Defines an updating interface for objects that should be notified of changes 
(typically a single update() function).
4. Concrete Observer: Implements the Observer interface to keep its state consistent with the 
subject's state.


*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>

using namespace std;

class IObserver
{
    private:
    public:
    virtual ~IObserver() = default;
    virtual void update(const string& str, const double price) = 0;
};

class ISubject
{
    private:

    public:
    virtual ~ISubject() = default;
    virtual void attach(const std::shared_ptr<IObserver>& ptr) = 0;
    virtual void detach(std::shared_ptr<IObserver>& ptr) = 0;
    virtual void notify() = 0;
    virtual void setStockData(const string& str, const double price) = 0;

};



class StockMarket:public ISubject
{
private:
std::string m_stockName;
double m_stockPrice;
std::vector<std::shared_ptr<IObserver>> m_listOfObservers;

public:
    void attach(const std::shared_ptr<IObserver>& ptr)
    {
        m_listOfObservers.push_back(ptr);
    }
    void detach(std::shared_ptr<IObserver>& ptr)
    {
        m_listOfObservers.erase(std::remove(m_listOfObservers.begin(), m_listOfObservers.end(), ptr), m_listOfObservers.end());
    }
    void notify()
    {
        cout<<"Notifying the observers"<<endl;
        for(const auto& observer:m_listOfObservers)
            observer->update(m_stockName, m_stockPrice);
    }

    //public method to set the stock data
    void setStockData(const string& str, const double price)
    {
        cout<<"Setting stock name and stock price"<<endl;
        m_stockName = str;
        m_stockPrice = price;
        notify();
    }
};

class LiveStockGraph:public IObserver
{
    public:
    void update(const string& str, const double price)
    {
        cout<<"Live graph for "<<str<<" is "<<price<<endl;
    }
};

class SMSAlert:public IObserver
{
private:
public:
    void update(const string &str, const double price)
    {
        cout << "SMS Alert: Stock price for " << str << " has reached " << price << endl;
    }
};


int main()
{

    std::shared_ptr<ISubject> stockMarketPtr = std::make_shared<StockMarket>();

    std::shared_ptr<IObserver> liveGraphObserver = std::make_shared<LiveStockGraph>();
    std::shared_ptr<IObserver> smsAlertObserver = std::make_shared<SMSAlert>();

    stockMarketPtr->attach(liveGraphObserver);
    stockMarketPtr->attach(smsAlertObserver);

    stockMarketPtr->setStockData("TCS", 2350);

    stockMarketPtr->detach(smsAlertObserver);
    stockMarketPtr->setStockData("TCS", 1800);
    return 0;
}