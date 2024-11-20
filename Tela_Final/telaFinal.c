#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

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


void menu() {
    int opcao;
    system("color 05"); // Define cor do console

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
                printf("Carregando fase!");
                system("start ..\\Fase_1\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 2:
                system("cls");
                printf("Carregando fase!");
                system("start ..\\Fase_2\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 3:
                system("cls");
                printf("Carregando fase!");
                system("start ..\\Fase_3\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 4:
                system("cls");
                printf("Carregando fase!");
                system("start ..\\Fase_4\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 5:
                system("cls");
                printf("Carregando fase!");
                system("start ..\\Fase_5\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 6:
                system("cls");
                printf("Carregando fase!");
                system("start ..\\Fase_6\\Maze.exe");
                Sleep(1000);
                system("cls");
                exit(1);
                break;
            case 7:
                system("cls");
                printf("Carregando estatisticas!");
                Sleep(1000);
                system("cls");
                lerEstatisticas();
                break;
            case 8:
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


void exibirTelaFinal() {
  
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
}

int main() {

    menu();

    exibirTelaFinal();

       
    return 0;
}
