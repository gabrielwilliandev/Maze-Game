#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "maze.h"

#define H 16 // Altura do mapa
#define W 30 // Largura do mapa

// Variáveis globais
int jogoativo = 1;       // Controla se o jogo está ativo ou não
int x = 0, y = 0;        // Coordenadas iniciais do jogador
int faseAtual = 1;       // Fase inicial
char mapa[H][W];         // Representação do mapa

// Função para carregar a fase
void carregarFase(int fase) {
    char arquivo[20];
    if(faseAtual <= 5){

    
    sprintf(arquivo, "Fase_%d.txt", fase);

    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo da fase");
        system("pause");
        exit(EXIT_FAILURE);
    }

    // Ler a posição inicial do jogador
    if (fscanf(file, "%d %d", &x, &y) != 2) {
        fprintf(stderr, "Erro na leitura das coordenadas iniciais!\n");
        system("pause");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Ler o mapa
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int valor;
            if (fscanf(file, "%d", &valor) != 1) {
                fprintf(stderr, "Erro ao ler o mapa!\n");
                system("pause");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            mapa[i][j] = (char)valor;
        }
    }

    fclose(file);
    printf("Fase %d carregada com sucesso!\n", fase);
    }
    else
    {   
        reiniciarMapa();
        printf("Fase %d gerada com sucesso!\n", fase);
    }
}
void inicializarLabirinto() {
    if(faseAtual == 6){
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                mapa[i][j] = 1; 
            }
        }
    }
}

void gerarLabirinto(int x, int y) {
 
    int direcoes[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
    
    if(faseAtual == 6){
        // Embaralha as direções
        for (int i = 0; i < 4; i++) {
            int r = rand() % 4;
            int tempX = direcoes[i][0];
            int tempY = direcoes[i][1];
            direcoes[i][0] = direcoes[r][0];
            direcoes[i][1] = direcoes[r][1];
            direcoes[r][0] = tempX;
            direcoes[r][1] = tempY;
        }

        // Marca a posição atual como caminho
        mapa[x][y] = 0;

        // Percorre as direções
        for (int i = 0; i < 4; i++) {
            int nx = x + direcoes[i][0];
            int ny = y + direcoes[i][1];

            // Verifica se a nova posição é válida e se é uma parede
            if (nx > 0 && nx < H - 1 && ny > 0 && ny < W - 1 && mapa[nx][ny] == 1) {
                // Quebra a parede entre as células
                mapa[x + direcoes[i][0] / 2][y + direcoes[i][1] / 2] = 0;
                // Recursivamente gera o labirinto
                gerarLabirinto(nx, ny);
            }
        }
    }   
}
void reiniciarMapa() {
    if(faseAtual == 6){
        inicializarLabirinto(); // Preenche tudo com paredes
        srand(time(NULL));      // Inicializa o gerador de números aleatórios

        gerarLabirinto(1, 1);   // Gera o labirinto a partir de (1, 1)

        // Define posições aleatórias para o jogador
        do {
            x = rand() % (H - 2) + 1; // Coordenada aleatória para x dentro do mapa
            y = rand() % (W - 2) + 1; // Coordenada aleatória para y dentro do mapa
        } while (mapa[x][y] != 0); // Repetir até encontrar um caminho livre

        mapa[x][y] = 2; // Marca a posição inicial do jogador no mapa

        // Define posição aleatória para o objetivo com distância mínima
        int objetivoX, objetivoY;
        int distancia; // Declara a variável distância
        do {
            objetivoX = rand() % (H - 2) + 1;
            objetivoY = rand() % (W - 2) + 1;


            distancia = abs(objetivoX - x) + abs(objetivoY - y);

        } while (mapa[objetivoX][objetivoY] != 0 || distancia < 20); // Garante distância mínima e célula válida

        mapa[objetivoX][objetivoY] = 3; // Marca o objetivo no mapa
    }
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// Menu principal do jogo
void menu(usuarios_t **listausuarios) {
    int opcao;
    system("color 05"); // Define cor do console
    SetConsoleTitle("Maze Game");

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
                printf("Carregando jogo!\n");
                Sleep(1000);
                system("cls");
                carregarFase(faseAtual);
                iniciar(listausuarios);
                break;
            case 2:
                system("cls");
                printf("Carregando estatisticas!\n");
                Sleep(1000);
                system("cls");
                lerEstatisticas();
                break;
            case 3:
                avancarfase(*listausuarios);
                break;
            case 4:
                printf("Saindo do jogo...\n");
                freememoria(listausuarios); // Libera memória antes de sair
                Sleep(200);
                return;
            default:
                printf("Opcao invalida!\n");
                system("pause");
                system("cls");
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

void avancarfase(usuarios_t *listausuarios) {
    if (faseAtual < 6) {
        faseAtual++;
        printf("Avancando para a fase %d...\n", faseAtual);
        Sleep(1000);

        jogoativo = 1; // Reinicia o loop do jogo
        system("cls");
        menu(&listausuarios);

    } else {
        printf("Parabens! Voce completou todas as fases!\nAvancando para tela final!");
        Sleep(2000);
        system("cls");
        menufinal(listausuarios);
        
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
                    salvarEstatisticas(listausuarios);
                    avancarfase(listausuarios);
                    
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    menu(&listausuarios);
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
                    salvarEstatisticas(listausuarios);
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    menu(&listausuarios);
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
                    salvarEstatisticas(listausuarios);
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    menu(&listausuarios);
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
                    salvarEstatisticas(listausuarios);
                    avancarfase(listausuarios);
                }
                else if (resp == 'N' || resp == 'n'){
                    printf("Retornando ao menu.\n");
                    salvarEstatisticas(listausuarios);
                    Sleep(1000);
                    system("cls");
                    menu(&listausuarios);
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


void salvarEstatisticas(usuarios_t *listausuarios) {
    if (listausuarios == NULL) {
        printf("Nenhum usuario para salvar!\n");
        return;
    }

    // Localizar o último jogador (jogador ativo)
    usuarios_t *jogadorAtivo = listausuarios;
    while (jogadorAtivo->prox != NULL) {
        jogadorAtivo = jogadorAtivo->prox;
    }

    FILE *arquivo = fopen("Estatisticas.bin", "ab"); // Modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar estatisticas!\n");
        return;
    }

    usuarios_t registro;
    strncpy(registro.nome, jogadorAtivo->nome, sizeof(registro.nome));
    registro.nome[sizeof(registro.nome) - 1] = '\0';
    registro.fase = faseAtual; // Salva a fase atual
    registro.cronometro = jogadorAtivo->cronometro;

    // Salvar apenas o jogador ativo
    if (fwrite(&registro, sizeof(usuarios_t), 1, arquivo) != 1) {
        printf("Erro ao salvar estatisticas!\n");
    } else {
        printf("Estatisticas da fase %d do jogador %s salvas com sucesso!\n", faseAtual, registro.nome);
    }

    fclose(arquivo);
}

void lerEstatisticas() {
    FILE *arquivo = fopen("Estatisticas.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhuma estatistica encontrada!\n");
        return;
    }

    usuarios_t usuario;
    printf("=== Estatisticas dos Usuarios ===\n");
    while (fread(&usuario, sizeof(usuarios_t), 1, arquivo) == 1) {
        printf("Fase %d | Nome: %s - Tempo: %s\n", 
               usuario.fase, 
               usuario.nome, 
               usuario.cronometro->tempoformatado);
    }

    fclose(arquivo);
    system("pause");
    system("cls");
}

void menufinal(usuarios_t **listausuarios) {
    int opcao;

    printf("Parabens por complentar o jogo!\nCaso queria jogar alguma fase novamente selecione o numero da fase abaixo: \n\n");
    do {
        printf("============== FASE SELECTOR ==============\n");
        printf("1 - Fase 1\n");
        printf("2 - Fase 2\n");
        printf("3 - Fase 3\n");
        printf("4 - Fase 4\n");
        printf("5 - Fase 5\n");
        printf("6 - Fase 6\n");
        printf("7 - Ler estatisticas finais\n");
        printf("8 - Finalizar\n");
        printf("\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                system("cls");
                faseAtual = 1;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
            case 2:
                system("cls");
                faseAtual = 2;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
            case 3:
                system("cls");
                faseAtual = 3;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
            case 4:
                system("cls");
                faseAtual = 4;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
                break;
            case 5:
                system("cls");
                faseAtual = 5;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
            case 6:
                system("cls");
                faseAtual = 6;
                printf("Carregando fase!");
                Sleep(1000);
                system("cls");
                menu(listausuarios);
                break;
            case 7:
                system("cls");
                printf("Carregando estatisticas!");
                Sleep(1000);
                system("cls");
                lerEstatisticas();
                break;
            case 8:
                system("cls");
                exibirTelaFinal(*listausuarios);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 8);
}

void centralizarTexto(const char *texto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int largura = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Divide o texto em linhas e centraliza cada uma
    char linha[256];
    const char *ptr = texto;
    while (*ptr) {
        int i = 0;
        while (*ptr && *ptr != '\n') {
            linha[i++] = *ptr++;
        }
        linha[i] = '\0';
        if (*ptr == '\n') ptr++;  // Pula o caractere de nova linha

        int comprimentoLinha = strlen(linha);
        int espacos = (largura - comprimentoLinha) / 2;
        for (int j = 0; j < espacos; j++) {
            printf(" ");
        }
        printf("%s\n", linha);
    }
}


void exibirTelaFinal(usuarios_t *listausuarios) {
  
    system("cls");

    
    const char *texto = 
        "\n\n"
        "=========================================\n"
        "      PARABENS, VOCE FINALIZOU O JOGO!  \n"
        "=========================================\n"
        "\n"
        "Criadores do jogo:\n"
        "Ana\n"
        "Gabriel\n"
        "Lavinia\n"
        "Luiz\n"
        "\n"
        "=========================================\n"
        "        Fim de Jogo. Obrigado por jogar! \n"
        "=========================================\n";

    
    centralizarTexto(texto);
    printf("\n\n");
    system("pause");
    freememoria(&listausuarios);
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



