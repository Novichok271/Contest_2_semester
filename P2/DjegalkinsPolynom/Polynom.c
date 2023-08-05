#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* readFromFile(FILE* fin, int* size)
{
  int t;
  fscanf(fin, "%d", &t);
  char* arr = NULL;
  if (fscanf(fin, "%d ", size) == 1)
  {
    int k = pow(2, *size);
    arr = (char*)malloc((k) * sizeof(char));
    if (arr != NULL)
    {
      char a;
      int i = 0;
      while (fscanf(fin, "%c", &a) == 1 && a != '\n')
      {
        arr[i] = a - 48;
        i++;
      }
    }
  }
  return arr;
}

char* getDjegalkinsPolynom(char* arr, int size, int* count)
{
  int k = pow(2, size);
  char* str = (char*)malloc(k * sizeof(char));
  if (str != NULL)
  {
    char x;
    (*count) = 0;
    for (int i = 0; i < k; i++)
    {
      str[i] = arr[0];
      for (int j = 0; j+i < k; j++)
      {
        arr[j] = (arr[j] + arr[j + 1]) % 2;
      }
      if (str[i] == 1)
        (* count)++;
    }
  }
  free(arr);
  return str;
}

void writeToFile(FILE* fout, char* arr, int size, int count)
{
  fprintf(fout, "2 %d %d\n", size, count);
  int k = pow(2, size);
  for (int i = 0; i < k; i++)
  {
    if (arr[i] == 1)
    {
      for (int j = 0; j < size; j++)
      {
        fprintf(fout, "%d", (i >> (size - j-1))&1);
      }
      fprintf(fout, " 1\n");
    }
  }
}
int main(int argc, char* argv[])
{
  if (argc == 3)
  {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (fin && fout)
    {
      int size;
      char* arr = readFromFile(fin, &size);
      if (arr != NULL)
      {
        int count;
        arr = getDjegalkinsPolynom(arr, size, &count);
        writeToFile(fout, arr, size, count);
      }
      else
      { 
        fprintf(fin, "0");
      }
      fclose(fin);
      fclose(fout);
    }
  }
  return 0;
}