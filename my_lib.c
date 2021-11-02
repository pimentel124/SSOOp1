#include "my_lib.h"

size_t my_strlen(const char *str) {
  size_t len = 0;
  while (*str) { // Check if the content is 0
      len++;
      str++; // Increment the pointer to the next char
  }
  return len;
}

int my_strcmp(const char *str1, const char *str2) {
    int i;

    for (i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return 0;
    return str1[i] - str2[i];
}

char *my_strcpy(char *dest, const char *src){ 
    int i;
    for(i=0; src[i] != '\0'; i++){
        dest[i] = src [i];
    }
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n){
    size_t i;
    for( i = 0; i < n && src[i] != '\0'; i++){
        dest[i] = src[i];
    }
    while (i < n) { 
        dest[i] = '\0';
    }
    return dest;
}

char *my_strcat(char *dest, const char *src){
    int x, y;
    for (x=0; dest[x] != '\0'; x++);
    for (y=0; src[y] != '\0'; y++)
        dest[x+y] = src[y];
    dest[x+y] = '\0';
    return dest;
}

char *my_strchr(const char *s, int c){
int i = 0;
    while (s[i] != c && s[i] != '\0')
        i++;
    if (s[i] == c)
        return &s[i];
    else
        return NULL;
}