// DEFINE
#ifndef TOOLS_H
#define TOOLS_H

#include "string"
#include <vector>

using namespace std;

void print_err(string err_code, string err);
void print_warn(string warn_code, string warn);
bool warn_prompt(string info_code, string info);

vector<string> split(const string &s, char delim);
string format_day_prop(int field);
string get_now();

#endif // TOOLS_H