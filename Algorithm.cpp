//
// Created by 刘凯源 on 24-10-13.
//
#include "Algorithm.h"
#include<queue>
#include<climits>
#include<stack>
#include<unordered_map>

namespace Graph {
    namespace Algorithm {
        std::list<Vertex> GetCircuit(LGraph& graph, Vertex start) {
            //TODO:从给定点出发获得一条回路
                std::list<Vertex> circuit;
                if (!graph.exist_vertex(graph.Map_re().at(start))) {
                    return circuit;
                }

                // 使用边访问标记而不是删除
                using EdgeMark = std::pair<Vertex, Vertex>;
                std::set<EdgeMark> visitedEdges;

                auto markEdge = [&](Vertex u, Vertex v) {
                    if (graph.directed) {
                        visitedEdges.insert({ u, v });
                    }
                    else {
                        // 无向图需要标记两个方向
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

                    // 查找第一个未访问的邻边
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
            

            //std::cerr << "GetCircuit 还没实现" << std::endl;
            //return {};
        }

        std::list<Vertex> EulerCircle(const LGraph& graph) {
            //TODO:获取欧拉回路,你可以使用GetCircuit函数
                std::list<Vertex> eulerCircuit;

                if (!HaveEulerCircle(const_cast<LGraph&>(graph))) {
                    return eulerCircuit;
                }

                // 使用边访问标记系统
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

                // 选择起始顶点
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

                    // 查找第一个未访问的邻边
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
            
            //std::cerr << "EulerCircle 还没实现" << std::endl;
            //return {};
        }

        bool HaveEulerCircle( LGraph& graph) {
            //TODO:判断是否有欧拉回路
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
            //std::cerr << "HaveEulerCircle 还没实现" << std::endl;
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
                    // 带回溯
                }
            }
            return out;
        }
        std::vector<int> BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited) {//v为顶点编号
            //TODO:广度优先搜索整个图
            std::vector<HeadNode> adj{ graph.List() };
            const std::map<Vertex, std::string> id_v{ graph.Map_re() };
            std::queue<int> q; // 队列用于BFS
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
            //std::cerr << "BFSv 还没实现" << std::endl;
            return result;
        }

        bool IsConnected(LGraph& graph) {
            //TODO:判断图是否联通
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
            //std::cerr << "IsConnected 还没实现" << std::endl;
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

                if (u == dest) break; // 如果找到了目标节点，则提前退出

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

            std::cout << vertex_name_x << "和" << vertex_name_y << "之间的最短距离为：" << dist[dest] << std::endl;
            std::cout << "路径为：";
            printPath(prev, dest,id_name);
            std::cout << std::endl;

            return dist[dest];
        }


        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //TODO:获取拓扑受限的最短路径，拓扑序由path给出

            std::unordered_map<std::string, int> dist; // 存储每个节点的最短距离
            std::map<std::string, Vertex> v_id{ graph.Map() };
            const std::map<Vertex, std::string> id_v{ graph.Map_re() };
            // 初始化：所有节点的距离为无穷大
            for (const auto& node : path) {
                dist[node] = INT_MAX;
            }

            // 起点距离为0
            dist[path[0]] = 0;

            // 按照用户给定的拓扑顺序松弛每条边
            for (const auto& u : path) {
                int uu = v_id[u];
                if (dist[u] == INT_MAX) continue; // 不可达节点跳过
                const std::vector<HeadNode> verlist{ graph.List() };
                for (const auto& edge : verlist.at(uu).adj) {
                   
                    const auto& vv = edge.dest;
                    int weight = edge.weight;
                    std::string v = id_v.at(vv);
                    // 松弛操作
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }

            // 返回从起点到终点的最短路径长度
            if (dist[path.back()] == INT_MAX) {
                std::cerr << "无法到达终点" << std::endl;
                return -1;
            }
            return dist[path.back()];
            //std::cerr << "TopologicalShortestPath 还没实现" << std::endl;
            //return -1;
        }

        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            //TODO:计算最小生成树，并返回树上的边
            std::vector<EdgeNode> edges0{ graph.SortedEdges() };
            std::priority_queue<EdgeNode> roads;
                for (int i = 1; i <= edges0.size(); i++) {
                  //无向图去重处理
                    //if (!graph.directed &&i % 2 == 0) { continue; }
                    //不用去重，合并时遇到已经贴加过的会自动跳过
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
            //std::cerr << "MinimumSpanningTree 还没实现" << std::endl;
            //return {};
        }
    }
}
//初版最短路径
/*void printPath(const std::vector<std::vector<int>>& next, int u, int v) {
    if (u == v) {
        std::cout << u;
        return;
    }
    if (next[u][v] == -1) {
        std::cout << "无路径";
        return;
    }

    std::cout << u;
    while (u != v) {
        u = next[u][v];
        std::cout << "->" << u;
    }
}*/

//int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x, const std::string& vertex_name_y) {
//    //TODO:获取两点之间的最短路径
//    int V = graph.VertexCount();
//    std::vector<std::vector<int>> next(V, std::vector<int>(V, -1));

//    // 初始化next矩阵（空间优化：直接使用graph作为dist矩阵）
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
//            // 提前终止优化：如果i到k不可达则跳过
//            if (g[i][k] == INF) continue;

//            for (int j = 0; j < V; j++) {
//                // 空间优化：直接使用graph矩阵
//                if (g[k][j] != INF && g[i][j] > g[i][k] + g[k][j]) {
//                    g[i][j] = g[i][k] + g[k][j];
//                    next[i][j] = next[i][k];
//                }
//            }
//        }
//    }
//    std::cout << vertex_name_x << "和" << vertex_name_y << "之间的最短距离为："<< g[v_id.at(vertex_name_x)][v_id.at(vertex_name_y)];
//    std::cout << std::endl<<"路径为：";

//    printPath(next, v_id.at(vertex_name_x), v_id.at(vertex_name_y));
//    std::cout <<std:: endl;
//    //std::cerr << "GetShortestPath 还没实现" << std::endl;
//    return -1;
//}