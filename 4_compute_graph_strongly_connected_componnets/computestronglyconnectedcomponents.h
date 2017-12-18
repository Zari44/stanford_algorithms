#ifndef COMPUTESTRONGLYCONNECTEDCOMPONENTS_H
#define COMPUTESTRONGLYCONNECTEDCOMPONENTS_H

#include <list>
#include <stack>
#include "graph.h"


class ComputeStronglyConnectedComponents
{
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing time
    static void fillOrder(Graph& graph, int v, bool visited[], stack<int> &Stack);
    static void printSCCs(list<int>& sccs, int sccs_to_print);
public:
    static void computeAndPrintSCCs(Graph& graph, int sccs_to_print);
};

#endif // COMPUTESTRONGLYCONNECTEDCOMPONENTS_H
