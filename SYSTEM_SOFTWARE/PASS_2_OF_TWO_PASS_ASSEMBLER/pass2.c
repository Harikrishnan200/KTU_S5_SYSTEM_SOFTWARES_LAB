#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int main(){

	char a[10],ad[10],label[10],opcode[10],operand[10],symbol[10],ch,op[10], ml_equ[10];
	int st,diff,i,address,add,len,actual_len,pgm_len,prevaddr,j=0, start = 0, f;
	
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	fp1 = fopen("ASSMLIST.DAT","wb+");//assembly listing
	fp2 = fopen("SYMTAB.DAT","r");//SYMTAB
	fp3 = fopen("INTERMEDIATE.DAT","r");//intermediate file
	fp4 = fopen("OBJCODE.DAT","wb+");//object code
	fp5 = fopen("OPTAB.DAT","r");//OPTAB
	

	fscanf(fp3,"%s%s%s",label,opcode,operand);//obtain pgm length
	if(strcmp(opcode,"START")==0)
		sscanf(operand, "%d", &start);
	fscanf(fp3, "%d%s%s%s",&address,label,opcode,operand);
	while(strcmp(opcode,"END")!=0)
	{
		prevaddr=address;
		fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
	}
	fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
	pgm_len = address - start;

  	fseek(fp3,0,SEEK_SET);
  	fscanf(fp3,"%s%s%s",label,opcode,operand);//read first input line {from intermediate file}
	if(strcmp(opcode,"START")==0)
	{
		fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);//write listing line
		fprintf(fp4,"H^%s^00%s^00%d\n",label,operand,pgm_len);//write HEADER record to object pgm
		fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);//read next input line from intermediate file
		diff = prevaddr-start;
		fprintf(fp4,"T^00%d^%d",address,diff);//creating single text record
	}
	while(strcmp(opcode,"END")!=0)
	{
		//if(not a comment line)
	    //search OPTAB for OPCODE
        fseek(fp5,0,SEEK_SET);
        while(!feof(fp5))
        {
            f = 0;
            fscanf(fp5,"%s%s",op,ml_equ);
            if(strcmp(opcode,op)== 0)//opcode found
            {
                f = 1;
                fseek(fp2,0,SEEK_SET);
                
                if(operand!=NULL)//if operand exits
                {
                    fscanf(fp2, "%s%d", symbol, &add);
                    while(strcmp(operand,symbol)!=0)//search SYMTAB for OPERAND
			            fscanf(fp2,"%s%d",symbol,&add);
                }
                else
                	add = 0000;

                fprintf(fp1,"%d\t%s\t%s\t%s\t%s%d\n",address,label,opcode,operand,ml_equ,add);
			    fprintf(fp4,"^%s%d",ml_equ,add);
                break;
            }
        }
        if(f==0)
        {
			if(strcmp(opcode,"BYTE")==0)
			{	
				fprintf(fp1,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
				len=strlen(operand)-3;
				fprintf(fp4,"^");
				for(i=2;i<(len+2);i++)
				{
					//itoa(operand[i],ad,16);
					fprintf(fp1,"%d",operand[i]);
					fprintf(fp4,"%d",operand[i]);
				}
				fprintf(fp1,"\n");
			}
			else if(strcmp(opcode,"WORD")==0)
			{
				//itoa(atoi(operand),a,10);
				fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,operand);
				fprintf(fp4,"^00000%s",operand);
			}
			else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))
				fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
		}

   		fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);//read next input line
  	}
  fprintf(fp4,"\nE^00%d",start);//write END record -> object pgm
  fprintf(fp1,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);//write last listing line
  printf("\nIntermediate file is converted into object code");

//display output in console
  printf("\n\nThe contents of Intermediate file:\n\n\t");
  fseek(fp3,0,SEEK_SET);
  while((ch = fgetc(fp3))!=EOF)
   printf("%c",ch);

  printf("\n\nThe contents of Symbol Table :\n\n");
  fseek(fp2,0,SEEK_SET);
  while((ch = fgetc(fp2))!=EOF)
   printf("%c",ch);

  printf("\n\nThe contents of assembly listing file :\n\n");
  fseek(fp1,0,SEEK_SET);
  while((ch = fgetc(fp1))!=EOF)
   printf("%c",ch);

  printf("\n\nThe contents of Object code file :\n\n");
  fseek(fp4,0,SEEK_SET);
  while((ch = fgetc(fp4))!=EOF)
   printf("%c",ch);
  printf("\n");
  fcloseall();    //comment fcloseall() if shows error
}