#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();

private:
    void createLayout();
    void addDigitButton(const QString &text, int row, int column);
    void addOperatorButton(const QString &op, int row, int column);

    QLineEdit *display;
    double pendingValue;
    QString pendingOperator;
    bool waitingForOperand;
};

#endif // CALCULATOR_H
