#ifndef Mp3_header
#define Mp3_header 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ERROR\
	printf("-------------------------------------------------------------------------\n\n");\
	printf("ERROR : ");\
	for(int i=0;i<argc;i++)\
	{\
		printf("%s ",argv[i]);\
	}\
	printf(": INVALID ARGUMENTS\n");\
	printf("USAGE :\n");\
	printf("For help please pass like : ./a.out --help\n");\
	printf("To view please pass like  : ./a.out -v mp3filename\n");\
	printf("To edit please pass like  : ./a.out -e -t/-a/-A/-y/-C/-c  mp3filename\n");\
	printf("-------------------------------------------------------------------------\n\n");\
	exit(0);\

#define USAGE\
	printf("-------------------------------------------------------------------------\n\n");\
	printf("USAGE :\n");\
	printf("To view please pass like : ./a.out -v mp3filename\n");\
	printf("To edit please pass like : ./a.out -e -t/-a/-A/-y/-C/-c  mp3filename\n");\
	printf("TAG MENU : \n");\
	printf("'-t' -> Title/Song Name\n");\
	printf("'-a' -> Artist Name\n");\
	printf("'-A' -> Album Name\n");\
	printf("'-y' -> Year\n");\
	printf("'-C' -> Content Type\n");\
	printf("'-c' -> Composer\n");\
	printf("-------------------------------------------------------------------------\n\n");\
	exit(0);\


// Functions used to Edit and View Tags of Mp3file
int validate_view(int ,char **);
int validate_edit(int ,char **,char (*)[]);
void BE_LE(char *);
void view_tags(int , char **,char (*)[]);
int find_edit_tag(char **,char (*)[]);
void edit_tag(int,char **,int,char (*)[]);


#endif
