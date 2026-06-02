#include "../Header/Functions.hpp"

NavigationStack::NavigationStack(int cap) {
    if (cap < 1) {
        capacity = 10;
    } else {
        capacity = cap;
    }
    top = -1;
    route = new string[capacity];
}

NavigationStack::~NavigationStack() {
    delete[] route;
    route = nullptr;
}

void NavigationStack::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    string* newRoute = new string[newCapacity];

    for (int i = 0; i <= top; i++) {
        newRoute[i] = route[i];
    }

    delete[] route;
    route = newRoute;
    capacity = newCapacity;
}

void NavigationStack::push(string location) {
    if (isFull()) {
        resize();
    }
    top++;
    route[top] = location;
    cout << "  Push: " << location << endl;
}

string NavigationStack::pop() {
    if (isEmpty()) {
        cerr << "  [ERROR] pop() failed - stack is empty." << endl;
        return "";
    }
    string removed = route[top];
    top--;
    return removed;
}

string NavigationStack::peek() {
    if (isEmpty()) {
        cerr << "  [ERROR] peek() failed - stack is empty." << endl;
        return "";
    }
    return route[top];
}

bool NavigationStack::isEmpty() {
    return (top == -1);
}

bool NavigationStack::isFull() {
    return (top == capacity - 1);
}

void NavigationStack::displayRoute() {
    cout << "\n  ----------------------------------------" << endl;
    cout << "  CURRENT ROUTE (Entrance -> Destination)" << endl;
    cout << "  ----------------------------------------" << endl;

    if (isEmpty()) {
        cout << "  (No locations recorded)" << endl;
        return;
    }

    for (int i = 0; i <= top; i++) {
        cout << "  Step " << (i + 1) << ": " << route[i] << endl;
    }
    cout << "  ----------------------------------------" << endl;
}

void NavigationStack::returnToStart() {
    cout << "\n  Returning..." << endl;
    if (isEmpty()) {
        cerr << "  [ERROR] returnToStart() failed - no route stored." << endl;
        return;
    }
    while (!isEmpty()) {
        string location = pop();
        cout << "  Pop: " << location << endl;
    }
    cout << "\n  Robot Returned Successfully" << endl;
}

bool NavigationStack::navigateTo(string location, bool isBlocked) {
    if (isBlocked) {
        cout << "  [OBSTACLE] Path blocked ahead: " << location << endl;
        if (!isEmpty()) {
            cout << "             Robot stays at: " << peek() << endl;
        }
        return false;
    }
    push(location);
    return true;
}

void NavigationStack::backtrackOneStep() {
    if (isEmpty()) {
        cerr << "  [ERROR] backtrackOneStep() failed - stack is empty." << endl;
        return;
    }
    string undone = pop();
    cout << "  [BACKTRACK] Undoing last move: " << undone << endl;

    if (!isEmpty()) {
        cout << "              Now at: " << peek() << endl;
    } else {
        cout << "              Now at: (start - no locations left)" << endl;
    }
}