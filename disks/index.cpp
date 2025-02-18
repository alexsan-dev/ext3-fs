#include "index.h"
#include "../env/index.h"
#include "../partitions/index.h"
#include "../utils/tools/index.h"

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

disk_commands::disk_commands() {}

/**
 * Imprimir EBR y Particiones
 * @param  {EBR} ebr_data
 */
string get_ebr_graph(MBR mbr_data, FILE *disk_file) {
  string dot_content;
  int extended_start = -1;

  // EXISTE
  if (disk_file != NULL) {
    // BUSCAR EXTENDIDA
    for (int partition_index = 0; partition_index < 4; partition_index++) {
      if (mbr_data.partitions[partition_index].status != '0')
        if (mbr_data.partitions[partition_index].type == 'E') {
          extended_start = mbr_data.partitions[partition_index].start;
          break;
        }
    }

    // POSICIONES DE EBRS
    if (extended_start != -1) {
      int positions[max_logical_partitions] = {-1};
      for (int i = 0; i < max_logical_partitions; i++)
        positions[i] = -1;
      positions[0] = extended_start;

      for (int ebr_index = 0; ebr_index < max_logical_partitions - 1;
           ebr_index++) {
        if (positions[ebr_index] != -1) {
          // BUSCAR EBR
          EBR ebr_data;
          fseek(disk_file, positions[ebr_index], SEEK_SET);
          fread(&ebr_data, sizeof(EBR), 1, disk_file);
          string ebr_name(ebr_data.name);

          if (ebr_data.status == '1') {
            if (ebr_index > 0 &&
                ebr_name.find("Footer_") == std::string::npos) {

              dot_content +=
                  "EBR" + to_string(ebr_index) +
                  " [shape=none, margin=0, label=<<table "
                  "border=\"0\" "
                  "cellborder=\"1\" cellspacing=\"0\" "
                  "cellpadding=\"4\"><tr><td>Nombre</td><td>Valor</td></"
                  "tr><tr><td>Status</td><td>" +
                  ebr_data.status + "</td></tr><tr><td>Fit</td><td>" +
                  ebr_data.fit + "</td></tr><tr><td>Start</td><td>" +
                  to_string(ebr_data.start) +
                  "</td></tr><tr><td>Size</td><td>" + to_string(ebr_data.size) +
                  "</td></tr><tr><td>Next</td><td>" + to_string(ebr_data.next) +
                  "</td></tr><tr><td>Name</td><td>" + ebr_data.name +
                  "</td></tr></table>>]";

              if (ebr_index == 1) {
                dot_content += "EXT -> EBR1;";
              } else {
                dot_content += "EBR" + to_string(ebr_index - 1) + " -> EBR" +
                               to_string(ebr_index);
              }
            }

            // SIGUIENTE
            positions[ebr_index + 1] = ebr_data.next;
          }
        } else
          break;
      }
    }
  }

  return dot_content;
}

/**
 * Imprimir EBR y Particiones
 * @param  {EBR} ebr_data
 */
string get_ebr_table(MBR mbr_data, FILE *disk_file, int ext_size) {
  string dot_content;
  int extended_start = -1;

  // EXISTE
  if (disk_file != NULL) {
    // BUSCAR EXTENDIDA
    for (int partition_index = 0; partition_index < 4; partition_index++) {
      if (mbr_data.partitions[partition_index].status != '0')
        if (mbr_data.partitions[partition_index].type == 'E') {
          extended_start = mbr_data.partitions[partition_index].start;
          break;
        }
    }

    // POSICIONES DE EBRS
    if (extended_start != -1) {
      int positions[max_logical_partitions] = {-1};
      for (int i = 0; i < max_logical_partitions; i++)
        positions[i] = -1;
      positions[0] = extended_start;

      for (int ebr_index = 0; ebr_index < max_logical_partitions - 1;
           ebr_index++) {
        if (positions[ebr_index] != -1) {
          // BUSCAR EBR
          EBR ebr_data;
          fseek(disk_file, positions[ebr_index], SEEK_SET);
          fread(&ebr_data, sizeof(EBR), 1, disk_file);
          string ebr_name(ebr_data.name);

          if (ebr_data.status == '1') {
            if (ebr_index > 0 &&
                ebr_name.find("Footer_") == std::string::npos) {
              float ebr_per = ((float)ebr_data.size / ext_size) * 100;
              dot_content +=
                  "<td>" + ebr_name + " " + to_string(ebr_per) + " %</td>";
            }

            // SIGUIENTE
            positions[ebr_index + 1] = ebr_data.next;
          }
        } else
          break;
      }
    }
  }

  return dot_content;
}

/**
 * Imprimir ESPACIOS EN DISCO
 * @brief  Imprime todo el espacio en bloques del disco
 * @param  {string} disk_path
 * @param  {string} path
 */
void get_disk_sp(string disk_path, string path, int part_start) {
  // LEER SUPERBLOQUE
  SuperBlock superblock;
  int partition_start = part_start;
  FILE *disk_file = fopen(disk_path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    fseek(disk_file, partition_start, SEEK_SET);
    fread(&superblock, sizeof(SuperBlock), 1, disk_file);

    string dot_path = "./reports/assets/";
    string dot_name = dot_path + "sp.dot";
    FILE *dot_file = fopen(dot_name.c_str(), "w+");

    // EXISTE
    if (dot_file != NULL) {
      // GENERAR DOT
      string dot = "digraph G {graph[rankdir=LR, overlap=false, "
                   "splines=true];node[shape = record, fontsize = 9, fontname "
                   "= \"Verdana\"]; SP [shape=none, margin=0, label=<<table "
                   "border=\"0\" "
                   "cellborder=\"1\" cellspacing=\"0\" "
                   "cellpadding=\"4\">";
      dot +=
          "<tr><td>Inodes count</td><td>" + to_string(superblock.inodes_count) +
          "</td></tr>" + "<tr><td>Blocks count</td><td>" +
          to_string(superblock.blocks_count) + "</td></tr>" +
          "<tr><td>Free blocks count</td><td>" +
          to_string(superblock.free_blocks_count) + "</td></tr>" +
          "<tr><td>Free inodes count</td><td>" +
          to_string(superblock.free_inodes_count) + "</td></tr>" +
          "<tr><td>Mnt count</td><td>" + to_string(superblock.mount_count) +
          "</td></tr><tr><td>Magic</td><td>0xEF53</td></tr>" +
          "<tr><td>Inode size</td><td>" + to_string(superblock.inode_size) +
          "</td></tr><tr><td>Block size</td><td>" +
          to_string(superblock.block_size) + "</td></tr>" +
          "<tr><td>First inode</td><td>" + to_string(superblock.first_inode) +
          "</td></tr><tr><td>First block</td><td>" +
          to_string(superblock.first_block) + "</td></tr>" +
          "<tr><td>Bitmap inode start</td><td>" +
          to_string(superblock.bm_inode_start) + "</td></tr>" +
          "<tr><td>Bitmap block start</td><td>" +
          to_string(superblock.bm_block_start) + "</td></tr>" +
          "<tr><td>Inode start</td><td>" + to_string(superblock.inode_start) +
          "</td></tr><tr><td>Block block start</td><td>" +
          to_string(superblock.block_start) + "</td></tr>";

      dot += "</table>>];}";
      fwrite(dot.c_str(), dot.length(), 1, dot_file);
      fclose(dot_file);

      // GENERAR IMAGEN
      string dot_svg = "dot -Tsvg " + dot_name + " -o " + path;
      system(dot_svg.c_str());
    }

    fclose(disk_file);
  }
}

/**
 * Imprimir ESPACIOS EN DISCO
 * @brief  Imprime todo el espacio en bloques del disco
 * @param  {string} disk_path
 * @param  {string} path
 */
void get_disk_table(string disk_path, string path) {
  // ABRIR ARCHIVO
  MBR mbr_data;
  FILE *disk_file = fopen(disk_path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    string dot_path = "./reports/assets/";
    string dot_name = dot_path + "disk.dot";

    // OBTENER MBR
    fseek(disk_file, 0, SEEK_SET);
    fread(&mbr_data, sizeof(MBR), 1, disk_file);
    FILE *dot_file = fopen(dot_name.c_str(), "w+");

    if (dot_file != NULL) {
      // GENERAR DOT
      string dot = "digraph G {graph[rankdir=LR, overlap=false, "
                   "splines=true];node[shape = record, fontsize = 9, fontname "
                   "= \"Verdana\"]; DISK [shape=none, margin=0, label=<<table "
                   "border=\"0\" "
                   "cellborder=\"1\" cellspacing=\"0\" "
                   "cellpadding=\"4\"><tr><td>" +
                   disk_path + "</td></tr><tr><td>MBR</td>";

      // ESPACIOS ENTRE PARTICIONES
      int free_space_start = 161;
      int free_space_end = 161;
      for (int part_index = 0; part_index < 4; part_index++) {

        free_space_end = mbr_data.partitions[part_index].start;

        if ((free_space_end - free_space_start) > 0) {
          float free_per =
              ((free_space_end - free_space_start) / mbr_data.size) * 100;
          dot += "<td>Libre " + to_string(free_per) + " %</td>";
        }

        if (mbr_data.partitions[part_index].status == '1') {
          float part_per =
              ((float)mbr_data.partitions[part_index].size / mbr_data.size) *
              100;
          string pType(1, mbr_data.partitions[part_index].type);
          if (mbr_data.partitions[part_index].type != 'E') {

            dot += "<td>Particion " + pType + " " + to_string(part_per) +
                   " %</td>";
          } else {
            dot += "<td><table><tr><td>Particion "
                   "Extendida</td></tr><tr>" +
                   get_ebr_table(mbr_data, disk_file,
                                 mbr_data.partitions[part_index].size) +
                   "</tr></table></td>";
          }

        } else {
          dot += "<td>Libre</td>";
        }

        free_space_start =
            free_space_end + mbr_data.partitions[part_index].size + 1;
      }

      dot += "</tr></table>>];}";

      fwrite(dot.c_str(), dot.length(), 1, dot_file);
      fclose(dot_file);

      // GENERAR IMAGEN
      string dot_svg = "dot -Tsvg " + dot_name + " -o " + path;
      system(dot_svg.c_str());
    }

    // CERRAR
    fclose(disk_file);
  }
}

/**
 * Imprimir MBR y Particiones
 * @brief  Imprime toda la informacion del disco
 * @param  {string} disk_path
 * @param  {string} path
 */
void get_disk_graph(string disk_path, string path) {
  // ABRIR ARCHIVO
  MBR mbr_data;
  FILE *disk_file = fopen(disk_path.c_str(), "rb+");

  // EXISTE
  if (disk_file != NULL) {
    string dot_path = "./reports/assets/";
    string dot_name = dot_path + "mbr.dot";

    // OBTENER MBR
    fseek(disk_file, 0, SEEK_SET);
    fread(&mbr_data, sizeof(MBR), 1, disk_file);
    FILE *dot_file = fopen(dot_name.c_str(), "w+");

    if (dot_file != NULL) {
      // GENERAR DOT
      string dot = "digraph G {graph[rankdir=LR, overlap=false, "
                   "splines=true];node[shape = record, fontsize = 9, fontname "
                   "= \"Verdana\"]; MBR [shape=none, margin=0, label=<<table "
                   "border=\"0\" "
                   "cellborder=\"1\" cellspacing=\"0\" "
                   "cellpadding=\"4\"><tr><td>Nombre</td><td>Valor</td></"
                   "tr><tr><td>Size</td><td>" +
                   to_string(mbr_data.size) + "</td></tr>" +
                   "<tr><td>Creation Date</td><td>" + mbr_data.date +
                   "</td></tr>" + "<tr><td>Signature</td><td>" +
                   to_string(mbr_data.signature) + "</td></tr>" +
                   "<tr><td>Fit</td><td>" + mbr_data.fit +
                   "</td></tr></table>>];";

      // PARTICIONES
      for (int part_index = 0; part_index < 4; part_index++) {
        Partition part = mbr_data.partitions[part_index];
        string id = part.type == 'E' ? "EXT" : "Part" + to_string(part_index);
        dot += id +
               " [shape=none, margin=0, label=<<table "
               "border=\"0\" "
               "cellborder=\"1\" cellspacing=\"0\" "
               "cellpadding=\"4\"><tr><td>Status</td><td>" +
               part.status + "</td></tr><tr><td>Type</td><td>" + part.type +
               "</td></tr><tr><td>Fit</td><td>" + part.fit +
               "</td></tr><tr><td>Start</td><td>" + to_string(part.start) +
               "</td></tr><tr><td>Size</td><td>" + to_string(part.size) +
               "</td></tr><tr><td>Name</td><td>" + part.name +
               "</td></tr></table>>];MBR -> " + id + ";";
      }

      dot += get_ebr_graph(mbr_data, disk_file);
      dot += "}";

      fwrite(dot.c_str(), dot.length(), 1, dot_file);
      fclose(dot_file);

      // GENERAR IMAGEN
      string dot_svg = "dot -Tsvg " + dot_name + " -o " + path;
      system(dot_svg.c_str());
    }

    // CERRAR
    fclose(disk_file);
  }
}

/**
 * Crear disco
 * @brief Crea un disco vacio con 4 particiones
 * @param  {DiskCommandsProps} disk_data
 */
void disk_commands::mkdisk(DiskCommandsProps props) {
  // VALIDAR PARAMETROS OBLIGATORIOS
  if (props.size != -1) {
    if (props.path.length() > 0) {
      // GLOBALES
      MBR mbr_data;
      EBR ebr_data;
      char buffer[1024];
      string disk_content = "";
      string parent_dir = props.path.substr(0, props.path.find_last_of("/\\"));
      string mkfiles = "mkdir -p " + parent_dir;
      system(mkfiles.c_str());

      FILE *disk_file = fopen(props.path.c_str(), "wb");

      if (disk_file != NULL) {
        // CREAR FECHA
        string current_date = get_now();
        strcpy(mbr_data.date, current_date.c_str());

        // ASIGNAR PROPIEDADES DEL MASTER BOOT
        mbr_data.fit = props.fit;
        mbr_data.size =
            props.unit == 'K' ? props.size * 1024 : props.size * 1024 * 1024;
        mbr_data.signature = rand() % 10;

        // CREAR ARCHIVO EBR INICIAL
        string partition_name = "-";
        strcpy(ebr_data.name, partition_name.c_str());
        ebr_data.status = '0';
        ebr_data.start = -1;
        ebr_data.fit = 'W';
        ebr_data.size = -1;
        ebr_data.next = -1;

        // CREAR PARTICIONES DEL MBR
        Partition empty_partition;
        strcpy(empty_partition.name, partition_name.c_str());
        empty_partition.status = '0';
        empty_partition.type = 'P';
        empty_partition.start = -1;
        empty_partition.size = -1;
        empty_partition.fit = 'W';

        // AGREGAR PARTICION VACIA
        for (int i = 0; i < 4; i++)
          mbr_data.partitions[i] = empty_partition;

        // AGREGAR AL DISCO
        if (disk_file != NULL) {
          // CREAR UN KB DE 0
          for (int i = 0; i < 1024; i++)
            buffer[i] = '\0';

          // RELLENAR EL RESTO CON 0
          for (int byte_index = 0;
               byte_index < (props.size * (props.unit == 'K' ? 1 : 1024));
               byte_index++)
            fwrite(&buffer, 1024, 1, disk_file);

          // GUARDAR MBR
          fseek(disk_file, 0, SEEK_SET);
          fwrite(&mbr_data, sizeof(MBR), 1, disk_file);

          // GUARDAR EBR
          fseek(disk_file, sizeof(MBR) + 1, SEEK_SET);
          fwrite(&ebr_data, sizeof(EBR), 1, disk_file);

          // CERRAR
          fclose(disk_file);
        }
      } else
        print_err("DISK_ERR", "El disco no se pudo crear.");
    } else
      print_err("DISK_ERR", "El parametro path es obligatorio.");
  } else
    print_err("DISK_ERR", "El parametro size es obligatorio.");
}

/**
 * Borrar disco
 * @brief Borra el archivo .disk
 * @param  {string} path
 */
void disk_commands::rmdisk(string path) {
  if (path.length() > 0) {
    // ABRIR ARCHIVO
    FILE *disk_file = fopen(path.c_str(), "rb");

    // EXISTE
    if (disk_file != NULL) {
      // PREGUNTAR PRIMERO
      if (warn_prompt("DISK_DELETE",
                      "¿Estas seguro de querer borrar este disco? (S/n):")) {

        int removed = remove(path.c_str());
        if (removed != 0)
          print_err("DISK_ERR", "No fue posible eliminar el disco.");
      }

      fclose(disk_file);
    } else
      print_err("DISK_ERR", "El disco no existe.");
  } else
    print_err("DISK_ERR", "El parametro path es obligatorio.");
}
