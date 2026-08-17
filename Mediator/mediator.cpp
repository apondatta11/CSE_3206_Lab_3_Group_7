#include <iostream>
using namespace std;

// Mediator
class AirTrafficController {
private:
    bool runwayBusy = false;

public:
    void requestRunway(string planeName) {

        if (!runwayBusy) {
            runwayBusy = true;
            cout << planeName << " can use the runway." << endl;
        }
        else {
            cout << planeName << " must wait." << endl;
        }
    }

    void runwayFree(string planeName) {
        runwayBusy = false;
        cout << planeName << " has left the runway." << endl;
    }
};

// Airplane
class Airplane {
private:
    string planeName;
    AirTrafficController* controller;

public:
    Airplane(string name, AirTrafficController* c) {
        planeName = name;
        controller = c;
    }

    void requestRunway() {
        controller->requestRunway(planeName);
    }

    void leaveRunway() {
        controller->runwayFree(planeName);
    }
};

int main() {

    AirTrafficController controller;

    Airplane planeA("Plane A", &controller);
    Airplane planeB("Plane B", &controller);

    planeA.requestRunway();
    planeB.requestRunway();

    planeA.leaveRunway();

    planeB.requestRunway();

    return 0;
}