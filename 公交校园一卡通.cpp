#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include<cstdlib>
#define LEN sizeof(struct Node) 
using namespace std;

struct Member
{
	char id[12];
	char  item[10];
	char name[10];
	char danwei[20];
	double busFee;
	double schFee;
	int Iflost;
	int state;
};

struct Uprecharge
{
	char id[12];
	double money;
	char Date[12];
	char oper[10];
	int way;
};

struct Consume
{
	char connum[12];
	char id[12];
	char Date[12];
	double money;
	char place[12];
	char Consumer[8];
	int way;
};

typedef struct Node
{
	int item;
	double Bus;
	double Campus;
	struct Node* next;
}Node;

typedef struct Input
{
	int Way;
	double Money;
	struct Input* next;
}Input;

typedef struct Linklist
{
	char id[12];
	char  item[10];
	char name[10];
	char danwei[20];
	double Bfee;
	double Cfee;
	int Lost;
	int del;
	struct Linklist* next;
}Linklist;

double a[5] = { 0.0 }, b[5] = {0.0};
bool Password();
void showMenu();
int EnterChoice();
void changePassword();
void inputRecord();
void charge();
void schConsum();
void busConsum();
void showMember();
void Deal();
void searchInfor();
void Total();
void TotalInput();

int main()
{
	int choice;
	printf("请输入密码：");
	if (Password()) {
		showMenu();
		while ((choice = EnterChoice()) != 10) {
			switch (choice) {
			case 1:
				cout << "请修改密码：" << endl;
				changePassword();
				break;
			case 2:
				inputRecord();
				break;
			case 3:
				charge();
				break;
			case 4:
				schConsum();
				break;
			case 5:
				busConsum();
				break;
			case 6:
				showMember();
				break;
			case 7:
				Deal();
				break;
			case 8:
				searchInfor();
				break;
			case 9:
				Total();
				TotalInput();
				break;
			default:
				cout << "请输入正确序号" << endl;
				break;
			}
			cout << "请继续选择要办理的业务" << endl;
			showMenu();
		}
	}
	else cout << "密码错误！" << endl;

	return 0;
}

//判断密码 
bool Password() {
	char str[10];
	char pass[10] = {'0'};
	scanf("%s", str);
	FILE *fp;
	if ((fp = fopen("key.dat","rb"))!=NULL){//rb 读文件 
		fread(pass,sizeof(pass), 11, fp);
		if(strcmp(str, pass) == 0)  return true;
	}
	return false;
}

void showMenu() {
	cout << "1.修改密码" << endl;
	cout << "2.录入信息" << endl;
	cout << "3.充值管理" << endl;
	cout << "4.校内消费管理" << endl;
	cout << "5.公交消费管理" << endl;
	cout << "6.输出全部信息" << endl;
	cout << "7.挂失、解挂、注销管理" << endl;
	cout << "8.查找指定信息" << endl;
	cout << "9.指定信息统计" << endl;
	cout << "10.退出系统" << endl;
}

int EnterChoice() {
	int menuChoice;
	cin >> menuChoice;

	return menuChoice;
}
//1.修改密码 
void changePassword() {
	cout << "请输入十位以内的密码" << endl; 
	char str[10];
	cin >> str;
	FILE *fp;
	if ((fp = fopen("key.dat","wb"))!=NULL){ //使用wb来写文件，并且覆盖掉之前的密码 
		fwrite(str,sizeof(char),12,fp);
	}
	cout << "修改密码成功！" << endl; 
}

//2.录入信息 
void inputRecord() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	char m_id[12];
	int panduan, choose;

	if ((fPtr = fopen("card_base.dat", "ab+")) == NULL) { //在文件尾部添加新数据之后,可以由位置函数设置开始读的起始位置. 
		cout << "写入账号信息文件有误" << endl;
		exit(0);
	}
	while (1) {
		cout << "请输入编号：" << endl;
		scanf("%s", m_id);
		rewind(fPtr); //改变文件内部位置 
		panduan = 0;
		while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
			if (strlen(m_id) != 5) {
				cout << "输入了错误编号" << endl;
				panduan = 1;
				break;
			}
			if (strcmp(m_id, mem.id) == 0) {
				cout << "输入账号不能重复" << endl;
				panduan = 1;
				break;
			}
		}
		if (panduan == 0) {
			cout << "请输入种类（教工卡、学生卡、其它卡、临时卡）、姓名、单位、公交费金额、校内金额、挂失(1.正常 0.挂失)、状态(1.正常 0.注销)：" << endl;
			cin >> mem.item >> mem.name >> mem.danwei >> mem.busFee >> mem.schFee >> mem.Iflost >> mem.state;
			strcpy(mem.id, m_id);
			fseek(fPtr, 0, SEEK_END); //指向文件尾 
			fwrite(&mem, sizeof(struct Member), 1, fPtr); //将数据写入文件中，一个单元就是一个结构体 
			cout << "添加信息成功！" << endl;
		}
		cout << "是否继续录入信息： 是：1； 否：非1； 请选择：" << endl;
		cin >> choose;
		if (choose != 1) break;
	}
	fclose(fPtr);
}

//3、充值管理 
void charge() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1,1 };
	char tempID[12];
	int flag = 0, choose, i = 0;
	int transaction;

	cout << "输入要充值的编号：" << endl;
	cin >> tempID;
	if ((fPtr = fopen("card_base.dat", "rb+")) == NULL) {
		cout << "不能打开文件" << endl;
		exit(0);
	}

	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		if (strcmp(mem.id, tempID) == 0) {
			if (mem.Iflost == 0 || mem.state == 0) {
				cout << "该账号已挂失或已注销，无法进行交易" << endl; return;
			}

			while (1) {
				cout << "请选择充值类型：1、校内充值 2、公交充值" << endl;
				cin >> choose;
				if (choose == 1 || choose == 2) break;
				else cout << "请输入正确操作!" << endl;
			}

			while (1) {
				cout << "请输入交易的金额（10的倍数）" << endl;
				cin >> transaction;
				if (transaction % 10 == 0)  break;
				else cout << "请输入正确金额数" << endl;
			}
			if (choose == 1) {
				mem.schFee += transaction;
			}
			else {
				mem.busFee += transaction;
			}
			fseek(fPtr, i * sizeof(struct Member), SEEK_SET); //用i来确定单元的大小 
			fwrite(&mem, sizeof(struct Member), 1, fPtr);
			flag = 1; break;
		}
		i++;
	}

	if (flag == 0) {
		cout << "文件中没有此信息" << endl; return;
	}

	FILE* cfptr;
	if (flag == 1) {
		struct Uprecharge upre = { "", 0.0, "", "", 0 };
		if ((cfptr = fopen("card_input.dat", "ab+")) == NULL) {
			cout << "写入账号信息文件有误" << endl;
			exit(0);
		}
		cout << "充值日期、操作员" << endl;
		cin >> upre.Date >> upre.oper;
		strcpy(upre.id, tempID);
		upre.way = choose;  upre.money = transaction;
		fseek(cfptr, 0, SEEK_END);
		fwrite(&upre, sizeof(struct Uprecharge), 1, cfptr);
		cout << "充值成功！" << endl;
		fclose(cfptr);
	}

	fclose(fPtr);
}

//创建链表存储基本信息 
struct Linklist* create() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	Linklist* head = (struct Linklist*)malloc(sizeof(struct Linklist));  //创建头节点，分配内存 ,需要的内存和结构体的大小相同，malloc前进行强制类型转换（struct node*) 
	head->next = NULL; //头节点指针初始化 
	Linklist* p; //= (struct Linklist*)malloc(sizeof(struct Linklist));  //创建p节点，分配内存 
	p = head; //p节点指针赋值为头节点 
	Linklist* q;

	if ((fPtr = fopen("card_base.dat", "rb")) == NULL) {
		cout << "不能打开文件" << endl;
		exit(0);
	}

	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		q = (struct Linklist*)malloc(sizeof(struct Linklist));
		q->Bfee = mem.busFee;
		q->Cfee = mem.schFee;
		strcpy(q->id, mem.id);
		strcpy(q->danwei, mem.danwei);
		strcpy(q->item, mem.item);
		strcpy(q->name, mem.name);
		q->Lost = mem.Iflost;
		q->del = mem.state;
		p->next = q;  //插完用p保存了上一个节点，从p后插入q； 
		q->next = NULL;  //尾部指针q指向NULL 
		p = q; //p保存q节点保证p始终是最后一个节点 
	}
	fclose(fPtr);
	return head;
}

//4、校内消费管理 
void schConsum() {
	char tempID[12];
	double tempPrice;
	int flag = 0;

	cout << "输入一卡通编号、消费金额" << endl;
	cin >> tempID >> tempPrice;

	Linklist* head = create();
	Linklist* p = head;

	while (p->next != NULL) {
		if (strcmp(p->next->id, tempID) == 0) {
			if (p->next->Lost == 0 || p->next->del == 0) {
				cout << "该账号已挂失或已注销，无法进行交易" << endl; return;
			}
			if (p->next->Cfee >= tempPrice) {
				p->next->Cfee -= tempPrice;
				flag = 1; break;
			}
			else {
				cout << "一卡通校内金额不足" << endl;
				flag = 2; return;
			}
		}
		p = p->next;
	}

	if (flag == 0)  cout << "无此一卡通信息" << endl;
	
	FILE *fptr;
	p = head; 
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	fptr = fopen("card_base.dat", "wb+");
	while (p->next != NULL){
		/*if ((fptr = fopen("card_base.dat", "wb+")) == NULL) {
			cout << "写入账号信息文件有误" << endl;
			exit(0);
		}*/
	    mem.busFee = p->next->Bfee;
		mem.schFee = p->next->Cfee;
		strcpy(mem.id,p->next->id);
		strcpy( mem.danwei,p->next->danwei);
		strcpy( mem.item,p->next->item);
		strcpy( mem.name,p->next->name);
		mem.Iflost = p->next->Lost;
		mem.state = p->next->del;
		fwrite(&mem, sizeof(struct Member), 1, fptr);
		p = p->next;
	}
	fclose(fptr);

	FILE* cfptr;
	if (flag) {
		struct Consume con = { "", "", "", 0.0, "", "" };
		if ((cfptr = fopen("card_sell.dat", "ab+")) == NULL) {
			cout << "写入账号信息文件有误" << endl;
			exit(0);
		}
		cout << "请输入消费编号、消费日期、消费地点、消费人员" << endl;
		cin >> con.connum >> con.Date >> con.place >> con.Consumer;
		strcpy(con.id, tempID);
		con.money = tempPrice;
		con.way = 1;
		fseek(cfptr, 0, SEEK_SET);
		fwrite(&con, sizeof(struct Consume), 1, cfptr);
		cout << "付费成功！" << endl;
		fclose(cfptr);
	}
}

//5、公交消费管理 
void busConsum() {
	char tempID[12];
	double tempPrice;
	int flag = 0;

	cout << "输入一卡通编号、消费金额" << endl;
	cin >> tempID >> tempPrice;
	Linklist* head = create();
	Linklist* p = head;

	while (p->next != NULL) {
		if (strcmp(p->next->id, tempID) == 0) {
			if (p->next->Lost == 0 || p->next->del == 0) {
				cout << "该账号已挂失或已注销，无法进行交易" << endl; return;
			}
			if (p->next->Bfee >= tempPrice) {
				p->next->Bfee -= tempPrice;
				flag = 1; break;
			}
			else {
				cout << "一卡通校内金额不足" << endl;
				flag = 2; return;
			}
		}
		p = p->next;
	}

	if (flag == 0)  cout << "无此一卡通信息" << endl;
	
	FILE *fptr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	fptr = fopen("card_base.dat", "wb+"); //wb+写并且覆盖掉原来的信息 
	p = head;
	while (p->next != NULL){
	    mem.busFee = p->next->Bfee;
		mem.schFee = p->next->Cfee;
		strcpy(mem.id,p->next->id);
		strcpy( mem.danwei,p->next->danwei);
		strcpy( mem.item,p->next->item);
		strcpy( mem.name,p->next->name);
		mem.Iflost = p->next->Lost;
		mem.state = p->next->del;
		fwrite(&mem,sizeof(struct Member), 1, fptr);
		p = p->next;
	}
	fclose(fptr);

	FILE* cfptr;
	if (flag) {
		struct Consume con = { "", "", "", 0.0, "", "" };
		if ((cfptr = fopen("card_sell.dat", "ab+")) == NULL) {
			cout << "写入账号信息文件有误" << endl;
			exit(0);
		}
		cout << "请输入消费编号、消费日期、消费地点、消费人员" << endl;
		cin >> con.connum >> con.Date >> con.place >> con.Consumer;
		strcpy(con.id, tempID);
		con.money = tempPrice;
		con.way = 2;
		fseek(cfptr, 0, SEEK_SET);
		fwrite(&con, sizeof(struct Consume), 1, cfptr);
		cout << "付费成功！" << endl;
		fclose(cfptr);
	}
}

//6、输出信息 
void showMember() {
	FILE* cfptr;
	int flag = 0, choose;

	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	struct Uprecharge upre = { "", 0.0, "", "", 0 };
	struct Consume con = { "", "", "", 0.0, "", "" };

	cout << "请输入输出信息种类：1.基本信息 2.充值信息 3.消费信息" << endl;
	cin >> choose;
	if(choose != 1&&choose != 2&&choose != 3)  {
		cout << "请输入正确序号" << endl; return ;
	}
	if (choose == 1) {
		if ((cfptr = fopen("card_base.dat", "rb")) == NULL) {
			cout << "无账号信息文件" << endl;
		}
		else {
			while (fread(&mem, sizeof(struct Member), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-10s%-6s%-12s%-0s %-0s %-0s %-0s\n", "编号", "种类", "名字", "单位", "公交费用", "校内费用", "挂失", "状态");
				printf("%-7s%-10s%-6s%-12s%-10.2lf%-10.2lf %-2d%-2d\n", mem.id, mem.item, mem.name, mem.danwei, mem.busFee, mem.schFee, mem.Iflost, mem.state);
				flag = 1;
			}
		}
	}

	if (choose == 2) {
		cout << "方式1为校内充值， 方式2为公交充值" << endl;
		if ((cfptr = fopen("card_input.dat", "rb")) == NULL) {
			cout << "无账号信息文件" << endl;
		}
		else {
			while (fread(&upre, sizeof(struct Uprecharge), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-10s%-10s%-6s%-5s\n", "编号", "金额", "日期", "操作人", "方式");
				printf("%-7s%-10.2lf%-12s%-6s%-5d\n", upre.id, upre.money, upre.Date, upre.oper, upre.way);
				flag = 1;
			}
		}
	}

	if (choose == 3) {
		cout << "方式1为校内充值， 方式2为公交充值" << endl;
		if ((cfptr = fopen("card_sell.dat", "rb")) == NULL) {
			cout << "无账号信息文件" << endl;
		}
		else {
			while (fread(&con, sizeof(struct Consume), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-7s%-10s%-0s%-10s%-6s%-0s\n", "消费编号", "编号", "日期", "金额", "消费地点", "操作人", "方式");
				printf("%-7s%-7s%-12s%-10.2lf%-10s%-6s%-2d\n", con.connum, con.id, con.Date, con.money, con.place, con.Consumer, con.way);
				flag = 1;
			}
		}
		fclose(cfptr);
	}

	
}

//7、挂失，解挂 
void Deal() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	char tempID[12], tempName[12];
	int choose = 0, i = 0;

	cout << "请输入一卡通编号，姓名：" << endl;
	cin >> tempID >> tempName;
	if ((fPtr = fopen("card_base.dat", "rb+")) == NULL) {
		cout << "不能打开文件" << endl;
		exit(0);
	}

	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		if (strcmp(mem.id, tempID) == 0 && strcmp(mem.name, tempName) == 0) {
			
			cout << "请输入想要进行的业务：1.挂失 2.解挂 3.注销" << endl;
			cin >> choose;

			if (choose == 1) {
				if (mem.Iflost == 0 || mem.state == 0) cout << "为挂失或注销状态,不能挂失" << endl;
				else {
					mem.Iflost = 0;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "挂失成功!" << endl;
				}
				break;
			}

			if (choose == 2) {
				if (mem.Iflost != 0 && mem.state != 0) cout << "不需解挂" << endl;
				else {
					mem.Iflost = mem.state = 1;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "解挂成功！" << endl;
				}
				break;
			}

			if (choose == 3) {
				if (mem.state == 0) cout << "为注销状态,不能注销" << endl;
				else {
					mem.state = 0;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "注销成功!" << endl;
				}
				break;
			}
			i++;
		}
	}
	if (choose == 0)  cout << "无此一卡通信息" << endl;
	fclose(fPtr);
}

//8查找信息 
void searchInfor(){
	FILE *fPtr;
	struct Member mem = {"", "", "", "", 0.0, 0.0, 1, 1};
	struct Uprecharge upre = {"", 0.0, "", "", 0};
	struct Consume con = {"", "", "", 0.0, "", ""};
	char tempID[10];
	int flag = 0,choose;
	
	cout << "请输入要查找的编号：" << endl;
	cin >> tempID;
	cout << "请输入你要查询的类别：1.基本信息 2.充值信息 3.消费信息" << endl;
	cin >> choose;
	if(choose == 1) {
		if ((fPtr = fopen("card_base.dat","rb")) == NULL){
		cout << "不能打开文件" << endl;
		exit(0); 
	}
	
	while ((fread(&mem, sizeof(struct Member), 1, fPtr))!= (int)NULL){
		if (strcmp(mem.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-10s%-6s%-12s%-0s %-0s %-0s  %-0s\n","编号","种类","名字","单位","公交费用","校内费用","挂失","状态");
			printf("%-7s%-10s%-6s%-12s%-10.2lf%-10.2lf %-2d %-2d\n",mem.id, mem.item, mem.name, mem.danwei, mem.busFee, mem.schFee, mem.Iflost, mem.state);
			flag = 1;
		}
	}
	if (flag == 0) cout << "没有要查找的信息" << endl;
	} 
	
	else if (choose == 2) {
		if ((fPtr = fopen("card_input.dat","rb")) == NULL){
		cout << "不能打开文件" << endl;
		exit(0); 
	}
	
	while ((fread(&upre, sizeof(struct Uprecharge), 1, fPtr))!= (int)NULL){
		if (strcmp(upre.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-10s%-10s%-6s%-5s\n","编号","金额","日期","操作人","方式");
			printf("%-7s%-10.2lf%-12s%-6s%-5d\n", upre.id, upre.money, upre.Date, upre.oper, upre.way);
			flag = 1;
		}
	}
	if (flag == 0) cout << "没有要查找的信息" << endl;
	}
	
	else if (choose == 3){
		if ((fPtr = fopen("card_sell.dat","rb")) == NULL){
		cout << "不能打开文件" << endl;
		exit(0); 
	}
	
	while ((fread(&con, sizeof(struct Consume), 1, fPtr))!= (int)NULL){
		if (strcmp(con.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-7s%-10s%-0s%-10s%-6s%-0s\n","消费编号","编号","日期","金额","消费地点","操作人","方式");
			printf("%-7s%-7s%-12s%-10.2lf%-10s%-6s%-2d\n",con.connum,con.id,con.Date,con.money,con.place,con.Consumer,con.way);
			flag = 1;
		}
	}
	if (flag == 0) cout << "没有要查找的信息" << endl;
	}
	fclose(fPtr);
}


void BusFee(Node* head) {
	Node* p;
	p = head;
	while (p->next != NULL)
	{
		if (p->next->item == 0)  {a[0] += p->next->Bus; b[0] += p->next->Campus;}//头部是空指针，所以要加next 
		if (p->next->item == 1)  {a[1] += p->next->Bus; b[1] += p->next->Campus;}
		if (p->next->item == 2)  {a[2] += p->next->Bus; b[2] += p->next->Campus;}
		if (p->next->item == 3)  {a[3] += p->next->Bus; b[3] += p->next->Campus;}
		//cout << p->next->item;
		p = p->next;
	}
	printf("公交费用：\n教工卡：%.2lf  学生卡：%.2lf  其他卡：%.2lf  临时卡：%.2lf\n", a[0], a[1], a[2], a[3]);
	printf("校内费用：\n教工卡：%.2lf  学生卡：%.2lf  其他卡：%.2lf  临时卡：%.2lf\n", b[0], b[1], b[2], b[3]);
}

//9、指定信息统计 
void Total() {
	Node* head = (struct Node*)malloc(LEN);  //创建头节点，分配内存 ,需要的内存和结构体的大小相同，malloc前进行强制类型转换（struct node*) 
	head->next = NULL; //头节点指针初始化 
	Node* p;// = (struct Node*)malloc(LEN);  //创建p节点，分配内存 
	p = head; //p节点指针赋值为头节点 
	Node* q;
	FILE* fPtr;
	struct Member mem = { "","","","",0.0,0.0,1,1 };

	if ((fPtr = fopen("card_base.dat", "rb")) == NULL) {
		cout << "不能打开文件" << endl;
		exit(0);
	}
	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		q = (struct Node*)malloc(LEN);
		q->Bus = mem.busFee;
		q->Campus = mem.schFee;
		if (strcmp(mem.item, "教工卡") == 0) q->item = 0;
		if (strcmp(mem.item, "学生卡") == 0) q->item = 1;
		if (strcmp(mem.item, "其他卡") == 0) q->item = 2;
		if (strcmp(mem.item, "临时卡") == 0) q->item = 3;
		p->next = q;  //插完用p保存了上一个节点，从p后插入q； 
		q->next = NULL;  //尾部指针q指向NULL 
		p = q; //p保存q节点保证p始终是最后一个节点 
	}
	BusFee(head);
}

void InputFee(Input *head){
	double X,G;
	X = G = 0;
	Input* p;
	p = head;
	while (p->next != NULL)
	{
		if (p->next->Way == 1)  X +=p->next->Money;//头部是空指针，所以要加next 
		if (p->next->Way == 2)  G += p->next->Money;
		p = p->next;
	}
	printf("校内充值：%.2lf\n公交充值：%.2lf\n",X, G);
}

void TotalInput() {
	Input* head = (struct Input*)malloc(LEN);  //创建头节点，分配内存 ,需要的内存和结构体的大小相同，malloc前进行强制类型转换（struct node*) 
	head->next = NULL; //头节点指针初始化 
	Input* p;// = (struct Node*)malloc(LEN);  //创建p节点，分配内存 
	p = head; //p节点指针赋值为头节点 
	Input* q;
	FILE* fPtr;
	struct Uprecharge upre = { "",0.0,"","",1 };

	if ((fPtr = fopen("card_input.dat", "rb")) == NULL) {
		cout << "不能打开文件" << endl;
		exit(0);
	}
	while ((fread(&upre, sizeof(struct Uprecharge), 1, fPtr)) != (int)NULL) {
		q = (struct Input*)malloc(LEN);
		q->Money = upre.money;
		q->Way = upre.way;
		p->next = q;  //插完用p保存了上一个节点，从p后插入q； 
		q->next = NULL;  //尾部指针q指向NULL 
		p = q; //p保存q节点保证p始终是最后一个节点 
	}
	InputFee(head);
}


