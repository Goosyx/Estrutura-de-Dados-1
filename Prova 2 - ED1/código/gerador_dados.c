#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/**
 * Gera três arquivos binários com números aleatórios:
 * - dados/pequeno.bin 20.000 elementos
 * - dados/medio.bin   100.000 elementos
 * - dados/grande.bin  265.000 elementos
 */
int main() 
{
    const long tamanhos[3] = {20000, 100000, 265000};
    const char *nomes[3]  = {"dados/pequeno.bin", "dados/medio.bin", "dados/grande.bin"};

    for (int i = 0; i < 3; i++) 
    {
        long n = tamanhos[i];
        const char *path = nomes[i];

        FILE *file = fopen(path, "wb");
        if (!file) 
        {
            perror(path);
            continue;
        }

        for (long j = 0; j < n; j++) 
        {
            int num = rand() % INT_MAX;  // gera número aleatório entre 0 e o maior inteiro
            if (fwrite(&num, sizeof(int), 1, file) != 1) 
            {
                perror("Erro ao escrever no arquivo");
                fclose(file);
                break;
            }
        }

        fclose(file);
        printf("Gerado: %s com %ld inteiros\n", path, n);
    }

    printf("\n");
    return EXIT_SUCCESS;
}
