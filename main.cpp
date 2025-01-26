#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <strstream>
#include <vector>
//#include <string>
#pragma warning (disable:4996)
int recordtype=0;//0��ʾ���������1��ʾ�ڲ�ѯ��ʱ���
int usertype = 0;//0��ʾ���ļ����������ж�ȡ��1��ʾ�Ӽ��̶�ȡ
using namespace std;

int getint(int arr[],int size)
{
	int i,j,flag=0;
	cin >> i;
	if (cin.fail())flag = 0;
	else
	{
		for (j = 0;j < size;j++)
		{
			if (i == arr[j])flag = 1;
		}
	}
	while (!flag)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cout << "�����������������" << endl;
		cin >> i;
		if (cin.fail())flag = 0;
		else
		{
			for (j = 0;j < size;j++)
			{
				if (i == arr[j])flag = 1;
			}
		}
	}
	return i;
}

class book
{
public:
	book(){}
	//book(char n[], char a[], char t[], char k[], char i[], bool s)
	//{
	//	if (n) { strcpy(name, n); }
	//	if (a) { strcpy(author, a); }
	//	if (t) { strcpy(type, t); }
	//	if (k) { strcpy(keywords, k); }
	//	if (i) { strcpy(intro, i); }
	//	status = s;
	//};
	void init(char line[])
	{
		strcpy(name, strtok(line, "|"));
		strcpy(author, strtok(NULL, "|"));
		strcpy(type, strtok(NULL, "|"));
		strcpy(keywords, strtok(NULL, "|"));
		strcpy(intro, strtok(NULL, "|"));
		if (strcmp(strtok(NULL, "|"), "1"))status = true;
		else status = false;
	};
	void init(char n[], char a[], char t[], char k[], char i[], bool s)
	{
		if (n) { strcpy(name, n); }
		if (a) { strcpy(author, a); }
		if (t) { strcpy(type, t); }
		if (k) { strcpy(keywords, k); }
		if (i) { strcpy(intro, i); }
		status = s;
	};
	void print()
	{
		cout << "-----------------------------" << endl;
		cout << "name        " << name << endl;
		cout << "author      " << author << endl;
		cout << "type        " << type << endl;
		cout << "keywords    " << keywords << endl;
		cout << "intro       " << intro << endl;
		if(status)cout << "status      " << "���" << endl;
		else cout << "status      " << "�ڼ�" << endl;
		cout << "-----------------------------" << endl;
	}
	int searchbookname(char search[]) const
	{
		int flag = 0;
		if (strstr(name, search))
		{
			flag = 1;
		}
		return flag;
	}
	friend ostream& operator << (ostream& output, book& B);//����������
private:
	char name[60];//����
	char author[20];//����
	char type[20];//����
	char keywords[20];//�ؼ���
	char intro[200];//���
	bool status;//����״̬��0��ʾ�ڼܣ�1��ʾ��裩
};

ostream& operator << (ostream& output, book& B)
{
	output << "-----------------------------" << endl;
	output << "name        " << B.name << endl;
	output << "author      " << B.author << endl;
	output << "type        " << B.type << endl;
	output << "keywords    " << B.keywords << endl;
	output << "intro       " << B.intro << endl;
	if (B.status)output << "status      " << "���" << endl;
	else output << "status      " << "�ڼ�" << endl;
	output << "-----------------------------" << endl;
	return output;
}


void searchbook()
{
	book* b=new book;
	char info[330],search[30];
	int count = 0;
	cout << "������Ҫ���ҵ�������" << endl;
	cin >> search;
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(info, 330, '\n');
		if (*info == '\0')break;
		b->init(info);
		if (b->searchbookname(search))
		{
			count++;
			//b->print();
			cout << *b;
		}
		//if(strstr(info,search))
	}
	if (count)cout << "���ҵ�" << count<< "������" << search << "�Ľ��" << endl;
	else cout << "δ�ҵ�����"<< search << "�Ľ��" << endl;
	infile.close();
	delete b;
}

void addbook()//������Ŀ
{
	int i, arr[] = { 1,2 };
	cout << "���������ӷ�ʽ��" << endl;
	cout << "1 �������" << endl;
	cout << "2 �������" << endl;
	i = getint(arr, 2);
	while (i != 1 && i != 2)
	{
		cout << "�����������������" << endl;
		cin >> i;
	}
	if (i == 1)
	{
		char info[330];
		cout << "������ͼ������������ߣ���𣬹ؼ��֣����ͽ���״̬��0��ʾ�ڼܣ�1��ʾ��裩��ÿ��֮���á�|��������" << endl;
		cin >> info;
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << info << endl;
		outfile.close();
	}
	else//i==2
	{
		char name[60];//����
		char author[20];//����
		char type[20];//���
		char keywords[20];//�ؼ���
		char intro[200];//���
		int status;//����״̬
		cout<<"������ͼ���������"<<endl;
		cin >> name;
		cout << "������ͼ������ߣ�" << endl;
		cin >> author;
		cout << "������ͼ������" << endl;
		cin >> type;
		cout << "������ͼ��Ĺؼ��֣�" << endl;
		cin >> keywords;
		cout << "������ͼ��ļ�飺" << endl;
		cin >> intro;
		cout << "������ͼ��Ľ���״̬��0��ʾ�ڼܣ�1��ʾ��裩��" << endl;
		cin >> status;
		while (cin.fail() || status != 0 || status != 1)
		{
			cout << "����״̬�����������������" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cin >> status;
		}
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << name << "|" << author << "|" << type << "|" << keywords << "|" << intro << "|" << status << endl;
		outfile.close();
	}
	cout << "�鼮�ѳɹ�д��" << endl;
}

void deletebook()
{
	char info[330], info2[330],name[60];
	int flag = 0,flag2=0;
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_book_.txt", ios::out | ios::app);
	cout << "������ɾ���鼮���ƣ�" << endl;
	cin >> name;
	while (!infile.eof())
	{
		infile.getline(info, 330, '\n');
		if (*info == '\0')break;
		//cout << strtok(info, "|") << endl;
		strcpy(info2, info);
		if (strstr(strtok(info2, "|"), name))
		{
			flag = 1;
		}
		else
		{
			outfile << info << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("book.txt");
	flag2 = rename("_book_.txt", "book.txt");
	if (flag && !flag2)	cout << "�鼮�ѳɹ�ɾ��" << endl;
	else cout<< "��Ǹ�������ڸ��鼮���޷�ɾ��" << endl;
}

void listbookname()
{
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	char info[330];
	//string info;
	cout << "--------------" << endl;
	while (!infile.eof())
	{
		infile.getline(info, 330, '\n');
		if (*info == '\0')break;
		cout << strtok(info, "|") << endl;
	}
	cout << "--------------" << endl;
	infile.close();
}

void listbook()
{
	book *b=new book;
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	char info[330];
	while (!infile.eof())
	{
		infile.getline(info, 330, '\n');
		if (*info == '\0')break;
		b->init(info);
		cout << *b;
	}
	infile.close();
	delete b;
}

void changebook()
{
	char info[330], info2[330], name[60];
	int flag = 0, flag2 = 0;
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_book_.txt", ios::out | ios::app);
	cout << "�������޸��鼮���ƣ�" << endl;
	cin >> name;
	while (!infile.eof())
	{
		infile.getline(info, 330, '\n');
		if (*info == '\0')break;
		strcpy(info2, info);
		if (strstr(strtok(info2, "|"), name))
		{
			flag = 1;
			int i, a[] = { 1,2 };
			cout << "�������޸ķ�ʽ��" << endl;
			cout << "1 ȫ���޸�" << endl;
			cout << "2 �����޸�" << endl;
			i = getint(a, 2);
			if (i == 1)
			{
				char info[330];
				cout << "������ͼ������������ߣ���𣬹ؼ��֣����ͽ���״̬��0��ʾ��裬1��ʾ�ڼܣ���ÿ��֮���á�|��������" << endl;
				cin >> info;
				outfile << info << endl;
			}
			else//i==2
			{
				char name[60];//����
				char author[20];//����
				char type[20];//���
				char keywords[20];//�ؼ���
				char intro[200];//���
				int status;//����״̬
				cout << "������ͼ���������" << endl;
				cin >> name;
				cout << "������ͼ������ߣ�" << endl;
				cin >> author;
				cout << "������ͼ������" << endl;
				cin >> type;
				cout << "������ͼ��Ĺؼ��֣�" << endl;
				cin >> keywords;
				cout << "������ͼ��ļ�飺" << endl;
				cin >> intro;
				cout << "������ͼ��Ľ���״̬��0��ʾ�ڼܣ�1��ʾ��裩��" << endl;
				cin >> status;
				while (cin.fail() || status != 0 || status != 1)
				{
					cout << "����״̬�����������������" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
					cin >> status;
				}
				ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
				outfile << name << "|" << author << "|" << type << "|" << keywords << "|" << intro << "|" << status << endl;
			}
		}
		else
		{
			outfile << info << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("book.txt");
	rename("_book_.txt", "book.txt");
	if (flag)	cout << "�鼮�ѳɹ��޸�" << endl;
	else cout << "��Ǹ���������鼮"<<name<<"����δ���޸�" << endl;
}
class date//������
{
public:
	void init(int y, int m, int d) { year = y;month = m;day = d; }
	int showy() { return year; }
	int showm() { return month; }
	int showd() { return day; }
	int GetYear() { return year; }
	void print() const{ cout << year << "." << month << "." << day; }
	friend istream& operator >> (istream& input, date& D);//�����������
	friend ostream& operator << (ostream& output, date& D);//����������
private:
	int year, month, day;
};

istream& operator >> (istream& input, date& D)
{
	input >> D.year >> D.month >> D.day;
	return input;
}

//�����м��пո�����û��
ostream& operator << (ostream& output, date& D)
{
	output << D.year << " " << D.month << " " << D.day;
	return output;
}

class record//�����¼��
{
public:
	void print()
	{
		cout << "-----------------------------" << endl;
		cout << "username    " << username << endl;
		cout << "bookname    " << name << endl;
		if (status)
		{
			cout << "status      " << "δ�黹" << endl;
			cout << "start date  ";
			start.print();
			cout << endl;
		}
		else
		{
			cout << "status      " << "�ѹ黹" << endl;
			cout << "start date  ";
			start.print();
			cout << endl;
			cout << "end date    ";
			end.print();
			cout << endl;
		}
		cout << "-----------------------------" << endl;
	}
	int searchbookname(char search[]) const
	{
		int flag = 0;
		if (strstr(name, search))
		{
			flag = 1;
		}
		return flag;
	}
	int searchusername(char search[]) const
	{
		int flag = 0;
		if (strstr(username, search))
		{
			flag = 1;
		}
		return flag;
	}
	friend istream& operator >> (istream& input, record& R);//�����������
	friend ostream& operator << (ostream& output, record& R);//����������
private:
	date start;//���鿪ʼ����
	date end;//�����������
	char name[60];//����
	char username[28];//����
	bool status;//����״̬��0��ʾ�ѹ黹��1��ʾδ�黹)
};

istream& operator >> (istream& input, record& R)
{
	int s;
	input >> s >> R.username >> R.name >> R.start;
	if(!s)
	{
		input >> R.end;
		R.status = 0;
	}
	else 
	{
		R.end.init(0, 0, 0);
		R.status = 1;
	}
	return input;
}

ostream& operator << (ostream& output, record& R)//����������
{
	if (recordtype)
	{
		output <<left<<setw(11)<< R.name<<" ";
		if (R.status)
		{
			output << "δ�黹��";
			R.start.print();
			output <<"���" << endl;
		}
		else
		{
			output << "�ѹ黹��" ;
			R.start.print();
			output << "�����" ;
			R.end.print();
			output << "�黹" << endl;
		}
	}
	else
	{
		output << "-----------------------------" << endl;
		output << "name        " << R.username << endl;
		output << "bookname    " << R.name << endl;
		if (R.status)
		{
			output << "status      " << "δ�黹" << endl;
			output << "start date  ";
			R.start.print();
			output << endl;
		}
		else
		{
			output << "status      " << "�ѹ黹" << endl;
			output << "start date  ";
			R.start.print();
			output << endl;
			output << "end date    ";
			R.end.print();
			output << endl;
		}
		output << "-----------------------------" << endl;
	}
	return output;
}

void addrecord()
{
	int i, arr[] = { 1,2 };
	cout << "���������ӷ�ʽ��" << endl;
	cout << "1 �������" << endl;
	cout << "2 �������" << endl;
	i = getint(arr, 2);
	if (i == 1)
	{
		char record[100];
		cout << "���������״̬��0��ʾ�ѹ黹��1��ʾδ�黹)�������ˡ����������պͻ��������գ�δ�黹����д���������գ���ÿ��֮���á� ��������" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin.getline(record, 100, '\n');
		ofstream outfile("record.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << record << endl;
		outfile.close();
	}
	else//i==2
	{
		char name[60];//����
		char author[20];//����
		char type[20];//���
		char keywords[20];//�ؼ���
		char intro[200];//���
		int status;//����״̬
		cout << "������ͼ���������" << endl;
		cin >> name;
		cout << "������ͼ������ߣ�" << endl;
		cin >> author;
		cout << "������ͼ������" << endl;
		cin >> type;
		cout << "������ͼ��Ĺؼ��֣�" << endl;
		cin >> keywords;
		cout << "������ͼ��ļ�飺" << endl;
		cin >> intro;
		cout << "������ͼ��Ľ���״̬��0��ʾ�ڼܣ�1��ʾ��裩��" << endl;
		cin >> status;
		while (cin.fail() || status != 0 || status != 1)
		{
			cout << "����״̬�����������������" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cin >> status;
		}
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << name << "|" << author << "|" << type << "|" << keywords << "|" << intro << "|" << status << endl;
		outfile.close();
	}
	cout << "�鼮�ѳɹ�д��" << endl;
}

//�г������¼
void listrecord()
{
	record* r = new record;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	char record[100];
	while (!infile.eof())
	{
		infile.getline(record, 100, '\n');
		if (*record == '\0')break;
		istrstream rs(record, 100);
		rs >> *r;
		cout << *r;
	}
	infile.close();
	delete r;
}

//��ѯ�û�������ʷ
void searchuserboookrecord()
{
	record* r = new record;
	char record[100],name[60];
	int count = 0;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	cout << "������Ҫ���ҵ�������" << endl;
	cin >> name;
	while (!infile.eof())
	{
		infile.getline(record, 100, '\n');
		if (*record == '\0')break;
		istrstream rs(record, 100);
		rs >> *r;
		if (r->searchbookname(name))
		{
			count++;
			cout << *r;
		}
	}
	infile.close();
	if (count)cout << "���ҵ�" << count << "����������" << name << "�Ľ��" << endl;
	else cout << "δ�ҵ���������" << name << "�Ľ��" << endl;
}

//��ѯͼ�������ʷ
void searchbookrecord()
{
	char username[28];
	cout << "������Ҫ���ҵ�������" << endl;
	cin >> username;

	record* r = new record;
	char record[100];
	int count = 0;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(record, 100, '\n');
		if (*record == '\0')break;
		istrstream rs(record, 100);
		rs >> *r;
		if (r->searchusername(username))
		{
			count++;
			cout << *r;
		}
	}
	infile.close();
	if (count)cout << "���ҵ�" << count << "����������" << username << "�Ľ��" << endl;
	else cout << "δ�ҵ���������" << username << "�Ľ��" << endl;
	delete r;
}


//���Ҽ�¼
void searchrecord()
{
	record* r = new record;
	char record[100];
	int count = 0,i;
	cout << "��������ҷ�ʽ��" << endl;
	cout << "1 ����������" << endl;
	cout << "2 ����������" << endl;
	cin >> i;
	while (i != 1 && i != 2)
	{
		cout << "�����������������" << endl;
		cin >> i;
	}
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	if (i == 1)
	{
		char name[60];
		cout << "������Ҫ���ҵ�������" << endl;
		cin >> name;	
		while (!infile.eof())
		{
			infile.getline(record, 100, '\n');
			if (*record == '\0')break;
			istrstream rs(record, 100);
			rs >> *r;
			if (r->searchbookname(name))
			{
				count++;
				cout << *r;
			}
		}
		if (count)cout << "���ҵ�" << count << "����������" << name << "�Ľ��" << endl;
		else cout << "δ�ҵ���������" << name << "�Ľ��" << endl;
	}
	else//i==2
	{
		char username[28];
		cout << "������Ҫ���ҵ�������" << endl;
		cin >> username;
		ifstream infile("record.txt", ios::in | ios::_Nocreate);
		while (!infile.eof())
		{
			infile.getline(record, 100, '\n');
			if (*record == '\0')break;
			istrstream rs(record, 100);
			rs >> *r;
			if (r->searchusername(username))
			{
				count++;
				cout << *r;
			}
		}	
		if (count)cout << "���ҵ�" << count << "����������" << username << "�Ľ��" << endl;
		else cout << "δ�ҵ���������" << username << "�Ľ��" << endl;
	}
	infile.close();
}

//������¼�¼
void returnrecord()
{
	record* r = new record;
	char record[100],name[60];
	int flag = 0, flag2 = 0, count = 0;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_record_.txt", ios::out | ios::app);
	cout << "������黹�鼮���ƣ�" << endl;
	cin >> name;
	while (!infile.eof())
	{
		infile.getline(record, 100, '\n');
		if (*record == '\0')break;
		istrstream rs(record, 100);
		rs >> *r;
		if (r->searchbookname(name))
		{
			flag = 1;
			if (record[0] == '1')
			{
				int y, m, d;
				count = 1;
				cout << "�����뻹�������գ�" << endl;
				cin >> y >> m >> d;
				record[0] = '0';
				outfile << record << " " << y << " " << m << " " << d << endl;
			}
			else
			{
				outfile << record << endl;
			}
		}
		else
		{
			outfile << record << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("record.txt");
	flag2 = rename("_record_.txt", "record.txt");
	if (count&&!flag2)cout << "�鼮��¼�Ѹ������" << endl;
	else
	{
		if (flag)cout << "�鼮" << name << "�Ѿ��黹���������" << endl;
		else if(flag2)cout << "�ļ��𻵣��޷�����" << endl;
		else cout << "�鼮" << name << "�����ڣ�δ������" << endl;
	}
}

//�ָ0Ϊ���ܻ�ӭ����ָ1Ϊ�������ĵ��˷ָ�
vector<string> splitname(const string& str,int type) {
	vector<string> tokens;
	istringstream iss(str);
	string junk, name,username;
	iss >> junk >> username >> name;
	if(type)tokens.push_back(username);
	else tokens.push_back(name);
	return tokens;
}

//�����ܻ�ӭ����ͳ����ĵ��ˣ�0Ϊ�ܻ�ӭ���飬1Ϊ�����ĵ���
void popular(int type)
{
	int max=0,flag=0;
	ifstream infile("record.txt");
	if (!infile.is_open()) {
		cerr << "�޷����ļ�:record.txt" << endl;
		exit(1);
	}
	map<string, int> wordCount;
	string line;
	while (getline(infile, line)) {
		// ��ÿһ�н��зִ�
		vector<string> words = splitname(line,type);
		for (const string& word : words) {
			// ͳ��ÿ�����ʳ��ֵĴ���
			wordCount[word]++;
		}
	}
	infile.close();

	// ��wordCount������ת�Ƶ�vector��
	vector<pair<string, int>> sortedWordCount(wordCount.begin(), wordCount.end());

	// ��vector�������򣬰��յ��ʳ��ֵĴ�����������
	sort(sortedWordCount.begin(), sortedWordCount.end(),
		[](const pair<string, int>& a, const pair<string, int>& b) {
			return a.second > b.second; // ����
		});

	// ��ӡ�����ĵ��ʼ�����ִ���,���ڴ˸Ľ���ʾ�����˵Ľ��������������ı��������
	for (const auto& pair : sortedWordCount) {
		if (!flag)
		{
			max = pair.second;
			flag = 1;
			if (type)cout << "�������Ķ����� ";
			else cout << "���ܻ�ӭ���鼮�� ";
		}
		if (pair.second == max)
		{
			cout << pair.first << " ";
		}
	}
	if (type)cout << "������ " << max << " �Ρ�" << endl;
	else cout << "��������" << max << " �Ρ�" << endl;
}


class people//����
{
public:
	virtual void print()const = 0;
	int searchusername(char search[]) const;
protected:
	char username[28];//����
	char pw[28];//����
	int age;//����
	char sex;//�Ա� m-male f-female
};

int people::searchusername(char search[]) const
{
	int flag = 0;
	if (strstr(username, search))
	{
		flag = 1;
	}
	return flag;
}

class user :public people//ʹ������
{
public:
	virtual void print()const;
	void printbookrecord()const;
	friend istream& operator >> (istream& input, user& U);//�����������
	friend ostream& operator << (ostream& output, user& U);//����������
protected:
	int idnum;//ѧ��֤����֤��idnumber
	char identity[28];//ʹ���ߵ���� ѧ��/��ʦ/������Ա ����13������
	date ustart;//����Ȩ�޿�ʼ����
	date uend;//����Ȩ�޽�������
};

void user::print()const
{
	cout << "-----------------------------" << endl;
	cout << "type        ʹ����" << endl;
	cout << "name        " << username << endl;
	cout << "age         " << age << endl;
	if(sex=='m')cout << "sex         ��"  << endl;
	else cout << "sex         Ů" << endl;
	cout << "id number   " << idnum << endl;
	cout << "identity    " << identity << endl;
	cout << "start date  ";
	ustart.print();
	cout << endl;
	cout << "end date    ";
	uend.print();
	cout << endl;
	printbookrecord();
	cout << "-----------------------------" << endl;
}

void user::printbookrecord() const
{
	record* r = new record;
	char record[100], uname[28];
	int count = 0;
	strcpy(uname, username);
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	cout << "�����¼��" << endl;
	while (!infile.eof())
	{
		infile.getline(record, 100, '\n');
		if (*record == '\0')break;
		istrstream rs(record, 100);
		rs >> *r;
		if (r->searchusername(uname))
		{
			count++;
			recordtype = 1;
			cout << *r;
		}
	}
	recordtype = 0;
	infile.close();
	if (count)cout << "����" << count << "��������" << endl;
	else cout << "δ�ҵ�������" << endl;
}

istream& operator >> (istream& input, user& U)
{
	if (usertype)input >> U.idnum >> U.username >> U.pw >> U.age >> U.sex >> U.identity >> U.ustart >> U.uend;
	else
	{
		char junk;
		input >> junk >> U.idnum >> U.username >> U.pw >>U.age>> U.sex >> U.identity >>U.ustart>>U.uend;
	}
	return input;
}

ostream& operator << (ostream& output, user& U)
{
	output << "0 " << U.idnum << " " << U.username << " " << U.pw << " " << U.age << " " << U.sex << " " << U.identity << " " << U.ustart << " " << U.uend;
	return output;
}

class admin :public user//����Ա��
{
public:
	virtual void print()const;
	friend istream& operator >> (istream& input, admin& A);//�����������
	friend ostream& operator << (ostream& output, admin& A);//����������
protected:
	char position[28];//����ϵͳ�е�ְλ ����13������
	date astart;//����ԱȨ�޿�ʼ����
	date aend;//����ԱȨ�޽�������
};

void admin::print()const
{
	cout << "-----------------------------" << endl;
	cout << "type        ����Ա" << endl;
	cout << "name        " << username << endl;
	cout << "age         " << age << endl;
	if (sex == 'm')cout << "sex         ��" << endl;
	else cout << "sex         Ů" << endl;
	cout << "id number   " << idnum << endl;
	cout << "identity    " << identity << endl;
	cout << "user start  ";
	ustart.print();
	cout << endl;
	cout << "user end    ";
	uend.print();
	cout << endl;
	cout << "position    " << position << endl;
	cout << "admin start ";
	astart.print();
	cout << endl;
	cout << "admin end   ";
	aend.print();
	cout << endl;
	printbookrecord();
	cout << "-----------------------------" << endl;
}


istream& operator >> (istream& input, admin& A)
{
	if(usertype)input >> A.idnum >> A.username >> A.pw >> A.age >> A.sex >> A.identity >> A.ustart >> A.uend >> A.position >> A.astart >> A.aend;
	else
	{
		char junk;
		input >> junk >> A.idnum >> A.username >> A.pw >> A.age >> A.sex >> A.identity >> A.ustart >> A.uend >> A.position >> A.astart >> A.aend;
	}
	return input;
}

ostream& operator << (ostream& output, admin& A)
{
	output << "1 " << A.idnum << " " << A.username << " " << A.pw << " " << A.age << " " << A.sex << " " << A.identity << " " << A.ustart << " " << A.uend <<" "<<A.position<<" "<<A.astart<<" "<<A.aend;
	return output;
}

void listuser()
{
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	char line[200];
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//ʹ����
		{
			user u;
			people* p = &u;
			rs >> u;
			p->print();
		}
		else//����Ա
		{
			admin a;
			people* p = &a;
			rs >> a;
			p->print();
		}
	}
	infile.close();
}

//1 �������,2 �������
void _adduser(int type, ofstream& outfile)
{
	if (type == 1)//��ɨ����д�룬���������ʽ����
	{
		char line[200];
		int flag = 0;
		user* u = new user;
		cout << "������ʹ����ѧ�ţ����ţ������������롢���䡢�Ա��С�m����Ů��f��������ݡ�����Ȩ�޿�ʼ�����պͽ��������գ��м��á� ��������" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin.getline(line, 200, '\n');
		istrstream rs(line, 200);
		usertype = 1;
		rs >> *u;
		if (rs.fail())flag = 1;
		while (flag)
		{
			rs.clear();
			rs.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cout << "�����������������" << endl;
			cin.getline(line, 200, '\n');
			istrstream rs(line, 200);
			rs >> *u;
			if (rs.fail())flag = 1;
			else flag = 0;
		}
		usertype = 0;
		outfile << *u << endl;
		delete u;
	}
	else
	{
		int idnum, age;//ѧ��֤����֤��idnumber
		char username[28], pw[28], identity[28], sex;//ʹ���ߵ���� ѧ��/��ʦ/������Ա ����13������
		date ustart, uend;
		cout << "������ʹ����ѧ�ţ����ţ���" << endl;
		cin >> idnum;
		cout << "������ʹ����������" << endl;
		cin >> username;
		cout << "������ʹ�������룺" << endl;
		cin >> pw;
		cout << "������ʹ�������䣺" << endl;
		cin >> age;
		cout << "������ʹ�����Ա��С�m����Ů��f������" << endl;
		cin >> sex;
		cout << "������ʹ������ݣ�" << endl;
		cin >> identity;
		cout << "������ʹ���߽���Ȩ�޿�ʼ�����գ�" << endl;
		cin >> ustart;
		cout << "������ʹ���߽���Ȩ�޽��������գ�" << endl;
		cin >> uend;
		outfile << "0 " << idnum << " " << username << " " << pw << " " << age << " " << sex << " " << identity << " " << ustart << " " << uend << endl;
	}
}

void _addadmin(int type, ofstream& outfile)
{
	if (type == 1)
	{
		char line[200];
		int flag = 0;
		admin* a = new admin;
		cout << "���������Ա���š����������롢���䡢�Ա��С�m����Ů��f��������ݡ�����Ȩ�޿�ʼ�����ա����������ա�ְλ������ԱȨ�޿�ʼ�����պͽ��������գ��м��á� ��������" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin.getline(line, 200, '\n');
		istrstream rs(line, 200);
		usertype = 1;
		rs >> *a;
		if (rs.fail())flag = 1;
		while (flag)
		{
			rs.clear();
			rs.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cout << "�����������������" << endl;
			cin.getline(line, 200, '\n');
			istrstream rs(line, 200);
			rs >> *a;
			if (rs.fail())flag = 1;
			else flag = 0;
		}
		usertype = 0;
		outfile << *a << endl;
		delete a;
	}
	else
	{
		int idnum, age;//ѧ��֤����֤��idnumber
		char username[28], pw[28], identity[28], position[28], sex;//ʹ���ߵ���� ѧ��/��ʦ/������Ա ����13������
		date ustart, uend, astart, aend;//����Ȩ�޿�ʼ����
		cout << "���������Աѧ�ţ����ţ���" << endl;
		cin >> idnum;
		cout << "���������Ա������" << endl;
		cin >> username;
		cout << "���������Ա���룺" << endl;
		cin >> pw;
		cout << "���������Ա���䣺" << endl;
		cin >> age;
		cout << "���������Ա�Ա��С�m����Ů��f������" << endl;
		cin >> sex;
		cout << "���������Ա��ݣ�" << endl;
		cin >> identity;
		cout << "���������Ա����Ȩ�޿�ʼ�����գ�" << endl;
		cin >> ustart;
		cout << "���������Ա����Ȩ�޽��������գ�" << endl;
		cin >> uend;
		cout << "���������Աְλ��" << endl;
		cin >> position;
		cout << "���������Ա����Ȩ�޿�ʼ�����գ�" << endl;
		cin >> astart;
		cout << "���������Ա����Ȩ�޽��������գ�" << endl;
		cin >> aend;
		outfile << "1 " << idnum << " " << username << " " << pw << " " << age << " " << sex << " " << identity << " " << ustart << " " << uend << " " << position << " " << astart << " " << aend << endl;
	}
}

void adduser()
{
	int i, j, a[] = { 1,2 };
	cout << "�������������ݣ�" << endl;
	cout << "1 ʹ����" << endl;
	cout << "2 ����Ա" << endl;
	i = getint(a, 2);
	cout << "���������ӷ�ʽ��" << endl;
	cout << "1 �������" << endl;
	cout << "2 �������" << endl;
	j = getint(a, 2);
	ofstream outfile("user.txt", ios::app | ios::ate | ios::_Nocreate);
	if (i == 1){_adduser(j, outfile); }
	else//i==2
	{
		_addadmin(j, outfile);
	}
	outfile.close();
	cout << "��Ϣ�ѳɹ�д��" << endl;
}

//����record.txt���û���Ϣ
void searchuser()
{
	char username[28], line[200];
	int count = 0;
	cout << "������Ҫ���ҵ�������" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//ʹ����
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username)) { p->print();count = 1; }
		}
		else//����Ա
		{
			admin a;
			people* p = &a;
			rs >> a;
			if (p->searchusername(username)) { p->print();count = 1; }
		}
	}
	infile.close();
	if (!count)cout << "δ�ҵ���������" << username << "�Ľ��" << endl;
}

void deleteuser()
{
	char username[28], line[200];
	int count = 0, flag = 0, flag2 = 0;
	cout << "������Ҫɾ����������" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_user_.txt", ios::out | ios::app);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//ʹ����
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username)) flag = 1; 
			else outfile << u << endl;
		}
		else//����Ա
		{
			admin a;
			people* p = &a;
			rs >> a;
			if (p->searchusername(username)) flag = 1;
			else outfile << a << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("user.txt");
	flag2 = rename("_user_.txt", "user.txt");
	if (flag && !flag2)	cout << "�û�"<<username<<"�ѳɹ�ɾ��" << endl;
	else cout << "��Ǹ���������û�"<<username<<"���޷�ɾ��" << endl;
}

void changeuser()
{
	char username[28], line[200],doucument[] = "_user.txt_";
	int count = 0, flag = 0, flag2 = 0, j, arr[] = { 1,2 };
	cout << "������Ҫ�޸ĵ�������" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_user_.txt", ios::out | ios::app);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//ʹ����
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username))
			{
				p->print();
				cout << "�������޸ķ�ʽ��" << endl;
				cout << "1 �����޸�" << endl;
				cout << "2 �����޸�" << endl;
				j = getint(arr, 2);
				_adduser(j, outfile);
				flag = 1;
			}
			else outfile << u << endl;
		}
		else//����Ա
		{
			admin a;
			people* p = &a;
			rs >> a;
			if (p->searchusername(username))
			{
				p->print();
				cout << "�������޸ķ�ʽ��" << endl;
				cout << "1 �����޸�" << endl;
				cout << "2 �����޸�" << endl;
				j = getint(arr, 2);
				_addadmin(j, outfile);
				flag = 1;
			}
			else outfile << a << endl;
		}
	}
	infile.close();
	outfile.close();
	remove("user.txt");
	flag2 = rename("_user_.txt", "user.txt");
	if (flag && !flag2)	cout << "�û�" << username << "�ѳɹ��޸�" << endl;
	else cout << "��Ǹ���������û�" << username << "���޷��޸�" << endl;
}

void userlogin()
{
	char username[28], pw[28],line[200];
	int flag = 0;
	people* p;
	cout << "�������û���" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//ʹ����
		{
			user u;
			p = &u;
			rs >> u;
			if (p->searchusername(username)) {flag = 1; }
		}
		else//����Ա
		{
			admin a;
			p = &a;
			rs >> a;
			if (p->searchusername(username)) { flag = 1; }
		}
	}
	while(!flag)
	{
		cout << "û�д��û��������������û���" << endl;
		cin >> username;
		while (!infile.eof())
		{
			infile.getline(line, 200, '\n');
			if (*line == '\0')break;
			istrstream rs(line, 200);
			if (line[0] == '0')//ʹ����
			{
				user u;
				p = &u;
				rs >> u;
				if (p->searchusername(username)) { flag = 1; }
			}
			else//����Ա
			{
				admin a;
				p = &a;
				rs >> a;
				if (p->searchusername(username)) { flag = 1; }
			}
		}
	}
	cout << "����������" << endl;
	cin >> pw;
	{
		//if (strstr())cout <<"" << endl;
	}


	infile.close();
	//if (!flag)cout << "δ�ҵ���������" << username << "�Ľ��" << endl;



	cout << "" << endl;
}

int main()
{
	//searchbook();
	//addbook();
	//listbook();
	//changebook();
	//listbook();
	//char s[]="1 С�� ˮ䰴� 2024 7 23",a[20], b[20];
	//istrstream ts(s, 30);
	//ts >> a >> b;
	//cout << a << endl;
	//cout << b << endl;
	//addrecord();
	//listrecord();
	//searchrecord();
	//searchbookrecord();
	//searchuserrecord();
	//listrecord();
	//listuser();
	//adduser();
	//listuser();
	//searchuser();
	//deleteuser();
	//listuser();
	//changeuser();
	//listuser();
	string s = "abcd";
	if (s[0] == 'a')cout << "aaa" << endl;
	return 0;
}

//if (!file.is_open()) 
// {
//	cerr << "�޷����ļ�: " << filename << endl;
//	return 1;
//}