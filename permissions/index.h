// DEFINE
#ifndef PERMISSIONCOMMANDS_H
#define PERMISSIONCOMMANDS_H

#include "string"

using namespace std;

// PROPIEDADES
struct ChmodProps {
  bool recursive = 0;
  string path;
  string ugo;

  void set_prop(string value, string key) {
    if (key == "r") {
      recursive = 1;
    } else if (key == "path") {
      path = value;
    } else if (key == "ugo") {
      ugo = value;
    }
  }
};

// COMANDOS
class permission_commands {
public:
  permission_commands();

  // METODOS
  void chmod(ChmodProps props);
};

#endif // PERMISSIONCOMMANDS_H