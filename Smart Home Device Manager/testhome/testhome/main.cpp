#include <iostream>
#include <string>
using namespace std;

const int MAX_DEVICES = 10;
const int MAX_ROOMS = 5;


class Schedulable {
public:
    virtual void scheduleOn(string time) = 0;
    virtual void scheduleOff(string time) = 0;
    virtual ~Schedulable() {}
};


class SmartDevice {
public:
    string name, location;
    bool isOn;

    SmartDevice() {}
    SmartDevice(string n, string loc){
        name = n;
        location = loc;
        isOn = false;
    }

    virtual void turnOn() {
        isOn = true;
        cout << name << " is ON " << endl;
    }
    virtual void turnOff() {
        isOn = false;
        cout << name << " is OFF " << endl;
    }

    virtual void showStatus() {
        cout << name << " in " << location << " is "
        << (isOn ? "ON" : "OFF") << endl;
    }

    virtual string getType(){
        return "Generic";
    }
    virtual ~SmartDevice() {}
};


class Light : public SmartDevice, public Schedulable {
public:
    Light() {}
    Light(string n, string loc) : SmartDevice(n, loc) { }

    void scheduleOn(string time) override {
        cout << name << " will turn ON at " << time << endl;
    }

    void scheduleOff(string time) override {
        cout << name << " will turn OFF at " << time << endl;
    }

    string getType() override {
        return "Light";
    }
};


class Thermostat : public SmartDevice, public Schedulable {
public:
    int temperature;

    Thermostat() : temperature(24) {}
    Thermostat(string n, string loc) : SmartDevice(n, loc), temperature(24) { }

    void scheduleOn(string time) override {
        cout << name << " will turn ON at " << time << endl;
    }

    void scheduleOff(string time) override {
        cout << name << " will turn OFF at " << time << endl;
    }

    void setTemperature(int temp) {
        temperature = temp;
        cout << name << " set to " << temperature << "°C" << endl;
    }

    string getType() override {
        return "Thermostat";
    }
};

class SecurityCamera : public SmartDevice {
public:
    SecurityCamera() {}
    SecurityCamera(string n, string loc) : SmartDevice(n, loc) { }

    void startRecording() {
        cout << name << " camera is recording " << endl;
    }

    string getType() override {
        return "Camera";
    }
};


class Room {
public:
    string roomName;

    Light lights[MAX_DEVICES];
    int lightCount = 0;

    Thermostat thermostats[MAX_DEVICES];
    int thermoCount = 0;

    SecurityCamera cameras[MAX_DEVICES];
    int camCount = 0;

    Room() {}
    Room(string name) {
        roomName = name;
    }

    void addDevice(SmartDevice* device) {
        if (device->getType() == "Light" && lightCount < MAX_DEVICES)
        {
            lights[lightCount++] = *dynamic_cast<Light*>(device);
        }
        else if (device->getType() == "Thermostat" && thermoCount < MAX_DEVICES)
        {
            thermostats[thermoCount++] = *dynamic_cast<Thermostat*>(device);
        }
        else if (device->getType() == "Camera" && camCount < MAX_DEVICES)
        {
            cameras[camCount++] = *dynamic_cast<SecurityCamera*>(device);
        } else {
            cout << "Unknown or too many devices in room.\n";
        }
    }

    void turnAllOn() {
        for (int i = 0; i < lightCount; i++)
        {
            lights[i].turnOn();
        }
        for (int i = 0; i < thermoCount; i++)
        {
            thermostats[i].turnOn();
            
        }
        for (int i = 0; i < camCount; i++)
        {
            cameras[i].turnOn();
        }
    }

    void scheduleAll() {
        for (int i = 0; i < lightCount; i++)
        {
            lights[i].scheduleOn("6:00 PM");
        }
        for (int i = 0; i < thermoCount; i++)
        {
            thermostats[i].scheduleOff("10:00 PM");
            thermostats[i].setTemperature(23);
        }
        for (int i = 0; i < camCount; i++)
        {
            cameras[i].startRecording();
        }
    }

    void showDevices() {
        cout << "\nDevices in Room: " << roomName << endl;
        for (int i = 0; i < lightCount; i++)
        {
            lights[i].showStatus();
        }
        for (int i = 0; i < thermoCount; i++)
        {
            thermostats[i].showStatus();
        }
        for (int i = 0; i < camCount; i++)
        {
            cameras[i].showStatus();
        }
    }
};


class DeviceFactory {
public:
    static SmartDevice* create(string type, string name, string location)
    {
        if (type == "Light" || type == "light")
        {
            return new Light(name, location);
        }
        else if (type == "Thermostat" || type == "thermostat")
        {
            return new Thermostat(name, location);
        }
        else if (type == "Camera" || type == "camera")
        {
            return new SecurityCamera(name, location);
        }
        else
        return nullptr;
    }
};


class SmartHomeController {
public:
    Room rooms[MAX_ROOMS];
    int roomCount = 0;

    void addRoom(string name) {
        if (roomCount < MAX_ROOMS) {
            rooms[roomCount++] = Room(name);
        } else {
            cout << "Maximum room limit reached " << endl;
        }
    }

    Room* getRoomByName(string name) {
        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].roomName == name)
            {
                return &rooms[i];
            }
        }
        return nullptr;
    }

    void showAllRooms() {
        for (int i = 0; i < roomCount; i++)
        {
            rooms[i].showDevices();
        }
    }
};

int main() {
    SmartHomeController controller;
    int choice;

    while (true) {
        cout << "\n========== SMART HOME MENU ==========\n";
        cout << "1) Add Room " << endl;
        cout << "2) Add Device to Room " << endl;
        cout << "3) Show All Devices " << endl;
        cout << "4) Turn All Devices ON Room " << endl;
        cout << "5) Schedule All Devices Room " << endl;
        cout << "6) Exit " << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1){
            
            string roomName;
            cout << "Enter Room Name: ";
            getline(cin, roomName);
            controller.addRoom(roomName);
        }
        else if (choice == 2) {
            string roomName, type, devName;
            cout << "Enter Room Name: ";
            getline(cin, roomName);
            Room* room = controller.getRoomByName(roomName);
            if (!room) {
                cout << "Room not found! " << endl;
                continue;
            }

            cout << "Enter Device Type (Light/Thermostat/Camera): ";
            getline(cin, type);
            cout << "Enter Device Name: ";
            getline(cin, devName);

            SmartDevice* device = DeviceFactory::create(type, devName, roomName);
            if (!device) {
                cout << "Invalid device type! " << endl;
                continue;
            }

            room->addDevice(device);
            delete device;
        }
        else if (choice == 3) {
            controller.showAllRooms();
        }
        else if (choice == 4) {
            string roomName;
            cout << "Enter Room Name: ";
            getline(cin, roomName);
            Room* room = controller.getRoomByName(roomName);
            if (room)
            {
                room->turnAllOn();
            }
            else
            {
                cout << "Room not found! " << endl;
            }
        }
        else if (choice == 5) {
            string roomName;
            cout << "Enter Room Name: ";
            getline(cin, roomName);
            Room* room = controller.getRoomByName(roomName);
            if (room)
            {
                room->scheduleAll();
            }
            else
            {
                cout << "Room not found! " << endl;
            }
        }
        else if (choice == 6) {
            cout << "Exiting program " << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again " << endl;
        }
    }

    return 0;
}

