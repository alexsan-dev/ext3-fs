%option case-insensitive
%option yylineno
%option noyywrap
%option nounput

%{
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "parser.h"

using namespace std;

void yyerror(const char *s);
int yylex();
int line = 0;
int prevC = 0;
int col = 1;
%}

number [0-9]+
letter [a-zA-ZÑñáéíóúÁÉÍÓÚ]
strtext [\"][^\"\n]*[\"\n]
likepath (\/[a-zA-ZÑñáéíóúÁÉÍÓÚ0-9\.\-_]+)+
word [a-zA-ZÑñáéíóúÁÉÍÓÚ0-9]{3,}([a-zA-ZÑñáéíóúÁÉÍÓÚ0-9\.\-_]+)+

%x COM

%%
"MKDISK" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mkdisk;}
"RMDISK" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return rmdisk;}
"FDISK" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return fdisk;}
"MOUNT" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mount;}
"UMOUNT" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return unmount;}
"MKFS" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mkfs;}
"LOGIN" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return login;}
"LOGOUT" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return logout;}
"MKGRP" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mkgrp;}
"RMGRP" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return rmgrp;}
"MKUSR" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mkusr;}
"RMUSR" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return rmusr;}
"CHMOD" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return chmod;}
"TOUCH" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return touch;}
"CAT" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return cat;}
"MKDIR" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return mkdir;}

"-DELETE" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return del;}
"-SIZE" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return sizeP;}
"-PATH" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return path;}
"-NAME" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return name;}
"-TYPE" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return type;}
"-ADD" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return add;}
"-F" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return fit;}
"-U" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return unit;}
"-P" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return pPr;}
"-ID" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return idP;}
"-FS" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return fs;}
"-PWD" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return pwd;}
"-USER" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return user;}
"-USR" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return usr;}
"-GRP" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return grp;}
"-UGO" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return ugo;}
"-R" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return rPr;}
"-CONT" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return cont;}
"-STDIN" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return stdinR;}
"-FILE" {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return filePr;}

{word} {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return word;}
{letter} {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return letter;}
{likepath} {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return likepath;}
{strtext} {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return strtext;}
{number} {col += prevC;  prevC = strlen(yytext); yylval.TEXT = yytext; return number;}

"#"[^"\n"]* {col += prevC; prevC = strlen(yytext); yylval.TEXT = yytext; return comment;}

"=" {col += prevC; prevC = strlen(yytext); yylval.TEXT = yytext; return equals;}

"\n" {
    line++; col=0; prevC=0;
}

[[:blank:]] { 
    col++; 
}

. {
    std::cout<<"Error Lexico: "<< line << "\n";
}
%%