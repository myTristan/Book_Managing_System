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
int recordtype=0;//0表示正常输出，1表示在查询人时输出
int usertype = 0;//0表示从文件中向计算机中读取，1表示从键盘读取
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
		cout << "输入错误，请重新输入" << endl;
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
		if(status)cout << "status      " << "外借" << endl;
		else cout << "status      " << "在架" << endl;
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
	friend ostream& operator << (ostream& output, book& B);//输出算符重载
private:
	char name[60];//书名
	char author[20];//作者
	char type[20];//类型
	char keywords[20];//关键词
	char intro[200];//简介
	bool status;//借阅状态（0表示在架，1表示外借）
};

ostream& operator << (ostream& output, book& B)
{
	output << "-----------------------------" << endl;
	output << "name        " << B.name << endl;
	output << "author      " << B.author << endl;
	output << "type        " << B.type << endl;
	output << "keywords    " << B.keywords << endl;
	output << "intro       " << B.intro << endl;
	if (B.status)output << "status      " << "外借" << endl;
	else output << "status      " << "在架" << endl;
	output << "-----------------------------" << endl;
	return output;
}


void searchbook()
{
	book* b=new book;
	char info[330],search[30];
	int count = 0;
	cout << "请输入要查找的书名：" << endl;
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
	if (count)cout << "共找到" << count<< "个包含" << search << "的结果" << endl;
	else cout << "未找到包含"<< search << "的结果" << endl;
	infile.close();
	delete b;
}

void addbook()//增加书目
{
	int i, arr[] = { 1,2 };
	cout << "请输入增加方式：" << endl;
	cout << "1 单行添加" << endl;
	cout << "2 逐项添加" << endl;
	i = getint(arr, 2);
	while (i != 1 && i != 2)
	{
		cout << "输入错误，请重新输入" << endl;
		cin >> i;
	}
	if (i == 1)
	{
		char info[330];
		cout << "请输入图书的书名，作者，类别，关键字，简介和借阅状态（0表示在架，1表示外借），每项之间用“|”隔开：" << endl;
		cin >> info;
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << info << endl;
		outfile.close();
	}
	else//i==2
	{
		char name[60];//书名
		char author[20];//作者
		char type[20];//类别
		char keywords[20];//关键词
		char intro[200];//简介
		int status;//借阅状态
		cout<<"请输入图书的书名："<<endl;
		cin >> name;
		cout << "请输入图书的作者：" << endl;
		cin >> author;
		cout << "请输入图书的类别：" << endl;
		cin >> type;
		cout << "请输入图书的关键字：" << endl;
		cin >> keywords;
		cout << "请输入图书的简介：" << endl;
		cin >> intro;
		cout << "请输入图书的借阅状态（0表示在架，1表示外借）：" << endl;
		cin >> status;
		while (cin.fail() || status != 0 || status != 1)
		{
			cout << "借阅状态输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cin >> status;
		}
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << name << "|" << author << "|" << type << "|" << keywords << "|" << intro << "|" << status << endl;
		outfile.close();
	}
	cout << "书籍已成功写入" << endl;
}

void deletebook()
{
	char info[330], info2[330],name[60];
	int flag = 0,flag2=0;
	ifstream infile("book.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_book_.txt", ios::out | ios::app);
	cout << "请输入删除书籍名称：" << endl;
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
	if (flag && !flag2)	cout << "书籍已成功删除" << endl;
	else cout<< "抱歉，不存在该书籍，无法删除" << endl;
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
	cout << "请输入修改书籍名称：" << endl;
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
			cout << "请输入修改方式：" << endl;
			cout << "1 全部修改" << endl;
			cout << "2 逐项修改" << endl;
			i = getint(a, 2);
			if (i == 1)
			{
				char info[330];
				cout << "请输入图书的书名，作者，类别，关键字，简介和借阅状态（0表示外借，1表示在架），每项之间用“|”隔开：" << endl;
				cin >> info;
				outfile << info << endl;
			}
			else//i==2
			{
				char name[60];//书名
				char author[20];//作者
				char type[20];//类别
				char keywords[20];//关键词
				char intro[200];//简介
				int status;//借阅状态
				cout << "请输入图书的书名：" << endl;
				cin >> name;
				cout << "请输入图书的作者：" << endl;
				cin >> author;
				cout << "请输入图书的类别：" << endl;
				cin >> type;
				cout << "请输入图书的关键字：" << endl;
				cin >> keywords;
				cout << "请输入图书的简介：" << endl;
				cin >> intro;
				cout << "请输入图书的借阅状态（0表示在架，1表示外借）：" << endl;
				cin >> status;
				while (cin.fail() || status != 0 || status != 1)
				{
					cout << "借阅状态输入错误，请重新输入" << endl;
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
	if (flag)	cout << "书籍已成功修改" << endl;
	else cout << "抱歉，不存在书籍"<<name<<"，故未作修改" << endl;
}
class date//日期类
{
public:
	void init(int y, int m, int d) { year = y;month = m;day = d; }
	int showy() { return year; }
	int showm() { return month; }
	int showd() { return day; }
	int GetYear() { return year; }
	void print() const{ cout << year << "." << month << "." << day; }
	friend istream& operator >> (istream& input, date& D);//输入算符重载
	friend ostream& operator << (ostream& output, date& D);//输出算符重载
private:
	int year, month, day;
};

istream& operator >> (istream& input, date& D)
{
	input >> D.year >> D.month >> D.day;
	return input;
}

//日期中间有空格，两端没有
ostream& operator << (ostream& output, date& D)
{
	output << D.year << " " << D.month << " " << D.day;
	return output;
}

class record//借书记录类
{
public:
	void print()
	{
		cout << "-----------------------------" << endl;
		cout << "username    " << username << endl;
		cout << "bookname    " << name << endl;
		if (status)
		{
			cout << "status      " << "未归还" << endl;
			cout << "start date  ";
			start.print();
			cout << endl;
		}
		else
		{
			cout << "status      " << "已归还" << endl;
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
	friend istream& operator >> (istream& input, record& R);//输入算符重载
	friend ostream& operator << (ostream& output, record& R);//输出算符重载
private:
	date start;//借书开始日期
	date end;//借书结束日期
	char name[60];//书名
	char username[28];//人名
	bool status;//借阅状态（0表示已归还，1表示未归还)
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

ostream& operator << (ostream& output, record& R)//输出算符重载
{
	if (recordtype)
	{
		output <<left<<setw(11)<< R.name<<" ";
		if (R.status)
		{
			output << "未归还，";
			R.start.print();
			output <<"借出" << endl;
		}
		else
		{
			output << "已归还，" ;
			R.start.print();
			output << "借出，" ;
			R.end.print();
			output << "归还" << endl;
		}
	}
	else
	{
		output << "-----------------------------" << endl;
		output << "name        " << R.username << endl;
		output << "bookname    " << R.name << endl;
		if (R.status)
		{
			output << "status      " << "未归还" << endl;
			output << "start date  ";
			R.start.print();
			output << endl;
		}
		else
		{
			output << "status      " << "已归还" << endl;
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
	cout << "请输入增加方式：" << endl;
	cout << "1 单行添加" << endl;
	cout << "2 逐项添加" << endl;
	i = getint(arr, 2);
	if (i == 1)
	{
		char record[100];
		cout << "请输入借阅状态（0表示已归还，1表示未归还)、借阅人、借书年月日和还书年月日（未归还不填写还书年月日），每项之间用“ ”隔开：" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin.getline(record, 100, '\n');
		ofstream outfile("record.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << record << endl;
		outfile.close();
	}
	else//i==2
	{
		char name[60];//书名
		char author[20];//作者
		char type[20];//类别
		char keywords[20];//关键词
		char intro[200];//简介
		int status;//借阅状态
		cout << "请输入图书的书名：" << endl;
		cin >> name;
		cout << "请输入图书的作者：" << endl;
		cin >> author;
		cout << "请输入图书的类别：" << endl;
		cin >> type;
		cout << "请输入图书的关键字：" << endl;
		cin >> keywords;
		cout << "请输入图书的简介：" << endl;
		cin >> intro;
		cout << "请输入图书的借阅状态（0表示在架，1表示外借）：" << endl;
		cin >> status;
		while (cin.fail() || status != 0 || status != 1)
		{
			cout << "借阅状态输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cin >> status;
		}
		ofstream outfile("book.txt", ios::app | ios::ate | ios::_Nocreate);
		outfile << name << "|" << author << "|" << type << "|" << keywords << "|" << intro << "|" << status << endl;
		outfile.close();
	}
	cout << "书籍已成功写入" << endl;
}

//列出借书记录
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

//查询用户借阅历史
void searchuserboookrecord()
{
	record* r = new record;
	char record[100],name[60];
	int count = 0;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	cout << "请输入要查找的书名：" << endl;
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
	if (count)cout << "共找到" << count << "个包含书名" << name << "的结果" << endl;
	else cout << "未找到包含书名" << name << "的结果" << endl;
}

//查询图书借阅历史
void searchbookrecord()
{
	char username[28];
	cout << "请输入要查找的人名：" << endl;
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
	if (count)cout << "共找到" << count << "个包含人名" << username << "的结果" << endl;
	else cout << "未找到包含人名" << username << "的结果" << endl;
	delete r;
}


//查找记录
void searchrecord()
{
	record* r = new record;
	char record[100];
	int count = 0,i;
	cout << "请输入查找方式：" << endl;
	cout << "1 按书名查找" << endl;
	cout << "2 按人名查找" << endl;
	cin >> i;
	while (i != 1 && i != 2)
	{
		cout << "输入错误，请重新输入" << endl;
		cin >> i;
	}
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	if (i == 1)
	{
		char name[60];
		cout << "请输入要查找的书名：" << endl;
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
		if (count)cout << "共找到" << count << "个包含书名" << name << "的结果" << endl;
		else cout << "未找到包含书名" << name << "的结果" << endl;
	}
	else//i==2
	{
		char username[28];
		cout << "请输入要查找的人名：" << endl;
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
		if (count)cout << "共找到" << count << "个包含人名" << username << "的结果" << endl;
		else cout << "未找到包含人名" << username << "的结果" << endl;
	}
	infile.close();
}

//还书更新记录
void returnrecord()
{
	record* r = new record;
	char record[100],name[60];
	int flag = 0, flag2 = 0, count = 0;
	ifstream infile("record.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_record_.txt", ios::out | ios::app);
	cout << "请输入归还书籍名称：" << endl;
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
				cout << "请输入还书年月日：" << endl;
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
	if (count&&!flag2)cout << "书籍记录已更改完成" << endl;
	else
	{
		if (flag)cout << "书籍" << name << "已经归还，无需更改" << endl;
		else if(flag2)cout << "文件损坏，无法更改" << endl;
		else cout << "书籍" << name << "不存在，未做更改" << endl;
	}
}

//分割，0为按受欢迎的书分割，1为按常借阅的人分割
vector<string> splitname(const string& str,int type) {
	vector<string> tokens;
	istringstream iss(str);
	string junk, name,username;
	iss >> junk >> username >> name;
	if(type)tokens.push_back(username);
	else tokens.push_back(name);
	return tokens;
}

//查找受欢迎的书和常借阅的人，0为受欢迎的书，1为常借阅的人
void popular(int type)
{
	int max=0,flag=0;
	ifstream infile("record.txt");
	if (!infile.is_open()) {
		cerr << "无法打开文件:record.txt" << endl;
		exit(1);
	}
	map<string, int> wordCount;
	string line;
	while (getline(infile, line)) {
		// 对每一行进行分词
		vector<string> words = splitname(line,type);
		for (const string& word : words) {
			// 统计每个单词出现的次数
			wordCount[word]++;
		}
	}
	infile.close();

	// 将wordCount的内容转移到vector中
	vector<pair<string, int>> sortedWordCount(wordCount.begin(), wordCount.end());

	// 对vector进行排序，按照单词出现的次数降序排序
	sort(sortedWordCount.begin(), sortedWordCount.end(),
		[](const pair<string, int>& a, const pair<string, int>& b) {
			return a.second > b.second; // 降序
		});

	// 打印排序后的单词及其出现次数,可在此改进显示所有人的借阅情况和所有书的被借阅情况
	for (const auto& pair : sortedWordCount) {
		if (!flag)
		{
			max = pair.second;
			flag = 1;
			if (type)cout << "借阅最多的读者是 ";
			else cout << "最受欢迎的书籍是 ";
		}
		if (pair.second == max)
		{
			cout << pair.first << " ";
		}
	}
	if (type)cout << "借阅了 " << max << " 次。" << endl;
	else cout << "被借阅了" << max << " 次。" << endl;
}


class people//人类
{
public:
	virtual void print()const = 0;
	int searchusername(char search[]) const;
protected:
	char username[28];//姓名
	char pw[28];//密码
	int age;//年龄
	char sex;//性别 m-male f-female
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

class user :public people//使用者类
{
public:
	virtual void print()const;
	void printbookrecord()const;
	friend istream& operator >> (istream& input, user& U);//输入算符重载
	friend ostream& operator << (ostream& output, user& U);//输出算符重载
protected:
	int idnum;//学生证或工作证号idnumber
	char identity[28];//使用者的身份 学生/教师/工作人员 至多13个汉字
	date ustart;//借书权限开始日期
	date uend;//借书权限结束日期
};

void user::print()const
{
	cout << "-----------------------------" << endl;
	cout << "type        使用者" << endl;
	cout << "name        " << username << endl;
	cout << "age         " << age << endl;
	if(sex=='m')cout << "sex         男"  << endl;
	else cout << "sex         女" << endl;
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
	cout << "借书记录：" << endl;
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
	if (count)cout << "共有" << count << "条借书结果" << endl;
	else cout << "未找到借书结果" << endl;
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

class admin :public user//管理员类
{
public:
	virtual void print()const;
	friend istream& operator >> (istream& input, admin& A);//输入算符重载
	friend ostream& operator << (ostream& output, admin& A);//输出算符重载
protected:
	char position[28];//管理系统中的职位 至多13个汉字
	date astart;//管理员权限开始日期
	date aend;//管理员权限结束日期
};

void admin::print()const
{
	cout << "-----------------------------" << endl;
	cout << "type        管理员" << endl;
	cout << "name        " << username << endl;
	cout << "age         " << age << endl;
	if (sex == 'm')cout << "sex         男" << endl;
	else cout << "sex         女" << endl;
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
		if (line[0] == '0')//使用者
		{
			user u;
			people* p = &u;
			rs >> u;
			p->print();
		}
		else//管理员
		{
			admin a;
			people* p = &a;
			rs >> a;
			p->print();
		}
	}
	infile.close();
}

//1 单行添加,2 逐项添加
void _adduser(int type, ofstream& outfile)
{
	if (type == 1)//先扫入再写入，避免输入格式不对
	{
		char line[200];
		int flag = 0;
		user* u = new user;
		cout << "请输入使用者学号（工号）、姓名、密码、年龄、性别（男“m”，女“f”）、身份、借书权限开始年月日和结束年月日，中间用“ ”隔开：" << endl;
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
			cout << "输入错误，请重新输入" << endl;
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
		int idnum, age;//学生证或工作证号idnumber
		char username[28], pw[28], identity[28], sex;//使用者的身份 学生/教师/工作人员 至多13个汉字
		date ustart, uend;
		cout << "请输入使用者学号（工号）：" << endl;
		cin >> idnum;
		cout << "请输入使用者姓名：" << endl;
		cin >> username;
		cout << "请输入使用者密码：" << endl;
		cin >> pw;
		cout << "请输入使用者年龄：" << endl;
		cin >> age;
		cout << "请输入使用者性别（男“m”，女“f”）：" << endl;
		cin >> sex;
		cout << "请输入使用者身份：" << endl;
		cin >> identity;
		cout << "请输入使用者借书权限开始年月日：" << endl;
		cin >> ustart;
		cout << "请输入使用者借书权限结束年月日：" << endl;
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
		cout << "请输入管理员工号、姓名、密码、年龄、性别（男“m”，女“f”）、身份、借书权限开始年月日、结束年月日、职位、管理员权限开始年月日和结束年月日，中间用“ ”隔开：" << endl;
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
			cout << "输入错误，请重新输入" << endl;
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
		int idnum, age;//学生证或工作证号idnumber
		char username[28], pw[28], identity[28], position[28], sex;//使用者的身份 学生/教师/工作人员 至多13个汉字
		date ustart, uend, astart, aend;//借书权限开始日期
		cout << "请输入管理员学号（工号）：" << endl;
		cin >> idnum;
		cout << "请输入管理员姓名：" << endl;
		cin >> username;
		cout << "请输入管理员密码：" << endl;
		cin >> pw;
		cout << "请输入管理员年龄：" << endl;
		cin >> age;
		cout << "请输入管理员性别（男“m”，女“f”）：" << endl;
		cin >> sex;
		cout << "请输入管理员身份：" << endl;
		cin >> identity;
		cout << "请输入管理员借书权限开始年月日：" << endl;
		cin >> ustart;
		cout << "请输入管理员借书权限结束年月日：" << endl;
		cin >> uend;
		cout << "请输入管理员职位：" << endl;
		cin >> position;
		cout << "请输入管理员管理权限开始年月日：" << endl;
		cin >> astart;
		cout << "请输入管理员管理权限结束年月日：" << endl;
		cin >> aend;
		outfile << "1 " << idnum << " " << username << " " << pw << " " << age << " " << sex << " " << identity << " " << ustart << " " << uend << " " << position << " " << astart << " " << aend << endl;
	}
}

void adduser()
{
	int i, j, a[] = { 1,2 };
	cout << "请输入增加内容：" << endl;
	cout << "1 使用者" << endl;
	cout << "2 管理员" << endl;
	i = getint(a, 2);
	cout << "请输入增加方式：" << endl;
	cout << "1 单行添加" << endl;
	cout << "2 逐项添加" << endl;
	j = getint(a, 2);
	ofstream outfile("user.txt", ios::app | ios::ate | ios::_Nocreate);
	if (i == 1){_adduser(j, outfile); }
	else//i==2
	{
		_addadmin(j, outfile);
	}
	outfile.close();
	cout << "信息已成功写入" << endl;
}

//查找record.txt中用户信息
void searchuser()
{
	char username[28], line[200];
	int count = 0;
	cout << "请输入要查找的人名：" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//使用者
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username)) { p->print();count = 1; }
		}
		else//管理员
		{
			admin a;
			people* p = &a;
			rs >> a;
			if (p->searchusername(username)) { p->print();count = 1; }
		}
	}
	infile.close();
	if (!count)cout << "未找到包含人名" << username << "的结果" << endl;
}

void deleteuser()
{
	char username[28], line[200];
	int count = 0, flag = 0, flag2 = 0;
	cout << "请输入要删除的人名：" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_user_.txt", ios::out | ios::app);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//使用者
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username)) flag = 1; 
			else outfile << u << endl;
		}
		else//管理员
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
	if (flag && !flag2)	cout << "用户"<<username<<"已成功删除" << endl;
	else cout << "抱歉，不存在用户"<<username<<"，无法删除" << endl;
}

void changeuser()
{
	char username[28], line[200],doucument[] = "_user.txt_";
	int count = 0, flag = 0, flag2 = 0, j, arr[] = { 1,2 };
	cout << "请输入要修改的人名：" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	ofstream outfile("_user_.txt", ios::out | ios::app);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//使用者
		{
			user u;
			people* p = &u;
			rs >> u;
			if (p->searchusername(username))
			{
				p->print();
				cout << "请输入修改方式：" << endl;
				cout << "1 单行修改" << endl;
				cout << "2 逐项修改" << endl;
				j = getint(arr, 2);
				_adduser(j, outfile);
				flag = 1;
			}
			else outfile << u << endl;
		}
		else//管理员
		{
			admin a;
			people* p = &a;
			rs >> a;
			if (p->searchusername(username))
			{
				p->print();
				cout << "请输入修改方式：" << endl;
				cout << "1 单行修改" << endl;
				cout << "2 逐项修改" << endl;
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
	if (flag && !flag2)	cout << "用户" << username << "已成功修改" << endl;
	else cout << "抱歉，不存在用户" << username << "，无法修改" << endl;
}

void userlogin()
{
	char username[28], pw[28],line[200];
	int flag = 0;
	people* p;
	cout << "请输入用户名" << endl;
	cin >> username;
	ifstream infile("user.txt", ios::in | ios::_Nocreate);
	while (!infile.eof())
	{
		infile.getline(line, 200, '\n');
		if (*line == '\0')break;
		istrstream rs(line, 200);
		if (line[0] == '0')//使用者
		{
			user u;
			p = &u;
			rs >> u;
			if (p->searchusername(username)) {flag = 1; }
		}
		else//管理员
		{
			admin a;
			p = &a;
			rs >> a;
			if (p->searchusername(username)) { flag = 1; }
		}
	}
	while(!flag)
	{
		cout << "没有此用户，请重新输入用户名" << endl;
		cin >> username;
		while (!infile.eof())
		{
			infile.getline(line, 200, '\n');
			if (*line == '\0')break;
			istrstream rs(line, 200);
			if (line[0] == '0')//使用者
			{
				user u;
				p = &u;
				rs >> u;
				if (p->searchusername(username)) { flag = 1; }
			}
			else//管理员
			{
				admin a;
				p = &a;
				rs >> a;
				if (p->searchusername(username)) { flag = 1; }
			}
		}
	}
	cout << "请输入密码" << endl;
	cin >> pw;
	{
		//if (strstr())cout <<"" << endl;
	}


	infile.close();
	//if (!flag)cout << "未找到包含人名" << username << "的结果" << endl;



	cout << "" << endl;
}

int main()
{
	//searchbook();
	//addbook();
	//listbook();
	//changebook();
	//listbook();
	//char s[]="1 小明 水浒传 2024 7 23",a[20], b[20];
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
//	cerr << "无法打开文件: " << filename << endl;
//	return 1;
//}