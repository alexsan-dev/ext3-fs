#include "disks/index.h"
#include "env/index.h"
#include "groups/index.h"
#include "nodes/index.h"
#include "partitions/index.h"
#include "users/index.h"

#include "lang/parser.h"
#include "lang/scanner.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

extern int yyparse();
extern int col;
extern int line;
extern int yylineno;

void print_disks() {
  disk_commands *disk_cmd = new disk_commands();

  disk_cmd->print_disk("/Disco01.disk");
  disk_cmd->print_ebr("/Disco01.disk");
}

void read_test() {
  // ABRIR
  ifstream ifs("./test/input.txt");
  string content((istreambuf_iterator<char>(ifs)),
                 (istreambuf_iterator<char>()));

  // BUFFER
  YY_BUFFER_STATE buffer = yy_scan_string(content.c_str());

  // REINICIAR
  line = 0;
  col = 0;
  yylineno = 0;

  // PARSERAR
  yyparse();

  // GRAFICAS
  get_tree_graph();
}

int main(int argc, char *argv[]) { read_test(); }
