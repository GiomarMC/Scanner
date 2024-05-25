#include <iostream>

// Definicion del nodo de la lista
struct Node {
    int data;   // Valor del nodo
    Node* next; // Puntero al siguiente nodo

    Node(int data) : data(data), next(nullptr) {} // Constructor para inicializar el nodo
};

// Clase de la lista enlazada
class LinkedList {
private:
    Node* head; // Puntero al primer nodo de la lista

public:
    LinkedList() : head(nullptr) {} // Constructor para inicializar la lista vacía

    // Método para agregar un nodo al final de la lista
    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Método para imprimir la lista
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Método para eliminar un nodo por valor
    void deleteNode(int key) {
        Node* temp = head;
        Node* prev = nullptr;

        // Si el nodo a eliminar es el nodo principal
        if (temp != nullptr && temp->data == key) {
            head = temp->next;
            delete temp;
            return;
        }

        // Buscar el nodo a eliminar, manteniendo el anterior nodo
        while (temp != nullptr && temp->data != key) {
            prev = temp;
            temp = temp->next;
        }

        // Si no se encontró el nodo
        if (temp == nullptr) return;

        // Desconectar el nodo del enlace de la lista
        prev->next = temp->next;
        delete temp;
    }

    // Destructor para liberar la memoria
    ~LinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

// Función principal para probar la lista enlazada
int main() {
    LinkedList list;

    // Agregar nodos a la lista
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    // Imprimir la lista
    std::cout << "Lista enlazada: ";
    list.printList();

    // Eliminar un nodo
    list.deleteNode(3);
    std::cout << "Lista enlazada después de eliminar 3: ";
    list.printList();

    return 0;
}