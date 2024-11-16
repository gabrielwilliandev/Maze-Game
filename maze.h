#ifndef MAZE_H
#define MAZE_H

// Estrutura para armazenar informações do cronômetro
typedef struct cronometro {
    int segundos;                  // Segundos acumulados
    int minutos;                   // Minutos acumulados
    char tempoformatado[6];        // Tempo formatado no estilo "MM:SS"
} cronometro_t;

// Estrutura para armazenar informações de um jogador
typedef struct usuarios {
    char nome[100];                // Nome do jogador
    cronometro_t *cronometro;      // Ponteiro para o cronômetro do jogador
    struct usuarios *prox;         // Ponteiro para o próximo jogador na lista
} usuarios_t;

// Prototipagem de funções

// Cria o primeiro usuário na lista de jogadores.
usuarios_t *primeiro_usuario(char *nome);

// Exibe o menu principal do jogo.
 
void menu(usuarios_t **listausuarios);

// Adiciona um novo jogador à lista de jogadores.
 
void proximo_usuario(usuarios_t *primeiro, char *nome);

// Atualiza o tempo do cronômetro.


void Atualizacronometro(cronometro_t *tempo);

// Controla o movimento do jogador com base na entrada do teclado.

void control(cronometro_t *tempo);

// Atualiza a posição do jogador no mapa e redesenha o cenário.

void draw(int px, int py, cronometro_t *tempo);

// Inicia uma nova partida do jogo.

void iniciar(usuarios_t **listausuarios);

// Exibe as estatísticas de todos os jogadores.

void estatisticas(usuarios_t *listausuarios);

//Libera a memória alocada para a lista de jogadores.
void freememoria(usuarios_t **listausuarios);

#endif

