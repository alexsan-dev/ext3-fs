#include "index.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

/**
 * Imprimir con color
 * @brief Imprime un texto con color
 * @param {string} color
 * @param {string} msg_code
 * @param {string} msg
 */
void print_with_color(string color, string msg_code, string msg,
                      bool new_line) {
  string break_line = new_line ? "\n" : " ";
  cout << "\033[1;" << color << "m[" << msg_code << "] "
       << "\033[0m" << msg << break_line;
}

/**
 * Imprimir error
 * @brief Imprime un texto en rojo
 * @param {string} err_code
 * @param {string} err
 */
void print_err(string err_code, string err) {
  print_with_color("31", err_code, err, 1);
}

/**
 * Imprimir advertencia
 * @brief Imprime un texto en amarillo
 * @param {string} warn_code
 * @param {string} warn
 */
void print_warn(string warn_code, string warn) {
  print_with_color("33", warn_code, warn, 1);
}

/**
 * Imprimir prompt de informacion
 * @brief Imprime un texto en amarillo y espera entrada;
 * @param {string} info_color
 * @param {string} info
 */
bool warn_prompt(string info_color, string info) {
  string confirm = "no";
  print_with_color("33", info_color, info, 0);
  cin >> confirm;

  // SI O NO
  return confirm == "s" || confirm == "S";
}

/**
 * Seperar string
 * @brief Separa un string con un delimitador
 * @param  {string} s
 * @param  {char} delim
 */
vector<string> split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> tokens;

  while (getline(ss, item, delim))
    tokens.push_back(item);

  return tokens;
}

/**
 * Obtener fecha como string
 * @brief Retorna un string de la fecha actual
 *
 */
string get_now() {
  time_t time_now = time(0);
  tm *now = localtime(&time_now);
  string current_date =
      format_day_prop(now->tm_mday) + "/" + format_day_prop(now->tm_mon + 1) +
      "/" + to_string(now->tm_year + 1900) + " " +
      format_day_prop(now->tm_hour) + ":" + format_day_prop(now->tm_min);
  return current_date;
}

/**
 * Formato de fecha
 * @brief Crea una fecha estandar
 * @param  {int} field
 */
string format_day_prop(int field) {
  return (field < 10 ? "0" : "") + to_string(field);
}