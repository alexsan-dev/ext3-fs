// DEFINE
#ifndef DISKCOMMANDS_H
#define DISKCOMMANDS_H

#include "../partitions/index.h"
#include "string"
#include <map>

#include <iostream>

using namespace std;

// EXTENDED BOOT RECORD
struct EBR {
  char name[16];
  char status;
  int start;
  char fit;
  int size;
  int next;
};

// MASTER BOOT RECORD
struct MBR {
  Partition partitions[4];
  char date[17];
  int signature;
  char fit;
  int size;
};

// PROPIEDADES DE COMANDOS
struct DiskCommandsProps {
  char unit = 'M'; // OPCIONAL
  char fit = 'F';  // OPCIONAL
  string path = "";
  int size = -1;

  void set_prop(string value, string name) {
    if (name == "unit") {
      unit = toupper(value.at(0));
    } else if (name == "fit") {
      fit = toupper(value.at(0));
    } else if (name == "path") {
      path = value;
    } else if (name == "size") {
      size = (int)stoi(value);
    }
  }
};

// COMANDOS
class disk_commands {
public:
  disk_commands();

  // METODOS
  void mkdisk(DiskCommandsProps props);
  void get_disk_graph(string disk_path, string path);
  void rmdisk(string path);
};

#endif // DISKCOMMANDS_H