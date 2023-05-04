// ЮФУ ИКТИБ МОП ЭВМ
// Программирование и Основы Теории Алгоритмов 2
// Индивидульное задания №2
// КТбо1-7 Черноусов Даниил Владимирович 
// 30.10.2022

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int condition = 1;

typedef struct Tape
    {
    vector<char> tape;
    int head;
    } Tape;

typedef struct Machine
    {
    map<char, int> change;
    map<char, char> shift;
    map<char, char> record;
    } Machine;

void init(Machine* ptr1)
    {
    ifstream fin("input.txt");
    int cnt;
    fin >> cnt;
    for (int i = 0; i < cnt; i++)
        {
        for (int j = 0; j <= 6; j++)
            {
            char input, side, put; int next_condition;
            fin >> input >> side >> put >> next_condition;
            ptr1[i].shift[input] = side;
            ptr1[i].record[input] = put;
            ptr1[i].change[input] = next_condition;
            }
        }
    }

void transition(Tape* ptr, Machine* ptr1)
    {
    char c = ptr->tape[ptr->head];
    Machine& currentRecord = ptr1[condition];

    condition = currentRecord.change[c]; 

    if (currentRecord.record[c] != 'O')
        {
        ptr->tape[ptr->head] = currentRecord.record[c];
        }
    if (currentRecord.shift[c] == 'R')
        {
        ptr->head++;
        }
    else
        {
        ptr->head--;
        }

    if (ptr->head == ptr->tape.size())
        {
        ptr->tape.push_back('_');
        }
    else if (ptr->head == -1)
        {
        ptr->tape.insert(ptr->tape.begin(), '_');
        ptr->head++;
        }
    }

bool isValidInput(const string& input)
    {
    for (char c : input)
        {
        if (!strchr("01#=IO", c))
            {
            return false;
            }
        }
    return true;
    }

int main()
    {
    setlocale(LC_ALL, "Russian");
    Machine* ptrMachine = new Machine[16];
    Tape* ptrTape = new Tape;
    ptrTape->head = 1;
    init(ptrMachine);
    char choice;
    bool valid = false;
    do
        {
        cout << "Введите входную строку: " << endl;
        ptrTape->tape.clear();
        ptrTape->tape.push_back('_');
        string input;
        cin >> input;
        valid = isValidInput(input);

        if (valid)
            {
            cout << "Текущее состояние: " << condition << endl;

            for (int i = 0; i < input.size(); i++) 
                ptrTape->tape.push_back(input[i]);
            ptrTape->tape.push_back('_');

            for (int i = 0; i < ptrTape->tape.size(); i++)
                cout << ptrTape->tape[i];
            cout << endl;

            for (int i = 0; i < ptrTape->head; i++)
                cout << ' ';
            cout << "^" << endl;

            int dist;
            while (condition != 0)
                {
                transition(ptrTape, ptrMachine);

                cout << "Текущее состояние: " << condition << endl;
                dist = 0;

                for (int i = 0; i < ptrTape->tape.size() - 1; i++)
                    {
                    if (ptrTape->tape[i] != '_' || ptrTape->tape[i + 1] != '_')
                        cout << ptrTape->tape[i];
                    else
                        dist++;
                    }
                if (ptrTape->tape.back() != '_')
                    {
                    cout << ptrTape->tape.back();
                    }
                cout << '_';
                cout << endl;
                for (int i = dist; i < ptrTape->head; i++)
                    {
                    cout << " ";
                    }
                cout << "^" << endl;
                }
            cout << "Обработка входной строки завершена. " << endl;
            }
        else
            {
            cout << "Неверный ввод. Проверьте строку на корректность ввода. (Допустимые символы: 0, 1, #)" << endl;
            }
        cout << "Хотите ввести новую строку? (y/n)" << endl;
        cin >> choice;
        condition = 1;
        ptrTape->head = 1;
        } while (choice == 'y' || choice == 'Y');

        delete[] ptrMachine;
        delete ptrTape;
        return 0;
    }