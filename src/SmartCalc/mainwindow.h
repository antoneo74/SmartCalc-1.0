#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDate>
#include "qcustomplot.h"
#include <QLabel>
#include <algorithm>


#ifdef __cplusplus
extern "C" {
#endif

#include "../calc.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void AnuitetChecked();

    void DiffChecked();

    void refreshCreditCalcWindow();

    void refreshDeposCalcWindow();

    int GetDuration(QDate);

    double GetAccruedDepositPercent(QDate, double, double, int);

    QDate GetPeriodOfPayment(QDate);

    QDate GetToday();

    void AddValueToVectorDepos(bool);

    void SortVectorDepos();

    void VariableInit();

    QString BuildStringDeposInfo(QDate, double, double, double);

    QString BuildStringCreditInfo(int, QDate, double, double, double, double);

    void BeginInput();



private slots:
    void Button_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Backspace_clicked();

    void on_pushButton_Equal_clicked();

    void on_pushButton_X_clicked();

    void on_pushButton_graph_clicked();

    void on_pushButton_creditCalc_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_Depos_clicked();

    void on_pushButton_AddDepos_clicked();

    void on_pushButton_TakeDepos_clicked();


private:
    Ui::MainWindow *ui;

    int _flag;

    double _bodyDepos, _bodyCredit, _percentDepos, _percentCredit, _durationDepos, _durationCredit;

    struct addToDepos
    {
        QDate date;
        double sum;
        bool action;
    };

    QVector<addToDepos> _additionSum;

    QVector<double> _month_pay, _month_perc;

    QString _titleDeposInfoLabel, _titleCreditInfoLabel;

    QDate _today;

};
#endif // MAINWINDOW_H
