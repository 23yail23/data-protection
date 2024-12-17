
#include <stdio.h>
#include <string.h>

int calculate_parity(int data[], int positions[], int size) {
    int parity = 0;
    for (int i = 0; i < size; i++) {
        parity ^= data[positions[i] - 1];
    }
    return parity;
}

void encode_hamming(const int input[4], int encoded[7]) {
    int p1_positions[] = {1, 3, 5, 7}, p2_positions[] = {2, 3, 6, 7}, p4_positions[] = {4, 5, 6, 7};
    memset(encoded, 0, 7 * sizeof(int));
    encoded[2] = input[0]; encoded[4] = input[1]; encoded[5] = input[2]; encoded[6] = input[3];
    encoded[0] = calculate_parity(encoded, p1_positions, 4);
    encoded[1] = calculate_parity(encoded, p2_positions, 4);
    encoded[3] = calculate_parity(encoded, p4_positions, 4);
}

void decode_hamming(int received[7], int decoded[4]) {
    int p1_positions[] = {1, 3, 5, 7}, p2_positions[] = {2, 3, 6, 7}, p4_positions[] = {4, 5, 6, 7};
    
    int p1 = calculate_parity(received, p1_positions, 4), p2 = calculate_parity(received, p2_positions, 4), p4 = calculate_parity(received, p4_positions, 4);
    
    int error_position = p1 + (p2 << 1) + (p4 << 2);
    if (error_position) { printf("Помилка в біті %d!\n", error_position); received[error_position - 1] ^= 1; }
    else { printf("Повідомлення не містить помилок.\n"); }
    decoded[0] = received[2]; decoded[1] = received[4]; decoded[2] = received[5]; decoded[3] = received[6];
}

int main() {
    int input[4], encoded[7], received[7], decoded[4];
    printf("Введіть 4 біти для кодування (через пробіл): ");
    for (int i = 0; i < 4; i++) scanf("%d", &input[i]);
    encode_hamming(input, encoded);
    printf("Закодоване повідомлення: "); for (int i = 0; i < 7; i++) printf("%d", encoded[i]); printf("\n");
    
    printf("Введіть отримане повідомлення (7 бітів, через пробіл): ");
    for (int i = 0; i < 7; i++) scanf("%d", &received[i]);
    decode_hamming(received, decoded);
    printf("Виправлене повідомлення: "); for (int i = 0; i < 7; i++) printf("%d", received[i]); printf("\n");
    
    printf("Декодоване (корисне) повідомлення: "); for (int i = 0; i < 4; i++) printf("%d", decoded[i]); printf("\n");
    return 0;
}
