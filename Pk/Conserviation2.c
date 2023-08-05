#include <stdio.h>
#include <stdlib.h>

int** readFromFile(const char* fileName, int* k, int*n, int* m)
{
    int** polynom = NULL;
    FILE* in = fopen(fileName, "r");
    if(fscanf(in , "%d %d %d\n", k, n, m) == 3)
    {
        int _k = *k;
        int _n = *n;
        int _m = *m;
        polynom = (int**)malloc(sizeof(int*) * _m);
        for(int i = 0; i != _m; ++i)
        {
            polynom[i] = (int*)malloc(sizeof(int) * (_n + 1));
        }   

        char sym;
        for(int i = 0; i != _m; ++i)
        {
            for(int j = 0; j != _n + 2; ++j)
            {
                if(fscanf(in, "%c", &sym) == 1 && sym != ' ' && sym != '\n' && sym != '\r')
                {
                    polynom[i][j] = sym - '0';
                }
                if (sym == ' ' || sym == '\r')
                {
                    --j;
                }
            }
        }
    }
    fclose(in);
    return polynom;
}

int isSavedSet(int* set, int** polynom, int k, int n, int m)
{
    int sum = 0;
    int product;
    for(int i = 0; i != m; ++i)
    {
        product = 1;
        for(int j = 0; j != n; ++j)
        {
            if(polynom[i][j])
            {
                product *= (polynom[i][j] * set[j]);
            }
        }
        sum += polynom[i][n] * product;
    }    
    sum %= k;
    if(sum == set[0])
    {
        return 1;
    }
    return 0;
}

int* getSavadSets(int** polynom, int k, int n, int m)
{
    int* savedSets = (int*)malloc(sizeof(int) * k);
    int** chekedSets = (int**)malloc(sizeof(int*) * k);
    for(int i = 0; i != k; ++i)
    {
        chekedSets[i] = (int*)malloc(sizeof(int) * n);
        for(int j = 0; j != n; ++j)
        {
            chekedSets[i][j] = i;
        }
    }

    for(int i = 0; i != k; ++i)
    {
        savedSets[i] = -1;
        if(isSavedSet(chekedSets[i], polynom, k, n, m) == 1)
        {
            savedSets[i] = i;
        }
    }
    for(int i = 0; i != k; ++i)
    {
        free(chekedSets[i]);
    }
    free(chekedSets);
    chekedSets = NULL;
    return savedSets;
}

void writeToFile(const char* fileName, int* savedSets, int k)
{
    FILE* out = fopen(fileName, "w");
    for(int i = 0; i != k; ++i)
    {
        if(savedSets[i] != -1)
        {
            fprintf(out, "%d\n", savedSets[i]);
        }
    }
    fclose(out);
    free(savedSets);
    savedSets = NULL;
}

int main()
{
    int k, n, m;
    int** polynom = readFromFile("input.txt", &k, &n, &m);
    int* savedSet = getSavadSets(polynom, k , n, m);
    writeToFile("output.txt", savedSet, k);
    for(int i = 0; i != m ; ++i)
    {
        free(polynom[i]);
    }
    free(polynom);
    polynom = NULL;
    return 0;
}

