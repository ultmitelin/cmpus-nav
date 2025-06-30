//
// Created by 刘凯源 on 24-10-13.
//

#ifndef CAMPUSNAVIGATION_ALGORITHM_H
#define CAMPUSNAVIGATION_ALGORITHM_H

#include "LGraph.h"

namespace Graph {
    namespace Algorithm {
        class DSU {
        private:
            std::vector<int> parent, rank;
        public:
            // 并查集构造函数
            explicit DSU(int n) {
                // TODO: 请完成并查集的构造函数
                parent.resize(n);
                rank.resize(n, 0);
                for (int i = 0; i < n; i++) {
                    parent[i] = i;
                }
            }

            // 查找根节点并路径压缩
            int find_p(int x) {
                if (parent[x] != x)
                    parent[x] = find_p(parent[x]);
                return parent[x];
                // TODO: 查找元素的根节点，并完成路径压缩
            }

            // 合并两个集合
            void unite(int x, int y) {
                // TODO: 合并集合
                int xRoot = find_p(x), yRoot = find_p(y);
                if (xRoot == yRoot) return;

                if (rank[xRoot] < rank[yRoot])
                    parent[xRoot] = yRoot;
                else if (rank[xRoot] > rank[yRoot])
                    parent[yRoot] = xRoot;
                else {
                    parent[yRoot] = xRoot;
                    rank[xRoot]++;
                }
            }

            // 检查两个节点是否属于同一集合
            bool same(int x, int y) {
                // TODO: 检查两个节点是否属于同一个集合
                if (find_p(x) == find_p(y)) {
                    return true;
                }
                return false;
            }
        };
        std::vector<int> DFSv(LGraph& graph, Vertex v, std::vector<bool>& visited);
        std::vector<int> BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited);
        std::list<Vertex> EulerCircle(const LGraph& graph); //计算欧拉回路
        bool HaveEulerCircle( LGraph& graph); //判断是否存在欧拉回路
        bool IsConnected(LGraph& graph) ; //判断图是否联通
        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x,
            const std::string& vertex_name_y); //计算单源最短路径
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //计算拓扑受限的最短路径
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //计算最小生成树
    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H
