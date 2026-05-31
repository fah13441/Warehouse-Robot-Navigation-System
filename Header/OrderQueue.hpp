#ifndef ORDER_QUEUE_HPP
#define ORDER_QUEUE_HPP

#include <string>
#include <iostream>

struct Order {
    std::string orderID;
    std::string itemID;   
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

    void enqueue(std::string oID, std::string iID, int qty);
    bool dequeue(Order& dequeuedOrder); 
    bool peek(Order& frontOrder) const;
    bool isEmpty() const;
    void displayOrders() const;
    int getSize() const;
};

#endif