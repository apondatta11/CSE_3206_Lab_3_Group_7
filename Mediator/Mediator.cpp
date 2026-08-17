#include <iostream>
#include <string>
using namespace std;

class Aircraft; // forward declaration

// ----- Mediator Interface -----
class ControlTowerMediator {
public:
    virtual void requestLanding(Aircraft* plane) = 0;
    virtual void requestTakeoff(Aircraft* plane) = 0;
    virtual void notifyRunwayFree() = 0;
    virtual ~ControlTowerMediator() {}
};

// ----- Colleague Interface -----
class Aircraft {
protected:
    ControlTowerMediator* tower;
    string callSign;
public:
    Aircraft(ControlTowerMediator* t, string sign) {
        tower = t;
        callSign = sign;
    }
    string getCallSign() { return callSign; }
    void requestLand() {
        tower->requestLanding(this);
    }
    void requestTakeoff() {
        tower->requestTakeoff(this);
    }
};

// ----- Concrete Mediator -----
class ControlTower : public ControlTowerMediator {
private:
    bool runwayBusy;
public:
    ControlTower() { runwayBusy = false; }
    void requestLanding(Aircraft* plane) override {
        if (!runwayBusy) {
            runwayBusy = true;
            cout << plane->getCallSign() << ": cleared to land.\n";
        } else {
            cout << plane->getCallSign() << ": hold, runway busy.\n";
        }
    }
    void requestTakeoff(Aircraft* plane) override {
        if (!runwayBusy) {
            runwayBusy = true;
            cout << plane->getCallSign() << ": cleared for takeoff.\n";
        } else {
            cout << plane->getCallSign() << ": hold, runway busy.\n";
        }
    }
    void notifyRunwayFree() override {
        runwayBusy = false;
        cout << "Control Tower: runway is now free.\n";
    }
};

int main() {
    ControlTower tower;
    Aircraft flightA(&tower, "BG-147");
    Aircraft flightB(&tower, "BG-202");

    flightA.requestLand(); // runway free -> cleared
    flightB.requestLand(); // runway busy -> hold
    tower.notifyRunwayFree();
    flightB.requestLand(); // runway free again -> cleared

    return 0;
}
