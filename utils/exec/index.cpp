#include "../../disks/index.h"
#include "../../env/index.h"
#include "../../groups/index.h"
#include "../../nodes/index.h"
#include "../../partitions/index.h"
#include "../../users/index.h"

#include "../../lang/parser.h"
#include "../../lang/scanner.h"

#include "index.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

void exec_file(string path) {
  // ABRIR
  ifstream ifs(path);
  string content((istreambuf_iterator<char>(ifs)),
                 (istreambuf_iterator<char>()));

  // BUFFER
  YY_BUFFER_STATE buffer = yy_scan_string(content.c_str());

  // PARSERAR
  yyparse();
}