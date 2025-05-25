//
// Created by nimsolated on 5/25/2025.
//

#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template <typename T>
struct Node {
    T m_data;
    Node* m_next;

    Node() : m_data(T()), m_next(nullptr) {}
    explicit Node(const T& data) : m_data(data), m_next(nullptr) {}
};

template <typename T>
class Stack {
public:
    Stack() : m_top(nullptr), m_bottom(nullptr) {}
    ~Stack() {
        while (m_bottom != nullptr) {
            Node<T>* temp = m_bottom;
            m_bottom = m_bottom->m_next;
            delete temp;
        }
    }

    [[nodiscard]] bool isEmpty() const {
        return !m_bottom;
    }

    void push(const T& data) {
        if (!m_bottom) {
            m_bottom = new Node<T>(data);
            m_top = m_bottom;
        } else {
            m_top->m_next = new Node<T>(data);
            m_top = m_top->m_next;
        }
    }
    T pop() {
        if (!m_top) {
            throw std::runtime_error("Stack is empty!");
        }

        T data;

        if (m_top == m_bottom) {
            data = m_bottom->m_data;
            delete m_bottom;
            m_bottom = nullptr;
            m_top = nullptr;
            return data;
        }

        Node<T>* curr = m_bottom;
        while (curr->m_next != m_top) {
            curr = curr->m_next;
        }
        data = m_top->m_data;
        delete m_top;
        m_top = curr;
        m_top->m_next = nullptr;
        return data;
    }
private:
    Node<T>* m_top;
    Node<T>* m_bottom;
};

#endif //STACK_H
