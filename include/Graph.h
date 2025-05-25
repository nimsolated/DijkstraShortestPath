//
// Created by nimsolated on 5/25/2025.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <stdexcept>
#include <unordered_map>
#include <algorithm>
#include <vector>

namespace Graph {
    template <typename T>
    struct Vertex {
        T m_data;
        size_t m_id;

        Vertex(const T& data, const size_t id) :
            m_data(data),
            m_id(id) {
        }
    };
    struct Edge {
        size_t m_fromId;
        size_t m_toId;
        size_t m_weight;

        Edge(const size_t from, const size_t to, const size_t weight) :
            m_fromId(from),
            m_toId(to),
            m_weight(weight) {
        }
    };

    template <typename T>
    class DirectedGraph {
    public:
        DirectedGraph() = default;
        DirectedGraph(const DirectedGraph& other) = default;
        DirectedGraph& operator=(const DirectedGraph& other) = default;
        ~DirectedGraph() = default;

        // Add a vertex to the graph
        size_t addVertex(const T& data) {
            size_t id = m_nextVertexId++;
            m_vertices[id] = Vertex<T>(data, id);
            m_adjacencyList[id] = std::vector<Edge>();
            return id;
        }

        // Add an edge between two vertices with a specified weight
        void addEdge(const size_t from, const size_t to, const size_t weight) {
            if (!hasVertex(from) || !hasVertex(to)) {
                throw std::runtime_error("Vertex does not exist!");
            }

            Edge edge(from, to, weight);
            m_adjacencyList[from].push_back(edge);
        }

        // Check if a vertex exists in the graph
        bool hasVertex(const size_t id) const {
            return m_vertices.contains(id) != m_vertices.end();
        }

        // Get all outgoing edges from a vertex
        const std::vector<Edge>& getOutgoingEdges(const size_t vertexId) const {
            const auto it = m_adjacencyList.find(vertexId);
            if (it == m_adjacencyList.end()) {
                throw std::runtime_error("Vertex not found!");
            }
            return it->second;
        }

        // Get all vertex IDs in the graph
        std::vector<size_t> getVertexIds() const {
            std::vector<size_t> ids;
            ids.reserve(m_vertices.size());
            for (const auto& pair : m_vertices) {
                ids.emplace_back(pair.first);
            }
            return ids;
        }

        // Get a count of vertices in the graph
        size_t getVertexCount() const {
            return m_vertices.size();
        }

        // Remove a vertex and all of its edges from the graph
        void removeVertex(const size_t id) {
            if (!hasVertex(id)) {
                throw std::runtime_error("Vertex does not exist!");
            }

            for (auto& pair : m_adjacencyList) {
                auto& edges = pair.second;
                edges.erase(
                    std::remove_if(
                        edges.begin(),
                        edges.end(),
                        [id](const Edge& e)->bool {
                            return e.m_toId == id;
                        }),
                    edges.end()
                );
            }

            m_adjacencyList.erase(id);
            m_vertices.erase(id);
        }

        // Remove an edge
        void removeEdge(const size_t from, const size_t to) {
            if (!hasVertex(from)) {
                throw std::runtime_error("Source vertex does not exist!");
            }

            auto& edges = m_adjacencyList[from];
            edges.erase(
                std::remove_if(
                    edges.begin(),
                    edges.end(),
                    [to](const Edge& e)->bool {
                        return e.m_toId == to;
                    }),
                edges.end()
            );
        }
    private:
        std::unordered_map<size_t, Vertex<T>> m_vertices;
        std::unordered_map<size_t, std::vector<Edge>> m_adjacencyList;
        size_t m_nextVertexId = 0;
    };
}

#endif //GRAPH_H
