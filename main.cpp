#include <iostream>
using namespace std;

void insertIntoMiddle(int value, int pos) {
    // Создаем новый узел
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    newNode->node_mutex = new mutex();

    
        // Захватываем глобальную блокировку очереди
        queue_mutex->lock();

    // Перемещаемся на позицию pos - 1
    Node* current = head;
    int count = 0;
    while (current->next && count < pos - 1) {
        current = current->next;
        count++;
    }

    // Если позиция pos больше длины списка, вставляем элемент в конец
    if (count < pos - 1) {
        current->next = newNode;
    }
    else {
        // Захватываем блокировку текущего узла и следующего за ним
        current->node_mutex->lock();
        Node* nextNode = current->next;
        nextNode->node_mutex->lock();

        // Вставляем новый узел в середину списка
        newNode->next = nextNode;
        current->next = newNode;

        // Освобождаем блокировки
        nextNode->node_mutex->unlock();
        current->node_mutex->unlock();
    }

    // Освобождаем глобальную блокировку очереди
    queue_mutex->unlock();
}
