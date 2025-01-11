#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minCars(int N, int W, int weights[]) {
    qsort(weights, N, sizeof(int), compare);  // 对小猫的重量进行排序

    int cars = 0;  // 缆车数量
    int current_weight = 0;  // 当前缆车上的重量

    for (int i = 0; i < N; i++) {
        if (current_weight + weights[i] <= W) {
            current_weight += weights[i];
        }
        else {
            cars++;
            current_weight = weights[i];
        }
    }

    if (current_weight > 0) {
        cars++;
    }

    return cars;
}

int main() {
    int N, W;
    printf("Enter the number of cats and the maximum weight: ");
    scanf("%d %d", &N, &W);

    int* weights = (int*)malloc(N * sizeof(int));
    printf("Enter the weights of the cats: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &weights[i]);
    }

    int min_cars = minCars(N, W, weights);
    printf("Minimum number of cars: %d\n", min_cars);

    free(weights);
	getchar();
    return 0;
}