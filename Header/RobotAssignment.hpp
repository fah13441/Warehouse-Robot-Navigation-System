#ifndef ROBOT_ASSIGNMENT_HPP
#define ROBOT_ASSIGNMENT_HPP

#include <iostream>
#include <string>
using namespace std;

struct Robot {
    string robotID;
    string robotName;
    string status;
    int taskCount;
    string currentOrderID;
};

class RobotAssignment {
private:
private:
    Robot* robots;
    int capacity;
    int robotCount;
    int nextIndex;
    string lastAssignedRobotID;

public:
    RobotAssignment(int size);
    ~RobotAssignment();

    void addRobot(string id, string name);
    void displayRobots();
    void updateRobotStatus(string id, string newStatus);
    bool assignTask(string orderID);
    void completeTask(string robotID);
    string getLastAssignedRobotID();
};

#endif