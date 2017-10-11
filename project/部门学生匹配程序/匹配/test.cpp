#include<iostream>
#include"json.h"
#include <fstream>
#include <cassert>
#include<string>
#include<stdlib.h>
using namespace std;
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
	string save[15];
	int count_member=0;
};
departments dep[20];//20������ 

string str1[12];
string str2[12];
string str3[12];
string str4[12];
string str5[12];
string str6[12];
int str1_count = 0;
int str2_count = 0;
void set_student(int num) //ѧ��freetime��Ϣ���� 
{
	//int n;
	//n = sizeof(stu[num].free_time) / sizeof(string);
	//cout << "n=" << n << endl;
	//cout << "num=" << num << endl;
	for (int m = 0; ; m++)
	{
		if (stu[num].free_time[m].length() != 0)
		{
			str1[m] = stu[num].free_time[m].substr(0, 3);     //�ܼ��ַ�����ȡ 		
			str1_count++;
		}
		if (stu[num].free_time[m + 1].length() == 0)break;
	}
	for (int m = 0; m < str1_count; m++)
	{
		if (str1_count == 0)break;
		str2[m] = stu[num].free_time[m].substr(4, 5);       //��ʼʱ�� �ַ�����ȡ 
		if (stu[num].free_time[m + 1].length() == 0)break;
	}
	for (int m = 0; m < str1_count; m++)
	{
		if (str1_count == 0)break;
		str3[m] = stu[num].free_time[m].substr(10, 11);   //����ʱ���ַ�����ȡ	
		if (stu[num].free_time[m + 1].length() == 0)break;
	}



}
void set_department(int num)
{

	for (int n = 0; ; n++)
	{
		if (dep[num].event_schedules[n].length() != 0)
		{
			str4[n] = dep[num].event_schedules[n].substr(0, 3); //�ܼ��ַ�����ȡ 
			str2_count++;
		}
		if (dep[num].event_schedules[n+1].length() == 0)break;


	}
	for (int n = 0; n < str2_count; n++)
	{
		if (str2_count == 0)break;
		str5[n] = dep[num].event_schedules[n].substr(4, 5); //�ܼ��ַ�����ȡ 
		if (dep[num].event_schedules[n + 1].length() == 0)break;
	}
	for (int n = 0; n < str2_count; n++)
	{
		if (str2_count == 0)break;
		str6[n] = dep[num].event_schedules[n].substr(10, 11); //�ܼ��ַ�����ȡ 
		if (dep[num].event_schedules[n + 1].length() == 0)break;
	}
}
int times = 0;
void application(int num)
{
	times++;
	cout <<"times="<< times << endl;
	int temp = 1;//�жϸ�ѧ����û������һ������¼ȡ��
	for (int i = 0; i<5 && temp == 1; i++)       //����5�������� 
	{
		
		for (int j = 0; j<20 && temp == 1; j++)    //����20������ 
		{
			
			int count = 0;        //�������� 
			if (stu[num].applications_department[i] == dep[j].department_no)       //��num��ѧ���ĵ�i�������ű��ƥ�䵽��Ӧ���� 
			{
				set_student(num);                       //�Ը�ѧ����freetime���д��� 
				set_department(j);                      //�Ըò��ŵ�event_schedule���д��� 
				for (int stu_time_count = 0; stu_time_count<str1_count&&temp == 1; stu_time_count++)     //����12������ʱ���  
				{
					for (int dep_time_count = 0; dep_time_count<str2_count&&temp == 1; dep_time_count++) //����12���ʱ��� 
					{
						if (str1[stu_time_count].compare(str4[dep_time_count]) == 0)         //ƥ�����ڼ� 
						{
							if (str2[stu_time_count].compare(str5[dep_time_count]) >= 0 && str3[stu_time_count].compare(str6[dep_time_count])<0)    //ʱ��αȽ� 
							{
								if (dep[j].count_member < dep[j].member_limit)//����ò�������û����
								{
									dep[j].save[count] = stu[num].student_no;         //���������ͽ���ѧ����ѧ�Ŵ����Ӧ������ 
									dep[j].count_member++;//������һ
									stu[num].student_no = "0";    //��ѧ���Ѿ���¼ȡ��     
									temp = 0;//��ѧ�����ܱ���������¼ȡ
								}						
							}
						}
					}
				}
			}
		}
	}
	cout << "finish" << endl;
}

void unlucky_stu()  //δ������ѡ�е�ѧ��unlucky_student��������� 
{
	cout << '"' << "unlucky_student" << '"' << ':' << ' ' << '[' << endl;
	for (int i = 0; i<300; i++)
	{
		if (stu[i].student_no != "0")      //ƥ������б�ѡ�оͽ���ѧ���ַ�����ֵΪ"0"   
		{
			cout << "	" << '"' << stu[i].student_no << '"' << ',' << endl;
		}
	}
	cout << ']' << ',' << endl;
}
void admit()        //��ѡ�е�ѧ����Ϣ������� 
{
	cout << '"' << "admitted" << '"' << ':' << ' ' << '[' << endl;
	cout << '	' << '{' << endl;
	for (int i = 0; i<20; i++)
	{
		if (dep[i].save[0] != "0")              //�ò��ŵ�ѧ��������Ϣ��һ����Ϊ�� �����ʾ��ѧ����ѡ 
		{
			cout << '	' << '"' << "member" << '"' << ':' << ' ' << '[' << endl;
			for (int l = 0;; l++)
			{
				if (dep[i].save[l].length() != 0)
					cout << '"' << dep[i].save[l] << '"' << endl;
				else break;

			}
			cout << ']' << ',' << endl;
			cout << '"' << "department_no" << '"' << ':' << '"' << dep[i].department_no << '"' << endl;
		}
		cout << '}' << ',' << endl;
	}

}
void unlucky_dep()       //û��ѧ����ѡ�Ĳ�����Ϣ������� 
{
	cout << '"' << "unlucky_department" << '"' << ':' << ' ' << '[' << endl;
	for (int i = 0; i<20; i++)
	{
		if (dep[i].save[0] == "0")          //�������ѧ���洢��ϢΪ0���ͱ�ʾû������ѡ 
		{
			cout << "	" << '"' << dep[i].department_no << '"' << ',' << endl;
		}
	}
	cout << ']' << ',' << endl;
}
void priority_choose()//���ȼ�ѡ�� 
{

	for (int stu_no = 0; stu_no<300; stu_no++)   //��ÿ��ѧ���������Ž���ɸѡ��ƥ����ѧ��ѧ�Ž��д��� 
	{
		application(stu_no);
	}
}



int main()
{
	//freopen("output_data.txt", "w", stdout);//�ѽ��д��output_data.txt
	ifstream ifs;
	ifs.open("input_data.txt");//��ȡinput_data.txt
	assert(ifs.is_open());
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		return -1;
	}
	ifs.close();//��ȡ��ر�input_data.txt
	for (int i = 0; i < 300; i++)//��ѧ����ֵ
	{
		int size ;
		size = root["students"][i]["free_time"].size();
		for (int j = 0; j< size; j++)//������ʱ�丳ֵ
		{
			stu[i].free_time[j] = root["students"][i]["free_time"][j].asString();
			//cout << stu[i].free_time[j] << endl;
		}
		stu[i].student_no = root["students"][i]["student_no"].asString();//ѧ�Ÿ�ֵ
		//cout << stu[i].student_no;
		size = root["students"][i]["applications_department"].size();
		
		for (int j = 0; j< size; j++)//�������Ÿ�ֵ
		{
			stu[i].applications_department[j] = root["students"][i]["applications_department"][j].asString();
			//cout << stu[i].applications_department[j] << endl;
		}
		size = root["students"][i]["tags"].size();
		for (int j = 0; j< size; j++)//����Ȥ��ǩ��ֵ
		{
			stu[i].tags[j] = root["students"][i]["tags"][j].asString();
			//cout << stu[i].tags[j] << endl;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		int size;
		size = root["departments"][i]["event_schedules"].size();
		for (int j = 0; j< size; j++)//���ʱ�丳ֵ
		{
			dep[i].event_schedules[j] = root["departments"][i]["event_schedules"][j].asString();
			//cout << dep[i].event_schedules[j] << endl;
		}
		dep[i].member_limit = root["departments"][i]["member_limit"].asInt();//������������ֵ
		//cout << dep[i].member_limit << endl;
		dep[i].department_no = root["departments"][i]["department_no"].asString();//�����ű��
		//cout << dep[i].department_no << endl;
		size = root["departments"][i]["tags"].size();
		for (int j = 0; j< size; j++)//����Ȥ��ǩ��ֵ
		{
			dep[i].tags[j] = root["departments"][i]["tags"][j].asString();
			//cout << dep[i].tags[j] << endl;
		}
	}
    //cout << "read success" << endl;
	priority_choose();
	unlucky_stu();
	admit();
	unlucky_dep();
	//system("pause");
	return 0;
}