
#define MARKS_AMOUNT 3

typedef struct student {
	char schSurname[100];
	char schName[100];
	char schDate[100];
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
void SetListFromFile(student* pHead, FILE* filePointer);
student* BubbleSortList(student* pHead);
student* DeleteStudentFromList(student* pHead, int nStudentNum);
student* AddStudentToList(student* pHead);

//-----------------------------------------------------------------------------------------------------------------