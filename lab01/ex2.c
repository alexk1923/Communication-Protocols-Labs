#include <stdio.h>

typedef struct Packet {
  char payload[100];
  int sum;
  int size;
} Packet;

int main(void) {
  FILE *file_input = fopen("input.txt", "rb");
  Packet p_arr[100];

  int i = 0;
  while (!feof(file_input)) {
    fread(&p_arr[i].payload, sizeof(p_arr[i].payload), 1, file_input);
    fread(&p_arr[i].size, sizeof(int), 1, file_input);
    fread(&p_arr[i].sum, sizeof(int), 1, file_input);
    i++;
  }

  int n = i;
  for (int i = 0; i <= n; i++) {
    printf("%s ", p_arr[i].payload);
    // printf("%d ", p_arr[i].size);
    //  printf("%d ", p_arr[i].sum);
    printf("\n");
  }
  return 0;
}