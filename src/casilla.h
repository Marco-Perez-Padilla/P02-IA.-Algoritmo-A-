/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Inteligencia Artificial
** Curso: 3º
** Practica 2: Algoritmo A*
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 13/10/2024

** Archivo casilla.h: Declaración de la clase Casilla
**      Contiene los métodos de la clase

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#ifndef CASILLA_H
#define CASILLA_H

#include <iostream>
#include <utility>

class Casilla {
 private:
  int row_;
  int column_;
  int estimation_;
  int coste_;
  int function_;
  bool wall_;
  Casilla* padre_;
 public:
  Casilla(int i, int j,  bool wall, int estimation = 0, int coste = 0, int function = 0) : row_(i), column_(j), wall_(wall), estimation_(estimation), coste_(coste), function_(function) {}

  int getRow () const {return row_;}
  int getColumn () const {return column_;}
  int getEstimation () const {return estimation_;}
  int getCoste () const {return coste_;}
  int getFunction() const {return function_;}
  bool getWall () const {return wall_;}
  Casilla* getPadre () const {return padre_;}

  void setRow (int i) {row_ = i;}
  void setColumn (int j) {column_ = j;}
  void setEstimation (int hn) {estimation_ = hn;}
  void setCoste (int coste) {coste_ = coste;}
  void setFunction (int function) {function_ = function;}
  void setWall (bool wall) {wall_ = wall;}
  void setPadre (Casilla* padre) {padre_ = padre;}
};
bool operator<(const Casilla& casilla1, const Casilla& casilla2);
bool operator==(const Casilla& casilla1, const Casilla& casilla2);
std::ostream& operator<<(std::ostream& os, const Casilla& casilla);

#endif