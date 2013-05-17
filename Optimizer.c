/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2013                              *
 *  Authors: Ulrich Kremer                   *
 *           Hans Christian Woithe           *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;
	Instruction *instr1, *instr2, *instr3;
	int opt_flag;
	opt_flag = 0;

	head = ReadInstructionList(stdin);
	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}

    	instr1 = head;
	instr2 = instr1->next;
	instr3 = instr2->next;
  	
	int x, y, z;

	while (instr3 != NULL) {	    
	  if (instr1->opcode == 1 && instr2->opcode == 1 && 
	     (instr3->opcode == 3 ||  instr3->opcode == 4 
	     || instr3->opcode == 5)) {
	    
	    opt_flag = 1;
	    x = instr1->field2;
	    y = instr2->field2;
	    
	    instr1->field1 = instr3->field1;

	    if (instr3->opcode == 3) {
	       	z = x+y;
		instr1->field2 = z;
	     }
	    else if (instr3->opcode == 4) {
		z = x-y;
		//printf("%d,%d,%d\n", x, y, z);
		instr1->field2 = z;
		//printf("%d,%d,%d\n",instr1->opcode, instr1->field1, instr1->field2);
		
	     }
	    else if (instr3->opcode == 5) {
		z = x*y;
		instr1->field2 = z;
	      }
	    else {
		ERROR("Unexpected instruction/n");
		exit(EXIT_FAILURE);
	      }
  	  }
	  /*  
	printf("Before sliding window\n");
	printf("%d,%d,%d\n", instr1->opcode, instr1->field1, instr1->field2);
	printf("%d,%d,%d\n", instr2->opcode, instr2->field1, instr2->field2);
	printf("%d,%d,%d,%d\n", instr3->opcode, instr3->field1, instr3->field2,
	instr3->field3);
	printf("Opt_flag is %d\n", opt_flag);
	  */
	  
	
	
	if (opt_flag == 0) {
	  instr1 = instr1->next;
	  instr2 = instr2->next;
	  instr3 = instr3->next;
	}
	else {
	  Instruction *temp1, *temp2;
	  temp1 = instr2;
	  temp2 = instr3;
	  free(temp1);
	  free(temp2);
	  instr1->next = instr3->next;
	  instr1 = instr1->next;
	  instr2 = instr1->next;
	  instr3 = instr2->next;
	  opt_flag = 0;
	  
	}
	
	/*
	printf("After sliding window:\n");
	printf("%d,%d,%d\n", instr1->opcode, instr1->field1, instr1->field2);
	printf("%d,%d,%d\n", instr2->opcode, instr2->field1, instr2->field2);
	printf("%d,%d,%d\n", instr3->opcode, instr3->field1, instr3->field2);
	*/
    }
		 
	PrintInstructionList(stdout, head);
	DestroyInstructionList(head);
	return EXIT_SUCCESS;
}
