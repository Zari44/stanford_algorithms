#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned int uint;
typedef std::vector<unsigned int> vint;
typedef std::vector<vint> vvector;
typedef std::vector<std::string> vstring;

class Graph
{
      void parse_input_line(string);
      void print_vector_int(vint);
      void get_random_edge();
      void edge_contraction();
      void concatinate_edges();
      void destroy_vertex();
      void destroy_self_loop();
      uint one_run_get_minimum_cut();

      vint N;
      vvector M;


      struct Edge{
          uint ni1;
          uint ni2;
      } edge;

    public:
      vint N_init;
      vvector M_init;
      void copy_graph_to_initial_state();
      Graph(string file_name);
      Graph();
      uint get_minimum_cut(uint number_of_runs);
      void print_edges();
      void print_vertices();
      uint get_number_of_edges();
      uint get_number_of_vertices();
};

#endif // GRAPH_H
