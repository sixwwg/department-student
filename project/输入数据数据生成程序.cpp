#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<sstream>
using namespace std;
string week[7] = { "Mon.","Tues.","Wed.","Thurs.","Fri.","Sat.","Sun." };
string ttags[12] = { "reading","programming","film","English","music","dance","basketball","football","chess","running","swimming","magic" };
//学生信息
struct student {
	string free_time[12];//空闲时间 
	string student_no;//学号 
	string applications_department[5];//意向部门 
	int dep_num;//意向部门个数 
	string tags[8];//兴趣标签 
	int tags_num;//兴趣标签个数 
};
student stu[300];//300个学生 
				 //部门信息
struct departments {
	string event_schedules[12];//活动时间
	int  member_limit;//部门人数限制 
	string department_no;//部门编号 
	string tags[3];//兴趣标签
	int tags_num;//兴趣标签个数 
};
departments dep[20];//20个部门 
int random_numm(int a, int b)//产生 (a,b]的随机数 
{
	//srand((unsigned)time(NULL));
	int rander;
	rander = (rand() % (b - a)) + a + 1;
	return rander;
}
int random_num(int a, int b)//产生 [a,b]的随机数 
{
	//srand((unsigned)time(NULL));
	int rander;
	rander = (rand() % (b - a + 1)) + a;
	return rander;
}
string num2str(int i)//数字转化为字符串 
{
	stringstream ss;
	ss << i;
	return ss.str();
}
int day[2240][24] = { 0 };//用来存放当天该部门活动时间或学生空闲时间时间情况 
string random_freetime(int id)//产生随机的空闲时间 
{
	int a;
	a = random_num(0, 6);
	string dayy = week[a];
	int x = random_num(7, 20);//7点到21点间有空 
	for (int i = x - 1; i<x + 1; i++)//判断当天时间是否会重复 
	{
		if (day[a + 7 * id][i] != 0)
		{
			x = random_num(7, 21);
		}
	}
	for (int i = x - 1; i<x + 1; i++)//给当天用过的时间赋值 
	{
		day[a + 7 * id][i] = 1;
	}
	string ttime = num2str(x);
	if(x<8)
	{
		ttime = dayy + "0"+ttime + ":00~" + "0"+num2str(x + 2) + ":00";
	}
	else if(x<10)
	{
		ttime = dayy + "0"+ttime + ":00~" + num2str(x + 2) + ":00";
	}
	else
	{
		ttime = dayy + ttime + ":00~" + num2str(x + 2) + ":00";
	}
	
	return ttime;
}
void random_stu()//随机生成学生信息
{
	for (int i = 0; i<300; i++)//300个学生 
	{
		int a;
		a = random_num(1, 11);//学生随机空闲时间的数目
		for (int j = 0; j<a; j++)//每个学生随机空闲时间的数目 
		{
			stu[i].free_time[j] = random_freetime(i);
		}
		stu[i].student_no = "031502" + num2str(100 + i);//生成学号 
		a = random_num(0, 5);//学生随机意向部门的数目
		stu[i].dep_num = a;//意向部门个数 
		int numm[5];
		for (int j = 0; j<a; j++)//意向部门 
		{
			int b;
			b = random_num(0, 19);
			for (int x = 0; x<j; x++)//意向部门不能重 
			{
				if (numm[x] == b)
				{
					b = random_num(0, 19);
					x = 0;
				}
			}
			numm[j] = b;
			if (b<10)
			{
				stu[i].applications_department[j] = "D00" + num2str(b);
			}
			else
			{
				stu[i].applications_department[j] = "D0" + num2str(b);
			}
		}
		a = random_num(1, 8);
		stu[i].tags_num = a;//兴趣标签个数 
		int num[8];
		for (int j = 0; j<a; j++)//兴趣标签 
		{
			int b;
			b = random_num(1, 11);
			for (int x = 0; x<j; x++)//兴趣标签不能重复 
			{
				if (num[x] == b)
				{
					b = random_num(1, 11);
					x = 0;
				}
			}
			num[j] = b;
			stu[i].tags[j] = ttags[b];
		}
	}
}
void random_dep()//随机生成部门信息 
{
	for (int i = 0; i<20; i++)//20个部门
	{
		int a;
		a = random_num(1, 11);//部门随机活动时间的数目	
		for (int j = 0; j<a; j++)//每个部门随机活动时间的数目
		{
			dep[i].event_schedules[j] = random_freetime(i + 300);
		}
		dep[i].member_limit = random_num(10, 15);//限制人数  
		if (i<10)
		{
			dep[i].department_no = "D00" + num2str(i);
		}
		else
		{
			dep[i].department_no = "D0" + num2str(i);
		}
		int num[3];
		a = random_num(1, 3);//兴趣标签随机个数 
		dep[i].tags_num = a;
		for (int j = 0; j<a; j++)//兴趣标签 
		{
			int y;
			y = random_num(1, 11);
			for (int x = 0; x<j; x++)//兴趣标签不能重复 
			{
				if (num[x] == y)
				{
					y = random_num(1, 11);
					x = 0;
				}
			}
			num[j] = y;
			dep[i].tags[j] = ttags[y];
		}
	}
}
void print_stu()//输出学生信息 
{
	cout << "{" << endl;
	cout << '"' << "students" << '"' << ":[ " << endl;
	for (int i = 0; i<300; i++)
	{
		cout << "{" << endl;
		cout << '"' << "free_time" << '"' << ": [" << endl;
		for (int j = 0; j<12 && stu[i].free_time[j].length() != 0; j++)
		{
			cout << '"' << stu[i].free_time[j] << '"';
			if (stu[i].free_time[j + 1].length() != 0)cout << ",";
			cout << endl;
		}
		cout << "]," << endl;
		cout << '"' << "student_no" << '"' << ":" << '"' << stu[i].student_no << '"' << "," << endl;
		cout << '"' << "applications_department" << '"' << ": [" << endl;
		for (int j = 0; j<stu[i].dep_num; j++)
		{
			cout << '"' << stu[i].applications_department[j] << '"';
			if ((j + 1) != stu[i].dep_num)cout << ",";
			cout << endl;
		}
		cout << "]," << endl;
		cout << '"' << "tags" << '"' << ": [" << endl;
		for (int j = 0; j<stu[i].tags_num; j++)
		{
			cout << '"' << stu[i].tags[j] << '"';
			if ((j + 1) != stu[i].tags_num)cout << ",";
			cout << endl;
		}
		cout << "]" << endl;
		cout << "}";
		if (i != 299)cout << ",";
		cout << endl;
	}
	cout << "]," << endl;
}
void print_dep()
{
	cout << '"' << "departments"<< '"' << ":[ " << endl;
	for (int i = 0; i<20; i++)
	{
		cout << "{" << endl;
		cout << '"' << "event_schedules" << '"' << ": [" << endl;
		for (int j = 0; j<12 && dep[i].event_schedules[j].length() != 0; j++)
		{
			cout << '"' << dep[i].event_schedules[j] << '"';
			if (dep[i].event_schedules[j + 1].length() != 0)cout << ",";
			cout << endl;
		}
		cout << "]," << endl;
		cout << '"' << "member_limit" << '"' << ":" << dep[i].member_limit << "," << endl;
		cout << '"' << "department_no" << '"' << ":" << '"' << dep[i].department_no << '"' << "," << endl;
		cout << '"' << "tags" << '"' << ": [" << endl;
		for (int j = 0; j<dep[i].tags_num; j++)
		{
			cout << '"' << dep[i].tags[j] << '"';
			if ((j + 1) != dep[i].tags_num)cout << ",";
			cout << endl;
		}
		cout << "]" << endl;
		cout << "}";
		if (i != 19)cout << ",";
		cout << endl;
	}
	cout << "]" << endl;
	cout << "}" << endl;
}
int main()
{
	freopen("input_data.txt", "w", stdout);
	random_stu();
	random_dep();
	print_stu();
	print_dep();
	return 0;
}
