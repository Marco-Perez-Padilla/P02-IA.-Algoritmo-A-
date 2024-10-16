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

** Archivo laberinto.h: Declaración de la clase Laberinto
**      Contiene los métodos de la clase

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#ifndef LABERINTO_H
#define LABERINTO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <set>

#include "casilla.h"


#define PASS_ID  0
#define WALL_ID  1
#define PATH_ID  2
#define START_ID 3
#define END_ID   4

#define WALL_CHR  "█"
#define PASS_CHR  " "
#define PATH_CHR  "*"
#define START_CHR "S"
#define END_CHR   "E"

enum Direction {N, NE, E, SE, S, SW, W, NW};

//                   N    NE    E   SE    S   SW    W   NW
const short i_d[] = {-1,  -1,   0,   1,   1,   1,   0,  -1};
const short j_d[] = {0,    1,   1,   1,   0,  -1,  -1,  -1};

struct CasillaComparator {
  bool operator() (const Casilla* casilla1, const Casilla* casilla2) const {return *casilla1 < *casilla2;}
};

class Laberinto {
 private:
  std::vector<std::vector<Casilla*>> laberinto_;
  Casilla* start_;
  Casilla* end_;
  int nodos_;
 public:
  Laberinto(std::vector<std::vector<Casilla*>> laberinto) : laberinto_(laberinto), start_(nullptr), end_(nullptr) {}
  Laberinto (std::istream& input);
  Laberinto () = default;
  ~Laberinto();
  
  Casilla* getStart () const {return start_;}
  Casilla* getEnd () const {return end_;}
  std::vector<std::vector<Casilla*>>& getLaberinto () {return laberinto_;}
  Casilla* getCasilla (int row, int column) {return laberinto_[row][column];}
  const int getNodos () const {return nodos_;}

  void setStart(Casilla* casilla);
  void setEnd(Casilla* casilla);
  void setLaberinto(const std::vector<std::vector<Casilla*>>& maze) {laberinto_ = maze;}

  void read(std::istream& input);
  void UpdateManhattan(Casilla* end);
  void UpdateFunction(Casilla* cell);
  void UpdateCosts (Casilla* current, Casilla* neigbour, Direction direction);
  void ChangeStartEnd(long unsigned int StartRow, long unsigned int StartColumn, bool StartWall, long unsigned int EndRow, long unsigned int EndColumn, bool EndWall);
  const long unsigned int ManhattanDistance (int start_row, int end_row, int start_column, int end_column, int factor);

  bool AStarAlgorithm(Casilla* current, Casilla* end, std::priority_queue<Casilla*, std::vector<Casilla*>, CasillaComparator>& border, std::set<Casilla*>& closed, std::vector<Casilla*>& border_vector, std::vector<Casilla*>& closed_vector, unsigned int& iteration);
};

#endif