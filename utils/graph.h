#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <string>


template <class T>
class graph {
    public:
        std::map<T, std::set<std::pair<int, T>>> g;
    public:
        graph() : g{} {}
        
        void add_edge(T src, T dest, int weight = 1) {
            auto it = g.find(src);
            if (it == g.end()) {
                std::set<std::pair<int, T>> s{};
                s.insert(std::pair<int, T>(weight, dest));
                g.insert(std::pair<T, std::set<std::pair<int, T>>>(src, s));
            } else {
                it->second.insert(std::pair<int, T>(weight, dest));
            }
        }

        bool path_exists(T src, T dest, std::set<T> known_connected = std::set<T>()) {
            auto it = g.find(src);
            if (it == g.end()) {
                return false;
            } else {
                bool path = false;
                for (std::pair<int, T> edge : it->second) {
                    if (path || edge.second == dest || known_connected.find(edge.second) != known_connected.end()) {
                        known_connected.insert(src);
                        return true;
                    } else {
                        path = path_exists(edge.second, dest, known_connected);
                    }
                }
                if (path) {
                    known_connected.insert(src);
                }
                return path;
            }
        }

        int contents(T root) {
            int total_contained = 0;
            auto it = g.find(root);
            if (it != g.end()) {
                for (std::pair<int, T> holding : it->second) {
                    total_contained += holding.first;
                    total_contained += holding.first * contents(holding.second);
                }
            }
            return total_contained;
        }

        int count_bottom_nodes(T node_val = NULL) {
            int count = 0;
            for (std::pair<T, std::set<std::pair<int, T>>> p : g) {
                for (std::pair<int, T> v : p.second) {
                    if (g.find(v.second) == g.end() && (node_val == NULL || v.second == node_val)) {
                        ++count;
                    }
                }
            }
            return count;
        }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const graph<T>& __g) {
    std::cout << "{" << std::endl;
    for (std::pair<T, std::set<std::pair<int, T>>> p : __g.g) {
        std::cout << "    " << p.first << " : [";
        for (std::pair<int, T> v : p.second) {
            std::cout << v.second << " (" << v.first << "), ";
        }
        std::cout << "]," << std::endl;
    }
    std::cout << "}";
    return std::cout;
}

# endif
