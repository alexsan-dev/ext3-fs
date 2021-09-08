// DEFINE
#ifndef PARTITIONCOMMANDS_H
#define PARTITIONCOMMANDS_H

#include "string"

#include <iostream>

using namespace std;

struct Journal {
  char operation[10];
  char content[200];
  int permissions;
  char name[200];
  char owner[10];
  char date[17];
  char type;
};

struct SuperBlock {
  int free_blocks_count;
  int free_inodes_count;
  int filesystem_type;
  int bm_inode_start;
  int bm_block_start;
  int inodes_count;
  int blocks_count;
  int mount_count;
  char umtime[17];
  int first_inode;
  int first_block;
  int inode_start;
  int block_start;
  char mtime[17];
  int inode_size;
  int block_size;
  int magic;
};

struct Inode {
  char atime[17];
  char ctime[17];
  char mtime[17];
  int block[15];
  char type;
  int size;
  int perm;
  int uid;
  int gid;
};

struct Content {
  char name[12];
  int inodo;
};

struct DirBlock {
  Content content[4];
};

struct FileBlock {
  char content[64];
};

// PARTICIONES MONTADAS
struct MountedPartition {
  string name;
  string path;
  char type;
  string id;
  int start;
  int size;
};

// PARTICIONES
struct Partition {
  char name[16];
  char status;
  char type;
  int start;
  char fit;
  int size;
};

struct PartitionFsProps {
  string id = "";
  string type = "full";
  string fs = "2fs";

  void set_prop(string value, string key) {
    if (key == "id") {
      id = value;
    } else if (key == "type") {
      type = value;
    } else if (key == "fs") {
      fs = value;
    }
  }
};

// PROPIEDADES DE COMANDOS
struct PartitionCommandsProps {
  char unit = 'K'; // OPCIONAL
  char fit = 'W';  // OPCIONAL
  char type = 'P'; // OPCIONAL
  string del = ""; // OPCIONAL
  int add = 0;     // OPCIONAL
  string path = "";
  string name = "";
  int size = 0;

  void set_prop(string value, string key) {
    if (key == "unit") {
      unit = toupper(value.at(0));
    } else if (key == "fit") {
      fit = toupper(value.at(0));
    } else if (key == "type") {
      type = toupper(value.at(0));
    } else if (key == "del") {
      del = value;
    } else if (key == "add") {
      add = (int)stoi(value);
    } else if (key == "path") {
      path = value;
    } else if (key == "name") {
      name = value;
    } else if (key == "size") {
      size = (int)stoi(value);
    }
  }
};

// COMANDOS
class partition_commands {
public:
  partition_commands();

  // METODOS
  void fdisk(PartitionCommandsProps props, bool preserve = 0);
  void mount(string path, string name);
  void mkfs(PartitionFsProps props);
  void unmount(string id);
};

extern int max_logical_partitions;

MountedPartition get_current_partition(string id);

#endif // PARTITIONCOMMANDS_H