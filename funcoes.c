#include <pthread.h>

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char mapa_floresta[N][M];
pthread_mutex_t travas_floresta[N][M];

void inicializar_mapa() {
    srand(time(NULL));
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            mapa_floresta[x][y] = (rand() % 2 == 0) ? SENSOR : LIVRE;
            pthread_mutex_init(&travas_floresta[x][y], NULL);
        }
    }
}

void* monitorar_sensor(void* arg) {
    int linha = ((int*)arg)[0];
    int coluna = ((int*)arg)[1];
    free(arg);

    while (1) {
        pthread_mutex_lock(&travas_floresta[linha][coluna]);
        if (mapa_floresta[linha][coluna] == FOGO) {
            printf("Sensor em (%d, %d) detectou fogo!\n", linha, coluna);
            if (linha == 0 || linha == N-1 || coluna == 0 || coluna == M-1) {
                alerta_central(linha, coluna);
            } else {
                alertar_vizinhos(linha, coluna);
            }
        }
        pthread_mutex_unlock(&travas_floresta[linha][coluna]);
        usleep(100000);
    }
}

void alertar_vizinhos(int linha, int coluna) {
    int movimentos_x[] = {-1, 1, 0, 0};
    int movimentos_y[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int vizinho_x = linha + movimentos_x[i];
        int vizinho_y = coluna + movimentos_y[i];

        if (vizinho_x >= 0 && vizinho_x < N && vizinho_y >= 0 && vizinho_y < M) {
            pthread_mutex_lock(&travas_floresta[vizinho_x][vizinho_y]);
            if (mapa_floresta[vizinho_x][vizinho_y] == SENSOR) {
                mapa_floresta[vizinho_x][vizinho_y] = FOGO;
                printf("Fogo se espalhou para (%d, %d)\n", vizinho_x, vizinho_y);
            }
            pthread_mutex_unlock(&travas_floresta[vizinho_x][vizinho_y]);
        }
    }
}

void alerta_central(int linha, int coluna) {
    printf("Central: Fogo detectado na borda em (%d, %d)\n", linha, coluna);
    controlar_fogo(linha, coluna);
}

void controlar_fogo(int linha, int coluna) {
    pthread_mutex_lock(&travas_floresta[linha][coluna]);
    if (mapa_floresta[linha][coluna] == FOGO) {
        mapa_floresta[linha][coluna] = QUEIMADO;
        printf("Fogo controlado em (%d, %d)\n", linha, coluna);
    }
    pthread_mutex_unlock(&travas_floresta[linha][coluna]);
}

void* iniciar_incendios(void* arg) {
    while (1) {
        sleep(3);

        int linha = rand() % N;
        int coluna = rand() % M;

        pthread_mutex_lock(&travas_floresta[linha][coluna]);
        if (mapa_floresta[linha][coluna] == SENSOR) {
            mapa_floresta[linha][coluna] = FOGO;
            printf("Incêndio iniciado em (%d, %d)\n", linha, coluna);
        }
        pthread_mutex_unlock(&travas_floresta[linha][coluna]);
    }
}

void mostrar_mapa() {
    printf("Estado atual do mapa da floresta:\n");
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            char simbolo;
            switch (mapa_floresta[x][y]) {
                case LIVRE:
                    simbolo = '-';
                break;
                case SENSOR:
                    simbolo = 'T';
                break;
                case FOGO:
                    simbolo = '@';
                break;
                case QUEIMADO:
                    simbolo = '/';
                break;
                default:
                    simbolo = '?';
                break;
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
    printf("\n");
}

