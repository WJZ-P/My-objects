//分数计算器的设计与实现
#include <iostream>
#include <string.h>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

//下面是类的实现
class Fraction
{
    friend Fraction operator+(const Fraction &frac1, const Fraction &frac2); //重载+运算符
    friend Fraction operator-(const Fraction &frac1, const Fraction &frac2); //重载-运算符
    friend Fraction operator*(const Fraction &frac1, const Fraction &frac2); //重载*运算符
    friend Fraction operator/(const Fraction &frac1, const Fraction &frac2); //重载/运算符
    friend bool operator==(Fraction frac1, Fraction frac2);                  //重载==运算符
    friend bool operator>(const Fraction &frac1, const Fraction &frac2);     //重载>运算符
    friend bool operator<(const Fraction &frac1, const Fraction &frac2);     //重载<运算符
    friend ostream &operator<<(ostream &out, const Fraction &frac);          //重载<<运算符
    friend istream &operator>>(istream &in, Fraction &frac);                 //重载>>运算符
    friend void sortFraction();                                              //对分数数组排序

    //下面是为了简化代码新定义的通分函数，返回通分所需乘以的因数factor
    friend int reduction(Fraction frac1, Fraction frac2); //对两个分数进行通分

public:
    Fraction();                     //无参造函数
    Fraction(int n, int d);         //带参造函数
    Fraction(const Fraction &f);    //复制造函数
    void setFraction(int n, int d); //设置分数的分子和分母
    int getNumer();                 //获取分数的分子
    int getDeno();                  //获取分数的分母
    void RdcFrc();                  //当前分数约分

    //以下为新增内容
    string Operator; //保存当前分数前的计算符
    Fraction(int n, int d, string Operator);
    //带运算符的构造函数

private:
    int numer; //分子
    int deno;  //分母
};

//下面是用到的算法函数
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

int reduction(Fraction frac1, Fraction frac2) //实现通分函数,返回的是最小公倍数
{
    //下面求最小公倍数
    int max = Max(frac1.deno, frac2.deno);
    int min = Min(frac1.deno, frac2.deno);
    int j = 2;

    if (frac1.deno == frac2.deno)
        return frac1.deno;

    for (int i = 1; 1; i++) //对大的分母进行乘法
    {
        while (j * min <= max * i) //对小的分母进行乘法
        {
            if (j * min == max * i)
            {
                return j * min;
            }

            j++;
        }
    }
}

//以下是各函数实现
Fraction::Fraction() //实现默认构造函数
{
    this->numer = 0;
    this->deno = 1;
}

Fraction::Fraction(int n, int d) //实现构造函数
{
    this->numer = n;
    this->deno = d;
}

Fraction::Fraction(const Fraction &f) //实现复制造函数
{
    this->deno = f.deno;
    this->numer = f.numer;
    this->Operator = f.Operator;
}

Fraction::Fraction(int n, int d, string Operator) //实现带运算符的构造函数
{
    this->deno = d;
    this->numer = n;
    this->Operator = Operator;
}

void Fraction::setFraction(int n, int d) //设置分数的分子和分母
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

void Fraction::RdcFrc() //当前分数约分
{
    if (this->numer == this->deno) //分子分母相等，输出1
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

Fraction operator+(const Fraction &frac1, const Fraction &frac2) //重载+运算符
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

Fraction operator-(const Fraction &frac1, const Fraction &frac2) //重载-运算符
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

Fraction operator*(const Fraction &frac1, const Fraction &frac2) //重载*运算符
{
    Fraction A(1, 1);
    A.deno = frac1.deno * frac2.deno;
    A.numer = frac1.numer * frac2.numer;
    return A;
}

Fraction operator/(const Fraction &frac1, const Fraction &frac2) //重载/运算符
{
    Fraction A(1, 1);
    A.deno = frac1.deno * frac2.numer;
    A.numer = frac1.numer * frac2.deno;
    return A;
}

bool operator==(Fraction frac1, Fraction frac2) //重载==运算符
{
    int min_d = Min(frac1.deno, frac2.deno);
    int max_d = Max(frac1.deno, frac2.deno);
    int min_n = Max(frac1.numer, frac2.numer);
    int max_n = Min(frac1.numer, frac2.numer); //定义分子和分母的最大、最小值

    for (int i = 1; min_d * i <= max_d; i++)
    {
        if (min_d * i == max_d && min_n * i == max_n)
            return true;
    }
    return false;
}

bool operator>(const Fraction &frac1, const Fraction &frac2) //重载>运算符
{
    int lcm = reduction(frac1, frac2); // least common multiple   最小公倍数
    return frac1.numer * (lcm / frac1.deno) > frac2.numer * (lcm / frac2.deno);
}

bool operator<(const Fraction &frac1, const Fraction &frac2) //重载<运算符
{
    //此处不知道为何，例如a<b，实际上传入的第一个参数是b,第二个参数是a，二者颠倒了？！
    //经查询，这就是语法规定...

    double fra1 = (double)frac1.numer / frac1.deno;
    double fra2 = (double)frac2.numer / frac2.deno;
    return fra1 < fra2;
}

ostream &operator<<(ostream &out, const Fraction &frac) //重载<<运算符
{
    out << frac.numer << '/' << frac.deno;
    return out;
}

istream &operator>>(istream &in, Fraction &frac) //重载>>运算符
{
    char s[100];
    in >> s;
    frac.numer = atoi(strtok(s, "/"));
    frac.deno = atoi(strtok(NULL, "/"));
    return in;
}

void sortFraction(vector<Fraction> &fraction, bool judge) //对分数数组排序
//必须传地址，否则要修改的无法返回！
{
    if (judge) //当a为true时，从小到大排列
    {

        sort(fraction.begin(), fraction.end(), [](Fraction &frac1, Fraction &frac2)
             { return frac1 < frac2; });
    }

    else //当a为false时，从大到小排列
    {
        sort(fraction.begin(), fraction.end(), [](Fraction &frac1, Fraction &frac2)
             { return frac1 > frac2; });
    }
}

int main()
{
    cout<<"Created by WJZ \n";
    string choice;
    regex pattern("^([+\\-*/]?((((?!0)-?\\d+)|0)\\/((?!0)-?\\d+)))+$"); //用于检测的正则
    regex pattern1("([+\\-*/])?((((?!0)-?\\d+)|0)/((?!0)-?\\d+))");     //用于算数的正则
    regex r1("^([+\\-]?[0-9]+/((?!0)[0-9]+|0),?[<=+*/>]?)+$");          //用于排序的正则
    regex r2("^(((?!0)[0-9]+)|0)\\/((?!0)[0-9]+)$");                    //用于通分和约分的正则
    //利用较为复杂的正则表达式判断用户输入是否符合格式
    while (1)
    {
        int judge = 0; //用于检测是否输入错误

        printf("请选择功能（键入1、2、3）:\n1.分数计算\n2.分数排序\n3.分数约分\n——");
        cin >> choice; //初始界面

        if (choice == "1") //分式计算
            while (1)
            {
                judge = 1; //当judge大于5时就是输入错误，返回上一层目录
                printf("请输入分数计算式（如1/2+1/3回车），输入#号键返回上一层目录");
                printf("（除法计算请用“/”）:\n——");

                string calculation; //计算式
                cin >> calculation; //输入计算式

                if (calculation[0] == '#')
                    break; //输入＃返回上层目录

                if (!regex_match(calculation, pattern))
                {
                    cout << "分数算式输入错误！" << endl;
                    continue;
                }

                //下面利用regex内的search进行算式的提取
                vector<Fraction> fraction;
                smatch result;
                while (regex_search(calculation, result, pattern1))
                {
                    fraction.push_back(Fraction(stoi(result[3]), stoi(result[5]), result[1]));
                    //添加到数组以方便运算
                    //从第二个开始依次是符号、分子、分母
                    calculation = result.suffix(); //让calculation变成剩余的字符继续切割
                }

                //下面进行乘除法的优先运算。
                vector<Fraction>::iterator it = fraction.begin(); //定义迭代器
                for (int i = 0; i < fraction.size(); i++)
                {
                    if (fraction[i].Operator == "*")
                    {
                        fraction[i] = fraction[i] * fraction[i - 1];     //进行乘法运算，第二个因子变为结果
                        fraction[i].Operator = fraction[i - 1].Operator; //变更运算符
                        fraction.erase(it + i - 1);                      //去除乘法的第一个因子
                        i--;
                    }

                    else if (fraction[i].Operator == "/")
                    {
                        fraction[i] = fraction[i - 1] / fraction[i];     //进行乘法运算，第二个因子变为结果
                        fraction[i].Operator = fraction[i - 1].Operator; //变更运算符
                        fraction.erase(it + i - 1);                      //去除乘法的第一个因子
                        i--;
                    }
                }

                //下面方法在乘除法计算完毕后再执行！
                for (int i = 0; i < fraction.size(); i++) //将运算符为减法的分子取成负数，以便最后的加减
                {
                    if (fraction[i].Operator == "-")
                    //因分式类中的分子与分母均为私有成员，无法直接访问，只能采取其他方式取负数
                    {
                        Fraction A(0, 1);
                        fraction[i] = A - fraction[i];
                    }
                }

                //最后的求和工作！
                Fraction Result(0, 1);
                for (Fraction i : fraction)
                    Result = Result + i;
                    Result.RdcFrc();

                cout << "=" << Result << endl;
            }

        if (choice == "2") //进行分式的排序工作
            while (1)
            {
                judge = 1; //当judge为0不变时就是输入错误，返回上一层目录
                printf("请输入一组分数，用逗号隔开，如需由小到大排序用符号<结尾，\n");
                printf("由大到小排序用符号>结尾（如1/2,1/4,3/5<回车）,输入#号键返回上一层目录");
                printf(":\n——");

                char equation[200];
                cin >> equation; //输入排序式

                if (equation[0] == '#')
                    break; //输入＃返回上层目录

                if (!regex_match((string)equation, r1)) //检验分数式是否符合规则
                {
                    cout << "分数算式输入错误！" << endl;
                    break;
                }

                //下面进行运算
                vector<Fraction> fraction; //用于保存分式
                string fra[50];            //存储切分的字符串
                char *token;
                token = strtok(equation, ","); //获取第一个分式
                fra[0] = token;

                for (int i = 1; token != NULL; i++)
                {
                    token = strtok(NULL, ",");
                    if (token != NULL)
                        fra[i] = token;
                }
                //完成对分式的切分，各分式存储在string数组fra内

                //下面对数据进行排序
                int j = -1;
                for (int i = 0; fra[i].size() > 0; i++, j++)
                    ; //确认最后一个分式的下标为j

                bool judge1;

                if (fra[j][fra[j].size() - 1] == '<')
                    judge1 = true;

                else if (fra[j][fra[j].size() - 1] == '>')
                    judge1 = false;

                else
                    cout << "分数算式排列类型输入错误！请在最后输入<号或>号！\n";

                //下面对最后一个fra进行处理，去掉大于号与小于号
                string copy1;
                int i1 = 0;
                for (; i1 < fra[j].size() - 1; i1++)
                    copy1 += fra[j][i1]; //复制一个copy1，内容删去了末尾的大于或小于号

                fra[j] = copy1; //删去数组最后的大于号和小于号

                for (int i = 0; i < j + 1; i++)
                {
                    //此处需要注意，最后一个fra元素的末尾符号为<或者>
                    char *equ = (char *)fra[i].c_str();

                    token = strtok(equ, "/"); //提取分子
                    int numer0 = atoi(token); //储存分子

                    token = strtok(NULL, "/"); //提取分母
                    int deno0 = atoi(token);   //储存分母

                    fraction.push_back(Fraction(numer0, deno0)); //添加到数组以方便运算
                }

                sortFraction(fraction, judge1); //按照judge1的布尔值确定从大到小或者从小到大进行输出

                cout << "排序结果为:" << endl;
                for (int i = 0; i < fraction.size(); i++)
                    cout << fraction[i] << ' '; //排列完成后进行输出
                cout << endl;
            }

        if (choice == "3") //分数约分
            while (1)
            {
                judge = 1;
                printf("请输入想要进行约分的分式：(输入#返回上层目录)\n——");

                char equation[20];
                cin >> equation; //输入排序式

                if (equation[0] == '#')
                    break; //输入＃返回上层目录

                if (!regex_match((string)equation, r1)) //检验分数式是否符合规则
                {
                    cout << "分数算式输入错误！" << endl;
                    break;
                }
                //下面依旧是将输入的分式转成类的形式

                char *token;
                token = strtok(equation, "/"); //提取分子
                char *token1;
                token1 = strtok(NULL, "/"); //提取分母

                Fraction A(atoi(token), atoi(token1));
                Fraction A1(A); //复制一个A，检测能否约分

                A.RdcFrc(); //调用约分函数

                if (A1 == A)
                    cout << "该分数无法约分！" << endl;
                else
                    cout << "约分结果为：" << endl
                         << A << endl;
            }

        if (judge == 0)
            cout << "输入错误！" << endl;
    } //大功告成,谢谢老师！（￣▽￣）
} // cqu 2022xxxx
