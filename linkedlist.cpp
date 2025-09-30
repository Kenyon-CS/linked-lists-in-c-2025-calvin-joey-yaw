#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;


template <typename T>
class node {
  public:
    T data;           // Data of generic type T
    node* next;       // Pointer to the next node in the list

    node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
  private:
    node<T>* head;  // Pointer to the first node of the list

  public:
    LinkedList() : head(nullptr) {}

    // Insert at the end
    void append(T value) {
        node<T>* newNode = new node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Insert at the beginning
    void prepend(T value) {
        node<T>* newNode = new node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Remove first occurrence of value
    void remove(T value) {
        if (head == nullptr) return;

        if (head->data == value) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) return;

        node<T>* nodeToRemove = temp->next;
        temp->next = temp->next->next;
        delete nodeToRemove;
    }

    // Print the list
    void print() {
        node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        while (head != nullptr) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    T lfirst() {
        if (head == nullptr) {
            throw std::runtime_error("lfirst() called on empty list");
        }
        node<T>* temp = head;
        head = head->next;
        T value = std::move(temp->data);
        delete temp;
        return value;
    }

    T last() {
        if (head == nullptr) {
            throw std::runtime_error("last() called on empty list");
        }

        if (head->next == nullptr) {
            T value = std::move(head->data);
            delete head;
            head = nullptr;
            return value;
        }

        node<T>* prev = nullptr;
        node<T>* cur  = head;
        while (cur->next != nullptr) {
            prev = cur;
            cur  = cur->next;
        }
        prev->next = nullptr;
        T value = std::move(cur->data);
        delete cur;
        return value;
    }
    void addOrder(const T& value) {
        node<T>* newNode = new node<T>(value);

        if (head == nullptr || !(head->data < value)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        node<T>* cur = head;
        while (cur->next != nullptr && cur->next->data < value) {
            cur = cur->next;
        }

        newNode->next = cur->next;
        cur->next = newNode;
    }
};

int main() {
    LinkedList<int> list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);

    std::cout << "Linked List: ";
    list.print();

    list.remove(2);
    std::cout << "After remove: ";
    list.print();

    list.lfirst();
    std::cout << "After lfirst: ";
    list.print();

    list.last();
    std::cout << "After last: ";
    list.print();

    list.addOrder(10);
    std::cout << "After addOrder: ";

    list.print();

    return 0;
}
