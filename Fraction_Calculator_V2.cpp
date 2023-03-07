//�����������������ʵ��
#include <iostream>
#include <string.h>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

//���������ʵ��
class Fraction
{
    friend Fraction operator+(const Fraction &frac1, const Fraction &frac2); //����+�����
    friend Fraction operator-(const Fraction &frac1, const Fraction &frac2); //����-�����
    friend Fraction operator*(const Fraction &frac1, const Fraction &frac2); //����*�����
    friend Fraction operator/(const Fraction &frac1, const Fraction &frac2); //����/�����
    friend bool operator==(Fraction frac1, Fraction frac2);                  //����==�����
    friend bool operator>(const Fraction &frac1, const Fraction &frac2);     //����>�����
    friend bool operator<(const Fraction &frac1, const Fraction &frac2);     //����<�����
    friend ostream &operator<<(ostream &out, const Fraction &frac);          //����<<�����
    friend istream &operator>>(istream &in, Fraction &frac);                 //����>>�����
    friend void sortFraction();                                              //�Է�����������

    //������Ϊ�˼򻯴����¶����ͨ�ֺ���������ͨ��������Ե�����factor
    friend int reduction(Fraction frac1, Fraction frac2); //��������������ͨ��

public:
    Fraction();                     //�޲��캯��
    Fraction(int n, int d);         //�����캯��
    Fraction(const Fraction &f);    //�����캯��
    void setFraction(int n, int d); //���÷����ķ��Ӻͷ�ĸ
    int getNumer();                 //��ȡ�����ķ���
    int getDeno();                  //��ȡ�����ķ�ĸ
    void RdcFrc();                  //��ǰ����Լ��

    //����Ϊ��������
    string Operator; //���浱ǰ����ǰ�ļ����
    Fraction(int n, int d, string Operator);
    //��������Ĺ��캯��

private:
    int numer; //����
    int deno;  //��ĸ
};

//�������õ����㷨����
int Max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int Min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int reduction(Fraction frac1, Fraction frac2) //ʵ��ͨ�ֺ���,���ص�����С������
{
    //��������С������
    int max = Max(frac1.deno, frac2.deno);
    int min = Min(frac1.deno, frac2.deno);
    int j = 2;

    if (frac1.deno == frac2.deno)
        return frac1.deno;

    for (int i = 1; 1; i++) //�Դ�ķ�ĸ���г˷�
    {
        while (j * min <= max * i) //��С�ķ�ĸ���г˷�
        {
            if (j * min == max * i)
            {
                return j * min;
            }

            j++;
        }
    }
}

//�����Ǹ�����ʵ��
Fraction::Fraction() //ʵ��Ĭ�Ϲ��캯��
{
    this->numer = 0;
    this->deno = 1;
}

Fraction::Fraction(int n, int d) //ʵ�ֹ��캯��
{
    this->numer = n;
    this->deno = d;
}

Fraction::Fraction(const Fraction &f) //ʵ�ָ����캯��
{
    this->deno = f.deno;
    this->numer = f.numer;
    this->Operator = f.Operator;
}

Fraction::Fraction(int n, int d, string Operator) //ʵ�ִ�������Ĺ��캯��
{
    this->deno = d;
    this->numer = n;
    this->Operator = Operator;
}

void Fraction::setFraction(int n, int d) //���÷����ķ��Ӻͷ�ĸ
{
    this->deno = d;
    this->numer = n;
}

int Fraction::getNumer()
{
    return this->numer;
}

int Fraction::getDeno()
{
    return this->deno;
}

void Fraction::RdcFrc() //��ǰ����Լ��
{
    if (this->numer == this->deno) //���ӷ�ĸ��ȣ����1
    {
        this->numer = 1;
        this->deno = 1;
    }

    for (int i = 2; i <= this->numer; i++)
    {
        while (this->numer % i == 0 && this->deno % i == 0)
        {
            this->numer /= i;
            this->deno /= i;
        }
    }
}

Fraction operator+(const Fraction &frac1, const Fraction &frac2) //����+�����
{
    Fraction A(1, 1);

    if (frac1.deno == frac2.deno)
    {
        A.numer = frac1.numer + frac2.numer;
        A.deno = frac1.deno;
    }

    else
    {
        int lcm = reduction(frac1, frac2); // least common multiple
        A.deno = lcm;
        A.numer = frac1.numer * (lcm / frac1.deno) + frac2.numer * (lcm / frac2.deno);
    }

    return A;
}

Fraction operator-(const Fraction &frac1, const Fraction &frac2) //����-�����
{
    Fraction A(1, 1);
    if (frac1.deno == frac2.deno)
        A.numer = frac1.numer - frac2.numer;
    else
    {
        int lcm = reduction(frac1, frac2); // least common multiple
        A.deno = lcm;
        A.numer = frac1.numer * (lcm / frac1.deno) - frac2.numer * (lcm / frac2.deno);
    }
    return A;
}

Fraction operator*(const Fraction &frac1, const Fraction &frac2) //����*�����
{
    Fraction A(1, 1);
    A.deno = frac1.deno * frac2.deno;
    A.numer = frac1.numer * frac2.numer;
    return A;
}

Fraction operator/(const Fraction &frac1, const Fraction &frac2) //����/�����
{
    Fraction A(1, 1);
    A.deno = frac1.deno * frac2.numer;
    A.numer = frac1.numer * frac2.deno;
    return A;
}

bool operator==(Fraction frac1, Fraction frac2) //����==�����
{
    int min_d = Min(frac1.deno, frac2.deno);
    int max_d = Max(frac1.deno, frac2.deno);
    int min_n = Max(frac1.numer, frac2.numer);
    int max_n = Min(frac1.numer, frac2.numer); //������Ӻͷ�ĸ�������Сֵ

    for (int i = 1; min_d * i <= max_d; i++)
    {
        if (min_d * i == max_d && min_n * i == max_n)
            return true;
    }
    return false;
}

bool operator>(const Fraction &frac1, const Fraction &frac2) //����>�����
{
    int lcm = reduction(frac1, frac2); // least common multiple   ��С������
    return frac1.numer * (lcm / frac1.deno) > frac2.numer * (lcm / frac2.deno);
}

bool operator<(const Fraction &frac1, const Fraction &frac2) //����<�����
{
    //�˴���֪��Ϊ�Σ�����a<b��ʵ���ϴ���ĵ�һ��������b,�ڶ���������a�����ߵߵ��ˣ���
    //����ѯ��������﷨�涨...

    double fra1 = (double)frac1.numer / frac1.deno;
    double fra2 = (double)frac2.numer / frac2.deno;
    return fra1 < fra2;
}

ostream &operator<<(ostream &out, const Fraction &frac) //����<<�����
{
    out << frac.numer << '/' << frac.deno;
    return out;
}

istream &operator>>(istream &in, Fraction &frac) //����>>�����
{
    char s[100];
    in >> s;
    frac.numer = atoi(strtok(s, "/"));
    frac.deno = atoi(strtok(NULL, "/"));
    return in;
}

void sortFraction(vector<Fraction> &fraction, bool judge) //�Է�����������
//���봫��ַ������Ҫ�޸ĵ��޷����أ�
{
    if (judge) //��aΪtrueʱ����С��������
    {

        sort(fraction.begin(), fraction.end(), [](Fraction &frac1, Fraction &frac2)
             { return frac1 < frac2; });
    }

    else //��aΪfalseʱ���Ӵ�С����
    {
        sort(fraction.begin(), fraction.end(), [](Fraction &frac1, Fraction &frac2)
             { return frac1 > frac2; });
    }
}

int main()
{
    cout<<"Created by WJZ \n";
    string choice;
    regex pattern("^([+\\-*/]?((((?!0)-?\\d+)|0)\\/((?!0)-?\\d+)))+$"); //���ڼ�������
    regex pattern1("([+\\-*/])?((((?!0)-?\\d+)|0)/((?!0)-?\\d+))");     //��������������
    regex r1("^([+\\-]?[0-9]+/((?!0)[0-9]+|0),?[<=+*/>]?)+$");          //�������������
    regex r2("^(((?!0)[0-9]+)|0)\\/((?!0)[0-9]+)$");                    //����ͨ�ֺ�Լ�ֵ�����
    //���ý�Ϊ���ӵ�������ʽ�ж��û������Ƿ���ϸ�ʽ
    while (1)
    {
        int judge = 0; //���ڼ���Ƿ��������

        printf("��ѡ���ܣ�����1��2��3��:\n1.��������\n2.��������\n3.����Լ��\n����");
        cin >> choice; //��ʼ����

        if (choice == "1") //��ʽ����
            while (1)
            {
                judge = 1; //��judge����5ʱ����������󣬷�����һ��Ŀ¼
                printf("�������������ʽ����1/2+1/3�س���������#�ż�������һ��Ŀ¼");
                printf("�������������á�/����:\n����");

                string calculation; //����ʽ
                cin >> calculation; //�������ʽ

                if (calculation[0] == '#')
                    break; //���룣�����ϲ�Ŀ¼

                if (!regex_match(calculation, pattern))
                {
                    cout << "������ʽ�������" << endl;
                    continue;
                }

                //��������regex�ڵ�search������ʽ����ȡ
                vector<Fraction> fraction;
                smatch result;
                while (regex_search(calculation, result, pattern1))
                {
                    fraction.push_back(Fraction(stoi(result[3]), stoi(result[5]), result[1]));
                    //��ӵ������Է�������
                    //�ӵڶ�����ʼ�����Ƿ��š����ӡ���ĸ
                    calculation = result.suffix(); //��calculation���ʣ����ַ������и�
                }

                //������г˳������������㡣
                vector<Fraction>::iterator it = fraction.begin(); //���������
                for (int i = 0; i < fraction.size(); i++)
                {
                    if (fraction[i].Operator == "*")
                    {
                        fraction[i] = fraction[i] * fraction[i - 1];     //���г˷����㣬�ڶ������ӱ�Ϊ���
                        fraction[i].Operator = fraction[i - 1].Operator; //��������
                        fraction.erase(it + i - 1);                      //ȥ���˷��ĵ�һ������
                        i--;
                    }

                    else if (fraction[i].Operator == "/")
                    {
                        fraction[i] = fraction[i - 1] / fraction[i];     //���г˷����㣬�ڶ������ӱ�Ϊ���
                        fraction[i].Operator = fraction[i - 1].Operator; //��������
                        fraction.erase(it + i - 1);                      //ȥ���˷��ĵ�һ������
                        i--;
                    }
                }

                //���淽���ڳ˳���������Ϻ���ִ�У�
                for (int i = 0; i < fraction.size(); i++) //�������Ϊ�����ķ���ȡ�ɸ������Ա����ļӼ�
                {
                    if (fraction[i].Operator == "-")
                    //���ʽ���еķ������ĸ��Ϊ˽�г�Ա���޷�ֱ�ӷ��ʣ�ֻ�ܲ�ȡ������ʽȡ����
                    {
                        Fraction A(0, 1);
                        fraction[i] = A - fraction[i];
                    }
                }

                //������͹�����
                Fraction Result(0, 1);
                for (Fraction i : fraction)
                    Result = Result + i;
                    Result.RdcFrc();

                cout << "=" << Result << endl;
            }

        if (choice == "2") //���з�ʽ��������
            while (1)
            {
                judge = 1; //��judgeΪ0����ʱ����������󣬷�����һ��Ŀ¼
                printf("������һ��������ö��Ÿ�����������С���������÷���<��β��\n");
                printf("�ɴ�С�����÷���>��β����1/2,1/4,3/5<�س���,����#�ż�������һ��Ŀ¼");
                printf(":\n����");

                char equation[200];
                cin >> equation; //��������ʽ

                if (equation[0] == '#')
                    break; //���룣�����ϲ�Ŀ¼

                if (!regex_match((string)equation, r1)) //�������ʽ�Ƿ���Ϲ���
                {
                    cout << "������ʽ�������" << endl;
                    break;
                }

                //�����������
                vector<Fraction> fraction; //���ڱ����ʽ
                string fra[50];            //�洢�зֵ��ַ���
                char *token;
                token = strtok(equation, ","); //��ȡ��һ����ʽ
                fra[0] = token;

                for (int i = 1; token != NULL; i++)
                {
                    token = strtok(NULL, ",");
                    if (token != NULL)
                        fra[i] = token;
                }
                //��ɶԷ�ʽ���з֣�����ʽ�洢��string����fra��

                //��������ݽ�������
                int j = -1;
                for (int i = 0; fra[i].size() > 0; i++, j++)
                    ; //ȷ�����һ����ʽ���±�Ϊj

                bool judge1;

                if (fra[j][fra[j].size() - 1] == '<')
                    judge1 = true;

                else if (fra[j][fra[j].size() - 1] == '>')
                    judge1 = false;

                else
                    cout << "������ʽ��������������������������<�Ż�>�ţ�\n";

                //��������һ��fra���д���ȥ�����ں���С�ں�
                string copy1;
                int i1 = 0;
                for (; i1 < fra[j].size() - 1; i1++)
                    copy1 += fra[j][i1]; //����һ��copy1������ɾȥ��ĩβ�Ĵ��ڻ�С�ں�

                fra[j] = copy1; //ɾȥ�������Ĵ��ںź�С�ں�

                for (int i = 0; i < j + 1; i++)
                {
                    //�˴���Ҫע�⣬���һ��fraԪ�ص�ĩβ����Ϊ<����>
                    char *equ = (char *)fra[i].c_str();

                    token = strtok(equ, "/"); //��ȡ����
                    int numer0 = atoi(token); //�������

                    token = strtok(NULL, "/"); //��ȡ��ĸ
                    int deno0 = atoi(token);   //�����ĸ

                    fraction.push_back(Fraction(numer0, deno0)); //��ӵ������Է�������
                }

                sortFraction(fraction, judge1); //����judge1�Ĳ���ֵȷ���Ӵ�С���ߴ�С����������

                cout << "������Ϊ:" << endl;
                for (int i = 0; i < fraction.size(); i++)
                    cout << fraction[i] << ' '; //������ɺ�������
                cout << endl;
            }

        if (choice == "3") //����Լ��
            while (1)
            {
                judge = 1;
                printf("��������Ҫ����Լ�ֵķ�ʽ��(����#�����ϲ�Ŀ¼)\n����");

                char equation[20];
                cin >> equation; //��������ʽ

                if (equation[0] == '#')
                    break; //���룣�����ϲ�Ŀ¼

                if (!regex_match((string)equation, r1)) //�������ʽ�Ƿ���Ϲ���
                {
                    cout << "������ʽ�������" << endl;
                    break;
                }
                //���������ǽ�����ķ�ʽת�������ʽ

                char *token;
                token = strtok(equation, "/"); //��ȡ����
                char *token1;
                token1 = strtok(NULL, "/"); //��ȡ��ĸ

                Fraction A(atoi(token), atoi(token1));
                Fraction A1(A); //����һ��A������ܷ�Լ��

                A.RdcFrc(); //����Լ�ֺ���

                if (A1 == A)
                    cout << "�÷����޷�Լ�֣�" << endl;
                else
                    cout << "Լ�ֽ��Ϊ��" << endl
                         << A << endl;
            }

        if (judge == 0)
            cout << "�������" << endl;
    } //�󹦸��,лл��ʦ������������
} // cqu 20221006