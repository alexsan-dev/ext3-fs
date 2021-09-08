#include "../env/index.h"
#include "../users/index.h"
#include "../utils/tools/index.h"
#include "index.h"

#include <deque>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <vector>

using namespace std;

node_commands::node_commands() {}

/**
 * Imprimir bitmap de inodos y bitmap de blocks
 * @brief Genera una grafica de arbol
 */
void print_bitmaps() {
  MountedPartition current_partition = get_current_partition(global_user.id);

  // LEER SUPERBLOQUE
  SuperBlock superblock;
  int partition_start = current_partition.start;
  FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    fseek(disk_file, partition_start, SEEK_SET);
    fread(&superblock, sizeof(SuperBlock), 1, disk_file);

    // BITMAP DE INODOS Y BLOQUES
    char bitinodes[superblock.inodes_count];
    char bitblocks[superblock.blocks_count];

    fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
    fread(bitinodes, superblock.inodes_count, 1, disk_file);

    fseek(disk_file, superblock.bm_block_start, SEEK_SET);
    fread(bitblocks, superblock.blocks_count, 1, disk_file);

    cout << "BITMAP DE INODOS:\n" << bitinodes << "\n\n";
    cout << "BITMAP DE BLOQUES:\n" << bitblocks << "\n";
  }
}

/**
 * Graficar
 * @brief Genera una grafica de arbol
 */
void get_tree_graph() {
  MountedPartition current_partition = get_current_partition(global_user.id);

  // LEER SUPERBLOQUE
  SuperBlock superblock;
  int partition_start = current_partition.start;
  FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    fseek(disk_file, partition_start, SEEK_SET);
    fread(&superblock, sizeof(SuperBlock), 1, disk_file);

    string dot_path = "./reports/assets/";
    string dot_name = dot_path + "tree.dot";
    FILE *dot_file = fopen(dot_name.c_str(), "w+");

    // EXISTE
    if (dot_file != NULL) {
      // GENERAR DOT
      string dot = "digraph G {graph[rankdir=LR, overlap=false, "
                   "splines=true];node[shape = record, fontsize = 9, fontname "
                   "= \"Verdana\"];";

      // BITMAP DE INODOS Y BLOQUES
      char bitinodes[superblock.inodes_count];
      char bitblocks[superblock.blocks_count];

      fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
      fread(bitinodes, superblock.inodes_count, 1, disk_file);

      fseek(disk_file, superblock.bm_block_start, SEEK_SET);
      fread(bitblocks, superblock.blocks_count, 1, disk_file);

      Inode first_inode;
      int inode_start = superblock.inode_start;
      fseek(disk_file, inode_start, SEEK_SET);
      fread(&first_inode, sizeof(Inode), 1, disk_file);

      // RECORRER
      deque<Inode> inodes;
      deque<int> inode_starts;
      inodes.push_back(first_inode);
      inode_starts.push_back(inode_start);

      while (inodes.size() > 0) {
        Inode current_inode = inodes.at(0);
        inode_start = inode_starts.at(0);
        inodes.pop_front();
        inode_starts.pop_front();

        string atime(current_inode.atime);
        string ctime(current_inode.ctime);
        string mtime(current_inode.mtime);

        string inode_id = "INode" + to_string(inode_start);
        int sup_inode_index =
            (int)(((superblock.inode_start - inode_start) * -1) /
                  sizeof(Inode));

        dot +=
            inode_id +
            " [shape=none, margin=0, label=<<table "
            "border=\"0\" "
            "cellborder=\"1\" cellspacing=\"0\" cellpadding=\"4\">" +
            "<tr><td bgcolor=\"#03A9F4\"><font color=\"white\"><b>INode" +
            to_string(sup_inode_index) + "</b></font></td></tr>" +
            "<tr><td bgcolor=\"#b3e5fc\">Append time: " + atime + "</td></tr>" +
            "<tr><td bgcolor=\"#e1f5fe\">Creation time: " + ctime +
            "</td></tr>" + "<tr><td bgcolor=\"#b3e5fc\">Modify time: " + mtime +
            "</td></tr>" + "<tr><td bgcolor=\"#e1f5fe\">Type: " +
            (current_inode.type == '1' ? "Directory" : "File") + "</td></tr>" +
            "<tr><td bgcolor=\"#b3e5fc\">Size: " +
            to_string(current_inode.size) + "</td></tr>" +
            "<tr><td bgcolor=\"#e1f5fe\">Permissions: " +
            to_string(current_inode.perm) + "</td></tr>" +
            "<tr><td bgcolor=\"#b3e5fc\">UID: " + to_string(current_inode.uid) +
            "</td></tr>" +
            "<tr><td bgcolor=\"#e1f5fe\">GID: " + to_string(current_inode.gid) +
            "</td></tr>";

        for (int block_index = 0; block_index < 15; block_index++) {
          if (current_inode.block[block_index] != -1) {
            string color = block_index % 2 == 0 ? "b3e5fc" : "e1f5fe";
            int sup_block_index = (int)(((superblock.block_start -
                                          current_inode.block[block_index]) *
                                         -1) /
                                        sizeof(FileBlock));

            dot += "<tr><td bgcolor=\"#" + color + "\">Block " +
                   to_string(block_index + 1) + ": #" +
                   to_string(sup_block_index) + "</td></tr>";
          }
        }

        dot += "</table>>];";

        for (int block_index = 0; block_index < 15; block_index++) {
          if (current_inode.block[block_index] != -1) {
            int sup_block_index = (int)(((superblock.block_start -
                                          current_inode.block[block_index]) *
                                         -1) /
                                        sizeof(FileBlock));

            if (current_inode.type == '1') {
              DirBlock dir_block;
              fseek(disk_file, current_inode.block[block_index], SEEK_SET);
              fread(&dir_block, sizeof(DirBlock), 1, disk_file);

              string block_id = inode_id + "_bloque_" + to_string(block_index);
              dot += block_id +
                     " [shape=none, margin=0, label=<<table border=\"0\" "
                     "cellborder=\"1\" cellspacing=\"0\" cellpadding=\"4\">" +
                     "<tr><td bgcolor=\"#ff6f00\"><font "
                     "color=\"white\"><b>" +
                     "Block " + to_string(sup_block_index) +
                     "</b></font></td></tr></table>>];";
              dot += inode_id + " -> " + block_id + ";";

              // BUSCAR CONTENIDO
              for (int content_index = 0; content_index < 4; content_index++) {
                if (dir_block.content[content_index].inodo != -1) {
                  string block_name(dir_block.content[content_index].name);
                  string content_id =
                      block_id + "_content_" + to_string(content_index);
                  int next_inode_start = dir_block.content[content_index].inodo;
                  int next_inode_index =
                      (int)(((superblock.inode_start - next_inode_start) * -1) /
                            sizeof(Inode));

                  dot += content_id +
                         " [shape=none, margin=0, label=<<table border=\"0\" "
                         "cellborder=\"1\" cellspacing=\"0\" "
                         "cellpadding=\"4\">" +
                         "<tr><td bgcolor=\"#4caf50\"><font "
                         "color=\"white\"><b>Directory "
                         "Content</b></font></td></tr>" +
                         "<tr><td bgcolor=\"#a5d6a7\">Name: " + block_name +
                         "</td></tr>" + "<tr><td bgcolor=\"#c8e6c9\">INode: " +
                         to_string(next_inode_index) + "</td></tr>" +
                         "</table>>];";
                  dot += block_id + " -> " + content_id + " [label=\"" +
                         to_string(content_index + 1) + "\"];";

                  Inode tmp_inode;
                  fseek(disk_file, next_inode_start, SEEK_SET);
                  fread(&tmp_inode, sizeof(Inode), 1, disk_file);

                  inodes.push_back(tmp_inode);
                  inode_starts.push_back(next_inode_start);
                  dot += content_id + " -> " + "INode" +
                         to_string(next_inode_start) + ";";
                }
              }
            } else {
              FileBlock file_block;
              fseek(disk_file, current_inode.block[block_index], SEEK_SET);
              fread(&file_block, sizeof(FileBlock), 1, disk_file);

              string file_content(file_block.content);

              std::string::size_type n = 0;
              string breakline = "\n";
              string br = "<br/>";
              while ((n = file_content.find(breakline, n)) !=
                     std::string::npos) {
                file_content.replace(n, breakline.size(), br);
                n += br.size();
              }

              string block_id = inode_id + "_bloque_" + to_string(block_index);
              dot += block_id +
                     " [shape=none, margin=0, label=<<table "
                     "border=\"0\" "
                     "cellborder=\"1\" cellspacing=\"0\" cellpadding=\"4\">" +
                     "<tr><td bgcolor=\"#FFC107\"><font "
                     "color=\"white\"><b>" +
                     "Block " + to_string(sup_block_index) +
                     "</b></font></td></tr><tr><td "
                     "bgcolor=\"#FFF9C4\">" +
                     file_content + "     </td></tr></table>>];";
              dot += inode_id + " -> " + block_id + ";";
            }
          }
        }
      }

      dot += "}";
      fwrite(dot.c_str(), dot.length(), 1, dot_file);
      fclose(dot_file);

      // GENERAR IMAGEN
      string dot_svg = "dot -Tsvg " + dot_name + " -o " + dot_path + "tree.svg";
      system(dot_svg.c_str());
    }

    fclose(disk_file);
  }
}

/**
 * Agregar Journal
 * @brief Crea un journal en la sigueinte posicion
 * @param {Journal} data
 * @param {SuperBlock} superblock
 * @param {FILE} *disk_file
 */
void add_journal(Journal data, SuperBlock superblock, FILE *disk_file) {
  if (superblock.filesystem_type == 3) {
    int journal_start = superblock.bm_inode_start - (sizeof(Journal) * 100);
    fseek(disk_file, journal_start, SEEK_SET);

    // BUSCAR SIGUIENTE JOURNAL
    int next_journal_index = 0;
    for (int journal_index = 0; journal_index < 100; journal_index++) {
      Journal tmp_journal;
      fseek(disk_file, journal_start + (sizeof(Journal) * journal_index),
            SEEK_SET);
      if (tmp_journal.operation[0] == '-') {
        next_journal_index = journal_index;
        break;
      }
    }

    // GUARDAR
    fseek(disk_file, journal_start + (sizeof(Journal) * next_journal_index),
          SEEK_SET);
    fwrite(&data, sizeof(Journal), 1, disk_file);
  }
}

/**
 * Crear carpeta
 * @brief Crea una carpeta en el sistema de archivos
 * @param {string} path
 * @param {bool} create
 */
void node_commands::mkdir(string path, bool create) {
  MountedPartition current_partition = get_current_partition(global_user.id);

  // LEER SUPERBLOQUE
  SuperBlock superblock;
  int partition_start = current_partition.start;
  FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    fseek(disk_file, partition_start, SEEK_SET);
    fread(&superblock, sizeof(SuperBlock), 1, disk_file);

    // BITMAP DE INODOS Y BLOQUES
    char bitinodes[superblock.inodes_count];
    char bitblocks[superblock.blocks_count];

    fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
    fread(&bitinodes, sizeof(bitinodes), 1, disk_file);

    fseek(disk_file, superblock.bm_block_start, SEEK_SET);
    fread(&bitblocks, sizeof(bitblocks), 1, disk_file);

    // BUSCAR PRIMER INODO Y BLOQUE LIBRE
    int current_inode_index = superblock.first_inode;
    int current_block_index = 0;

    // GLOBALES
    string now_date = get_now();
    vector<string> path_components = split(path, '/');
    string new_path = path.at(path_components.size() - 1) == '/'
                          ? path.substr(0, path.size() - 2)
                          : path;
    int path_cmp_size = path_components.size();
    path_components.at(0) = "/";

    // PRIMER INODO
    if (path_cmp_size == 1) {
      Inode first_inode;
      strcpy(first_inode.atime, now_date.c_str());
      strcpy(first_inode.ctime, now_date.c_str());
      strcpy(first_inode.mtime, now_date.c_str());

      for (int block_index = 0; block_index < 15; block_index++) {
        first_inode.block[block_index] = -1;
      }

      first_inode.type = '1';
      first_inode.size = 0;
      first_inode.perm = 664;
      first_inode.uid = (int)stoi(global_user.uid);
      first_inode.gid = (int)stoi(global_user.grp);

      fseek(disk_file, superblock.inode_start, SEEK_SET);
      fwrite(&first_inode, sizeof(Inode), 1, disk_file);

      bitblocks[0] = '1';
      bitinodes[0] = '1';
    } else {
      bool recursive = 0;
      Inode current_inode;
      int inode_start = superblock.inode_start;
      fseek(disk_file, inode_start, SEEK_SET);
      fread(&current_inode, sizeof(Inode), 1, disk_file);

      int path_counter = 1;
      int next_inode_index = current_inode_index;

      // CREAR CARPETAS SI NO EXISTEN
      string segment_dir;
      vector<string> empty_dirs;
      Inode tmp_inode = current_inode;
      for (int path_index = 1; path_index < path_components.size() - 1;
           path_index++) {
        bool exists_dir = 0;
        segment_dir += "/" + path_components.at(path_index);
        empty_dirs.push_back(segment_dir);

        for (int block_index = 0; block_index < 15; block_index++) {
          if (tmp_inode.block[block_index] != -1) {
            DirBlock dir_block;
            fseek(disk_file, tmp_inode.block[block_index], SEEK_SET);
            fread(&dir_block, sizeof(DirBlock), 1, disk_file);

            // BUSCAR CONTENIDO
            for (int content_index = 0; content_index < 4; content_index++) {
              if (dir_block.content[content_index].inodo != -1) {
                string block_name(dir_block.content[content_index].name);
                if (block_name == path_components.at(path_index)) {
                  fseek(disk_file, dir_block.content[content_index].inodo,
                        SEEK_SET);
                  fread(&tmp_inode, sizeof(Inode), 1, disk_file);
                  exists_dir = 1;
                }
              }
            }
          }
        }

        // NO EXISTE
        if (!exists_dir) {
          recursive = 1;
        }
      }

      // CREAR CARPETAS FALTANTES
      if (recursive) {
        if (create) {
          for (int path_index = 0; path_index < empty_dirs.size();
               path_index++) {
            mkdir(empty_dirs.at(path_index), 0);
          }
          mkdir(new_path, 0);
        } else {
          print_err("NODES_ERR",
                    "La ruta no existe, intenta con el parametro -p.");
        }
        return;
      }

      // BUSCAR INODO
      for (int path_index = 0; path_index < path_components.size();
           path_index++) {
        for (int block_index = 0; block_index < 15; block_index++) {
          if (current_inode.block[block_index] != -1) {
            DirBlock dir_block;
            fseek(disk_file, current_inode.block[block_index], SEEK_SET);
            fread(&dir_block, sizeof(DirBlock), 1, disk_file);

            // BUSCAR CONTENIDO
            for (int content_index = 0; content_index < 4; content_index++) {
              if (dir_block.content[content_index].inodo != -1) {
                string block_name(dir_block.content[content_index].name);

                if (block_name == path_components.at(path_index)) {
                  path_counter++;
                  inode_start = dir_block.content[content_index].inodo;
                  fseek(disk_file, inode_start, SEEK_SET);
                  fread(&current_inode, sizeof(Inode), 1, disk_file);
                  next_inode_index =
                      (int)(((superblock.inode_start - inode_start) * -1) /
                            sizeof(Inode));
                }
              }
            }
          }
        }
      }

      // USAR INODO
      bool repeated_dir = path_counter == path_components.size();
      current_inode_index =
          repeated_dir ? next_inode_index : current_inode_index;
      bitinodes[current_inode_index] = '1';

      if (!repeated_dir)
        superblock.free_inodes_count = superblock.free_inodes_count - 1;

      bool is_new_block = 0;
      bool free_block_inside = 0;
      int block_position[2] = {0, 1};

      // BUSQUEDA EN APUNTADORES DIRECTOS
      for (int block_index = 0; block_index < 15; block_index++) {
        // BLOQUE OCUPADO
        if (current_inode.block[block_index] != -1) {
          // BLOQUE ACTUAL
          DirBlock current_block;
          block_position[0] = block_index;
          fseek(disk_file, current_inode.block[block_index], SEEK_SET);
          fread(&current_block, sizeof(DirBlock), 1, disk_file);

          // BUSCAR ESPACIO EN CONTENIDO DEL BLOQUE
          for (int ct_index = 0; ct_index < 4; ct_index++) {
            block_position[1] = ct_index;
            Content content = current_block.content[ct_index];
            if (content.inodo == -1) {
              free_block_inside = 1;
              break;
            }
          }

          // PRIMER BLOQUE LIBRE
          if (free_block_inside) {
            break;
          }
        }
        // SINO CREAR UN NUEVO BLOQUE
        else {
          block_position[0] = block_index;
          block_position[1] = 0;
          free_block_inside = 1;
          is_new_block = 1;
          break;
        }
      }

      // SE ENCONTRO UN BLOQUE DISPONIBLE
      if (free_block_inside && !repeated_dir) {
        // CREAR UN CONTENIDO
        Content new_block_content;
        strcpy(new_block_content.name,
               path_components.at(path_components.size() - 1).c_str());

        // CREAR UN NUEVO INODO
        Inode new_inode;
        strcpy(new_inode.atime, now_date.c_str());
        strcpy(new_inode.ctime, now_date.c_str());
        strcpy(new_inode.mtime, now_date.c_str());
        new_inode.type = '1';
        new_inode.size = 0;
        new_inode.perm = 664;
        new_inode.uid = (int)stoi(global_user.uid);
        new_inode.gid = (int)stoi(global_user.gid);
        for (int block_index = 0; block_index < 15; block_index++) {
          new_inode.block[block_index] = -1;
        }

        new_block_content.inodo =
            superblock.inode_start + (sizeof(Inode) * current_inode_index);
        fseek(disk_file, new_block_content.inodo, SEEK_SET);
        fwrite(&new_inode, sizeof(Inode), 1, disk_file);

        DirBlock current_block;
        if (!is_new_block) {
          fseek(disk_file, current_inode.block[block_position[0]], SEEK_SET);
          fread(&current_block, sizeof(DirBlock), 1, disk_file);
          current_block_index =
              (int)(((superblock.block_start -
                      current_inode.block[block_position[0]]) *
                     -1) /
                    sizeof(DirBlock));

        } else {
          for (int content_index = 0; content_index < 4; content_index++) {
            current_block.content[content_index] = (Content){{}, -1};
          }

          // OCUPAR UN NUEVO BLOQUE
          superblock.free_blocks_count = superblock.free_blocks_count - 1;
          current_block_index = superblock.first_block;
          bitblocks[current_block_index] = '1';
        }

        current_block.content[block_position[1]] = new_block_content;
        current_inode.block[block_position[0]] =
            superblock.block_start + (sizeof(FileBlock) * current_block_index);

        // GUARDAR BLOQUE DE INODO PADRE
        fseek(disk_file, current_inode.block[block_position[0]], SEEK_SET);
        fwrite(&current_block, sizeof(DirBlock), 1, disk_file);

        // CAMBIOS EN INODO PADRE
        strcpy(current_inode.atime, now_date.c_str());
        strcpy(current_inode.mtime, now_date.c_str());

        fseek(disk_file, inode_start, SEEK_SET);
        fwrite(&current_inode, sizeof(Inode), 1, disk_file);
      }
    }

    // ASIGNAR A SUPERBLOQUE
    int first_sp_inode = 0;
    int first_sp_block = 0;
    for (int inode_index = 0; inode_index < sizeof(bitinodes); inode_index++) {
      if (bitinodes[inode_index] == '0') {
        first_sp_inode = inode_index;
        break;
      }
    }

    for (int block_index = 0; block_index < sizeof(bitblocks); block_index++) {
      if (bitblocks[block_index] == '0') {
        first_sp_block = block_index;
        break;
      }
    }

    // GUARDAR CAMBIOS EN SUPERBLOQUE Y EN BITNODES
    superblock.first_inode = first_sp_inode;
    superblock.first_block = first_sp_block;

    fseek(disk_file, partition_start, SEEK_SET);
    fwrite(&superblock, sizeof(SuperBlock), 1, disk_file);

    fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
    fwrite(&bitinodes, sizeof(bitinodes), 1, disk_file);

    fseek(disk_file, superblock.bm_block_start, SEEK_SET);
    fwrite(&bitblocks, sizeof(bitblocks), 1, disk_file);

    // AGREGAR NUEVO JOURNAL
    Journal new_journal;
    string operation = "mkdir";
    new_journal.permissions = 664;
    new_journal.name[0] = '0';
    new_journal.type = '1';
    strcpy(new_journal.operation, operation.c_str());
    strcpy(new_journal.content, new_path.c_str());
    strcpy(new_journal.owner, global_user.user.c_str());
    strcpy(new_journal.date, now_date.c_str());
    add_journal(new_journal, superblock, disk_file);

    fclose(disk_file);
  } else
    print_err("NODES_ERR", "El disco no existe.");
}

/**
 * Crear archivo
 * @brief Crea un archivo en el sistema de archivos
 * @param {string} content
 * @param {string} path
 * @param {bool} create
 */
void node_commands::mkfile(string content, string path, bool create) {
  MountedPartition current_partition = get_current_partition(global_user.id);

  // LEER SUPERBLOQUE
  SuperBlock superblock;
  int partition_start = current_partition.start;
  FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    // RUTA
    string now_date = get_now();
    vector<string> path_components = split(path, '/');
    int path_cmp_size = path_components.size();
    path_components.at(0) = "/";

    string file_name = path_components.at(path_components.size() - 1).c_str();

    // CREAR CARPETAS
    if (path_cmp_size > 2 && create) {
      string parent_next_dir;
      for (int path_index = 1; path_index < path_cmp_size - 1; path_index++) {
        parent_next_dir += "/" + path_components.at(path_index);
      }
      mkdir(parent_next_dir, 1);
    }

    fseek(disk_file, partition_start, SEEK_SET);
    fread(&superblock, sizeof(SuperBlock), 1, disk_file);

    // BITMAP DE INODOS Y BLOQUES
    char bitinodes[superblock.inodes_count];
    char bitblocks[superblock.blocks_count];

    fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
    fread(&bitinodes, sizeof(bitinodes), 1, disk_file);

    fseek(disk_file, superblock.bm_block_start, SEEK_SET);
    fread(&bitblocks, sizeof(bitblocks), 1, disk_file);

    // GLOBALES
    int current_inode_index = superblock.first_inode;
    int current_block_index = 0;

    Inode current_inode;
    int inode_start = superblock.inode_start;

    fseek(disk_file, inode_start, SEEK_SET);
    fread(&current_inode, sizeof(Inode), 1, disk_file);

    // BUSCAR INODO
    for (int path_index = 0; path_index < path_cmp_size; path_index++) {
      for (int block_index = 0; block_index < 15; block_index++) {
        if (current_inode.block[block_index] != -1) {
          DirBlock dir_block;
          fseek(disk_file, current_inode.block[block_index], SEEK_SET);
          fread(&dir_block, sizeof(DirBlock), 1, disk_file);

          // BUSCAR CONTENIDO
          for (int content_index = 0; content_index < 4; content_index++) {
            if (dir_block.content[content_index].inodo != -1) {
              string block_name(dir_block.content[content_index].name);

              if (block_name == path_components.at(path_index)) {
                Inode tmp_inode;

                fseek(disk_file, dir_block.content[content_index].inodo,
                      SEEK_SET);
                fread(&tmp_inode, sizeof(Inode), 1, disk_file);

                // ES UN INODO DE CARPETA
                if (tmp_inode.type == '1') {
                  inode_start = dir_block.content[content_index].inodo;
                  current_inode = tmp_inode;
                }
              }
            }
          }
        }
      }
    }

    bool same_file = 0;
    bool is_new_block = 0;
    bool free_block_inside = 0;
    int block_position[2] = {0, 1};

    // BUSQUEDA EN APUNTADORES DIRECTOS
    for (int block_index = 0; block_index < 15; block_index++) {
      // BLOQUE OCUPADO
      if (current_inode.block[block_index] != -1) {
        // BLOQUE ACTUAL
        DirBlock current_block;
        block_position[0] = block_index;
        fseek(disk_file, current_inode.block[block_index], SEEK_SET);
        fread(&current_block, sizeof(DirBlock), 1, disk_file);

        // BUSCAR ESPACIO EN CONTENIDO DEL BLOQUE
        for (int ct_index = 0; ct_index < 4; ct_index++) {
          block_position[1] = ct_index;
          Content content = current_block.content[ct_index];

          if (content.inodo == -1) {
            free_block_inside = 1;
            break;
          } else {
            string content_name(content.name);
            if (content_name == file_name) {
              free_block_inside = 1;
              same_file = 1;
              break;
            }
          }
        }

        // PRIMER BLOQUE LIBRE
        if (free_block_inside) {
          break;
        }
      }
      // SINO CREAR UN NUEVO BLOQUE
      else {
        block_position[0] = block_index;
        block_position[1] = 0;
        free_block_inside = 1;
        is_new_block = 1;
        break;
      }
    }

    // SE ENCONTRO UN BLOQUE DISPONIBLE
    if (free_block_inside) {
      // CREAR UN CONTENIDO
      Content new_block_content;
      strcpy(new_block_content.name, file_name.c_str());

      // CREAR UN NUEVO INODO
      Inode new_inode;
      strcpy(new_inode.atime, now_date.c_str());
      strcpy(new_inode.ctime, now_date.c_str());
      strcpy(new_inode.mtime, now_date.c_str());
      new_inode.type = '0';
      new_inode.size = content.length();
      new_inode.perm = 664;
      new_inode.uid = (int)stoi(global_user.uid);
      new_inode.gid = (int)stoi(global_user.gid);
      for (int block_index = 0; block_index < 15; block_index++) {
        new_inode.block[block_index] = -1;
      }

      // NUEVO BLOQUE
      if (is_new_block) {
        // OCUPAR UN NUEVO BLOQUE
        superblock.free_blocks_count = superblock.free_blocks_count - 1;
        current_block_index = superblock.first_block;
        bitblocks[current_block_index] = '1';
      }

      // DISTRIBUIR CONTENIDO EN NUEVO INODO
      int content_size = content.length();
      float pref_sized = (float)content_size / (float)(sizeof(FileBlock) - 1);
      int content_block_count = ceil(pref_sized);

      // LIMPIAR BLOQUES ANTERIORES Y RESCRIBIR
      if (same_file) {
        // BLOQUE ANTERIOR
        DirBlock dir_block;
        fseek(disk_file, current_inode.block[block_position[0]], SEEK_SET);
        fread(&dir_block, sizeof(DirBlock), 1, disk_file);

        // INODO ANTERIOR
        Inode prev_inode;
        int prev_inode_start = dir_block.content[block_position[1]].inodo;
        current_inode_index =
            (int)(((superblock.inode_start - prev_inode_start) * -1) /
                  sizeof(Inode));

        // CAMBIAR FECHA DE MODIFICACION
        strcpy(prev_inode.atime, now_date.c_str());
        strcpy(prev_inode.mtime, now_date.c_str());

        // GUARDAR
        fseek(disk_file, prev_inode_start, SEEK_SET);
        fread(&prev_inode, sizeof(Inode), 1, disk_file);

        // BORRAR INODO
        for (int block_index = 0; block_index < 15; block_index++) {
          if (prev_inode.block[block_index] != -1) {
            int current_block_address = (int)(((superblock.block_start -
                                                prev_inode.block[block_index]) *
                                               -1) /
                                              sizeof(FileBlock));

            bitblocks[current_block_address] = '0';
            superblock.free_blocks_count = superblock.free_blocks_count + 1;
          }
        }
      }

      // CORTAR BLOQUES ANTES
      string next_content = content;
      string content_block[content_block_count];

      for (int block_index = 0; block_index < content_block_count;
           block_index++) {
        string tmp_block;

        // DIVIDIR BLOQUES EN 63 BYTES
        for (int char_index = (sizeof(FileBlock) - 1) * block_index;
             char_index < ((sizeof(FileBlock) - 1) * (block_index + 1));
             char_index++) {
          if (char_index < next_content.size()) {
            tmp_block += next_content.at(char_index);
          }
        }

        // AGREGAR
        content_block[block_index] = tmp_block;
      }

      // RECORRER BLOQUES
      for (int block_index = 0; block_index < content_block_count;
           block_index++) {
        FileBlock file_block;
        snprintf(file_block.content, sizeof(FileBlock), "%s",
                 content_block[block_index].c_str());

        // BUSCAR NUEVO BLOQUE LIBRE Y OCUPARLO
        int free_file_block = 0;
        for (int free_block_index = 0;
             free_block_index < superblock.blocks_count; free_block_index++) {
          if (bitblocks[free_block_index] == '0') {
            bitblocks[free_block_index] = '1';
            superblock.free_blocks_count = superblock.free_blocks_count - 1;
            free_file_block = free_block_index;
            break;
          }
        }

        // ACTUALIZAR INODO
        int next_file_block_start =
            superblock.block_start + (sizeof(FileBlock) * free_file_block);
        new_inode.block[block_index] = next_file_block_start;

        // GAURDAR NUEVO BLOQUE
        fseek(disk_file, next_file_block_start, SEEK_SET);
        fwrite(&file_block, sizeof(FileBlock), 1, disk_file);
      }

      // GUARDAR NUEVO INODO SI NO ES EL MISMO
      bitinodes[current_inode_index] = '1';
      new_block_content.inodo =
          superblock.inode_start + (sizeof(Inode) * current_inode_index);

      fseek(disk_file, new_block_content.inodo, SEEK_SET);
      fwrite(&new_inode, sizeof(Inode), 1, disk_file);

      DirBlock current_block;
      if (!is_new_block) {
        fseek(disk_file, current_inode.block[block_position[0]], SEEK_SET);
        fread(&current_block, sizeof(DirBlock), 1, disk_file);
        current_block_index = (int)(((superblock.block_start -
                                      current_inode.block[block_position[0]]) *
                                     -1) /
                                    sizeof(DirBlock));

      } else {
        for (int content_index = 0; content_index < 4; content_index++) {
          current_block.content[content_index] = (Content){{}, -1};
        }
      }

      current_block.content[block_position[1]] = new_block_content;
      current_inode.block[block_position[0]] =
          superblock.block_start + (sizeof(FileBlock) * current_block_index);

      // GUARDAR BLOQUE DE INODO PADRE
      fseek(disk_file, current_inode.block[block_position[0]], SEEK_SET);
      fwrite(&current_block, sizeof(DirBlock), 1, disk_file);

      // CAMBIOS EN INODO PADRE
      strcpy(current_inode.atime, now_date.c_str());
      strcpy(current_inode.mtime, now_date.c_str());

      fseek(disk_file, inode_start, SEEK_SET);
      fwrite(&current_inode, sizeof(Inode), 1, disk_file);
    }

    // ASIGNAR A SUPERBLOQUE
    int first_sp_inode = 0;
    int first_sp_block = 0;
    for (int inode_index = 0; inode_index < sizeof(bitinodes); inode_index++) {
      if (bitinodes[inode_index] == '0') {
        first_sp_inode = inode_index;
        break;
      }
    }

    for (int block_index = 0; block_index < sizeof(bitblocks); block_index++) {
      if (bitblocks[block_index] == '0') {
        first_sp_block = block_index;
        break;
      }
    }

    // GUARDAR CAMBIOS EN SUPERBLOQUE Y EN BITNODES
    superblock.first_inode = first_sp_inode;
    superblock.first_block = first_sp_block;

    fseek(disk_file, partition_start, SEEK_SET);
    fwrite(&superblock, sizeof(SuperBlock), 1, disk_file);

    fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
    fwrite(&bitinodes, sizeof(bitinodes), 1, disk_file);

    fseek(disk_file, superblock.bm_block_start, SEEK_SET);
    fwrite(&bitblocks, sizeof(bitblocks), 1, disk_file);

    // AGREGAR NUEVO JOURNAL
    Journal new_journal;
    string operation = "touch";
    new_journal.permissions = 664;
    new_journal.name[0] = '0';
    new_journal.type = '1';
    strcpy(new_journal.operation, operation.c_str());
    strcpy(new_journal.content, content.c_str());
    strcpy(new_journal.owner, global_user.user.c_str());
    strcpy(new_journal.date, now_date.c_str());
    add_journal(new_journal, superblock, disk_file);

    fclose(disk_file);
  } else
    print_err("NODES_ERR", "El disco no existe.");
}

/**
 * Crear archivo extendido
 * @brief Crear contenido para mkfile
 * @param {TouchProps} props
 */
void node_commands::touch(TouchProps props) {
  if (props.path.length() > 0) {
    struct stat sb {};
    string file_content;

    if (props.cont.length() > 0) {
      FILE *local_file = fopen(props.cont.c_str(), "r");
      if (local_file != NULL) {
        // OBTENER CONTENIDO
        stat(props.cont.c_str(), &sb);
        file_content.resize(sb.st_size);

        fread(const_cast<char *>(file_content.data()), sb.st_size, 1,
              local_file);
        fclose(local_file);
      }

    } else if (props.stdinR) {
      file_content = stdin_content;
    } else {
      // CONTENIDO CON SIZE
      if (props.size >= 0) {
        int counter = 0;
        for (int char_index = 0; char_index < props.size; char_index++) {
          file_content += to_string(counter);
          if (counter < 9) {
            counter++;
          } else {
            counter = 0;
          }
        }
      } else
        print_err("USER_ERR", "El parametro size debe no debe ser negativo.");
    }

    // CREAR
    mkfile(file_content, props.path, props.r);
  } else
    print_err("USER_ERR", "El parametro path es obligatorio.");
}