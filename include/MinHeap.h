//
// Created by nimsolated on 5/25/2025.
//

#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdexcept>

template <typename T>
class MinHeap {
public:
    MinHeap() :
        m_heapArray(new T[3]),
        m_capacity(3) {
    }
    MinHeap(const MinHeap& other) :
        m_heapArray(new T[other.m_capacity]),
        m_capacity(other.m_capacity),
        m_nextIdx(other.m_nextIdx) {

        for (size_t i = 0; i < other.m_nextIdx; i++) {
            m_heapArray[i] = other.m_heapArray[i];
        }
    }
    MinHeap& operator=(const MinHeap& other) {
        if (this != &other) {
            delete[] m_heapArray;
            m_capacity = other.m_capacity;
            m_nextIdx = other.m_nextIdx;
            m_heapArray = new T[m_capacity];
            for (size_t i = 0; i < m_nextIdx; i++) {
                m_heapArray[i] = other.m_heapArray[i];
            }
        }
        return *this;
    }
    ~MinHeap() {
        delete[] m_heapArray;
    }

    [[nodiscard]] bool isEmpty() const {
        return m_nextIdx == 0;
    }
    [[nodiscard]] size_t size() const {
        return m_nextIdx;
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty!");
        }
        return m_heapArray[0];
    }
    void insert(const T& data) {
        if (m_nextIdx >= m_capacity) {
            realloc();
        }

        m_heapArray[m_nextIdx] = data;
        m_nextIdx++;

        siftup(m_nextIdx - 1);
    }
    void remove() {
        if (m_nextIdx == 0) {
            return; // the heap is empty
        }

        m_heapArray[0] = m_heapArray[m_nextIdx - 1];
        m_nextIdx--;

        siftdown(0);
    }
private:
    void realloc() {
        m_capacity *= 2;
        T *newHeapArray = new T[m_capacity];
        for (size_t i = 0; i < m_nextIdx; i++) {
            newHeapArray[i] = m_heapArray[i];
        }
        delete[] m_heapArray;
        m_heapArray = newHeapArray;
    }
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    void siftup(const size_t idx) {
        if (idx == 0) {
            return;
        }
        size_t parentIdx = (idx - 1) / 2;
        if (m_heapArray[parentIdx] > m_heapArray[idx]) {
            swap(m_heapArray[parentIdx], m_heapArray[idx]);
            siftup(parentIdx);
        }
    }
    void siftdown(const size_t idx) {
        size_t leftChildIdx = 2 * idx + 1;
        size_t rightChildIdx = 2 * idx + 2;

        if (leftChildIdx >= m_nextIdx) {
            return; // no children
        }

        size_t smallestChildIdx = leftChildIdx;
        if (rightChildIdx < m_nextIdx && m_heapArray[rightChildIdx] < m_heapArray[leftChildIdx]) {
            smallestChildIdx = rightChildIdx;
        }
        if (m_heapArray[smallestChildIdx] < m_heapArray[idx]) {
            swap(m_heapArray[smallestChildIdx], m_heapArray[idx]);
            siftdown(smallestChildIdx);
        }
    }
private:
    T *m_heapArray;
    size_t m_capacity{};
    size_t m_nextIdx{};
};

#endif //MINHEAP_H
