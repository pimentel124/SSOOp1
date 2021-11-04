#include "my_lib.h"

size_t my_strlen(const char *str) {
  size_t len = 0;
  int i = 0;
  while (str[i]) { //Mentre no final, itinera
          i++;
          len++;
  }
  return len;
}

int my_strcmp(const char *str1, const char *str2) {
    int i;
    i = 0;
    while (str1[i] == str2[i]){ //Mentre siguin iguals, itineram
        if (str1[i] == '\0'){ //Retorna 0 si dos strings iguals
            return 0;
        }
        i++;
    }
    return str1[i] - str2[i]; //Quan trobi una diferència, retornarà la diferència
}

char *my_strcpy(char *dest, const char *src){ 
    int i;
    i=0;
    while (src[i] != '\0'){ //Mentre no s'arribi al final, itinera i copia char a char
        dest[i] = src [i];
        i++;
    }
    dest[i] = '\0'; //Tancam el string destí
    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n){
    size_t i;
    i=0;
    while (i < n && src[i] != '\0') { //Itineram fins final de src si n>i, o fins quantitat desitjada de caràcters a copiar
        dest[i] = src[i]; //Copiam char a char en dest
        i++;
    }
    while (i < n) { //Si length de src < n, omplim amb 0's
        dest[i] = '\0';
    }
    return dest;
}

char *my_strcat(char *dest, const char *src){
    int x, y;
    x=0;
    while(dest[x] != '\0'){ //Trobam length de dest
        x++;
    }
    y=0;
    while(src[y] != '\0'){ //Amb y, itineram fins a arribar al final de src. A la vegada, al final del string copiam char a char el string src.
        dest[x+y] = src[y];
        y++;
    }
    dest[x+y] = '\0'; //Tancam el string dest
    return dest;
}

char *my_strchr(const char *s, int c){
int i;
i=0;
while(s[i] != c && s[i] != '\0'){ //Mentre char no trobat i no final itinera
    i++;
}
if (s[i] == c) //Si char trobat, retorna el valor de la posició s[i]
        return &s[i];
    else
        return NULL; //Si no trobat, retorna NULL
}