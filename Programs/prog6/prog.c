#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#define COUNT 10
#define FILE_NAME "words.txt"

char search_words[][COUNT] = {"The", "around", "graphics", "from", "by", "be", "any", "which", "various", "mount"};
long counts[COUNT];
int line_c = 0;
int is_alpha(char c)
{
    return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
int is_equal(char *a, const char *key, int ignore_case)
{
    char b[20];
    strcpy(b, key);
    // int len_a = strlen(a), len_b = strlen(b);
    // if (len_a != len_b)
    // {
    //     return 0;
    // }
    // if (ignore_case != 0)
    // {
    //     int i;
    //     for (i = 0; i < len_a; i++)
    //     {
    //         if (a[i] > 90)
    //         {
    //             a[i] -= 32;
    //         }
    //     }
    //     for (i = 0; i < len_b; i++)
    //     {
    //         if (b[i] > 90)
    //         {
    //             b[i] -= 32;
    //         }
    //     }
    // }
    return (strcasecmp(a, b) == 0);
}

void read_word(char *temp, FILE *fp)
{
    int i = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF && isalpha(ch) == 0)
    {
    }
    while (ch != EOF && isalpha(ch) != 0)
    {
        temp[i++] = ch;
        ch = fgetc(fp);
    }
    temp[i] = '\0';
}

long determine_count(const char *file_name, const char *key, int ignore_case)
{
    long word_count = 0;
    char ch;
    FILE *fp = fopen(file_name, "r");
    char temp[40];
    while (feof(fp) == 0)
    {
        read_word(temp, fp);
        // printf("\n%s ", temp);
        if (is_equal(temp, key, ignore_case) != 0)
        {
            word_count++;
        }
    }
    printf("\nWord %s: %ld", key, word_count);
    return word_count;
}
void main()
{
    int i;
    for (int n = 1; n <= 8; n *= 2)
    {
        for (i = 0; i < COUNT; i++)
        {
            counts[i] = 0;
        }
        double t = omp_get_wtime();
        omp_set_num_threads(n);
#pragma omp parallel for
        for (i = 0; i < COUNT; i++)
        {
            counts[i] = determine_count(FILE_NAME, search_words[i], 1);
        }
        t = omp_get_wtime() - t;

        // for (i = 0; i < COUNT; i++)
        // {
        //     printf("\n%s: %ld", search_words[i], counts[i]);
        // }
        printf("\nTime Taken : %lf Threads: %d\n", t, n);
    }
}
