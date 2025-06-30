//
// Created by ����Դ on 24-10-13.
//
#include "Algorithm.h"
#include<queue>
#include<climits>
#include<stack>
#include<unordered_map>

namespace Graph {
    namespace Algorithm {
        std::list<Vertex> GetCircuit(LGraph& graph, Vertex start) {
            //TODO:�Ӹ�����������һ����·
                std::list<Vertex> circuit;
                if (!graph.exist_vertex(graph.Map_re().at(start))) {
                    return circuit;
                }

                // ʹ�ñ߷��ʱ�Ƕ�����ɾ��
                using EdgeMark = std::pair<Vertex, Vertex>;
                std::set<EdgeMark> visitedEdges;

                auto markEdge = [&](Vertex u, Vertex v) {
                    if (graph.directed) {
                        visitedEdges.insert({ u, v });
                    }
                    else {
                        // ����ͼ��Ҫ�����������
                        visitedEdges.insert({ u, v });
                        visitedEdges.insert({ v, u });
                    }
                    };

                auto isEdgeVisited = [&](Vertex u, Vertex v) {
                    return visitedEdges.count({ u, v }) > 0;
                    };

                std::stack<Vertex> stack;
                stack.push(start);

                while (!stack.empty()) {
                    Vertex current = stack.top();
                    bool found = false;

                    // ���ҵ�һ��δ���ʵ��ڱ�
                    for (auto& edge : graph.List()[current].adj) {
                        if (!isEdgeVisited(current, edge.dest)) {
                            markEdge(current, edge.dest);
                            stack.push(edge.dest);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        circuit.push_front(current);
                        stack.pop();
                    }
                }

                return circuit;
            

            //std::cerr << "GetCircuit ��ûʵ��" << std::endl;
            //return {};
        }

        std::list<Vertex> EulerCircle(const LGraph& graph) {
            //TODO:��ȡŷ����·,�����ʹ��GetCircuit����
                std::list<Vertex> eulerCircuit;

                if (!HaveEulerCircle(const_cast<LGraph&>(graph))) {
                    return eulerCircuit;
                }

                // ʹ�ñ߷��ʱ��ϵͳ
                using EdgeMark = std::pair<Vertex, Vertex>;
                std::set<EdgeMark> visitedEdges;

                auto markEdge = [&](Vertex u, Vertex v) {
                    if (graph.directed) {
                        visitedEdges.insert({ u, v });
                    }
                    else {
                        visitedEdges.insert({ u, v });
                        visitedEdges.insert({ v, u });
                    }
                    };

                auto isEdgeVisited = [&](Vertex u, Vertex v) {
                    return visitedEdges.count({ u, v }) > 0;
                    };

                // ѡ����ʼ����
                Vertex start = 0;
                const auto& list = graph.List();

                if (!graph.directed) {
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (list[i].adj.size() % 2 != 0) {
                            start = i;
                            break;
                        }
                    }
                }
                else {
                    std::unordered_map<Vertex, int> inDegree, outDegree;
                    for (size_t i = 0; i < list.size(); ++i) {
                        for (const auto& edge : list[i].adj) {
                            outDegree[i]++;
                            inDegree[edge.dest]++;
                        }
                    }
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (outDegree[i] > inDegree[i]) {
                            start = i;
                            break;
                        }
                    }
                }

                std::stack<Vertex> stack;
                stack.push(start);

                while (!stack.empty()) {
                    Vertex current = stack.top();
                    bool found = false;

                    // ���ҵ�һ��δ���ʵ��ڱ�
                    for (auto& edge : list[current].adj) {
                        if (!isEdgeVisited(current, edge.dest)) {
                            markEdge(current, edge.dest);
                            stack.push(edge.dest);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        eulerCircuit.push_front(current);
                        stack.pop();
                    }
                }

                return eulerCircuit;
            
            //std::cerr << "EulerCircle ��ûʵ��" << std::endl;
            //return {};
        }

        bool HaveEulerCircle( LGraph& graph) {
            //TODO:�ж��Ƿ���ŷ����·
            if (!IsConnected(graph)) { return false; }
            const auto& adj = graph.List();
            if(!graph.directed){
                for (const auto& node : adj) {
                    if (node.adj.size() % 2 != 0) {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                const std::vector<EdgeNode>edge{ graph.Edge() };
                //std::unordered_map<int, std::vector<int>> adj;
                std::unordered_map<int, int> inDegree(graph.VertexCount()), outDegree(graph.VertexCount());
                for (auto &e : edge) {
                    inDegree[e.from]++;
                    outDegree[e.dest]++;
                }
                for (int i = 0; i < graph.VertexCount();i++) {
                    if (inDegree[i] != outDegree[i]) {
                        return false;
                    }
                }
                return true;
            }
            //std::cerr << "HaveEulerCircle ��ûʵ��" << std::endl;
            //return false;
        }
        std::vector<int> DFSv(LGraph& graph, Vertex v, std::vector<bool>& visited) {
            const std::map<Vertex, std::string> id_v{ graph.Map_re() };
            std::vector<int> out;
            std::cout << id_v.at(v)<< std::endl;
            out.push_back(v);
            visited[v] = 1;
            std::vector<HeadNode> v_list{ graph.List() };
            for (auto &x :v_list.at(v).adj) {
                if (!visited[x.dest]) {
                    DFSv(graph, x.dest,visited);
                    // cout << s << ' ';
                    // ������
                }
            }
            return out;
        }
        std::vector<int> BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited) {//vΪ������
            //TODO:���������������ͼ
            std::vector<HeadNode> adj{ graph.List() };
            const std::map<Vertex, std::string> id_v{ graph.Map_re() };
            std::queue<int> q; // ��������BFS
            visited[v] = true;
            std::vector<int> result;
            q.push(v);
            int s = v;
            while (!q.empty()) {
                s = q.front();
                result.push_back(s);
                std::cout << "Visited: " << id_v.at(s) << std::endl;
                q.pop(); 
                for (auto &adjacent : adj[s].adj) {
                    if (!visited[adjacent.dest]) {
                        visited[adjacent.dest] = true;
                        q.push(adjacent.dest);
                    }
                }
            }
            //std::cerr << "BFSv ��ûʵ��" << std::endl;
            return result;
        }

        bool IsConnected(LGraph& graph) {
            //TODO:�ж�ͼ�Ƿ���ͨ
            const std::vector<EdgeNode>edge{ graph.Edge() };
            DSU p(graph.VertexCount());
            for (auto &e : edge) {
                p.unite(e.from, e.dest);
            }
            int a = p.find_p(0);
            for (int i = 1; i < graph.VertexCount(); i++) {
                if (!p.same(a, p.find_p(i))) { return false; }
            }
            return true;
            //std::cerr << "IsConnected ��ûʵ��" << std::endl;
            //return false;
        }
        void printPath(const std::vector<int>& prev, int dest, const std::map<Vertex, std::string> id_name) {
            std::vector<int> path;
            for (int v = dest; v != -1; v = prev[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());

            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << id_name.at(path[i]);
            }
        }

        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x, const std::string& vertex_name_y) {
            auto v_id = graph.Map();
            int src = v_id.at(vertex_name_x);
            int dest = v_id.at(vertex_name_y);
            int V = graph.VertexCount();
            std::vector<int> dist(V, std::numeric_limits<int>::max());
            std::vector<int> prev(V, -1);
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
            const std::map<Vertex, std::string> id_name{ graph.Map_re() };
            dist[src] = 0;
            pq.push({ 0, src });

            while (!pq.empty()) {
                int u = pq.top().second;
                pq.pop();

                if (u == dest) break; // ����ҵ���Ŀ��ڵ㣬����ǰ�˳�

                for (const auto& edge : graph.Edge()) {
                    if (edge.from != u) continue;
                    int v = edge.dest;
                    int weight = edge.weight;
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                        pq.push({ dist[v], v });
                    }
                }
            }

            std::cout << vertex_name_x << "��" << vertex_name_y << "֮�����̾���Ϊ��" << dist[dest] << std::endl;
            std::cout << "·��Ϊ��";
            printPath(prev, dest,id_name);
            std::cout << std::endl;

            return dist[dest];
        }


        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //TODO:��ȡ�������޵����·������������path����

            std::unordered_map<std::string, int> dist; // �洢ÿ���ڵ����̾���
            std::map<std::string, Vertex> v_id{ graph.Map() };
            const std::map<Vertex, std::string> id_v{ graph.Map_re() };
            // ��ʼ�������нڵ�ľ���Ϊ�����
            for (const auto& node : path) {
                dist[node] = INT_MAX;
            }

            // ������Ϊ0
            dist[path[0]] = 0;

            // �����û�����������˳���ɳ�ÿ����
            for (const auto& u : path) {
                int uu = v_id[u];
                if (dist[u] == INT_MAX) continue; // ���ɴ�ڵ�����
                const std::vector<HeadNode> verlist{ graph.List() };
                for (const auto& edge : verlist.at(uu).adj) {
                   
                    const auto& vv = edge.dest;
                    int weight = edge.weight;
                    std::string v = id_v.at(vv);
                    // �ɳڲ���
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }

            // ���ش���㵽�յ�����·������
            if (dist[path.back()] == INT_MAX) {
                std::cerr << "�޷������յ�" << std::endl;
                return -1;
            }
            return dist[path.back()];
            //std::cerr << "TopologicalShortestPath ��ûʵ��" << std::endl;
            //return -1;
        }

        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            //TODO:������С�����������������ϵı�
            std::vector<EdgeNode> edges0{ graph.SortedEdges() };
            std::priority_queue<EdgeNode> roads;
                for (int i = 1; i <= edges0.size(); i++) {
                  //����ͼȥ�ش���
                    //if (!graph.directed &&i % 2 == 0) { continue; }
                    //����ȥ�أ��ϲ�ʱ�����Ѿ����ӹ��Ļ��Զ�����
                    roads.push(edges0[i-1]);
                }
                //edges0.clear();
            
            int n = graph.VertexCount();
            DSU p(n);
           
            std::vector<EdgeNode> mst;
            while (!roads.empty()) {
                EdgeNode x = roads.top();
                if (p.find_p(x.dest) != p.find_p(x.from)) {
                    p.unite(x.dest, x.from);
                    mst.push_back(x);
                }
                roads.pop();
                if (mst.size() == n-1) {
                    break;
                }
            }
            return mst;
            //std::cerr << "MinimumSpanningTree ��ûʵ��" << std::endl;
            //return {};
        }
    }
}
//�������·��
/*void printPath(const std::vector<std::vector<int>>& next, int u, int v) {
    if (u == v) {
        std::cout << u;
        return;
    }
    if (next[u][v] == -1) {
        std::cout << "��·��";
        return;
    }

    std::cout << u;
    while (u != v) {
        u = next[u][v];
        std::cout << "->" << u;
    }
}*/

//int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x, const std::string& vertex_name_y) {
//    //TODO:��ȡ����֮������·��
//    int V = graph.VertexCount();
//    std::vector<std::vector<int>> next(V, std::vector<int>(V, -1));

//    // ��ʼ��next���󣨿ռ��Ż���ֱ��ʹ��graph��Ϊdist����
//    int INF = INT_MAX;
//    std::vector<std::vector<int>> g(V, std::vector<int>(V,INF));
//    const std::vector<EdgeNode> edges{graph.Edge()};
//    const std::map< std::string, Vertex>v_id{ graph.Map()};
//    for (auto e : edges) {
//        if (g[e.from][e.dest] == INF) {
//            g[e.from][e.dest] = e.weight;
//        }
//        else
//        {
//            if(g[e.from][e.dest]>e.weight){ g[e.from][e.dest] = e.weight; }
//        }
//    }
//    for (int i = 0; i < V; i++) {
//        for (int j = 0; j < V; j++) {
//            if (g[i][j] != INF && i != j) {
//                next[i][j] = j;
//            }
//        }
//    }
//    for (int k = 0; k < V; k++) {
//        for (int i = 0; i < V; i++) {
//            // ��ǰ��ֹ�Ż������i��k���ɴ�������
//            if (g[i][k] == INF) continue;

//            for (int j = 0; j < V; j++) {
//                // �ռ��Ż���ֱ��ʹ��graph����
//                if (g[k][j] != INF && g[i][j] > g[i][k] + g[k][j]) {
//                    g[i][j] = g[i][k] + g[k][j];
//                    next[i][j] = next[i][k];
//                }
//            }
//        }
//    }
//    std::cout << vertex_name_x << "��" << vertex_name_y << "֮�����̾���Ϊ��"<< g[v_id.at(vertex_name_x)][v_id.at(vertex_name_y)];
//    std::cout << std::endl<<"·��Ϊ��";

//    printPath(next, v_id.at(vertex_name_x), v_id.at(vertex_name_y));
//    std::cout <<std:: endl;
//    //std::cerr << "GetShortestPath ��ûʵ��" << std::endl;
//    return -1;
//}