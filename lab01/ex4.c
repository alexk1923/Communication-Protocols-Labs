#include <stdio.h>

typedef struct Packet {
  char payload[100];
  int sum;
  int size;
} Packet;

int main(void) {
  FILE *file_input = fopen("input_test_1.txt", "r");

  int bufferLength = 255;
  char buffer[bufferLength];

  while (fgets(buffer, bufferLength, file_input)) {
    printf("%s", buffer);
  }

  fclose(file_input);
  return 0;
}