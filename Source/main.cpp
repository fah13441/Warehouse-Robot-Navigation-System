#include "../Header/Functions.hpp"
#include <iostream>

using namespace std;

int main() {
    ItemSearchManager inventorySystem; 
    OrderQueue orderSystem;    
    RobotAssignment robotSystem(5);    
    NavigationStack robotRoute(5); 

    cout << "========================================== WAREHOUSE ROBOT SYSTEM INITIALIZATION ==========================================\n";

    robotSystem.addRobot("R001", "Robot Alpha");
    robotSystem.addRobot("R002", "Robot Beta");
    robotSystem.addRobot("R003", "Robot Gamma");
    robotSystem.updateRobotStatus("R002", "Maintenance");
    robotSystem.displayRobots();    

    inventorySystem.insertItem("ITM003", "Microphone", "Zone B, Aisle 2, Shelf A");
    inventorySystem.insertItem("ITM001", "Wireless Mouse", "Zone A, Aisle 1, Shelf C");
    inventorySystem.insertItem("ITM002", "Mechanical Keyboard", "Zone A, Aisle 4, Shelf B");
    inventorySystem.displayInventory();

    // --------------------------------------------------------- ORDER QUEUING: Fahad Bin Zaharuddin Fikri (TP085541) ---------------------------------------------------------
    
    cout << "\n========================================== SIMULATING INCOMING ORDERS ==========================================\n";

    orderSystem.enqueue("ORD100", "ITM002", 1); 
    orderSystem.enqueue("ORD101", "ITM001", 5); 
    orderSystem.displayOrders();

    // --------------------------------------------------------- SYSTEM PROCESSING & INTEGRATION ---------------------------------------------------------
    
    cout << "\n========================================== ROBOT PROCESSING SEQUENCE (FIFO) ==========================================\n";

    Order currentOrder;
    
    while (!orderSystem.isEmpty()) {
        if (orderSystem.dequeue(currentOrder)) {
            cout << "\n[System] Processing Order " << currentOrder.orderID << ".\n";

            // Assign Robot (Bektay Abdinur)
            if (robotSystem.assignTask(currentOrder.orderID)) {
                cout << "[System] Robot assigned successfully.\n";
                cout << "[Robot] Querying database for Item ID: " << currentOrder.itemID << "...\n";

                // Search Inventory (Aeivandra Van Keer Rao)
                inventorySystem.searchItem(currentOrder.itemID);

                robotSystem.completeTask(robotSystem.getLastAssignedRobotID());
            } else {
                cout << "[System] Order could not be assigned because no robot is available.\n";
            }
        }
    }

    cout << "\n[System] All orders have been processed. Queue is empty.\n";
    robotSystem.displayRobots();

    // --------------------------------------------------------- NAVIGATION STACK ISOLATED DEMO: Akhmad Ali Rafi (TP077577) ---------------------------------------------------------
    
    cout << "\n========================================== ROBOT NAVIGATION & PATH TRACKING ==========================================" << endl;

    cout << "\n[Phase 1] Robot Moving..." << endl;
    robotRoute.push("Entrance");
    robotRoute.push("Zone A");

    cout << "\n[Phase 2] Obstacle / Backtracking Demo..." << endl;
    robotRoute.push("Aisle 5");          
    robotRoute.backtrackOneStep();       
    robotRoute.push("Aisle 3");          
    robotRoute.push("Shelf B");
    robotRoute.navigateTo("Narrow Passage", true);
    robotRoute.push("Item Location");

    robotRoute.displayRoute();

    cout << "\n[Phase 3] Stack Operations" << endl;
    cout << "  Peek (current location): " << robotRoute.peek() << endl;
    cout << "  isEmpty(): " << (robotRoute.isEmpty() ? "true" : "false") << endl;
    cout << "  isFull():  " << (robotRoute.isFull() ? "true" : "false") << endl;

    cout << "\n[Phase 4] Return Journey" << endl;
    robotRoute.returnToStart();

    cout << "\n  isEmpty() after return: " << (robotRoute.isEmpty() ? "true" : "false") << endl;
    cout << "==========================================" << endl;

    return 0;
}