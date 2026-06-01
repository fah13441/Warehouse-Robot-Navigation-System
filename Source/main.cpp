#include "ItemSearchManager.hpp"
#include "OrderQueue.hpp"
#include <iostream>
#include "RobotAssignment.hpp"

using namespace std;

int main() {
    ItemSearchManager inventorySystem; 
    OrderQueue orderSystem;    
    RobotAssignment robotSystem(5);    
    robotSystem.addRobot("R001", "Robot Alpha");
    robotSystem.addRobot("R002", "Robot Beta");
    robotSystem.addRobot("R003", "Robot Gamma");
    robotSystem.updateRobotStatus("R002", "Maintenance");
    robotSystem.displayRobots();    

    cout << "==========================================\n";
    cout << "  WAREHOUSE ROBOT SYSTEM INITIALIZATION   \n";
    cout << "==========================================\n";

    inventorySystem.insertItem("ITM003", "Microphone", "Zone B, Aisle 2, Shelf A");
    inventorySystem.insertItem("ITM001", "Wireless Mouse", "Zone A, Aisle 1, Shelf C");
    inventorySystem.insertItem("ITM002", "Mechanical Keyboard", "Zone A, Aisle 4, Shelf B");
    
    inventorySystem.displayInventory();

    cout << "\n==========================================\n";
    cout << "      SIMULATING INCOMING ORDERS          \n";
    cout << "==========================================\n";

    orderSystem.enqueue("ORD100", "ITM002", 1); 
    orderSystem.enqueue("ORD101", "ITM001", 5); 
    orderSystem.enqueue("ORD102", "ITM099", 2); 

    orderSystem.displayOrders();

    cout << "\n==========================================\n";
    cout << "    ROBOT PROCESSING SEQUENCE (FIFO)      \n";
    cout << "==========================================\n";

    Order currentOrder;
    
    while (!orderSystem.isEmpty()) {
        if (orderSystem.dequeue(currentOrder)) {
           cout << "\n[System] Processing Order " << currentOrder.orderID << ".\n";

if (robotSystem.assignTask(currentOrder.orderID)) {
    cout << "[System] Robot assigned successfully.\n";
    cout << "[Robot] Querying database for Item ID: " << currentOrder.itemID << "...\n";

    inventorySystem.searchItem(currentOrder.itemID);

    robotSystem.completeTask(robotSystem.getLastAssignedRobotID());
} else {
    cout << "[System] Order could not be assigned because no robot is available.\n";
}
        }
    }

    cout << "\n[System] All orders have been processed. Queue is empty.\n";
robotSystem.displayRobots();
    return 0;
}