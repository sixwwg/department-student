#include<iostream>
#include"json.h"
#include <fstream>
#include <cassert>
#include<string>
#include<stdlib.h>
using namespace std;
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
	string save[15];
	int count_member=0;
};
departments dep[20];//20个部门 

string str1[12];
string str2[12];
string str3[12];
string str4[12];
string str5[12];
string str6[12];
int str1_count = 0;
int str2_count = 0;
void set_student(int num) //学生freetime信息处理 
{
	//int n;
	//n = sizeof(stu[num].free_time) / sizeof(string);
	//cout << "n=" << n << endl;
	//cout << "num=" << num << endl;
	for (int m = 0; ; m++)
	{
		if (stu[num].free_time[m].length() != 0)
		{
			str1[m] = stu[num].free_time[m].substr(0, 3);     //周几字符串截取 		
			str1_count++;
		}
		if (stu[num].free_time[m + 1].length() == 0)break;
	}
	for (int m = 0; m < str1_count; m++)
	{
		if (str1_count == 0)break;
		str2[m] = stu[num].free_time[m].substr(4, 5);       //开始时间 字符串截取 
		if (stu[num].free_time[m + 1].length() == 0)break;
	}
	for (int m = 0; m < str1_count; m++)
	{
		if (str1_count == 0)break;
		str3[m] = stu[num].free_time[m].substr(10, 11);   //结束时间字符串截取	
		if (stu[num].free_time[m + 1].length() == 0)break;
	}



}
void set_department(int num)
{

	for (int n = 0; ; n++)
	{
		if (dep[num].event_schedules[n].length() != 0)
		{
			str4[n] = dep[num].event_schedules[n].substr(0, 3); //周几字符串截取 
			str2_count++;
		}
		if (dep[num].event_schedules[n+1].length() == 0)break;


	}
	for (int n = 0; n < str2_count; n++)
	{
		if (str2_count == 0)break;
		str5[n] = dep[num].event_schedules[n].substr(4, 5); //周几字符串截取 
		if (dep[num].event_schedules[n + 1].length() == 0)break;
	}
	for (int n = 0; n < str2_count; n++)
	{
		if (str2_count == 0)break;
		str6[n] = dep[num].event_schedules[n].substr(10, 11); //周几字符串截取 
		if (dep[num].event_schedules[n + 1].length() == 0)break;
	}
}
int times = 0;
void application(int num)
{
	times++;
	cout <<"times="<< times << endl;
	int temp = 1;//判断该学生有没被其中一个部门录取过
	for (int i = 0; i<5 && temp == 1; i++)       //至多5个意向部门 
	{
		
		for (int j = 0; j<20 && temp == 1; j++)    //至多20个部门 
		{
			
			int count = 0;        //计数变量 
			if (stu[num].applications_department[i] == dep[j].department_no)       //第num个学生的第i个意向部门编号匹配到相应部门 
			{
				set_student(num);                       //对该学生的freetime进行处理 
				set_department(j);                      //对该部门的event_schedule进行处理 
				for (int stu_time_count = 0; stu_time_count<str1_count&&temp == 1; stu_time_count++)     //至多12个空闲时间段  
				{
					for (int dep_time_count = 0; dep_time_count<str2_count&&temp == 1; dep_time_count++) //至多12个活动时间段 
					{
						if (str1[stu_time_count].compare(str4[dep_time_count]) == 0)         //匹配星期几 
						{
							if (str2[stu_time_count].compare(str5[dep_time_count]) >= 0 && str3[stu_time_count].compare(str6[dep_time_count])<0)    //时间段比较 
							{
								if (dep[j].count_member < dep[j].member_limit)//如果该部门人数没收满
								{
									dep[j].save[count] = stu[num].student_no;         //满足条件就将该学生的学号存入对应的数组 
									dep[j].count_member++;//计数加一
									stu[num].student_no = "0";    //这学生已经被录取过     
									temp = 0;//该学生不能被其他部门录取
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

void unlucky_stu()  //未被部门选中的学生unlucky_student的输出函数 
{
	cout << '"' << "unlucky_student" << '"' << ':' << ' ' << '[' << endl;
	for (int i = 0; i<300; i++)
	{
		if (stu[i].student_no != "0")      //匹配过程中被选中就将其学号字符串赋值为"0"   
		{
			cout << "	" << '"' << stu[i].student_no << '"' << ',' << endl;
		}
	}
	cout << ']' << ',' << endl;
}
void admit()        //被选中的学生信息输出函数 
{
	cout << '"' << "admitted" << '"' << ':' << ' ' << '[' << endl;
	cout << '	' << '{' << endl;
	for (int i = 0; i<20; i++)
	{
		if (dep[i].save[0] != "0")              //该部门的学生保存信息第一个不为空 ，则表示有学生入选 
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
void unlucky_dep()       //没有学生入选的部门信息输出函数 
{
	cout << '"' << "unlucky_department" << '"' << ':' << ' ' << '[' << endl;
	for (int i = 0; i<20; i++)
	{
		if (dep[i].save[0] == "0")          //如果部门学生存储信息为0，就表示没有人入选 
		{
			cout << "	" << '"' << dep[i].department_no << '"' << ',' << endl;
		}
	}
	cout << ']' << ',' << endl;
}
void priority_choose()//优先级选择 
{

	for (int stu_no = 0; stu_no<300; stu_no++)   //对每个学生的意向部门进行筛选，匹配则将学生学号进行储存 
	{
		application(stu_no);
	}
}



int main()
{
	//freopen("output_data.txt", "w", stdout);//把结果写入output_data.txt
	ifstream ifs;
	ifs.open("input_data.txt");//读取input_data.txt
	assert(ifs.is_open());
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		return -1;
	}
	ifs.close();//读取完关闭input_data.txt
	for (int i = 0; i < 300; i++)//给学生赋值
	{
		int size ;
		size = root["students"][i]["free_time"].size();
		for (int j = 0; j< size; j++)//给空闲时间赋值
		{
			stu[i].free_time[j] = root["students"][i]["free_time"][j].asString();
			//cout << stu[i].free_time[j] << endl;
		}
		stu[i].student_no = root["students"][i]["student_no"].asString();//学号赋值
		//cout << stu[i].student_no;
		size = root["students"][i]["applications_department"].size();
		
		for (int j = 0; j< size; j++)//给意向部门赋值
		{
			stu[i].applications_department[j] = root["students"][i]["applications_department"][j].asString();
			//cout << stu[i].applications_department[j] << endl;
		}
		size = root["students"][i]["tags"].size();
		for (int j = 0; j< size; j++)//给兴趣标签赋值
		{
			stu[i].tags[j] = root["students"][i]["tags"][j].asString();
			//cout << stu[i].tags[j] << endl;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		int size;
		size = root["departments"][i]["event_schedules"].size();
		for (int j = 0; j< size; j++)//给活动时间赋值
		{
			dep[i].event_schedules[j] = root["departments"][i]["event_schedules"][j].asString();
			//cout << dep[i].event_schedules[j] << endl;
		}
		dep[i].member_limit = root["departments"][i]["member_limit"].asInt();//给限制人数赋值
		//cout << dep[i].member_limit << endl;
		dep[i].department_no = root["departments"][i]["department_no"].asString();//给部门编号
		//cout << dep[i].department_no << endl;
		size = root["departments"][i]["tags"].size();
		for (int j = 0; j< size; j++)//给兴趣标签赋值
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