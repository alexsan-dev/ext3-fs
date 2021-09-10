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
#include <vector>

using namespace std;

extern int yyparse();
extern int col;
extern int line;
extern int yylineno;

void start_parse(string content) {
  // BUFFER
  YY_BUFFER_STATE buffer = yy_scan_string(content.c_str());

  // REINICIAR
  line = 0;
  col = 0;
  yylineno = 0;

  // PARSERAR
  yyparse();
}

int main(int argc, char *argv[]) {
  // LEER DE STDIN
  string content;
  string lineInput;
  while (getline(cin, lineInput)) {
    content += lineInput;
  }

  // EJECUTAR DIRECTAMENTE
  std::vector<std::string> all_args;
  if (argc > 1) {
    all_args.assign(argv + 1, argv + argc);
  }

  string new_content;
  for (int arg_index = 0; arg_index < all_args.size(); arg_index++) {
    new_content += all_args.at(arg_index) + " ";
  }

  start_parse(new_content);

  // ASIGNAR A GLOBAL
  stdin_content = content;
}
