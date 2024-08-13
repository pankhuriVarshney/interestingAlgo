#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct badMatchTable{
    char letter;
    int value;
};

int findPattern(char str[], int strlen, char pattern[], int patternlen); 

int main(){
    char str[50];
    char pattern[50];
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Enter a patter: ");
    scanf("%s", pattern);
    findPattern(str, strlen(str), pattern, strlen(pattern));
}

int findPattern(char str[], int strlen, char pattern[], int patternlen){
    //bad match table:
    //number of unique letters:
    int count=0;
    struct badMatchTable *bmt=(struct badMatchTable*)(calloc(patternlen, sizeof(struct badMatchTable)));
    for(int i=0; i<patternlen; i++){
        int j;
        for(j=0; j<i; j++){
            if(pattern[i]==pattern[j])
                break;
        }
        if(i==j){
            bmt[count].letter=pattern[i];
            count++;
        }
    }
    count++;
    bmt=(struct badMatchTable*)(realloc(bmt, sizeof(struct badMatchTable) *count));
    //calculating the values:

    bmt[count-1].letter='*';
    bmt[count-1].value=patternlen;
    for(int i=0; i<count-1; i++){
        for(int j=0; j<patternlen; j++){
            if(bmt[i].letter==pattern[j]){
                bmt[i].value=1>(patternlen-j-1)?1:(patternlen-j-1);
            }
        }
    }

    for(int i=0; i<count; i++){
        printf("%c\t%d\n", bmt[i].letter, bmt[i].value);
    }

    int i=patternlen-1;
    int flag1=-1, flag2=1;
    while(i<strlen){
        for(int j=i, k=patternlen-1; j>=0 && k>=0; j--, k--){
            if(str[j]!=pattern[k]){
                flag1=-1;
                flag2=1;
                for(int l=0; l<count-1; l++){
                    if(str[j]==bmt[l].letter){
                        i+=bmt[l].value;
                        flag2=0;
                        break;
                    }
                }
                if(flag2){
                    i+=bmt[count-1].value;
                }
            }
            else{
                flag1=j;
            }
        }
    }
    if(flag1!=-1){
        printf("FOUND AT INDEX %d\n", flag1);
    }
    else
        printf("NOT FOUND\n");
}