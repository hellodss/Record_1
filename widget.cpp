#include "widget.h" //包含我们自己写的类
#include "ui_widget.h" //
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include<sstream>
#include <cmath>
#include <QDateTime>

QString a = nullptr;
QString b = nullptr;
QString texT;
int selectedValue = 1;
bool ADD = false;
bool Sub = false;
bool Mul = false;
bool Div = false;

class Integer
{
public:
    int numberSon;
    int numberMom;
    int numberDate;
};

class Brither: public Integer
{
public:
    Brither(int x=0,int y=0,int z=0)
    {
        numberMom = x;
        numberSon = y;
        numberDate = z;
    }

    QString Cal_age(QString &brith_date)
    {
        QDateTime birthdate = QDateTime::fromString(brith_date, "yyyy-MM-dd");
        QDateTime currentTime = QDateTime::currentDateTime();
        // 计算年龄
        int age = birthdate.daysTo(currentTime) / 365;

        // 计算距离生日天数
        QDateTime nextBirthday = birthdate.addYears(age);
        if (nextBirthday < currentTime) {
            nextBirthday = nextBirthday.addYears(1);
        }
        int daysToBirthday = currentTime.daysTo(nextBirthday);

            // 输出结果

        return "年龄为：" + QString::number(age)+"\n" + "距离生日：" +  QString::number(daysToBirthday)+ "天";
    }


};

class  Space: public Integer
{
public:
    QString Cal_Cricle(QString &radius)
    {
        return QString::number(radius.toDouble() * 3.14);
    }

    QString Cal_Rectangle(QString &Side)
    {
        QStringList s = Side.split("-");
        return QString::number(s[0].toDouble()*s[1].toDouble());
    }

    QString Cal_Triangle(QString &Side)
    {
        QStringList s = Side.split("-");
        if (s.size() == 3) {
                // 将字符串转换为浮点数
                bool conversionOk;
                double sideA = s[0].toDouble(&conversionOk);
                double sideB = s[1].toDouble(&conversionOk);
                double sideC = s[2].toDouble(&conversionOk);

                if (conversionOk) {
                    // 判断是否构成三角形
                    if (sideA + sideB > sideC && sideB + sideC > sideA && sideC + sideA > sideB) {
                        // 计算半周长
                        double s = (sideA + sideB + sideC) / 2;
                        // 使用海伦公式计算面积
                        double area = std::sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
                        // 将面积转换为QString并返回
                        return QString::number(area);
                    } else {
                        // 不能构成三角形的情况
                        return "不能构成三角形";
                    }
                } else {
                    // 转换失败的情况
                    return "输入的边不是有效的数字";
                }
            } else {
                // 输入不包含三个边的情况
                return "输入的边数不正确";
            }
    }
};


class fenshu: public Integer
{
public:
    fenshu(int x = 0, int y= 1)
    {
        numberSon = x;
        numberMom = y;
    }

    ~fenshu()
    {
        qDebug()<< "析构函数运行";
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

    //在类中重构加法，及定义了分数类的加法运算，也可以直接写函数但是直接重构运算符更加的简洁
    fenshu operator+(const fenshu& other) const //const 表示函数对类中的属性只有 只读权限
    {
        fenshu temp;
        if (numberMom == other.numberMom)
        {
            temp.numberSon = numberSon + other.numberSon;
            temp.numberMom = numberMom;
            temp.Simplify();
            return temp;
        }
        else
        {
            temp.numberSon = numberSon * other.numberMom + other.numberSon * numberMom;
            temp.numberMom = numberMom * other.numberMom;
            temp.Simplify();
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
            temp.Simplify();
            return temp;
        }
        else
        {
            temp.numberSon = numberSon * other.numberMom - other.numberSon * numberMom;
            temp.numberMom = numberMom * other.numberMom;
            temp.Simplify();
            return temp;
        }

    }

    fenshu operator*(const fenshu& other) const
    {
        fenshu temp;
        temp.numberSon = numberSon * other.numberSon;
        temp.numberMom = numberMom*other.numberMom;
        temp.Simplify();
        return temp;
    }

    fenshu operator/(const fenshu& other) const
    {
        fenshu temp;
        temp.numberSon = numberSon * other.numberMom;
        temp.numberMom = numberMom * other.numberSon;
        temp.Simplify();
        return temp;
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

class converter
{
public:
    fenshu tofenshu(const QString& Str) const
    {
        fenshu temp;
        QStringList t = Str.split("/");
        temp.numberSon = t[0].toInt();
        temp.numberMom = t[1].toInt();
        std::cout<<"temp:" <<temp<<std::endl;
        return temp;
    }

    QString toString(const fenshu &temp ) const
    {
        QString temp_str;
        temp_str = QString::number(temp.numberSon) + "/" + QString::number(temp.numberMom);
        std::cout<<"temp"<<temp;
        qDebug()<< temp.numberSon<<temp.numberMom;
        return temp_str;
    }


    QString evaluateExpression(const std::string& expression)
    {
        if (selectedValue ==1 )
        {
            std::istringstream ss(expression); //将字符串s转化为stringstream对象ss
             char op; int x, y;
             ss >> x; //读取第一个操作数
             while (ss >> op >> y)
             {
               if(op == '+') x += y;
               else if(op == '-') x -= y;
               else if(op == '*') x *= y;
               else if(op == '/') x /= y;
             }

             return QString::number(x);
        }
    }

};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("分数计算器");
    ui->plainTextEdit->setPlaceholderText("请输入算式");
    texT = ui->plainTextEdit->toPlainText();
    QPushButton *numButtons[11];
    for (int i= 0; i<11; i++)
    {
        QString numName = "num"+QString::number(i);
        numButtons[i] = Widget::findChild<QPushButton *>(numName);
        connect(numButtons[i],SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    }

    connect(ui->jia, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->jian, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->cheng, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->chu, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->left, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->right, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->AC, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->deng, SIGNAL(clicked(bool)), this, SLOT(equalNum()));
    connect(ui->backspace, SIGNAL(clicked(bool)), this, SLOT(fuhao()));
    connect(ui->Normal, &QRadioButton::clicked, [&]() {
        selectedValue = 1;
        QMessageBox::information(this, "提示", "选择了普通计算器");
    });
    connect(ui->Age, &QRadioButton::clicked, [&]() {
        selectedValue = 2;
        QMessageBox::information(this, "提示", "选择了年龄计算器");
        ui->plainTextEdit->setPlaceholderText("请输入出生日期，例如：1990-01-01");
        });
    connect(ui->Faction, &QRadioButton::clicked, [&]() {
        selectedValue = 3;
        QMessageBox::information(this, "提示", "选择了分数计算器");
        ui->plainTextEdit->setPlaceholderText("请输入分数算式");
        });
    connect(ui->Space, &QRadioButton::clicked, [&]() {
        selectedValue = 4;
        QMessageBox::information(this, "提示", "选择了面积计算器");
        ui->plainTextEdit->setPlaceholderText("请输入边长或者半径,例如三角形：3-4-5");
        });



}

void Widget::numOnClick()
{
    QPushButton *numName = (QPushButton*)sender(); //发送按键的名字
    ui->plainTextEdit->textCursor().insertText(numName->text());
    texT = ui->plainTextEdit->toPlainText();//获取文本内容
    if(ADD)
    {
        int i =texT.indexOf("+");
        texT = texT.mid(i+1);
        b = texT;
    }
    else if (Sub)
    {
        int i = texT.indexOf("-");
        texT = texT.mid(i+1);
        b=texT;
    }
    else if (Mul)
    {
        int i = texT.indexOf("*");
        texT = texT.mid(i+1);
        b=texT;
    }
    else if (Div)
    {
        int i = texT.indexOf("/");
        texT = texT.mid(i+1);
        b=texT;
    }
    else {
        a= texT;
        qDebug() << a << b;
    }
}

void Widget::matchFh()
{
    if (texT.contains("+",Qt::CaseInsensitive)) //检测文本是否有+号
    {
        QStringList t = texT.split("+");//按加号将字符串分离
        a = t[0];
        b + t[1];
        ADD = true;
    }
    else if(texT.contains("-",Qt::CaseInsensitive))
    {
        QStringList t = texT.split("-");
        a = t[0];
        b = t[1];
        Sub = true;
    }
    else if(texT.contains("*",Qt::CaseInsensitive))
    {
        QStringList t = texT.split("*");
        a = t[0];
        b = t[1];
        Mul = true;
    }
    else if(texT.contains("/",Qt::CaseInsensitive))
    {
        QStringList t = texT.split("/");
        if (selectedValue==3)
        {
            if (t[1].toInt() ==0 &&t[3].toInt()==0 )
                QMessageBox::information(this, "提示", "分母不能为零");
            a = t[0]+'/'+ t[1];
            b = t[2]+'/'+ t[3];
            Div = true;
        }
        else{
            a = t[0];
            b = t[1];
            Div = true;
        }
    }
//    else if(texT.contains("/",Qt::CaseInsensitive)&&selectedValue == 2)
//    {
//        QStringList t = texT.split(".");
//        a = t[0];
//        b = t[1];
//    }
    else
    {
          a = texT;
    }
}

void Widget::fuhao()
{
    QPushButton *fh = (QPushButton*)sender();
    QString f = fh->text();
    if (f=='+')
    {
        ADD = true;
        ui->plainTextEdit->textCursor().insertText("+");
    }

    if (f == '-')
    {
        Sub = true;
        ui->plainTextEdit->textCursor().insertText("-");
    }
    if (f == '*')
    {
        Mul = true;
        ui->plainTextEdit->textCursor().insertText("*");
    }
    if (f == '/')
    {
        if (selectedValue==1){Div = true;}
        ui->plainTextEdit->textCursor().insertText("/");
    }
    if (f == 10)
    {
        qDebug()<<"point";
        ui->plainTextEdit->textCursor().insertText(".");
    }

    if(f =="backspace")
    {
//        texT = ui->plainTextEdit->toPlainText();
//        texT.chop(1);
//        ADD = Sub = Mul = Div = false;
//        matchFh();//识别输入文本与符号分割
//        ui->plainTextEdit->setPlainText(texT);
//        ui->plainTextEdit->moveCursor(QTextCursor::End);
        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor, 1);
        cursor.removeSelectedText();
        ui->plainTextEdit->moveCursor(QTextCursor::End);
    }

    if (f == "left")
    {
        qDebug()<<"left";
        ui->plainTextEdit->moveCursor(QTextCursor::Left);
        ui->plainTextEdit->setFocus(); //设置聚焦光标确保光标可见
    }
    if (f == "right")
    {
        ui->plainTextEdit->moveCursor(QTextCursor::Right);
        ui->plainTextEdit->setFocus();
    }

    if (f == "AC")
    {

        a=b=nullptr;
        ADD = Sub = Mul=Div = false;
        ui->plainTextEdit->setPlainText("");
    }

}

void Widget::equalNum()
{

    converter Converter;
    Space space;
    Brither brither;
    switch(selectedValue)
    {
    case 1:
        {qDebug() << "等于";
        texT = ui->plainTextEdit->toPlainText();
        ui->plainTextEdit->moveCursor(QTextCursor::End);
        QString result = Converter.evaluateExpression(texT.toStdString());
        ui->plainTextEdit->setPlainText(result);
        break;}
    case 2:
    {
        qDebug() <<"年龄计算";
        texT = ui->plainTextEdit->toPlainText();
        ui->plainTextEdit->setPlainText(brither.Cal_age(texT));
        break;
    }


    case 3:
    {
        qDebug()<<"分数计算";
        fenshu fen1,fen2;
        texT = ui->plainTextEdit->toPlainText();
        qDebug()<<texT.size();
        if (texT.size() ==3 )
        {
            qDebug()<<"化简";
            fen1 = Converter.tofenshu(texT);
            if (fen1.numberMom == 0)
            {
               QMessageBox::information(this, "提示", "分母不能为零");
            }

            ui->plainTextEdit->setPlainText(Converter.toString(fen1+fen2));
            break;
        }

        matchFh();
        qDebug()<<"分数分离后"<<a<<b;
        fen1 = Converter.tofenshu(a);
        fen2 = Converter.tofenshu(b);

        if (b == nullptr)
        {
            ui->plainTextEdit->setPlainText(Converter.toString(fen1));
        }

        if  (ADD)
        {
            ui->plainTextEdit->setPlainText(Converter.toString(fen1+fen2));
            ADD = false;
        }

        if  (Sub)
        {
            ui->plainTextEdit->setPlainText(Converter.toString(fen1-fen2));
            Sub = false;
        }

        if  (Mul)
        {
            qDebug()<<"乘法计算";
            std::cout<<"***"<<fen1*fen2<<std::endl;
            ui->plainTextEdit->setPlainText(Converter.toString(fen1*fen2));
            Mul = false;
        }

        if  (Div)
        {
            qDebug()<<"除法运算";
            ui->plainTextEdit->setPlainText(Converter.toString(fen1/fen2));
            Div = false;
        }

        break;
    }

     case 4:
        qDebug()<<"情况四";
        texT = ui->plainTextEdit->toPlainText();
        qDebug()<<texT.size();
        switch (texT.size())
        {

            case 1:
                qDebug()<<"圆形";
                ui->plainTextEdit->setPlainText("圆形的面积为：" + space.Cal_Cricle(texT));
            break;
            case 3:
                qDebug()<<"矩形";
                ui->plainTextEdit->setPlainText("矩形的面积为：" +space.Cal_Rectangle(texT));
            break;
            case 5:
            qDebug()<<"三角形";
                ui->plainTextEdit->setPlainText("三角形的面积为：" +space.Cal_Triangle(texT));
            break;
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
