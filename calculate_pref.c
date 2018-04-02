#include <stdio.h>
#include <stdlib.h>

#define FILE_CAL_CPY "pref_cpy.txt"
#define FILE_CAL_REF "pref_ref.txt"
#define WORDMAX 256

int main(void)
{
    FILE *fp_cpy = fopen(FILE_CAL_CPY, "r");
    FILE *fp_ref = fopen(FILE_CAL_REF, "r");
    FILE *dict = fopen("calculate_pref.txt", "w");

    //char word[WORDMAX] = "";
    double time_cpy, time_ref;
    int scaler_cpy = 0;
    int scaler_ref = 0;
    int total_scaler_cpy[201]= {0};
    int total_scaler_ref[201]= {0};
    char s[3];

    if (!fp_cpy || !fp_ref || !dict) {
        if (fp_cpy) {
            printf( "error: file open failed in '%s'.\n", FILE_CAL_CPY);
            fclose(fp_cpy);
        }
        if (fp_ref) {
            printf( "error: file open failed in '%s'.\n", FILE_CAL_REF);
            fclose(fp_ref);
        }
        if (dict) {
            printf( "error: file open failed in '%s'.\n","calculate_pref..txt");
            fclose(dict);
        }
        return 1;
    }

    for (int i = 0; i < 1001; i++) {
        if (feof(fp_cpy)) {
            printf("ERROR: You need 1000 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }

        fscanf(fp_cpy, "%d %lf %s\n", &i, &time_cpy, s);
        scaler_cpy = time_cpy/0.000005;
        printf("%d %lf %d ",i,time_cpy,scaler_cpy);
        total_scaler_cpy[scaler_cpy]++;

        if (feof(fp_ref)) {
            printf("ERROR: You need 1000 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp_ref, "%d %lf %s\n", &i, &time_ref,s);
        scaler_ref = time_ref/0.000005;
        printf("%d %lf %d \n",i,time_ref,scaler_ref);
        total_scaler_ref[scaler_ref]++;
    }
    fclose(fp_cpy);
    fclose(fp_ref);

    for (int i = 1; i <201 ; i++) {
        printf("%lf %d %d\n", 0.000005*i,total_scaler_ref[i],total_scaler_cpy[i]);
        fprintf(dict , "%lf %d %d\n", 0.000005*i,total_scaler_ref[i],total_scaler_cpy[i]);
    }
    fclose(dict);
    return 0;
}
