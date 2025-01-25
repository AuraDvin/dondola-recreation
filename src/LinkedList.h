#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstdint>

//TODO:
// * Fix the iterator ig
// * idk what's wrong with it it seems to be written just fine

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
            start = new Node<T>;
            start->val = x;
            start->next = nullptr;
            return;
        }

        Node<T> *tmp = start;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new Node<T>;
        tmp->next->val = x;
        tmp->next->next = nullptr;
    }

    Node<T> *find(T x) {
        if (start == nullptr) {
            return nullptr;
        }

        if (start.val == x) {
            return start;
        }

        Node<T> *prev = findPrev(x);
        if (prev != nullptr) return prev->next;
        return nullptr;
    }


    void remove(T x) {
        Node<T> *tmp = find(x);
        if (tmp == nullptr) return;
        if (tmp == start) {
            start = start->next;
            delete tmp;
            length--;
            return;
        }
        Node<T> *prev = findPrev(x);
        prev->next = tmp->next;
        delete tmp;
        length--;
    }

    Node<T> *getStart() { return start; }

    class Iterator {
        Node<T> *current;

    public:
        explicit Iterator(Node<T> *start) : current(start) {
        }

        T &operator*() { return current->val; }

        Iterator &operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator &other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(start); }
    Iterator end() { return Iterator(nullptr); }


private:
    Node<T> *findPrev(T x) {
        return findHelper(x, start);
    }

    Node<T> *findHelper(T x, Node<T> &node) {
        while (node != nullptr) {
            if (node.next == nullptr) return nullptr;
            if (node.next->val == x) return &node;
            node = node.next;
        }
        return nullptr;
    }
};


#endif //LINKEDLIST_H
