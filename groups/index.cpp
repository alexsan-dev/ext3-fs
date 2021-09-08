#include "index.h"
#include "../env/index.h"
#include "../users/index.h"
#include "../utils/tools/index.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

group_commands::group_commands() {}

/**
 * Crear grupo
 * @brief Crea un grupo en una particion
 * @param  {string} name
 */
void group_commands::mkgrp(string name) {
  if (global_user.grp == "root") {
    // ABRIR
    string new_content;
    int last_uid = 0;
    bool group_exits = 0, is_deleted_group = 0;

    // LEER
    vector<string> user_lines = get_users(global_user.id);

    for (int line_index = 0; line_index < user_lines.size(); line_index++) {
      string line = user_lines.at(line_index);
      UserOrGroup user_info = get_user_line_info(line);

      // BUSCAR GRUPO EXISTENTE
      if (user_info.type == "G") {
        if (user_info.grp == name) {
          group_exits = 1;

          // RESTAURAR
          if (user_info.uid == "0") {
            group_exits = 0;
            is_deleted_group = 1;
          }
        } else
          last_uid = stoi(user_info.uid);
      }

      // AGREGAR LINEA
      if (!is_deleted_group)
        new_content += line + "\n";
    }

    // EL GRUPO NO EXISTE
    if (!group_exits) {
      // VALIDAR MAXIMO 10 LETRAS PARA NOMBRE
      if (name.length() <= 10) {
        // GUARDAR
        new_content += to_string(++last_uid) + "," + "G" + "," + name + "\n";
        save_users(new_content);

        // EL GRUPO ESTA ELIMINADO
        if (is_deleted_group)
          print_warn("GROUPS_WARN",
                     "El grupo \"" + name +
                         "\" esta eliminado pero se procedera a restaurar.");
      } else
        print_err("GROUPS_ERR", "El nombre debe tener un maximo de 10 letras.");
    } else
      print_err("GROUPS_ERR", "El grupo \"" + name + "\"" + " ya existe.");
  } else
    print_err("GROUPS_ERR", "Este comando solo se ejecuta desde root.");
}

/**
 * Borrar grupo
 * @brief Configura el id 0 para el grupo seleccioando
 * @param  {string} name
 */
void group_commands::rmgrp(string name) {
  if (name.length() > 0) {

    if (global_user.grp == "root") {
      // ABRIR
      string new_content;
      bool group_exists = 0, is_deleted_group = 0;

      // LEER
      vector<string> user_lines = get_users(global_user.id);

      for (int line_index = 0; line_index < user_lines.size(); line_index++) {
        string line = user_lines.at(line_index);
        UserOrGroup user_info = get_user_line_info(line);

        // BUSCAR AL GRUPO
        if (user_info.grp == name) {
          group_exists = 1;

          // ELIMINAR GRUPO
          if (line.at(0) != '0')
            line = line.replace(0, 1, "0");
          else
            is_deleted_group = 1;
        }

        // AGREGAR LINEA
        new_content += line + "\n";
      }

      // EL GRUPO EXISTE
      if (group_exists) {
        // EL GRUPO NO ESTA ELIMINADO
        if (!is_deleted_group) {
          save_users(new_content);
        } else
          print_err("GROUPS_ERR",
                    "El grupo \"" + name + "\" ya esta eliminado.");
      } else
        print_err("GROUPS_ERR", "No existe ningun grupo \"" + name + "\".");
    } else
      print_err("GROUPS_ERR", "Este comando solo se ejecuta desde root.");
  } else
    print_err("GROUPS_ERR", "El parametro name es obligatorio.");
}