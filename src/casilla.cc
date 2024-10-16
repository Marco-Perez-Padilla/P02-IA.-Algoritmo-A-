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

** Archivo cya-P02-strings.cc: Implementación de la clase Casilla.
**      Contiene la sobrecarga del operador <

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#include <iostream>

#include "casilla.h"

bool operator<(const Casilla& casilla1, const Casilla& casilla2) {
  if (casilla1.getFunction() != casilla2.getFunction()) {
    return casilla1.getFunction() < casilla2.getFunction();
  }
  if (casilla1.getEstimation() != casilla2.getEstimation()) {
    return casilla1.getEstimation() < casilla2.getEstimation();
  }
  if (casilla1.getCoste() != casilla2.getCoste()) {
    return casilla1.getCoste() < casilla2.getCoste();
  }
  if (casilla1.getRow() != casilla2.getRow()) {
    return casilla1.getRow() < casilla2.getRow();
  }
  if (casilla1.getColumn() != casilla2.getColumn()) {
    return casilla1.getColumn() < casilla2.getColumn();
  }
  if (casilla1.getWall() != casilla2.getWall()) {
    return casilla1.getWall() > casilla2.getWall();
  }
}

std::ostream& operator<<(std::ostream& os, const Casilla& casilla) {
    os << "Casilla(" << casilla.getRow() << ", " << casilla.getColumn() 
       << ", Estimation: " << casilla.getEstimation() 
       << ", Coste: " << casilla.getCoste() 
       << ", Function: " << casilla.getFunction() 
       << ", Wall: " << (casilla.getWall() ? "Yes" : "No") << ")";
    return os;
}

bool operator==(const Casilla& casilla1, const Casilla& casilla2) {
  return (casilla1.getRow() == casilla2.getRow() && casilla1.getColumn() == casilla2.getColumn() && casilla1.getCoste() == casilla2.getCoste() && casilla1.getFunction() == casilla2.getFunction() && casilla1.getPadre() == casilla2.getPadre());
}
