
namespace dsa {
    template <typename T>
    int Graph<T>::add_vertex(T data) {
        auto id = this->_id_manager.next();
        this->_v_data.emplace(id, std::move(data));
        this->_vertices.emplace(id, Vertex());
        this->_modified = true;
        return id;
    }
    template <typename T>
    void Graph<T>::add_edge(int id_source, int id_target) {
        if (this->_vertices.contains(id_source) && 
            this->_vertices.contains(id_target)
        ) {
            this->_vertices.at(id_source).out_edges.emplace(id_target);
            this->_vertices.at(id_target).in_edges.emplace(id_source);
            this->_modified = true;
        }
    }
    template <typename T>
    void Graph<T>::update_vertex_data(int id, T data) {
        if (this->_v_data.contains(id)) {
            this->_v_data.emplace(id, data);
            this->_modified = true;
        }
    }
    template <typename T>
    void Graph<T>::remove_vertex(int id) {
        if (this->_vertices.contains(id)) {
            this->_id_manager.recycle(id);
            this->_v_data.erase(id);
            this->_vertices.erase(id);
            this->_modified = true;
        }
    }
    template <typename T>
    void Graph<T>::remove_edge(int id_source, int id_target) {
        if (this->_vertices.contains(id_source) && 
            this->_vertices.contains(id_target)
        ) {
            // edge does not exist
            if (!this->_vertices.at(id_source).out_edges.contains(id_target) &&
                !this->_vertices.at(id_target).in_edges.contains(id_source)
            ) {
                return;
            }
            this->_vertices.at(id_source).out_edges.erase(id_target);
            this->_vertices.at(id_target).in_edges.erase(id_source);
            this->_modified = true;
        }
    }
    template <typename T>
    const std::vector<int>& Graph<T>::find_path(int id_source, int id_target) {
        static auto result = std::vector<int>();
        if (!_modified) {
            return result;
        }
        return result;
    }

    template <typename T>
    bool Graph<T>::cycle_test() {
        if (!this->_modified) {
            return this->_cycle_test;
        }

        enum class DFSState : uint8_t {
            Unvisited,
            Visiting,
            Finished
        };

        struct DFSFrame final {
            int vertex;
            bool exiting;
        };

        this->_modified = false;
        this->_cycle_test = false;

        std::unordered_map<int, DFSState> states;
        std::vector<DFSFrame> v_stack;

        states.reserve(this->_vertices.size());
        v_stack.reserve(this->_vertices.size());

        for (const auto& [v, vertex] : this->_vertices) {
            if (states[v] != DFSState::Unvisited) {
                continue;
            }

            v_stack.emplace_back(v, false);

            while (!v_stack.empty()) {
                const auto frame = v_stack.back();
                v_stack.pop_back();

                const auto this_v = frame.vertex;

                // end of single dfs recursion
                if (frame.exiting) {
                    states[this_v] = DFSState::Finished;
                    continue;
                }

                // cut dfs against processed subgraph
                if (states[this_v] == DFSState::Finished) {
                    continue;
                }

                // revisit in same dfs
                if (states[this_v] == DFSState::Visiting) {
                    this->_cycle_test = true;
                    goto END_OF_CYCLE_TEST;
                }

                states[this_v] = DFSState::Visiting;

                v_stack.emplace_back(this_v, true);

                const auto& this_vertex = this->_vertices.at(this_v);

                for (const auto next_v : this_vertex.out_edges) {
                    const auto next_state = states[next_v];

                    if (next_state == DFSState::Visiting) {
                        this->_cycle_test = true;
                        goto END_OF_CYCLE_TEST;
                    }

                    if (next_state == DFSState::Unvisited) {
                        v_stack.emplace_back(next_v, false);
                    }
                }
            }
        }

    END_OF_CYCLE_TEST: {}
    return this->_cycle_test;
    }

}