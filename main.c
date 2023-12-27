#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_WIDTH 30 //Max width of one column of the table
#define COL 3

struct arrData{
    int numline;
};

void swap(char* a, char* b);
void swapStrings(char **str1, char **str2);
void removeSpacesAndNewLine(char* str);
void Header();

void ReadFile(const char* name);
void CreateFile(const char* name);
void DeleteFile(const char* name);

void ReadLine(const char* name, int fline, int lline);
int DeleteLine(const char* name, int num);  
void PasteLine(const char* name, int num);
void SortLines(const char* name, int sorted);
void ChangeLine(const char* name, int num);

void SortArray(char*** arr, int parameter, int line, int dir);

int CheckIfSorted(const char* name);
int CheckInput(char* prompt, int min);
int OpenFile(const char* name);
int CheckIfFileExists(char* name);

int sortedAsc(char*** arr, int lines, int col);
int sortedDesc(char*** arr, int lines, int col);

char*** Write(const char* name, int linecount, char mode);
char*** splitArray(const char* name, const char* delimiter, struct arrData* data);

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
            if(CheckIfFileExists(name)){}
            else{
                printf("File with such name does not exist. Try again\n");
                continue;
            }
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
int CheckInput(char* prompt, int min){
    char buffer[100];
    int check;
    printf("%s", prompt);
    while(1){
        check = 1;
        scanf("%99s", buffer);
        for(int i = 0; buffer[i]; i++){
            if(isdigit(buffer[i]) == 0 || atoi(buffer) < min){
                printf("\nYour input is invalid. Reenter: ");
                check = 0;
                break;
            }
            
        }
        if(check == 1){
            break;
        }
    }
    return atoi(buffer);
}


int CheckIfFileExists(char* name){
    return access(name, F_OK) != -1;
}


int CheckIfSorted(const char* name){
    struct arrData data;
    char ***arr = splitArray(name, "|", &data);
    int lines = data.numline;
    for(int i = 0; i < lines; i++){
        for(int k = 0; k < COL; k++){
            removeSpacesAndNewLine(arr[i][k]);
        }
    }
    int pass;
    //Check if sorted in ascending order
    for(int i = 0; i < COL; i++){
        pass = sortedAsc(arr, lines, i);
        if(pass != 0){
            break;
        }
    }
    printf("\n%d\n", pass);
    //Check if sorted in descending order
    if(pass != 0){
        return pass;
    }
    pass = 0;
    for(int i = 0; i < COL; i++){
        pass = sortedDesc(arr, lines, i);
        if(pass != 0){
            break;
        }
    }
   
    return pass;
   

    
}
int sortedAsc(char*** arr, int lines, int col){
    for(int i = 0; i < lines-1; i++){
        if(col == 0){
            if(strcmp(arr[i][0], arr[i+1][0]) >= 0){
                return 0;
            }
        }
        else if(col == 1 || col == 2){
            if(atof(arr[i][col]) > atof(arr[i+1][col])){
                return 0;
            }
        }
    }
    return col+1;
}
int sortedDesc(char*** arr, int lines, int col){
    for(int i = 0; i < lines-1; i++){
        if(col == 0){
            if(strcmp(arr[i][0], arr[i+1][0]) <= 0){
                return 0;
            }
        }
        else if(col == 1 || col == 2){
            if(atof(arr[i][col]) < atof(arr[i+1][col])){
                return 0;
            }
        }
    }
    return col+4;
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
    fseek(filePointer, 0, SEEK_END);
    if(ftell(filePointer) == 0){
        printf("File is empty\n");
        fclose(filePointer);
    }
    else{
        fclose(filePointer);
        filePointer = fopen(name, "r");
        for(int i = 1; i < fline; i++){
            fgets(buffer, sizeof(buffer), filePointer);
        }
        Header();
        for(int k = fline; k <= lline; k++){
            if(fgets(buffer, sizeof(buffer), filePointer) == NULL){
                printf("Line %d not found\n", k);
                fclose(filePointer);
            }
            else{
                printf("Line %d : %s", k, buffer);
            }
        
        
        }
        fclose(filePointer);
    
    }

    
    
}

void ReadFile(const char* name){
    FILE* filePointer;
    char buffer[100]; 
    filePointer = fopen(name, "r");
    int line = 1;

    Header();
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL){
        if(line < 9){
            printf("Line %d:  %s",line, buffer);
        }
        else if(line > 9){
            printf("Line %d: %s",line, buffer);
        }
        else if(line > 99){
            printf("Line %d:%s",line, buffer);
        }
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
    //0 - pasting as the last line
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

int DeleteLine(const char* name, int num){
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
    if(num > currentLine){
        printf("\nLine not found\n");
        return 0;
    }
    fclose(filePointer);
    fclose(tempFile);
    remove(name);
    rename("temp.txt", name);
    return 1;
}


void ChangeLine(const char* name, int num){
    if(DeleteLine(name, num)){
        PasteLine(name, num);
    }
    
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




void SortLines(const char *name, int sorted) {
    FILE *filePointer;
    FILE* tempfile;
    struct arrData data;


    char ***arr = splitArray(name, "|", &data);

    int choice;
    int dir;
    char buffer[100];
    int line = data.numline; 
    filePointer = fopen(name, "r");
    tempfile = fopen("temp.txt", "w");
    if(sorted == 0){
        choice = CheckInput("Choose how do you want to sort: \n1. Oblast\n2. Population\n3. Square\n", 1);
        dir = CheckInput("\nChoose how do you want to sort: \n1. Ascending\n2. Descending\n", 1);
        SortArray(arr, choice, line, dir);
    }
    else if(sorted > 0){
        if(sorted >= 1 && sorted < 4){
            SortArray(arr, sorted, line, 1);
        }
        else if(sorted >= 4){
            SortArray(arr, sorted - 3, line, 2);
        }
    }
    

    
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



char*** splitArray(const char* name, const char* delimiter, struct arrData* data){
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
    data->numline = line;
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
    int sorted;
    sorted  = CheckIfSorted(name);
    char answer;

    choice = CheckInput("\nFile is ready. Next functions available: \n1.Read line\n2.Read file \n3.Write\n4.Paste line\n5.Delete line\n6.Sort file\n7.Change line\nEnter your choice: ", 1);
    while(choice > 7){
        choice = CheckInput("Please, reenter your choice", 1);
    }
    printf("\n");
    if(choice == 1){
        int fline;
        int lline;
        printf("\nWhich range of lines do you want to print out?");
        fline = CheckInput("First line: ", 1);
        lline = CheckInput("\nLast line: ", 1);
        ReadLine(name, fline, lline);
    }
    else if(choice == 2){
        ReadFile(name);
    }
    else if(choice == 3){
        int linecount = CheckInput("\nHow many lines do you want to write? Enter: ", 1);
        Write(name, linecount, 'w');
    }
    else if(choice == 4){
        if(sorted > 0){
            printf("The file is sorted. Would you like to maintains its order (default - N)? Y/N\n");
            getchar();
            scanf("%c", &answer);
            if(answer == 'Y'){
                PasteLine(name, 0);
                SortLines(name, sorted);
                
            }
            else if(answer == 'N'){
                num = CheckInput("Enter the position where you want to paste the line (0 - end position): ", 0);
                PasteLine(name, num);
            }
            else{
                printf("Couldn't determine the answer. Set to default (N)");

            }

        }
        else{
            num = CheckInput("Enter the position where you want to paste the line (0 - end position): ", 0);
            PasteLine(name, num);
        }
        
    }
    else if(choice == 5){
        ReadFile(name);
        num = CheckInput("Enter the position where you want to delete a line: ", 1);
        DeleteLine(name, num);
    }
    else if(choice == 6){
        SortLines(name, 0);
    }
    else if(choice == 7){
        num = CheckInput("Enter the position where you want to change a line: ", 1);
        ChangeLine(name, num);
    }
    return 1;

}
