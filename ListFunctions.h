
#define MARKS_AMOUNT 3

typedef struct student {
	char schSurname[21];
	char schName[21];
	char schDate[11];
	int nMarks[MARKS_AMOUNT];
	double dblAverageMark;
	struct student* next;
} student;

//Prototypes--------------------------------------------------------------------------------------------------------

int GetListVolume(student* pHead);
void SwapStudentsList(student* pHead);
void PrintList(student* pHead);
void FreeList(student** pHead);
void PrintFileStudents(student* pHead, FILE* filePointer);
void SetListFromFile(student* pCur, FILE* filePointer, student** pHead);
void BubbleSortList(student** pHead);
void DeleteStudentFromList(student** pHead, int nStudentNum);
void AddStudentToList(student** pHead);

//-----------------------------------------------------------------------------------------------------------------