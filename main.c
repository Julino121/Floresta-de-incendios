#include "funcoes.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* iniciar_sensor(void* arg) {
    int* coords = (int*) arg;
    monitorar_sensor(coords);
    free(coords);
    return NULL;
}

int main() {
    pthread_t threads_sensores[N][M];
    pthread_t thread_incendios;

    inicializar_mapa();

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            int* coordenadas = malloc(2 * sizeof(int));
            coordenadas[0] = x;
            coordenadas[1] = y;
            pthread_create(&threads_sensores[x][y], NULL, iniciar_sensor, coordenadas);
        }
    }


    pthread_create(&thread_incendios, NULL, iniciar_incendios, NULL);


    while (1) {
        sleep(5);
        mostrar_mapa();
    }


    pthread_join(thread_incendios, NULL);
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            pthread_join(threads_sensores[x][y], NULL);
        }
    }

    return 0;
}
