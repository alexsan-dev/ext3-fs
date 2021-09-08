#include "index.h"
#include "../env/index.h"
#include "../nodes/index.h"
#include "../partitions/index.h"
#include "../utils/tools/index.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

user_commands::user_commands() {}

/**
 * Obtener usuarios como texto plano
 * @brief Retorna la informacion de los usuatios
 * @param {string} id
 */
string get_users_content(string id) {
  // PARTICION
  MountedPartition partition = get_current_partition(id);
  string users_content;

  if (partition.path.length() > 0) {
    // STREAM
    bool login = 0;
    bool deleted_user = 0;
    FILE *users_file = fopen(partition.path.c_str(), "rb+");

    if (users_file != NULL) {
      // BUSCAR BLOQUE DE USUARIOS
      SuperBlock superblock;
      fseek(users_file, partition.start, SEEK_SET);
      fread(&superblock, sizeof(SuperBlock), 1, users_file);

      Inode first_inode;
      fseek(users_file, superblock.inode_start, SEEK_SET);
      fread(&first_inode, sizeof(Inode), 1, users_file);

      DirBlock root_block;
      fseek(users_file, first_inode.block[0], SEEK_SET);
      fread(&root_block, sizeof(DirBlock), 1, users_file);

      Inode users_inode;
      fseek(users_file, root_block.content[0].inodo, SEEK_SET);
      fread(&users_inode, sizeof(Inode), 1, users_file);

      string users_text;
      for (int block_index = 0; block_index < 15; block_index++) {
        if (users_inode.block[block_index] != -1) {
          FileBlock users_block;
          fseek(users_file, users_inode.block[block_index], SEEK_SET);
          fread(&users_block, sizeof(FileBlock), 1, users_file);

          // CONTENT
          string file_content = users_block.content;
          users_text += file_content;
        }
      }

      users_content = users_text;
      fclose(users_file);
    }
  } else {
    print_err("USERS_ERR", "No existe ninguna particion " + id + ".");
  }

  return users_content;
}

/**
 * Obtener lineas de usuarios
 * @brief Retorna una lista con las lineas de los usuarios
 * @param {string} id
 */
vector<string> get_users(string id) {
  vector<string> lines = split(get_users_content(id), '\n');
  return lines;
}

/**
 * Guardar archivo
 * @brief Guardar el nuevo archivo en el disco
 * @param {string} new_content
 */
void save_users(string new_content) {
  // MKFILE
  node_commands *node_cmd = new node_commands();
  node_cmd->mkfile(new_content, "/users.txt", 0);
}

/**
 * Split de linea
 * @brief Retorna un struct con las propiedades de una linea en users
 * @param {char*} line
 */
UserOrGroup get_user_line_info(string line) {
  int token_index = 0;
  UserOrGroup user_info;
  vector<string> user_line = split(line, ',');

  // RECORRER STRING
  for (int char_index = 0; char_index < user_line.size(); char_index++) {
    if (char_index == 0) {
      user_info.uid = user_line.at(char_index);
    } else if (char_index == 1) {
      user_info.type = user_line.at(char_index);
    } else if (char_index == 2) {
      user_info.grp = user_line.at(char_index);
    } else if (char_index == 3) {
      user_info.name = user_line.at(char_index);
    } else if (char_index == 4) {
      user_info.pwd = user_line.at(char_index);
    }
  }

  return user_info;
}

/**
 * Login
 * @brief Iniciar sesion en una particion
 * @param {user_commands} user_data
 */
void user_commands::login(UserCommandsProps props) {
  if (props.user.length() > 0) {
    if (props.pwd.length() > 0) {
      if (props.id.length() > 0) {
        // SESION NO INICIADA
        if (global_user.logged) {
          print_err("USERS_ERR",
                    "Debe cerrar sesion de \"" + global_user.user + "\".");
        } else {
          // STREAM
          bool login = 0;
          bool deleted_user = 0;

          // BUSCAR BLOQUE DE USUARIOS
          vector<string> user_lines = get_users(props.id);

          // LEER
          for (int line_index = 0; line_index < user_lines.size();
               line_index++) {
            UserOrGroup user_info =
                get_user_line_info(user_lines.at(line_index));

            // LOGIN
            if (user_info.type == "U") {
              if (user_info.name == props.user && user_info.pwd == props.pwd) {
                if (user_info.uid != "0") {
                  global_user.id = props.id;
                  global_user.user = user_info.name;
                  global_user.logged = 1;
                  global_user.pwd = user_info.pwd;
                  global_user.grp = user_info.grp;
                  global_user.uid = user_info.uid;
                  global_user.gid = user_info.uid;
                } else
                  deleted_user = 1;

                break;
              }
            }
          }

          // BUSCAR GRUPO
          for (int line_index = 0; line_index < user_lines.size();
               line_index++) {
            UserOrGroup user_info =
                get_user_line_info(user_lines.at(line_index));

            if (user_info.type == "G") {
              if (user_info.grp == global_user.grp) {
                if (user_info.uid != "0") {
                  global_user.gid = user_info.uid;
                } else
                  deleted_user = 1;

                break;
              }
            }
          }

          // NO SE ENCONTRO NINGUN USUARIO
          if (!deleted_user) {
            if (!global_user.logged)
              print_err("USERS_ERR", "No se encontro ningun usuario \"" +
                                         props.user + "\".");
          } else
            print_err("USER_ERR", "El usuario esta eliminado.");
        }
      } else
        print_err("USER_ERR", "El parametro id es obligatorio.");
    } else
      print_err("USER_ERR", "El parametro pwd es obligatorio.");
  } else
    print_err("USER_ERR", "El parametro user es obligatorio.");
}

/**
 * Logout
 * @brief Cerrar la sesion actual
 */
void user_commands::logout() {
  if (global_user.logged) {
    global_user.logged = 0;
    global_user.user = "";
    global_user.pwd = "";
    global_user.grp = "";
    global_user.id = "";
  }

  // NO HAY SESION
  else
    print_err("USERS_ERR", "No existe ninguna sesion.");
}

/**
 * Crear usuario
 * @brief Crea un usuario en una particion
 * @param  {user_commands} user_data
 */
void user_commands::mkusr(MkUserProps props) {
  if (props.usr.length() > 0) {
    if (props.pwd.length() > 0) {
      if (props.grp.length() > 0) {
        if (global_user.grp == "root") {
          // ABRIR
          int last_uid;
          string user_group = "";
          bool exists_same_user = 0;
          bool on_deleted_group = 0;

          // BUSCAR GRUPO
          string user_content = get_users_content(global_user.id);
          vector<string> user_lines = split(user_content, '\n');

          for (int line_index = 0; line_index < user_lines.size();
               line_index++) {
            UserOrGroup user_info =
                get_user_line_info(user_lines.at(line_index));

            // ASIGNAR GRUPO Y ULTIMO UID
            if (user_info.type == "G" && user_info.grp == props.grp) {
              if (user_info.uid == "0")
                on_deleted_group = 1;

              user_group = props.grp;
            } else if (user_info.type == "U") {
              if (user_info.name == props.usr)
                exists_same_user = 1;

              last_uid = (int)stoi(user_info.uid);
            }
          }

          // EL USUARIO NO EXISTE
          if (!exists_same_user) {
            // EXISTE GRUPO
            if (user_group.length() > 0) {
              // NO ES UN GRUPO ELIMINADO
              if (!on_deleted_group) {
                // VALIDAR MAXIMO 10 LETRAS PARA NOMBRE
                if (props.usr.length() <= 10) {
                  // VALIDAR MAXIMO 10 LETRAS PARA CONTRASEÑA
                  if (props.pwd.length() <= 10) {
                    // CREAR USUARIO
                    user_content += to_string(++last_uid) + "," + "U" + "," +
                                    user_group + "," + props.usr + "," +
                                    props.pwd + "\n";
                    save_users(user_content);
                  } else
                    print_err(
                        "USERS_ERR",
                        "La contraseña debe tener un maximo de 10 letras.");
                } else
                  print_err("USERS_ERR",
                            "El nombre debe tener un maximo de 10 letras.");
              } else
                print_err("USERS_ERR",
                          "El grupo \"" + props.grp + "\" esta eliminado.");
            } else
              print_err("USERS_ERR",
                        "No existe ningun grupo \"" + props.grp + "\".");
          } else
            print_err("USERS_ERR", "Este usuario ya existe.");
        } else
          print_err("USERS_ERR", "Este comando solo se ejecuta desde root.");
      } else
        print_err("USER_ERR", "El parametro grp es obligatorio.");
    } else
      print_err("USER_ERR", "El parametro pwd es obligatorio.");
  } else
    print_err("USER_ERR", "El parametro user es obligatorio.");
}

/**
 * Borrar usuario
 * @brief Configura el id 0 para el usuario seleccioando
 * @param  {user_commands} user_data
 */
void user_commands::rmusr(string user) {
  if (user.length() > 0) {
    if (global_user.grp == "root") {
      // ABRIR
      string new_content;
      bool user_exists = 0, is_deleted_user = 0;

      // LEER
      vector<string> user_lines = get_users(global_user.id);

      for (int line_index = 0; line_index < user_lines.size(); line_index++) {
        string line = user_lines.at(line_index);
        UserOrGroup user_info = get_user_line_info(line);

        // BUSCAR AL USUARIO
        if (user_info.type == "U") {
          if (user_info.name == user) {
            user_exists = 1;

            // ELIMINAR USUARIO
            if (line[0] != '0')
              line[0] = '0';
            else
              is_deleted_user = 1;
          }
        }

        // AGREGAR LINEA
        new_content += line + "\n";
      }

      // EL USUARIO EXISTE
      if (user_exists) {
        // EL USUARIO NO ESTA ELIMINADO
        if (!is_deleted_user) {
          save_users(new_content);
        } else
          print_err("USERS_ERR",
                    "El usuario \"" + user + "\" ya esta eliminado.");
      } else
        print_err("USERS_ERR", "No existe ningun usuario \"" + user + "\".");
    } else
      print_err("USERS_ERR", "Este comando solo se ejecuta desde root.");
  } else
    print_err("USER_ERR", "El parametro user es obligatorio.");
}