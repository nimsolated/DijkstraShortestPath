//
// Created by nimsolated on 5/25/2025.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

namespace Graph {
    template <typename T>
    struct Vertex {
        T m_data;

        Vertex() : m_data(T()) {}
        explicit Vertex(const T& data) : m_data(data) {}
    };
    template <typename T>
    struct Edge {
        Vertex<T>* m_from;
        Vertex<T>* m_to;
        size_t m_weight;

        Edge() : m_from(nullptr), m_to(nullptr), m_weight(0) {}
        explicit Edge(const size_t weight) : m_from(nullptr), m_to(nullptr), m_weight(weight) {}
        ~Edge() {
            delete m_from;
            delete m_to;
        }
    };

    template <typename T>
    class DirectGraph {
    public:
        DirectGraph() = default;
        DirectGraph(const DirectGraph& other) {
            for (auto edge : other.m_edges) {
                m_edges.push_back(new Edge<T>(*edge));
            }
        }
        DirectGraph& operator=(const DirectGraph& other) {
            if (this != &other) {
                for (auto edge : other.m_edges) {
                    m_edges.push_back(new Edge<T>(*edge));
                }
            }
            return *this;
        }
        ~DirectGraph() {
            for (auto edge : m_edges) {
                delete edge;
            }
        }

        void addEdge(const Vertex<T>* from, const Vertex<T>* to, const size_t weight) {
            auto* newEdge = new Edge<T>(weight);
            newEdge->m_from = from;
            newEdge->m_to = to;
            m_edges.emplace_back(newEdge);
        }
    private:
        std::vector<Edge<T>*> m_edges;
    };
}

#endif //GRAPH_H
