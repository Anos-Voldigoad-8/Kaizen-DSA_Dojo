// Li Chao Tree · minimum of inserted lines
// Standalone curated implementation. Change the input declarations to experiment.
// Output is a flat sequence; boolean results use 1 (true) and 0 (false).
// Integer x-domain is [−16,16], represented internally by shifted positions 0..32. Each node retains the line winning at its midpoint; a displaced line can improve at most one side. Strict comparisons retain the existing line on ties. O(log U) insertion/query, O(U) reserved storage, with U=33.
#include <stdio.h>
int values[4] = {-4, 0, 2, 6};
int output[512] = {0};
int slopes[3] = {2, -1, 0};
int intercepts[3] = {3, 5, 1};
int lineId[132] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int nodeLow[132] = {0};
int nodeHigh[132] = {0};
int leftChild[132] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int rightChild[132] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int answers[4] = {0};
int length = 4;
int outputSize = 0;
int nodeCount = 1;
int lineCount = 3;
int lineValue(int line, int position);
int insertLine(int node, int low, int high, int incoming);
int minimumLine(int node, int low, int high, int position);
int run(void);

int lineValue(int line, int position) {
    return ((slopes[line] * (position - 16)) + intercepts[line]);
}

int insertLine(int node, int low, int high, int incoming) {
    int middle = 0;
    int betterLeft = 0;
    int betterMiddle = 0;
    int displaced = 0;
    int child = 0;
    nodeLow[node] = low;
    nodeHigh[node] = high;
    if (lineId[node] == -1) {
        lineId[node] = incoming;
        return 0;
    }
    middle = ((low + high) / 2);
    betterLeft = 0;
    betterMiddle = 0;
    if (lineValue(incoming, low) < lineValue(lineId[node], low)) {
        betterLeft = 1;
    }
    if (lineValue(incoming, middle) < lineValue(lineId[node], middle)) {
        betterMiddle = 1;
    }
    if (betterMiddle == 1) {
        displaced = lineId[node];
        lineId[node] = incoming;
        incoming = displaced;
    }
    if (low == high) {
        return 0;
    }
    if (betterLeft != betterMiddle) {
        if (leftChild[node] == -1) {
            leftChild[node] = nodeCount;
            nodeCount = (nodeCount + 1);
        }
        child = leftChild[node];
        insertLine(child, low, middle, incoming);
    }
    else {
        if (rightChild[node] == -1) {
            rightChild[node] = nodeCount;
            nodeCount = (nodeCount + 1);
        }
        child = rightChild[node];
        insertLine(child, (middle + 1), high, incoming);
    }
    return 0;
}

int minimumLine(int node, int low, int high, int position) {
    int answer = 0;
    int middle = 0;
    int candidate = 0;
    if (node == -1) {
        return 1000000;
    }
    answer = lineValue(lineId[node], position);
    if (low == high) {
        return answer;
    }
    middle = ((low + high) / 2);
    if (position <= middle) {
        candidate = minimumLine(leftChild[node], low, middle, position);
    }
    else {
        candidate = minimumLine(rightChild[node], (middle + 1), high, position);
    }
    if (candidate < answer) {
        answer = candidate;
    }
    return answer;
}

int run(void) {
    int i = 0;
    int q = 0;
    i = 0;
    while (i < lineCount) {
        insertLine(0, 0, 32, i);
        i = (i + 1);
    }
    q = 0;
    while (q < length) {
        answers[q] = minimumLine(0, 0, 32, (values[q] + 16));
        output[outputSize] = answers[q];
        outputSize = (outputSize + 1);
        q = (q + 1);
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