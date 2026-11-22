// Spiral Matrix · shrinking boundaries
// Standalone curated implementation. Change the input declarations to experiment.
// Output is a flat sequence; boolean results use 1 (true) and 0 (false).
// Clockwise from the top-left. Recheck the remaining row and column before reversing direction, so one-row and one-column interiors are not visited twice. O(rows·columns) time; the visited/traversal teaching lanes use O(rows·columns) storage.
#include <stdio.h>
int values[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int output[512] = {0};
int visited[12] = {0};
int traversal[12] = {0};
int length = 12;
int outputSize = 0;
int rows = 3;
int columns = 4;
int top = 0;
int bottom = 2;
int left = 0;
int right = 3;
int count = 0;
int run(void);

int run(void) {
    int row = 0;
    int column = 0;
    int cell = 0;
    while ((top <= bottom) && (left <= right)) {
        row = top;
        column = left;
        while (column < (right + 1)) {
            cell = ((row * columns) + column);
            visited[cell] = (count + 1);
            traversal[count] = values[cell];
            count = (count + 1);
            output[outputSize] = values[cell];
            outputSize = (outputSize + 1);
            column = (column + 1);
        }
        top = (top + 1);
        column = right;
        row = top;
        while (row < (bottom + 1)) {
            cell = ((row * columns) + column);
            visited[cell] = (count + 1);
            traversal[count] = values[cell];
            count = (count + 1);
            output[outputSize] = values[cell];
            outputSize = (outputSize + 1);
            row = (row + 1);
        }
        right = (right + -1);
        if (top <= bottom) {
            row = bottom;
            column = right;
            while (left <= column) {
                cell = ((row * columns) + column);
                visited[cell] = (count + 1);
                traversal[count] = values[cell];
                count = (count + 1);
                output[outputSize] = values[cell];
                outputSize = (outputSize + 1);
                column = (column + -1);
            }
            bottom = (bottom + -1);
        }
        if (left <= right) {
            column = left;
            row = bottom;
            while (top <= row) {
                cell = ((row * columns) + column);
                visited[cell] = (count + 1);
                traversal[count] = values[cell];
                count = (count + 1);
                output[outputSize] = values[cell];
                outputSize = (outputSize + 1);
                row = (row + -1);
            }
            left = (left + 1);
        }
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