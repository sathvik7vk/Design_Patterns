//For adapter design pattern


/*****************************************************************************************
 * Adapter Design Pattern (Structural Pattern)
 *
 * Intent:
 * --------
 * The Adapter pattern allows incompatible interfaces to work together by converting
 * the interface of one class into another interface that the client expects.
 *
 * It acts as a "wrapper" around an existing (often third-party or legacy) class and
 * translates client requests into a form that the wrapped class can understand.
 *
 * Problem Solved:
 * ----------------
 * - Client code expects a common interface (CloudStorage).
 * - Some classes already match this interface (CloudDrive, FastShare).
 * - A third-party class (VirtualDrive) has a different interface:
 *       - uploadData(data, id)
 *       - usedSpace(), totalSpace
 * - We cannot modify the third-party class.
 *
 * Without Adapter → Client cannot directly use VirtualDrive.
 *
 * Solution:
 * ----------
 * - Create an Adapter class (VirtualDriveAdapter) that:
 *     - Inherits from the target interface (CloudStorage).
 *     - Internally contains the adaptee (VirtualDrive).
 *     - Translates CloudStorage calls into VirtualDrive calls.
 *
 * Example Mapping in this program:
 * --------------------------------
 * CloudStorage::uploadContents(content)
 *        --> VirtualDrive::uploadData(content, generatedID)
 *
 * CloudStorage::getFreeSpace()
 *        --> totalSpace - usedSpace()
 *
 * Benefits:
 * ----------
 * - Enables reuse of existing / third-party code without modification.
 * - Keeps client code independent of concrete implementations.
 * - Supports Open/Closed Principle (open for extension, closed for modification).
 * - Improves maintainability and scalability.
 *
 * When to Use Adapter:
 * --------------------
 * - When you want to use an existing class but its interface does not match
 *   what your system expects.
 * - When integrating third-party libraries or legacy systems.
 * - When you want to standardize multiple different APIs behind one interface.
 *
 * Key Roles:
 * ----------
 * - Target Interface   : CloudStorage
 * - Adaptee            : VirtualDrive (incompatible interface)
 * - Adapter            : VirtualDriveAdapter
 * - Client             : main() using CloudStorage polymorphically
 *
 *****************************************************************************************/

 
#include <iostream>
#include <string>
#include <memory>
#include <ctime>

using namespace std;

class CloudStorage
{
public:
    virtual bool uploadContents(const string &content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;

        return true;
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here.
        const int size = arc4random_uniform(20);
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        const int size = arc4random_uniform(10);
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }
    int usedSpace()
    {
        return arc4random_uniform(10);
    }
    const int totalSpace = 15;
};

// Adapter class
// This class adapts the VirtualDrive interface to conform to the CloudStorage interface.

class VirtualDriveAdapter : public CloudStorage
{
private:
    // m_adaptee: The third-party VirtualDrive service being adapted
    std::unique_ptr<VirtualDrive> m_adaptee;

public:
    // Constructor: Initializes the adapter by creating an instance of the VirtualDrive adaptee
    VirtualDriveAdapter() { m_adaptee = make_unique<VirtualDrive>(); }

    // uploadContents: Override method that adapts the uploadData interface
 
    // This method bridges the different interface by converting the content string
    // to the format required by VirtualDrive's uploadData method (data string and unique ID)
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to VirtualDrive: " << endl;

        int id = rand();  // Generate a unique ID for the VirtualDrive service

        bool rc = m_adaptee->uploadData(content, id);
        return rc;
    }

    // getFreeSpace: Override method that adapts the free space calculation interface
    // Returns: int - The available free space in GB
    // This method adapts VirtualDrive's interface (totalSpace and usedSpace methods)
    // to match the CloudStorage interface's getFreeSpace method
    int getFreeSpace() override
    {
        int freeSpace = m_adaptee->totalSpace - m_adaptee->usedSpace();
        return freeSpace;
    }

    // Destructor: Cleans up the adaptee (automatically handled by unique_ptr)
    ~VirtualDriveAdapter() = default;
};

int main()
{
    // Create an array of pointers to CloudStorage objects.
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<VirtualDriveAdapter>()
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object.
    const string content = "Beam me up, Scotty!";
    for (const auto &service : cloudServices)
    {        
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
