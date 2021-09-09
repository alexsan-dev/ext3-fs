#include "index.h"
#include "../env/index.h"
#include "../partitions/index.h"
#include "../utils/tools/index.h"
#include <string.h>

using namespace std;

permission_commands::permission_commands() {}

/**
 * Cambiar permisos
 * @brief Cambia los permisos en un inodo
 * @param props
 */
void permission_commands::chmod(ChmodProps props) {
  if (props.path.length() > 0) {
    if (props.ugo.length() > 0) {
      int users_perm = (int)(props.ugo.at(0) - '0');
      int groups_perm = (int)(props.ugo.at(1) - '0');
      int others_perm = (int)(props.ugo.at(2) - '0');

      if (users_perm <= 7 && groups_perm <= 7 && others_perm <= 7) {
        MountedPartition current_partition =
            get_current_partition(global_user.id);

        // LEER SUPERBLOQUE
        SuperBlock superblock;
        int partition_start = current_partition.start;
        FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

        // EXISTE
        if (disk_file != NULL) {
          vector<string> path_components = split(props.path, '/');
          int path_cmp_size = path_components.size();
          path_components.at(0) = "/";

          fseek(disk_file, partition_start, SEEK_SET);
          fread(&superblock, sizeof(SuperBlock), 1, disk_file);

          Inode parent_inode;
          int inode_start = superblock.inode_start;

          fseek(disk_file, inode_start, SEEK_SET);
          fread(&parent_inode, sizeof(Inode), 1, disk_file);

          // BUSCAR INODO
          for (int path_index = 0; path_index < path_cmp_size; path_index++) {
            for (int block_index = 0; block_index < 15; block_index++) {
              if (parent_inode.block[block_index] != -1) {
                DirBlock dir_block;
                fseek(disk_file, parent_inode.block[block_index], SEEK_SET);
                fread(&dir_block, sizeof(DirBlock), 1, disk_file);

                // BUSCAR CONTENIDO
                for (int content_index = 0; content_index < 4;
                     content_index++) {
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
                        parent_inode = tmp_inode;
                      }
                    }
                  }
                }
              }
            }
          }

          // BUSCAR SI ES UNA CARPETA O UN ARCHIVO
          Inode first_inode = parent_inode;
          for (int block_index = 0; block_index < 15; block_index++) {
            if (first_inode.block[block_index] != -1) {
              DirBlock dir_block;
              bool find_block = 0;
              fseek(disk_file, first_inode.block[block_index], SEEK_SET);
              fread(&dir_block, sizeof(DirBlock), 1, disk_file);

              // RECORRER CONTENIDO
              for (int content_index = 0; content_index < 4; content_index++) {
                if (dir_block.content[content_index].name ==
                    path_components.at(path_components.size() - 1)) {
                  inode_start = dir_block.content[content_index].inodo;
                  fseek(disk_file, inode_start, SEEK_SET);
                  fread(&first_inode, sizeof(Inode), 1, disk_file);

                  find_block = 1;
                  break;
                }
              }

              if (find_block) {
                break;
              }
            }
          }

          // VERIFICAR SI EL INODO PERTENECE AL USUARIO
          if (first_inode.uid == (int)stoi(global_user.uid) ||
              global_user.grp == "root") {
            // RECORRER BLOQUES
            deque<Inode> inodes;
            deque<int> inode_starts;
            inodes.push_back(first_inode);
            inode_starts.push_back(inode_start);
            int inode_counter = 0;

            while (inodes.size() > 0) {
              Inode current_inode = inodes.at(0);
              inode_start = inode_starts.at(0);
              inodes.pop_front();
              inode_starts.pop_front();

              string date_now = get_now();

              // CAMBIAR PERMISOS
              current_inode.perm = (int)stoi(props.ugo);
              strcpy(current_inode.atime, date_now.c_str());
              strcpy(current_inode.mtime, date_now.c_str());

              fseek(disk_file, inode_start, SEEK_SET);
              fwrite(&current_inode, sizeof(Inode), 1, disk_file);

              // GUARDAR
              if (props.recursive && inode_counter >= 0) {
                if (current_inode.type == '1') {
                  for (int block_index = 0; block_index < 15; block_index++) {
                    if (current_inode.block[block_index] != -1) {
                      // LEER BLOQUE
                      DirBlock dir_block;
                      fseek(disk_file, current_inode.block[block_index],
                            SEEK_SET);
                      fread(&dir_block, sizeof(DirBlock), 1, disk_file);

                      // SIGUIENTE INODO
                      for (int content_index = 0; content_index < 4;
                           content_index++) {
                        if (dir_block.content[content_index].inodo != -1) {
                          Inode new_inode;
                          fseek(disk_file,
                                dir_block.content[content_index].inodo,
                                SEEK_SET);
                          fread(&new_inode, sizeof(Inode), 1, disk_file);

                          // AGREGAR
                          inodes.push_back(new_inode);
                          inode_starts.push_back(
                              dir_block.content[content_index].inodo);
                        }
                      }
                    }
                  }
                }
              }

              inode_counter++;
            }

          } else
            print_err("PERMISSIONS_ERR", "El usuario no es propietario.");

          fclose(disk_file);
        }
      } else
        print_err("PERMISSIONS_ERR", "El parametro ugo fuera de rango.");
    } else
      print_err("PERMISSIONS_ERR", "El parametro ugo es obligatorio.");
  } else
    print_err("PERMISSIONS_ERR", "El parametro path es obligatorio.");
}