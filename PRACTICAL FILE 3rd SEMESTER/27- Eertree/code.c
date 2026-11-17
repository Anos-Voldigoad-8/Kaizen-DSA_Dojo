// Eertree · distinct palindromes and occurrence counts
// Standalone curated implementation. Change the input declarations to experiment.
// Output is a flat sequence; boolean results use 1 (true) and 0 (false).
// Two roots represent lengths −1 and 0. An edge labeled c represents wrapping an existing palindrome as cPc. Each new distinct palindrome creates exactly one node. After construction, propagate end-position counts down suffix links. O(n) time and O(128n) space for fixed ASCII.
// Reference: Rubinchik and Shur, EERTREE: An Efficient Data Structure for Processing Palindromes in Strings (2015).
#include <stdio.h>
int values[7] = {97, 98, 97, 99, 97, 98, 97};
int output[512] = {0};
int transitions[1152] = {0};
int palindromeLength[9] = {-1, 0, 0, 0, 0, 0, 0, 0, 0};
int suffixLink[9] = {0};
int firstEnd[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
int occurrences[9] = {0};
int parent[9] = {0};
int labels[9] = {0};
int length = 7;
int outputSize = 0;
int nodeCount = 2;
int last = 1;
int position = 0;
int extendableSuffix(int node);
int run(void);

int extendableSuffix(int node) {
    while ((((position - 1) - palindromeLength[node]) < 0) || (values[((position - 1) - palindromeLength[node])] != values[position])) {
        node = suffixLink[node];
    }
    return node;
}

int run(void) {
    int symbol = 0;
    int node = 0;
    int child = 0;
    int fallback = 0;
    position = 0;
    while (position < length) {
        symbol = values[position];
        node = extendableSuffix(last);
        child = transitions[((node * 128) + symbol)];
        if (child == 0) {
            child = nodeCount;
            nodeCount = (nodeCount + 1);
            palindromeLength[child] = (palindromeLength[node] + 2);
            parent[child] = node;
            labels[child] = symbol;
            firstEnd[child] = position;
            transitions[((node * 128) + symbol)] = child;
            if (palindromeLength[child] == 1) {
                suffixLink[child] = 1;
            }
            else {
                fallback = extendableSuffix(suffixLink[node]);
                suffixLink[child] = transitions[((fallback * 128) + symbol)];
            }
            last = child;
        }
        else {
            last = child;
        }
        occurrences[last] = (occurrences[last] + 1);
        position = (position + 1);
    }
    node = (nodeCount - 1);
    while (node >= 2) {
        occurrences[suffixLink[node]] = (occurrences[suffixLink[node]] + occurrences[node]);
        node = (node + -1);
    }
    node = 2;
    while (node < nodeCount) {
        output[outputSize] = ((firstEnd[node] - palindromeLength[node]) + 1);
        outputSize = (outputSize + 1);
        output[outputSize] = palindromeLength[node];
        outputSize = (outputSize + 1);
        output[outputSize] = occurrences[node];
        outputSize = (outputSize + 1);
        node = (node + 1);
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