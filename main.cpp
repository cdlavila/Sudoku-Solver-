#include <iostream>
#include "sudoku.h"
using namespace std;

int main() {
    cout << "SUDOKU SOLVER!" << endl;
    //Recibo el sudoku y lo almaceno en un vector
    vector<vector<int>> s{
            //Dificil
            {0,0,0,3,0,7,0,0,0},
            {0,5,0,0,6,0,4,7,0},
            {9,0,0,0,0,8,0,6,2},
            {0,1,4,7,0,3,0,0,6},
            {7,0,0,0,0,5,0,0,1},
            {5,0,0,6,0,0,9,8,0},
            {0,7,0,4,0,0,0,0,8},
            {3,0,6,0,0,0,0,2,4},
            {0,0,0,9,7,2,0,0,0}};
    //Facil
    /*{2,0,0,0,6,4,9,0,0},
    {5,0,8,1,0,0,6,4,0},
    {0,0,6,0,0,5,0,0,0},
    {0,0,0,3,0,0,5,9,0},
    {0,3,0,4,0,0,0,2,0},
    {0,7,5,0,9,1,0,0,0},
    {0,0,0,8,0,0,3,5,0},
    {9,0,7,0,0,2,0,0,8},
    {0,0,1,5,4,0,0,0,6}};
    */
    //Se crea el tablero almacenando {1,2,3,4,5,6,7,8,9} donde haya 0 y dejando las celdas ya asignadas
    Board initial = initialBoard(s);

    cout<<"Your sudoku is this" <<endl;
    printboard(initial);

    bool a=false;
    solve(initial, a);

    cout<<"Sudoku solved is this" <<endl;
    printboard(initial);

    return 0;
}