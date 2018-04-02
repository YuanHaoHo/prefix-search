#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tst.h"
#include "bench.h"
#define DICT_FILE "cities.txt"
#define WORDMAX 256

double tvgetf()
{
    struct timespec ts;
    double sec;

    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;

    return sec;
}

int bench_test(const tst_node *root, char *out_file, const int max,double T,int state)
{
    char prefix[3] = "";
    char word[WORDMAX] = "";
    char **sgl;
    FILE *fp = fopen(out_file, "a+");
    FILE *dict = fopen(DICT_FILE, "r");
    int idx = 0, sidx = 0;
    double t1, t2;
    int idn = 1;

    if (!fp || !dict) {
        if (fp) {
            fprintf(stderr, "error: file open failed in '%s'.\n", DICT_FILE);
            fclose(fp);
        }
        if (dict) {
            fprintf(stderr, "error: file open failed in '%s'.\n", out_file);
            fclose(dict);
        }
        return 1;
    }

    if(state == 0) {
        while (fgets(word,20,fp) != NULL) {
            idn++;
        }
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "%d %.6f sec\n",idn, T);

    } else {
        sgl = (char **)malloc(sizeof(char *) * max);
        while (fscanf(dict, "%s", word) != EOF) {
            if (strlen(word) < 4) continue;
            strncpy(prefix, word, 3);
            t1 = tvgetf();
            tst_search_prefix(root, prefix, sgl, &sidx, max);
            t2 = tvgetf();
            fprintf(fp, "%d %.9f sec\n", idx, t2-t1);
            idx++;
        }
    }

    fclose(fp);
    fclose(dict);
    return 0;
}