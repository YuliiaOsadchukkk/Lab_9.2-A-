#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Spec{ ��, ��, ��, �� };
string SpecStr[] = { "��", "��", "��", "��" };

struct  Student
{
	string prizv;
	Spec spec;
	int kurs;
	int Fiz;
	int Mat;
	int Inf;
	double Mark;
};

void Create(Student* s, const int N);
void Average(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, const Spec spec, const double Mark);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{ 
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 

	int N;
	cout << "������ ������� �������� N: "; cin >> N;
	Student* s = new Student[N];
	int ispec;
	Spec spec;
	string prizv;
	int kurs = 0;
	double Mark = 0;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ������� ����� ���� �� ������� �� ��������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;
		cout << " [6] - ���������� ���������� ���� �� ����� � ���������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;

		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			break;
		case 4:
			cout << "������ ����� ������:" << endl;
			cout << " ������������ (0 - ��, 1 - ��, 2 - ��, 3 - ��): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get(); 
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << "������ ������� ���"; cin >> Mark;
			cout << endl; 
			if ((found = BinSearch(s, N, prizv,spec,Mark)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 6:
			Average(s, N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}


void Create(Student* s, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " �������: "; getline(cin, s[i].prizv);
		cout << " ����: "; cin >> s[i].kurs;
		cout << " ������������ (0 - ��, 1 - ��, 2 - ��, 3 - ��): "; cin >> spec;
		s[i].spec = (Spec)spec;
		cout << "������ � ������ :"; cin >> s[i].Fiz;
		cout << "������ � ���������� :"; cin >> s[i].Mat;
		cout << "������ � ����������� :"; cin >> s[i].Inf;
	}
}

void Average(Student* s, const int N)
{
	for (int i = 0; i < N; i++)
	{
		double average = (s[i].Fiz + s[i].Mat + s[i].Inf) / 3.;
		s[i].Mark = average;
	}
}

void Print(Student* s, const int N)
{
	cout << "======================================================================================"
		<< endl;
	cout << "| � | ������� | ���� |������������| Գ���� | ����������|  ����������� |������� ���|"
		<< endl;
	cout << "--------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[i].prizv
			<< "| " << setw(4) << right << s[i].kurs << " "
			<< "| " << setw(11) << right << SpecStr[s[i].spec] << " "
			<< "| " << setw(6) << right << s[i].Fiz << " "
			<< "| " << setw(9) << right << s[i].Mat << " "
			<< "| " << setw(12) << right << s[i].Inf << " "
			<< "| " << setw(10) << right << s[i].Mark << " " << "|" << endl;
	}
	cout << "======================================================================================"
		<< endl;
	cout << endl;
}

void Sort(Student* s, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) 
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((s[i1].Mark > s[i1 + 1].Mark)
				||
				(s[i1].Mark == s[i1 + 1].Mark &&
					s[i1].spec > s[i1 + 1].spec)
				||
				(s[i1].Mark == s[i1 + 1].Mark &&
					s[i1].spec == s[i1 + 1].spec &&
					s[i1].prizv < s[i1 + 1].prizv))
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
}

int BinSearch(Student* s, const int N, const string prizv, const  Spec spec, const double Mark)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].prizv == prizv && s[m].spec == spec && s[m].Mark == Mark)
			return m;
		if ((s[m].Mark < Mark)
			||
			(s[m].Mark == Mark &&
				(s[m].spec < spec))
			||
			(s[m].Mark == Mark &&
				s[m].spec == spec &&
				s[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

int* IndexSort(Student* s, const int N)
{
	int* I = new int[N]; 
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value; 
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((s[I[j]].Mark > s[value].Mark) ||
				(s[I[j]].Mark == s[value].Mark &&
					s[I[j]].spec > s[value].spec) ||
				(s[I[j]].Mark == s[value].Mark &&
					s[I[j]].spec == s[value].spec &&
					s[I[j]].prizv < s[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{ 
	cout << "======================================================================================"
		<< endl;
	cout << "| � | ������� | ���� |������������| Գ���� |���������� |  ����������� |������� ���|"
		<< endl;
	cout << "--------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[I[i]].prizv
			<< "| " << setw(4) << right << s[I[i]].kurs << " "
			<< "| " << setw(11) << right << SpecStr[s[i].spec] << " "
			<< "| " << setw(6) << right << s[i].Fiz << " "
			<< "| " << setw(9) << right << s[i].Mat << " "
			<< "| " << setw(9) << right << s[i].Inf << " "
			<< "| " << setw(10) << right << s[i].Mark<< " " << "|" << endl;
	}
	cout << "======================================================================================"
		<< endl;
	cout << endl;
}
