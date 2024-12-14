
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decrypt(char *txt, int key) {
    for (int i = 0; txt[i] != '\0'; i++) {
        if (isalpha(txt[i])) {
            char base = islower(txt[i]) ? 'a' : 'A';
            txt[i] = (txt[i] - base - key + 26) % 26 + base;
        }
    }
}

void breakCaesar(const char *encTxt) {
    char temp[256];
    for (int key = 1; key < 26; key++) {
        strcpy(temp, encTxt);
        decrypt(temp, key);
        printf("Ключ - %d, Текст - %s\n", key, temp);
    }
}

int main() {
    char txt[256];

    while (1) {
        printf("Введіть зашифрований текст (або \"end\" для завершення): ");
        fgets(txt, sizeof(txt), stdin);
        txt[strcspn(txt, "\n")] = '\0';

        if (strcmp(txt, "end") == 0) {
            printf("Завершення програми.\n");
            break;
        }

        breakCaesar(txt);
    }
  
    return 0;
}
