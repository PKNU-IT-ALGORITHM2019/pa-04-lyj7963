#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFFER_SIZE 200
#define numoflog 160000

typedef struct LOG {
	char *IP;
	char *time;
	char *URL;
	char *status;
}LOG;

LOG list[numoflog];
int n = 0;
int x = 0;

int read_line(FILE *fp, char str[], int n);
void sort();
void load();
void print();
int ip_compare(const void *first, const void *second);
int URL_compare(const void *first, const void *second);
int status_compare(const void *first, const void *second);
int time_compare(const void * first, const void * second);

int main()
{
	char buffer[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf_s("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "sort") == 0)
			sort();
		else if (strcmp(buffer, "print") == 0)
			print();
		else if (strcmp(buffer, "exit") == 0)
			break;
	}
	return 0;
}
int read_line(FILE *fp, char str[], int n) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n - 1)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}
void sort()
{
	char buffer[BUFFER_SIZE];
	scanf_s("%s", buffer);
	if (strcmp(buffer, "read") == 0)
		load();
	else if (strcmp(buffer, "-t") == 0) {
		qsort(list, n, sizeof(LOG), time_compare);
		x = 0;
	}
	else if (strcmp(buffer, "-ip") == 0) {
		qsort(list, n, sizeof(LOG), ip_compare);
		x = 1;
	}
	else if (strcmp(buffer, "-u") == 0) {
		qsort(list, n, sizeof(LOG), URL_compare);
		x = 2;
	}
	else if (strcmp(buffer, "-s") == 0) {
		qsort(list, n, sizeof(LOG), status_compare);
		x = 3;
	}
	else return;
}
void load() 
{ 
	char fileName[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	scanf_s("%s", fileName);
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	read_line(fp, buffer, BUFFER_SIZE);
	while (read_line(fp, buffer, BUFFER_SIZE) != 0) {
		list[n].IP = strdup(strtok(buffer, ","));
		list[n].time = strdup(strtok(NULL, ","));
		list[n].URL = strdup(strtok(NULL, ","));
		list[n].status = strdup(strtok(NULL, ","));
		n++;
	}
	fclose(fp);
}
int time_compare(const void *first, const void *second)
{
	int a_month, b_month;
	LOG *pa = (LOG*)first;
	LOG *pb = (LOG*)second;

	char *buf1 = strtok(strdup(pa->time), "/, :");
	char *buf2 = strtok(NULL, "/, :");
	char *buf3 = strtok(NULL, "/, :");
	char *buf4 = strtok(NULL, "");
	char *buf5 = strtok(strdup(pb->time), "/, :");
	char *buf6 = strtok(NULL, "/, :");
	char *buf7 = strtok(NULL, "/, :");
	char *buf8 = strtok(NULL, "");

	if (strcmp(buf3, buf7) != 0) return strcmp(buf3, buf7);

	if (strcmp(buf2, "Jan")) a_month = 1;
	else if (strcmp(buf2, "Feb")) a_month = 2;
	else if (strcmp(buf2, "Mar")) a_month = 3;
	else if (strcmp(buf2, "Nov")) a_month = 11;
	else if (strcmp(buf2, "Dec")) a_month = 12;
	if (strcmp(buf6, "Jan")) b_month = 1;
	else if (strcmp(buf6, "Feb")) b_month = 2;
	else if (strcmp(buf6, "Mar")) b_month = 3;
	else if (strcmp(buf6, "Nov")) b_month = 11;
	else if (strcmp(buf6, "Dec")) b_month = 12;

	if (a_month > b_month) return 1;
	else if (a_month < b_month) return -1;

	if (strcmp(buf1, buf5) != 0) return strcmp(buf1, buf5);
	return  strcmp(buf4, buf8);

}
int ip_compare(const void *first, const void *second)
{
	LOG *pa = (LOG*)first;
	LOG *pb = (LOG*)second;

	return strcmp(pa->IP, pb->IP);
}
int URL_compare(const void *first, const void *second)
{
	LOG *pa = (LOG*)first;
	LOG *pb = (LOG*)second;

	return strcmp(pa->URL, pb->URL);
}
int status_compare(const void *first, const void *second)
{
	LOG *pa = (LOG*)first;
	LOG *pb = (LOG*)second;

	return strcmp(pa->status, pb->status);
}
void print()
{
	if (x == 0)
		for (int i = 0; i < n; i++)
			printf("%s\n	IP: %s\n	URL: %s\n	Status: %s\n", list[i].time, list[i].IP, list[i].URL, list[i].status);
	else if (x == 1)
		for (int i = 0; i < n; i++)
			printf("%s\n	Time: %s\n	URL: %s\n	Status: %s\n", list[i].IP, list[i].time, list[i].URL, list[i].status);
	else if (x == 2)
		for (int i = 0; i < n; i++)
			printf("%s\n	Time: %s\n	IP: %s\n	Status: %s\n", list[i].URL, list[i].time, list[i].IP, list[i].status);
	else
		for (int i = 0; i < n; i++)
			printf("%s\n	Time: %s\n	IP: %s\n	URL: %s\n", list[i].status, list[i].time, list[i].IP, list[i].URL);
}