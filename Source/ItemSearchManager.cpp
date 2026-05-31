#include "ItemSearchManager.hpp"

ItemSearchManager::ItemSearchManager() : root(nullptr) {}

ItemSearchManager::~ItemSearchManager() {
    clearTree(root);
}

void ItemSearchManager::clearTree(BSTNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

// Helper to recursively insert items sorted by Item ID
BSTNode* ItemSearchManager::insertRecursive(BSTNode* node, Item item) {
    if (node == nullptr) {
        return new BSTNode(item);
    }
    if (item.itemID < node->data.itemID) {
        node->left = insertRecursive(node->left, item);
    } else if (item.itemID > node->data.itemID) {
        node->right = insertRecursive(node->right, item);
    } else {
        std::cout << "Warning: Item ID " << item.itemID << " already exists!\n";
    }
    return node;
}

void ItemSearchManager::insertItem(std::string id, std::string name, std::string loc) {
    Item newItem = {id, name, loc};
    root = insertRecursive(root, newItem);
}

// Helper to perform optimized Binary Search O(log n)
BSTNode* ItemSearchManager::searchRecursive(BSTNode* node, std::string itemID) const {
    if (node == nullptr || node->data.itemID == itemID) {
        return node;
    }
    if (itemID < node->data.itemID) {
        return searchRecursive(node->left, itemID);
    }
    return searchRecursive(node->right, itemID);
}

void ItemSearchManager::searchItem(std::string id) const {
    BSTNode* result = searchRecursive(root, id);
    std::cout << "\n--- Item Search Result (ID: " << id << ") ---\n";
    if (result != nullptr) {
        std::cout << "Item Found!\n";
        std::cout << "Name: " << result->data.name << "\n";
        std::cout << "Location: " << result->data.location << "\n";
    } else {
        std::cout << "Error: Item ID " << id << " not found in database.\n";
    }
}

BSTNode* ItemSearchManager::findMin(BSTNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Helper to handle record deletion and structure restructuring
BSTNode* ItemSearchManager::deleteRecursive(BSTNode* node, std::string itemID) {
    if (node == nullptr) return node;

    if (itemID < node->data.itemID) {
        node->left = deleteRecursive(node->left, itemID);
    } else if (itemID > node->data.itemID) {
        node->right = deleteRecursive(node->right, itemID);
    } else {
        // Node with only one child or no child
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        // Node with two children: Get inorder successor
        BSTNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, temp->data.itemID);
    }
    return node;
}

void ItemSearchManager::deleteItem(std::string id) {
    root = deleteRecursive(root, id);
    std::cout << "Item " << id << " processing complete (removed/updated).\n";
}

// In-Order Traversal automatically outputs data sorted lexicographically by ID
void ItemSearchManager::displayInOrder(BSTNode* node) const {
    if (node != nullptr) {
        displayInOrder(node->left);
        std::cout << "ID: " << node->data.itemID 
                  << " | Name: " << node->data.name 
                  << " | Location: " << node->data.location << "\n";
        displayInOrder(node->right);
    }
}

void ItemSearchManager::displayInventory() const {
    std::cout << "\n=== WAREHOUSE ITEM DATABASE (Sorted Listing) ===\n";
    if (root == nullptr) {
        std::cout << "Database is empty.\n";
    } else {
        displayInOrder(root);
    }
}