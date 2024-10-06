// functions.h
#ifndef FUNCOES_H
#define FUNCOES_H

#define N 30
#define M 30
#define SENSOR 'S'
#define LIVRE 'L'
#define FOGO 'F'
#define QUEIMADO 'Q'

// Prototipos de função
void inicializar_mapa();
void* monitorar_sensor(void* arg);
void alertar_vizinhos(int linha, int coluna);
void alerta_central(int linha, int coluna);
void controlar_fogo(int linha, int coluna);
void* iniciar_incendios(void* arg);
void mostrar_mapa();

#endif // FUNCTIONS_H