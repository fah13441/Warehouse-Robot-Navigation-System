#include "RobotAssignment.hpp"

RobotAssignment::RobotAssignment(int size) {
    capacity = size;
    robotCount = 0;
    nextIndex = 0;
    lastAssignedRobotID = "";
    robots = new Robot[capacity];
}

RobotAssignment::~RobotAssignment() {
    delete[] robots;
}

void RobotAssignment::addRobot(string id, string name) {
    if (robotCount >= capacity) {
        cout << "[Robot Assignment] Cannot add robot. Robot list is full.\n";
        return;
    }

    robots[robotCount].robotID = id;
    robots[robotCount].robotName = name;
    robots[robotCount].status = "Available";
    robots[robotCount].taskCount = 0;
    robots[robotCount].currentOrderID = "-";

    robotCount++;

    cout << "[Robot Assignment] Robot " << id << " added successfully.\n";
}

void RobotAssignment::displayRobots() {
    cout << "\n==============================================\n";
    cout << "          ROBOT STATUS OVERVIEW\n";
    cout << "==============================================\n";

    if (robotCount == 0) {
        cout << "No robots have been registered yet.\n";
        return;
    }

    cout << "ID\tName\t\tStatus\t\tTasks\tCurrent Order\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < robotCount; i++) {
        cout << robots[i].robotID << "\t"
             << robots[i].robotName << "\t"
             << robots[i].status << "\t\t"
             << robots[i].taskCount << "\t"
             << robots[i].currentOrderID << "\n";
    }
}

void RobotAssignment::updateRobotStatus(string id, string newStatus) {
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].robotID == id) {
            robots[i].status = newStatus;

            if (newStatus == "Available") {
                robots[i].currentOrderID = "-";
            }

            cout << "[Robot Assignment] Robot " << id
                 << " status updated to " << newStatus << ".\n";
            return;
        }
    }

    cout << "[Robot Assignment] Robot " << id << " was not found.\n";
}

bool RobotAssignment::assignTask(string orderID) {
    if (robotCount == 0) {
        cout << "[Robot Assignment] No robots are registered.\n";
        return false;
    }

    int checkedRobots = 0;

    while (checkedRobots < robotCount) {
        if (robots[nextIndex].status == "Available") {
            robots[nextIndex].status = "Busy";
            robots[nextIndex].currentOrderID = orderID;
            robots[nextIndex].taskCount++;
            lastAssignedRobotID = robots[nextIndex].robotID;

            cout << "[Robot Assignment] Order " << orderID
                 << " assigned to " << robots[nextIndex].robotID
                 << " (" << robots[nextIndex].robotName << ").\n";

            nextIndex = (nextIndex + 1) % robotCount;
            return true;
        }

        cout << "[Robot Assignment] " << robots[nextIndex].robotID
             << " skipped because status is "
             << robots[nextIndex].status << ".\n";

        nextIndex = (nextIndex + 1) % robotCount;
        checkedRobots++;
    }

    cout << "[Robot Assignment] No available robot found for Order "
         << orderID << ".\n";

    return false;
}

void RobotAssignment::completeTask(string robotID) {
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].robotID == robotID) {
            if (robots[i].status == "Busy") {
                cout << "[Robot Assignment] Robot " << robotID
                     << " completed Order " << robots[i].currentOrderID << ".\n";

                robots[i].status = "Available";
                robots[i].currentOrderID = "-";
            } else {
                cout << "[Robot Assignment] Robot " << robotID
                     << " is not currently busy.\n";
            }

            return;
        }
    }

    cout << "[Robot Assignment] Robot " << robotID << " was not found.\n";
}  
string RobotAssignment::getLastAssignedRobotID() {
    return lastAssignedRobotID;
}