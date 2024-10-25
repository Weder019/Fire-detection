#include <pthread.h>
#include "functions.h"

int main() {
    // Inicializa a floresta
    inicializa_floresta();

    // Cria as threads
    pthread_t thread_incendios, thread_combate, thread_central;

    // Thread para gerar incêndios
    pthread_create(&thread_incendios, NULL, gerar_incendios, NULL);

    // Thread para combater incêndios
    pthread_create(&thread_combate, NULL, combater_fogo, NULL);

    // Thread central para gerenciar mensagens
    pthread_create(&thread_central, NULL, central, NULL);

    // Aguarda a execução das threads (programa rodará indefinidamente)
    pthread_join(thread_incendios, NULL);
    pthread_join(thread_combate, NULL);
    pthread_join(thread_central, NULL);

    return 0;
}
