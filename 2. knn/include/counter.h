#ifndef COUNTER_H
#define COUNTER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int label;
    int count;
} LabelCount;

int compare_counter(const void *a, const void *b) {
    return ((LabelCount *)b)->count - ((LabelCount *)a)->count;
}

int find_most_common_label(int *labels, int size) {
    LabelCount *label_counts = (LabelCount *)malloc(size * sizeof(LabelCount));
    int unique_labels_count = 0;

    // Initialize label_counts
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_labels_count; j++) {
            if (label_counts[j].label == labels[i]) {
                label_counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            label_counts[unique_labels_count].label = labels[i];
            label_counts[unique_labels_count].count = 1;
            unique_labels_count++;
        }
    }

    // Sort label_counts by count in descending order
    qsort(label_counts, unique_labels_count, sizeof(LabelCount), compare_counter);

    int most_common_label = label_counts[0].label;

    free(label_counts);
    return most_common_label;
}

#endif