//For adapter design pattern

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
