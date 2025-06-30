//
// Created by 刘凯源 on 24-5-16.
//

#include "LGraph.h"
#include"GraphException.h"
#include<string.h>

namespace Graph {
    LGraph::LGraph(bool directed)
        : n_verts(0), m_edges(0), directed(directed), ver_list(std::vector<HeadNode>()) {}

    bool LGraph::exist_vertex(const std::string& name) const {
        //TODO:判断是否存在name名称的节点
        
            if (vertex_map.find(name)!=vertex_map.end()){ return true; }
        
        //std::cerr << "LGraph::exist_vertex(const std::string &name) 还没实现" << std::endl;
        return false;
    }

    bool LGraph::exist_edge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:判断是否存在x-y的边
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
        
        /*std::cerr << "LGraph::exist_edge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;
        return false;*/
    }
    void LGraph::FindVerticesByType(const std::string& type)  {
        std::vector<std::string> result;
        // 遍历所有顶点
        for (const auto& pair : v_type) {
            
            // 检查顶点类型是否匹配
            if (pair.second == type) {
                // 获取顶点信息并添加到结果中
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
        //TODO:插入节点，节点信息由LocationInfo类给出
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
        //std::cout << "点插入成功" << std::endl;
        //std::cerr << "LGraph::InsertVertex(const LocationInfo &vertex_info) 还没实现" << std::endl;
    }

    void LGraph::DeleteVertex(const LocationInfo& vertex_info) {
        //TODO:删除节点，节点信息由LocationInfo类给出
        deleted.insert(vertex_info.name);
        v_type[vertex_map[vertex_info.name]] = "已删除";
        v_time[vertex_map[vertex_info.name]]=0;
        vertex_map_re[vertex_map[vertex_info.name]]="已删除";
        vertex_map[(vertex_info.name)]=-1;
        for (auto it = ver_list.begin(); it != ver_list.end(); it++) {
            if (it->data.name == vertex_info.name) { it->adj.clear() ;
            break; }
        }
        n_verts--;
        std::cout << "点删除成功" << std::endl;
        //std::cerr << "LGraph::DeleteVertex(const LocationInfo &vertex_info) 还没实现" << std::endl;
    }

    void LGraph::UpdateVertex(const LocationInfo& old_info, LocationInfo& new_info) {
        //TODO:更新节点，新/旧节点的信息由LocationInfo类给出
            // 检查旧顶点是否存在
            if (!exist_vertex(old_info.name)) {
                throw GraphException("要更新的顶点不存在: " + old_info.name);
            }

            // 获取顶点ID
            Vertex v_id = vertex_map[old_info.name];

            // 如果名称改变，需要更新映射关系
            if (old_info.name != new_info.name) {
                // 检查新名称是否已存在
                if (exist_vertex(new_info.name)) {
                    throw GraphException("新顶点名称已存在: " + new_info.name);
                }

                // 更新映射关系
                vertex_map.erase(old_info.name);
                vertex_map[new_info.name] = v_id;
                vertex_map_re[v_id] = new_info.name;
            }

            // 更新顶点信息
            ver_list[v_id].data = new_info;        // 更新邻接表中的数据
            v_time[v_id] = new_info.visitTime;     // 更新参观时间
            v_type[v_id] = new_info.type;          // 更新顶点类型
        
        std::cerr << "LGraph::UpdateVertex(const LocationInfo &old_info, LocationInfo &new_info) 还没实现" << std::endl;
    }

    VertInfo LGraph::GetVertex(const std::string& name) const {
        //TODO:获取节点，由节点名查询节点信息
            int visitTime;       // 建议参观用时（单位：分钟）
            std::string type;
            int vertex = vertex_map.at(name);
            visitTime = v_time.at(vertex);
            type = v_type.at(vertex);


            //std::cerr << "LGraph::GetVertex(const Vertex vertex) 还没实现" << std::endl;
            //return VertInfo(name,visitTime,type);
            return VertInfo(name, visitTime, type);
            //std::cerr << "LGraph::GetVertex(const std::string &name) 还没实现" << std::endl;
        
        //return VertInfo();
    }

    VertInfo LGraph::GetVertex(const Vertex vertex) const {
        //未处理v不存在
        
        //TODO:获取节点，由节点的ID查询
        std::string name;         // 地点名称
        int visitTime;       // 建议参观用时（单位：分钟）
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
        //std::cerr << "LGraph::GetVertex(const Vertex vertex) 还没实现" << std::endl;
        //return VertInfo(name,visitTime,type);
        return VertInfo(name,visitTime,type);
    }

    void LGraph::InsertEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet weight) {
        //TODO:插入边
       
        if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
            throw Graph::GraphException(vertex_x_name + "or" + vertex_y_name + "要插入的边的顶点不存在");
        }
        if (exist_edge(vertex_x_name, vertex_y_name)) {
            throw Graph::GraphException(vertex_x_name + "_" + vertex_y_name + "要插入的边已存在");
        }
        //应该两地之间可以有两条边吧
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
        //std::cerr << "LGraph::InsertEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet weight) 还没实现" << std::endl;
    }

    void LGraph::DeleteEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) {
        //TODO:删除边，由两个节点名确定一条边
        if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
            throw GraphException(vertex_x_name+"or"+ vertex_y_name+"您要删除的顶点不存在");
        }
        if (!exist_edge(vertex_x_name, vertex_y_name)) {
            throw GraphException(vertex_x_name+"_"+ vertex_y_name+"您要删除边不存在");
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
        std::cout << "边"+ vertex_x_name + "-" + vertex_y_name +"删除成功" << std::endl;
            /*for (auto edge : edges) {
            if (edge.from == x && edge.dest == y) {
                edges.erase()
            }
        }*/
        //std::cerr << "LGraph::DeleteEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;

    }

    void LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) {
        //TODO:删除边，由两个节点ID确定一条边
        if (!exist_vertex(vertex_map_re[vertex_x]) || !exist_vertex(vertex_map_re[vertex_y])) {
            throw GraphException(std::to_string(vertex_x) + "or" + std::to_string( vertex_y) + "要删除的边的顶点不存在(id)");
        }
        if (!exist_edge(vertex_map_re[vertex_x], vertex_map_re[vertex_y])) {
            throw GraphException(std::to_string(vertex_x) + "-" + std::to_string(vertex_y)+"要删除的边不存在（id）");
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
        std::cout << "边(id)" + std::to_string(vertex_x) + "-" + std::to_string(vertex_y) + "删除成功" << std::endl;

        //std::cerr << "LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) 还没实现" << std::endl;
    }


    void LGraph::UpdateEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_weight) {
        //TODO:更新边，由两个节点名确定一条边
            // 检查顶点是否存在
            if (!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name)) {
                throw GraphException(vertex_x_name + "or" + vertex_y_name + "您要更新的顶点不存在");
            }

            // 检查边是否存在
            if (!exist_edge(vertex_x_name, vertex_y_name)) {
                throw GraphException(vertex_x_name+"-"+vertex_y_name + "您要更新的边不存在");
            }

            // 获取顶点ID
            Vertex x = vertex_map[vertex_x_name];
            Vertex y = vertex_map[vertex_y_name];

            // 更新x->y方向的边
            for (auto& edge : ver_list[x].adj) {
                if (edge.dest == y) {
                    edge.weight = new_weight;
                    break;
                }
            }

            // 更新edges容器中的边
            for (auto& edge : edges) {
                if (edge.from == x && edge.dest == y) {
                    edge.weight = new_weight;
                    break;
                }
            }

            // 如果是无向图，还需要更新y->x方向的边
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
            std::cout << "边" + vertex_x_name + "-" + vertex_y_name + "更新成功" << std::endl;
        //std::cerr << "LGraph::UpdateEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet new_weight) 还没实现" << std::endl;
    }

    GElemSet LGraph::GetEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:获取边的信息
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
        //std::cerr << "LGraph::GetEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;
        //return GElemSet();
    }

    std::vector<EdgeNode> LGraph::SortedEdges(std::function<bool(const GElemSet&, const GElemSet&)> cmp) const {
        //TODO:获取按边权和给定规则排序的所有边
        std::vector<EdgeNode> edg(edges.begin(),edges.end());
        sort(edg.begin(), edg.end());
        return edg;
        std::cerr << "LGraph::SortedEdges(std::function<bool(const GElemSet &, const GElemSet &)> cmp) 还没实现" << std::endl;
        return std::vector<EdgeNode>();
    }


}