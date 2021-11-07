#include "my_lib.h"

size_t my_strlen(const char *str) { //String a comparar
  size_t len = 0;
  int i = 0;
  while (str[i]) { //Mentre no final, itinera
          i++;
          len++;
  }
  return len; //Retorna length
}

int my_strcmp(const char *str1, const char *str2) { //String1 i string 2 a comparar
    int i;
    i = 0;
    while (str1[i] == str2[i]){ //Mentre siguin iguals, itineram
        if (str1[i] == '\0'){ //Retorna 0 si dos strings iguals
            return 0;
        }
        i++;
    }
    return str1[i] - str2[i]; //Retorna diferència, str1 major si >0, i str2 major si <0
}

char *my_strcpy(char *dest, const char *src){  //dest string on copiarem chars de src
    int i;
    i=0;
    while (src[i] != '\0'){ //Mentre no s'arribi al final, itinera i copia char a char
        dest[i] = src [i];
        i++;
    }
    dest[i] = '\0'; //Tancam el string destí
    return dest; //Retorna el string ja copiat
}

char *my_strncpy(char *dest, const char *src, size_t n){ /*Strings per realitzar la còpia de chars*/
                                                         /*N enter amb el nombre de chars a copiar*/
    size_t i;
    i=0;
    while (i < n && src[i] != '\0') { /*Itineram fins final de src si n>i,*/
                                      /* o fins quantitat desitjada de caràcters a copiar*/
        dest[i] = src[i]; //Copiam char a char en dest
        i++;
    }
    while (i < n) { //Si length de src < n, omplim amb 0's
        dest[i] = '\0';
    }
    return dest; //Retorna el string ja copiat
}

char *my_strcat(char *dest, const char *src){ //dest string on copiarem chars de src
    int x, y;
    x=0;
    while(dest[x] != '\0'){ //Trobam length de dest
        x++;
    }
    y=0;
    while(src[y] != '\0'){ /*Amb y, itineram fins a arribar al final de src.*/
                           /*A la vegada, al final del string copiam char a char el string src.*/
        dest[x+y] = src[y];
        y++;
    }
    dest[x+y] = '\0'; //Tancam el string dest
    return dest; //Retorna el string ja copiat
}

char *my_strchr(const char *s, int c){ //String on buscar i c char a buscar
int i;
i=0;
while(s[i] != c && s[i] != '\0'){ //Mentre char no trobat i no final itinera
    i++;
}
if (s[i] == c) //Si char trobat, retorna el valor de la posició s[i]
        return (char*)&s[i]; 
    else
        return NULL; //Si no trobat, retorna NULL
}

struct my_stack *my_stack_init (int size){ //Tamany de les dades
    struct my_stack *stack = malloc(sizeof(struct my_stack)); //Cream i reservam espai per la pila
    stack -> top = NULL; //El node superior de la pila s'inicialitza com a NULL
    stack -> size = size; //Establim el tamany de les dades
    return stack; //Retorna punter a la pila inicialitzada
}

int my_stack_push (struct my_stack *stack, void *data){ //Punter al nou node amb data
    struct my_stack_node *nodeToAdd; //Inicialitzam el nou node a afegir
    nodeToAdd = malloc(sizeof(struct my_stack_node)); //Reservam la memória necessaria

    if(stack == NULL && sizeof(data)> 0){ /*Comprobam que la pila existeixi i*/
                                          /* Que el tamany de les dades no sigui 0*/
        printf("Hi ha un error amb el tamany de les dades o No existeix la pila.\n");
        return -1; //Incorrecte retorna -1
    } 
    else {
        nodeToAdd -> data = data; //Establim la data al camp data del node
        if(stack -> top == NULL) { //si no existeix un node superior, afegim el nou node com aquest.
            nodeToAdd -> next = NULL;
            stack -> top = nodeToAdd;

        }
        else { //En cas contrari, afegim el nou node a la següent posoció de la pila
            nodeToAdd -> next = stack -> top;
            stack -> top = nodeToAdd;  
        }
    }
    return 0; //Correcte retorna 0
}

void *my_stack_pop (struct my_stack *stack){ //Ens arriba el punter als nodes
    if(stack -> top == NULL) { //Comprobam que hi hagi qualque node per eliminar
        return NULL;
    }
    struct my_stack_node *deleteNode = stack -> top; //Apuntam al node superior de la pila
    void *data = deleteNode -> data;
    stack -> top = deleteNode -> next; //Feim que el node superior ara sugui el següent node de la pila
    free(deleteNode); //Lliberam l'espai del anterior node superior

    return data; //Retorna punter a les dades de l'element eliminat
}

int my_stack_len (struct my_stack *stack){  //Ens arriba el punter als nodes
    int numNodes = 0; 
    struct my_stack_node *currentNode = stack -> top; //Apuntam al node superior de la pila
    while(currentNode != NULL) { //Mentres que el node al que apuntam no sigui null
        numNodes++; //Aumentam el contador de nodes
        currentNode = currentNode ->next; //Apuntam al següent node de la pila
    }
    return numNodes; //Retorna nombre de nodes
}

int my_stack_purge (struct my_stack *stack){ //Ens arriba punter als nodes
    int numNodes = my_stack_len(stack); /*Feim us del métode my_stack_len() per*/ 
                                        /*Obtenir el nombre de nodes de la pila*/
    int numBytes = 0; //Inicialitzam el nombre de bytes lliberats a 0
    struct my_stack_node *currentNode = stack -> top; //Apuntam al node superior de la pila
    while(currentNode != NULL) { //Mentre el node no sigui null
        my_stack_pop(stack); //Eliminam el node
        currentNode = currentNode ->next; //Passam al següent
    }
    numBytes = numNodes*(sizeof(struct my_stack_node)+stack -> size) + sizeof (struct my_stack); 
    //Calculam el nombre de bytes eliminats
    free(stack); //Alliberam memória
    return numBytes; //Retorna nombre de bytes
}

void recursWrite(struct my_stack_node *nodo, ssize_t file, int size_data) { 
    /*Arriba node, arxiu i tamany de data*/
    /*Mètode que escriu de manera recursiva en la pila*/
    if(nodo ->next != NULL){ //Mentre hi hagi un següent node que escriure
        recursWrite(nodo -> next,file,size_data); //Tornam a cridar al métode
    } 
    ssize_t wrt = write(file, nodo -> data, size_data); // Escribim a l'arxiu el node amb les dades
    if(wrt == -1){//En cas de que no s'hagi pogut escriure, write() retorna -1
        printf("Error d'escriptura\n"); //Hi ha hagut un error
        return;
    }
    
}

int my_stack_write(struct my_stack *stack, char *filename) {
    /*Ens arriben les dades a emmagatzemar a l'arxiu*/
    struct my_stack_node *thisNode = stack -> top; //Apuntam al node superior de la pila
    ssize_t file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
    //Obrim y cream l'arxiu a escriure
    int size_data = stack -> size; 
    if(file == -1) { //En cas de que no s'hagi pogut obrir o crear l'arxiu, open() retorna -1
        return -1; //Retorna -1 en cas d'error
    }
    ssize_t wrt = write(file, &stack -> size, sizeof(size_data));
    if(wrt == -1){
        return -1; //Retorna -1 en cas d'error
    }
    
    recursWrite(thisNode,file,size_data); //Cridam a el metode d'escriptura recursiva
    close(file); //Tancam l'arxiu

    return my_stack_len(stack); //Retorna el nombre d'elements emmagatzemats
}

struct my_stack *my_stack_read(char *filename) { //Nom de l'arxiu
    int file = open(filename, O_RDONLY, S_IRUSR); //Obrim l'arxiu a llegir
    if(file == -1) { //En cas de que no s'hagi pogut obrir l'arxiu, open retorna -1
        return NULL;
    }
    char *buffer = malloc(sizeof(int)); 
    ssize_t readBytes;
    readBytes = read(file, buffer, sizeof(int));
    if(readBytes == -1) {
        return NULL;
    }
    int size_data = 0;
    size_data = (int) *buffer;
    struct my_stack *stack; 
    stack = malloc(sizeof(struct my_stack));
    stack = my_stack_init(size_data);
    buffer = realloc(buffer, stack -> size);
    if(buffer == NULL){
        return NULL;
    }
    else{
        ssize_t rd = read(file, buffer, stack -> size);
        while(rd > 0) {
            int push = my_stack_push(stack,buffer);
            if(push == -1){
                printf("Push error.\n");
                return NULL;
            }
            buffer = malloc(stack -> size);
            rd = read(file, buffer, stack -> size);
        }
    close(file);
    return stack;
    }
}