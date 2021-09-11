// DEFINE
#ifndef NODESCOMMANDS_H
#define NODESCOMMANDS_H

#include "../partitions/index.h"
#include "string"
#include <iostream>
#include <vector>

using namespace std;

struct ListProp {
  vector<string> list;
};

struct TouchProps {
  string path;
  bool r = 0;
  int size = 0;
  bool stdinR = 0;
  string cont = "";

  void set_prop(string value, string key) {
    if (key == "path") {
      path = value;
    } else if (key == "r") {
      r = 1;
    } else if (key == "size") {
      size = (int)stoi(value);
    } else if (key == "stdin") {
      stdinR = 1;
    } else if (key == "cont") {
      cont = value;
    }
  }
};

// COMANDOS
class node_commands {
public:
  node_commands();

  // METODOS
  void mkdir(string path, bool create);
  void mkfile(string content, string path, bool create);
  void touch(TouchProps props);
  void cat(ListProp files);
  void rm(string path);
};

extern void get_tree_graph(string disk_path, string path, int part_start,
                           string root = "/");
extern void print_bitmaps();
extern bool has_permissions(Inode current_inode, int key);

#endif // NODESCOMMANDS_H