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

** Archivo general_functions.cc: Implementación de funciones de ayuda
**      

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#include <iostream>

#include "general_functions.h"

void Usage() {
  std::cout << "Usage: ./AStarAlgorithm filein1.txt filein2.txt filein3.txt board.txt iterations.txt out_maze.txt\n"
            << "Try './AStarAlgorithm --help' for further information\n";
}

void Help () {
    std::cout << "./AStarAlgorithm   -- Result to a maze\n"
              << "Usage:             ./AStarAlgorithm filein1.txt filein2.txt filein3.txt board.txt iterations.txt out_maze.txt\n"
              << "\n"              
              << "filein[1-3].txt:   Input maze files\n"
              << "board.txt:         Board of all maze inputs\n"
              << "iterations.txt:    Results of search for each maze\n"
              << "out_mazes.txt:     Board of all maze inputs\n"
              << "\n";
}
