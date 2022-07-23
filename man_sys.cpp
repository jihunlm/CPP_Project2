#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 

using namespace std;

class student {
	int studentno;
	char name[50];
	int eng_mark, math_mark, physics_mark, chemistry_mark;
	double average;
	char grade;

	public:
	void getdata();
	void showdata();
	void calculate();
	int retrollno();
};

void student::calculate() 
{
	average = (eng_mark + math_mark + physics_mark + chemistry_mark) / 4;
	if(average >= 90) {
		grade = 'A';
	}
	else if (average >= 80){ 	
		grade = 'B';
	}
	else if (average >= 70) { 
		grade = 'C';
	}
	else if (average >= 60) { 
		grade = 'D';
	}
	else {
		grade = 'F';
	}
}

void student::showdata() 
{
	cout << "The student number you requested : " << studentno << endl;
	cout << "The name : " << name << endl;
	cout << "Average score of the student : " << average << endl;
	cout << "The final grade for the student is : " << grade << endl;
}

void student::getdata() 
{
	cout << "\nInput the student number : ";
	cin >> studentno;
	cout << "\nInput the name of the student : ";
	cin >> name;
	cout << "\nInput the English score of the student : ";
	cin >> eng_mark;
	cout << "\nInput the Math score of the student : ";
	cin >> math_mark;
	cout << "\nInput the Physics score of the student : ";
	cin >> physics_mark;
	cout << "\nnnput the Chemistry score of the student : ";
	cin >> chemistry_mark;
	calculate();
}

int student::retrollno()
{
	return studentno;
}

void create_student();
void display_sp(int);
void display_all();
void delete_student(int);
void change_student(int);

///////////////////////////////////////////////       MAIN        //////////////////////////////////////////////////////////////////

int main() 
{
	char ch;
	cout << setprecision(2);
	do
	{
		char ch;
		int num;
		cout <<"\n\n\n\tMENU";
		cout <<"\n\n\n\t1. Create student record";
		cout <<"\n\n\n\t2. Search student record";
		cout <<"\n\n\n\t3. Display all students records ";
		cout <<"\n\n\n\t4. Delete student record";
		cout <<"\n\n\n\t5. Modify student record";
		cout <<"\n\n\t6. Exit";
		cout <<"What is your Choice (1/2/3/4/5/6) ";
		cin >> ch;
		system("cls");
		switch(ch)
		{
		case '1' : create_student(); break;
		case '2' : cout << "\n\n\tEnter The roll number ";
		cin >> num;
		display_sp(num); break;	   
		case '3' : display_all(); break;
		case '4' : cout << "\n\n\tEnter the roll number ";
		cin >> num;
		delete_student(num); break;
		case '5' : cout << "\n\n\tEnter The roll number "; cin >> num;
		change_student(num); break;
		case '6' : cout << "Exiting, Thank you!"; exit(0);
		}
	} while (ch!='6');
		return 0;	
}

void create_student()
{
	student stud;
	ofstream oFile;
	oFile.open("student.dat", ios::binary|ios::app);
	stud.getdata();
	oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
	oFile.close();
		cout << "\n\nStudent record has been created ";
	cin.ignore();
	cin.get();
}

void display_all()
{
	student stud;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened!! Press any Key ot exti";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\t DISPLAYING ALL RECORDS\n\n";
	while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
	{
		stud.showdata();
		cout <<"\n\n=============================================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

void display_sp(int n)
{
	student stud;
	ifstream iFile;
	iFile.open("student.dat", ios::binary);
	if(!iFile)
	{
		cout << "File could not be opened... Press any Key to exit";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
	{
		if(stud. retrollno() == n)
		{
			stud.showdata();
			flag = true;
		}
	}
	iFile.close();
	if(flag == false)
	cout << "\n\nrecord does not exist";
	cin.ignore();
	cin.get();
}

void change_student(int n)
{
	bool found = false;
	student stud;
	fstream f1;
	f1.open("student.dat", ios::binary|ios::in|ios::out);
	if(!f1)
	{
		cout << "File could not be opened. Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	while(!f1.eof() && found==false)
	{
		f1.read(reinterpret_cast<char *> (&stud), sizeof(student));
		if(stud.retrollno()==n)
		{
			stud.showdata();
			cout<<"\n\tEnter new student dtails:"<<endl;
			stud.getdata();
			int pos=(-1)*static_cast<int>(sizeof(stud));
			f1.seekp(pos,ios::cur);
			f1.write(reinterpret_cast<char *> (&stud), sizeof(student));
			cout << "\n\n\t Record Updated";
			found=true;
		}
	}
	f1.close();
	if(found=false)
	cout << "\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}

void delete_student(int n)
{
	student stud;
	ifstream iFile;
	iFile.open("student.dat", ios::binary);
	if(!iFile)
	{
		cout<<"File could not be opened... Press any Key to exit...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream oFile;
	oFile.open("Temp.dat", ios::out);
	iFile.seekg(0,ios::beg);
	while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
	{
		if(stud.retrollno() != n)
		{
			oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
		}
	}
	oFile.close();
	iFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\t Record Deleted ..";
	cin.ignore();
	cin.get();
}
