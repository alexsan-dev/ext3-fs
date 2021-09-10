// DEFINE
#ifndef GRAPHCOMMANDS_H
#define GRAPHCOMMANDS_H

#include "string"

// PROPIEDADES
struct RepProps {
  string name;
  string path;
  string id;
  string ruta;
  string root;

  void set_props(string value, string key) {
    if (key == "name") {
      name = value;
    } else if (key == "path") {
      path = value;
    } else if (key == "id") {
      id = value;
    } else if (key == "ruta") {
      ruta = value;
    } else if (key == "root") {
      root = value;
    }
  }
};

// COMANDOS
class graph_commands {
public:
  graph_commands();

  // METODOS
  void rep(RepProps props);
};

#endif // GRAPHCOMMANDS_H