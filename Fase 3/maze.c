#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "maze.h"

#define H 17 // Altura do mapa
#define W 30 // Largura do mapa

int jogoativo = 1; // Controla se o jogo está ativo ou não
int x = 1, y = 1;  // Coordenadas iniciais do jogador (obs: necessário alterar na função "iniciar()" também.

// Estado inicial do mapa (1 = Parede vertical | 3 = Objetivo)
char mapa[H][W] = { 
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};;

// Reinicia o estado inicial do mapa
void reiniciarMapa() {
    char novoMapa[H][W] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};;
    memcpy(mapa, novoMapa, sizeof(mapa)); // Copia o estado inicial para `mapa`
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// Menu principal do jogo
void menu(usuarios_t **listausuarios) {
    int opcao;
    system("color 05"); // Define cor do console

    do {
        printf("============== MAZE GAME ==============\n");
        printf("1 - Iniciar fase\n");
        printf("2 - Estatisticas\n");
        printf("3 - Ir para proxima fase\n");
        printf("4 - Sair\n");
        printf("\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                system("cls");
                printf("Carregando jogo!");
                Sleep(1000);
                system("cls");
                iniciar(listausuarios);
                break;
            case 2:
                system("cls");
                printf("Carregando estatisticas!");
                Sleep(1000);
                system("cls");
                estatisticas(*listausuarios);
                break;
            case 3:
                avancarfase();
                break;
            case 4:
                printf("Saindo do jogo...\n");
                freememoria(listausuarios);
                Sleep(200);
                return;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 4);
}


// Cria o primeiro usu�rio na lista de jogadores
usuarios_t *primeiro_usuario(char *nome) {
    usuarios_t *usuario1 = malloc(sizeof(usuarios_t));
    if (usuario1 == NULL) {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    strncpy(usuario1->nome, nome, sizeof(usuario1->nome) - 1);
    usuario1->nome[sizeof(usuario1->nome) - 1] = '\0';

    usuario1->cronometro = malloc(sizeof(cronometro_t));
    if (usuario1->cronometro == NULL) {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    usuario1->cronometro->segundos = 0;
    usuario1->cronometro->minutos = 0;
    sprintf(usuario1->cronometro->tempoformatado, "00:00");

    usuario1->prox = NULL;
    return usuario1;
}

// Adiciona um pr�ximo jogador � lista
void proximo_usuario(usuarios_t *primeiro, char *nome) {
    usuarios_t *aux = primeiro;

    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    usuarios_t *usuario = malloc(sizeof(usuarios_t));
    if (usuario == NULL) {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    strncpy(usuario->nome, nome, sizeof(usuario->nome) - 1);
    usuario->nome[sizeof(usuario->nome) - 1] = '\0';

    usuario->cronometro = malloc(sizeof(cronometro_t));
    if (usuario->cronometro == NULL) {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    usuario->cronometro->segundos = 0;
    usuario->cronometro->minutos = 0;
    sprintf(usuario->cronometro->tempoformatado, "00:00");

    usuario->prox = NULL;
    aux->prox = usuario;
}

void avancarfase(){
    if (jogoativo == 1) {
    printf("Termine a fase para avancar para a proxima!\n");
    system("pause");
    system("cls");
    return;
} else {
    printf("Avancando para a proxima fase...\n");
    Sleep(1000);
    system("start mspaint");
    exit(1);
   
}
}


// Atualiza a posi��o do boneco no mapa e redesenha
void draw(int px, int py, cronometro_t *tempo) {
	int i, j;
    mapa[x][y] = 0; // Limpa a posi��o anterior
    x += px;
    y += py;
    if (mapa[x][y] != 3) { // Verifica se a nova posi��o n�o � o objetivo
        mapa[x][y] = 2;    // Atualiza a posi��o do boneco
    }

    system("cls");
    for ( i = 0; i < H; i++) {
        for ( j = 0; j < W; j++) {
            switch (mapa[i][j]) {
                case 0: printf(" "); break;       // Espa�o vazio
                case 1: 
                setColor(05);
                printf("%c", 219); break; // Parede
                case 2: 
                setColor(15);
                printf("%c", 207); break; // Boneco
                setColor(05);
                case 3:
                setColor(15); 
                printf("%c", 254); break; // Objetivo
                setColor(05);
            }
        }
        printf("\n");
    }
    printf("Tempo: %s\n", tempo->tempoformatado);
}

// Atualiza o cron�metro em formato MM:SS
void Atualizacronometro(cronometro_t *tempo) {
    tempo->segundos++;
    if (tempo->segundos == 60) {
        tempo->segundos = 0;
        tempo->minutos++;
    }
    sprintf(tempo->tempoformatado, "%02d:%02d", tempo->minutos, tempo->segundos);
}

// Controla o movimento do jogador
void control(cronometro_t *tempo) {
    char resp;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && y > 0 && (mapa[x][y - 1] == 0 || mapa[x][y - 1] == 3)) {
        draw(0, -1, tempo);
        if (mapa[x][y] == 3) {
            printf("Parabens, voc� completou o jogo!\n");
            system("pause");
            system("cls");
            jogoativo = 0;
            while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
                printf("Deseja ir para proxima fase? [S/N]: ");
                scanf(" %c", &resp);
                if(resp == 'S' || resp == 's'){
                    avancarfase();
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.");
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!");
                }
            }
        }
    } else if (GetAsyncKeyState(VK_UP) & 0x8000 && x > 0 && (mapa[x - 1][y] == 0 || mapa[x - 1][y] == 3)) {
        draw(-1, 0, tempo);
        if (mapa[x][y] == 3) {
            printf("Parabens, voce completou o jogo!\n");
            system("pause");
            system("cls");
            jogoativo = 0;
            while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
                printf("Deseja ir para proxima fase? [S/N]: ");
                scanf(" %c", &resp);
                if(resp == 'S' || resp == 's'){
                    avancarfase();
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.");
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!");
                }
            }
        }
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && y < W - 1 && (mapa[x][y + 1] == 0 || mapa[x][y + 1] == 3)) {
        draw(0, 1, tempo);
        if (mapa[x][y] == 3) {
            printf("Parabens, voce completou o jogo!\n");
            system("pause");
            system("cls");
            jogoativo = 0;
            while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
                printf("Deseja ir para proxima fase? [S/N]: ");
                scanf(" %c", &resp);
                if(resp == 'S' || resp == 's'){
                    avancarfase();
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.");
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!");
                }
            }
        }
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && x < H - 1 && (mapa[x + 1][y] == 0 || mapa[x + 1][y] == 3)) {
        draw(1, 0, tempo);
        if (mapa[x][y] == 3) {
            printf("Parabens, voce completou o jogo!\n");
            system("pause");
            system("cls");
            jogoativo = 0;
            while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
                printf("Deseja ir para proxima fase? [S/N]: ");
                scanf(" %c", &resp);
                if(resp == 'S' || resp == 's'){
                    avancarfase();
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.");
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!");
                }
            }
        }
    } else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        return;
    }
}

// Inicia o jogo
void iniciar(usuarios_t **listausuarios) {
    reiniciarMapa();
    x = 1;
    y = 1;
    jogoativo = 1;

    char nome[100];
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    if (*listausuarios == NULL) {
        *listausuarios = primeiro_usuario(nome);
    } else {
        proximo_usuario(*listausuarios, nome);
    }

    usuarios_t *jogadoratual = *listausuarios;
    while (jogadoratual->prox != NULL) {
        jogadoratual = jogadoratual->prox;
    }

    cronometro_t *tempo = jogadoratual->cronometro;
    draw(0, 0, tempo);

    unsigned long lastUpdate = GetTickCount();
    while (jogoativo) {
        unsigned long now = GetTickCount();
        if (now - lastUpdate >= 1000) {
            Atualizacronometro(tempo);
            lastUpdate = now;
        }
        control(tempo);
        Sleep(50);
    }
}

// Organiza a lista
void ordenarPorMenorTempo(usuarios_t **listausuarios) {
    if (*listausuarios == NULL || (*listausuarios)->prox == NULL) {
        return; // Lista vazia ou com apenas um elemento
    }

    usuarios_t *atual, *prox;
    int trocou;
    do {
        trocou = 0;
        atual = *listausuarios;

        while (atual->prox != NULL) {
            prox = atual->prox;

            // Calcula o tempo total em segundos para comparar
            int tempoAtual = (atual->cronometro->minutos * 60) + atual->cronometro->segundos;
            int tempoProx = (prox->cronometro->minutos * 60) + prox->cronometro->segundos;

            if (tempoAtual > tempoProx) {
                // Troca os dados dos nós
                char nomeTemp[50];
                strcpy(nomeTemp, atual->nome);
                strcpy(atual->nome, prox->nome);
                strcpy(prox->nome, nomeTemp);

                cronometro_t tempCronometro = *(atual->cronometro);
                *(atual->cronometro) = *(prox->cronometro);
                *(prox->cronometro) = tempCronometro;

                trocou = 1;
            }
            atual = atual->prox;
        }
    } while (trocou);
}


// Mostra as estat�sticas de todos os jogadores
void estatisticas(usuarios_t *listausuarios) {
    if (listausuarios == NULL) {
        printf("Nenhum jogador registrado!\n");
        system("pause");
        system("cls");
        return;
    }

    // Ordena a lista antes de mostrar as estatísticas
    ordenarPorMenorTempo(&listausuarios);

    printf("===== Estatísticas dos Jogadores =====\n");
    usuarios_t *aux = listausuarios;

    while (aux != NULL) {
        printf("Nome: %s | Tempo: %s\n", aux->nome, aux->cronometro->tempoformatado);
        aux = aux->prox;
    }

    printf("======================================\n");
    system("pause");
    system("cls");
}

// Libera a mem�ria alocada para os jogadores
void freememoria(usuarios_t **listausuarios) {
    usuarios_t *aux;
    while (*listausuarios != NULL) {
        aux = *listausuarios;
        *listausuarios = (*listausuarios)->prox;
        free(aux->cronometro);
        free(aux);
    }
     *listausuarios = NULL;
}



