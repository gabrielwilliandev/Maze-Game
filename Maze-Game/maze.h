#ifndef MAZE_H
#define MAZE_H

// Estrutura para armazenar informa��es do cron�metro
typedef struct cronometro {
    int segundos;                  // Segundos acumulados
    int minutos;                   // Minutos acumulados
    char tempoformatado[6];        // Tempo formatado no estilo "MM:SS"
} cronometro_t;

// Estrutura para armazenar informa��es de um jogador
typedef struct usuarios {
    char nome[100];                // Nome do jogador
    cronometro_t *cronometro;      // Ponteiro para o cron�metro do jogador
    int fase;
    struct usuarios *prox;         // Ponteiro para o pr�ximo jogador na lista
} usuarios_t;

// Prototipagem de fun��es

void carregarFase(int fase);


// Cria o primeiro usu�rio na lista de jogadores.
usuarios_t *primeiro_usuario(char *nome);

// Seta cores;
void setColor(int color);

// Inicia o labirinto como parede

void inicializarLabirinto();

// Cria o caminho do labirinto.

void gerarLabirinto(int x, int y);

void reiniciarMapa();

// Exibe o menu principal do jogo.
void menu(usuarios_t **listausuarios);

// Adiciona um novo jogador � lista de jogadores.
 
void proximo_usuario(usuarios_t *primeiro, char *nome);

// Atualiza o tempo do cron�metro.


void Atualizacronometro(cronometro_t *tempo);

// Controla o movimento do jogador com base na entrada do teclado.

void control(cronometro_t *tempo, usuarios_t *listausuarios);

// Usado para avancar as fases.

void avancarfase(usuarios_t *listausuarios);

// Atualiza a posi��o do jogador no mapa e redesenha o cen�rio.

void draw(int px, int py, cronometro_t *tempo);

// Inicia uma nova partida do jogo.

void iniciar(usuarios_t **listausuarios);


int converterTempo(const char *tempo);


// Organiza a lista de jogadores.

void ordenarPorMenorTempo(usuarios_t **listausuarios);

// Exibe as estat�sticas de todos os jogadores.

void salvarEstatisticas(usuarios_t *listausuarios);


void lerEstatisticas();

void menufinal();

void centralizarTexto(const char *texto);

void exibirTelaFinal(usuarios_t *listausuarios);

//Libera a mem�ria alocada para a lista de jogadores.
void freememoria(usuarios_t **listausuarios);

#endif

