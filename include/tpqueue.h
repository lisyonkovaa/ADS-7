// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
        Item* previous;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);

 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Queue is Empty!");
    } else {
        Item* temporary = head->next;
        T data = head->data;
        delete head;
        head = temporary;
        return data;
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* items = new Item;
    items->data = data;
    items->next = nullptr;
    items->previous = nullptr;
    return items;
}

template <typename T>
void TPQueue<T>::print() const {
    Item* temporary = head;
    while (temporary) {
        std::cout << temporary->data << " ";
        temporary = temporary->next;
    }
    std::cout << std::endl;
}

template <typename T>
void TPQueue<T>::push(const T& d) {
    if (head == nullptr) {
        head = create(d);
        tail = head;
    } else if (tail->data.prior >= d.prior) {
        if (tail->data.ch == d.ch) {
            tail->data = d;
        } else {
            tail->next = create(d);
            tail->next->previous = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->previous = create(d);
        head = tail->previous;
        head->next = tail;
    } else {
        Item* temporary = tail;
        while (temporary != head && temporary->data.prior < d.prior) {
            temporary = temporary->previous;
        }
        if (temporary->data.prior > d.prior) {
            Item* cell = new Item;
            cell->next = temporary->next;
            cell->previous = temporary;
            cell->data = d;
            temporary->next->previous = cell;
            temporary->next = cell;
        }
        if (temporary == head && temporary->data.prior < d.prior) {
            head->previous = create(d);
            head = head->previous;
            head->next = temporary;
        }
    }
}

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
