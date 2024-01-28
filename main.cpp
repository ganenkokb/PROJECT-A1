#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Судя по содержимому это вершина, Vertex или Node. Принято назыать Node
// Нужно другой подход реализовать - более каноничный
// у тебя есть Node которая ссылается на другие Node (список указателей) и Graph это просто список нодов
// Функция IsTree просто отдельная. Классы можно просто сделать структурами.
class Graph {
protected:
    int V;
    std::list<int> *adj;

public:
    Graph(int V) : V(V) {
        adj = new std::list<int>[V];
    }

    virtual ~Graph() {
        delete[] adj;
    }

    void addEdge(int v, int w) {
        adj[v - 1].push_back(w - 1);
        adj[w - 1].push_back(v - 1);
    }
};

class Tree : public Graph {
private:
    bool DFS(int v, std::vector<bool> &visited, int parent) {
        visited[v] = true;
        for (int i : adj[v]) {
            if (!visited[i]) {
                if (!DFS(i, visited, v))
                    return false;
            } else if (i != parent) {
                return false;
            }
        }
        return true;
    }

public:
    Tree(int V) : Graph(V) {}

    bool isTree() {
        std::vector<bool> visited(V, false);
        if (!DFS(0, visited, -1))
            return false;
        for (int i = 0; i < V; i++)
            if (!visited[i])
                return false;
        return true;
    }
};

int main() {
    std::string line;
    std::ifstream file("/Users/grpmgk/Desktop/untitled folder/Project/Project/file.txt");
    // 1 Тут кажется можно было относительный путь укзаТЬ, например file.txt 
    if (!file) {    // Хм, не знал что такая проверка работает
        std::cerr << "Ошибка при открытии файла." << std::endl; // Пиши комменты на английском
        return 1;
    }

    int maxVertex = 0;
    std::vector<std::pair<int, int>> edges;

    // В принципе норм парсинг, в xml тебе придется по символьно парсить...
    while (getline(file, line)) {
        std::istringstream iss(line);
        int v1, v2;
        if (iss >> v1 >> v2) {
            edges.emplace_back(v1, v2);
            maxVertex = std::max(maxVertex, std::max(v1, v2));
        }
    }

    Tree tree(maxVertex);
    for (const auto& edge : edges) {
        tree.addEdge(edge.first, edge.second);
    }

    if (tree.isTree()) {
        std::cout << "Граф является деревом." << std::endl;
    } else {
        std::cout << "Граф не является деревом." << std::endl;
    }
    return 0;
}
