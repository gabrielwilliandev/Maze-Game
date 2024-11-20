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

// Estado inicial do mapa (1 = Parede vertical | 2 = Parede Horizontal)
char mapa[H][W] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 3, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};;
// Reinicia o estado inicial do mapa
void reiniciarMapa()
{
    char novoMapa[H][W] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 3, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};;
        memcpy(mapa, novoMapa, sizeof(mapa)); // Copia o estado inicial para `mapa`
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// Menu principal do jogo
void menu(usuarios_t **listausuarios) {
    int opcao;
    system("color 05"); // Define cor do console]
    SetConsoleTitle("Maze Game | Fase 4");

    do {
        printf("============== MAZE GAME | FASE 4 ==============\n");
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
                lerEstatisticas();
                break;
            case 3:
                avancarfase(*listausuarios);
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

void avancarfase(usuarios_t *listausuarios){
    if (jogoativo == 1) {
    printf("Termine a fase para avancar para a proxima!\n");
    system("pause");
    system("cls");
    return;
} else {
    printf("Avancando para a proxima fase...\n");
    Sleep(1000);
    salvarEstatisticas(listausuarios);
    system("start ..\\Fase_5\\Maze.exe");
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
void control(cronometro_t *tempo, usuarios_t *listausuarios) {
    char resp;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && y > 0 && (mapa[x][y - 1] == 0 || mapa[x][y - 1] == 3)) {
        draw(0, -1, tempo);
        if (mapa[x][y] == 3) {
            printf("Parabens, voce completou o jogo!\n");
            system("pause");
            system("cls");
            jogoativo = 0;
            while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
                printf("Deseja ir para proxima fase? [S/N]: ");
                scanf(" %c", &resp);
                if(resp == 'S' || resp == 's'){
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!\n");
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
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!\n");
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
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
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
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    return;
                }
                else{
                    printf("Opcao invalida!\n");
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
        control(tempo, *listausuarios);
        Sleep(50);
    }
}

int converterTempo(const char *tempo) {
    return atoi(tempo) * 60 + atoi(&tempo[3]);
}

void ordenarPorMenorTempo(usuarios_t **listausuarios) {
    if (*listausuarios == NULL || (*listausuarios)->prox == NULL) {
        return;
    }

    int trocou;
    usuarios_t *atual;
    usuarios_t *anterior = NULL;

    do {
        trocou = 0;
        atual = *listausuarios;

        while (atual->prox != anterior) {
            int tempoAtual = converterTempo(atual->cronometro->tempoformatado);
            int tempoProximo = converterTempo(atual->prox->cronometro->tempoformatado);

            if (tempoAtual > tempoProximo) {
                // Troca as informações do nó
                char nomeTemp[50];
                snprintf(nomeTemp, sizeof(nomeTemp), "%s", atual->nome);

                cronometro_t *tempCronometro = atual->cronometro;

                snprintf(atual->nome, sizeof(atual->nome), "%s", atual->prox->nome);
                atual->cronometro = atual->prox->cronometro;

                snprintf(atual->prox->nome, sizeof(atual->prox->nome), "%s", nomeTemp);
                atual->prox->cronometro = tempCronometro;

                trocou = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocou);
}

// Função para salvar as estatísticas em um arquivo
void salvarEstatisticas(usuarios_t *usuarios) {
    FILE *arquivo = fopen("../Estatistica.txt", "a"); // Abre o arquivo no modo append
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de estatisticas!");
        return;
    }

    usuarios_t *aux = usuarios;
    while (aux != NULL) {
        fprintf(arquivo, "Fase: 4 | Nome: %s, Tempo: %s\n", aux->nome, aux->cronometro->tempoformatado);
        puts("\n");
        aux = aux->prox;
    }

    fclose(arquivo);
    printf("Estatisticas salvas com sucesso!\n");
}

// Função para ler e exibir as estatísticas salvas no arquivo
void lerEstatisticas() {
    FILE *arquivo = fopen("../Estatistica.txt", "r"); // Abre o arquivo no modo leitura
    if (arquivo == NULL) {
        printf("Ainda nao ha estatisticas salvas!\n");
        return;
        system("pause");
        system("cls");
    }

    char linha[100];
    printf("=========== Estatisticas ===========\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha); // Exibe cada linha do arquivo
    }
    printf("====================================\n");

    fclose(arquivo);
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

