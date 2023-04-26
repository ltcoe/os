#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 100
#define MAX_RESOURCES 100
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];
int num_processes, num_resources;
bool is_safe()
{
int work[MAX_RESOURCES];
int i, j, k;
for (i=0; i<num_resources; i++)
{
work[i] = available[i];
}
for(i=0; i<num_processes; i++)
{
if (finish[i]) continue;
bool can_allocate = true;
for (j=0;j<num_resources; j++)
{
if (need[i][j]>work[j])
{
can_allocate = false;
break;
}
}
if (can_allocate) {
for (j=0;j<num_resources; j++)
{
work[j] += allocation[i][j];
}
finish[i] = true;
i=-1;
}
}
for (i=0; i<num_processes; i++)
{
if (!finish[i]) {
return false;
}
}
return true;
}
bool request_resources(int pid, int request[]) {
int i;
for (i=0; i<num_resources; i++) { if (request[i]> need[pid][i]) {
return false;
}
}
for (i=0; i<num_resources; i++) { if (request[i]> available[i]) {
return false;
}
}
for (i=0; i<num_resources; i++)
{
available[i]=request[i];
allocation[pid][i] += request[1];
need[pid][i]-request[i];
}
if (is_safe())
{
return true;
} else {
for (i=0; i<num_resources; i++)
{
available[i] += request[i];
allocation[pid][i] = request[i];
need[pid][i] += request[i];
}
return false;
}
}
int main(){
int i, j;
printf("Enter the number of processes: ");
scanf("%d", &num_processes);
printf("Enter the number of resources: ");
scanf("%d", &num_resources);
printf("Enter the maximum need of each process for each resource:\n");
for (i=0; i<num_processes; i++) {
printf("Process %d:\n", i);
for (j=0;j<num_resources; j++)
{ scanf("%d", &maximum[i][j]);
need[i][j]=maximum[i][j];
}
finish[i]= false;
}
printf("Enter the number of available resources: \n");
for (i=0; i<num_resources; i++)
{
scanf("%d", &available[i]);
}
int pid;
int request[MAX_RESOURCES];
while (true) {
printf("Enter the process ID and the requested resources (-1 to exit): \n"); scanf("%d",
&pid);
if (pid==-1){
break;
}
if (pid <0 || pid >= num_processes) { printf("Invalid process ID.\n"); continue;
}
for (i=0; i<num_resources; i++) { scanf("%d", &request[i]);
}
if (request_resources(pid, request)) { printf("Request granted.\n");
}
else
{
printf("Request denied.\n");
}
}
return 0;
}