#include "Calculator.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), pendingValue(0.0), waitingForOperand(true)
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    createLayout();
}

void Calculator::createLayout()
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(2);

    mainLayout->addWidget(display, 0, 0, 1, 4);

    QString digits[10] = {"0","1","2","3","4","5","6","7","8","9"};
    int pos = 0;
    for (int row=3; row>0; --row)
        for (int col=0; col<3; ++col)
            addDigitButton(digits[++pos], row, col);

    addDigitButton("0", 4, 1);
    QPushButton *pointButton = new QPushButton(".");
    mainLayout->addWidget(pointButton, 4, 0);
    connect(pointButton, &QPushButton::clicked, [this](){
        if (waitingForOperand) display->clear();
        if (!display->text().contains('.'))
            display->setText(display->text() + ".");
        waitingForOperand = false;
    });

    QPushButton *clearButton = new QPushButton("C");
    mainLayout->addWidget(clearButton, 4, 2);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearClicked);

    addOperatorButton("+",1,3);
    addOperatorButton("-",2,3);
    addOperatorButton("*",3,3);
    addOperatorButton("/",4,3);

    QPushButton *equalsButton = new QPushButton("=");
    mainLayout->addWidget(equalsButton,1,4,4,1);
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::equalsClicked);
}

void Calculator::addDigitButton(const QString &text, int row, int column)
{
    QPushButton *button = new QPushButton(text);
    static_cast<QGridLayout*>(layout())->addWidget(button, row, column);
    connect(button, &QPushButton::clicked, this, &Calculator::digitClicked);
}

void Calculator::addOperatorButton(const QString &op, int row, int column)
{
    QPushButton *button = new QPushButton(op);
    static_cast<QGridLayout*>(layout())->addWidget(button, row, column);
    connect(button, &QPushButton::clicked, this, &Calculator::operatorClicked);
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString digitValue = clickedButton->text();
    if (display->text() == "0" && digitValue == "0") return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + digitValue);
}

void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    if (!pendingOperator.isEmpty()) {
        if (pendingOperator == "+") pendingValue += operand;
        else if (pendingOperator == "-") pendingValue -= operand;
        else if (pendingOperator == "*") pendingValue *= operand;
        else if (pendingOperator == "/") pendingValue /= operand;
        display->setText(QString::number(pendingValue));
    } else {
        pendingValue = operand;
    }
    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalsClicked()
{
    double operand = display->text().toDouble();
    if (pendingOperator == "+") pendingValue += operand;
    else if (pendingOperator == "-") pendingValue -= operand;
    else if (pendingOperator == "*") pendingValue *= operand;
    else if (pendingOperator == "/") pendingValue /= operand;
    display->setText(QString::number(pendingValue));
    pendingOperator.clear();
    waitingForOperand = true;
}

void Calculator::clearClicked()
{
    display->setText("0");
    pendingValue = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

