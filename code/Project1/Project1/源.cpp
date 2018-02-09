#include<iostream>
using namespace std;
#include<math.h>
#define Groupsize 5       //�����װ������������(�������װ�س˿���Ŀ)
#define Time_waiting 12  //ÿ���ͣ��ʱ��Ϊ12��
#define time_gap 3        //����һ�������ʱ��Ϊ3��
#define Power 2.67        //���ݵ������ܺ�Ϊ9.6kwh����2.67w/s
#define Wait_P 30       //���ݵ�ͣ���ܺ�Ϊ�����30w��ÿ�μ����������ƶ��ܺı������߳�5-6�������й����2.67*4*3=30w��
#define k1 2           //����ʱ������Ȩֵ
#define k2 1           //�����ܺ�����Ȩֵ
#define height 5       //����¥��߶�


struct Elevator                     //������ݽṹ��
{
	int ef, flag, f_num, status, floor;
	//����������еĵ�������Զ����¥�㣬�����б�־��¥�������������ݱ�־,Ŀǰ¥��
	//Elevator *next;//����ָ����һ��
};
struct Person                        //�����˽ṹ��
{
	int Decision[Groupsize];//ÿ���˵�Ŀ��¥��,�ް���Ϊ0
	int waiting_num;//ÿ������
	int Request;//�ڲ������־
	int time_ask[Groupsize];//ÿ���˵�Ŀ��¥������ʱ��
};


struct Elevator ele1, ele2;
struct Person per[Groupsize];

double Clock = 0;
double iniClock = 0;
double Energy = 0;
double iniEnergy = 0;
int record_floor[height] ;
//int earliest;//������������ʱ��


//���ߺ��������ֵ
int MAX(int a, int b)
{
	if (a >= b) return a;
	else return b;
}
//��ʼ���˵Ľṹ��
void init_person()
{
	int i,j;
	cout << "�������˵�����"<<endl;

	for (i = 0;i < Groupsize;i++)
	{
		cout << "�����" << i + 1 << "���������������ʱ��" << endl;
		for (j = 0;j < Groupsize;j++)
		{
			cin >> per[i].Decision[j] >> per[i].time_ask[j];
			if (per[i].Decision[j] == 1) 
			{
				cout << "�е�"<<i+1<<"��"<<"����"<<j+1<<"��ĵ�����"<<endl;
			}
			if (per[i].Decision[j] != 1)
			{
				cout << "û�е�" << i + 1 << "��" << "����" << j + 1 << "��ĵ�����" << endl;
			}
		}
		cout << "�������"<<i+1<<"���ڲ������־����������" << endl;
		cin >> per[i].Request>>per[i].waiting_num;
		cout << "��" << i+1 << "����ڲ���������������ֱ�Ϊ" << per[i].Request << "��" << per[i].waiting_num << endl;
	}
	record_floor[height] = { 0 };
	cout << "�����˵���������"<<endl;
	cout << "��ʾ�������" << endl;
	cout << "\t"<<"1"<<"\t"<<"2"<<"\t"<<"3"<<"\t"<<"4"<<"\t"<<"5"<< endl;
	for (i = 0;i < Groupsize;i++)
	{
		cout << i +1<< "\t";
		for (j = 0;j < Groupsize;j++)
			cout << per[i].Decision[j] << '\t';
		cout << endl;
	}

}


//��λ���ݲ���
void Reset_Elevator()
{
	int m,n;
	
	
	cout << "��������Ҫ��ʼ���ĵ��ݵ����"<<endl ;
	cin >> m;
if (m == 1)
	{
		    ele1.flag = ele1.f_num= ele1.status = 0;
			cout << "�������ʼʱ���ݵ�λ�����ģ�";
			cin >> ele1.floor;
			ele1.ef = ele1.floor;
			//ele1.next = &ele1;
	}
	else if(m==2)
	{
		ele2.flag = ele2.f_num = ele2.status = 0;
		cout << "�������ʼʱ���ݵ�λ�����ģ�";
		cin >> ele2.floor;
		ele2.ef = ele2.floor;
		//ele2.next = &ele2;
	}
	else
	{
		cout << "��ѯ��������Ҫ�ĵ���"<<endl ;
		Reset_Elevator();
     }
	cout << "�Ƿ���Ҫ�������е��ݸ�λ���������밴1�����밴��1�����";
	cin >> n;
	if (n == 1)  Reset_Elevator();
}


//��ѯ���������¥��ĸ�������¼��Щ�㷢��������
int Search_floor()
{
	int temp;//��¼���ٸ�¥�㷢��������
	int i, j;
	int m=0;
	temp = 0;
	for (i = 0;i < Groupsize;i++)
		for (j = 0;j < Groupsize;j++)
		{
			if (per[i].Decision[j] != 0)
			{
				temp = temp + 1;
				record_floor[m++] = i;
				break;
			}
		}
	return temp;
}




//��Ѱ��������¥���¥����
int tem;
int Search_ear()
{
	int temp1,temp2;
	int i,j;
	temp1 = 0;
	for (i = 0;i < Groupsize;i++)
	{
		
		temp2 = per[0].time_ask[0];
		for (j = 0;j < Groupsize;j++)
		{
			if (temp2 >= per[i].time_ask[j]&&per[i].Decision [j]==1)
			{
				temp2 = per[i].time_ask[j];
				temp1 = i;
				tem = j;
			}
        }
     }
	cout << temp1;
	if (per[temp1].Decision[tem] == 0)
	{
		return 9;
	}
	else
	return temp1;
}

//����¥����Ϣ����Ѱ��i��ı߽�Ŀ��¥��(min,max)��Ŀ��¥����(num)������¥����(upf,downf)
int min[Groupsize], max[Groupsize];
int upf[Groupsize], downf[Groupsize];
int Search_eag(int flr)
{
	int i;
	int num=0;
	upf[Groupsize] = 0; downf[Groupsize] = 0;
	max[Groupsize] = 0;min[Groupsize] = 0;

	for (i = 0;i < Groupsize;i++)
	{
		if (per[flr].Decision[i] == 1)
		{
			min[flr] = i+1;
			break;
		}
	}
	for (i = 0;i < Groupsize;i++)
	{
		if (per[flr].Decision[i] == 1)
		{
			max[flr] = i+1;
			num = num + 1;
			if (per[flr].Decision[i]==1&& i < flr) downf[flr] = downf[flr] + 1;
			else if (per[flr].Decision[i] ==1&&i> flr) upf[flr] = upf[flr] + 1;
		}
	}
	return num;

}


//����¥�����
int goal2[Groupsize];
void Set_mission(int flr)
{
	int i, temp;
	temp = 0;
	if (ele1.status != 0 && ele2.status == 0)
	{
		cout << "1���ݽ������������������" << endl;
	}
	if (ele1.status == 0 && ele2.status != 0)
	{
		cout << "2���ݽ������������������" << endl;
	}
	if (ele1.status == 0 && ele2.status == 0)
	{
		cout << "û�����󣬵��ݲ�����" << endl;
	}
	/*if (ele1.status == 1 && ele2.status == 1)
	{
		for (i = flr;i < Groupsize;i++)
		{
			if (per[flr].Decision[i] != 0)
				temp++;
			if (temp == upf[flr] / 2)
			{
				goal2[flr] = i+1;
				break;
			}
			cout << "���������ݷֱ�������е�" << max[flr] << goal2[flr] << "�������" << endl;
		}
	}*/
	if (ele1.status == 1 && ele2.status == 2)
	{
		for (i = 0;i <Groupsize;i++)
		{
			if (per[flr].Decision[i] != 0)
				temp++;
			if (temp == upf[flr] / 2)
			{
				goal2[flr] = i+1;
				
				break;
			}
		}
	}
	if (ele1.status == 2 && ele2.status == 1)
	{
		for (i = 0;i <Groupsize;i++)
		{
			if (per[flr].Decision[i] != 0)
				temp++;
			if (temp == upf[flr] / 2)
			{
				goal2[flr] = i + 1;

				break;
			}
		}
	}
	//if (ele1.status == 1 && ele2.status == 2)
		//cout << "1��ִ����������2��ִ���½�����" << endl;
	if (ele1.status == 2 && ele2.status == 1)
		cout << "1�ŵ���ִ���½�����2�ŵ���ִ����������" << endl;
}


//��������������״̬
void Det_state(int m)
{
	int temp1, temp2;
	temp1 = abs(m+1 - ele1.floor);
	temp2 = abs(m +1- ele2.floor);

	if (temp1 <= temp2)
	{
		ele1.flag = m+1 > ele1.floor ? 1 : 2;
		ele1.status=1;
		ele1.ef = ele1.flag == 1 ? max[m] : min[m];
		
	}
	else
	{
		ele2.flag= m+1 > ele1.floor ? 1 : 2;
		ele2.status= 1;
		ele2.ef = ele2.flag == 1 ? max[m] : min[m];
		
	}
}

//�����ε���״̬
void Det_sec(int i)
{
	int j,up=0, down=0;
	cout << min[i] << max[i]<<upf[i]<<downf[i];
	for (j = 0;j < Groupsize;j++)
	{
		if (per[i].Decision[j]==1&&j>i) up = 1;
		else if (per[i].Decision[j]==1 && j<i) down = 1;
	}
	cout << up << down << endl;
	if(ele1.status==1)
	{ 
		if ((min[i] - i - 1)*(max[i] - i - 1) < 0)
		{
			ele2.status = 2;
			if (up&down == 0) ele2.flag = ele1.flag;
			if (up&down == 1)ele2.flag = 3 - ele1.flag;
			cout << "a";

		}
		if (per[i].waiting_num > 10)
	    {
			ele2.status = 2;
			if (up*down == 0) ele2.flag = ele1.flag;
			if (up*down == 1)ele2.flag = 3 - ele1.flag;
			cout << "b";
	     }
	}
	if (ele2.status == 1)
	{
		if (up*down==1)
		{
			ele1.status = 2;
		    ele1.flag = 3 - ele2.flag;
			cout << "c";
		}
		if (per[i].waiting_num > 10)
		{
			ele1.status = 2;
			if (up&down == 0) ele1.flag = ele2.flag;
			if (up&down == 1)ele1.flag = 3 - ele2.flag;
			cout << "d";
		}
	}
}



//��һ��¥�㷢������ʱ������״̬
void Running_1()
{
	int i;
	int m;
	int dom;
	int num;//Ŀ��¥����
	i = Search_ear();
	Det_state(i);
	Det_sec(i);
	Set_mission(i);
	cout << "��λ" << ele1.status << ele2.status << goal2[i];



	if (per[i].waiting_num <= 10)
	{
		if (ele1.status == 0)
		{
			Clock = Clock + time_gap*abs(i + 1 - ele2.floor) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] + min[i] - 2 * i - 2);
			Energy = Energy + Power*(abs(i + 1 - ele2.floor) + abs(max[i] + min[i] - 2 * i - 2)) + Wait_P*(upf[i] + downf[i] + 1);
			cout << "1�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;
			cin >> m;
			iniClock = iniClock + time_gap*abs(i + 1 - ele1.floor) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] + min[i] - 2 * i - 2);
			iniEnergy = iniEnergy + Power*(abs(i + 1 - ele1.floor) + abs(max[i] + min[i] - 2 * i - 2)) + Wait_P*(upf[i] + downf[i] + 1);
			cout << "1ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;

		}
		else if (ele1.status == 1)
		{
			if (ele2.status == 0)
			{
				Clock = Clock + time_gap*abs(i + 1 - ele1.floor) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] + min[i] - 2 * i - 2);
				Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(max[i] + min[i] - 2 * i - 2)) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "2�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;
				cin >> m;
				iniClock = iniClock + time_gap*abs(i + 1 - ele1.floor) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] + min[i] - 2 * i - 2);
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele1.floor) + abs(max[i] + min[i] - 2 * i - 2)) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "2ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
			}
			if (ele2.status == 2)
			{
				Clock = Clock + time_gap*abs(i + 1 - ele2.floor) + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]));
				Energy = Energy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "3�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;
				cin >> m;
				if (ele1.flag == 1)
				{
					iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(i + 1 - ele1.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor));
					iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
					cout << "3ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
				}

				else
				{
					iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(i + 1 - ele1.floor));
					iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
					cout << "4ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
				}
			}
		}



		else if (ele1.status == 2)
		{
			Clock = Clock + time_gap*abs(i + 1 - ele1.floor) + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]));
			Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
			cout << "4�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;
			if (ele2.flag == 1)
			{
				iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(i + 1 - ele1.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor));
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "5ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
			}
			else if (ele2.flag == 2)
			{
				iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(i + 1 - ele1.floor));
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "6ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
			}
		}
	}


	else if (per[i].waiting_num > 10)
	{
		if (upf[i] * downf[i] != 0)
		{
			if (ele1.flag == 1)
			{
				Clock = Clock + MAX(time_gap*abs(i + 1 - ele1.floor) + Time_waiting*upf[i] + time_gap*(max[i] - i - 1), time_gap*abs(i + 1 - ele2.floor) + Time_waiting*downf[i] + time_gap*(i + 1 - min[i]));
				Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "5�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;

				iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(i + 1 - ele1.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor));
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "7ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
			}
			else if (ele1.flag == 2)
			{
				Clock = Clock + MAX(time_gap*abs(i + 1 - ele1.floor) + Time_waiting*upf[i] + time_gap*(i + 1 - min[i]), time_gap*abs(i + 1 - ele2.floor) + Time_waiting*downf[i] + time_gap*(max[i] - i - 1));
				Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "6�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;

				iniClock = iniClock + MAX(Time_waiting*upf[i] + time_gap*(max[i] - i - 1) + time_gap*abs(2 * i + 2 - ele1.floor - ele2.floor), Time_waiting*downf[i] + time_gap*(i + 1 - min[i]) + time_gap*abs(i + 1 - ele1.floor));
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele2.floor) + abs(i + 1 - ele1.floor) + abs(max[i] - min[i])) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "8ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
			}
		}

		else
		{
			if (ele1.status == 1)
			{
				cout << "2��λ" << ele2.status << endl;
				cout << "1��2�ŵ��ݷֱ�������е�" << max[i] << goal2[i] << "�������" << endl;
				Clock = Clock + time_gap * abs(i + 1 - ele2.floor) + Time_waiting*(upf[i] + downf[i]) / 2 + time_gap*abs(max[i] - i - 1);
				Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + 2 * abs(max[i] + min[i] - i - 1) - abs(goal2[i] - i)) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "7�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;

				iniClock = iniClock + time_gap * (abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor)) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] - i - 1);
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + 2 * abs(max[i] + min[i] - i - 1)) + 2 * Wait_P*(upf[i] + downf[i]);
				cout << "9ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
				cin >> m;
			}
			else if (ele1.status == 2)
			{
				Clock = Clock + time_gap * abs(i + 1 - ele1.floor) + Time_waiting*(upf[i] + downf[i]) / 2 + time_gap*abs(max[i] - i - 1);
				Energy = Energy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + 2 * abs(max[i] + min[i] - i - 1) - abs(goal2[i] - i)) + Wait_P*(upf[i] + downf[i] + 1);
				cout << "8�Ľ���������ʹ����" << Clock << "��ʱ�䵥λ" << endl << "ʹ����" << Energy << "��������λ" << endl;

				iniClock = iniClock + time_gap * (abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor)) + Time_waiting*(upf[i] + downf[i]) + time_gap*abs(max[i] - i - 1);
				iniEnergy = iniEnergy + Power*(abs(i + 1 - ele1.floor) + abs(i + 1 - ele2.floor) + 2 * abs(max[i] + min[i] - i - 1)) + 2 * Wait_P*(upf[i] + downf[i]);
				cout << "10ԭϵͳ���㷨��ʹ����" << iniClock << "��ʱ�䵥λ" << endl << "ʹ����" << iniEnergy << "��������λ" << endl;
				cin >> m;
			}
		}


	}
}


//��������ģʽ
void Det_model(int num_req)
{
	switch (num_req)
	{
	case 0:
	{
		cout << "û������" << endl;
		init_person();
		break;
	}
	case 1:Running_1();

	}
}

void main()
{
	
	int num_req;
	int i;
	int num;
	    cout << "===========================================================================" << endl;
		cout << "==========================��ӭ�������ܵ���ʹ�ý���=========================" << endl;
		cout << "========================�����ˣ����𣬹����룬��FԶ=======================" << endl;
		cout << "===========================================================================" <<endl<<endl<< endl;
	
		cout << "===                    ��������г�ʼ������ʼ��������Ϊ��       ===========" << endl;
		cout << "===                     1.�˵�����ĳ�ʼ����                    ===========" << endl;
		cout << "===                     2.���ݵĳ�ʼ����                        ===========" << endl;
		init_person();
		i = Search_ear();
		
		num = Search_eag(i);
		while(1)
		{
		Reset_Elevator();
		cout << "===========================================================================" << endl;
		cout << "=================================��ʼ�������==============================" << endl;
		cout << "===========================================================================" << endl;
		cout << "===========================================================================" << endl;
		cout << "=============================���ڽ���ʾ�������н��========================" << endl;
		cout << "===========================================================================" << endl;
		num_req = Search_floor();

		Det_model(num_req);
		Clock = iniClock = Energy = iniEnergy = 0;
		

	}
}