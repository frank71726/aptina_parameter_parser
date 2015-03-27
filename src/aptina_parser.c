#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int __attribute__((unused))  argc , char **argv)
{
    int cnt=0,total_item=0,total_data=0;
	FILE *psource = NULL;
	FILE *phiaddr = NULL;
	FILE *ploaddr = NULL;
	FILE *pdata = NULL;
	FILE *pnum = NULL;

	char buffer[220], filename[220];

	strcpy(filename,argv[1]);
	strcat(filename,".hi");
	phiaddr = fopen(filename, "w");
	if(phiaddr == NULL)
	{
		fprintf(stderr, "open phiaddr file fail!\n");
		return -1;
	}
	else
		fprintf(stderr, "open phiaddr file :%s\n", filename);

	strcpy(filename,argv[1]);
	strcat(filename,".lo");
	ploaddr = fopen(filename, "w");
	if(ploaddr == NULL)
	{
		fprintf(stderr, "open ploaddr file fail!\n");
		return -1;
	}
	else
		fprintf(stderr, "open ploaddr file :%s\n", filename);

	strcpy(filename,argv[1]);
	strcat(filename,".data");
	pdata = fopen(filename, "w");
	if(pdata == NULL)
	{
		fprintf(stderr, "open pdata file fail!\n");
		return -1;
	}
	else
		fprintf(stderr, "open pdata file :%s\n", filename);

	strcpy(filename,argv[1]);
	strcat(filename,".num");
	pnum = fopen(filename, "w");
	if(pdata == NULL)
	{
		fprintf(stderr, "open pnum file fail!\n");
		return -1;
	}
	else
		fprintf(stderr, "open pnua file :%s\n", filename);

	/*--------------------------------------------------------------------*/
	strcpy(filename,argv[1]);
	strcat(filename,".txt");
	psource = fopen(filename, "r");
	if(psource == NULL) {
		fprintf(stderr, "open psource file fail!\n");
		return -1;
	}
	else
		fprintf(stderr, "open psource file :%s\n", filename);
	/*--------------------------------------------------------------------*/
 	while( fgets(buffer,200, psource) )
	{
		printf("---%s",buffer);

		total_item++;

        /* get hi-byte address*/
 		printf("phiaddr=0x%c%c  ",buffer[7], buffer[8]);
		fprintf(phiaddr, "0x%c%c, ", buffer[7], buffer[8]);
        /* get lo-byte address*/
		printf("ploaddr=0x%c%c  ",buffer[9], buffer[10]);
		fprintf(ploaddr, "0x%c%c, ", buffer[9], buffer[10]);
        /* get data*/
		if( buffer[17] == 0x20 )/* ascii code space = 0x20*/
		{/* only one byte data*/
			total_data += 1;
			printf("pdata=0x%c%c  ",buffer[15], buffer[16]);
			fprintf(pdata, "0x%c%c, ", buffer[15], buffer[16]);

			printf("pnum=0x%c%c  ",'0', '1');
			fprintf(pnum, "0x%c%c, ",'0', '1');
		} else
		{/* have two bytes data*/
			total_data += 2;
			printf("pdata=0x%c%c  ",buffer[15], buffer[16]);
			fprintf(pdata, "0x%c%c, ", buffer[15], buffer[16]);
			printf("pdata=0x%c%c  ",buffer[17], buffer[18]);
			fprintf(pdata, "0x%c%c, ", buffer[17], buffer[18]);

			printf("pnum=0x%c%c  ",'0', '2');
			fprintf(pnum, "0x%c%c, ",'0', '2');
		}

		printf("\n");/* new line at screen*/

		if((total_data % 10) == 0)/* store up ten items at each line*/
			fprintf(pdata, "\n");

		cnt++;
		if(cnt == 10)/* store up ten items at each line*/
		{
			fprintf(phiaddr, "\n");
			fprintf(ploaddr, "\n");
			fprintf(pnum, "\n");
			cnt = 0 ;
		}
	}

	printf("total item : %d\n",total_item);
	printf("total data : %d\n",total_data);

	fclose(phiaddr);
	fclose(ploaddr);
	fclose(pdata);
	fclose(pnum);
	fclose(psource);
	return 1;
}


