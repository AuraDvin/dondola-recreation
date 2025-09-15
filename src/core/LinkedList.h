#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstdint>
#include <iostream>

template<typename T>
struct Node {
    T val;
    Node *next = nullptr;
};

template<typename T>
class LinkedList {
    Node<T> *start = nullptr;
    uint32_t length = 0;

public:
    ~LinkedList() {
        while (pop());
    }

    bool pop() {
        if (start == nullptr) return false;
        const Node<T> *tmp = start;
        start = start->next;
        delete tmp;
        length--;
        return true;
    }

    void add(T x) {
        length++;
        if (start == nullptr) {
            start = new Node<T>{x, nullptr};
            return;
        }

        Node<T> *tmp = start;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new Node<T>{x, nullptr};
    }

    Node<T> *find(T x) {
        Node<T> *current = start;
        while (current != nullptr) {
            if (current->val == x) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(T x) {
        if (start == nullptr) return;

        if (start->val == x) {
            const Node<T> *tmp = start;
            start = start->next;
            delete tmp;
            length--;
            return;
        }

        Node<T> *prev = nullptr;
        Node<T> *current = start;
        while (current != nullptr && current->val != x) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) return; // Not found

        prev->next = current->next;
        delete current;
        length--;
    }

    Node<T> *getStart() { return start; }

    class Iterator {
        Node<T> *current;

    public:
        explicit Iterator(Node<T> *start) : current(start) {}

        T &operator*() { return current->val; }

        Iterator &operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(start); }
    Iterator end() { return Iterator(nullptr); }

    void update(const float dt) {
        for (auto &item : *this) {
            item.update(dt);
        }
    }

    void render(sf::RenderWindow &window) {
        for (auto &item : *this) {
            item.render(&window);
        }
    }
};

#endif //LINKEDLIST_H
