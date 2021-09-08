// DEFINE
#ifndef NODESCOMMANDS_H
#define NODESCOMMANDS_H

#include "../partitions/index.h"
#include "string"
#include <iostream>
#include <vector>

using namespace std;

// COMANDOS
class node_commands {
public:
  node_commands();

  // METODOS
  void mkdir(string path, bool create);
  void mkfile(string content, string path, bool create);
};

extern void get_tree_graph();
extern void print_bitmaps();

#endif // NODESCOMMANDS_H