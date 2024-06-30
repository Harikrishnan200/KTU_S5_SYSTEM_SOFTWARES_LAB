#include<stdio.h>
#include<string.h>

main(){

	FILE *f1,*f2,*f3;
	f1 = fopen("input.txt","r");
	f2 = fopen("NAMTAB","w+");
	f3 = fopen("DEFTAB","w+");

	char line[50],label[10],opcode[10],operand[10]; 

	fscanf(f1,"%s%s%s", label,opcode,operand);
	while(strcmp(opcode,"MEND")!=0)
	{
		if(strcmp(opcode,"MACRO")==0)
		{
			fprintf(f2,"%s\n",label);
			fprintf(f3, "%s\t%s\n",label,operand);
		}
		else
		{
			fprintf(f3, "%s\t%s\n",opcode,operand);
		}
		fscanf(f1,"%s%s%s",label,opcode,operand);
	}
    fprintf(f3,"%s",opcode);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	printf("\nPass 1 of Two pass Macro processor is successful.\n");
}
