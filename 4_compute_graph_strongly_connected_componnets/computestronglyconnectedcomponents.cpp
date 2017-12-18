#include "computestronglyconnectedcomponents.h"
#include <vector>
#include <iostream>
using namespace std;

void ComputeStronglyConnectedComponents::fillOrder(Graph& graph, int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for(vector<int>::iterator i = graph.adjacency[v].begin(); i != graph.adjacency[v].end(); ++i)
        if(!visited[*i])
            fillOrder(graph, *i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
void ComputeStronglyConnectedComponents::computeAndPrintSCCs(Graph& graph, int sccs_to_print)
{
    stack<int> Stack;
    list<int> computed_scc;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[graph._number_of_vertices];
    for(int i = 0; i < graph._number_of_vertices; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < graph._number_of_vertices; i++)
        if(visited[i] == false)
            fillOrder(graph, i, visited, Stack);

    // Create a reversed graph
    Graph graph_transposed = graph.getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < graph._number_of_vertices; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (!Stack.empty())
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            unsigned int scc = 0;
            scc = graph_transposed.DFS(v, visited, scc);
            computed_scc.push_back(scc);
        }
    }

    printSCCs(computed_scc, sccs_to_print);
}

void ComputeStronglyConnectedComponents::printSCCs(list<int> &computed_scc, int sccs_to_print)
{
    computed_scc.sort();

    cout << sccs_to_print << " largest strongly connected components \n"
                             "sizes of a given graph are : " << endl;
    for (uint i = 0; i < sccs_to_print; ++i)
    {
        if (computed_scc.empty())
            break;
        cout << computed_scc.back() << endl;
        computed_scc.pop_back();
    }
    cout << endl;
}
