#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
unsigned int csize;
unsigned int fsize;
//选择题链表
typedef struct choice {
	int id;              //编号
	char topic[1000];    //题干
	char A[1000];        //选项  
	char B[1000];
	char C[1000];
	char D[1000];
	char answer;         //答案  
	struct choice* next;
}Choice;
//链接选择题节点
typedef struct list_coice {


	Choice* head;
	Choice* tail;
}List_choice;
//填空题链表
typedef struct fill {
	int num;             //题目编号
	char topic[1000];    //题干
	char answer[1000];   //答案 
	struct fill* next;
}Fill;
List_choice* Clist;

//打印菜单
int print_menu();
//读取文件
void read_file();
//添加一个新的选择题节点
List_choice* CreateNode(void* input);
//将新的选择题节点插入
List_choice* ListInsert(List_choice* p, Choice* new);
//将选择题存储进文件
void add_choice_file(Choice* node);
//添加选择题
void add_choice(List_choice* pchoice);
//添加填空题
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
			printf("1.选择题 2.填空题:");
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
		system("pause");//暂停
		system("cls");//清屏
	}
	return 0;
}
int print_menu()
{
	printf("\n\n\t\t欢迎使用试卷管理系统\n\n");
	printf("\t菜单\n\n");
	printf("\t添加题目------------------------1\n");
	printf("\t删除题目------------------------2\n");
	printf("\t备份全部题目--------------------3\n");
	printf("\t删除全部题目--------------------4\n");
	printf("\t修改题目------------------------5\n");
	printf("\t试题查询------------------------6\n");
	printf("\t统计题目数量--------------------7\n");
	printf("\t查询题干含关键词的题目内容------8\n");
	printf("\t随机生成试卷和答案--------------9\n");
	printf("\t退出系统------------------------0\n\n");
	printf("请选择功能：");
	int num = -1;//初始化并且不影响后续输入
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
	// 初始化内存空间为0，确保成员变量初始状态正确
	memset(p, 0, sizeof(List_choice));
	// 这里input暂时未用到，可根据后续拓展需求来处理，目前先按原逻辑保持
	p->head = NULL;
	p->tail = NULL;
	return p;
}
List_choice* ListInsert(List_choice* p, Choice* new)
{
	if (p == NULL) {
		printf("传入的链表指针为空，无法插入节点\n");
		return NULL;
	}
	if (p->head == NULL) {
		// 如果链表为空，新节点既是头节点也是尾节点
		p->head = p->tail = new;
	}
	else {
		// 将新节点插入到尾节点后面，并更新尾节点指针
		p->tail->next = new;
		p->tail = new;
	}
	return p;
}
void read_file()
{
	FILE* choicefile = fopen("D:\\choice.txt", "a+");
	if (choicefile == NULL) {
		printf("读取选择题题库发生错误");
		return;
	}//load
	Clist = CreateNode(NULL);
	List_choice* C = Clist;
	while (1) {
		char buffer[1000];
		Choice* c = (Choice*)malloc(sizeof(Choice));
		if (c == NULL)
		{
			printf("指针不存在");
		}
		if (fscanf(choicefile, "%X", &c->id) == EOF)
			break;
		fgetc(choicefile);//刷新缓冲
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
		fprintf(output, "正确答案：%c\n", node->answer);
		printf("添加成功！\n");
		fclose(output);
	}
	
	else {
		printf("写文件失败！\n");
	}
}
void add_choice(List_choice* pchoice)
{
	//为一个选择题节点动态分配内存
	Choice* node = (Choice*)malloc(sizeof(Choice));
	if (!node) {
		printf("malloc failed\n");
		return;
	}
	node->next = NULL;
	//输入选择题信息
	printf("请输入题目：");
	scanf("%s", node->topic);
	getchar();
	printf("请输入选项A：");
	scanf("%s", node->A);
	getchar();
	printf("请输入选项B：");
	scanf("%s", node->B);
	getchar();
	printf("请输入选项C：");
	scanf("%s", node->C);
	getchar();
	printf("请输入选项D：");
	scanf("%s", node->D);
	getchar();
	printf("请输入答案：");
	scanf("%c", &node->answer);
	//对答案格式进行检查
	while (node->answer != 'A' && node->answer != 'B' && node->answer != 'C' && node->answer != 'D') {
		printf("输入的答案格式不正确，请重新输入（只能输入A、B、C或D其中一个）：");
		scanf(" %c", &node->answer);
	}
	//插入到List_choice链表当中
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


