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
	printf("���������룺");
	if (Password()) {
		showMenu();
		while ((choice = EnterChoice()) != 10) {
			switch (choice) {
			case 1:
				cout << "���޸����룺" << endl;
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
				cout << "��������ȷ���" << endl;
				break;
			}
			cout << "�����ѡ��Ҫ�����ҵ��" << endl;
			showMenu();
		}
	}
	else cout << "�������" << endl;

	return 0;
}

//�ж����� 
bool Password() {
	char str[10];
	char pass[10] = {'0'};
	scanf("%s", str);
	FILE *fp;
	if ((fp = fopen("key.dat","rb"))!=NULL){//rb ���ļ� 
		fread(pass,sizeof(pass), 11, fp);
		if(strcmp(str, pass) == 0)  return true;
	}
	return false;
}

void showMenu() {
	cout << "1.�޸�����" << endl;
	cout << "2.¼����Ϣ" << endl;
	cout << "3.��ֵ����" << endl;
	cout << "4.У�����ѹ���" << endl;
	cout << "5.�������ѹ���" << endl;
	cout << "6.���ȫ����Ϣ" << endl;
	cout << "7.��ʧ����ҡ�ע������" << endl;
	cout << "8.����ָ����Ϣ" << endl;
	cout << "9.ָ����Ϣͳ��" << endl;
	cout << "10.�˳�ϵͳ" << endl;
}

int EnterChoice() {
	int menuChoice;
	cin >> menuChoice;

	return menuChoice;
}
//1.�޸����� 
void changePassword() {
	cout << "������ʮλ���ڵ�����" << endl; 
	char str[10];
	cin >> str;
	FILE *fp;
	if ((fp = fopen("key.dat","wb"))!=NULL){ //ʹ��wb��д�ļ������Ҹ��ǵ�֮ǰ������ 
		fwrite(str,sizeof(char),12,fp);
	}
	cout << "�޸�����ɹ���" << endl; 
}

//2.¼����Ϣ 
void inputRecord() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	char m_id[12];
	int panduan, choose;

	if ((fPtr = fopen("card_base.dat", "ab+")) == NULL) { //���ļ�β�����������֮��,������λ�ú������ÿ�ʼ������ʼλ��. 
		cout << "д���˺���Ϣ�ļ�����" << endl;
		exit(0);
	}
	while (1) {
		cout << "�������ţ�" << endl;
		scanf("%s", m_id);
		rewind(fPtr); //�ı��ļ��ڲ�λ�� 
		panduan = 0;
		while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
			if (strlen(m_id) != 5) {
				cout << "�����˴�����" << endl;
				panduan = 1;
				break;
			}
			if (strcmp(m_id, mem.id) == 0) {
				cout << "�����˺Ų����ظ�" << endl;
				panduan = 1;
				break;
			}
		}
		if (panduan == 0) {
			cout << "���������ࣨ�̹�����ѧ����������������ʱ��������������λ�������ѽ�У�ڽ���ʧ(1.���� 0.��ʧ)��״̬(1.���� 0.ע��)��" << endl;
			cin >> mem.item >> mem.name >> mem.danwei >> mem.busFee >> mem.schFee >> mem.Iflost >> mem.state;
			strcpy(mem.id, m_id);
			fseek(fPtr, 0, SEEK_END); //ָ���ļ�β 
			fwrite(&mem, sizeof(struct Member), 1, fPtr); //������д���ļ��У�һ����Ԫ����һ���ṹ�� 
			cout << "�����Ϣ�ɹ���" << endl;
		}
		cout << "�Ƿ����¼����Ϣ�� �ǣ�1�� �񣺷�1�� ��ѡ��" << endl;
		cin >> choose;
		if (choose != 1) break;
	}
	fclose(fPtr);
}

//3����ֵ���� 
void charge() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1,1 };
	char tempID[12];
	int flag = 0, choose, i = 0;
	int transaction;

	cout << "����Ҫ��ֵ�ı�ţ�" << endl;
	cin >> tempID;
	if ((fPtr = fopen("card_base.dat", "rb+")) == NULL) {
		cout << "���ܴ��ļ�" << endl;
		exit(0);
	}

	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		if (strcmp(mem.id, tempID) == 0) {
			if (mem.Iflost == 0 || mem.state == 0) {
				cout << "���˺��ѹ�ʧ����ע�����޷����н���" << endl; return;
			}

			while (1) {
				cout << "��ѡ���ֵ���ͣ�1��У�ڳ�ֵ 2��������ֵ" << endl;
				cin >> choose;
				if (choose == 1 || choose == 2) break;
				else cout << "��������ȷ����!" << endl;
			}

			while (1) {
				cout << "�����뽻�׵Ľ�10�ı�����" << endl;
				cin >> transaction;
				if (transaction % 10 == 0)  break;
				else cout << "��������ȷ�����" << endl;
			}
			if (choose == 1) {
				mem.schFee += transaction;
			}
			else {
				mem.busFee += transaction;
			}
			fseek(fPtr, i * sizeof(struct Member), SEEK_SET); //��i��ȷ����Ԫ�Ĵ�С 
			fwrite(&mem, sizeof(struct Member), 1, fPtr);
			flag = 1; break;
		}
		i++;
	}

	if (flag == 0) {
		cout << "�ļ���û�д���Ϣ" << endl; return;
	}

	FILE* cfptr;
	if (flag == 1) {
		struct Uprecharge upre = { "", 0.0, "", "", 0 };
		if ((cfptr = fopen("card_input.dat", "ab+")) == NULL) {
			cout << "д���˺���Ϣ�ļ�����" << endl;
			exit(0);
		}
		cout << "��ֵ���ڡ�����Ա" << endl;
		cin >> upre.Date >> upre.oper;
		strcpy(upre.id, tempID);
		upre.way = choose;  upre.money = transaction;
		fseek(cfptr, 0, SEEK_END);
		fwrite(&upre, sizeof(struct Uprecharge), 1, cfptr);
		cout << "��ֵ�ɹ���" << endl;
		fclose(cfptr);
	}

	fclose(fPtr);
}

//��������洢������Ϣ 
struct Linklist* create() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	Linklist* head = (struct Linklist*)malloc(sizeof(struct Linklist));  //����ͷ�ڵ㣬�����ڴ� ,��Ҫ���ڴ�ͽṹ��Ĵ�С��ͬ��mallocǰ����ǿ������ת����struct node*) 
	head->next = NULL; //ͷ�ڵ�ָ���ʼ�� 
	Linklist* p; //= (struct Linklist*)malloc(sizeof(struct Linklist));  //����p�ڵ㣬�����ڴ� 
	p = head; //p�ڵ�ָ�븳ֵΪͷ�ڵ� 
	Linklist* q;

	if ((fPtr = fopen("card_base.dat", "rb")) == NULL) {
		cout << "���ܴ��ļ�" << endl;
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
		p->next = q;  //������p��������һ���ڵ㣬��p�����q�� 
		q->next = NULL;  //β��ָ��qָ��NULL 
		p = q; //p����q�ڵ㱣֤pʼ�������һ���ڵ� 
	}
	fclose(fPtr);
	return head;
}

//4��У�����ѹ��� 
void schConsum() {
	char tempID[12];
	double tempPrice;
	int flag = 0;

	cout << "����һ��ͨ��š����ѽ��" << endl;
	cin >> tempID >> tempPrice;

	Linklist* head = create();
	Linklist* p = head;

	while (p->next != NULL) {
		if (strcmp(p->next->id, tempID) == 0) {
			if (p->next->Lost == 0 || p->next->del == 0) {
				cout << "���˺��ѹ�ʧ����ע�����޷����н���" << endl; return;
			}
			if (p->next->Cfee >= tempPrice) {
				p->next->Cfee -= tempPrice;
				flag = 1; break;
			}
			else {
				cout << "һ��ͨУ�ڽ���" << endl;
				flag = 2; return;
			}
		}
		p = p->next;
	}

	if (flag == 0)  cout << "�޴�һ��ͨ��Ϣ" << endl;
	
	FILE *fptr;
	p = head; 
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	fptr = fopen("card_base.dat", "wb+");
	while (p->next != NULL){
		/*if ((fptr = fopen("card_base.dat", "wb+")) == NULL) {
			cout << "д���˺���Ϣ�ļ�����" << endl;
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
			cout << "д���˺���Ϣ�ļ�����" << endl;
			exit(0);
		}
		cout << "���������ѱ�š��������ڡ����ѵص㡢������Ա" << endl;
		cin >> con.connum >> con.Date >> con.place >> con.Consumer;
		strcpy(con.id, tempID);
		con.money = tempPrice;
		con.way = 1;
		fseek(cfptr, 0, SEEK_SET);
		fwrite(&con, sizeof(struct Consume), 1, cfptr);
		cout << "���ѳɹ���" << endl;
		fclose(cfptr);
	}
}

//5���������ѹ��� 
void busConsum() {
	char tempID[12];
	double tempPrice;
	int flag = 0;

	cout << "����һ��ͨ��š����ѽ��" << endl;
	cin >> tempID >> tempPrice;
	Linklist* head = create();
	Linklist* p = head;

	while (p->next != NULL) {
		if (strcmp(p->next->id, tempID) == 0) {
			if (p->next->Lost == 0 || p->next->del == 0) {
				cout << "���˺��ѹ�ʧ����ע�����޷����н���" << endl; return;
			}
			if (p->next->Bfee >= tempPrice) {
				p->next->Bfee -= tempPrice;
				flag = 1; break;
			}
			else {
				cout << "һ��ͨУ�ڽ���" << endl;
				flag = 2; return;
			}
		}
		p = p->next;
	}

	if (flag == 0)  cout << "�޴�һ��ͨ��Ϣ" << endl;
	
	FILE *fptr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	fptr = fopen("card_base.dat", "wb+"); //wb+д���Ҹ��ǵ�ԭ������Ϣ 
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
			cout << "д���˺���Ϣ�ļ�����" << endl;
			exit(0);
		}
		cout << "���������ѱ�š��������ڡ����ѵص㡢������Ա" << endl;
		cin >> con.connum >> con.Date >> con.place >> con.Consumer;
		strcpy(con.id, tempID);
		con.money = tempPrice;
		con.way = 2;
		fseek(cfptr, 0, SEEK_SET);
		fwrite(&con, sizeof(struct Consume), 1, cfptr);
		cout << "���ѳɹ���" << endl;
		fclose(cfptr);
	}
}

//6�������Ϣ 
void showMember() {
	FILE* cfptr;
	int flag = 0, choose;

	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	struct Uprecharge upre = { "", 0.0, "", "", 0 };
	struct Consume con = { "", "", "", 0.0, "", "" };

	cout << "�����������Ϣ���ࣺ1.������Ϣ 2.��ֵ��Ϣ 3.������Ϣ" << endl;
	cin >> choose;
	if(choose != 1&&choose != 2&&choose != 3)  {
		cout << "��������ȷ���" << endl; return ;
	}
	if (choose == 1) {
		if ((cfptr = fopen("card_base.dat", "rb")) == NULL) {
			cout << "���˺���Ϣ�ļ�" << endl;
		}
		else {
			while (fread(&mem, sizeof(struct Member), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-10s%-6s%-12s%-0s %-0s %-0s %-0s\n", "���", "����", "����", "��λ", "��������", "У�ڷ���", "��ʧ", "״̬");
				printf("%-7s%-10s%-6s%-12s%-10.2lf%-10.2lf %-2d%-2d\n", mem.id, mem.item, mem.name, mem.danwei, mem.busFee, mem.schFee, mem.Iflost, mem.state);
				flag = 1;
			}
		}
	}

	if (choose == 2) {
		cout << "��ʽ1ΪУ�ڳ�ֵ�� ��ʽ2Ϊ������ֵ" << endl;
		if ((cfptr = fopen("card_input.dat", "rb")) == NULL) {
			cout << "���˺���Ϣ�ļ�" << endl;
		}
		else {
			while (fread(&upre, sizeof(struct Uprecharge), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-10s%-10s%-6s%-5s\n", "���", "���", "����", "������", "��ʽ");
				printf("%-7s%-10.2lf%-12s%-6s%-5d\n", upre.id, upre.money, upre.Date, upre.oper, upre.way);
				flag = 1;
			}
		}
	}

	if (choose == 3) {
		cout << "��ʽ1ΪУ�ڳ�ֵ�� ��ʽ2Ϊ������ֵ" << endl;
		if ((cfptr = fopen("card_sell.dat", "rb")) == NULL) {
			cout << "���˺���Ϣ�ļ�" << endl;
		}
		else {
			while (fread(&con, sizeof(struct Consume), 1, cfptr) != (int)NULL) {
				if (flag == 0) printf("%-7s%-7s%-10s%-0s%-10s%-6s%-0s\n", "���ѱ��", "���", "����", "���", "���ѵص�", "������", "��ʽ");
				printf("%-7s%-7s%-12s%-10.2lf%-10s%-6s%-2d\n", con.connum, con.id, con.Date, con.money, con.place, con.Consumer, con.way);
				flag = 1;
			}
		}
		fclose(cfptr);
	}

	
}

//7����ʧ����� 
void Deal() {
	FILE* fPtr;
	struct Member mem = { "", "", "", "", 0.0, 0.0, 1, 1 };
	char tempID[12], tempName[12];
	int choose = 0, i = 0;

	cout << "������һ��ͨ��ţ�������" << endl;
	cin >> tempID >> tempName;
	if ((fPtr = fopen("card_base.dat", "rb+")) == NULL) {
		cout << "���ܴ��ļ�" << endl;
		exit(0);
	}

	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		if (strcmp(mem.id, tempID) == 0 && strcmp(mem.name, tempName) == 0) {
			
			cout << "��������Ҫ���е�ҵ��1.��ʧ 2.��� 3.ע��" << endl;
			cin >> choose;

			if (choose == 1) {
				if (mem.Iflost == 0 || mem.state == 0) cout << "Ϊ��ʧ��ע��״̬,���ܹ�ʧ" << endl;
				else {
					mem.Iflost = 0;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "��ʧ�ɹ�!" << endl;
				}
				break;
			}

			if (choose == 2) {
				if (mem.Iflost != 0 && mem.state != 0) cout << "������" << endl;
				else {
					mem.Iflost = mem.state = 1;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "��ҳɹ���" << endl;
				}
				break;
			}

			if (choose == 3) {
				if (mem.state == 0) cout << "Ϊע��״̬,����ע��" << endl;
				else {
					mem.state = 0;
					fseek(fPtr, i * sizeof(struct Member), SEEK_SET);
					fwrite(&mem, sizeof(struct Member), 1, fPtr);
					cout << "ע���ɹ�!" << endl;
				}
				break;
			}
			i++;
		}
	}
	if (choose == 0)  cout << "�޴�һ��ͨ��Ϣ" << endl;
	fclose(fPtr);
}

//8������Ϣ 
void searchInfor(){
	FILE *fPtr;
	struct Member mem = {"", "", "", "", 0.0, 0.0, 1, 1};
	struct Uprecharge upre = {"", 0.0, "", "", 0};
	struct Consume con = {"", "", "", 0.0, "", ""};
	char tempID[10];
	int flag = 0,choose;
	
	cout << "������Ҫ���ҵı�ţ�" << endl;
	cin >> tempID;
	cout << "��������Ҫ��ѯ�����1.������Ϣ 2.��ֵ��Ϣ 3.������Ϣ" << endl;
	cin >> choose;
	if(choose == 1) {
		if ((fPtr = fopen("card_base.dat","rb")) == NULL){
		cout << "���ܴ��ļ�" << endl;
		exit(0); 
	}
	
	while ((fread(&mem, sizeof(struct Member), 1, fPtr))!= (int)NULL){
		if (strcmp(mem.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-10s%-6s%-12s%-0s %-0s %-0s  %-0s\n","���","����","����","��λ","��������","У�ڷ���","��ʧ","״̬");
			printf("%-7s%-10s%-6s%-12s%-10.2lf%-10.2lf %-2d %-2d\n",mem.id, mem.item, mem.name, mem.danwei, mem.busFee, mem.schFee, mem.Iflost, mem.state);
			flag = 1;
		}
	}
	if (flag == 0) cout << "û��Ҫ���ҵ���Ϣ" << endl;
	} 
	
	else if (choose == 2) {
		if ((fPtr = fopen("card_input.dat","rb")) == NULL){
		cout << "���ܴ��ļ�" << endl;
		exit(0); 
	}
	
	while ((fread(&upre, sizeof(struct Uprecharge), 1, fPtr))!= (int)NULL){
		if (strcmp(upre.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-10s%-10s%-6s%-5s\n","���","���","����","������","��ʽ");
			printf("%-7s%-10.2lf%-12s%-6s%-5d\n", upre.id, upre.money, upre.Date, upre.oper, upre.way);
			flag = 1;
		}
	}
	if (flag == 0) cout << "û��Ҫ���ҵ���Ϣ" << endl;
	}
	
	else if (choose == 3){
		if ((fPtr = fopen("card_sell.dat","rb")) == NULL){
		cout << "���ܴ��ļ�" << endl;
		exit(0); 
	}
	
	while ((fread(&con, sizeof(struct Consume), 1, fPtr))!= (int)NULL){
		if (strcmp(con.id,tempID) == 0){
			if (flag == 0) printf("%-7s%-7s%-10s%-0s%-10s%-6s%-0s\n","���ѱ��","���","����","���","���ѵص�","������","��ʽ");
			printf("%-7s%-7s%-12s%-10.2lf%-10s%-6s%-2d\n",con.connum,con.id,con.Date,con.money,con.place,con.Consumer,con.way);
			flag = 1;
		}
	}
	if (flag == 0) cout << "û��Ҫ���ҵ���Ϣ" << endl;
	}
	fclose(fPtr);
}


void BusFee(Node* head) {
	Node* p;
	p = head;
	while (p->next != NULL)
	{
		if (p->next->item == 0)  {a[0] += p->next->Bus; b[0] += p->next->Campus;}//ͷ���ǿ�ָ�룬����Ҫ��next 
		if (p->next->item == 1)  {a[1] += p->next->Bus; b[1] += p->next->Campus;}
		if (p->next->item == 2)  {a[2] += p->next->Bus; b[2] += p->next->Campus;}
		if (p->next->item == 3)  {a[3] += p->next->Bus; b[3] += p->next->Campus;}
		//cout << p->next->item;
		p = p->next;
	}
	printf("�������ã�\n�̹�����%.2lf  ѧ������%.2lf  ��������%.2lf  ��ʱ����%.2lf\n", a[0], a[1], a[2], a[3]);
	printf("У�ڷ��ã�\n�̹�����%.2lf  ѧ������%.2lf  ��������%.2lf  ��ʱ����%.2lf\n", b[0], b[1], b[2], b[3]);
}

//9��ָ����Ϣͳ�� 
void Total() {
	Node* head = (struct Node*)malloc(LEN);  //����ͷ�ڵ㣬�����ڴ� ,��Ҫ���ڴ�ͽṹ��Ĵ�С��ͬ��mallocǰ����ǿ������ת����struct node*) 
	head->next = NULL; //ͷ�ڵ�ָ���ʼ�� 
	Node* p;// = (struct Node*)malloc(LEN);  //����p�ڵ㣬�����ڴ� 
	p = head; //p�ڵ�ָ�븳ֵΪͷ�ڵ� 
	Node* q;
	FILE* fPtr;
	struct Member mem = { "","","","",0.0,0.0,1,1 };

	if ((fPtr = fopen("card_base.dat", "rb")) == NULL) {
		cout << "���ܴ��ļ�" << endl;
		exit(0);
	}
	while ((fread(&mem, sizeof(struct Member), 1, fPtr)) != (int)NULL) {
		q = (struct Node*)malloc(LEN);
		q->Bus = mem.busFee;
		q->Campus = mem.schFee;
		if (strcmp(mem.item, "�̹���") == 0) q->item = 0;
		if (strcmp(mem.item, "ѧ����") == 0) q->item = 1;
		if (strcmp(mem.item, "������") == 0) q->item = 2;
		if (strcmp(mem.item, "��ʱ��") == 0) q->item = 3;
		p->next = q;  //������p��������һ���ڵ㣬��p�����q�� 
		q->next = NULL;  //β��ָ��qָ��NULL 
		p = q; //p����q�ڵ㱣֤pʼ�������һ���ڵ� 
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
		if (p->next->Way == 1)  X +=p->next->Money;//ͷ���ǿ�ָ�룬����Ҫ��next 
		if (p->next->Way == 2)  G += p->next->Money;
		p = p->next;
	}
	printf("У�ڳ�ֵ��%.2lf\n������ֵ��%.2lf\n",X, G);
}

void TotalInput() {
	Input* head = (struct Input*)malloc(LEN);  //����ͷ�ڵ㣬�����ڴ� ,��Ҫ���ڴ�ͽṹ��Ĵ�С��ͬ��mallocǰ����ǿ������ת����struct node*) 
	head->next = NULL; //ͷ�ڵ�ָ���ʼ�� 
	Input* p;// = (struct Node*)malloc(LEN);  //����p�ڵ㣬�����ڴ� 
	p = head; //p�ڵ�ָ�븳ֵΪͷ�ڵ� 
	Input* q;
	FILE* fPtr;
	struct Uprecharge upre = { "",0.0,"","",1 };

	if ((fPtr = fopen("card_input.dat", "rb")) == NULL) {
		cout << "���ܴ��ļ�" << endl;
		exit(0);
	}
	while ((fread(&upre, sizeof(struct Uprecharge), 1, fPtr)) != (int)NULL) {
		q = (struct Input*)malloc(LEN);
		q->Money = upre.money;
		q->Way = upre.way;
		p->next = q;  //������p��������һ���ڵ㣬��p�����q�� 
		q->next = NULL;  //β��ָ��qָ��NULL 
		p = q; //p����q�ڵ㱣֤pʼ�������һ���ڵ� 
	}
	InputFee(head);
}


