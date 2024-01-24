#pragma once
#include "../Header.h"

class PrintTour {
    struct PetrolPump {
        int petrol;
        int distance;
        PetrolPump(int petrol, int distance) :petrol(petrol), distance(distance) {}
        string to_string() {
            return "{" + std::to_string(petrol) + ", " + std::to_string(distance) + "}";
        }
    };
public:
    static void test() {
        vector<PetrolPump> petrolPumps = { {6, 4}, {3, 6}, {7, 3},{1,3},{4,3},{5,2},{7,2},{8,1},{8,3},{5,4} };

        int n = petrolPumps.size();
        int start = 0, end = 0;
        int curPetrol = 0;
        do {
            while (start <= end && curPetrol < 0) {
                curPetrol -= petrolPumps[start].petrol - petrolPumps[start].distance;
                start++;
            }
            if (start == n) break;

            curPetrol += petrolPumps[end].petrol - petrolPumps[end].distance;
            end = (end + 1) % n;
        } while (start != end);

        if (curPetrol < 0) cout << "No path exists" << endl;
        else {
            do {
                cout << petrolPumps[start].to_string() << " -> ";
                start = (start + 1) % n;
            } while (start != end);
        }
    }
};