#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
unsigned int csize;
unsigned int fsize;
//ѡ��������
typedef struct choice {
	int id;              //���
	char topic[1000];    //���
	char A[1000];        //ѡ��  
	char B[1000];
	char C[1000];
	char D[1000];
	char answer;         //��  
	struct choice* next;
}Choice;
//����ѡ����ڵ�
typedef struct list_coice {


	Choice* head;
	Choice* tail;
}List_choice;
//���������
typedef struct fill {
	int num;             //��Ŀ���
	char topic[1000];    //���
	char answer[1000];   //�� 
	struct fill* next;
}Fill;
List_choice* Clist;

//��ӡ�˵�
int print_menu();
//��ȡ�ļ�
void read_file();
//���һ���µ�ѡ����ڵ�
List_choice* CreateNode(void* input);
//���µ�ѡ����ڵ����
List_choice* ListInsert(List_choice* p, Choice* new);
//��ѡ����洢���ļ�
void add_choice_file(Choice* node);
//���ѡ����
void add_choice(List_choice* pchoice);
//��������
void add_fill();
int main()
{
	csize = 0;
	List_choice pchoice;
	pchoice.head = pchoice.tail = NULL;
	while (true) {
		switch (print_menu())
		{
		case 0:
			break;
		case 1:
		{
			printf("1.ѡ���� 2.�����:");
			int num;
			scanf("%d", &num);
			if (num == 1) {
				add_choice(&pchoice);
			}
			else if (num == 2) {
				add_fill();
			}
		}
		break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
		system("pause");//��ͣ
		system("cls");//����
	}
	return 0;
}
int print_menu()
{
	printf("\n\n\t\t��ӭʹ���Ծ����ϵͳ\n\n");
	printf("\t�˵�\n\n");
	printf("\t�����Ŀ------------------------1\n");
	printf("\tɾ����Ŀ------------------------2\n");
	printf("\t����ȫ����Ŀ--------------------3\n");
	printf("\tɾ��ȫ����Ŀ--------------------4\n");
	printf("\t�޸���Ŀ------------------------5\n");
	printf("\t�����ѯ------------------------6\n");
	printf("\tͳ����Ŀ����--------------------7\n");
	printf("\t��ѯ��ɺ��ؼ��ʵ���Ŀ����------8\n");
	printf("\t��������Ծ�ʹ�--------------9\n");
	printf("\t�˳�ϵͳ------------------------0\n\n");
	printf("��ѡ���ܣ�");
	int num = -1;//��ʼ�����Ҳ�Ӱ���������
	scanf("%d", &num);
	return num;
}
List_choice* CreateNode(void* input)
{
	List_choice* p = (List_choice*)malloc(sizeof(List_choice));
	if (p == NULL) {
		printf("malloc ERROR!\n");
		return NULL;
	}
	// ��ʼ���ڴ�ռ�Ϊ0��ȷ����Ա������ʼ״̬��ȷ
	memset(p, 0, sizeof(List_choice));
	// ����input��ʱδ�õ����ɸ��ݺ�����չ����������Ŀǰ�Ȱ�ԭ�߼�����
	p->head = NULL;
	p->tail = NULL;
	return p;
}
List_choice* ListInsert(List_choice* p, Choice* new)
{
	if (p == NULL) {
		printf("���������ָ��Ϊ�գ��޷�����ڵ�\n");
		return NULL;
	}
	if (p->head == NULL) {
		// �������Ϊ�գ��½ڵ����ͷ�ڵ�Ҳ��β�ڵ�
		p->head = p->tail = new;
	}
	else {
		// ���½ڵ���뵽β�ڵ���棬������β�ڵ�ָ��
		p->tail->next = new;
		p->tail = new;
	}
	return p;
}
void read_file()
{
	FILE* choicefile = fopen("D:\\choice.txt", "a+");
	if (choicefile == NULL) {
		printf("��ȡѡ������ⷢ������");
		return;
	}//load
	Clist = CreateNode(NULL);
	List_choice* C = Clist;
	while (1) {
		char buffer[1000];
		Choice* c = (Choice*)malloc(sizeof(Choice));
		if (c == NULL)
		{
			printf("ָ�벻����");
		}
		if (fscanf(choicefile, "%X", &c->id) == EOF)
			break;
		fgetc(choicefile);//ˢ�»���
		fgets(buffer, sizeof(buffer), choicefile);
		strcpy(c->topic, buffer);
		fgets(buffer, sizeof(buffer), choicefile);
		strcpy(c->A, buffer);
		fgets(buffer, sizeof(buffer), choicefile);
		strcpy(c->B, buffer);
		fgets(buffer, sizeof(buffer), choicefile);
		strcpy(c->C, buffer);
		fgets(buffer, sizeof(buffer), choicefile);
		strcpy(c->D, buffer);
		c->answer = fgetc(choicefile);
		Clist = ListInsert(Clist, c);
		csize = c->id;
	}
	fclose(choicefile);
	Clist = C;
}
void add_choice_file(Choice* node)
{
	read_file();
	node->id = ++csize;
	FILE* output = fopen("D:\\choice.txt", "a");
	if (output) {
		fprintf(output, "%08X\n", node->id);
		fprintf(output, "%s\n", node->topic);
		fprintf(output, "A:%s\n", node->A);
		fprintf(output, "B:%s\n", node->B);
		fprintf(output, "C:%s\n", node->C);
		fprintf(output, "D:%s\n", node->D);
		fprintf(output, "��ȷ�𰸣�%c\n", node->answer);
		printf("��ӳɹ���\n");
		fclose(output);
	}
	
	else {
		printf("д�ļ�ʧ�ܣ�\n");
	}
}
void add_choice(List_choice* pchoice)
{
	//Ϊһ��ѡ����ڵ㶯̬�����ڴ�
	Choice* node = (Choice*)malloc(sizeof(Choice));
	if (!node) {
		printf("malloc failed\n");
		return;
	}
	node->next = NULL;
	//����ѡ������Ϣ
	printf("��������Ŀ��");
	scanf("%s", node->topic);
	getchar();
	printf("������ѡ��A��");
	scanf("%s", node->A);
	getchar();
	printf("������ѡ��B��");
	scanf("%s", node->B);
	getchar();
	printf("������ѡ��C��");
	scanf("%s", node->C);
	getchar();
	printf("������ѡ��D��");
	scanf("%s", node->D);
	getchar();
	printf("������𰸣�");
	scanf("%c", &node->answer);
	//�Դ𰸸�ʽ���м��
	while (node->answer != 'A' && node->answer != 'B' && node->answer != 'C' && node->answer != 'D') {
		printf("����Ĵ𰸸�ʽ����ȷ�����������루ֻ������A��B��C��D����һ������");
		scanf(" %c", &node->answer);
	}
	//���뵽List_choice������
	if (pchoice->tail)
	{
		pchoice->tail->next = node;
		pchoice->tail = node;
	}
	else
	{
		pchoice->head = pchoice->tail = node;
	}
	add_choice_file(node);
}
void add_fill()
{

}


