#pragma once
#include "IdGenerator.hpp"
#include "macros.h"
#include <unordered_set>
#include <unordered_map>

namespace dsa {
    
    struct Vertex final {
        std::unordered_set<int> in_edges;
        std::unordered_set<int> out_edges;
    };

    template <typename T>
    class Graph final {
    private:
        std::unordered_map<int, T> _v_data;
        std::unordered_map<int, Vertex> _vertices;
        IdGenerator _id_manager;

        bool _modified = true;
        bool _cycle_test = false;
    public:
        // returns id of vertex
        [[nodiscard]]
        int add_vertex(T data);
        // there should not be repetition
        void add_edge(int id_source, int id_target);
        void update_vertex_data(int id, T data);
        void remove_vertex(int id);
        void remove_edge(int id_source, int id_target);
        // returns list of id from source to target, including source and target
        const std::vector<int>& find_path(int id_source, int id_target);

        bool cycle_test();
    };
}

#include "Graph.inl"