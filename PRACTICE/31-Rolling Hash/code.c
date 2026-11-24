// Rolling Hash · fixed-length polynomial windows
// Standalone curated implementation. Change the input declarations to experiment.
// Output is a flat sequence; boolean results use 1 (true) and 0 (false).
// ASCII character codes are polynomial digits. Hash(s)=Σcode(s[i])×base^(m−1−i) mod modulus. Slide by subtracting the outgoing weighted digit, multiplying by base, and adding the incoming code. Hash equality is only a candidate equality: collisions require comparing actual strings. O(n) time, O(1) rolling state plus O(n) displayed hash history.
#include <stdio.h>
int values[6] = {66, 65, 78, 65, 78, 65};
int output[512] = {0};
int hashes[4] = {0};
int length = 6;
int outputSize = 0;
int window = 3;
int radix = 31;
int modulus = 101;
int power = 1;
int hashValue = 0;
int windowCount = 4;
int run(void);

int run(void) {
    int offset = 0;
    int start = 0;
    int outgoing = 0;
    int incomingIndex = 0;
    offset = 0;
    while (offset < (window - 1)) {
        power = ((power * radix) % modulus);
        offset = (offset + 1);
    }
    offset = 0;
    while (offset < window) {
        hashValue = (((hashValue * radix) + values[offset]) % modulus);
        offset = (offset + 1);
    }
    hashes[0] = hashValue;
    start = 1;
    while (start < windowCount) {
        outgoing = ((values[(start - 1)] * power) % modulus);
        hashValue = (((hashValue + modulus) - outgoing) % modulus);
        incomingIndex = ((start + window) - 1);
        hashValue = (((hashValue * radix) + values[incomingIndex]) % modulus);
        hashes[start] = hashValue;
        start = (start + 1);
    }
    start = 0;
    while (start < windowCount) {
        output[outputSize] = hashes[start];
        outputSize = (outputSize + 1);
        start = (start + 1);
    }
    return 0;
}
int main(void) {
    run();
    for (int i = 0; i < outputSize; i++) {
        printf("%d ", output[i]);
    }
    return 0;
}