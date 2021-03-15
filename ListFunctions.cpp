#include <stdio.h>
#include <string.h>
#include "ListFunctions.h"

#define STUDENTS_AMOUNT 10
#define MARKS_AMOUNT 3

//-----------------------------------------------------------------------------------------------------------------
//creates and sets the list with data from file, the memory is free after ending the work
void SetListFromFile(student* pHead, FILE* filePointerIn) {
	char chStrFromFile[50];
	char* chpLimits = " ";
	char* chpPutToList;
	for (int i = 0; i < STUDENTS_AMOUNT; i++) {
		fgets(chStrFromFile, 50, filePointerIn);
		chpPutToList = strtok(chStrFromFile, chpLimits);
		strcpy(pHead->schSurname, chpPutToList);
		chpPutToList = strtok(NULL, chpLimits);
		strcpy(pHead->schName, chpPutToList);
		chpPutToList = strtok(NULL, chpLimits);
		strcpy(pHead->schDate, chpPutToList);
		chpPutToList = strtok(NULL, chpLimits);
		double dblSumOfMarks = 0;
		for (int j = 0; j < MARKS_AMOUNT; j++) {
			pHead->nMarks[j] = atoi(chpPutToList);
			dblSumOfMarks += pHead->nMarks[j];
			chpPutToList = strtok(NULL, chpLimits);
		}
		pHead->dblAverageMark = dblSumOfMarks / MARKS_AMOUNT;
		student* nextStudent = (student*)malloc(sizeof(student));
		nextStudent->next = NULL;
		pHead->next = nextStudent;
		pHead = nextStudent;
	}
}

//-----------------------------------------------------------------------------------------------------------------

void PrintFileStudents(student* pHead, FILE* filePointer) {
	student* TempList = pHead;
	int nListVolume = GetListVolume(TempList);
	if (!nListVolume) {
		fprintf(filePointer, "The list is epmty.\n");
		return;
	}
	for (int i = 0; i < nListVolume; i++) {
		fprintf(filePointer, " ____________________________________________________");
		fprintf(filePointer, "___________________________________________________\n");
		fprintf(filePointer, "|\t %s \t|\t %s      \t|\t %s \t|", TempList->schSurname, TempList->schName, TempList->schDate);
		fprintf(filePointer, "\t ");
		for (int j = 0; j < MARKS_AMOUNT; j++) {
			fprintf(filePointer, "%d ", TempList->nMarks[j]);
		}
		fprintf(filePointer, "\t|\t %.2f \t|\n", TempList->dblAverageMark);
		fprintf(filePointer, " ____________________________________________________");
		fprintf(filePointer, "___________________________________________________\n");
		TempList = TempList->next;
	}
	TempList = pHead;
}

//-----------------------------------------------------------------------------------------------------------------

int GetListVolume(student* pHead) {
	int nListVolume = 0;
	student* TempList = pHead;
	while (TempList->next) {
		nListVolume++;
		TempList = TempList->next;
	}
	TempList = pHead;
	return nListVolume;
}

//-----------------------------------------------------------------------------------------------------------------
//returns the list without deleted student
student* DeleteStudentFromList(student* pHead, int nStudentNum) {
	student* TempList = pHead;
	int nListVolume = GetListVolume(TempList);
	printf("Do you want to delete all the students that have 2, 3, 4 or 5?(1 - yes, 0 - no)\n");
	int nDeleteOption;
	scanf("%d", &nDeleteOption);
	if (nDeleteOption) {
		for (int i = 0; i < nListVolume; i++) {
			if (TempList->nMarks[0] != 1 || TempList->nMarks[1] != 1 || TempList->nMarks[2] != 1) {//if there`re only '1' marks,
				TempList = TempList->next;                                                         //the student won`t be deleted.
			}
		}
		TempList->next->next = NULL;
		PrintList(TempList);
	} else {
		if (nStudentNum - 1 == 0) {
			TempList = TempList->next;
		} else {
			for (int i = 0; i < nStudentNum - 2; i++) {
				TempList = TempList->next;
			}
			TempList->next = TempList->next->next;
			TempList = pHead;
		}
	}
	return TempList;
}

//-----------------------------------------------------------------------------------------------------------------
//returns the list with added student
student* AddStudentToList(student* pHead) {
	printf("Enter the student to add (Example:'Added Student 09.01.2021 2 2 4')\n");
	char chsStudentAdd[300];
	scanf(" %[^\t\n]s", &chsStudentAdd);
	char* chpLimits = " ";
	student StudentAdd;
	student* pStudentAdd = (student*)malloc(sizeof(student));
	pStudentAdd = &StudentAdd;
	strcpy(pStudentAdd->schSurname, strtok(chsStudentAdd, chpLimits));
	strcpy(pStudentAdd->schName, strtok(NULL, chpLimits));
	strcpy(pStudentAdd->schDate, strtok(NULL, chpLimits));
	for (int i = 0; i < MARKS_AMOUNT; i++) {
		pStudentAdd->nMarks[i] = atoi(strtok(NULL, chpLimits));
	}
	pStudentAdd->dblAverageMark = 0;
	for (int i = 0; i < MARKS_AMOUNT; i++) {
		pStudentAdd->dblAverageMark += pStudentAdd->nMarks[i];
	}
	pStudentAdd->dblAverageMark /= MARKS_AMOUNT;
	pStudentAdd->next = NULL;
	student* TempList = pHead;
	if (strcmp(pStudentAdd->schSurname, TempList->next->schSurname) < 0) {//add the student in sorted list(eng alphabet)
		pStudentAdd->next = TempList;                                     //set new student at the top of the list
		return pStudentAdd;
	}
	int nListVolume = GetListVolume(TempList);
	for (int i = 0; i < nListVolume; i++) {
		if (i == nListVolume - 1) {//add new student to the end of the list
			pStudentAdd->next = NULL;
			TempList->next = pStudentAdd;
			break;
		}
		if (strcmp(pStudentAdd->schSurname, TempList->next->schSurname) < 0) {//add new student in a sorting position
			pStudentAdd->next = TempList->next;
			TempList->next = pStudentAdd;
			break;
		} else {
			TempList = TempList->next;
		}
	}
	TempList = pHead;
	PrintList(TempList);
	return TempList;
}

//-----------------------------------------------------------------------------------------------------------------
//returns eng alphabetically sorted list
student* BubbleSortList(student* pHead) {
	student* SortList = pHead;
	student* TempList = SortList;
	int nListVolume = GetListVolume(SortList);
	printf("Do you want to leave only students that were born in autumn?(1 - yes, 0 - no)\n");
	int nSortOption;
	scanf("%d", &nSortOption);
	if (nSortOption) {
		int nStudentsMonths[STUDENTS_AMOUNT];
		char* chpLimits = ".";
		char chTempStr[30];
		for (int i = 0; i < nListVolume; i++) {
			strcpy(chTempStr, SortList->schDate);
			nStudentsMonths[i] = atoi(strtok(chTempStr, chpLimits));
			nStudentsMonths[i] = atoi(strtok(NULL, chpLimits));
			SortList = SortList->next;
		}
		SortList = pHead;                                                    //9, 10, 11 - months of autumn
		while (!((nStudentsMonths[0] == 9) || (nStudentsMonths[0] == 10) || (nStudentsMonths[0] == 11))) {
			SortList = SortList->next;
		}
		for (int i = 0; i < nListVolume - 1; i++) {
			if (!((nStudentsMonths[i + 1] == 9) || (nStudentsMonths[i + 1] == 10) || (nStudentsMonths[i + 1] == 11))) {
				SortList->next = SortList->next->next;
			} else {
				SortList = SortList->next;
			}
		}
		SortList->next = NULL;
		SortList = pHead;
	}
	int nContinueSort = 1;
	while (nContinueSort) {//stops when the list is eng alphabetically sorted
		if (strcmp(SortList->schSurname, SortList->next->schSurname) > 0) {
			SortList = SortList->next;
			TempList->next = SortList->next;
			SortList->next = TempList;
			pHead = SortList;
		}
		int nStopSort = 1;
		while (SortList->next->next->next) {
			if (strcmp(SortList->next->schSurname, SortList->next->next->schSurname) > 0) {
				nStopSort = 0;
				SwapStudentsList(SortList);
			}
			SortList = SortList->next;
		}
		if (nStopSort) {
			SortList = pHead;
			if (strcmp(SortList->schSurname, SortList->next->schSurname) > 0) {
				SortList = SortList->next;
				TempList->next = SortList->next;
				SortList->next = TempList;
				pHead = SortList;
			}
			return SortList;
		}
		SortList = pHead;
	}
}

//-----------------------------------------------------------------------------------------------------------------
//swaps the next (2-nd) with the next of the next (3-rd) student 
void SwapStudentsList(student* pHead) {
	student* TempList;
	TempList = pHead->next;
	pHead->next = pHead->next->next;
	TempList->next = TempList->next->next;
	pHead->next->next = TempList;
}

//-----------------------------------------------------------------------------------------------------------------

void PrintList(student* pHead) {
	student* TempList = pHead;
	int nListVolume = GetListVolume(TempList);
	if (!nListVolume) {
		printf("The list is epmty.\n");
		return;
	}
	for (int i = 0; i < nListVolume; i++) {
		printf(" ____________________________________________________");
		printf("___________________________________________________\n");
		printf("|\t %s \t|\t %s      \t|\t %s \t|", TempList->schSurname, TempList->schName, TempList->schDate);
		printf("\t ");
		for (int j = 0; j < MARKS_AMOUNT; j++) {
			printf("%d ", TempList->nMarks[j]);
		}
		printf("\t|\t %.2f \t|\n", TempList->dblAverageMark);
		printf(" ____________________________________________________");
		printf("___________________________________________________\n");
		TempList = TempList->next;
	}
	TempList = pHead;
}

//-----------------------------------------------------------------------------------------------------------------
//use after ending the work of program
void FreeList(student** pHead) {
	student* tmpFree = (*pHead)->next, * tmp;
	while (tmpFree != NULL) {
		tmp = tmpFree->next;
		free(tmpFree);
		tmpFree = tmp;
	}
	free(*pHead);
}

//-----------------------------------------------------------------------------------------------------------------