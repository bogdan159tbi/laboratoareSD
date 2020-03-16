typedef struct 
{
	float nota;
	char *nume;
}TStudent;

void AfiStr(void *ax)
{
	printf("%s ",*(char*)ax);
}

int cmpStr(void *a,void *b)
{
	return strcmp(*(char*)a,*(char*)b);
}

void readTStudent(TLDI s,int *lg)
{
	float nota;
	char *nume;
	printf("se citesc nume si nota\n");
	for(*lg = 0; scanf("%f",&nota) == 1; )
	{
		nume = malloc(20);
		if(!nume)
			return;
		scanf("%s",nume);
		InsDupa(s->pre,)
	}
}