#include<stdio.h>
#include<string.h>

void main()
{
	FILE *f1,*f2,*f3,*f4,*f5;
	f1 = fopen("input.txt","r");
	f2 = fopen("NAMTAB","r");
	f3 = fopen("DEFTAB","r");
	f4 = fopen("ARGTAB","w+");
	f5 = fopen("output.txt","w+");

	int len,i;

	char label[10],opcode[10],operand[10],name[10],def_opcode[10],def_operand[10],arg[10];

	fscanf(f1,"%s%s%s",label,opcode,operand);//read first input line
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(opcode,"MACRO")==0)
		{
			fscanf(f1,"%s%s%s",label,opcode,operand);//read next input line
			while(strcmp(opcode,"MEND")!=0)
				fscanf(f1,"%s%s%s",label,opcode,operand);//read next input line
		}
		else
		{
			fscanf(f2,"%s",name);
			if(strcmp(opcode,name)==0)//search NAMTAB for opcode ie EX1 N1,N2
			{
				//insert operand into ARGTAB
				len = strlen(operand);
				for(i=0;i<len;i++)
				{
					if(operand[i]!=',')
						fprintf(f4,"%c", operand[i]);
					else
						fprintf(f4,"\n");
				}
				fseek(f4,SEEK_SET,0);
				fseek(f2,SEEK_SET,0);

				fscanf(f3,"%s%s",def_opcode,def_operand);//read next row of DEFTAB
				fprintf(f5, ".\t%s\t%s\n", def_opcode,operand);//for replacing EX1 &A,&B to EX1 N1,N2

				fscanf(f3,"%s%s",def_opcode,def_operand);//read next row of DEFTAB
				while(strcmp(def_opcode,"MEND")!=0)
				{
					if(def_operand[0] == '&')
					{
						//search ARGTAB for argument
						fscanf(f4,"%s",arg);
						fprintf(f5, "-\t%s\t%s\n", def_opcode, arg);
					}
					else
						fprintf(f5, "-\t%s\t%s\n", def_opcode, def_operand);
					fscanf(f3,"%s%s",def_opcode,def_operand);//read next row of DEFTAB

				}
			}
			else
				fprintf(f5,"%s\t%s\t%s\n", label,opcode,operand);
		}
		fscanf(f1,"%s%s%s",label,opcode,operand);//read next input line
	}
	fprintf(f5, "%s\t%s\t%s\n", label,opcode,operand);
	fcloseall();
	printf("Pass 2 of a Two pass Macro processor is sucessful.\n");
}