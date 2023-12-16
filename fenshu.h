#ifndef FENSHU_H
#define FENSHU_H

#include <iostream>
#include <QWidget>

class Integer
{
public:
    int numberSon;
    int numberMom;
};

class fenshu : public Integer
{
public:

    fenshu(int x = 0, int y = 1);
    ~fenshu();

    fenshu operator+(const fenshu& other) const;

    fenshu operator-(const fenshu& other) const;

    fenshu operator*(const fenshu& other) const;

    fenshu operator/(const fenshu& other) const;

    fenshu tofenshu(const QString & Str) const;
    QString toString() const;

    void Simplify();

    friend std::ostream& operator<<(std::ostream& output, const fenshu& other);

    friend std::istream& operator>>(std::istream& input, fenshu& other);
};

#endif // FENSHU_H
