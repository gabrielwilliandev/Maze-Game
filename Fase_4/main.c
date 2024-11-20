#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "maze.h"

/**
 * Fun��o principal do programa.
 * Inicializa a lista de usu�rios e chama o menu principal do jogo.
 */
int main() {
    // Ponteiro para a lista de usu�rios, inicialmente vazio
    usuarios_t *listausuarios = NULL;

    // Exibe o menu principal do jogo
    menu(&listausuarios);

    return 0;
}

