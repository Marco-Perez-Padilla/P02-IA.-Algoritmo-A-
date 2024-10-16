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

** Archivo laberinto.h: Implementación de la clase Laberinto
**      Contiene los métodos de la clase

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#include <cmath>
#include <algorithm>

#include "laberinto.h"

Laberinto::~Laberinto() {
  for (auto& row : getLaberinto()) {
    for (auto& casilla: row) {
      delete casilla;
      casilla = nullptr;
    }
  }
}

Laberinto::Laberinto(std::istream& input) {
  read(input);
}

void Laberinto::UpdateManhattan(Casilla* end) {
  if (!end || end->getEstimation() != 0) {
    std::cerr << "Error: End isn't defined, or given cell isn't the end" << std::endl;
    return;
  }
  unsigned int endRow = end->getRow();
  unsigned int endColumn = end->getColumn();
  for (auto& row : getLaberinto()) {
    for (auto& cell : row) {
      if (cell) {
        unsigned heuristic = ManhattanDistance(cell->getRow(), endRow, cell->getColumn(), endColumn, 3);
        cell->setEstimation(heuristic);
      }
    }
  }
}

void Laberinto::read(std::istream& input) {
  unsigned int rows, columns;
  input >> rows >> columns;
  nodos_ = rows*columns;
  std::vector<std::vector<Casilla*>> maze(rows, std::vector<Casilla*>(columns, nullptr));
  Casilla* tempStart = nullptr;
  for (unsigned int i {0}; i < rows; ++i) {
    for (unsigned int j {0}; j < columns; ++j) {
      int wall_value;
      if (!(input >> wall_value)) {
        for (unsigned int k = 0; k < i; ++k) {
          for (unsigned int l = 0; l < columns; ++l) {
            delete maze[k][l];
          }
        }
        std::cerr << "Error reading the cell (" << i << ", " << j << ")" << std::endl;
        return;
      }
      bool isWall {wall_value == 1};
      maze[i][j] = new Casilla(i, j, isWall);
      if (wall_value == 3) {
        tempStart =maze[i][j];
      } else if (wall_value == 4) {
        setEnd(maze[i][j]);
      }
    }
  }
  setStart(tempStart);
  setLaberinto(maze);
  UpdateManhattan(getEnd());
  if (!getStart() || !getEnd()) {
    std::cerr << "Error: Start or End not set correctly." << std::endl;
    for (unsigned int k = 0; k < rows; ++k) {
      for (unsigned int l = 0; l < columns; ++l) {
        delete maze[k][l];
      }
    }
    return;
  }
}

void Laberinto::setStart(Casilla* casilla) {
  if (casilla) { 
    start_ = casilla;
    getStart()->setCoste(0);
    getStart()->setEstimation(ManhattanDistance(getStart()->getRow(), getEnd()->getRow(), getStart()->getColumn(), getEnd()->getColumn(), 3));  
    UpdateFunction(getStart());
  } else {
    std::cerr << "Error: Trying to set Start pointer to invalid memory area." << std::endl;
  }
}

void Laberinto::setEnd(Casilla* casilla) {
  if (casilla) { 
    end_ = casilla;
    getEnd()->setEstimation(0);  
    UpdateFunction(casilla);
  } else {
    std::cerr << "Error: Trying to set End pointer to invalid memory area." << std::endl;
  }
}

void Laberinto::UpdateCosts (Casilla* current, Casilla* neigbour, Direction direction) {
  int move;
  if (direction == N || direction == E || direction == S || direction == W){
    move = 5;
  } else {
    move = 7;
  }
  neigbour->setCoste(current->getCoste() + move);
}

void Laberinto::UpdateFunction(Casilla* cell) {
  int coste = cell->getCoste();
  int heuristic = cell->getEstimation();
  int function = coste + heuristic;
  cell->setFunction(function);
}



void Laberinto::ChangeStartEnd(long unsigned int StartRow, long unsigned int StartColumn, bool StartWall, long unsigned int EndRow, long unsigned int EndColumn, bool EndWall) {
  if (StartRow < 0 || StartRow >= getLaberinto().size() || StartColumn < 0 || StartColumn >= getLaberinto()[0].size()) {
    std::cerr << "Error: Start coordenates out of range" << std::endl;
    return;
  }
  if (EndRow < 0 || EndRow >= getLaberinto().size() || EndColumn < 0 || EndColumn >= getLaberinto()[0].size()) {
    std::cerr << "Error: End coordenates out of range" << std::endl;
    return;
  }  

  Casilla* start = getStart();
  Casilla* end = getEnd();
  Casilla* newEnd = getCasilla(EndRow, EndColumn);
  Casilla* newStart = getCasilla(StartRow, StartColumn);

  if (!newStart || !newEnd) {
    std::cerr << "Error: Invalid new Start or End" << std::endl;
    return;
  }

  if (newEnd) {
    setEnd(newEnd); 
    getEnd()->setWall(false); 
    getEnd()->setEstimation(0);
  } else {
    std::cerr << "Error: New End invalid" << std::endl;
  }

  if (newStart) {
    setStart(newStart); 
    getStart()->setWall(false); 
    getStart()->setEstimation(ManhattanDistance(getStart()->getRow(), getEnd()->getRow(), getStart()->getColumn(), getEnd()->getColumn(), 3)); 
  } else {
    std::cerr << "Error: New Start invalid" << std::endl;
  }

  if (start) {
    start->setWall(StartWall); 
    start->setEstimation(ManhattanDistance(getStart()->getRow(), getEnd()->getRow(), getStart()->getColumn(), getEnd()->getColumn(), 3));
  } 
  if (end) {
    end->setWall(EndWall); 
    end->setEstimation(ManhattanDistance(getStart()->getRow(), getEnd()->getRow(), getStart()->getColumn(), getEnd()->getColumn(), 3));
  }
}

const long unsigned int Laberinto::ManhattanDistance (int start_row, int end_row, int start_column, int end_column, int factor) {
  return ((std::abs(start_row - end_row) + std::abs(start_column - end_column)) * factor);
}


bool Laberinto::AStarAlgorithm(Casilla* start, Casilla* end, std::priority_queue<Casilla*, std::vector<Casilla*>, CasillaComparator>& border, std::set<Casilla*>& closed, std::vector<Casilla*>& border_vector, std::vector<Casilla*>& closed_vector, unsigned int& iteration) {
  if (!start || !end) {
    std::cerr << "Error: start or end position is nullptr." << std::endl;
    return false;
  }
  
  if (start == end) {
    std::cout << "Found" << std::endl;
    return true;
  }

  border.push(start);
  border_vector.push_back(start);

  while (!border.empty()) {
    Casilla* current = border.top();
    border.pop();
    

    for (int dir = 0; dir < 8; ++dir) {
      int neighborRow = current->getRow() + i_d[dir];
      int neighborCol = current->getColumn() + j_d[dir];

      if (neighborRow >= 0 && neighborRow < laberinto_.size() && neighborCol >= 0 && neighborCol < laberinto_[0].size()) {
        Casilla* neighbor = getCasilla(neighborRow, neighborCol);
        neighbor->setPadre(current);
        if (neighbor && !neighbor->getWall() && closed.find(neighbor) == closed.end()) {
          auto it = std::find_if(border_vector.begin(), border_vector.end(), [neighbor](Casilla* c) {return c != nullptr && neighbor != nullptr && *c == *neighbor;});
          if (it == border_vector.end()) {
            UpdateCosts(current, neighbor, static_cast<Direction>(dir));
            neighbor->setPadre(current);
            UpdateFunction(neighbor);
            border.push(neighbor);
            border_vector.push_back(neighbor);
          } else {
            int func = neighbor->getFunction();
            int coste = neighbor->getCoste();
            UpdateCosts(current, neighbor, static_cast<Direction>(dir));
            UpdateFunction(neighbor);
            if (neighbor->getFunction() < func) {
              neighbor->setPadre(current);
            } else {
              neighbor->setCoste(coste);
              neighbor->setFunction(func);
            }
          }
        }
      } 
    }
    closed.insert(current);
    closed_vector.push_back(current);
    std::cout << *current << std::endl;
  }
  return false;
}
