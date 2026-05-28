/*  NAME	: SIVA KUMAR P
 *  DATE	: 30/10/2025
 *  DESCRIPTION	: The MP3 Tag Reader is a command-line program developed in C to read and modify ID3 metadata from 
 		  MP3 audio files.It enables users to view details such as Title, Artist, Album, Year, Genre, and Comments,
		  and also update specific fields when needed. The project highlights key concepts like file handling, 
		  string manipulation,and command-line argument processing, offering practical understanding of 
		  how metadata is stored and managed in MP3 files.*/

#include"Mp3_header.h"
int main(int argc,char* argv[])
{
	char tag_names[6][10] = {"Title","Artist","Album","Year","Music","Comment"};
	char tags[6][3] = {"-t","-a","-A","-y","-C","-c"};
	// validate command line arguments
	if(argc == 3)
	{
		if(validate_view(argc,argv))
		{
			view_tags(argc,argv,tag_names);
		}
	}
	else if(argc == 5)
	{
		if(validate_edit(argc,argv,tags))
		{
			int tag_num; 
			tag_num = find_edit_tag(argv,tags);// To determine which tag needs to be edited
			edit_tag(argc,argv,tag_num,tag_names);
		}
	}
	else if(argc == 2)
	{
		if(!(strcmp(argv[1],"--help")))
		{
			USAGE;//macro
		}
		else
		{
			ERROR;//macro
		}
	}
	else
	{
		ERROR;
	}
}
