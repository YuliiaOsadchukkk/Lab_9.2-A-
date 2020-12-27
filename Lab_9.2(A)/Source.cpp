#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Spec{ КН, ІТ, ПЗ, СА };
string SpecStr[] = { "КН", "ІТ", "ПЗ", "СА" };

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
	cout << "Введіть кількість студентів N: "; cin >> N;
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
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук учня за посадою та прізвищем" << endl;
		cout << " [5] - індексне впорядкування та вивід даних" << endl;
		cout << " [6] - обчислення середнього балу та запис у структуру" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;

		cout << "Введіть значення: "; cin >> menuItem;
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
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - СА): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get(); 
			cin.sync();
			cout << " Прізвище: "; getline(cin, prizv);
			cout << "Введіть середній бал"; cin >> Mark;
			cout << endl; 
			if ((found = BinSearch(s, N, prizv,spec,Mark)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
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
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}


void Create(Student* s, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, s[i].prizv);
		cout << " курс: "; cin >> s[i].kurs;
		cout << " спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - СА): "; cin >> spec;
		s[i].spec = (Spec)spec;
		cout << "Оцінка з фізики :"; cin >> s[i].Fiz;
		cout << "Оцінка з математики :"; cin >> s[i].Mat;
		cout << "Оцінка з інформатики :"; cin >> s[i].Inf;
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
	cout << "| № | Прізвище | Курс |Спеціальність| Фізика | Математика|  Інформатика |Середній бал|"
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
	cout << "| № | Прізвище | Курс |Спеціальність| Фізика |Математика |  Інформатика |Середній бал|"
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
