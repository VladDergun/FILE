#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_WIDTH 30 //Max width of one column of the table
#define COL 3

void swap(char* a, char* b);
void removeSpacesAndNewLine(char* str);
void ReadFile(const char* name);
void CreateFile(const char* name);
void DeleteFile(const char* name);
void ReadLine(const char* name, int fline, int lline);
void PasteLine(const char* name, int num);
void DeleteLine(const char* name, int num);  
void SortLines(const char* name);
void ChangeLine(const char* name, int num);
void SortArray(char*** arr, int parameter, int line, int dir);
void swapStrings(char **str1, char **str2);
void Header();

int OpenFile(const char* name);
char*** Write(const char* name, int linecount, char mode);
char*** splitArray(const char* name, const char* delimiter);

int main(){
    FILE* filePointer;
    char name[100];
    char choice[100];

    while(1){
        printf("Would you like to open/create/delete a new file? open/create/delete/exit: ");
        scanf("%s", &choice);
        if(strcmp(choice, "open") == 0){
            printf("Please, enter the name of a file including the format (example.txt): ");
            scanf("%s", &name);
            OpenFile(name);
        }
        else if (strcmp(choice, "create") == 0){
            printf("Please, enter the name of a file including the format (example.txt): ");
            scanf("%s", &name);
            CreateFile(name);
        }
        else if(strcmp(choice, "delete") == 0){
            printf("Please, enter the name of a file including the format (example.txt): ");
            scanf("%s", &name);
            DeleteFile(name);
        } 
        else if(strcmp(choice, "exit") == 0){
            break;
        }
    }
    getchar();
    getchar();
    
    
    return 0;
}
void Header(){
    printf("                     Oblast                           Population                   Square\n");
}

void swap(char* a, char* b){
    char temp[1000];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);

}

void removeSpacesAndNewLine(char* str) {
   int start = 0, end = strlen(str) - 1;

    // Find the index of the first non-whitespace character from the beginning
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r') {
        start++;
    }

    // Find the index of the first non-whitespace character from the end
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) {
        end--;
    }

    // Calculate the length of the non-whitespace portion
    int length = end - start + 1;
    memmove(str, str + start, length);
    str[length] = '\0';

}



void CreateFile(const char* name){
    FILE* filePointer;
    filePointer = fopen(name, "w");
    if(filePointer == NULL){
        printf("Error creating the file.\n");
        
    }
    fclose(filePointer);

}

void DeleteFile(const char* name){
    FILE *filePointer;

    if (remove(name) == 0) {
        printf("File deleted successfully: %s\n", name);
    } else {
        perror("Error deleting the file");
       
    }
 
}

void ReadLine(const char* name, int fline, int lline){
    FILE* filePointer;
    char buffer[100];
    filePointer = fopen(name, "r");
    Header();
    for(int k = fline; k <= lline; k++){
        for(int i = 1; i <= fline; i++){
            if(fgets(buffer, sizeof(buffer), filePointer) == 0){
                printf("Line %d not found in the file.\n", k);
                fclose(filePointer);
                
            }
        }
        printf("Line %d : %s", k, buffer);
        
    }
    fclose(filePointer);
    
    
}

void ReadFile(const char* name){
    FILE* filePointer;
    char buffer[100]; 
    filePointer = fopen(name, "r");
    int line = 1;

    Header();
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        printf("Line %d: %s",line, buffer);
        line++;
    }
   

    fclose(filePointer);

}


void PasteLine(const char* name, int num){
    FILE* filePointer;
    FILE* tempFile;
    char ***arr = Write(name, 1, 'p');
    filePointer = fopen(name, "r");
    tempFile = fopen("temp.txt", "w");
    char buffer[1000];
    char newline[1000];
    int currentPos = 1;
  
    if(num == 0){
        while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
            fprintf(tempFile, "%s", buffer);
        }
        for(int j = 0; j < COL; j++){
            if(j != COL-1){
                fprintf(tempFile, " %-*.*s |", MAX_WIDTH, MAX_WIDTH, arr[0][j]);
            }
            else{
                fprintf(tempFile, " %-*.*s ", MAX_WIDTH, MAX_WIDTH, arr[0][j]);
            }
        }
        fprintf(tempFile, "\n");
    }
    else{
        while(fgets(buffer, sizeof(buffer), filePointer) != NULL){

            if (currentPos == num) {
                for(int i = 0; i < COL; i++){
                    if(i != COL-1){
                        fprintf(tempFile, " %-*.*s |", MAX_WIDTH, MAX_WIDTH, arr[0][i]);
                    }
                    else{
                        fprintf(tempFile, " %-*.*s ", MAX_WIDTH, MAX_WIDTH, arr[0][i]);
                    }
                }
                
                fprintf(tempFile, "\n");
            }
            fprintf(tempFile, "%s", buffer);
            currentPos++;
        
        }
    }
    
    for(int j = 0; j < COL; j++){
            free(arr[0][j]);
        }
    free(arr[0]);
    free(arr);
    
    fclose(filePointer);
    fclose(tempFile);
    remove(name);
    rename("temp.txt", name);

}

void DeleteLine(const char* name, int num){
    FILE* filePointer;
    FILE* tempFile;
    filePointer = fopen(name, "r");
    tempFile = fopen("temp.txt", "w");
    char buffer[1000];
    int currentLine = 0;
    
    
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        currentLine++;
        if(currentLine != num){
            fprintf(tempFile, "%s", buffer);
        }
        
    }
    fclose(filePointer);
    fclose(tempFile);
    remove(name);
    rename("temp.txt", name);
}


void ChangeLine(const char* name, int num){
    DeleteLine(name, num);
    PasteLine(name, num);
}


void swapStrings(char **str1, char **str2) {
    char temp[100];
    for(int k = 0; k < COL; k++){
        strcpy(temp, str1[k]);
        strcpy(str1[k], str2[k]);
        strcpy(str2[k], temp);
    }
}


void SortArray(char*** arr, int parameter, int line, int dir){
    char temp[100];
    if(dir == 1){
        if(parameter == 1){
            for(int i = 0; i < line - 1; i++){
                for(int j = 0; j < line - i -1; j++){
                    if (strcmp(arr[j][0], arr[j + 1][0]) > 0) {
                        swapStrings(arr[j], arr[j+1]);
                    }
                }
            }
        }
        if(parameter == 2 || parameter == 3){
            for(int i = 0; i < line -1; i++){
                for(int j = 0; j < line - i -1; j++){
                    if(atof(arr[j][parameter-1]) > atof(arr[j+1][parameter-1])){
                        swapStrings(arr[j], arr[j+1]);
                    }
                }
            }
        }
        
    }
    if(dir == 2){
        if(parameter == 1){
            for(int i = 0; i < line - 1; i++){
                for(int j = 0; j < line - i -1; j++){
                    if (strcmp(arr[j][0], arr[j + 1][0]) < 0) {
                        swapStrings(arr[j], arr[j+1]);
                    }
                }
            }
        }
        if(parameter == 2 || parameter == 3){
            for(int i = 0; i < line -1; i++){
                for(int j = 0; j < line - i -1; j++){
                    if(atof(arr[j][parameter-1]) < atof(arr[j+1][parameter-1])){
                        swapStrings(arr[j], arr[j+1]);
                    }
                }
            }
        }
    }
    
    
    


}




void SortLines(const char *name) {
    FILE *filePointer;
    FILE* tempfile;
    char ***arr = splitArray(name, "|");
    int choice;
    int dir;
    char buffer[100];
    int line = 0;
    filePointer = fopen(name, "r");
    tempfile = fopen("temp.txt", "w");
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        line++;
    }
    
    printf("Choose how do you want to sort: 1. Oblast\n2. Population\n3. Square\n");
    scanf("%d", &choice);
    printf("\nChoose how do you want to sort: 1. Ascending\n2. Descending\n");
    scanf("%d", &dir);

    SortArray(arr, choice, line, dir);
    for(int i = 0; i < line; i++){
        for(int j = 0; j < COL; j++){
            if(j != COL-1){
                removeSpacesAndNewLine(arr[i][j]);
                fprintf(tempfile, " %-*.*s |", MAX_WIDTH, MAX_WIDTH, arr[i][j]);
            }
            else{
                removeSpacesAndNewLine(arr[i][j]);
                fprintf(tempfile, " %-*.*s ", MAX_WIDTH, MAX_WIDTH, arr[i][j]);
            }
            
        }
        fprintf(tempfile, "\n");
    }
    

    for (int i = 0; i < line; i++) {
        for (int j = 0; j < COL; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
    fclose(tempfile);
    fclose(filePointer);
    remove(name);
    rename("temp.txt", name);
    ReadFile(name);
}



char*** splitArray(const char* name, const char* delimiter){
    FILE* filePointer;
    int line = 0;

    char buffer[100];
    filePointer = fopen(name, "r");
    if (filePointer == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Counting the lines
    char ch;
    while ((ch = fgetc(filePointer)) != EOF) {
        if (ch == '\n') {
            line++;
        }
    }

    // Reopening the file
    fseek(filePointer, 0, SEEK_SET);
    int i = 0;

    // Creating a dynamic array to store lines
    char** arr = (char**)malloc(line * sizeof(char*));
    // Assigning elements to the array
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        // Allocating memory for each line
        arr[i] = (char*)malloc(strlen(buffer) + 1);
        strcpy(arr[i], buffer);
        i++;
    }


    
    //Part 2. Tokenization.
    //Creating 2D array
    char ***arr2 = (char***)malloc(line*sizeof(char**));
    for(int i = 0; i < line; i++){
        arr2[i] = (char**)malloc(COL*sizeof(char*));
        for(int j = 0; j < COL; j++){
            arr2[i][j] = (char*)malloc(MAX_WIDTH*sizeof(char));
        }
    }
    
    


    for(int i = 0; i < line; i++){
        char *token = strtok(arr[i], delimiter);
        int j = 0;
        while(token != NULL){
            if(strlen(token) > 0){
                //strcpy(arr2[i][j], token);
                strncpy(arr2[i][j], token, MAX_WIDTH - 1);
                arr2[i][j][MAX_WIDTH - 1] = '\0';
            }
            
            token = strtok(NULL, delimiter);
            j++;
        }
    }

    for(int i = 0; i < line; i++){
        free(arr[i]);
    }
    free(arr);
    fclose(filePointer);
    return arr2;

}



char*** Write(const char* name, int linecount, char mode){ //w - writing mode; p - PasteLine mode
    FILE* filePointer;
    char buffer[1000];
    getchar();
    int line = 1;
    filePointer = fopen(name, "r+");
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        line++;
    }
    
    printf("Currect at line %d\n", line);
    
    //Dynamic Array Declaration
    char ***arr = (char***)malloc(linecount*sizeof(char**));
    for(int i = 0; i < linecount; i++){
        arr[i] = (char**)malloc(COL*sizeof(char*));
        for(int j = 0; j < 3; j++){
            arr[i][j] = (char*)malloc(sizeof(buffer)*sizeof(char));
        }
    }

    
    
    for(int i = 0; i < linecount; i++){

        printf("Enter the city: ");
        fgets(buffer, sizeof(buffer), stdin);
        removeSpacesAndNewLine(buffer);
        strcpy(arr[i][0], buffer);

        printf("Enter the population: ");
        fgets(buffer, sizeof(buffer), stdin);
        removeSpacesAndNewLine(buffer);
        strcpy(arr[i][1], buffer);

        printf("Enter the square: ");
        fgets(buffer, sizeof(buffer), stdin);
        removeSpacesAndNewLine(buffer);
        strcpy(arr[i][2], buffer);
        if(mode == 'w'){
            for(int j = 0; j < COL; j++){
                if(j != COL-1){
                    fprintf(filePointer, " %-*.*s |", MAX_WIDTH, MAX_WIDTH, arr[i][j]);
                }
                else{
                    fprintf(filePointer, " %-*.*s ", MAX_WIDTH, MAX_WIDTH, arr[i][j]);
                }
                
            }
            fprintf(filePointer, "\n");
        }
        
        
       
    }
    if(mode == 'p'){
        fclose(filePointer);
        return arr;
    } 
    for(int i = 0; i < linecount; i++){
        for(int j = 0; j < COL; j++){
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);

    fclose(filePointer);
    return NULL;
}





int OpenFile(const char* name){
    FILE* filePointer;
    int choice;
    int num;
    printf("\nFile is ready. Next functions available: \n1.Read line\n2.Read file \n3.Write\n4.Paste line\n5.Delete line\n6.Sort file\n7.Change line\nEnter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    if(choice == 1){
        int line;
        int fline;
        printf("\nWhich range of lines do you want to print out? First line: ");
        scanf("%d", &line);
        printf("\nLast line: ");
        scanf("%d", &fline);
        ReadLine(name, line, fline);
    }
    else if(choice == 2){
        ReadFile(name);
    }
    else if(choice == 3){
        int linecount;
        printf("\nHow many lines do you want to write? ");
        scanf("%d", &linecount);
        Write(name, linecount, 'w');
    }
    else if(choice == 4){
        printf("Enter the position where you want to paste the line: ");
        scanf("%d", &num);
        PasteLine(name, num);
    }
    else if(choice == 5){
        ReadFile(name);
        printf("Enter the position where you want to delete a line: ");
        scanf("%d", &num);
        DeleteLine(name, num);
    }
    else if(choice == 6){
        SortLines(name);
    }
    else if(choice == 7){
        printf("Enter the position where you want to change a line: ");
        scanf("%d", &num);
        ChangeLine(name, num);
    }
    return 1;

}

