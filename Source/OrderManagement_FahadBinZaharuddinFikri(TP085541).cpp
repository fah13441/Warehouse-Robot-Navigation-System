#include "../Header/Functions.hpp"

OrderQueue::OrderQueue() {
    front = nullptr;
    rear = nullptr;
    currentSize = 0;
}

OrderQueue::~OrderQueue() {
    Order temp;
    while (!isEmpty()) {
        dequeue(temp);
    }
}

bool OrderQueue::isEmpty() const {
    return front == nullptr;
}

void OrderQueue::enqueue(std::string oID, std::string iID, int qty) {
    Order newOrder = {oID, iID, qty};
    OrderNode* newNode = new OrderNode(newOrder);

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    currentSize++;
    std::cout << "[Queue] Order " << oID << " received and added to the processing line.\n";
}

bool OrderQueue::dequeue(Order& dequeuedOrder) {
    if (isEmpty()) {
        std::cout << "[Queue] Error: No pending orders to process.\n";
        return false;
    }

    OrderNode* temp = front;
    dequeuedOrder = temp->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr; 
    }

    delete temp;
    currentSize--;
    return true;
}

bool OrderQueue::peek(Order& frontOrder) const {
    if (isEmpty()) {
        return false;
    }
    frontOrder = front->data;
    return true;
}

void OrderQueue::displayOrders() const {
    std::cout << "\n=== PENDING ORDERS QUEUE ===\n";
    if (isEmpty()) {
        std::cout << "No pending orders.\n";
        return;
    }
    
    OrderNode* current = front;
    int pos = 1;
    while (current != nullptr) {
        std::cout << pos++ << ". Order ID: " << current->data.orderID 
                  << " | Target Item: " << current->data.itemID 
                  << " | Qty: " << current->data.quantity << "\n";
        current = current->next;
    }
    std::cout << "----------------------------\n";
}

int OrderQueue::getSize() const {
    return currentSize;
}