#include "Mp3_header.h"
int validate_view(int argc,char *argv[])
{
	if(!(!(strcmp(argv[1],"-v")) || !(strcmp(argv[1],"-e"))))
	{
		printf("view 1\n");
		ERROR;
	}
	if(!(strstr(argv[argc-1],".mp3")))
	{
		printf("view 2\n");
		ERROR;
	}
	return 1;
}
void BE_LE(char * ptr)//function Big endian data into Little endian data
{
	int i=0,j=3;
	while(i<j)
	{
		char temp = ptr[i];
		ptr[i] = ptr[j];
		ptr[j] = temp;
		i++;
		j--;
	}
}
void view_tags(int argc,char *argv[],char (*tag_names)[10])
{

	FILE * fp = fopen(argv[2],"r");
	if(fp == NULL)
	{
		printf("No such Mp3 file Exist\n");
		exit(0);
	}
	char buffer[4];
	fread(buffer,sizeof(char),3,fp);
	buffer[3]='\0';
	if(strcmp(buffer,"ID3"))//check whether the file is ID3 type or not
	{
		printf("File Type Does Not Match\n");
		exit(0);
	}
	fseek(fp,7,SEEK_CUR);
	printf("-----------------------------------------------------------------------\n\n");
	printf("MP3 Tag Reader and Editor for %s\n",buffer);
	printf("-----------------------------------------------------------------------\n");
	for(int i=0;i<6;i++)
	{
		char tag[4];	
		fread(tag,sizeof(tag),1,fp);
		int size;
		fread(&size,sizeof(int),1,fp);
		BE_LE((char *)&size);
		fseek(fp,3,SEEK_CUR);
		char content[size];
		fread(content,sizeof(content)-1,1,fp);
		content[size-1] = '\0';
		printf("%s\t:\t%s\n",tag_names[i],content);
	}
	printf("-----------------------------------------------------------------------\n");
	fclose(fp);
}
