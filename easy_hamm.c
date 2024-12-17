
#include <stdio.h>
#include <string.h>

// Кодування
void encode(const char *input, char *encoded) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '1') {
            encoded[j++] = '1';
            encoded[j++] = '1';
            encoded[j++] = '1';
        } else {
            encoded[j++] = '0';
            encoded[j++] = '0';
            encoded[j++] = '0';
        }
    }
    encoded[j] = '\0';
}

// Декодування
void decode(const char *received, char *decoded) {
    int i, j = 0;
    for (i = 0; received[i] != '\0'; i += 3) {
        int count1 = 0, count0 = 0;

        if (received[i] == '1') count1++; else count0++;
        if (received[i+1] == '1') count1++; else count0++;
        if (received[i+2] == '1') count1++; else count0++;
        decoded[j++] = (count1 > count0) ? '1' : '0';
    }
    decoded[j] = '\0';
}

int main() {
    char input[50];   
    char encoded[150];  
    char received[150]; 
    char decoded[50];   
   
    printf("Введіть бінарне повідомлення (0 і 1): ");
    scanf("%s", input);

    encode(input, encoded);
    printf("Закодоване повідомлення: %s\n", encoded);

    printf("Введіть отримане повідомлення (з можливими помилками): ");
    scanf("%s", received);

    decode(received, decoded);
    printf("Виправлене (декодоване) повідомлення: %s\n", decoded);

    return 0;
}
