#include "../include/Graph.h"
#include "../include/Stack.h"
#include "../include/MinHeap.h"
#include <iostream>
#include <limits>

struct DistanceEntry {
    size_t m_vertexID;
    size_t m_distance;

    DistanceEntry() : m_vertexID(0), m_distance(0) {}
    DistanceEntry(const size_t id, const size_t dist) : m_vertexID(id), m_distance(dist) {}

    bool operator<(const DistanceEntry& other) const {
        return m_distance < other.m_distance;
    }
    bool operator>(const DistanceEntry& other) const {
        return m_distance > other.m_distance;
    }
    bool operator==(const DistanceEntry& other) const {
        return m_distance == other.m_distance;
    }
    bool operator!=(const DistanceEntry& other) const {
        return m_distance != other.m_distance;
    }
};

template <typename T>
std::vector<size_t> dijkstra(
    const Graph::DirectedGraph<T>& graph,
    const size_t sourceID,
    const size_t targetID
    ) {

    if (!graph.hasVertex(sourceID) || !graph.hasVertex(targetID)) {
        throw std::runtime_error("Source or target vertex does not exist!");
    }

    std::vector<size_t> vertexIDs = graph.getVertexIds();

    constexpr size_t INFINITY = std::numeric_limits<size_t>::max();
    std::unordered_map<size_t, size_t> distances;
    std::unordered_map<size_t, size_t> previous;

    for (size_t id : vertexIDs) {
        distances[id] = INFINITY;
        previous[id] = INFINITY; // in this case, INFINITY indicates "undefined"
    }

    // Distance to source (start point) is always 0
    distances[sourceID] = 0;

    MinHeap<DistanceEntry> priorityQueue;
    priorityQueue.insert(DistanceEntry(sourceID, 0));

    std::unordered_map<size_t, bool> visited;

    // The main loop of dijkstra's algorithm
    while (!priorityQueue.isEmpty()) {
        DistanceEntry curr = priorityQueue.peek();
        priorityQueue.remove();
        size_t currID = curr.m_vertexID;

        // Stops once the target is reached
        if (currID == targetID) {
            break;
        }

        // Skips if already visited
        if (visited[currID]) {
            continue;
        }

        visited[currID] = true;

        const std::vector<Graph::Edge>& edges = graph.getOutgoingEdges(currID);
        for (const Graph::Edge& edge : edges) {
            size_t neighborID = edge.m_toId;

            // Skip neighbors that are already visited
            if (visited[neighborID]) {
                continue;
            }

            // Calculate potential new distance
            if (const size_t newDistance = distances[currID] + edge.m_weight;
                newDistance < distances[neighborID]
                ) {
                distances[neighborID] = newDistance;
                previous[neighborID] = currID;
                priorityQueue.insert(DistanceEntry(neighborID, newDistance));
            }
        }
    }

    std::vector<size_t> path;

    if (previous[targetID] == INFINITY) {
        return path; // Empty path, route doesn't exist
    }

    // Use a stack to find the shortest path
    Stack<size_t> pathStack;

    for (size_t at = targetID; at != INFINITY; at = previous[at]) {
        pathStack.push(at);
        if (at == sourceID) {
            break; // Reached the source
        }
    }

    while (!pathStack.isEmpty()) {
        path.emplace_back(pathStack.pop());
    }

    return path;
}

template <typename T>
void printPath(const std::vector<size_t>& path, const Graph::DirectedGraph<T>& graph) {
    if (path.empty()) {
        std::cout << "No path exists!" << std::endl;
        return;
    }

    std::cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) {
            std::cout << " -> ";
        }
        std::cout << graph.getVertexData(path[i]);
    }
    std::cout << std::endl;
}

int main() {
    // Create a directed graph
    Graph::DirectedGraph<char> graph;

    // Add vertices
    const size_t aID = graph.addVertex('A');
    const size_t bID = graph.addVertex('B');
    const size_t cID = graph.addVertex('C');
    const size_t dID = graph.addVertex('D');
    const size_t eID = graph.addVertex('E');
    const size_t fID = graph.addVertex('F');

    // Add edges
    graph.addEdge(aID, bID, 7); // A -> B: 7
    graph.addEdge(aID, cID, 9);  // A -> C: 9
    graph.addEdge(aID, fID, 14); // A -> F: 14
    graph.addEdge(bID, cID, 10); // B -> C: 10
    graph.addEdge(bID, dID, 15); // B -> D: 15
    graph.addEdge(cID, dID, 11); // C -> D: 11
    graph.addEdge(cID, fID, 2);  // C -> F: 2
    graph.addEdge(dID, eID, 6);  // D -> E: 6
    graph.addEdge(fID, eID, 9);  // F -> E: 9

    // Find the shortest path from A to E

    std::cout << "Shortest path from A to E... " << std::endl;

    try {
        std::vector<size_t> path = dijkstra(graph, aID, eID);
        printPath(path, graph);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}