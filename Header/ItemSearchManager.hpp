#ifndef ITEM_SEARCH_MANAGER_HPP
#define ITEM_SEARCH_MANAGER_HPP

#include <string>
#include <iostream>

// Item Data Model
struct Item {
    std::string itemID;
    std::string name;
    std::string location; // e.g., "Zone A, Aisle 3, Shelf 2"
};

// Custom Binary Search Tree Node 
struct BSTNode {
    Item data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Item item) : data(item), left(nullptr), right(nullptr) {}
};

// Task 4 Module Class Implementation
class ItemSearchManager {
private:
    BSTNode* root;

    // Helper functions for recursive BST operations
    BSTNode* insertRecursive(BSTNode* node, Item item);
    BSTNode* searchRecursive(BSTNode* node, std::string itemID) const;
    void displayInOrder(BSTNode* node) const;
    void clearTree(BSTNode* node);
    BSTNode* findMin(BSTNode* node);
    BSTNode* deleteRecursive(BSTNode* node, std::string itemID);

public:
    ItemSearchManager();
    ~ItemSearchManager();

    // Core Functional Requirements
    void insertItem(std::string id, std::string name, std::string loc);
    void searchItem(std::string id) const;
    void deleteItem(std::string id);
    void displayInventory() const;
};

#endif