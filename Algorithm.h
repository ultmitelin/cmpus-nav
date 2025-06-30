//
// Created by ����Դ on 24-10-13.
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
            // ���鼯���캯��
            explicit DSU(int n) {
                // TODO: ����ɲ��鼯�Ĺ��캯��
                parent.resize(n);
                rank.resize(n, 0);
                for (int i = 0; i < n; i++) {
                    parent[i] = i;
                }
            }

            // ���Ҹ��ڵ㲢·��ѹ��
            int find_p(int x) {
                if (parent[x] != x)
                    parent[x] = find_p(parent[x]);
                return parent[x];
                // TODO: ����Ԫ�صĸ��ڵ㣬�����·��ѹ��
            }

            // �ϲ���������
            void unite(int x, int y) {
                // TODO: �ϲ�����
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

            // ��������ڵ��Ƿ�����ͬһ����
            bool same(int x, int y) {
                // TODO: ��������ڵ��Ƿ�����ͬһ������
                if (find_p(x) == find_p(y)) {
                    return true;
                }
                return false;
            }
        };
        std::vector<int> DFSv(LGraph& graph, Vertex v, std::vector<bool>& visited);
        std::vector<int> BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited);
        std::list<Vertex> EulerCircle(const LGraph& graph); //����ŷ����·
        bool HaveEulerCircle( LGraph& graph); //�ж��Ƿ����ŷ����·
        bool IsConnected(LGraph& graph) ; //�ж�ͼ�Ƿ���ͨ
        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x,
            const std::string& vertex_name_y); //���㵥Դ���·��
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //�����������޵����·��
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //������С������
    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H
