#include<stdio.h>
void FIFO(int pages[], int n, int frames);
void LRU(int pages[], int n, int frames);
void Optimal(int pages[], int n, int frames);
int main() {
int pages[50], n, frames;
printf("Enter the number of pages: ");
scanf("%d", &n);
printf("Enter the size of the page: ");
scanf("%d", &frames);
printf("Enter the page reference string: ");
for(int i=0; i<n; i++) {
scanf("%d", &pages[i]);
}
FIFO(pages, n, frames);
LRU(pages, n, frames);
Optimal(pages, n, frames);
return 0;
}
void FIFO(int pages[], int n, int frames) {
int memory[10], page_faults = 0, front = 0, rear = 0;
for(int i=0; i<frames; i++) {
memory[i] = -1;
}
for(int i=0; i<n; i++) {
int flag = 0;
for(int j=0; j<frames; j++) {
if(memory[j] == pages[i]) {
flag = 1;
break;
}
}
if(flag == 0) {
memory[rear] = pages[i];
rear = (rear + 1) % frames;
page_faults++;
}
}
printf("\nFIFO Algorithm:\n");
printf("Total page faults: %d\n", page_faults);
}
void LRU(int pages[], int n, int frames) {
int memory[10], page_faults = 0, min, index;
for(int i=0; i<frames; i++) {
memory[i] = -1;
}
for(int i=0; i<n; i++) {
int flag = 0;
for(int j=0; j<frames; j++) {
if(memory[j] == pages[i]) {
flag = 1;
break;
}
}
if(flag == 0) {
if(i >= frames) {
min = n;
for(int j=0; j<frames; j++) {
int k;
for(k=i-1; k>=0; k--) {
if(memory[j] == pages[k]) {
break;
}
}
if(k < min) {
min = k;
index = j;
}
}
}
memory[index] = pages[i];
page_faults++;
}
}
printf("\nLRU Algorithm:\n");
printf("Total page faults: %d\n", page_faults);
}
void Optimal(int pages[], int n, int frames) {
int memory[50], page_faults = 0, flag1, flag2, pos;
for(int i=0; i<frames; i++) {
memory[i] = -1;
}
for(int i=0; i<n; i++) {
flag1 = flag2 = 0;
for(int j=0; j<frames; j++) {
if(memory[j] == pages[i]) {
flag1 = flag2 = 1;
break;
}
}
if(flag1 == 0) {
for(int j=0; j<frames; j++) {
if(memory[j] == -1) {
memory[j] = pages[i];
flag2 = 1;
page_faults++;
break;
}
}
}
if(flag2 == 0) {
int future[10];
for(int j=0; j<frames; j++) {
future[j] = -1;
for(int k=i+1; k<n; k++) {
if(memory[j] == pages[k]) {
future[j] = k;
break;
}
}
}
flag1 = 0;
for(int j=0; j<frames; j++) {
if(future[j] == -1) {
pos = j;
flag1 = 1;
break;
}
}
if(flag1 == 0) {
int max = future[0];
pos = 0;
for(int j=1; j<frames; j++) {
if(future[j] > max) {
max = future[j];
pos = j;
}
}
}
memory[pos] = pages[i];
page_faults++;
}
}
printf("\nOptimal Algorithm:\n");
printf("Total page faults: %d\n", page_faults);
}