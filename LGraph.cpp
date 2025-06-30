//
// Created by ����Դ on 24-5-16.
//

#include "LGraph.h"
#include"GraphException.h"
#include<string.h>

namespace Graph {
    LGraph::LGraph(bool directed)
        : n_verts(0), m_edges(0), directed(directed), ver_list(std::vector<HeadNode>()) {}

    bool LGraph::exist_vertex(const std::string& name) const {
        //TODO:�ж��Ƿ����name���ƵĽڵ�
        
            if (vertex_map.find(name)!=vertex_map.end()){ return true; }
        
        //std::cerr << "LGraph::exist_vertex(const std::string &name) ��ûʵ��" << std::endl;
        return false;
    }

    bool LGraph::exist_edge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:�ж��Ƿ����x-y�ı�
            if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
                return false;
            }
            Vertex x = vertex_map.at(vertex_x_name);
            for (const auto& edge : ver_list[x].adj) {
                if (GetVertex(edge.dest).name == vertex_y_name) {
                    return true;
                }
            }
            return false;
        
        /*std::cerr << "LGraph::exist_edge(const std::string &vertex_x_name, const std::string &vertex_y_name) ��ûʵ��" << std::endl;
        return false;*/
    }
    void LGraph::FindVerticesByType(const std::string& type)  {
        std::vector<std::string> result;
        // �������ж���
        for (const auto& pair : v_type) {
            
            // ��鶥�������Ƿ�ƥ��
            if (pair.second == type) {
                // ��ȡ������Ϣ����ӵ������
                std::cout<<vertex_map_re[pair.first]<<' ';
            }
        }
        std::cout <<std:: endl;
        return ;
    }
    void LGraph::adj_edge(const std::string& name) {
        int id = vertex_map[name];
        for (auto &node : ver_list[id].adj) {
            std::string name1 = vertex_map_re[node.dest];
            std::cout << name1<< ' ';
        }
        std::cout << std::endl;
        return;
    };
    void LGraph::InsertVertex(const LocationInfo& vertex_info) {
        //TODO:����ڵ㣬�ڵ���Ϣ��LocationInfo�����
        vertex_map.emplace(vertex_info.name, n_verts);
        vertex_map_re[n_verts] = vertex_info.name;
        //v_time.emplace(n_verts, vertex_info.visitTime);
        v_time[n_verts] = vertex_info.visitTime;
        //v_type_re[vertex_info.type] = vertex_info.name;
        v_type[n_verts]=vertex_info.type;
        HeadNode newhead;
        newhead.data = vertex_info;
        ver_list.push_back(newhead);
        n_verts++;
        //std::cout << "�����ɹ�" << std::endl;
        //std::cerr << "LGraph::InsertVertex(const LocationInfo &vertex_info) ��ûʵ��" << std::endl;
    }

    void LGraph::DeleteVertex(const LocationInfo& vertex_info) {
        //TODO:ɾ���ڵ㣬�ڵ���Ϣ��LocationInfo�����
        deleted.insert(vertex_info.name);
        v_type[vertex_map[vertex_info.name]] = "��ɾ��";
        v_time[vertex_map[vertex_info.name]]=0;
        vertex_map_re[vertex_map[vertex_info.name]]="��ɾ��";
        vertex_map[(vertex_info.name)]=-1;
        for (auto it = ver_list.begin(); it != ver_list.end(); it++) {
            if (it->data.name == vertex_info.name) { it->adj.clear() ;
            break; }
        }
        n_verts--;
        std::cout << "��ɾ���ɹ�" << std::endl;
        //std::cerr << "LGraph::DeleteVertex(const LocationInfo &vertex_info) ��ûʵ��" << std::endl;
    }

    void LGraph::UpdateVertex(const LocationInfo& old_info, LocationInfo& new_info) {
        //TODO:���½ڵ㣬��/�ɽڵ����Ϣ��LocationInfo�����
            // ���ɶ����Ƿ����
            if (!exist_vertex(old_info.name)) {
                throw GraphException("Ҫ���µĶ��㲻����: " + old_info.name);
            }

            // ��ȡ����ID
            Vertex v_id = vertex_map[old_info.name];

            // ������Ƹı䣬��Ҫ����ӳ���ϵ
            if (old_info.name != new_info.name) {
                // ����������Ƿ��Ѵ���
                if (exist_vertex(new_info.name)) {
                    throw GraphException("�¶��������Ѵ���: " + new_info.name);
                }

                // ����ӳ���ϵ
                vertex_map.erase(old_info.name);
                vertex_map[new_info.name] = v_id;
                vertex_map_re[v_id] = new_info.name;
            }

            // ���¶�����Ϣ
            ver_list[v_id].data = new_info;        // �����ڽӱ��е�����
            v_time[v_id] = new_info.visitTime;     // ���²ι�ʱ��
            v_type[v_id] = new_info.type;          // ���¶�������
        
        std::cerr << "LGraph::UpdateVertex(const LocationInfo &old_info, LocationInfo &new_info) ��ûʵ��" << std::endl;
    }

    VertInfo LGraph::GetVertex(const std::string& name) const {
        //TODO:��ȡ�ڵ㣬�ɽڵ�����ѯ�ڵ���Ϣ
            int visitTime;       // ����ι���ʱ����λ�����ӣ�
            std::string type;
            int vertex = vertex_map.at(name);
            visitTime = v_time.at(vertex);
            type = v_type.at(vertex);


            //std::cerr << "LGraph::GetVertex(const Vertex vertex) ��ûʵ��" << std::endl;
            //return VertInfo(name,visitTime,type);
            return VertInfo(name, visitTime, type);
            //std::cerr << "LGraph::GetVertex(const std::string &name) ��ûʵ��" << std::endl;
        
        //return VertInfo();
    }

    VertInfo LGraph::GetVertex(const Vertex vertex) const {
        //δ����v������
        
        //TODO:��ȡ�ڵ㣬�ɽڵ��ID��ѯ
        std::string name;         // �ص�����
        int visitTime;       // ����ι���ʱ����λ�����ӣ�
        std::string type;
        for (std::pair< std::string, Vertex > x : vertex_map) {
            if (x.second == vertex) { name = x.first; }
        }
        visitTime = v_time.at(vertex);
        type = v_type.at(vertex);
        
        /*for (auto x : v_time) {
            if (x.first == name) { visitTime = x.second; }
        }
        for (auto x : v_type) {
            if (x.first == name) {
                type = x.second;
            }
        }*/
        //std::cerr << "LGraph::GetVertex(const Vertex vertex) ��ûʵ��" << std::endl;
        //return VertInfo(name,visitTime,type);
        return VertInfo(name,visitTime,type);
    }

    void LGraph::InsertEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet weight) {
        //TODO:�����
       
        if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
            throw Graph::GraphException(vertex_x_name + "or" + vertex_y_name + "Ҫ����ıߵĶ��㲻����");
        }
        if (exist_edge(vertex_x_name, vertex_y_name)) {
            throw Graph::GraphException(vertex_x_name + "_" + vertex_y_name + "Ҫ����ı��Ѵ���");
        }
        //Ӧ������֮������������߰�
        Vertex x = vertex_map.at(vertex_x_name);
        Vertex y = vertex_map.at(vertex_y_name);
        EdgeNode newedge(x,y, weight);
        edges.push_back(newedge);
        ver_list[x].adj.push_back(newedge);
        m_edges++;
        if (!directed) 
        {
             EdgeNode newedge1(y, x, weight);
            edges.push_back(newedge1);
            ver_list[y].adj.push_back(newedge1);
            m_edges++;
        }
        //std::cerr << "LGraph::InsertEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet weight) ��ûʵ��" << std::endl;
    }

    void LGraph::DeleteEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) {
        //TODO:ɾ���ߣ��������ڵ���ȷ��һ����
        if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
            throw GraphException(vertex_x_name+"or"+ vertex_y_name+"��Ҫɾ���Ķ��㲻����");
        }
        if (!exist_edge(vertex_x_name, vertex_y_name)) {
            throw GraphException(vertex_x_name+"_"+ vertex_y_name+"��Ҫɾ���߲�����");
        }
        Vertex x = vertex_map[vertex_x_name];
        Vertex y = vertex_map[vertex_y_name];
        auto it_e = std::find_if(edges.begin(), edges.end(), [x, y](const EdgeNode a) {return a.from == x && a.dest == y; });
        if (it_e != edges.end()) {
            edges.erase(it_e);
        }
        auto  it2 = std::find_if(ver_list[y].adj.begin(), ver_list[y].adj.end(), [x](const EdgeNode a)
            {return a.dest == x; });
        if (it2 != ver_list[y].adj.end()) { ver_list[y].adj.erase(it2);
    }
        m_edges--;

        if (!directed) {
            auto it_e = std::find_if(edges.begin(), edges.end(), [x, y](const EdgeNode a) {return a.from == y && a.dest == x; });
            if (it_e != edges.end()) {
                edges.erase(it_e);
            }
            auto  it2 = std::find_if(ver_list[x].adj.begin(), ver_list[x].adj.end(), [y](const EdgeNode a)
                {return a.dest == y; });
            if (it2 != ver_list[x].adj.end()) { ver_list[x].adj.erase(it2);
        }
            m_edges--;
        }
        std::cout << "��"+ vertex_x_name + "-" + vertex_y_name +"ɾ���ɹ�" << std::endl;
            /*for (auto edge : edges) {
            if (edge.from == x && edge.dest == y) {
                edges.erase()
            }
        }*/
        //std::cerr << "LGraph::DeleteEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) ��ûʵ��" << std::endl;

    }

    void LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) {
        //TODO:ɾ���ߣ��������ڵ�IDȷ��һ����
        if (!exist_vertex(vertex_map_re[vertex_x]) || !exist_vertex(vertex_map_re[vertex_y])) {
            throw GraphException(std::to_string(vertex_x) + "or" + std::to_string( vertex_y) + "Ҫɾ���ıߵĶ��㲻����(id)");
        }
        if (!exist_edge(vertex_map_re[vertex_x], vertex_map_re[vertex_y])) {
            throw GraphException(std::to_string(vertex_x) + "-" + std::to_string(vertex_y)+"Ҫɾ���ı߲����ڣ�id��");
        }
        Vertex x = vertex_x;
        Vertex y = vertex_y;
        auto it_e = std::find_if(edges.begin(), edges.end(), [x, y](const EdgeNode a) {return a.from == x && a.dest == y; });
        if (it_e != edges.end()) {
            edges.erase(it_e);
        }
        auto  it2 = std::find_if(ver_list[y].adj.begin(), ver_list[y].adj.end(), [x](const EdgeNode a)
            {return a.dest == x; });
        if (it2 != ver_list[y].adj.end()) {
            ver_list[y].adj.erase(it2);
        }
        m_edges--;

        if (!directed) {
            auto it_e = std::find_if(edges.begin(), edges.end(), [x, y](const EdgeNode a) {return a.from == y && a.dest == x; });
            if (it_e != edges.end()) {
                edges.erase(it_e);
            }
            auto  it2 = std::find_if(ver_list[x].adj.begin(), ver_list[x].adj.end(), [y](const EdgeNode a)
                {return a.dest == y; });
            if (it2 != ver_list[x].adj.end()) {
                ver_list[x].adj.erase(it2);
            }
            m_edges--;
        }
        std::cout << "��(id)" + std::to_string(vertex_x) + "-" + std::to_string(vertex_y) + "ɾ���ɹ�" << std::endl;

        //std::cerr << "LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) ��ûʵ��" << std::endl;
    }


    void LGraph::UpdateEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_weight) {
        //TODO:���±ߣ��������ڵ���ȷ��һ����
            // ��鶥���Ƿ����
            if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
                throw GraphException(vertex_x_name + "or" + vertex_y_name + "��Ҫ���µĶ��㲻����");
            }

            // �����Ƿ����
            if (!exist_edge(vertex_x_name, vertex_y_name)) {
                throw GraphException(vertex_x_name+"-"+vertex_y_name + "��Ҫ���µı߲�����");
            }

            // ��ȡ����ID
            Vertex x = vertex_map[vertex_x_name];
            Vertex y = vertex_map[vertex_y_name];

            // ����x->y����ı�
            for (auto& edge : ver_list[x].adj) {
                if (edge.dest == y) {
                    edge.weight = new_weight;
                    break;
                }
            }

            // ����edges�����еı�
            for (auto& edge : edges) {
                if (edge.from == x && edge.dest == y) {
                    edge.weight = new_weight;
                    break;
                }
            }

            // ���������ͼ������Ҫ����y->x����ı�
            if (!directed) {
                for (auto& edge : ver_list[y].adj) {
                    if (edge.dest == x) {
                        edge.weight = new_weight;
                        break;
                    }
                }

                for (auto& edge : edges) {
                    if (edge.from == y && edge.dest == x) {
                        edge.weight = new_weight;
                        break;
                    }
                }
            }
            std::cout << "��" + vertex_x_name + "-" + vertex_y_name + "���³ɹ�" << std::endl;
        //std::cerr << "LGraph::UpdateEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet new_weight) ��ûʵ��" << std::endl;
    }

    GElemSet LGraph::GetEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:��ȡ�ߵ���Ϣ
        for (auto x : ver_list) {
            if (x.data.name == vertex_x_name) {
                for (auto &xx : x.adj) {
                    if (xx.dest == vertex_map.at(vertex_y_name)) {
                        return xx.weight; 
                    }
                }
                
            }
        }
        return -1;
        //std::cerr << "LGraph::GetEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) ��ûʵ��" << std::endl;
        //return GElemSet();
    }

    std::vector<EdgeNode> LGraph::SortedEdges(std::function<bool(const GElemSet&, const GElemSet&)> cmp) const {
        //TODO:��ȡ����Ȩ�͸���������������б�
        std::vector<EdgeNode> edg(edges.begin(),edges.end());
        sort(edg.begin(), edg.end());
        return edg;
        std::cerr << "LGraph::SortedEdges(std::function<bool(const GElemSet &, const GElemSet &)> cmp) ��ûʵ��" << std::endl;
        return std::vector<EdgeNode>();
    }


}