#include <stdio.h>
#define MAX_PARTITIONS 100
#define MAX_PROCESSES 100
int partitions[MAX_PARTITIONS];
int processes[MAX_PROCESSES];
int num_partitions;
int num_processes;
// First Fit algorithm
void first_fit() {
int i, j;
for (i = 0; i < num_processes; i++) {
for (j = 0; j < num_partitions; j++) {
if (processes[i] <= partitions[j]) {
partitions[j] -= processes[i];
printf("Process %d allocated to partition %d.\n", i + 1, j + 1);
break;
}
}
if (j == num_partitions) {
printf("Process %d cannot be allocated.\n", i + 1);
}
}
}
// Best Fit algorithm
void best_fit() {
int i, j, best;
for (i = 0; i < num_processes; i++) {
best = -1;
for (j = 0; j < num_partitions; j++) {
if (processes[i] <= partitions[j]) {
if (best == -1 || partitions[j] < partitions[best]) {
best = j;
}
}
}
if (best != -1) {
partitions[best] -= processes[i];
printf("Process %d allocated to partition %d.\n", i + 1, best + 1);
} else {
printf("Process %d cannot be allocated.\n", i + 1);
}
}
}
// Worst Fit algorithm
void worst_fit() {
int i, j, worst;
for (i = 0; i < num_processes; i++) {
worst = -1;
for (j = 0; j < num_partitions; j++) {
if (processes[i] <= partitions[j]) {
if (worst == -1 || partitions[j] > partitions[worst]) {
worst = j;
}
}
}
if (worst != -1) {
partitions[worst] -= processes[i];
printf("Process %d allocated to partition %d.\n", i + 1, worst + 1);
} else {
printf("Process %d cannot be allocated.\n", i + 1);
}
}
}
int main() {
int i;
printf("Enter the number of partitions: ");
scanf("%d", &num_partitions);
printf("Enter the size of each partition:\n");
for (i = 0; i < num_partitions; i++) {
scanf("%d", &partitions[i]);
}
printf("Enter the number of processes: ");
scanf("%d", &num_processes);
printf("Enter the size of each process:\n");
for (i = 0; i < num_processes; i++) {
scanf("%d", &processes[i]);
}
printf("\nFirst Fit Algorithm:\n");
first_fit();
printf("\nBest Fit Algorithm:\n");
best_fit();
printf("\nWorst Fit Algorithm:\n");
worst_fit();
return 0;
}