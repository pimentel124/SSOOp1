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

//https://stackoverflow.com/questions/52927678/c-stack-manager-project-file-i-o-with-syscalls-problems
struct my_stack *my_stack_init (int size){
    struct my_stack *stack = malloc(sizeof(struct my_stack));
    stack -> top = NULL;
    stack -> size = size;
    return stack;
}

int my_stack_push (struct my_stack *stack, void *data){
    struct my_stack_node *newNode = malloc(sizeof(struct my_stack_node));

    if(stack == NULL && sizeof(data)> 0){
        printf("Null Stack or data size error.\n");
        //la pila debe existir
        return -1;
    } 
    else {
        newNode -> data = data;
        if(stack -> top == NULL) {
            newNode -> next = NULL;
            stack -> top = newNode;

        }
        else {
            newNode -> next = stack -> top;
            stack -> top = newNode;  
        }
    }
    return 0;
}

void *my_stack_pop (struct my_stack *stack){
    if(stack -> top == NULL) {
        return NULL;
    }
    struct my_stack_node *nodeToDelete = stack -> top;
    void *data = nodeToDelete -> data;
    stack -> top = nodeToDelete -> next;
    free(nodeToDelete);

    return data; 
}

int my_stack_len (struct my_stack *stack){
    int numNodes = 0;
    struct my_stack_node *currentElement = stack -> top;
    while(currentElement != NULL) {
        numNodes++;
        currentElement = currentElement ->next;
    }
    return numNodes;
}

int my_stack_purge (struct my_stack *stack){
    int numNodes = 0;
    int numBytes = 0;
    struct my_stack_node *currentNode = stack -> top;
    struct my_stack_node *nextNode;
    while(currentNode != NULL) {
        nextNode = currentNode ->next;
        free(currentNode);
        currentNode = nextNode;
        numNodes++;
    }
    numBytes = numNodes*(sizeof(struct my_stack_node)+stack -> size) + sizeof (struct my_stack);
    return numBytes;
}

void recursiveWrite(struct my_stack_node *nodo, int fileDesc, int sizeData) {
    if(nodo ->next != NULL) recursiveWrite(nodo -> next,fileDesc,sizeData);
    if(write(fileDesc, nodo -> data, sizeData)== -1){
        printf("Error de escritura\n");
        return;// error escritura.
    }
}

int my_stack_write(struct my_stack *stack, char *filename) {
    struct my_stack_node *currentNode = stack -> top;
    int fileDesc = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fileDesc == -1) {
        return -1; // Error open();
    }
    if(write(fileDesc, &stack -> size, sizeof(stack -> size)) == -1){
        return -1; // Error write();
    }
    int sizeData = stack -> size;
    recursiveWrite(currentNode,fileDesc,sizeData);
    close(fileDesc);

    return my_stack_len(stack);
}

struct my_stack *my_stack_read(char *filename) {
    int fileDesc = open(filename, O_RDONLY, S_IRUSR);
    if(fileDesc == -1) {
        return NULL; // Error open();
    }
    char *buffer = malloc(sizeof(int));
    ssize_t readBytes;
    readBytes = read(fileDesc, buffer, sizeof(int));
    if(readBytes == -1) {
        return NULL;
    }
    int dataSize = 0;
    dataSize = (int) *buffer; // parse data Size from buffer.
    struct my_stack *stack; 
    stack = malloc(sizeof(struct my_stack));
    stack = my_stack_init(dataSize); // initialize Stack
    buffer = realloc(buffer, stack -> size);
    if(buffer == NULL){
        return NULL;
    }
    else{
        while(read(fileDesc, buffer, stack -> size) > 0) {
            int push = my_stack_push(stack,buffer);
            if(push == -1){
                printf("Error en my_stack_read: Push error.\n");
                return NULL;
            }
            buffer = malloc(stack -> size);
        }
    close(fileDesc);
    return stack;
    }
}   