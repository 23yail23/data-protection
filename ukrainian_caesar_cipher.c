
#include <stdio.h>
#include <string.h>

// Український алфавіт
const char ALPHABET[] = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
const int ALPHABET_LENGTH = 33;

// Функція для дешифрування тексту
void decryptUA(char *txt, int key) {
    for (int i = 0; txt[i] != '\0'; i++) {
        // Знаходимо індекс символу у алфавіті
        char *charPos = strchr(ALPHABET, txt[i]);
        if (charPos) {
            int index = charPos - ALPHABET;
            // Обчислюємо новий індекс з урахуванням ключа
            int newIndex = (index - key + ALPHABET_LENGTH) % ALPHABET_LENGTH;
            txt[i] = ALPHABET[newIndex];
        }
    }
}

// Функція для перебору всіх можливих ключів
void breakCaesarUA(const char *encTxt) {
    char temp[256];
    for (int key = 1; key < ALPHABET_LENGTH; key++) {
        strcpy(temp, encTxt);
        decryptUA(temp, key);
        printf("Ключ - %d, Текст - %s\n", key, temp);
    }
}

int main() {
    char txt[256];
    while (1) {
        printf("Введіть зашифрований текст (або \"вихід\" для завершення): ");
        fgets(txt, sizeof(txt), stdin);
        txt[strcspn(txt, "\n")] = '\0';

        if (strcmp(txt, "вихід") == 0) {
            printf("Завершення програми.\n");
            break;
        }

        breakCaesarUA(txt);
    }
    return 0;
}
