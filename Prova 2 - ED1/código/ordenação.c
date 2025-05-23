#include <stddef.h>

/**
 * selection_sort:
 *   vet: vetor de inteiros a ser ordenado
 *   n: tamanho do vetor
 *   comparacoes: ponteiro para contador de comparações
 *   trocas: ponteiro para contador de trocas
 */
void selection_sort(int *vet, size_t n, long *comparacoes, long *trocas) 
{
    *comparacoes = 0;
    *trocas = 0;

    for (size_t i = 0; i + 1 < n; i++) 
    {
        size_t pos = i;

        for (size_t j = i + 1; j < n; j++) 
        {
            (*comparacoes)++;

            if (vet[j] < vet[pos])
            {
                pos = j;
            }
        }

        if (pos != i) 
        {
            int tmp = vet[i];
            vet[i] = vet[pos];
            vet[pos] = tmp;
            (*trocas)++;
        }
    }
}

/**
 * bubble_sort:
 *  vet: vetor de inteiros a ser ordenado
 *  n: tamanho do vetor
 *  comparacoes: ponteiro para contador de comparações 
 *  trocas: ponteiro para contador de trocas
 */
void bubble_sort(int *vet, size_t n, long *comparacoes, long *trocas) 
{
    *comparacoes = 0;
    *trocas = 0;

    for (size_t i = 0; i < n - 1; i++) 
    {
        for (size_t j = 0; j < n - i - 1; j++) 
        {
            (*comparacoes)++;

            if (vet[j] > vet[j + 1]) 
            {
                int tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
                (*trocas)++;
            }
        }
    }
}

/**
 * bubble_sort_otimizado:
 *  vet: vetor de inteiros a ser ordenado
 *  n: tamanho do vetor
 *  comparacoes: ponteiro para contador de comparações 
 *  trocas: ponteiro para contador de trocas 
 *  trocou: variavel para verificar se houve troca 
 */
void bubble_sort_otimizado(int *vet, size_t n, long *comparacoes, long *trocas) 
{
    *comparacoes = 0;
    *trocas = 0;

    int trocou;
    for (size_t i = 0; i < n - 1; i++) 
    {
        trocou = 0;

        for (size_t j = 0; j < n - i - 1; j++) 
        {
            (*comparacoes)++;

            if (vet[j] > vet[j + 1]) 
            {
                int tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
                (*trocas)++;
                trocou = 1;
            }
        }

        if (!trocou) 
        {
            break;
        }
    }
}

/**
 * insertion_sort:
 *  vet: vetor de inteiros a ser ordenado
 *  n: tamanho do vetor
 *  comparacoes: ponteiro para contador de comparações 
 *  trocas: ponteiro para contador de trocas
 *  chave: variavel para armazenar o valor a ser inserido
 */
void insertion_sort(int *vet, size_t n, long *comparacoes, long *trocas) 
{
    *comparacoes = 0;
    *trocas = 0;

    for (size_t i = 1; i < n; i++) 
    {
        int chave = vet[i];
        size_t j = i - 1;

        while (j < n && vet[j] > chave) 
        {
            (*comparacoes)++;
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j + 1] = chave;
        (*trocas)++;
    }
}

/**
 * insertion_sort_otimizado:
 *  vet: vetor de inteiros a ser ordenado
 *  n: tamanho do vetor
 *  comparacoes: ponteiro para contador de comparações 
 *  trocas: ponteiro para contador de trocas
 *  chave: variável para armazenar o valor a ser inserido
 *  j != i - 1 : condição para verificar se houve troca
 */
void insertion_sort_otimizado(int *vet, size_t n, long *comparacoes, long *trocas) 
{
    *comparacoes = 0;
    *trocas = 0;

    for (size_t i = 1; i < n; i++) 
    {
        int chave = vet[i];
        size_t j = i - 1;

        while (j < n && vet[j] > chave) 
        {
            (*comparacoes)++;
            vet[j + 1] = vet[j];
            j--;
        }

        if (j != i - 1) 
        {
            vet[j + 1] = chave;
            (*trocas)++;
        }
    }
}
