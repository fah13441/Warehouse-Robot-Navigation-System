#include "../Header/Functions.hpp"

// Constructor
WarehouseLayout::WarehouseLayout() {
    root = new WarehouseNode("Warehouse");
}

// Destructor
WarehouseLayout::~WarehouseLayout() {
    clearTree(root);
}

void WarehouseLayout::clearTree(WarehouseNode* node) {
    if (node == nullptr)
        return;

    clearTree(node->firstChild);
    clearTree(node->nextSibling);

    delete node;
}

WarehouseNode* WarehouseLayout::findNode(
    WarehouseNode* node,
    string name
) {
    if (node == nullptr)
        return nullptr;

    if (node->name == name)
        return node;

    WarehouseNode* found =
        findNode(node->firstChild, name);

    if (found)
        return found;

    return findNode(node->nextSibling, name);
}

void WarehouseLayout::addLocation(
    string parentName,
    string locationName
) {
    WarehouseNode* parent =
        findNode(root, parentName);

    if (!parent) {
        cout << "Parent location not found.\n";
        return;
    }

    WarehouseNode* newNode =
        new WarehouseNode(locationName);

    if (parent->firstChild == nullptr) {
        parent->firstChild = newNode;
    }
    else {
        WarehouseNode* current =
            parent->firstChild;

        while (current->nextSibling != nullptr)
            current = current->nextSibling;

        current->nextSibling = newNode;
    }
}

void WarehouseLayout::createWarehouse() {

    addLocation("Warehouse", "Zone A");
    addLocation("Warehouse", "Zone B");

    addLocation("Zone A", "Aisle A1");
    addLocation("Zone A", "Aisle A2");

    addLocation("Zone B", "Aisle B1");
    addLocation("Zone B", "Aisle B2");

    addLocation("Aisle A1", "Shelf A1-1");
    addLocation("Aisle A1", "Shelf A1-2");

    addLocation("Aisle A2", "Shelf A2-1");

    addLocation("Aisle B1", "Shelf B1-1");

    addLocation("Aisle B2", "Shelf B2-1");
}

void WarehouseLayout::displayRecursive(
    WarehouseNode* node,
    int level
) {
    if (node == nullptr)
        return;

    for (int i = 0; i < level; i++)
        cout << "   ";

    cout << "- " << node->name << endl;

    displayRecursive(node->firstChild,
        level + 1);

    displayRecursive(node->nextSibling,
        level);
}

void WarehouseLayout::displayLayout() {

    cout << "\n===== Warehouse Layout =====\n";

    displayRecursive(root, 0);
}

void WarehouseLayout::traverseLayout() {

    cout << "\n===== Traversal Result =====\n";

    displayRecursive(root, 0);
}

bool WarehouseLayout::findPathRecursive(
    WarehouseNode* node,
    string destination,
    string path[],
    int& pathLength
) {
    if (node == nullptr)
        return false;

    path[pathLength++] = node->name;

    if (node->name == destination)
        return true;

    if (findPathRecursive(
        node->firstChild,
        destination,
        path,
        pathLength))
        return true;

    pathLength--;

    return findPathRecursive(
        node->nextSibling,
        destination,
        path,
        pathLength);
}

void WarehouseLayout::findRoute(
    string destination
) {
    string path[100];
    int pathLength = 0;

    bool found =
        findPathRecursive(
            root,
            destination,
            path,
            pathLength);

    if (!found) {
        cout << "Destination not found.\n";
        return;
    }

    cout << "\n===== Route =====\n";

    for (int i = 0; i < pathLength; i++) {

        cout << path[i];

        if (i < pathLength - 1)
            cout << " -> ";
    }

    cout << endl;
}