// DEFINE
#ifndef USERCOMMANDS_H
#define USERCOMMANDS_H

#include "../partitions/index.h"
#include "string"
#include <vector>

using namespace std;

// LINEAS
struct UserOrGroup {
  string uid;
  string type;
  string name;
  string pwd;
  string grp;
};

struct MkUserProps {
  string usr;
  string pwd;
  string grp;

  void set_prop(string value, string key) {
    if (key == "usr") {
      usr = value;
    } else if (key == "pwd") {
      pwd = value;
    } else if (key == "grp") {
      grp = value;
    }
  }
};

// PROPIEDADES
struct UserCommandsProps {
  string user;
  string pwd;
  string grp;
  string id;

  void set_prop(string value, string key) {
    if (key == "id") {
      id = value;
    } else if (key == "user") {
      user = value;
    } else if (key == "pwd") {
      pwd = value;
    }
  }
};

// HERRAMIENTAS
string get_users_content(string id);
vector<string> get_users(string id);
void save_users(string new_content);
UserOrGroup get_user_line_info(string line);

// COMANDOS
class user_commands {
public:
  user_commands();

  // METODOS
  void login(UserCommandsProps props);
  void mkusr(MkUserProps props);
  void rmusr(string user);
  void logout();
};

#endif // USERCOMMANDS_H