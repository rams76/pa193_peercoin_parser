/* Programe: This programe reads the Magic number of peercoin block verifyies it,
reades the size of the block and extracts the block for furhter processing in raw format.

Programmer :

Date : 5th Oct 2017

Ver : 00

Input : Name of the raw block file
output : Verification of magic number, block size and raw block

*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGICNUMBER 0xE6E8E9E5;

int block_Verifier(FILE *, int *, int *);

int main()

{


	FILE *inFileP;
	FILE *outFileP;
	char tempBuffer[255];
	char inFileName[255];
	char outFileName[255];
	char flag = 'Y';
	int blockNum[10];
	int blockPos[10];
	int blockLength[10];
	int num_of_Blocks;
	
	printf("\n Enter the raw file name : ");
	scanf("%s",tempBuffer);
	strncpy_s(inFileName, 255, tempBuffer, 255);

	inFileP= fopen("blocks.dat", "rb");
	if (inFileP == NULL)
	{
		printf("\n The input file could not be opended \n");
		return -1;
	}
	num_of_Blocks=block_Verifier(inFileP, blockNum, blockPos);
	if (num_of_Blocks > 0)
	{
		printf("\nBlock extraction is sucessfull\n");
	}
	else
	{
		printf("\No block could be extraced");
		return(0);
	}

	for (int i = 0; i < num_of_Blocks; i++)
	{
		printf("\n Block Number: %d,  Starting position: %d",blockNum[i],blockPos[i]);
		

	}
	

}

int block_Verifier(FILE *inF,int *bNum, int *bPos)
{
	
	int magicNumber=0; // Vraible to read the magic number from the file
	int blockLength=0;
	int blockCount=0; // Variable to store the number of blocks obtained in file
	int byteRead=0;
	
	char flag = 'Y';
	do
	{
		byteRead = fread(&magicNumber, 4, 1, inF);
		printf("\n Number of byte read %d",byteRead);
		if (byteRead < 1)
		{
			flag = 'N';
			magicNumber = 0;
		}

		{
			if (magicNumber == 0xE5E9E8E6)
			{
				
				blockCount++;
				*(bNum + (blockCount - 1)) = blockCount;
				*(bPos + (blockCount - 1)) = ftell(inF);
				printf("\nThe magic number is found in the file");
				fread(&blockLength,1,4,inF);
				//convLittleEndian(&blockLength);
				printf("\nThe length of the block is : %d", blockLength);
				fseek(inF, blockLength, SEEK_CUR);
			}

		}
	} while (flag == 'Y');
	return (blockCount);
}



int convLittleEndian(int *data)
{
	int num = *data;
	int b0, b1, b2, b3, b4, b5, b6, b7;
	int res = 0;

	b0 = (num & 0xf) << 28;
	b1 = (num & 0xf0) << 24;
	b2 = (num & 0xf00) << 20;
	b3 = (num & 0xf000) << 16;
	b4 = (num & 0xf0000) << 12;
	b5 = (num & 0xf00000) << 8;
	b6 = (num & 0xf000000) << 4;
	b7 = (num & 0xf0000000) << 4;

	res = b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7;
	*data = res;
	printf("%d\n", res);

}