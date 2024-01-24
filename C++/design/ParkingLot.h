#pragma once
#include "../header.h"

class OwnerDetail {
public:
    string name;
    string id;

    OwnerDetail(string name, string id) : name(name), id(id) {}
    string to_string() {
        return "Owner Dtail:{" + name + ", " + id + "}";
    }
};
class Vehicle {
public:
    enum class Type { Motorcycle, Car, Bus };
    string id;
    Type type;
    OwnerDetail ownerDetail;

    Vehicle(string id, Type type, OwnerDetail ownerDetail) : id(id), type(type), ownerDetail(ownerDetail) {}

    string to_string() {
        stringstream ss;
        ss << "{";
        ss << "Vehicle Detail: {Id:" << id << ", Type:" << toTypeStr(type) << "}" << endl;
        ss << ownerDetail.to_string() << endl;
        ss << "}";
        return ss.str();
    }

private:
    string toTypeStr(Type type) {
        switch (type) {
            case Type::Motorcycle:
                return "Motorcycle";
            case Type::Car:
                return "Car";
            case Type::Bus:
                return "Bus";
        }
        return "";
    }
};

class AllocatedSpace {
public:
    int floor = -1;
    int rowNum = -1;
    int start = -1;
    int end = -1;

    string to_string() {
        return "{" + std::to_string(floor) + ", " + std::to_string(rowNum) + ", " + std::to_string(start) + ", " + std::to_string(end) + "}";
    }
};

class FloorPlan {
public:
    class Slot {
    public:
        enum class Type { Small, Medium, Large };
        int slotId;
        Type type;
        bool isAvailable = true;
        string vehicleId;

        string to_string() {
            return "{" + std::to_string(slotId) + ", " + getTypeStr(type) + ", " + getAvailable() + "," + vehicleId + "}";
        }
    private:
        string getTypeStr(Type type) {
            switch (type) {
                case Type::Small:
                    return "Small";
                case Type::Medium:
                    return "Medium";
                case Type::Large:
                    return "Large";
            }
            return "";
        }

        string getAvailable() {
            return isAvailable ? "Empty" : "Occupied";
        }
    };
    class RowPlan {
    public:
        vector<Slot> slots;
        const unordered_map<Vehicle::Type, pair<Slot::Type, int>> vehicleSpace = {
            {Vehicle::Type::Motorcycle,{Slot::Type::Small,1}},
            {Vehicle::Type::Car,{Slot::Type::Medium,1}},
            {Vehicle::Type::Bus,{Slot::Type::Large,5}}
        };

        RowPlan(int numSlots) {
            slots.resize(numSlots);
        }
        void InitRandom(int floorNum, int floorSize, int rowNum) {
            int pos = 0;
            for (auto& slot : slots) {
                Slot::Type t = (Slot::Type)(rand() % 3);
                slot.type = t;
                slot.slotId = floorNum * floorSize + rowNum * size() + pos++;
            }
        }

        int size() {
            return slots.size();
        }

        string to_string() {
            stringstream ss;
            ss << "Row: {";
            for (auto& slot : slots) {
                ss << slot.to_string() << ", ";
            }
            ss << "}";
            return ss.str();
        }

        bool park(Vehicle& vehicle, AllocatedSpace& space) {
            auto reqSpace = vehicleSpace.at(vehicle.type);
            for (int i = 0; i < slots.size(); i++) {
                if (slots[i].type == reqSpace.first && hasContinuousSpace(i, reqSpace.first, reqSpace.second)) {
                    space.start = i;
                    space.end = i + reqSpace.second;
                    updateSlots(vehicle, i, reqSpace.first, reqSpace.second);
                    return true;
                }
            }
            return false;
        }

        bool hasContinuousSpace(int startIndex, Slot::Type type, int reqSize) {
            reqSize--;
            for (int i = startIndex + 1; i < slots.size(); i++) {
                if (slots[i].type == type) reqSize--;
                else break;
            }
            return reqSize == 0;
        }
        void updateSlots(Vehicle& vehicle, int startIndex, Slot::Type type, int reqSize)
        {
            for (int i = startIndex; i < startIndex + reqSize; i++) {
                slots[i].isAvailable = false;
                slots[i].vehicleId = vehicle.id;
            }
        }
    };
    vector<RowPlan> rows;

    FloorPlan(int numRows, int slotsPerRow) {
        for (int i = 0; i < numRows; i++) {
            rows.push_back(RowPlan(slotsPerRow));
        }
    }

    void InitRandom(int floorNum) {
        for (int i = 0; i < rows.size(); i++) {
            rows[i].InitRandom(floorNum, size(), i);
        }
    }

    string to_string() {
        stringstream ss;
        ss << "Floor: {" << endl;
        for (auto& row : rows) {
            ss << row.to_string() << endl;
        }
        ss << "}";
        return ss.str();
    }

    bool park(Vehicle& vehicle, AllocatedSpace& space) {
        for (int i = 0; i < rows.size(); i++) {
            if (rows[i].park(vehicle, space)) {
                space.rowNum = i;
                return true;
            }
        }
        return false;
    }
private:
    int size() {
        int sz = 0;
        for (auto& row : rows) {
            sz += row.size();
        }
        return sz;
    }
};


class ParkingLot {
private:
    vector<FloorPlan> floors;
    unordered_map<string, AllocatedSpace> vehicles;

public:
    void Init(int numFloors, int numRows, int slotsPerRow) {
        for (int i = 0; i < numFloors; i++) {
            floors.push_back(FloorPlan(numRows, slotsPerRow));
        }
    }
    void InitFloor(int numRows) {
        for (int i = 0; i < floors.size(); i++) {
            floors[i].InitRandom(i);
        }
    }

    string to_string() {
        stringstream ss;
        ss << "Parking Slot: {" << endl;
        for (auto& floor : floors) {
            ss << floor.to_string() << endl;
        }
        ss << "}";
        return ss.str();
    }

    bool park(Vehicle& vehicle) {
        AllocatedSpace space;
        vector<FloorPlan::Slot> slots;
        for (int i = 0; i < floors.size(); i++) {
            if (floors[i].park(vehicle, space)) {
                space.floor = i;
                vehicles.insert({ vehicle.id, space });
                return true;
            }
        }
        return false;
    }

    AllocatedSpace& getParkedSpace(string id) {
        return vehicles.at(id);
    }
};

class ParkingLotTest {
public:
    static void test() {
        ParkingLot parkingLot;
        int numFloors = 3;
        int numRows = 4;
        int slotsPerRow = 5;
        parkingLot.Init(numFloors, numRows, slotsPerRow);
        parkingLot.InitFloor(numRows);

        cout << "Initial state of parking lot:" << endl;
        cout << parkingLot.to_string() << endl;

        vector<Vehicle> vehicles;
        vehicles.push_back(Vehicle("vehicleid1", Vehicle::Type::Motorcycle, OwnerDetail("ownerName1", "ownerid1")));
        vehicles.push_back(Vehicle("vehicleid2", Vehicle::Type::Bus, OwnerDetail("ownerName2", "ownerid2")));
        vehicles.push_back(Vehicle("vehicleid3", Vehicle::Type::Motorcycle, OwnerDetail("ownerName3", "ownerid3")));
        vehicles.push_back(Vehicle("vehicleid4", Vehicle::Type::Car, OwnerDetail("ownerName4", "ownerid4")));
        vehicles.push_back(Vehicle("vehicleid5", Vehicle::Type::Car, OwnerDetail("ownerName5", "ownerid5")));
        vehicles.push_back(Vehicle("vehicleid6", Vehicle::Type::Car, OwnerDetail("ownerName6", "ownerid6")));
        vehicles.push_back(Vehicle("vehicleid7", Vehicle::Type::Motorcycle, OwnerDetail("ownerName7", "ownerid7")));
        vehicles.push_back(Vehicle("vehicleid8", Vehicle::Type::Bus, OwnerDetail("ownerName8", "ownerid8")));
        vehicles.push_back(Vehicle("vehicleid9", Vehicle::Type::Car, OwnerDetail("ownerName9", "ownerid9")));

        for (auto& vehicle : vehicles) {
            cout << "Can park vehicle: " << endl;
            auto res = parkingLot.park(vehicle);
            cout << vehicle.to_string() << "::" << res << endl;
            if (res) cout << parkingLot.getParkedSpace(vehicle.id).to_string() << endl;
            cout << endl << endl;
        }

        //cout << "Current state of parking lot:" << endl;
        //cout << parkingLot.to_string() << endl;

        //for (auto& vehcile : database) {
        //    if (shouldRemove()) {
        //        parkingLot.unpark(vehicle);
        //    }
        //}
        //cout << "Current state of parking lot:" << endl;
        //cout << parkingLot.to_string() << endl;

        //for (auto& vehicle : parkingLot.getVehicles()) {
        //    parkingLot.park(vehicle);
        //}

        //cout << "Current state of parking lot:" << endl;
        //cout << parkingLot.to_string() << endl;
    }
};