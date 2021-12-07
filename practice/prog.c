#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<omp.h>
#include<string.h>
#define FILE_NAME "words.txt"
#define COUNT 7
char words[7][10] = {"The", "graphics", "from", "by", "be", "any", "around"};
int counts[7];

void readWord(char *temp, FILE *fp){
    char ch;
    int i=0;
    while((ch=fgetc(fp))!=EOF && !isalpha(ch));

    while(ch!=EOF && isalpha(ch)){
        temp[i++]=ch;
        ch = fgetc(fp);
    }
    temp[i] = '\0';
}

int determineCount(const char *filename, char *word, int ignore){
    FILE *fp = fopen(filename,"r");
    int count=0;
    if(fp==NULL){
        printf("Error in file");
        return count;
    } else{
        char c;
        while(feof(fp)==0){
            char temp[40];
            readWord(temp,fp);
            if(ignore==1){
                for(int i=0;i<strlen(temp);i++){
                    temp[i]=tolower(temp[i]);
                }
                if(strcmp(temp,word)==0){
                    count++;
                }
            }
        }
    }
    return count;

}

int main(){
    int ignore_case=1;
    int n_t, i;
    for(int j=0;j<5;j++){
        counts[j] = 0;
    }
    for(n_t=1;n_t<=8;n_t*=2){
        double t = omp_get_wtime();
        omp_set_num_threads(n_t);
        #pragma omp parallel for 
        for(i=0;i<7;i++){
            counts[i] = determineCount(FILE_NAME, words[i],ignore_case);
        }
        t = omp_get_wtime() - t;
        printf("Time: %lf", t);
        for(int k=0;k<7;k++){
            printf("%s: %d\n",words[k], counts[k]);
        }
    }
    return 0;
}