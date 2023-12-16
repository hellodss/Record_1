#include <iostream>
#include <stdlib.h>
#include <QWidget>

class Integer
{
public:
    int numberSon;
    int numberMom;
};

class fenshu: public Integer
{

    int numberSon;
    int numberMom;
public:

    fenshu(int x = 0, int y= 1)
    {
        numberSon = x;
        numberMom = y;
    }

    ~fenshu()
    {
        std::cout << "析构函数运行" << std::endl;
    }


    //在类中重构加法，及定义了分数类的加法运算，也可以直接写函数但是直接重构运算符更加的简洁
    fenshu operator+(const fenshu& other) const //const 表示函数对类中的属性只有 只读权限
    {
        fenshu temp;
        if (numberMom == other.numberMom)
        {
            temp.numberSon = numberSon + other.numberSon;
            temp.numberMom = numberMom;
            return temp;
        }
        else
        {
            temp.numberSon = numberSon * other.numberMom + other.numberSon * numberMom;
            temp.numberMom = numberMom * other.numberMom;
            return temp;
        }
    }

    fenshu operator-(const fenshu& other) const
    {
        fenshu temp;
        if (numberMom == other.numberMom)
        {
            temp.numberSon = numberSon - other.numberSon;
            temp.numberMom = numberMom;
            return temp;
        }
        else
        {
            temp.numberSon = numberSon * other.numberMom - other.numberSon * numberMom;
            temp.numberMom = numberMom * other.numberMom;
            return temp;
        }

    }

    fenshu operator*(const fenshu& other) const
    {
        fenshu temp;
        temp.numberSon = numberSon * other.numberSon;
        temp.numberMom = numberMom;
        return temp;
    }

    fenshu operator/(const fenshu& other) const
    {
        fenshu temp;
        temp.numberSon = numberSon * other.numberMom;
        temp.numberMom = numberMom * other.numberSon;
        return temp;
    }


    void Simplify()
    {
        int largest, gcd = 1;  // 最大公约数

        largest = (numberSon > numberMom) ? numberSon : numberMom;

        for (int loop = 2; loop <= largest; loop++)
            if (numberSon % loop == 0 && numberMom % loop == 0)
                gcd = loop;

        numberSon /= gcd;
        numberMom /= gcd;
    }

    fenshu tofenshu(const QString Str) const
    {
        fenshu temp;
        QStringList t = Str.split("/");
        temp.numberSon = t[0].toInt();
        temp.numberMom = t[1].toInt();
        return temp;
    }

    QString toString() const
        {
            return QString("%1/%2").arg(numberSon).arg(numberMom);
        }


    friend std::ostream& operator<<(std::ostream& output,
        const fenshu& other)
    {
        if (other.numberSon == other.numberMom)
        {
            output << 1;
        }
        else{ output << other.numberSon << "/" << other.numberMom; }

        return	output;
    }

    friend std::istream& operator>>(std::istream& input, fenshu& other)
    {
        input >> other.numberSon;
        getchar();
        input >>other.numberMom;
        return input;
    }
};
