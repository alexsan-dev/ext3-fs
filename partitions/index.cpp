#include "index.h"
#include "../disks/index.h"
#include "../env/index.h"
#include "../nodes/index.h"
#include "../utils/tools/index.h"

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// GLOBALES
int max_logical_partitions = 23;
int mounted_prefix = 17;

partition_commands::partition_commands() {}

/**
 * Obtener particion
 * @brief Retorna la informacion de la particion montada
 * @param {string} id
 */
MountedPartition get_current_partition(string id) {
  // PARTICION
  MountedPartition partition;
  string disk_path = "";
  for (int partition_index = 0; partition_index < mounted_partitions.size();
       partition_index++) {
    if (mounted_partitions.at(partition_index).id == id) {
      partition = mounted_partitions.at(partition_index);
    }
  }

  return partition;
}

/**
 * Particiones de disco
 * @brief Crea particiones en el mbr de un disco
 * @param  {DiskCommandsProps} disk_data
 */
void partition_commands::fdisk(PartitionCommandsProps props, bool preserve) {
  if (props.path.length() > 0) {
    if (props.name.length() > 0) {
      // ABRIR ARCHIVO
      MBR mbr_data;
      FILE *disk_file = fopen(props.path.c_str(), "rb+");

      // EXISTE
      if (disk_file != NULL) {
        // OBTENER MBR
        fseek(disk_file, 0, SEEK_SET);
        fread(&mbr_data, sizeof(MBR), 1, disk_file);

        // CALCULAR ESPACIO DISPONIBLE Y POSICIONES
        int searched_partition_index = -1;
        int extended_partition_index = -1;
        int partitions_count = 0;
        bool has_same_name = 0;

        // CALCULAR ESPACIO EN PARTICIONES
        for (int partition_index = 0; partition_index < 4; partition_index++) {
          if (mbr_data.partitions[partition_index].status == '1') {
            partitions_count++;

            // BUSCAR PARTICION EXTENDIDA
            if (mbr_data.partitions[partition_index].type == 'E')
              extended_partition_index = partition_index;

            // NOMBRE ENCONTRADO
            if (mbr_data.partitions[partition_index].name == props.name) {
              has_same_name = 1;
              searched_partition_index = partition_index;
            }
          }
        }

        // BUSCAR EN PARTICIONES LOGICAS
        int searched_logical_partition_index = -1;
        EBR logical_partitions[max_logical_partitions];
        for (int logical_partition_index = 0;
             logical_partition_index < max_logical_partitions;
             logical_partition_index++) {
          EBR empty_ebr;
          empty_ebr.status = '0';
          empty_ebr.start = -1;
          empty_ebr.next = -1;
          empty_ebr.size = 0;
          logical_partitions[logical_partition_index] = empty_ebr;
        }

        if (extended_partition_index != -1) {
          // CABECERA DE PARTICIONES LOGICAS
          EBR ebr_header;
          fseek(disk_file, mbr_data.partitions[extended_partition_index].start,
                SEEK_SET);
          fread(&ebr_header, sizeof(EBR), 1, disk_file);
          logical_partitions[0] = ebr_header;

          // BUSCAR RESTO DE PARTICIONES LOGICAS
          for (int logical_partition_index = 0;
               logical_partition_index < max_logical_partitions;
               logical_partition_index++) {
            EBR logical_partition;
            fseek(disk_file, logical_partitions[logical_partition_index].next,
                  SEEK_SET);
            fread(&logical_partition, sizeof(EBR), 1, disk_file);

            // NOMBRE ENCONTRADO
            if (logical_partition.name == props.name) {
              has_same_name = 1;
              searched_logical_partition_index = logical_partition_index + 1;
            }

            // ASIGNAR SIGUIENTE
            if (logical_partition.status == '1')
              logical_partitions[logical_partition_index + 1] =
                  logical_partition;
          }
        }

        if (props.del.length() == 0) {
          if (props.add <= 0) {
            if (props.size > 0) {
              // PROPIEDADES BASICAS DE LA PARTICION
              int size =
                  props.size * (props.unit == 'K'
                                    ? 1024
                                    : props.unit == 'M' ? 1024 * 1024 : 1);

              // SIN NOMBRE REPETIDO
              if (!has_same_name) {
                // PARTICIONES PRIMARIAS Y EXTENDIDAS
                if (props.type != 'L') {
                  // BUSCAR PRIMER ESPACIO
                  bool hast_last_inactive = 0;
                  int free_partition_index = -1;
                  int partition_start = sizeof(MBR) + 1;
                  int free_space = mbr_data.size - sizeof(MBR);

                  // BUSCAR POSICION NUEVA CUANDO HAY MAS DE UNA  PARTICION
                  if (partitions_count > 0) {
                    for (int partition_index = 0; partition_index < 4;
                         partition_index++) {
                      // PARTICION ELIMINADA PERO CON ESPACIO RESERVADO
                      if (mbr_data.partitions[partition_index].status == '0') {
                        if (mbr_data.partitions[partition_index].size != -1) {
                          int next_index = partition_index + 1;
                          int next_free_space =
                              next_index < 4
                                  ? mbr_data.partitions[next_index].start -
                                        mbr_data.partitions[partition_index]
                                            .start
                                  : mbr_data.size - sizeof(MBR) -
                                        (mbr_data.partitions[partition_index]
                                             .start +
                                         mbr_data.partitions[partition_index]
                                             .size);
                          free_space -= next_free_space;

                          // VALIDAR Y ASIGNAR BLOQUE
                          if (next_free_space >= size) {
                            if (next_index == 4)
                              hast_last_inactive = 1;

                            free_partition_index = partition_index;
                            partition_start =
                                mbr_data.partitions[partition_index].start;
                            break;
                          }
                        }
                      } else
                        free_space -= mbr_data.partitions[partition_index].size;
                    }

                    // ASIGNAR AL ULTIMO
                    if ((free_partition_index == -1 && free_space >= size) ||
                        hast_last_inactive) {

                      int index_couter = 0;
                      for (int partition_index = 0; partition_index < 4;
                           partition_index++)
                        if (mbr_data.partitions[partition_index].status ==
                            '1') {
                          mbr_data.partitions[index_couter] =
                              mbr_data.partitions[partition_index];
                          index_couter++;
                        }

                      free_partition_index = partitions_count;
                      partition_start =
                          mbr_data.partitions[partitions_count - 1].start + 1 +
                          mbr_data.partitions[partitions_count - 1].size;
                    }
                  } else
                    free_partition_index = 0;

                  // SI HAY ESPACIO
                  if (free_partition_index != -1) {
                    // MAXIMO 4 PARTICIONES
                    if (partitions_count < 4) {
                      // SOLO SE PERMITE UNA EXTENDIDA
                      if ((extended_partition_index == -1 &&
                           props.type == 'E') ||
                          props.type == 'P') {
                        // CREAR NUEVA PARTICION
                        Partition new_partition;
                        strcpy(new_partition.name, props.name.c_str());
                        new_partition.start = partition_start;
                        new_partition.status = '1';
                        new_partition.type = props.type;
                        new_partition.size = size;
                        new_partition.fit = props.fit;

                        // AGREGAR AL MBR
                        mbr_data.partitions[free_partition_index] =
                            new_partition;

                        // GUARDAR
                        fseek(disk_file, 0, SEEK_SET);
                        fwrite(&mbr_data, sizeof(MBR), 1, disk_file);

                        // ACTIVAR EBR SI EXISTE
                        if (props.type == 'E') {
                          // NUEVO EBR
                          EBR ebr_data;
                          string head_ebr_name =
                              "Header_" + to_string(mbr_data.signature);
                          ebr_data.next = partition_start + size - sizeof(EBR);
                          strcpy(ebr_data.name, head_ebr_name.c_str());
                          ebr_data.start = partition_start;
                          ebr_data.size = 0;
                          ebr_data.status = '1';
                          ebr_data.fit = 'W';

                          // GUARDAR
                          fseek(disk_file, partition_start, SEEK_SET);
                          fwrite(&ebr_data, sizeof(EBR), 1, disk_file);

                          // NUEVO EBR
                          EBR ebr_footer_data;
                          string foot_ebr_name =
                              "Footer_" + to_string(mbr_data.signature);
                          strcpy(ebr_footer_data.name, foot_ebr_name.c_str());
                          ebr_footer_data.start =
                              partition_start + size - sizeof(EBR);
                          ebr_footer_data.size = 0;
                          ebr_footer_data.next = -1;
                          ebr_footer_data.status = '1';
                          ebr_footer_data.fit = 'W';

                          // GUARDAR
                          fseek(disk_file, partition_start + size - sizeof(EBR),
                                SEEK_SET);
                          fwrite(&ebr_footer_data, sizeof(EBR), 1, disk_file);
                        }
                      } else
                        print_err("PART_ERR", "Solo se permite una particion "
                                              "extendida maximo por disco.");
                    } else
                      print_err("PART_ERR",
                                "Solo se permiten cuatro particiones "
                                "maximo por disco.");
                  } else
                    print_err("PART_ERR",
                              "No existe espacio disponible en el disco.");
                }

                // PARTICIONES LOGICAS
                else {
                  if (extended_partition_index != -1) {
                    int logical_partition_start = 0;
                    int new_logical_partition_index = 0;

                    // CALCULAR ESPACIO
                    for (int logical_partition_index = 0;
                         logical_partition_index < max_logical_partitions;
                         logical_partition_index++) {
                      int start =
                          logical_partitions[logical_partition_index].start +
                          sizeof(EBR) +
                          logical_partitions[logical_partition_index].size;
                      int free_space =
                          logical_partitions[logical_partition_index + 1]
                              .start -
                          start;

                      if (free_space >= size) {
                        logical_partition_start = start + 1;
                        new_logical_partition_index =
                            logical_partition_index + 1;
                        break;
                      }
                    }

                    // GUARDAR NUEVA PARTICION LOGICA
                    if (logical_partition_start != 0) {
                      EBR new_logical_partition;
                      strcpy(new_logical_partition.name, props.name.c_str());
                      new_logical_partition.next =
                          logical_partitions[new_logical_partition_index].start;
                      new_logical_partition.start = logical_partition_start;
                      new_logical_partition.status = '1';
                      new_logical_partition.size = size;
                      new_logical_partition.fit = props.fit;

                      // GUADAR
                      fseek(disk_file, logical_partition_start, SEEK_SET);
                      fwrite(&new_logical_partition, sizeof(EBR), 1, disk_file);

                      // CAMBIAR PUNTERO DE PARTICION ANTERIOR
                      EBR prev_logical_partition =
                          logical_partitions[new_logical_partition_index - 1];
                      prev_logical_partition.next = new_logical_partition.start;

                      // GUARDAR
                      fseek(disk_file, prev_logical_partition.start, SEEK_SET);
                      fwrite(&prev_logical_partition, sizeof(EBR), 1,
                             disk_file);
                    } else
                      print_err("PART_ERR",
                                "No hay espacio disponible en el disco.");
                  } else
                    print_err("PART_ERR",
                              "Debe existir al menos una particion extendida.");
                }

              } else
                print_err("PART_ERR",
                          "Ya existe una particion \"" + props.name + "\".");
            } else
              print_err("PART_ERR", "El parametro size es invalido.");
          } else {
            // MODO DE AGREGAR ESPACIO
            if (has_same_name) {
              // CALCULAR NUEVA DIMENSION
              int add = props.add * (props.unit == 'K'
                                         ? 1024
                                         : props.unit == 'M' ? 1024 * 1024 : 1);

              // PARTICIONES PRIMARIAS Y EXTENDIDAS
              if (searched_partition_index != -1) {
                // CALCULAR ESPACIO DISPONIBLE EN PARTICION
                int prev_size =
                    mbr_data.partitions[searched_partition_index].start;
                int next_size =
                    mbr_data.partitions[searched_partition_index + 1].start;
                int new_size =
                    mbr_data.partitions[searched_partition_index].size + add;

                // VALIDAR Y GUARDAR
                if (new_size > 0) {
                  if (next_size - prev_size >= new_size) {
                    // ESCRIBIR MBR
                    mbr_data.partitions[searched_partition_index].size =
                        new_size;
                    fseek(disk_file, 0, SEEK_SET);
                    fwrite(&mbr_data, sizeof(MBR), 1, disk_file);
                  } else
                    print_err("PART_ERR",
                              "No hay mas espacio en la particion.");
                } else
                  print_err("PART_ERR",
                            "El tamaño de la particion llego a menos de 0.");
              }

              // AGREGAR EN PARTICIONES LOGICAS
              else {
                // CALCULAR ESPACIO DISPONIBLE EN PARTICION
                int prev_size =
                    logical_partitions[searched_logical_partition_index].start +
                    sizeof(EBR);
                int next_size =
                    logical_partitions[searched_logical_partition_index + 1]
                        .start;
                int new_size =
                    logical_partitions[searched_logical_partition_index].size +
                    add;

                // VALIDAR Y GUARDAR
                if (new_size > 0) {
                  if (next_size - prev_size >= new_size) {
                    // ESCRIBIR EBR
                    EBR logical_partition =
                        logical_partitions[searched_logical_partition_index];
                    logical_partition.size = new_size;

                    // GUARDAR
                    fseek(disk_file, logical_partition.start, SEEK_SET);
                    fwrite(&logical_partition, sizeof(EBR), 1, disk_file);
                  } else
                    print_err("PART_ERR",
                              "No hay mas espacio en la particion.");
                } else
                  print_err("PART_ERR",
                            "El tamaño de la particion llego a menos de 0.");
              }
            } else
              print_err("PART_ERR",
                        "No existe la particion \"" + props.name + "\".");
          }
        } else {
          // MODO DE BORRADO
          if (has_same_name) {
            // PREGUNTAR PRIMERO
            bool ask_first = preserve
                                 ? true
                                 : warn_prompt("PART_DELETE",
                                               "¿Estas seguro de querer borrar "
                                               "esta particion? (S/n):");

            if (ask_first) {
              // BORRADO PARA EXTENDIDAS Y PRIMARIAS
              if (searched_logical_partition_index == -1) {
                Partition deleted_partition =
                    mbr_data.partitions[searched_partition_index];

                // BORRAR EN MBR
                mbr_data.partitions[searched_partition_index].status = '0';

                // LLENAR CON 0
                int partition_space =
                    deleted_partition.type == 'e' ? 2 * sizeof(EBR) : 0;
                int content_size = deleted_partition.size - partition_space;
                char new_content_bytes[1024];
                for (int i = 0; i < 1024; i++)
                  new_content_bytes[i] = '\0';

                // BORRADO COMPLETO, BORRAR TODO EL ESPACIO EN DISCO
                if (props.del == "full" || deleted_partition.type == 'E') {
                  string default_partition_name = "";
                  strcpy(mbr_data.partitions[searched_partition_index].name,
                         default_partition_name.c_str());
                  mbr_data.partitions[searched_partition_index].fit = 'W';
                  mbr_data.partitions[searched_partition_index].type = 'P';
                  mbr_data.partitions[searched_partition_index].start = 0;
                  mbr_data.partitions[searched_partition_index].size = 0;

                  // BORRAR CONTENIDO EN DISCO
                  fseek(disk_file,
                        deleted_partition.start +
                            (deleted_partition.type == 'E' ? sizeof(EBR) : 0),
                        SEEK_SET);

                  for (int bytes_index = 0; bytes_index < content_size / 1024;
                       bytes_index++)
                    fwrite(&new_content_bytes, 1024, 1, disk_file);

                  if (deleted_partition.type == 'E') {
                    // RESTABLECER EBR INICIAL
                    EBR header_ebr_data;
                    string head_ebr_name =
                        "Header_" + to_string(mbr_data.signature);
                    header_ebr_data.next = deleted_partition.start +
                                           deleted_partition.size - sizeof(EBR);
                    strcpy(header_ebr_data.name, head_ebr_name.c_str());
                    header_ebr_data.start = deleted_partition.start;
                    header_ebr_data.size = 0;
                    header_ebr_data.status = '1';
                    header_ebr_data.fit = 'W';

                    // GUARDAR
                    fseek(disk_file, deleted_partition.start, SEEK_SET);
                    fwrite(&header_ebr_data, sizeof(EBR), 1, disk_file);
                  }
                }

                // GUARDAR
                if (!preserve) {
                  fseek(disk_file, 0, SEEK_SET);
                  fwrite(&mbr_data, sizeof(MBR), 1, disk_file);
                }
              }

              // BORRADO PARA PARTICIONES LOGICAS
              else {
                EBR prev_ebr =
                    logical_partitions[searched_logical_partition_index - 1];
                prev_ebr.next =
                    logical_partitions[searched_logical_partition_index + 1]
                        .start;

                // GUARDAR EBR
                if (!preserve) {
                  fseek(disk_file, prev_ebr.start, SEEK_SET);
                  fwrite(&prev_ebr, sizeof(EBR), 1, disk_file);
                }

                // BORRADO COMPLETO
                if (props.del == "full") {
                  // LLENAR BYTES CON 0
                  int partition_size =
                      logical_partitions[searched_logical_partition_index]
                          .next -
                      (logical_partitions[searched_logical_partition_index]
                           .start);
                  if (preserve) {
                    partition_size -= sizeof(EBR);
                  }

                  char new_content_bytes[1024];
                  for (int i = 0; i < 1024; i++)
                    new_content_bytes[i] = '\0';

                  // BORRAR PARTICION COMPLETA
                  fseek(disk_file,
                        logical_partitions[searched_logical_partition_index]
                                .start +
                            (preserve ? sizeof(EBR) : 0),
                        SEEK_SET);

                  for (int bytes_index = 0; bytes_index < partition_size / 1024;
                       bytes_index++)
                    fwrite(&new_content_bytes, 1024, 1, disk_file);
                }
              }
            }
          } else
            print_err("PART_ERR",
                      "No existe la particion \"" + props.name + "\".");
        }

        // CERRAR
        fclose(disk_file);
      } else
        print_err("PART_ERR", "El disco no existe.");

    } else
      print_err("PART_ERR", "El parametro name es obligatorio.");
  } else
    print_err("PART_ERR", "El parametro path es obligatorio.");
}

/**
 * Montar particion
 * @brief Monta una particion en memoria
 * @param  {string} path
 * @param  {string} name
 */
void partition_commands::mount(string path, string name) {
  if (path.length() > 0) {
    if (name.length() > 0) {
      // ABRIR ARCHIVO
      MBR mbr_data;
      FILE *disk_file = fopen(path.c_str(), "rb+");

      // EXISTE
      if (disk_file != NULL) {
        // OBTENER MBR
        fseek(disk_file, 0, SEEK_SET);
        fread(&mbr_data, sizeof(MBR), 1, disk_file);

        // GLOBALES
        EBR logical_partitions[max_logical_partitions];
        int searched_logical_partition_index = -1;
        int searched_partition_index = -1;
        int extended_partition_index = -1;
        bool name_founded = 0;

        // BUSCAR EN PARTICIONES PRIMARIAS O EXTENDIDAS
        for (int partition_index = 0; partition_index < 4; partition_index++) {
          if (mbr_data.partitions[partition_index].status == '1') {
            // NOMBRE ENCONTRADO
            if (mbr_data.partitions[partition_index].name == name) {
              name_founded = 1;
              searched_partition_index = partition_index;
            }

            // BUSCAR PARTICION EXTENDIDA

            if (mbr_data.partitions[partition_index].type == 'E')
              extended_partition_index = partition_index;
          }
        }

        // BUSCAR EN PARTICIONES LOGICAS
        for (int logical_partition_index = 0;
             logical_partition_index < max_logical_partitions;
             logical_partition_index++) {
          EBR empty_ebr;
          empty_ebr.status = '0';
          empty_ebr.start = -1;
          empty_ebr.next = -1;
          empty_ebr.size = 0;
          logical_partitions[logical_partition_index] = empty_ebr;
        }

        if (extended_partition_index != -1) {
          // CABECERA DE PARTICIONES LOGICAS
          EBR ebr_header;
          fseek(disk_file, mbr_data.partitions[extended_partition_index].start,
                SEEK_SET);
          fread(&ebr_header, sizeof(EBR), 1, disk_file);
          logical_partitions[0] = ebr_header;

          // BUSCAR RESTO DE PARTICIONES LOGICAS
          for (int logical_partition_index = 0;
               logical_partition_index < max_logical_partitions;
               logical_partition_index++) {
            EBR logical_partition;
            fseek(disk_file, logical_partitions[logical_partition_index].next,
                  SEEK_SET);
            fread(&logical_partition, sizeof(EBR), 1, disk_file);

            // NOMBRE ENCONTRADO
            if (logical_partition.name == name) {
              name_founded = 1;
              searched_logical_partition_index = logical_partition_index + 1;
            }

            // ASIGNAR SIGUIENTE
            if (logical_partition.status == '1')
              logical_partitions[logical_partition_index + 1] =
                  logical_partition;
          }
        }

        // PARTICION ENCONTRADA
        if (name_founded) {
          MountedPartition partition;
          int partition_start =
              (searched_logical_partition_index != -1 ? sizeof(EBR) : 0) +
              (searched_logical_partition_index != -1
                   ? logical_partitions[searched_logical_partition_index].start
                   : mbr_data.partitions[searched_partition_index].start);
          string partition_name;
          char partition_letter = 67 + mounted_partitions.size();
          string partition_id = to_string(mounted_prefix) +
                                to_string(mbr_data.signature % 10) +
                                partition_letter;

          // EN PARTICIONES PRIMARIAS Y EXTENDIDAS
          if (searched_partition_index != -1)
            partition_name = mbr_data.partitions[searched_partition_index].name;

          // EN PARTICIONES LOGICAS
          else
            partition_name =
                logical_partitions[searched_logical_partition_index].name;

          partition.name = partition_name;
          partition.id = partition_id;
          partition.path = path;
          partition.start = partition_start;
          partition.size = mbr_data.partitions[searched_partition_index].size;
          partition.type = mbr_data.partitions[searched_partition_index].type;

          // AGREGAR
          mounted_partitions.push_back(partition);

          // IMPRIMIR
          for (int mounted_index = 0; mounted_index < mounted_partitions.size();
               mounted_index++) {
            cout << mounted_partitions.at(mounted_index).path << "|"
                 << mounted_partitions.at(mounted_index).name << "|"
                 << mounted_partitions.at(mounted_index).id << "\n";
          }
          cout << "\n";

        } else
          print_err("PART_ERR", "No existe la particion \"" + name + "\".");

        fclose(disk_file);
      } else
        print_err("PART_ERR", "El disco no existe.");
    } else
      print_err("PART_ERR", "El parametro name es obligatorio.");
  } else
    print_err("PART_ERR", "El parametro path es obligatorio.");
}

/**
 * Desmontar particion
 * @brief Monta una particion en memoria
 * @param  {string} id
 */
void partition_commands::unmount(string id) {
  if (id.length() > 0) {
    // BUSCAR PARTICION MONTADA
    int mounted_index = -1;
    for (int mount_index = 0; mount_index < mounted_partitions.size();
         mount_index++) {
      if (mounted_partitions.at(mount_index).id == id) {
        mounted_index = mount_index;
      }
    }

    // SE ENCONTRO
    if (mounted_index != -1) {
      MountedPartition current_partition = mounted_partitions.at(mounted_index);
      FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

      if (disk_file != NULL) {
        // CAMBIAR SUPERBLOQUE
        SuperBlock super_block;
        fseek(disk_file, current_partition.start, SEEK_SET);
        fread(&super_block, sizeof(SuperBlock), 1, disk_file);

        // FECHA DE UNMOUNT
        string date_now = get_now();
        strcpy(super_block.umtime, date_now.c_str());

        // GUARDAR
        fwrite(&super_block, sizeof(SuperBlock), 1, disk_file);
      }

      // BORRAR
      mounted_partitions.erase(mounted_partitions.begin() + mounted_index);
    } else
      print_err("PART_ERR",
                "No existe ninguna particion \"" + id + "\" montada.");
  } else
    print_err("PART_ERR", "El parametro id es obligatorio.");
}

/**
 * Crear sistema de archivos en particion
 * @brief Crea superbloques, journal bloques e inodos
 * @param  {PartitionFsProps} props
 */
void partition_commands::mkfs(PartitionFsProps props) {
  if (props.id.length() > 0) {
    // BUSCAR PARTICION MONTADA
    MountedPartition current_partition;
    for (int mount_index = 0; mount_index < mounted_partitions.size();
         mount_index++) {
      if (mounted_partitions.at(mount_index).id == props.id) {
        current_partition = mounted_partitions.at(mount_index);
      }
    }

    // INICIAR SESION
    global_user.logged = 1;
    global_user.uid = "1";
    global_user.user = "root";
    global_user.pwd = "123";
    global_user.grp = "1";
    global_user.id = current_partition.id;
    global_user.gid = "1";

    // SE ENCONTRO
    if (current_partition.path.length() > 0) {
      // ABRIR ARCHIVO
      MBR mbr_data;
      FILE *disk_file = fopen(current_partition.path.c_str(), "rb+");

      // EXISTE
      if (disk_file != NULL) {
        // OBTENER MBR
        fseek(disk_file, 0, SEEK_SET);
        fread(&mbr_data, sizeof(MBR), 1, disk_file);

        // CALCULO NUMERO DE INODOS Y BLOQUES
        int n = ((current_partition.size - sizeof(SuperBlock)) /
                 (4 + sizeof(Journal) + sizeof(Inode) + 3 * sizeof(FileBlock)));

        // BORRAR CON FDISK
        if (props.type == "full") {
          PartitionCommandsProps fProps;
          fProps.name = current_partition.name;
          fProps.path = current_partition.path;
          fProps.del = props.type;
          fdisk(fProps, 1);
        }

        // CREAR SUPERBLOQUE
        SuperBlock superblock;
        int fs_type = (int)(props.fs.at(0) - '0');

        superblock.mount_count = 1;
        superblock.magic = 0xEF53;
        superblock.first_inode = 0;
        superblock.first_block = 0;
        superblock.inodes_count = n;
        superblock.blocks_count = 3 * n;
        superblock.free_inodes_count = n - 2;
        superblock.free_blocks_count = (3 * n) - 2;
        superblock.inode_size = sizeof(Inode);
        superblock.block_size = sizeof(FileBlock);
        superblock.bm_inode_start = current_partition.start +
                                    sizeof(SuperBlock) +
                                    (fs_type == 3 ? 100 * sizeof(Journal) : 0);
        superblock.filesystem_type = fs_type;
        superblock.bm_block_start = superblock.bm_inode_start + n;
        superblock.inode_start = superblock.bm_block_start + 3 * n;
        superblock.block_start = superblock.inode_start + n * sizeof(Inode);

        // CALCULA FECHA
        string def_time = "";
        string current_date = get_now();
        strcpy(superblock.umtime, def_time.c_str());

        fseek(disk_file, current_partition.start, SEEK_SET);
        fwrite(&superblock, sizeof(SuperBlock), 1, disk_file);

        // CREAR INODOS Y BLOQUES
        char bitinodes[n];
        char bitblocks[3 * n];
        for (int i = 0; i < n; i++)
          bitinodes[i] = '0';

        fseek(disk_file, superblock.bm_inode_start, SEEK_SET);
        fwrite(&bitinodes, n, 1, disk_file);

        // BLOQUES
        for (int i = 0; i < 3 * n; i++)
          bitblocks[i] = '0';

        fseek(disk_file, superblock.bm_block_start, SEEK_SET);
        fwrite(&bitblocks, 3 * n, 1, disk_file);

        // JOURNALING
        if (fs_type == 3) {
          int journalstart = (current_partition.start + sizeof(SuperBlock));
          Journal journal_data;
          journal_data.operation[0] = '-';
          journal_data.content[0] = '\0';
          journal_data.permissions = -1;
          journal_data.owner[0] = '\0';
          journal_data.name[0] = '\0';
          journal_data.date[0] = '\0';
          journal_data.type = '-';

          // ESCRIBO TODOS LOS JOURNAL
          for (int i = 0; i < 100; i++) {
            fseek(disk_file, (journalstart + (i * sizeof(Journal))), SEEK_SET);
            fwrite(&journal_data, sizeof(Journal), 1, disk_file);
          }
        }

        fclose(disk_file);

        // CREAR RUTA
        node_commands *nodes_cmd = new node_commands();
        nodes_cmd->mkdir("/", 0);

        string def_users = "1,G,root\n1,U,root,root,123\n";
        nodes_cmd->mkfile(def_users, "/users.txt", 1);

        // CERRAR SESION
        global_user.logged = 0;
        global_user.uid = "";
        global_user.user = "";
        global_user.pwd = "";
        global_user.grp = "";
        global_user.id = "";
        global_user.gid = "";

      } else
        print_err("PART_ERR", "El disco no existe.");
    } else
      print_err("PART_ERR",
                "No existe ninguna particion \"" + props.id + "\" montada.");
  } else
    print_err("PART_ERR", "El parametro id es obligatorio.");
}