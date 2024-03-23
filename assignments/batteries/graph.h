#pragma once

#include <vector>

template <class T>
class Graph
{
public:
  Graph() = default;
  Graph(int width, int height) : width(width), height(height) { data.reserve(width * height); }
  Graph(Graph<T> &grid) { data = grid.data; }
  ~Graph() { data.clear(); }

  T &operator()(int x, int y) { return data[x + y * width]; }
  const T &operator()(int x, int y) const { return data[x + y * width]; }

  T Get(int x, int y) const { return data[x + y * width]; }
  void Set(int x, int y, T value) { data[x + y * width] = value; }

  void Clear()
  {
    data.clear();
  }

  void Resize(int width, int height)
  {
    this->width = width;
    this->height = height;
    data.resize(width * height);
  }

private:
  int width = 0;
  int height = 0;

  std::vector<T> data;
  std::vector<Node> edges;
};

// #include <iostream>
// using namespace std;
// // stores adjacency list items
// struct adjNode {
//     int val, cost;
//     adjNode* next;
// };
// // structure to store edges
// struct graphEdge {
//     int start_ver, end_ver, weight;
// };
// class DiaGraph{
//     // insert new nodes into adjacency list from given graph
//     adjNode* getAdjListNode(int value, int weight, adjNode* head)   {
//         adjNode* newNode = new adjNode;
//         newNode->val = value;
//         newNode->cost = weight;
//         newNode->next = head;   // point new node to current head
//         return newNode;
//     }
//     int N;  // number of nodes in the graph
// public:
//     adjNode **head;                //adjacency list as array of pointers
//     // Constructor
//     DiaGraph(graphEdge edges[], int n, int N)  {
//         // allocate new node
//         head = new adjNode*[N]();
//         this->N = N;
//         // initialize head pointer for all vertices
//         for (int i = 0; i < N; ++i)
//             head[i] = nullptr;
//         // construct directed graph by adding edges to it
//         for (unsigned i = 0; i < n; i++)  {
//             int start_ver = edges[i].start_ver;
//             int end_ver = edges[i].end_ver;
//             int weight = edges[i].weight;
//             // insert in the beginning
//             adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);

//                         // point head pointer to new node
//             head[start_ver] = newNode;
//              }
//     }
//       // Destructor
//      ~DiaGraph() {
//     for (int i = 0; i < N; i++)
//         delete[] head[i];
//         delete[] head;
//      }
// };