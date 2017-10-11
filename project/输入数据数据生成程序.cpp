#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<sstream>
using namespace std;
string week[7] = { "Mon.","Tues.","Wed.","Thurs.","Fri.","Sat.","Sun." };
string ttags[12] = { "reading","programming","film","English","music","dance","basketball","football","chess","running","swimming","magic" };
//ѧ����Ϣ
struct student {
	string free_time[12];//����ʱ�� 
	string student_no;//ѧ�� 
	string applications_department[5];//������ 
	int dep_num;//�����Ÿ��� 
	string tags[8];//��Ȥ��ǩ 
	int tags_num;//��Ȥ��ǩ���� 
};
student stu[300];//300��ѧ�� 
				 //������Ϣ
struct departments {
	string event_schedules[12];//�ʱ��
	int  member_limit;//������������ 
	string department_no;//���ű�� 
	string tags[3];//��Ȥ��ǩ
	int tags_num;//��Ȥ��ǩ���� 
};
departments dep[20];//20������ 
int random_numm(int a, int b)//���� (a,b]������� 
{
	//srand((unsigned)time(NULL));
	int rander;
	rander = (rand() % (b - a)) + a + 1;
	return rander;
}
int random_num(int a, int b)//���� [a,b]������� 
{
	//srand((unsigned)time(NULL));
	int rander;
	rander = (rand() % (b - a + 1)) + a;
	return rander;
}
string num2str(int i)//����ת��Ϊ�ַ��� 
{
	stringstream ss;
	ss << i;
	return ss.str();
}
int day[2240][24] = { 0 };//������ŵ���ò��Żʱ���ѧ������ʱ��ʱ����� 
string random_freetime(int id)//��������Ŀ���ʱ�� 
{
	int a;
	a = random_num(0, 6);
	string dayy = week[a];
	int x = random_num(7, 20);//7�㵽21����п� 
	for (int i = x - 1; i<x + 1; i++)//�жϵ���ʱ���Ƿ���ظ� 
	{
		if (day[a + 7 * id][i] != 0)
		{
			x = random_num(7, 21);
		}
	}
	for (int i = x - 1; i<x + 1; i++)//�������ù���ʱ�丳ֵ 
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
void random_stu()//�������ѧ����Ϣ
{
	for (int i = 0; i<300; i++)//300��ѧ�� 
	{
		int a;
		a = random_num(1, 11);//ѧ���������ʱ�����Ŀ
		for (int j = 0; j<a; j++)//ÿ��ѧ���������ʱ�����Ŀ 
		{
			stu[i].free_time[j] = random_freetime(i);
		}
		stu[i].student_no = "031502" + num2str(100 + i);//����ѧ�� 
		a = random_num(0, 5);//ѧ����������ŵ���Ŀ
		stu[i].dep_num = a;//�����Ÿ��� 
		int numm[5];
		for (int j = 0; j<a; j++)//������ 
		{
			int b;
			b = random_num(0, 19);
			for (int x = 0; x<j; x++)//�����Ų����� 
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
		stu[i].tags_num = a;//��Ȥ��ǩ���� 
		int num[8];
		for (int j = 0; j<a; j++)//��Ȥ��ǩ 
		{
			int b;
			b = random_num(1, 11);
			for (int x = 0; x<j; x++)//��Ȥ��ǩ�����ظ� 
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
void random_dep()//������ɲ�����Ϣ 
{
	for (int i = 0; i<20; i++)//20������
	{
		int a;
		a = random_num(1, 11);//��������ʱ�����Ŀ	
		for (int j = 0; j<a; j++)//ÿ����������ʱ�����Ŀ
		{
			dep[i].event_schedules[j] = random_freetime(i + 300);
		}
		dep[i].member_limit = random_num(10, 15);//��������  
		if (i<10)
		{
			dep[i].department_no = "D00" + num2str(i);
		}
		else
		{
			dep[i].department_no = "D0" + num2str(i);
		}
		int num[3];
		a = random_num(1, 3);//��Ȥ��ǩ������� 
		dep[i].tags_num = a;
		for (int j = 0; j<a; j++)//��Ȥ��ǩ 
		{
			int y;
			y = random_num(1, 11);
			for (int x = 0; x<j; x++)//��Ȥ��ǩ�����ظ� 
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
void print_stu()//���ѧ����Ϣ 
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
