
#include <stdio.h>

int main()
{
	int count = 0;
	char str[] = "AAA AAD AAM AAS ADC ADD AND CALL CBW CLC CLD CLI CMC CMP CMPSB CMPSW CWD DAA DAS DEC DIV HLT IDIV IMUL IN INC INT INTO IRET JA JAE JB JBE JC JCXZ JE JG JGE JL JLE JMP JNA JNAE JNB JNBE JNC JNE JNG JNGE JNL JNLE JNO JNP JNS JNZ JO JP JPE JPO JS JZ LAHF LDS LEA LES LODSB LODSW LOOP LOOPE LOOPNE LOOPNZ LOOPZ MOV MOVSB MOVSW MUL NEG NOP NOT OR OUT POP POPA POPF PUSH PUSHA PUSHF RCL RCR REP REPE REPNE REPNZ REPZ RET RETF ROL ROR SAHF SAL SAR SBB SCASB SCASW SHL SHR STC STD STI STOSB STOSW SUB TEST XCHG XLATB XOR";
	for (size_t i = 0; str[i]!='\0'; i++)
	{
		if (str[i]==' ')
		{
			count++;
		}
	}
	printf("\n%d", ++count);
}

