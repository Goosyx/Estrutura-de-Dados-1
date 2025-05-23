#define _POSIX_C_SOURCE 199309L // para usar clock_gettime
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

// declaração da função selection_sort definida em ordenação.c
void selection_sort(int *vet, size_t n, long *comparacoes, long *trocas);

// declaração da função bubble_sort definida em ordenação.c
void bubble_sort(int *vet, size_t n, long *comparacoes, long *trocas);

// declaração da função bubble_sort_otimizado definida em ordenação.c
void bubble_sort_otimizado(int *vet, size_t n, long *comparacoes, long *trocas);

// declaração da função insertion_sort definida em ordenação.c
void insertion_sort(int *vet, size_t n, long *comparacoes, long *trocas);

// declaração da função insertion_sort_otimizado definida em busca.c
void insertion_sort_otimizado(int *vet, size_t n, long *comparacoes, long *trocas);


// função para calcular o tempo
static double calcula_tempo(const struct timespec *inicio, const struct timespec *fim) 
{
    return (fim->tv_sec - inicio->tv_sec) + (fim->tv_nsec - inicio->tv_nsec) / 1e9;
}

// busca sequencial em vetor ordenado
int busca_sequencial(int *vet, size_t n, int alvo, long *comparacoes) 
{
    *comparacoes = 0;

    for (size_t i = 0; i < n; i++) 
    {
        (*comparacoes)++;
        
        if (vet[i] == alvo)
        {
            return (int)i;
        }
    }

    // se não encontrou, retorna -1
    return -1;
}

// busca binária em vetor ordenado
int busca_binaria(int *vet, size_t n, int alvo, long *comparacoes) 
{
    size_t min = 0, max = n;
    *comparacoes = 0;

    while (min < max) 
    {
        size_t mid = min + (max - min) / 2;
        (*comparacoes)++;
        
        if (vet[mid] == alvo)
        {
            return (int)mid;

        } else if (vet[mid] < alvo){ 

            min = mid + 1;

        }else{

            max = mid;
        }
       

    }

    // se não encontrou retorna -1
    return -1;
}

/**
 * Função principal:
 * - Recebe um número alvo a ser buscado fornecido pelo usuário
 * - Lê três arquivos binários com números inteiros (pequeno, médio e grande)
 * - Ordena os números usando selection_sort, bubble_sort, bubble_sort_otimizado, insertion sort e insertion_sort_otimizado
 *    - Calcula o tempo de ordenação de cada algoritmo
 *    - Conta o número de comparações e trocas realizadas de cada algoritmo
 *    - Imprime o tempo de ordenação, número de comparações e trocas de cada algoritmo
 *    - Salva o novo arquivo binário ordenado separado por algoritmo
 * - Realiza buscas sequenciais e binárias nos vetores ordenados com base no número alvo
 *    - Calcula o tempo de busca de cada algoritmo
 *    - Conta o número de comparações realizadas de cada algoritmo
 *    - Imprime o tempo de busca e número de comparações de cada algoritmo
 *    - Imprime a posição do número alvo encontrado
 *    - Se não encontrado, imprime -1
 */

int main() 
{
    const char *entradas[3] = {"dados/pequeno.bin", "dados/medio.bin", "dados/grande.bin"};

    // número de arquivos a serem processados por ordenação (utilizado para testes)
    // 1 = processa apenas o arquivo pequeno, 2 = processa o pequeno e o médio, 3 = processa os três arquivos
    int executar = 3;
    int alvo; // variável para armazenar o valor alvo a ser buscado
    printf("Digite o valor alvo para busca: ");
    if (scanf("%d", &alvo) != 1) 
    {
        fprintf(stderr, "Valor inválido.\n");
        return EXIT_FAILURE;
    }

    // selection sort
    for (int i = 0; i < executar; i++) 
    {
        const char *saidas[3] = {"dados/pequeno_ordenado_selection.bin", "dados/medio_ordenado_selection.bin", "dados/grande_ordenado_selection.bin"};
        const char *arquivo = entradas[i];
        const char *arquivo_saida = saidas[i];

        // abre e determina tamanho
        FILE *file = fopen(arquivo, "rb");
        if (!file) 
        { 
            perror(arquivo); 
            continue; 
        }
        fseek(file, 0, SEEK_END);
        long bytes = ftell(file);
        size_t n   = bytes / sizeof(int);
        rewind(file);

        // aloca e lê
        int *vet = malloc(n * sizeof(int));
        if (!vet) 
        { 
            perror("malloc"); 
            fclose(file); 
            continue; 
        }

        // lê o vetor
        if (fread(vet, sizeof(int), n, file) != n) 
        {
            perror("fread"); 
            free(vet); 
            fclose(file); 
            continue;
        }

        fclose(file);

        // ordena e mede o tempo
        struct timespec inicio, fim;
        long comparacoes, trocas;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        selection_sort(vet, n, &comparacoes, &trocas);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        double tempo_ord = calcula_tempo(&inicio, &fim);

        // grava o vetor ordenado
        FILE *out = fopen(arquivo_saida, "wb");
        if (!out) 
        { 
            perror(arquivo_saida);
            free(vet); 
            continue; 
        }
        fwrite(vet, sizeof(int), n, out);
        fclose(out);

        // relatório de ordenação
        printf("\nArquivo: %s\nTamanho da entrada(n) = %zu\n", arquivo, n); // zu = ler ou escrever valores do tipo size_t
        printf("Selection_sort  -> tempo: %.3fs | Comparacoes feitas: %ld | Trocas realizadas: %ld\n",tempo_ord, comparacoes, trocas);

        // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_seq; // contador de comparações
        int pos_seq = busca_sequencial(vet, n, alvo, &comp_seq); // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_seq = calcula_tempo(&inicio, &fim); // calcula tempo

        // busca binária
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_bin; // contador de comparações
        int pos_bin = busca_binaria(vet, n, alvo, &comp_bin); // busca binária
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_bin = calcula_tempo(&inicio, &fim); // calcula tempo

        // relatório de buscas
        printf("Busca Sequencial  -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_seq, tempo_seq, comp_seq);
        printf("Busca Binária     -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_bin, tempo_bin, comp_bin);

        free(vet);
    }

    // bubble sort
    for (int i = 0; i < executar; i++) 
    {
        const char *saidas[3] = {"dados/pequeno_ordenado_bubble.bin", "dados/medio_ordenado_bubble.bin", "dados/grande_ordenado_bubble.bin"};
        const char *arquivo = entradas[i];
        const char *arquivo_saida = saidas[i];

        // abre e determina tamanho
        FILE *file = fopen(arquivo, "rb");
        if (!file) 
        { 
            perror(arquivo); 
            continue; 
        }
        fseek(file, 0, SEEK_END);
        long bytes = ftell(file);
        size_t n   = bytes / sizeof(int);
        rewind(file);

        // aloca e lê
        int *vet = malloc(n * sizeof(int));
        if (!vet) 
        { 
            perror("malloc"); 
            fclose(file); 
            continue; 
        }

        // lê o vetor
        if (fread(vet, sizeof(int), n, file) != n) 
        {
            perror("fread"); 
            free(vet); 
            fclose(file); 
            continue;
        }

        fclose(file);

        // ordena e mede o tempo
        struct timespec inicio, fim;
        long comparacoes, trocas;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        bubble_sort(vet, n, &comparacoes, &trocas);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        double tempo_ord = calcula_tempo(&inicio, &fim);

        // grava o vetor ordenado
        FILE *out = fopen(arquivo_saida, "wb");
        if (!out) 
        { 
            perror(arquivo_saida);
            free(vet); 
            continue; 
        }
        fwrite(vet, sizeof(int), n, out);
        fclose(out);

        // relatório de ordenação
        printf("\nArquivo: %s\nTamanho da entrada(n) = %zu\n", arquivo, n); // zu = ler ou escrever valores do tipo size_t
        printf("Bubble_sort  -> tempo: %.3fs | Comparacoes feitas: %ld | Trocas realizadas: %ld\n",tempo_ord, comparacoes, trocas);

        // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_seq; // contador de comparações
        int pos_seq = busca_sequencial(vet, n, alvo, &comp_seq); // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_seq = calcula_tempo(&inicio, &fim); // calcula tempo

        // busca binária
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_bin; // contador de comparações
        int pos_bin = busca_binaria(vet, n, alvo, &comp_bin); // busca binária
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_bin = calcula_tempo(&inicio, &fim); // calcula tempo

        // relatório de buscas
        printf("Busca Sequencial  -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_seq, tempo_seq, comp_seq);
        printf("Busca Binária     -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_bin, tempo_bin, comp_bin);

        free(vet);
    }

    // bubble sort otimizado
    for (int i = 0; i < executar; i++) 
    {
        const char *saidas[3] = {
            "dados/pequeno_ordenado_bubbleOtimizado.bin",
            "dados/medio_ordenado_bubbleOtimizado.bin",
            "dados/grande_ordenado_bubbleOtimizado.bin"
        };
        const char *arquivo = entradas[i];
        const char *arquivo_saida = saidas[i];

        // abre e determina tamanho
        FILE *file = fopen(arquivo, "rb");
        if (!file) 
        { 
            perror(arquivo); 
            continue; 
        }
        fseek(file, 0, SEEK_END);
        long bytes = ftell(file);
        size_t n   = bytes / sizeof(int);
        rewind(file);

        // aloca e lê
        int *vet = malloc(n * sizeof(int));
        if (!vet) 
        { 
            perror("malloc"); 
            fclose(file); 
            continue; 
        }

        // lê o vetor
        if (fread(vet, sizeof(int), n, file) != n) 
        {
            perror("fread"); 
            free(vet); 
            fclose(file); 
            continue;
        }

        fclose(file);

        // ordena e mede o tempo
        struct timespec inicio, fim;
        long comparacoes, trocas;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        bubble_sort_otimizado(vet, n, &comparacoes, &trocas);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        double tempo_ord = calcula_tempo(&inicio, &fim);

        // grava o vetor ordenado
        FILE *out = fopen(arquivo_saida, "wb");
        if (!out) 
        { 
            perror(arquivo_saida);
            free(vet); 
            continue; 
        }
        fwrite(vet, sizeof(int), n, out);
        fclose(out);

        // relatório de ordenação
        printf("\nArquivo: %s\nTamanho da entrada(n) = %zu\n", arquivo, n); // zu = ler ou escrever valores do tipo size_t
        printf("Bubble_sort_otimizado  -> tempo: %.3fs | Comparacoes feitas: %ld | Trocas realizadas: %ld\n",tempo_ord, comparacoes, trocas);

        // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_seq; // contador de comparações
        int pos_seq = busca_sequencial(vet, n, alvo, &comp_seq); // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_seq = calcula_tempo(&inicio, &fim); // calcula tempo

        // busca binária
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_bin; // contador de comparações
        int pos_bin = busca_binaria(vet, n, alvo, &comp_bin); // busca binária
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_bin = calcula_tempo(&inicio, &fim); // calcula tempo

        // relatório de buscas
        printf("Busca Sequencial  -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_seq, tempo_seq, comp_seq);
        printf("Busca Binária     -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_bin, tempo_bin, comp_bin);

        free(vet);
    }

    // insertion sort
    for (int i = 0; i < executar; i++) 
    {
        const char *saidas[3] = {
            "dados/pequeno_ordenado_insertion.bin",
            "dados/medio_ordenado_insertion.bin",
            "dados/grande_ordenado_insertion.bin"
        };
        const char *arquivo = entradas[i];
        const char *arquivo_saida = saidas[i];

        // abre e determina tamanho
        FILE *file = fopen(arquivo, "rb");
        if (!file) 
        { 
            perror(arquivo); 
            continue; 
        }
        fseek(file, 0, SEEK_END);
        long bytes = ftell(file);
        size_t n   = bytes / sizeof(int);
        rewind(file);

        // aloca e lê
        int *vet = malloc(n * sizeof(int));
        if (!vet) 
        { 
            perror("malloc"); 
            fclose(file); 
            continue; 
        }

        // lê o vetor
        if (fread(vet, sizeof(int), n, file) != n) 
        {
            perror("fread"); 
            free(vet); 
            fclose(file); 
            continue;
        }

        fclose(file);

        // ordena e mede o tempo
        struct timespec inicio, fim;
        long comparacoes, trocas;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        insertion_sort(vet, n, &comparacoes, &trocas);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        double tempo_ord = calcula_tempo(&inicio, &fim);

        // grava o vetor ordenado
        FILE *out = fopen(arquivo_saida, "wb");
        if (!out) 
        { 
            perror(arquivo_saida);
            free(vet); 
            continue; 
        }
        fwrite(vet, sizeof(int), n, out);
        fclose(out);

        // relatório de ordenação
        printf("\nArquivo: %s\nTamanho da entrada(n) = %zu\n", arquivo, n); // zu = ler ou escrever valores do tipo size_t
        printf("Insertion_sort  -> tempo: %.3fs | Comparacoes feitas: %ld | Trocas realizadas: %ld\n",tempo_ord, comparacoes, trocas);

        // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_seq; // contador de comparações
        int pos_seq = busca_sequencial(vet, n, alvo, &comp_seq); // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_seq = calcula_tempo(&inicio, &fim); // calcula tempo

        // busca binária
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_bin; // contador de comparações
        int pos_bin = busca_binaria(vet, n, alvo, &comp_bin); // busca binária
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_bin = calcula_tempo(&inicio, &fim); // calcula tempo

        // relatório de buscas
        printf("Busca Sequencial  -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_seq, tempo_seq, comp_seq);
        printf("Busca Binária     -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_bin, tempo_bin, comp_bin);

        free(vet);
    }

    // insertion sort otimizado
    for (int i = 0; i < executar; i++) 
    {
        const char *saidas[3] = {
            "dados/pequeno_ordenado_insertionOtimizado.bin",
            "dados/medio_ordenado_insertionOtimizado.bin",
            "dados/grande_ordenado_insertionOtimizado.bin"
        };
        const char *arquivo = entradas[i];
        const char *arquivo_saida = saidas[i];

        // abre e determina tamanho
        FILE *file = fopen(arquivo, "rb");
        if (!file) 
        { 
            perror(arquivo); 
            continue; 
        }
        fseek(file, 0, SEEK_END);
        long bytes = ftell(file);
        size_t n   = bytes / sizeof(int);
        rewind(file);

        // aloca e lê
        int *vet = malloc(n * sizeof(int));
        if (!vet) 
        { 
            perror("malloc"); 
            fclose(file); 
            continue; 
        }

        // lê o vetor
        if (fread(vet, sizeof(int), n, file) != n) 
        {
            perror("fread"); 
            free(vet); 
            fclose(file); 
            continue;
        }

        fclose(file);

        // ordena e mede o tempo
        struct timespec inicio, fim;
        long comparacoes, trocas;
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        insertion_sort_otimizado(vet, n, &comparacoes, &trocas);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        double tempo_ord = calcula_tempo(&inicio, &fim);

        // grava o vetor ordenado
        FILE *out = fopen(arquivo_saida, "wb");
        if (!out) 
        { 
            perror(arquivo_saida);
            free(vet); 
            continue; 
        }
        fwrite(vet, sizeof(int), n, out);
        fclose(out);

        // relatório de ordenação
        printf("\nArquivo: %s\nTamanho da entrada(n) = %zu\n", arquivo, n); // zu = ler ou escrever valores do tipo size_t
        printf("Insertion_sort_otimizado  -> tempo: %.3fs | Comparacoes feitas: %ld | Trocas realizadas: %ld\n",tempo_ord, comparacoes, trocas);

        // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_seq; // contador de comparações
        int pos_seq = busca_sequencial(vet, n, alvo, &comp_seq); // busca sequencial
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_seq = calcula_tempo(&inicio, &fim); // calcula tempo

        // busca binária
        clock_gettime(CLOCK_MONOTONIC, &inicio); // inicia contagem
        long comp_bin; // contador de comparações
        int pos_bin = busca_binaria(vet, n, alvo, &comp_bin); // busca binária
        clock_gettime(CLOCK_MONOTONIC, &fim); // finaliza contagem
        double tempo_bin = calcula_tempo(&inicio, &fim); // calcula tempo

        // relatório de buscas
        printf("Busca Sequencial  -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_seq, tempo_seq, comp_seq);
        printf("Busca Binária     -> posição: %d | tempo: %.6fs | comparações: %ld\n",pos_bin, tempo_bin, comp_bin);

        free(vet);
    }

    

    return EXIT_SUCCESS;
}