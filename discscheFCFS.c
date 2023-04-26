#include <stdio.h>
// function to calculate absolute value
int abs(int x) {
return x > 0 ? x : -x;
}
// function to swap two integers
void swap(int *a, int *b) {
int temp = *a;
*a = *b;
*b = temp;
}
// function to implement FCFS scheduling
void fcfs(int disk[], int n, int head) {
int distance = abs(head - disk[0]);
for (int i = 1; i < n; i++) {
distance += abs(disk[i] - disk[i-1]);
}
printf("\n\nFCFS scheduling: Total head movement = %d\n", distance);
}
// function to implement SCAN scheduling
void scan(int disk[], int n, int head, int max) {
int distance = 0;
int direction = 1; // 1 = upward, -1 = downward
int i = 0;
// find the index of the head position
while (i < n && disk[i] < head) {
i++;
}
// move upward
for (; i < n; i++) {
distance += abs(head - disk[i]);
head = disk[i];
}
// move downward
if (head != max) {
distance += abs(head - max);
head = max;
}
i = n-1;
while (i >= 0 && disk[i] > head) {
i--;
}
// move downward
for (; i >= 0; i--) {
distance += abs(head - disk[i]);
head = disk[i];
}
printf("SCAN scheduling: Total head movement = %d\n", distance);
}
// function to implement CSCAN scheduling
void cscan(int disk[], int n, int head, int max) {
int distance = 0;
int direction = 1; // 1 = upward, -1 = downward
int i = 0;
// find the index of the head position
while (i < n && disk[i] < head) {
i++;
}
// move upward
for (; i < n; i++) {
distance += abs(head - disk[i]);
head = disk[i];
}
// move to the beginning of the disk
distance += abs(head - max);
head = 0;
// move upward
for (i = 0; i < n; i++) {
distance += abs(head - disk[i]);
head = disk[i];
}
printf("C-SCAN scheduling: Total head movement = %d\n", distance);
}
// function to implement SSTF scheduling
void sstf(int disk[], int n, int head) {
int distance = 0;
int current = head;
int min_index;
for (int i = 0; i < n; i++) {
min_index = i;
for (int j = i+1; j < n; j++) {
if (abs(current - disk[j]) < abs(current - disk[min_index])) {
min_index = j;
}
}
distance += abs(current - disk[min_index]);
current = disk[min_index];
swap(&disk[min_index], &disk[i]);
}
printf("SSTF scheduling: Total head movement = %d\n", distance);
}
int main() {
int n, head, max;
printf("Enter the number of disk requests: ");
scanf("%d", &n);
int disk[n];
printf("Enter the disk requests: ");
for (int i = 0; i < n; i++) {
scanf("%d", &disk[i]);
}
printf("Enter the initial head position: ");
scanf("%d", &head);
printf("Enter the maximum disk position: ");
scanf("%d", &max);
// call the FCFS function
fcfs(disk, n, head);
// sort the disk requests in ascending order
for (int i = 0; i < n-1; i++) {
for (int j = i+1; j < n; j++) {
if (disk[i] > disk[j]) {
swap(&disk[i], &disk[j]);
}
}
}
// call the SCAN function
scan(disk, n, head, max);
// call the C-SCAN function
cscan(disk, n, head, max);
// call the SSTF function
sstf(disk, n, head);
return 0;
}