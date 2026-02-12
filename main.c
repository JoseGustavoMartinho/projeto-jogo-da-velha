#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANKING_FILE "data/ranking.txt"

char tabuleiro[3][3];

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void initTabuleiro() {
    char c = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tabuleiro[i][j] = c++;
}

void mostrarTabuleiro() {
    clear_screen();
    printf("\n Jogo da Velha\n\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int checarVitoria(char p) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == p && tabuleiro[i][1] == p && tabuleiro[i][2] == p) return 1;
        if (tabuleiro[0][i] == p && tabuleiro[1][i] == p && tabuleiro[2][i] == p) return 1;
    }
    if (tabuleiro[0][0] == p && tabuleiro[1][1] == p && tabuleiro[2][2] == p) return 1;
    if (tabuleiro[0][2] == p && tabuleiro[1][1] == p && tabuleiro[2][0] == p) return 1;
    return 0;
}

int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabuleiro[i][j] >= '1' && tabuleiro[i][j] <= '9') return 0;
    return 1;
}

int read_int(const char *prompt, int *out) {
    char line[128];
    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, "%d", out) != 1) return 0;
    return 1;
}

typedef struct {
    char name[64];
    int wins;
} PlayerRecord;

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

int ensure_data_dir() {
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif
    return 0;
}

void salvarRanking(const char *nome) {
    ensure_data_dir();
    FILE *f = fopen(RANKING_FILE, "a");
    if (!f) return;
    fprintf(f, "%s\n", nome);
    fclose(f);
}

int lerRankingAgregado(PlayerRecord *out, int max_records) {
    FILE *f = fopen(RANKING_FILE, "r");
    if (!f) return 0;

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        int found = -1;
        for (int i = 0; i < count; i++) {
            if (strcmp(out[i].name, line) == 0) {
                found = i;
                break;
            }
        }

        if (found >= 0) {
            out[found].wins++;
        } else if (count < max_records) {
            strncpy(out[count].name, line, 63);
            out[count].name[63] = '\0';
            out[count].wins = 1;
            count++;
        }
    }
    fclose(f);
    return count;
}

int cmp_records(const void* a, const void* b) {
    const PlayerRecord* pa = (const PlayerRecord*)a;
    const PlayerRecord* pb = (const PlayerRecord*)b;
    if (pb->wins != pa->wins) return pb->wins - pa->wins;
    return strcmp(pa->name, pb->name);
}

void mostrarRanking() {
    PlayerRecord players[256];
    int n = lerRankingAgregado(players, 256);

    if (n == 0) {
        printf("\nNenhum ranking salvo ainda.\n");
        return;
    }

    qsort(players, n, sizeof(PlayerRecord), cmp_records);

    printf("\n=== RANKING ===\n");
    printf("%-4s %-30s %s\n", "POS", "NOME", "VITORIAS");
    for (int i = 0; i < n && i < 20; i++)
        printf("%-4d %-30s %d\n", i + 1, players[i].name, players[i].wins);
}

char nomeJogadorX[64];
char nomeJogadorO[64];
int vsComputador = 0;

void jogadaComputador() {
    int linha, coluna;
    printf("\nVez do Computador (O): Pensando...\n");

#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif

    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O');

    tabuleiro[linha][coluna] = 'O';
}

void playGame() {
    char jogador = 'X';

    while (1) {
        mostrarTabuleiro();

        if (vsComputador && jogador == 'O') {
            jogadaComputador();
        } else {
            printf("Jogador %c, escolha uma posicao (1-9): ", jogador);
            int pos;
            if (!read_int("", &pos) || pos < 1 || pos > 9) {
                printf("Entrada invalida. Pressione Enter...");
                getchar();
                continue;
            }

            int r = (pos - 1) / 3;
            int c = (pos - 1) % 3;

            if (tabuleiro[r][c] == 'X' || tabuleiro[r][c] == 'O') {
                printf("Posicao ocupada. Pressione Enter...");
                getchar();
                continue;
            }

            tabuleiro[r][c] = jogador;
        }

        if (checarVitoria(jogador)) {
            mostrarTabuleiro();
            printf("Jogador %c venceu!\n", jogador);

            if (jogador == 'X')
                salvarRanking(nomeJogadorX);
            else
                salvarRanking(vsComputador ? "Computador" : nomeJogadorO);

            break;
        }

        if (isDraw()) {
            mostrarTabuleiro();
            printf("Empate!\n");
            break;
        }

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    printf("Pressione Enter...");
    getchar();
}

void menu() {
    int opcao = 0;
    char line[32];

    do {
        clear_screen();
        printf("===== JOGO DA VELHA =====\n");
        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Creditos\n");
        printf("4. Sair\n");
        printf("Escolha: ");

        if (!fgets(line, sizeof(line), stdin)) break;
        opcao = atoi(line);

        switch (opcao) {
            case 1:
                printf("Deseja jogar contra o computador? (s/n): ");
                char escolha;
                scanf(" %c", &escolha);
                getchar();
                vsComputador = (escolha == 's' || escolha == 'S');

                printf("Digite o nome do Jogador X: ");
                fgets(nomeJogadorX, sizeof(nomeJogadorX), stdin);
                nomeJogadorX[strcspn(nomeJogadorX, "\r\n")] = '\0';

                if (!vsComputador) {
                    printf("Digite o nome do Jogador O: ");
                    fgets(nomeJogadorO, sizeof(nomeJogadorO), stdin);
                    nomeJogadorO[strcspn(nomeJogadorO, "\r\n")] = '\0';
                } else {
                    strcpy(nomeJogadorO, "Computador");
                }

                initTabuleiro();
                playGame();
                break;

            case 2:
                mostrarRanking();
                printf("\nPressione Enter...");
                getchar();
                break;

            case 3:
                printf("\nEquipe:\n - Jose Gustavo Martinho Araujo de Almeida \n - Jose Kennedy Barbosa da Silva Junior\n - Pedro Henrique Oliveira do Nascimento\n - Carlos Eduardo Menezes Cavalcante\n\n");
                printf("Pressione Enter...");
                getchar();
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Pressione Enter...");
                getchar();
        }

    } while (opcao != 4);
}

int main() {
    ensure_data_dir();
    srand(time(NULL));
    menu();
    return 0;
}
