#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>

using namespace std;

// ========================================================================= Order Management: Fahad Bin Zaharuddin Fikri (TP085541) =========================================================================

struct Order {
    string orderID;
    string itemID;   
    int quantity;
};

struct OrderNode {
    Order data;
    OrderNode* next;

    OrderNode(Order ord) : data(ord), next(nullptr) {}
};

class OrderQueue {
private:
    OrderNode* front;
    OrderNode* rear;
    int currentSize;

public:
    OrderQueue();
    ~OrderQueue();

    void enqueue(string oID, string iID, int qty);
    bool dequeue(Order& dequeuedOrder); 
    bool peek(Order& frontOrder) const;
    bool isEmpty() const;
    void displayOrders() const;
    int getSize() const;
};


// ========================================================================= Robot Assignment : Bektay Abdinur (TP076035) =========================================================================

struct Robot {
    string robotID;
    string robotName;
    string status;
    int taskCount;
    string currentOrderID;
};

class RobotAssignment {
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


// ========================================================================= Navigation Stack: Akhmad Ali Rafi (TP077577) =========================================================================

class NavigationStack {
private:
    string* route;   
    int top;              
    int capacity;         

    void resize();

public:
    NavigationStack(int cap = 10);
    ~NavigationStack();

    NavigationStack(const NavigationStack&) = delete;
    NavigationStack& operator=(const NavigationStack&) = delete;

    void push(string location);
    string pop();
    string peek();
    bool isEmpty();
    bool isFull();
    void displayRoute();
    void returnToStart();
    bool navigateTo(string location, bool isBlocked);
    void backtrackOneStep();
};


// ========================================================================= Item Search Manager: Aeivendra Van Keer Rao (TP064243) =========================================================================

struct Item {
    string itemID;
    string name;
    string location; 
};

struct BSTNode {
    Item data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Item item) : data(item), left(nullptr), right(nullptr) {}
};

class ItemSearchManager {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, Item item);
    BSTNode* searchRecursive(BSTNode* node, string itemID) const;
    void displayInOrder(BSTNode* node) const;
    void clearTree(BSTNode* node);
    BSTNode* findMin(BSTNode* node);
    BSTNode* deleteRecursive(BSTNode* node, string itemID);

public:
    ItemSearchManager();
    ~ItemSearchManager();

    void insertItem(string id, string name, string loc);
    void searchItem(string id) const;
    void deleteItem(string id);
    void displayInventory() const;
};


// ========================================================================= Warehouse Layout & Navigation: Altayeb Abdelgadir Mohamed (TP085687) =========================================================================


struct WarehouseNode {
    string name;
    WarehouseNode* firstChild;
    WarehouseNode* nextSibling;

    WarehouseNode(string nodeName)
        : name(nodeName), firstChild(nullptr), nextSibling(nullptr) {
    }
};

class WarehouseLayout {
private:
    WarehouseNode* root;

    void displayRecursive(WarehouseNode* node, int level);
    WarehouseNode* findNode(WarehouseNode* node, string name);
    bool findPathRecursive(WarehouseNode* node,
        string destination,
        string path[],
        int& pathLength);
    void clearTree(WarehouseNode* node);

public:
    WarehouseLayout();
    ~WarehouseLayout();

    void createWarehouse();

    void addLocation(string parentName, string locationName);

    void displayLayout();

    void traverseLayout();

    void findRoute(string destination);
};

#endif