#include "../Header/Functions.hpp"

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

BSTNode* ItemSearchManager::insertRecursive(BSTNode* node, Item item) {
    if (node == nullptr) {
        return new BSTNode(item);
    }
    if (item.itemID < node->data.itemID) {
        node->left = insertRecursive(node->left, item);
    } else if (item.itemID > node->data.itemID) {
        node->right = insertRecursive(node->right, item);
    } else {
        cout << "Warning: Item ID " << item.itemID << " already exists!\n";
    }
    return node;
}

void ItemSearchManager::insertItem(string id, string name, string loc) {
    Item newItem = {id, name, loc};
    root = insertRecursive(root, newItem);
}

BSTNode* ItemSearchManager::searchRecursive(BSTNode* node, string itemID) const {
    if (node == nullptr || node->data.itemID == itemID) {
        return node;
    }
    if (itemID < node->data.itemID) {
        return searchRecursive(node->left, itemID);
    }
    return searchRecursive(node->right, itemID);
}

void ItemSearchManager::searchItem(string id) const {
    BSTNode* result = searchRecursive(root, id);
    cout << "\n--- Item Search Result (ID: " << id << ") ---\n";
    if (result != nullptr) {
        cout << "Item Found!\n";
        cout << "Name: " << result->data.name << "\n";
        cout << "Location: " << result->data.location << "\n";
    } else {
        cout << "Error: Item ID " << id << " not found in database.\n";
    }
}

BSTNode* ItemSearchManager::findMin(BSTNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BSTNode* ItemSearchManager::deleteRecursive(BSTNode* node, string itemID) {
    if (node == nullptr) return node;

    if (itemID < node->data.itemID) {
        node->left = deleteRecursive(node->left, itemID);
    } else if (itemID > node->data.itemID) {
        node->right = deleteRecursive(node->right, itemID);
    } else {
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        BSTNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, temp->data.itemID);
    }
    return node;
}

void ItemSearchManager::deleteItem(string id) {
    root = deleteRecursive(root, id);
    cout << "Item " << id << " processing complete (removed/updated).\n";
}

void ItemSearchManager::displayInOrder(BSTNode* node) const {
    if (node != nullptr) {
        displayInOrder(node->left);
        cout << "ID: " << node->data.itemID 
             << " | Name: " << node->data.name 
             << " | Location: " << node->data.location << "\n";
        displayInOrder(node->right);
    }
}

void ItemSearchManager::displayInventory() const {
    cout << "\n=== WAREHOUSE ITEM DATABASE (Sorted Listing) ===\n";
    if (root == nullptr) {
        cout << "Database is empty.\n";
    } else {
        displayInOrder(root);
    }
}