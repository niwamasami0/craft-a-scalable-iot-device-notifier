#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <ctime>
#include <cstdlib>

using namespace std;

// IoT Device class
class IoTDevice {
public:
    IoTDevice(string id, string name) : id(id), name(name), state(false) {}
    string getId() { return id; }
    string getName() { return name; }
    bool getState() { return state; }
    void setState(bool state) { this->state = state; }

private:
    string id;
    string name;
    bool state;
};

// Notifier class
class Notifier {
public:
    Notifier() {}
    void addDevice(IoTDevice* device) {
        lock_guard<mutex> lock(mutex_);
        devices_.push_back(device);
    }
    void notifyDevices() {
        lock_guard<mutex> lock(mutex_);
        for (IoTDevice* device : devices_) {
            if (device->getState()) {
                cout << "Notification: " << device->getName() << " is online." << endl;
            } else {
                cout << "Notification: " << device->getName() << " is offline." << endl;
            }
        }
    }

private:
    vector<IoTDevice*> devices_;
    mutex mutex_;
};

// IoT Device simulator
void simulateIoTDevice(IoTDevice* device, Notifier* notifier) {
    srand(time(0));
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        int randNum = rand() % 2;
        device->setState(randNum == 0 ? false : true);
        notifier->notifyDevices();
    }
}

int main() {
    Notifier notifier;
    IoTDevice device1("D1", "Temperature Sensor");
    IoTDevice device2("D2", "Humidity Sensor");
    IoTDevice device3("D3", "Light Sensor");

    notifier.addDevice(&device1);
    notifier.addDevice(&device2);
    notifier.addDevice(&device3);

    thread t1(simulateIoTDevice, &device1, &notifier);
    thread t2(simulateIoTDevice, &device2, &notifier);
    thread t3(simulateIoTDevice, &device3, &notifier);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}