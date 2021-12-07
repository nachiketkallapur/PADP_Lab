#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#define COUNT 10
char search_words[][COUNT] = {"The", "around", "graphics", "from", "by", "be", "any", "which", "various", "mount"};

void read_word(char *temp, FILE *fp)
{
    // int i = 0;
    // char ch;
    // while ((ch = fgetc(fp)) != EOF && isalpha(ch) == 0)
    // {
    // }
    // while (ch != EOF && isalpha(ch) != 0)
    // {
    //     temp[i++] = ch;
    //     ch = fgetc(fp);
    // }
    // temp[i] = '\0';
    char ch;
    int tempIdx = 0;
    while ((ch = fgetc(fp)) != EOF && isalpha(ch) == 0)
    {
    }

    while (ch != EOF && isalpha(ch) != 0)
    {
        temp[tempIdx++] = ch;
        ch = fgetc(fp);
    }
    temp[tempIdx]='\0';
}

int determine_count(const char *file_name, const char *search_word, int ignore_case)
{
    FILE *fp = fopen(file_name, "r");

    int search_word_count = 0;
    char temp[40];
    while (feof(fp) == 0)
    {
        read_word(temp, fp);
        // printf("%s\n", temp);
        if (strcasecmp(temp, search_word) == 0)
        {
            search_word_count++;
        }
    }

    return search_word_count;
}

int main()
{

    int counts[COUNT];

    for (int t = 1; t <= 8; t *= 2)
    {
        double t1 = omp_get_wtime();
        int i;
        omp_set_num_threads(t);
#pragma omp parallel for shared(counts,search_words) private(i)
        for ( i = 0; i < COUNT; i++)
        {
            counts[i] = determine_count("words.txt", search_words[i], 1);
        }

        double t2 = omp_get_wtime();

        printf("\nthreads: %d, time: %lf",t,t2-t1);
        for (int i = 0; i < COUNT; i++)
        {
            printf("\nFrequency of %s is %d", search_words[i], counts[i]);
        }
    }
    printf("\n");
    return 0;
}