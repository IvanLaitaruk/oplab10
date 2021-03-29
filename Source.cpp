#include <stdio.h>
#include <string.h>
#include "ListFunctions.h"

#define STUDENTS_AMOUNT 10
#define MARKS_AMOUNT 3

int main(){
	student* pHead = NULL;
	student* pCur = (student*)malloc(sizeof(student));
	FILE* filePointerIn = fopen("students.txt", "r");
	FILE* filePointerOut;
	SetListFromFile(pCur, filePointerIn, &pHead);
	int nListOption, nContinueWork = 1;
		while (nContinueWork){
			printf("Choose what to do with the list:\n");
			printf("1 - delete the element \n");
			printf("2 - add the element \n");
			printf("3 - print the list\n");
			printf("4 - sort the list\n");
			printf("5 - print the list in the file\n");
			scanf("%d", &nListOption);
			switch (nListOption){
			  case 1:
				printf("Choose the number of student to delete[1; %d] or 0 to continue\n", GetListVolume(pHead)+1);
				int nStudentNum;
				scanf("%d", &nStudentNum);
				DeleteStudentFromList(&pHead, nStudentNum);
				break;
			  case 2:
				  AddStudentToList(&pHead);
				break;
			  case 3:
				PrintList(pHead);
				break;
			case 4:
				BubbleSortList(&pHead);
				break;
			case 5:
				filePointerOut = fopen("WriteStudents.txt", "w");
				PrintFileStudents(pHead, filePointerOut);
				fclose(filePointerOut);
				break;
			}
			printf("Do you want to continue?(1 - yes, 0 - no)\n");
			scanf("%d", &nContinueWork);
		}
		FreeList(&pHead);
		return 0;
}

