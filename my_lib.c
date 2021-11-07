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
        return (char*)&s[i];
    else
        return NULL; //Si no trobat, retorna NULL
}

struct my_stack *my_stack_init (int size){
    struct my_stack *stack = malloc(sizeof(struct my_stack));
    stack -> top = NULL;
    stack -> size = size;
    return stack;
}

int my_stack_push (struct my_stack *stack, void *data){
    struct my_stack_node *nodeToAdd;
    nodeToAdd = malloc(sizeof(struct my_stack_node));

    if(stack == NULL && sizeof(data)> 0){
        printf("Null Stack or data size error.\n");
        return -1;
    } 
    else {
        nodeToAdd -> data = data;
        if(stack -> top == NULL) {
            nodeToAdd -> next = NULL;
            stack -> top = nodeToAdd;

        }
        else {
            nodeToAdd -> next = stack -> top;
            stack -> top = nodeToAdd;  
        }
    }
    return 0;
}

void *my_stack_pop (struct my_stack *stack){
    if(stack -> top == NULL) {
        return NULL;
    }
    struct my_stack_node *deleteNode = stack -> top;
    void *data = deleteNode -> data;
    stack -> top = deleteNode -> next;
    free(deleteNode);

    return data; 
}

int my_stack_len (struct my_stack *stack){
    int numNodes = 0;
    struct my_stack_node *currentNode = stack -> top;
    while(currentNode != NULL) {
        numNodes++;
        currentNode = currentNode ->next;
    }
    return numNodes;
}

int my_stack_purge (struct my_stack *stack){
    int numNodes = my_stack_len(stack);
    int numBytes = 0;
    struct my_stack_node *currentNode = stack -> top;
    while(currentNode != NULL) {
        my_stack_pop(stack);
        currentNode = currentNode ->next;
    }
    numBytes = numNodes*(sizeof(struct my_stack_node)+stack -> size) + sizeof (struct my_stack);
    free(stack);
    return numBytes;
}

void recursWrite(struct my_stack_node *nodo, ssize_t file, int size_data) {
    if(nodo ->next != NULL){
        recursWrite(nodo -> next,file,size_data);
    } 
    ssize_t wrt = write(file, nodo -> data, size_data);
    if(wrt == -1){
        printf("Error d'escriptura\n");
        return;
    }
    
}

int my_stack_write(struct my_stack *stack, char *filename) {
    struct my_stack_node *thisNode = stack -> top;
    ssize_t file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int size_data = stack -> size;
    if(file == -1) {
        return -1;
    }
    ssize_t wrt = write(file, &stack -> size, sizeof(size_data));
    if(wrt == -1){
        return -1;
    }
    
    recursWrite(thisNode,file,size_data);
    close(file);

    return my_stack_len(stack);
}

struct my_stack *my_stack_read(char *filename) {
    int file = open(filename, O_RDONLY, S_IRUSR);
    if(file == -1) {
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