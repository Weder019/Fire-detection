#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>

#define N 30  // Tamanho da matriz da floresta

// Definindo os estados das células
#define LIVRE '-'
#define SENSOR 'T'
#define FOGO '@'
#define QUEIMADO '/'

// Estrutura para representar cada célula da floresta
typedef struct {
    char estado;  // Pode ser LIVRE, SENSOR, FOGO ou QUEIMADO
    int fogo_tratado;  // Indica se o fogo foi tratado (0 = não, 1 = sim)
    pthread_mutex_t lock;  // Mutex para sincronização entre threads
} Celula;

// Declaração da matriz da floresta
extern Celula floresta[N][N];

// Funções declaradas
void inicializa_floresta();
void imprime_floresta();
void *gerar_incendios(void *arg);
void *combater_fogo(void *arg);
void *central(void *arg);

#endif
