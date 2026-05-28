#include "Mp3_header.h"
int validate_edit(int argc,char * argv[],char (*tags)[3])
{
	validate_view(argc,argv);
	for(int i=0;i<6;i++)
	{
		if(!(strcmp(argv[2],tags[i])))
		{
			return 1;
		}
	}
	ERROR;

}
int find_edit_tag(char *argv[],char (*tags)[3])
{
	for(int i=0;i<6;i++)
	{
		if(!(strcmp(argv[2],tags[i])))
		{
			return i;
		}
	}
	exit(0);
}
void edit_tag(int argc,char *argv[],int tag_num,char(*Tags)[10])
{
	printf("   --------------------------Select Edit Option-------------------------\n");
	char tags[6][5] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
	FILE * fp = fopen(argv[argc-1],"r");
	if(fp == NULL)
	{
		printf("No Such MP3 File Exist\n");
	}
	FILE * tfp = fopen("temp.mp3","w");//New file to copy data 
	char header[11];
	fread(header,sizeof(char),10,fp);
	header[10] = '\0';
	fwrite(header,sizeof(char),10,tfp);
	while(!(feof(fp)))
	{
		char Tag[5];
		fread(Tag,sizeof(char),4,fp);
		Tag[4] = '\0';
		if(!(strcmp(tags[tag_num],Tag)))//compare the tag readed from file and user input
		{
			//if tag matches tag data will get edited
			printf("--------------------------Select %s Edit Option-------------------------\n",Tags[tag_num]);
			fwrite(Tag,sizeof(char),4,tfp);
			int size;
			fread(&size,sizeof(int),1,fp);
			BE_LE((char *)&size);
			int len;
			len = strlen(argv[3])+1;
			BE_LE((char*)&len);
			fwrite(&len,sizeof(int),1,tfp);
			char trash[4];	
			fread(trash,sizeof(char),3,fp);
			trash[3] = '\0';
			fwrite(trash,sizeof(char),3,tfp);
			fwrite(argv[3],sizeof(char),strlen(argv[3]),tfp);
			fseek(fp,size-1,SEEK_CUR);
			printf("%s : %s\n",Tags[tag_num],argv[3]);
			break;
		}
		else
		{
			// if tag doesn't match same data will be copied
			fwrite(Tag,sizeof(char),4,tfp);
			int size;
			fread(&size,sizeof(int),1,fp);
			fwrite(&size,sizeof(int),1,tfp);
			BE_LE((char *)&size);
			char trash[4];
			fread(trash,sizeof(char),3,fp);
			trash[3] = '\0';
			fwrite(trash,sizeof(char),3,tfp);
			char ch;
			for(int i=0;i<size-1;i++)
			{
				fread(&ch,sizeof(char),1,fp);
				fwrite(&ch,sizeof(char),1,tfp);
			}
		}
	}
	printf("--------------------------%s Edited Successfully-------------------------\n",Tags[tag_num]);
	char ch;
	while(!(feof(fp)))//after tag data got edited remaining audio data gets copied
	{
		fread(&ch,sizeof(char),1,fp);
		fwrite(&ch,sizeof(char),1,tfp);
	}
	// removal of old file and rename new file
	remove(argv[argc-1]);
	rename("temp.mp3",argv[argc-1]);
	fclose(tfp);
}
