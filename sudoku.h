//
// Created by Carlos Daniel on 29/08/2020.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

// Carlos Daniel Londoño Avila (1006593030) UTP
// Programa que resuelve un sudoku

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<vector<vector<int>>> Board;

// Convierte el sudoku recibido en un tablero donde se almacenas las
// posibilidades de cada celda
Board initialBoard(const vector<vector<int>>& s) {
  Board b;
  for (unsigned int i = 0; i < 9; i++) {
    vector<vector<int>> f;
    for (unsigned int j = 0; j < 9; j++) {
      if (s[i][j] == 0) {
        vector<int> x{1, 2, 3, 4, 5, 6, 7, 8, 9};
        f.push_back(x);
      } else {
        vector<int> x{s[i][j]};
        f.push_back(x);
      }
    }
    b.push_back(f);
  }
  return b;
}
// Verifica si la celda ya esta asignada
bool assigned(const Board& b, unsigned int i, unsigned int j) {
  return b[i][j].size() == 1;
}
// Muestra en pantalla la celda
void printCell(const Board& b, unsigned int i, unsigned int j) {
  const vector<int>& v = b[i][j];
  for (unsigned int k = 0; k < v.size(); k++) {
    cout << v[k];
  }
}
// Muestra el tablero en pantalla
void printboard(Board& b) {
  for (unsigned int f = 0; f < 9; f++) {
    // Por pura estetica
    if (f == 3 || f == 6) cout << "-----------" << endl;

    // Ciclo que recorre el tablero de celda en celda
    for (unsigned int c = 0; c < 9; c++) {
      // Por pura estetica
      if (c % 3 == 0 && c != 0) cout << "|";

      // Mostramos la celda
      if (assigned(b, f, c))
        printCell(b, f, c);
      else
        cout << "*";
    }
    cout << endl;
  }
  cout << endl;
}
// Elimina una posibilidad
void removeValue(Board& b, unsigned int i, unsigned int j, unsigned int val) {
  vector<int>& v = b[i][j];
  unsigned int p = -1;
  for (unsigned int k = 0; k < v.size(); k++) {
    if (v[k] == val) p = k;
  }
  if (p != -1) {
    v[p] = v[v.size() - 1];
    v.pop_back();
  }
}
// Filtra por fila
void rowFilter(Board& b, unsigned int i, unsigned int j) {
  assert(!assigned(b, i, j));
  for (unsigned int c = 0; c < 9; c++) {
    if (c != j && assigned(b, i, c)) {
      removeValue(b, i, j, b[i][c][0]);
    }
  }
}
// Filtra por columna
void colFilter(Board& b, unsigned int i, unsigned int j) {
  assert(!assigned(b, i, j));
  for (unsigned int f = 0; f < 9; f++) {
    if (f != i && assigned(b, f, j)) {
      removeValue(b, i, j, b[f][j][0]);
    }
  }
}
// Filtra por region
void regionFilter(Board& b, unsigned int i, unsigned int j) {
  assert(!assigned(b, i, j));  // Si la celda no esta asignada hace todo, de lo
                               // contrario aborta el programa
  for (unsigned int f = i - (i % 3); f < i - (i % 3) + 3; f++) {
    for (unsigned int c = j - (j % 3); c < j - (j % 3) + 3; c++) {
      if (assigned(b, f, c) && (f != i || c != j)) {
        removeValue(b, i, j, b[f][c][0]);
      }
    }
  }
}
// Filtra todo el tablero: por columna, fila y region
void boardFilter(Board& b) {
  for (unsigned int f = 0; f < 9; f++) {
    for (unsigned int c = 0; c < 9; c++) {
      if (!assigned(b, f, c)) {
        colFilter(b, f, c);
      }

      if (!assigned(b, f, c)) {
        rowFilter(b, f, c);
      }

      if (!assigned(b, f, c)) {
        regionFilter(b, f, c);
      }
    }
  }
}
// Cuenta cuantas celdas hay asignadas ya con un valor fijo
unsigned int countAssigned(const Board& b) {
  unsigned int x = 0;
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      if (assigned(b, i, j)) {
        x++;
      }
    }
  }
  return x;
}
// Retorna true si el sudoku ya esta solucionado o false de lo contrario
bool solution(const Board& b) { return countAssigned(b) == 81; }
// Filtra hasta mas no poder
void filterMax(Board& b) {
  unsigned int ideal = 81;
  unsigned int filtrados = countAssigned(b);
  assert(!solution(b));

  while (filtrados != ideal) {
    filtrados = ideal;
    boardFilter(b);
    ideal = countAssigned(b);
  }
}
// Retorna verdadero si hay un fallo en una celda(la celda se quedó sin
// posibilidades)
bool failure(const Board& b) {
  for (unsigned int f = 0; f < 9; f++) {
    for (unsigned int c = 0; c < 9; c++) {
      if (b[f][c].size() == 0) return true;
    }
  }
}
// Encuentra la celda sin asignar con menos posibilidades, almacena su posicion
// por referencia en i y j
unsigned int unsolvedCell(const Board& b, unsigned int& i, unsigned int& j) {
  unsigned int menor = 9;
  for (int f = 0; f < 9; f++) {
    for (int c = 0; c < 9; c++) {
      if (!assigned(b, f, c) && b[f][c].size() < menor) {
        menor = b[f][c].size();
        i = f;
        j = c;
      }
    }
  }
  return 0;
}
// Escoge una de las posibilidades de la celda
unsigned int possibleValue(const Board& b, unsigned int i, unsigned int j) {
  unsigned int t = b[i][j].size() - 1;
  return b[i][j][t];
}
// Asigna un celda
void assignedCell(Board& b, unsigned int i, unsigned int j, unsigned int val) {
  b[i][j][0] = val;

  while (b[i][j].size() > 1) {
    b[i][j].pop_back();
  }
}
// Resuelve el sudoku
Board solve(Board& b, bool& sol) {
  filterMax(b);

  if (solution(b)) {
    sol = true;
    return b;
  }

  if (failure(b)) {
    sol = false;
    return b;
  }
  Board a = b;
  unsigned int i;
  unsigned int j;
  unsolvedCell(a, i, j);
  unsigned int v = possibleValue(a, i, j);
  assignedCell(a, i, j, v);
  bool s = false;
  Board c = solve(a, s);
  if (s) {
    sol = true;
    return c;
  }
  removeValue(b, i, j, v);
  return solve(b, s);
}

#endif  // SUDOKU_SUDOKU_H
