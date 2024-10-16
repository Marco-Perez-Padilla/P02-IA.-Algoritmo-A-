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

** Archivo AStarAlgorithm.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las clases X e Y
**      para ... (indicar brevemente el objetivo)

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**/

#include <iostream>

#include "../docs/general_functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include "laberinto.h"

int main(int argc, char* argv[]) {
    // Verificar que se haya pasado un argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_de_entrada>" << std::endl;
        return 1;
    }

    // Abrir el archivo de entrada
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error al abrir el archivo: " << argv[1] << std::endl;
        return 1;
    }

    // Crear un objeto Laberinto
    Laberinto laberinto(inputFile);

    // Mostrar el laberinto
    const auto& maze = laberinto.getLaberinto();
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            if (cell->getWall()) {
                std::cout << "▒";  
            } else if (cell == laberinto.getStart()) {
                std::cout << "S";  
            } else if (cell == laberinto.getEnd()) {
                std::cout << "E";  
            } else {
                std::cout << " ";  
            }
        }
        std::cout << std::endl; 
    }
    std::priority_queue<Casilla *, std::vector<Casilla *>, CasillaComparator> border;
    std::set<Casilla*> closed;
    std::vector<Casilla*> border_vector(1000);
    std::vector<Casilla*> closed_vector(1000);
    unsigned int iteration {0};
    laberinto.AStarAlgorithm(laberinto.getStart(), laberinto.getEnd(), border, closed, border_vector, closed_vector, iteration);
    return 0;
}
