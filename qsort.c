#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *arg1, const void *arg2) {
    const char **s1 = (const char **)arg1;
    const char **s2 = (const char **)arg2;
    return strcmp(*s1, *s2);
}

int main(int argc, char **argv) {
    int i;
    int nmemb = argc - 1;

    char **arguments = malloc(sizeof(char *) * (nmemb));

    for (i = 0; i < nmemb; i++) {
        arguments[i] = argv[i + 1];
    }

    puts("unsorted:");
    for (i = 0; i < nmemb; i++) {
        printf("\t%s\n", arguments[i]);
    }

    qsort(
        arguments,
        nmemb,
        sizeof(char *),
        compare
    );

    puts("sorted:");
    for (i = 0; i < nmemb; i++) {
        printf("\t%s\n", arguments[i]);
    }

    free(arguments);
}
