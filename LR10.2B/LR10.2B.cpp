//Реалізувати фізичне та індексне сортування і бінарний пошук студентів за спеціальністю, курсом та прізвищем,
// використовуючи структури з об’єднанням union для третьої оцінки.
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Specialties in alphabetical order by their English names.
enum Specialty { CS, INF, ME, PI, TE };

struct Student
{
    string surname;
    int course;
    Specialty spec;
    int physics, math;
    union
    {
        int programming;
        int numerical;
        int pedagogy;
    };
};

string SpecName(Specialty spec)
{
    switch (spec)
    {
    case CS: return "Computer Science";
    case INF: return "Informatics";
    case ME: return "Math and Economics";
    case PI: return "Physics and Informatics";
    case TE: return "Technology Education";
    }
    return "Unknown";
}

int ReadInt(const string& prompt, int low, int high)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= low && x <= high)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid value. Try again.\n";
    }
}

Specialty ReadSpec()
{
    cout << "0-CS, 1-INF, 2-ME, 3-PI, 4-TE\n";
    return (Specialty)ReadInt("Specialty: ", 0, 4);
}

void Create(Student* s, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Student " << i + 1 << ":\n";
        cout << "Surname: ";
        getline(cin >> ws, s[i].surname);
        s[i].course = ReadInt("Course: ", 1, 6);
        s[i].spec = ReadSpec();
        s[i].physics = ReadInt("Physics: ", 2, 5);
        s[i].math = ReadInt("Mathematics: ", 2, 5);
        switch (s[i].spec)
        {
        case CS:
            s[i].programming = ReadInt("Programming: ", 2, 5);
            break;
        case INF:
            s[i].numerical = ReadInt("Numerical methods: ", 2, 5);
            break;
        default:
            s[i].pedagogy = ReadInt("Pedagogy: ", 2, 5);
        }
    }
}

void Print(const Student* s, int n, const int* index = nullptr)
{
    cout << "\nStudents\n";
    cout << left << setw(4) << "No" << setw(16) << "Surname"
        << setw(8) << "Course" << setw(25) << "Specialty"
        << setw(6) << "Phys" << setw(6) << "Math"
        << setw(6) << "Prog" << setw(6) << "Num" << "Ped\n";
    for (int i = 0; i < n; i++)
    {
        int j = index == nullptr ? i : index[i];
        cout << left << setw(4) << i + 1
            << setw(16) << s[j].surname << setw(8) << s[j].course
            << setw(25) << SpecName(s[j].spec)
            << setw(6) << s[j].physics << setw(6) << s[j].math;
        if (s[j].spec == CS)
            cout << setw(6) << s[j].programming << setw(6) << "";
        else if (s[j].spec == INF)
            cout << setw(6) << "" << setw(6) << s[j].numerical;
        else
            cout << setw(12) << "" << s[j].pedagogy;
        cout << '\n';
    }
}

// Compare by specialty, course, then surname.
int Compare(const Student& a, const Student& b)
{
    if (a.spec < b.spec) return -1;
    if (a.spec > b.spec) return 1;
    if (a.course < b.course) return -1;
    if (a.course > b.course) return 1;
    if (a.surname < b.surname) return -1;
    if (a.surname > b.surname) return 1;
    return 0;
}

void Sort(Student* s, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (Compare(s[j], s[j + 1]) > 0)
            {
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
}

void IndexSort(const Student* s, int* index, int n)
{
    for (int i = 0; i < n; i++) index[i] = i;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (Compare(s[index[j]], s[index[j + 1]]) > 0)
            {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
}

int BinSearch(const Student* s, const int* index,
    int n, const Student& key)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int j = index[mid];
        int c = Compare(s[j], key);
        if (c == 0) return j;
        if (c < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

Student ReadKey()
{
    Student key{};
    cout << "Surname: ";
    getline(cin >> ws, key.surname);
    key.spec = ReadSpec();
    key.course = ReadInt("Course: ", 1, 6);
    return key;
}

void Menu()
{
    cout << "\n1 - Print\n2 - Physical sort\n"
        << "3 - Index sort\n4 - Binary search\n"
        << "5 - Enter new data\n0 - Exit\n";
}

#ifndef UNIT_TEST
int main()
{
    int n = ReadInt("Number of students: ", 1, 1000);
    Student* s = new Student[n];
    int* index = new int[n];
    Create(s, n);
    int choice;
    do
    {
        Menu();
        choice = ReadInt("Choice: ", 0, 5);
        switch (choice)
        {
        case 1: Print(s, n); break;
        case 2: Sort(s, n); Print(s, n); break;
        case 3: IndexSort(s, index, n); Print(s, n, index); break;
        case 4:
        {
            Student key = ReadKey();
            IndexSort(s, index, n);
            int pos = BinSearch(s, index, n, key);
            if (pos >= 0) cout << "Student found: "
                << s[pos].surname << '\n';
            else cout << "Student not found.\n";
            break;
        }
        case 5: Create(s, n); break;
        }
    } while (choice != 0);
    delete[] index;
    delete[] s;
    return 0;
}
#endif
