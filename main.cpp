#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<set>
#include <vector>
#include <cassert>
#include <windows.h>
#include "LGraph.h"
#include "Algorithm.h"

#include "LocationInfo.h"
#include "GraphException.h"
//#include "Algorithm.cpp"

using Graph::LGraph;
using Graph::VertInfo;
using namespace Graph::Algorithm;

// Hint: �������д����Ŀ�����������ļ���������backup�ļ����л�ȡԭʼ�ļ�
// TODO: ����ݿ�ִ���ļ���csv��λ����д�ļ�·��
const std::string nodes_path{ "nodes.csv" };
const std::string edges_path{ "edges.csv" };

struct edge {
    std::string from;
    std::string to;
    int length;
};

void init(LGraph& graph);

std::vector<VertInfo> read_nodes(const std::string& nodes_path);

std::vector<edge> read_edges(const std::string& edges_path);

void store_nodes(const std::string& nodes_path, const LGraph& graph);

void store_edges(const std::string& edges_path, const LGraph& graph);

void show_all_nodes(const LGraph& graph);

void show_all_edges(const LGraph& graph);

int main() {
    LGraph graph(false); //��ʼ��һ������ͼ��
    init(graph);
    //std::vector<bool> visited(graph.VertexCount(), false);
    //std::cout<<Graph::Algorithm::HaveEulerCircle(graph);
    while (true) {
        int choice{ 0 };
        std::cout << "��ӭʹ��У԰����ϵͳ��" << std::endl
            << "��ѡ����Ҫ���еĲ�����" << std::endl
            << "1.������ز���" << std::endl
            << "2.����ز���" << std::endl
            << "3.���ļ������¼��ص����" << std::endl
            << "4.�Ƿ����ŷ��ͨ·" << std::endl
            << "5.��������������̾���" << std::endl
            << "6.����С������" << std::endl
            << "7.�����������ʱ�����·��" << std::endl
            << "8.�˳�����" << std::endl
            << "���������ǰ�����֣�";
        std::cin >> choice;
        if (choice == 1) { // ������ز���
            std::cout << "������ز�����" << std::endl
                << "1.����ض�������Ϣ" << std::endl
                << "2.������ж�����Ϣ" << std::endl
                << "3.���һ������" << std::endl
                << "4.ɾ��һ������" << std::endl
                << "5.�洢���㵽�ļ���" << std::endl
                << "6.����ض����͵ı�" << std::endl
                << "7.����붥���ڽӵı�" << std::endl
                << "8.�ص���һ���˵�" << std::endl
                << "���������ǰ�����֣�";
            std::cin >> choice;
            if (choice == 1) {
                std::string name;
                std::cout << "�����붥�����ƣ�";
                std::cin >> name;
                try {
                    if (!graph.exist_vertex(name)) { 
                        throw Graph::GraphException(name);
                              }
                    VertInfo v{ graph.GetVertex(name) };
                    std::cout << "�������ƣ�" << v.name << std::endl
                        << "�������ͣ�" << v.type << std::endl
                        << "��������ʱ�䣺" << v.visitTime << std::endl;

                }
                catch (Graph::GraphException& e) {
                    std::cout << "����Ϊ " << name << " �Ķ��㲻����" << std::endl;
                }
            }
            else if (choice == 2) {
                std::cout << "��������, ��������, ��������ʱ�䣺" << std::endl;
                show_all_nodes(graph);
            }
            else if (choice == 3) {
                std::cout << "�����붥�����ƣ��������ͣ���������ʱ��(�ո�ָ�)��";
                std::string name, type;
                int visit_time;
                std::cin >> name >> type >> visit_time;
                try {

                    graph.InsertVertex({ name, visit_time, type });
                }
                catch (Graph::GraphException& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else if (choice == 4) {
                std::cout << "�����붥�����ƣ�";
                std::string name;
                std::cin >> name;
                try {
                    if (!graph.exist_vertex(name)) {
                        throw Graph::GraphException("����Ϊ " + name + " �Ķ��㲻����");
                    }
                    graph.DeleteVertex({ name, 0, "" });
                }
                catch (Graph::GraphException& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else if (choice == 5) {
                std::cout << "���ڽ�����洢��test_nodes.csv��..." << std::endl;
                store_nodes("test_nodes.csv", graph);
                std::cout << "�洢�ɹ���" << std::endl;
            }
            else if (choice == 6) {
                std::cout << "�������������ƣ�";
                std::string name;
                std::cin >> name;
                graph.FindVerticesByType(name);
            }
            else if (choice == 7) {
                std::cout << "�����붥������";
                std::string name;
                std::cin >> name;
                graph.adj_edge(name);
            }
        }
        else if (choice == 2) { // ����ز���
            std::cout << "����ز�����" << std::endl
                << "1.����ض�����Ϣ" << std::endl
                << "2.������б���Ϣ" << std::endl
                << "3.���һ����" << std::endl
                << "4.ɾ��һ����" << std::endl
                << "5.����һ����" << std::endl
                << "6.�洢�ߵ��ļ���" << std::endl
                << "6.�ص���һ���˵�" << std::endl
                << "���������ǰ�����֣�";
            std::cin >> choice;
            if (choice == 1) {
                std::string from, to;
                std::cout << "������ߵ�������յ�(�ո�ָ�)��";
                std::cin >> from >> to;
                Graph::GElemSet w{ graph.GetEdge(from, to) };
              if(w==-1)  { std::cout << from << " <---> " << to << " �����ڣ�" << std::endl; }
              else
              {
                  std::cout << from << " <---> " << to << " ����Ϊ��" << w << std::endl;
              }                
            }
            else if (choice == 2) {
                std::cout << "���, �յ�, ���룺" << std::endl;
                show_all_edges(graph);
            }
            else if (choice == 3) {
                std::cout << "������������ƣ��յ����ƣ�����(�ո�ָ�)��";
                std::string from, to;
                int length;
                std::cin >> from >> to >> length;
                
                try {
                    graph.InsertEdge(from, to, length);
                    }
                catch (Graph::GraphException& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else if (choice == 4) {
                std::cout << "������������ƣ��յ�����(�ո�ָ�)��";
                std::string from, to;
                std::cin >> from >> to;
                try { graph.DeleteEdge(from, to); } // ɾ��һ���� 
                catch (Graph::GraphException& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else if (choice == 5) {
                std::cout << "������������ƣ��յ�����,�µľ���(�ո�ָ�)��";
                std::string from, to;
                int length;
                std::cin >> from >> to>>length;
                try { graph.UpdateEdge(from, to, length); }  
                catch (Graph::GraphException& e) {
                    std::cout << e.what() << std::endl;
                }

            }
            else if (choice == 6) {
                std::cout << "���ڽ��ߴ洢��test_edges.csv�ļ���..." << std::endl;
                store_edges("test_edges.csv", graph);
                std::cout << "�洢�ɹ���" << std::endl;
            }
        }
        else if (choice == 3) {// ���ļ������¼��ص����
            try { 
                LGraph new_graph(graph.directed); // ����һ���µ�ͼ������ԭͼ������/��������
                graph = new_graph; // �滻ԭͼ
                init(graph); // ���³�ʼ��ͼ
                std::cout << "ͼ�����¼��أ�" << std::endl;
                 }
            catch (Graph::GraphException& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (choice == 4) { // �Ƿ����ŷ��ͨ·
            bool res = HaveEulerCircle(graph);
            std::cout << (res ? "����ŷ����·" : "������ŷ����·") << std::endl<<'\n'<<'\n';
        }
        else if (choice == 5) { // ��������������̾���
            std::cout << "�����������ص㣬ʹ�ÿո�ֿ���" << std::endl;
            std::string x, y;
            std::cin >> x >> y;
            try {
                GetShortestPath(graph, x, y) ;

            }
            catch (Graph::GraphException& e) {
                std::cout << "���ҵ�����յľ���" << std::endl;
            }
        }
        else if (choice == 6) { // ����С������
            if (IsConnected(graph)) {
                std::cout << "��С�������ĵ����£�";
                auto res = MinimumSpanningTree(graph);
                int sum = 0;
                for (auto &item : res) {
                    const auto& e = edge{ graph.List()[item.from].data.name, graph.List()[item.dest].data.name, item.weight };
                    std::cout << e.from << "," << e.to << "," << e.length << std::endl;
                    sum += e.length;
                }
                std::cout << "��Ȩ��Ϊ" << sum << std::endl;
            }
            else {
                std::cout << "ͼ����ͨ" << std::endl;
            }
        }
        else if (choice == 7) { // �����������ʱ�����·��
            if (HaveEulerCircle(graph)) { std::cout << "ͼ�л����޷����иò���" << '\n'; continue; }
            std::cout << "��������ϣ���������򣬵�һ��һ��nΪ���г��ȣ��ڶ���n���ص�Ϊ��������" << std::endl;
            int n;
            std::vector<std::string> list;
            std::cin >> n;
            while (n--) {
                std::string x;
                std::cin >> x;
                list.push_back(x);
            }
            std::cout << "���·��Ϊ" << TopologicalShortestPath(graph, list) << std::endl;
        }
        else {
            std::cout << "��л����ʹ�ã��ټ���\n �����ߣ�\\lky1433223/ \\Voltline/" << std::endl;
            break;
        }
    }
    return 0;
}

/* ���ļ��ж�ȡ������Ϣ
 * @param nodes_path: �����ļ�·��
 * @return: ������ȡ�������ж����std::vector
 */
std::vector<VertInfo> read_nodes(const std::string& nodes_path) {
    std::ifstream fin(nodes_path);              // �����ļ�����������
    assert(fin.good());                         // ���ԣ�ͨ���ļ���������good()��������ļ��Ƿ����
    std::vector<VertInfo> nodes;                // ��ʱ�洢������Ϣ
    std::string line;
    std::getline(fin, line);                               // ͨ��std::getline��ȡ����ÿһ�У���ʱ�洢���ַ���line��
    while (std::getline(fin, line)) {       // ͨ��std::getline(std::istream&, std::string&)����ȡ��������һ��
        for (auto& c : line) {
            if (c == ',') c = ' ';              // csv�ļ��Զ��ŷָ���Ϊ�˷������ʹ���ַ������������������滻Ϊ�ո�
        }
        std::istringstream sin(line);           // ����std::istringstream���Ի�ȡ����Ϊ���ݹ���һ���ַ���������
        std::string name, type;                 // �ļ�ÿ���еĶ���������������
        int visit_time;                         // �ļ���ÿ�еĶ����Ƽ�����ʱ��
        sin >> name >> type >> visit_time;      // �����ѹ�����ַ�������������ȡ��Ӧ�ļ�������
        nodes.push_back({ name, visit_time, type });  // ������Ҫ���ص�std::vector��
    }
    fin.close();                                // �ļ�ʹ����Ϻ������ʹ��close���ʹر��������������ļ���
    return nodes;
}

/* ���ļ��ж�ȡ����Ϣ
 * @param edges_path: ���ļ�·��
 * @return: ������ȡ�������бߵ�std::vector
 */
std::vector<edge> read_edges(const std::string& edges_path) {
    // TODO: ��ο�read_nodes��������������ʾ�����edges.csv�ļ������ݣ���ɱ������Ķ���
    std::ifstream fin(edges_path);
    assert(fin.good());
    std::vector<edge>edges;
    std::string line;
    std::getline(fin, line);
    while (std::getline(fin, line)) {
        for (auto& c : line) {
            if (c == ',')c = ' ';
        }
        std::stringstream s(line);
        std::string from, to;
        int weight;
        s >> from >> to >>weight;
        edges.push_back({ from,to,weight });
        //std::cout << "cun" << ' ' << from << ' ' << to << ' ' << weight << '\n';
    }
    fin.close();
    return edges;
}

void init(LGraph& graph) {
    //LGraph g1(graph.directed);
    std::vector<VertInfo> nodes{ read_nodes(nodes_path) };        // ͨ��read_nodes������ö�����Ϣ
    std::vector<edge> edges{ read_edges(edges_path) };            // ͨ��read_edges������ñ���Ϣ
    try{
        for (auto& v : nodes) {
            // TODO: ��ͼgraph�в��붥��
            graph.InsertVertex(v);
        }
        for (auto& e : edges) {
            // TODO: ��ͼgraph�в����
            graph.InsertEdge(e.from, e.to, e.length);
        }
    }
    catch (Graph::GraphException& e) {
        std::cout << e.what() << std::endl;
    }
}

/* ��ӡĿǰ�����ж���
 * @param graph: ͼ
 */
void show_all_nodes(const LGraph& graph) {
    // TODO: ʵ�ִ�ӡ���ж�����Ϣ
    // TODO: ÿ�������ʽ��������,��������,�Ƽ�����ʱ��
    for (int i = 0; i < graph.VertexCount(); i++) {
        VertInfo x(graph.GetVertex(i));
        std::cout << x.name << ',' << x.type << ',' << x.visitTime<<std::endl;
    }
    //std::cerr << "show_all_nodes��ûʵ��" << std::endl;

}

/* ��ӡĿǰ�����б�
 * @param graph: ͼ
 */
void show_all_edges(const LGraph& graph) {
    // LGraph��ֻ�ṩ�˻�ȡ�ڽӱ�ͻ�ȡ��������ıߵķ���
    // Ϊ���ܹ���ȡ��ÿ���ߵ�Ԫ��Ϣ��������Ҫ������������������Ϣ�Ļ�ȡ
    const auto& graph_edges{ graph.SortedEdges() };       // ��ȡ��������ı�
    const auto& graph_list{ graph.List() };               // ��ȡ�ڽӱ�
    std::set<std::pair<std::string, std::string>>displayed_edges;
    for (const auto& en : graph_edges) {                 // �����ߣ�ͨ���±�����ȡ��Ӧ�Ķ�����Ϣ
        std::string from = graph_list[en.from].data.name;
        std::string to = graph_list[en.dest].data.name;
        if (displayed_edges.count({ from,to })) { continue; }
        if (!graph.directed && displayed_edges.count({ to, from }) ){ continue; }
        displayed_edges.insert({ from,to });

        //const auto& e = edge{ graph_list[en.from].data.name, graph_list[en.dest].data.name, en.weight };
        std::cout << from << "," << to << "," << en.weight << std::endl;
    }
}

/* ��������Ϣ�洢���ļ���
 * @param nodes_path: �����ļ�·��
 * @param graph: ͼ
 */
void store_nodes(const std::string& nodes_path, const LGraph& graph) {
    std::ofstream fout(nodes_path);                                         // ͨ��Ŀ¼�����ļ������
    const auto& graph_list{ graph.List() };                                   // ͨ��LGraph�����List()��������ڽӱ�
    for (const auto& n : graph_list) {                                       // �����ڽӱ��е�ÿ������
        const auto& v = n.data;                                             // ��ö����е�Ԫ����
        fout << v.name << "," << v.type << "," << v.visitTime << std::endl; // ���ն���洢�ĸ�ʽ���������뵽�ļ���
    }
    fout.close();                                                           // ��ʹ�����κ��ļ����󣬶�Ҫʹ��close�����ر�
}

/* ������Ϣ�洢���ļ���
 * @param edges_path: ���ļ�·��
 * @param graph: ͼ
 */
void store_edges(const std::string& edges_path, const LGraph& graph) {
    // TODO: ��ο�store_nodes��������������ʾ�����edges.csv�ļ�������
    // TODO: �Լ�show_all_edges�����л�ȡ�ߵ�Ԫ��Ϣ�ķ�ʽ���store_edges�����Ķ���
    std::ofstream fout(edges_path);
    const auto& edges{ graph.Edge() };
    const auto& node_map{ graph.Map_re() };
    for (const auto& e : edges) {

        fout << node_map.at( e.from) << ',' <<node_map.at( e.dest) << ',' << e.weight << std::endl;
    }
    fout.close();
}