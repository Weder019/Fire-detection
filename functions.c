#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // Para usar sleep()
#include "functions.h"

// A matriz da floresta é declarada globalmente aqui
Celula floresta[N][N];

// Função para inicializar a floresta e os mutexes
void inicializa_floresta() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            floresta[i][j].estado = LIVRE;  // Inicializa todas as células como LIVRE
            floresta[i][j].fogo_tratado = 0;  // Nenhum fogo tratado inicialmente
            pthread_mutex_init(&floresta[i][j].lock, NULL);  // Inicializa o mutex de cada célula
        }
    }
}

// Função para imprimir a matriz da floresta
void imprime_floresta() {
    printf("\nEstado atual da floresta:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", floresta[i][j].estado);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para propagar a notificação de fogo para os vizinhos
void notifica_vizinhos(int x, int y) {
    // Notificar as células vizinhas (cima, baixo, esquerda, direita)
    printf("[Sensor] Fogo detectado na célula (%d, %d). Notificando vizinhos:\n", x, y);

    // Célula de cima
    if (x > 0) {
        pthread_mutex_lock(&floresta[x - 1][y].lock);
        printf("Célula (%d, %d) avisada sobre fogo na célula (%d, %d).\n", x - 1, y, x, y);
        pthread_mutex_unlock(&floresta[x - 1][y].lock);
    }

    // Célula de baixo
    if (x < N - 1) {
        pthread_mutex_lock(&floresta[x + 1][y].lock);
        printf("Célula (%d, %d) avisada sobre fogo na célula (%d, %d).\n", x + 1, y, x, y);
        pthread_mutex_unlock(&floresta[x + 1][y].lock);
    }

    // Célula à esquerda
    if (y > 0) {
        pthread_mutex_lock(&floresta[x][y - 1].lock);
        printf("Célula (%d, %d) avisada sobre fogo na célula (%d, %d).\n", x, y - 1, x, y);
        pthread_mutex_unlock(&floresta[x][y - 1].lock);
    }

    // Célula à direita
    if (y < N - 1) {
        pthread_mutex_lock(&floresta[x][y + 1].lock);
        printf("Célula (%d, %d) avisada sobre fogo na célula (%d, %d).\n", x, y + 1, x, y);
        pthread_mutex_unlock(&floresta[x][y + 1].lock);
    }
}

// Função para gerar incêndios aleatórios a cada 3 segundos
void *gerar_incendios(void *arg) {
    while (1) {
        int x = rand() % N;
        int y = rand() % N;

        pthread_mutex_lock(&floresta[x][y].lock);
        if (floresta[x][y].estado == LIVRE || floresta[x][y].estado == SENSOR) {
            floresta[x][y].estado = FOGO;
            printf("\n[Incêndio] Incêndio iniciado na célula (%d, %d).\n", x, y);
            imprime_floresta();  // Imprime a floresta após cada incêndio
            notifica_vizinhos(x, y);  // Propaga o incêndio para os vizinhos
        }
        pthread_mutex_unlock(&floresta[x][y].lock);

        sleep(3);  // Espera 3 segundos antes de gerar o próximo incêndio
    }
    return NULL;
}

// Função para combater incêndios
void *combater_fogo(void *arg) {
    while (1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                pthread_mutex_lock(&floresta[i][j].lock);
                if (floresta[i][j].estado == FOGO && !floresta[i][j].fogo_tratado) {
                    floresta[i][j].fogo_tratado = 1;
                    printf("[Central] Fogo controlado na célula (%d, %d). Estado alterado para QUEIMADO.\n", i, j);
                    floresta[i][j].estado = QUEIMADO;
                    imprime_floresta();  // Imprime a floresta após controlar o incêndio
                }
                pthread_mutex_unlock(&floresta[i][j].lock);
            }
        }
        sleep(1);  // Combate incêndios a cada segundo
    }
    return NULL;
}

// Função central que gerencia notificações da borda (a ser implementada)
void *central(void *arg) {
    // Placeholder para gerenciamento de eventos nas bordas
    while (1) {
        // Aqui entraria o código que processa as mensagens dos nós da borda
        sleep(1);
    }
    return NULL;
}
