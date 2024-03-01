#include <stdio.h>
#include <stdint.h>

int main(void) {
  printf("const unsigned long long int %zu\n", sizeof(const unsigned long long int));
  printf("const unsigned long int      %zu\n", sizeof(const unsigned long int));
  printf("const unsigned short int     %zu\n", sizeof(const unsigned short int));
  printf("const unsigned int           %zu\n", sizeof(const unsigned int));
  printf("const unsigned char          %zu\n", sizeof(const unsigned char));
  printf("const signed long long int %zu\n", sizeof(const signed long long int));
  printf("const signed long int      %zu\n", sizeof(const signed long int));
  printf("const signed short int     %zu\n", sizeof(const signed short int));
  printf("const signed int           %zu\n", sizeof(const signed int));
  printf("const signed char          %zu\n", sizeof(const signed char));
  printf("unsigned long long int %zu\n", sizeof(unsigned long long int));
  printf("unsigned long int      %zu\n", sizeof(unsigned long int));
  printf("unsigned short int     %zu\n", sizeof(unsigned short int));
  printf("unsigned int           %zu\n", sizeof(unsigned int));
  printf("unsigned char          %zu\n", sizeof(unsigned char));
  printf("signed long long int %zu\n", sizeof(signed long long int));
  printf("signed long int      %zu\n", sizeof(signed long int));
  printf("signed short int     %zu\n", sizeof(signed short int));
  printf("signed int           %zu\n", sizeof(signed int));
  printf("signed char          %zu\n", sizeof(signed char));
  return 0;
}
