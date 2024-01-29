#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	int locctr,length,len,op, start,pgrm_len,flag;
	char label[10], opcode[10], operand[10], code[10],ch;
	FILE *f1, *f2, *f3, *f4,*f5;
	f1 = fopen("input.txt","r");
	f2 = fopen("optab.txt","r");
	f3 = fopen("symtab.txt","wb+");
	f4 = fopen("output.txt","wb+");
    f5 = fopen("length.txt","wb+");
	
	fscanf(f1,"%s%s%x",label,opcode,&op);
	
	if(strcmp(opcode,"START") == 0){
		
		start = op;
		locctr = start;
		fprintf(f4,"\t%s\t%s\t%x\n", label, opcode, op);
		fscanf(f1,"%s%s%s",label,opcode,operand);
	}
	else
		locctr = 0;
	
	while(strcmp(opcode,"END") != 0){
		fprintf(f4,"%x\t",locctr);
		
		if(strcmp(label,"-") != 0){
			fprintf(f3,"%s\t%x\n",label, locctr);
		}
		
		rewind(f2);
		flag = 0;
		while(!feof(f2)){
			fscanf(f2,"%s",code);
			if(strcmp(opcode,code) == 0){
				locctr = locctr + 3;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
		if(strcmp(opcode,"WORD") == 0){
			locctr = locctr + 3;
		}
		else if(strcmp(opcode,"RESW") == 0){
			locctr = locctr + 3 * atoi(operand);
		}
		else if(strcmp(opcode,"RESB") == 0){
			locctr = locctr + atoi(operand);
		}
		else if(strcmp(opcode,"BYTE") == 0){
			
			locctr+=strlen(operand)-3; 
		}
		}
		fprintf(f4,"%s\t%s\t%s\n",label,opcode,operand);
		fscanf(f1,"%s%s%s",label,opcode,operand);
	}
	
	fprintf(f4,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
  pgrm_len = locctr - start;
 
	printf("\nThe length of the program is:%d\n",pgrm_len);
  fprintf(f5,"%d",pgrm_len); 

  printf("\n\nThe contents of symtab :\n\n");
  fseek(f3,0,SEEK_SET);
  while((ch = fgetc(f3))!=EOF)
    printf("%c",ch); 

  printf("\n\nThe contents of intermediate file :\n\n");
  fseek(f4,0,SEEK_SET);
  while((ch = fgetc(f4))!=EOF)
    printf("%c",ch);

   
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}