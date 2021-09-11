%output "parser.cpp"
%defines "parser.h"
%error-verbose
%locations

/* AGREGAR CODIGO */
%{
#include "scanner.h"
#include <iostream>
#include <string.h>

#include "../permissions/index.h"
#include "../partitions/index.h"
#include "../utils/exec/index.h"
#include "../graphs/index.h"
#include "../groups/index.h"
#include "../disks/index.h"
#include "../nodes/index.h"
#include "../users/index.h"

using namespace std;

extern int yylineno; 
extern char *yytext;
extern int col;

int yyerror(const char* mens) {
    std::cout << mens << " " << yytext << std::endl;
    return 0;
}
%}

/* ESTRUCTURAS LOCALES */
%code requires {
    struct PropVariant {
        char *value;
        char *name;
    };
}

/* FUNCIONES LOCALES */
%code {
    PropVariant set_prop(char *value, char *key){
        PropVariant prop = { value, key };
        return prop;
    }
}

/* TIPOS EN PRODUCCIONES */
%union {
    struct PartitionCommandsProps *PTCMDPROPS;
    struct DiskCommandsProps *DKCMDPROPS;
    struct PartitionFsProps *FSCMDPROPS;
    struct UserCommandsProps *USRCMDPROPS;
    struct MkUserProps *MKUSRCMDPROPS;
    struct ChmodProps *CHMODCMDPROPS;
    struct TouchProps *TOUCHCMDPROPS;
    struct RepProps *REPCMDPROPS;
    struct ListProp *FILELIST;
    struct PropVariant PROP;
    char *TEXT;
}

/* SIMBOLOS */
%token<TEXT> equals;

/* PALABRAS RESERVADAS */
%token<TEXT> mkdisk;
%token<TEXT> rmdisk;
%token<TEXT> fdisk;
%token<TEXT> mount;
%token<TEXT> unmount;
%token<TEXT> mkfs;
%token<TEXT> login;
%token<TEXT> logout;
%token<TEXT> mkgrp;
%token<TEXT> rmgrp;
%token<TEXT> mkusr;
%token<TEXT> rmusr;
%token<TEXT> chmod;
%token<TEXT> touch;
%token<TEXT> cat;
%token<TEXT> mkdir;
%token<TEXT> execR;
%token<TEXT> repR;

%token<TEXT> sizeP;
%token<TEXT> path;
%token<TEXT> unit;
%token<TEXT> fit;
%token<TEXT> type;
%token<TEXT> name;
%token<TEXT> add;
%token<TEXT> del;
%token<TEXT> idP;
%token<TEXT> pPr;
%token<TEXT> fs;
%token<TEXT> pwd;
%token<TEXT> user;
%token<TEXT> usr;
%token<TEXT> grp;
%token<TEXT> ugo;
%token<TEXT> rPr;
%token<TEXT> cont;
%token<TEXT> stdinR;
%token<TEXT> filePr;
%token<TEXT> rootR;
%token<TEXT> ruta;

/* MBR */
%token<TEXT> mbr;
%token<TEXT> sp;

/* TIPOS GENERALES */
%token<TEXT> likepath;
%token<TEXT> strtext;
%token<TEXT> letter;
%token<TEXT> number;
%token<TEXT> word;
%token<TEXT> comment;

/* TIPOS ESPECIALES */
%type<TEXT> STRVALUE;
%type<TEXT> NUMVALUE;

/* OPCIONES MKDISK */
%type<DKCMDPROPS> MKDISKPROPS;
%type<PROP> MKDISKPROP;
%type<TEXT> PATHPARAM;
%type<TEXT> UNITPARAM;
%type<TEXT> SIZEPARAM;
%type<TEXT> FITPARAM;
%type<TEXT> IDPARAM;

/* OPCIONES FDISK */
%type<PTCMDPROPS> FDISKPROPS;
%type<PROP> FDISKPROP;
%type<TEXT> TYPEPARAM;
%type<TEXT> DELPARAM;
%type<TEXT> NAMEPARAM;
%type<TEXT> ADDPARAM;

/* OPCIONES MKFS */
%type<FSCMDPROPS> MKFSPROPS;
%type<TEXT> TYPEEXTPARAM;
%type<PROP> MKFSPROP;
%type<TEXT> FSPARAM;

/* OPCIONES LOGIN */
%type<USRCMDPROPS> LOGINPROPS;
%type<PROP> LOGINPROP;
%type<TEXT> PWDPARAM;

/* OPCIONES MKUSER */
%type<MKUSRCMDPROPS> MKUSRPROPS;
%type<PROP> MKUSRPROP;
%type<TEXT> USRPARAM;
%type<TEXT> GRPPARAM;

/* OPCIONES CHMOD */
%type<CHMODCMDPROPS> CHMODPROPS;
%type<PROP> CHMODPROP;
%type<TEXT> UGOPARAM;

/* OPCIONES TOUCH */
%type<TOUCHCMDPROPS> TOUCHPROPS;
%type<PROP> TOUCHPROP;
%type<TEXT> CONTPARAM;

/* OPCIONES PARA CAT */
%type<FILELIST> FILELIST;

/* OPCIONES REP */
%type<REPCMDPROPS> REPPROPS;
%type<PROP> REPPROP;
%type<TEXT> ROOTPARAM;
%type<TEXT> RUTAPARAM;

%start START

%left likepath word letter 

%%

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* INICIO */
STRVALUE : strtext {
    string value = $1;
    value = value.substr(1, value.size() - 2);
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    $$ = text;
} | likepath {
    string value = $1;
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    $$ = text;
} | word {
    string value = $1;
    char *text =  new char[value.length() + 1];
    strcpy(text, value.c_str());
    $$ = text;
};

NUMVALUE : word {
    $$ = $1;
} | number {
    $$ = $1;
}

START : COMMANDS { };

COMMANDS : COMMANDS COMMAND | COMMAND { };

COMMAND : MKDISKCMD | RMDISKCMD | FDISKCMD 
| MOUNTCMD | UNMOUNTCMD | MKFSCMD | MKDIRCMD 
| LOGINCMD | LOGOUTCMD | MKUSRCMD | MKGRPCMD 
| RMGRPCMD | RMUSRCMD | CHMODCMD | TOUCHCMD 
| CATCMD | EXECCMD | REPCMD | comment { };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MKDISK */
MKDISKCMD : mkdisk MKDISKPROPS { 
    disk_commands *disk_cmd = new disk_commands();
    disk_cmd->mkdisk(*$2);  
    delete disk_cmd;
};

MKDISKPROPS : MKDISKPROP {
    DiskCommandsProps *props = new DiskCommandsProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | MKDISKPROPS MKDISKPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

MKDISKPROP : SIZEPARAM { $$ = set_prop($1, (char*) "size"); }
| PATHPARAM { $$ = set_prop($1, (char*) "path"); }
| UNITPARAM { $$ = set_prop($1, (char*) "unit"); }
| FITPARAM { $$ = set_prop($1, (char*) "fit"); };

UNITPARAM : unit equals letter { $$ = $3; };
PATHPARAM : path equals STRVALUE { $$ = $3; };
SIZEPARAM : sizeP equals NUMVALUE { $$ = $3; };
FITPARAM : fit equals letter letter { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* RMDISK */
RMDISKCMD : rmdisk PATHPARAM { 
    disk_commands *disk_cmd = new disk_commands();
    string path = $2;
    disk_cmd->rmdisk(path);
    delete disk_cmd;
};

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* FDISK */
FDISKCMD : fdisk FDISKPROPS { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->fdisk(*$2); 
    delete part_cmd; 
};

FDISKPROPS : FDISKPROP {
    PartitionCommandsProps *props = new PartitionCommandsProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | FDISKPROPS FDISKPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

FDISKPROP : SIZEPARAM { $$ = set_prop($1, (char*) "size"); }
| PATHPARAM { $$ = set_prop($1, (char*) "path"); }
| UNITPARAM { $$ = set_prop($1, (char*) "unit"); }
| FITPARAM { $$ = set_prop($1, (char*) "fit"); }
| TYPEPARAM { $$ = set_prop($1, (char*) "type"); }
| DELPARAM { $$ = set_prop($1, (char*) "del"); }
| NAMEPARAM { $$ = set_prop($1, (char*) "name"); }
| ADDPARAM { $$ = set_prop($1, (char*) "add"); };

TYPEPARAM : type equals letter { $$ = $3; };
DELPARAM : del equals STRVALUE { $$ = $3; };

NAMEPARAM : name equals STRVALUE { $$ = $3; }
| name equals mbr { $$ = (char*) "mbr"; };
| name equals sp { $$ = (char*) "sp"; };

ADDPARAM : add equals NUMVALUE { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MOUNT */
MOUNTCMD : mount PATHPARAM NAMEPARAM { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mount($2, $3);  
    delete part_cmd;
} | mount NAMEPARAM PATHPARAM { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mount($3,$2); 
    delete part_cmd; 
};

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* UNMOUNT */
UNMOUNTCMD : unmount IDPARAM { 
    partition_commands *part_cmd = new partition_commands();
    string id = $2;
    part_cmd->unmount(id);  
    delete part_cmd;
};

IDPARAM : idP equals STRVALUE { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MKFS */
MKFSCMD : mkfs MKFSPROPS { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mkfs(*$2);  
    delete part_cmd;
};

MKFSPROPS : MKFSPROP {
    PartitionFsProps *props = new PartitionFsProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | MKFSPROPS MKFSPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

MKFSPROP : IDPARAM { $$ = set_prop($1, (char*) "id"); }
| TYPEEXTPARAM { $$ = set_prop($1, (char*) "type"); }
| FSPARAM { $$ = set_prop($1, (char*) "fs"); };

TYPEEXTPARAM : type equals STRVALUE { $$ = $3; };
FSPARAM : fs equals number letter letter { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* LOGIN */
LOGINCMD : login LOGINPROPS { 
    user_commands *user_cmd = new user_commands();
    user_cmd->login(*$2);  
    delete user_cmd;
};

LOGINPROPS : LOGINPROP {
    UserCommandsProps *props = new UserCommandsProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | LOGINPROPS LOGINPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

LOGINPROP : IDPARAM { $$ = set_prop($1, (char*) "id"); }
| USRPARAM { $$ = set_prop($1, (char*) "user"); }
| PWDPARAM { $$ = set_prop($1, (char*) "pwd"); };

PWDPARAM : pwd equals STRVALUE { $$ = $3; } | pwd equals number { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* LOGOUT */
LOGOUTCMD : logout { 
    user_commands *user_cmd = new user_commands();
    user_cmd->logout(); 
    delete user_cmd; 
}

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MKGRP */
MKGRPCMD : mkgrp NAMEPARAM { 
    group_commands *grp_cmd = new group_commands();
    grp_cmd->mkgrp($2); 
    delete grp_cmd; 
}

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* RMGRP */
RMGRPCMD : rmgrp NAMEPARAM { 
    group_commands *grp_cmd = new group_commands();
    grp_cmd->rmgrp($2); 
    delete grp_cmd; 
}

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MKUSR */
MKUSRCMD : mkusr MKUSRPROPS { 
    user_commands *user_cmd = new user_commands();
    user_cmd->mkusr(*$2); 
    delete user_cmd;
}

MKUSRPROPS : MKUSRPROP {
    MkUserProps *props = new MkUserProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | MKUSRPROPS MKUSRPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

MKUSRPROP : PWDPARAM { $$ = set_prop($1, (char*) "pwd"); }
| USRPARAM { $$ = set_prop($1, (char*) "usr"); }
| GRPPARAM { $$ = set_prop($1, (char*) "grp"); };

USRPARAM : usr equals STRVALUE { $$ = $3; };
GRPPARAM : grp equals STRVALUE { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* RMUSR */
RMUSRCMD : rmusr USRPARAM { 
    user_commands *user_cmd = new user_commands();
    user_cmd->rmusr($2); 
    delete user_cmd; 
}

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* CHMOD */
CHMODCMD : chmod CHMODPROPS { 
    permission_commands *perm_cmd = new permission_commands();
    perm_cmd->chmod(*$2);  
    delete perm_cmd;
};

CHMODPROPS : CHMODPROP {
    ChmodProps *props = new ChmodProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | CHMODPROPS CHMODPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

CHMODPROP : PATHPARAM { $$ = set_prop($1, (char*) "path"); }
| UGOPARAM { $$ = set_prop($1, (char*) "ugo"); }
| rPr { $$ = set_prop($1, (char*) "r"); };

UGOPARAM : ugo equals STRVALUE { $$ = $3; } | ugo equals number { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* TOUCH */
TOUCHCMD : touch TOUCHPROPS { 
    node_commands *node_cmd = new node_commands();
    node_cmd->touch(*$2); 
    delete node_cmd;
};

TOUCHPROPS : TOUCHPROP {
    TouchProps *props = new TouchProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | TOUCHPROPS TOUCHPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

TOUCHPROP : PATHPARAM { $$ = set_prop($1, (char*) "path"); }
| SIZEPARAM { $$ = set_prop($1, (char*) "size"); }
| CONTPARAM { $$ = set_prop($1, (char*) "cont"); }
| rPr { $$ = set_prop($1, (char*) "r"); }
| stdinR { $$ = set_prop($1, (char*) "stdin"); };

CONTPARAM : cont equals STRVALUE { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* CAT */
CATCMD : cat FILELIST {
    node_commands *node_cmd = new node_commands();
    node_cmd->cat(*$2); 
    delete node_cmd;
}

FILELIST : filePr number equals STRVALUE {
    ListProp *props = new ListProp();
    props->list.push_back($3);
    $$ = props;
} | FILELIST filePr number equals STRVALUE {
    $1->list.push_back($4);
    $$ = $1;
};

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* MKDIR */
MKDIRCMD : mkdir PATHPARAM pPr { 
    node_commands *node_cmd = new node_commands();
    string path = $2;
    node_cmd->mkdir(path, 1); 
    delete node_cmd;
} | mkdir pPr PATHPARAM { 
    node_commands *node_cmd = new node_commands();
    string path = $3;
    node_cmd->mkdir(path, 1); 
    delete node_cmd; 
} | mkdir PATHPARAM { 
    node_commands *node_cmd = new node_commands();
    string path = $2;
    node_cmd->mkdir(path, 0); 
    delete node_cmd; 
};

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* REP */
REPCMD : repR REPPROPS { 
    graph_commands *graph_cmd = new graph_commands();
    graph_cmd->rep(*$2); 
    delete graph_cmd;
};

REPPROPS : REPPROP {
    RepProps *props = new RepProps();
    props->set_prop($1.value, $1.name);
    $$ = props;
} | REPPROPS REPPROP {
    $1->set_prop($2.value, $2.name);
    $$ = $1;
};

REPPROP : NAMEPARAM { $$ = set_prop($1, (char*) "name"); }
| PATHPARAM { $$ = set_prop($1, (char*) "path"); }
| IDPARAM { $$ = set_prop($1, (char*) "id"); }
| RUTAPARAM { $$ = set_prop($1, (char*) "ruta"); }
| ROOTPARAM { $$ = set_prop($1, (char*) "root"); };

RUTAPARAM : ruta equals STRVALUE { $$ = $3; };
ROOTPARAM : rootR equals STRVALUE { $$ = $3; };

/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/
/* EXEC */
EXECCMD : execR PATHPARAM {
    exec_file($2);
};

%%