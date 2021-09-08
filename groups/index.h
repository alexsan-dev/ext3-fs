// DEFINE
#ifndef GROUPCOMMANDS_H
#define GROUPCOMMANDS_H

#include "string"

using namespace std;

// COMMANDOS
class group_commands {
public:
  group_commands();

  // METODOS
  void mkgrp(string name);
  void rmgrp(string name);
};

#endif // GROUPCOMMANDS_H