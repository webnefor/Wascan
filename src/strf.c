
#include "strf.h"

int   split     (char *message, char symblol_edit, char add_split[][1024]) {

    u_int64_t lenElemnt          = strlen(message);

    u_int64_t j                  = 0;
    u_int64_t i                  = 0;

    u_int16_t count_arr          = 0;
    u_int16_t count_elemnt       = 0;
    u_int16_t count_toch         = 0;

    unsigned char array[lenElemnt * 2];

    sprintf(array, "%s", message);

    memset(add_split, 0, 1024 * 1024 * sizeof(char));

    for (;i < lenElemnt;i++) {

        if (array[i] != symblol_edit) {

            add_split[count_arr+1][count_elemnt] = array[i];
            count_elemnt++;

        } else {
            count_elemnt = 0;
            count_arr +=1;
        }

        if (array[i] == symblol_edit)
            count_toch+=1;
    }

    count_toch +=1;

    char *num = mvsymbol(count_toch);

    strcpy(add_split[0], num);

    add_split[count_arr+2][0] = '\n';

    free(num);

    return (0);
}

char *str (int input[],int len) {

    int value = 255;
    char *one_h, *two_h, *three_h, *four_h;
    char *return_addr = calloc(value, value);
    char *p_value[] = {one_h, ".", two_h,".", \
                                three_h,".",four_h};

    for (int i = 0; i < 7;i++)
        strcat(return_addr, p_value[i]);

    return return_addr;
}

char *mvsymbol  (int n) {

    char *c;
    char ar[900];
    c = (char *)malloc(10 * sizeof(char));
    int v = 0;

    while (n > 9) {
        c[v++] = (n % 10) + '0';
        n = n / 10;
    }
    c[v++] = n + '0';
    c[v] = '\0';
    char t;

    for (int i = 0; i < v / 2; i++)
    {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    v = 0;

    return c;
}

char *mvstring  (int one, int two, int three, int four) {

    int value = 255;
    char *one_h, *two_h, *three_h, *four_h;
    char *return_addr = calloc(value, value);

    one_h       = mvsymbol(one);
    two_h       = mvsymbol(two);
    three_h     = mvsymbol(three);
    four_h      = mvsymbol(four);

    char *p_value[] = {one_h, ".", two_h,".", \
                                three_h,".",four_h};

    for (int i = 0; i < 7;i++)
        strcat(return_addr, p_value[i]);

    free(one_h);
    free(two_h);
    free(three_h);
    free(four_h);

    return return_addr;
}

char *concat (char *arr[], int __size) {

    char *memtemp = malloc(__size * 512);

    char *low;

    int utemp = 0;

    for (int i = 0;i < __size;i++)
        for (int len = 0; len < strlen(arr[i]);len++) {
            memtemp[utemp] = arr[i][len];
            utemp+=1;
        }

    low = memtemp;

    free(memtemp);

    return low;
}

int splet(char *message, char symblol_edit, char *add_split[]) {

    int lenElemnt          = strlen(message);

    int j                  = 0;
    int i                  = 0;

    int count_arr          = 0;
    int count_elemnt       = 0;
    int count_toch         = 0;

    char temp_arr[256][256];

    char *temp;

    for (;i < lenElemnt;i++) {

        if (message[i] == symblol_edit) {
            count_arr += 1;
            count_elemnt = 0;
            i++;
        }
        temp_arr[count_arr][count_elemnt] = message[i];
        temp = temp_arr[count_arr];
        add_split[count_arr] = temp;
        count_elemnt +=1;
    }

    return 0;
}