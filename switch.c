#include <stdio.h>
#include <ctype.h>

int main(void) {
    char x;
    printf("Enter a char: ");
    scanf("%c", &x);

    switch(x) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            printf("Vowel\n");
            break;
        case 'y':
            printf("Sometimes\n");
            break;
        default :
            printf("Consonant\n");
    }
}