#include <iostream>

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList(int n) {
        if (n <= 0) {
            head = nullptr;
            size = 0;
            return;
        }
        
        // Create first node
        head = new Node(1);
        Node* current = head;
        
        // Create remaining nodes and link them
        for (int i = 2; i <= n; i++) {
            current->next = new Node(i);
            current = current->next;
        }
        
        // Make it circular by linking last node to head
        current->next = head;
        size = n;
    }
    
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Traverse the circular list and delete all nodes
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
    
    // Get the last node in the list (the one that points to head)
    Node* getLastNode() {
        if (head == nullptr) return nullptr;
        
        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        return current;
    }
    
    // Get current head
    Node* getHead() const {
        return head;
    }
    
    // Remove the node at position m from current start position
    // Returns the value of the removed node
    // The prev pointer is updated to point to the node before the next start position
    int removeAt(Node*& prev, int m) {
        if (head == nullptr || size == 0) return -1;
        
        // Special case: if only one node remains
        if (size == 1) {
            int value = head->data;
            // Don't actually delete it here, let the destructor handle it
            // Just update pointers and size
            head = nullptr;
            size = 0;
            return value;
        }
        
        // Move m-1 steps forward from the current position
        for (int i = 0; i < m - 1; i++) {
            prev = prev->next;
        }
        
        // Node to be deleted is the next node
        Node* toDelete = prev->next;
        int value = toDelete->data;
        
        // If deleting the head node, update head pointer
        if (toDelete == head) {
            head = head->next;
        }
        
        // Remove the node by updating the previous node's next pointer
        prev->next = toDelete->next;
        delete toDelete;
        size--;
        
        return value;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    
    CircularLinkedList list(n);
    
    // Start with the last node as previous, so prev->next is head
    Node* prev = list.getLastNode();
    
    // Remove n nodes (all nodes)
    for (int i = 0; i < n; i++) {
        // Remove the m-th node from current position
        int removedValue = list.removeAt(prev, m);
        std::cout << removedValue << std::endl;
        
        // After deletion, prev is already pointing to the node before the next start position
        // No need to update prev, as it's already correctly positioned
    }
    
    return 0;
}