#include<stdio.h>
#include<string.h>

main()
{
	//declaration
	FILE *fp;
	fp = fopen("obj_code.txt","r");

	int i, j, sa1;

	char name[20],name1[20],line[50],sa[10];

	printf("Enter program name: ");
	scanf("%s", name);

	fscanf(fp,"%s",line);
	for(i=0,j=2;i<6,j<8;i++,j++)
	{
		name1[i] = line[j]; 
	}
	name1[i] = '\0';
	printf("Name from object program : %s\n", name1);
	
	if(strcmp(name,name1)==0)//verify program name
	{
		while(!feof(fp))
		{
			fscanf(fp,"%s",line);//read next object program record
			
			if(line[0] == 'T')//find starting address for each text record
			{
				for(i=0,j=2;i<6,j<8;i++,j++)
				{
					sa[i] = line[j]; 
				}
				sa[i] = '\0';
				sa1 = atoi(sa);
				i = 12;
				while(line[i]!='$')
				{
					if(line[i]!='^')
					{
						printf("00%d\t%c%c\n", sa1,line[i],line[i+1]);
						sa1+=1;//move object code to specified location in memory 
						i+=2;
					}
					else
						i+=1;
				}
			}
			else if(line[0] == 'E')
				break;//jump to specified location in END record
		}
	}
}