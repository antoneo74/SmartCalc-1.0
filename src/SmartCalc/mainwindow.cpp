#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calcdisignstyle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _flag = 0;
    this->setFixedSize(800,420);
    ui->tabWidget->setCurrentIndex(0);
    ui->customPlot->xAxis->setRange(-3,3);
    ui->customPlot->yAxis->setRange(-4,4);
    ui->Screen->setText("0");
    ui->scrollArea_2->setWidget(ui->depos_info);
    ui->scrollArea->setWidget(ui->label_info);
    ui->XValue->setReadOnly(true);
    ui->pushButton_Equal->setStyleSheet(calcDisignStyle::buttonYellowStyle());
    ui->pushButton_graph->setStyleSheet(calcDisignStyle::buttonBlueStyle());
    ui->pushButton_X->setStyleSheet(calcDisignStyle::buttonBlueStyle());

    connect(ui->pushButton_0, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_dot, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_left_bracket, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_right_bracket, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_mult, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_mod, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_exp, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_sin  , SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_acos, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()),this,SLOT(Button_clicked()));
    connect(ui->pushButton_X, SIGNAL(clicked()),this,SLOT(Button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::BeginInput()
{
    QPushButton *button = (QPushButton*)sender();
    QString SenderText = button->text();
    if(ui->Screen->text()=="0"){
        if(SenderText=='.'){
            ui->Screen->setText("0"+SenderText);
        } else {
            ui->Screen->setText(SenderText);
        }

    } else {
        ui->Screen->setText(ui->Screen->text()+SenderText);
    }
}


void MainWindow::Button_clicked()
{
    QPushButton *button = (QPushButton*)sender();
    QString SenderText = button->text();
    if(_flag)
    {
        _flag=0;
        if ((SenderText!="*" && SenderText!="/" && SenderText!="+" && SenderText!="-" && SenderText!="^") || ui->Screen->text()== "nan" || ui->Screen->text()== "Error")
        {
            on_pushButton_Clear_clicked();
        }
        BeginInput();
    }
    else
    {
        BeginInput();
    }
}


void MainWindow::on_pushButton_Clear_clicked()
{
    ui->Screen->setText("0");
    ui->XValue->setText("input X here");
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    _flag=0;
}

void MainWindow::on_pushButton_Backspace_clicked()
{
    QString text = ui->Screen->text();
    text.chop(1);
    if (text.isEmpty()){
        ui->Screen->setText("0");
    } else {
        ui->Screen->setText(text);
    }
}


void MainWindow::on_pushButton_Equal_clicked()
{
    double result=0;
    QString str1 = ui->Screen->text();
    QByteArray array = str1.toLocal8Bit();
    const char *str2 = array.data();

    QString XButtonValue = ui->XValue->text();
    double X = XButtonValue.toDouble();
    int error = push_button_equal(str2, &result,X);
    if (error) {
        ui->Screen->setText("Error");
    } else {
        QString itog = QString::number(result, 'g', 8);
        ui->Screen->setText(itog);
    }
    _flag=1;
}


void MainWindow::on_pushButton_X_clicked()
{
    ui->XValue->setReadOnly(false);
    ui->XValue->setText("");
}


void MainWindow::on_pushButton_graph_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    this->setFixedSize(1000,880);
    _flag=1;
    double a = -10;
    double b =  10;
    double h = 0.001;
    int N = (b - a) / h + 1;
    QVector<double> x(N), y(N);
    QString str1 = ui->Screen->text();
    QByteArray array = str1.toLocal8Bit();
    const char *str2 = array.data();

    int i=0;
    for (double X = a; X <= b; X += h,i++)
    {
        double result=0;
        if(push_button_equal(str2, &result,X) || result>20 || result < -20)
        {
            x[i] = X;
            y[i] = qQNaN();
        }
        else
        {
            x[i] = X;
            y[i] = result;
        }
    }
    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(a, b);//Для оси Ox
    double minY=0, maxY=0;
    for (int i = 1; i < N; i++) {
      if (y[i] > -20 && y[i] < 20)
      {
          minY = y[i];
          maxY = y[i];
          break;
      }
    }
    for (int i = 1; i < N; i++) {
      if (y[i] < minY) minY = y[i];
      if (y[i] > maxY) maxY = y[i];
    }
    ui->customPlot->yAxis->setRange(minY, maxY);//Для оси Oy
    ui->customPlot->replot();
}


QString MainWindow::BuildStringCreditInfo(int index, QDate date, double value1, double value2, double value3, double value4)
{
    QString str1 = QString::number(index);
    QString str2 = date.toString("MMMyyyy");
    QString str3 = QString::number(value1,'f', 2);
    QString str4 = QString::number(value2,'f', 2);
    QString str5 = QString::number(value3,'f', 2);
    QString str6 = QString::number(value4,'f', 2);
    return QString("%1\t%2\t%3\t%4\t%5\t%6\n\n").arg(str1,-3).arg(str2,-20).arg(str3,-30).arg(str4,-50).arg(str5,-50).arg(str6);
}


void MainWindow::AnuitetChecked()
{
    double payment = round(Anuitet(_bodyCredit, _durationCredit, _percentCredit)*100)/100;
    double totalPercent = round(Pereplata(_bodyCredit,payment,_durationCredit)*100)/100;
    double total = _bodyCredit + totalPercent;
    int index = 0;
    ui->month_payment->setText(QString::number(payment, 'f', 2));
    ui->interest_charges->setText(QString::number(totalPercent,'f',2));
    ui->total_amount->setText(QString::number(total,'f',2));

    while (_bodyCredit > 1)
    {
        double monthlyPercentPayment = Monthly_percent_payment(_bodyCredit, _percentCredit);
        double montlyPayBodyCredit = payment - monthlyPercentPayment;
        _bodyCredit -= montlyPayBodyCredit;
        _today = _today.addMonths(1);
        _titleCreditInfoLabel+= BuildStringCreditInfo(index+1, _today, payment, montlyPayBodyCredit, monthlyPercentPayment, _bodyCredit);
        index++;
    }
    ui->label_info->setText(_titleCreditInfoLabel);
}


void MainWindow::DiffChecked()
{
    int index = 0;
    double body_tmp = _bodyCredit;
    double montly_pay_basis_credit = _bodyCredit / _durationCredit;
    double pereplata = 0;
    while (_bodyCredit > 1)
    {
        double monthly_percent_payment = Monthly_percent_payment(_bodyCredit, _percentCredit);
        pereplata += monthly_percent_payment;
        double monthly_payment = montly_pay_basis_credit + monthly_percent_payment;
        _month_pay.append(monthly_payment);
        _month_perc.append(monthly_percent_payment);
        _bodyCredit -= montly_pay_basis_credit;
    }

    double min_pay = *std::min_element(_month_pay.begin(), _month_pay.end());
    double max_pay = *std::max_element(_month_pay.begin(), _month_pay.end());
    ui->month_payment->setText(QString::number(max_pay,'f',2)+"..."+QString::number(min_pay,'f',2));
    ui->interest_charges->setText(QString::number(pereplata,'f',2));
    ui->total_amount->setText(QString::number(body_tmp+pereplata, 'f', 2));

    for(; index < _month_pay.length(); index++)
    {
        _today = _today.addMonths(1);
        body_tmp-=montly_pay_basis_credit;
        _titleCreditInfoLabel+= BuildStringCreditInfo(index+1, _today,_month_pay[index],montly_pay_basis_credit, _month_perc[index], body_tmp);
    }
    ui->label_info->setText(_titleCreditInfoLabel);
}



void MainWindow::on_pushButton_creditCalc_clicked()
{
    VariableInit();
    if(_bodyCredit && _percentCredit && _durationCredit)
    {
        this->setFixedSize(1100,1000);

        if(ui->Anuit->isChecked()){
            AnuitetChecked();
        }
        else if (ui->Diff->isChecked())
        {
            DiffChecked();
        }
    }
}



void MainWindow::refreshCreditCalcWindow()
{
    this->setFixedSize(850,475);
    ui->Anuit->setChecked(true);
    ui->BodyCredit->clear();
    ui->DurationCredit->clear();
    ui->PercentCredit->clear();
    ui->month_payment->clear();
    ui->interest_charges->clear();
    ui->total_amount->clear();
    ui->label_info->setText("");
}


int MainWindow::GetDuration(QDate begin)
{
    int duration = 0;
    QDate end;
    int value = ui->DurationDepos->text().toInt();
    if(ui->PeriodValueDepos->currentText() == "Дней")
    {
        end = begin.addDays(value);
    }
    else if(ui->PeriodValueDepos->currentText() == "Месяцев")
    {
        end = begin.addMonths(value);
    }
    else  if(ui->PeriodValueDepos->currentText() == "Лет")
    {
        end = begin.addYears(value);
    }
    duration = begin.daysTo(end);

    return duration;
}


QDate MainWindow::GetPeriodOfPayment(QDate day)
{
    if(ui->periodOfPayment->currentText() == "Каждый день")
    {
        day=day.addDays(1);
    }
    else if(ui->periodOfPayment->currentText() == "Каждую неделю")
    {
        day=day.addDays(7);
    }
    else if(ui->periodOfPayment->currentText() == "Раз в месяц")
    {
        day=day.addMonths(1);
    }
    else if(ui->periodOfPayment->currentText() == "Раз в квартал")
    {
        day=day.addMonths(3);
    }
    else if(ui->periodOfPayment->currentText() == "Раз в полгода")
    {
        day=day.addMonths(6);
    }
    else if(ui->periodOfPayment->currentText() == "Раз в год")
    {
        day=day.addYears(1);
    }
    else if(ui->periodOfPayment->currentText() == "В конце срока")
    {
        day=day.addDays(GetDuration(day));
    }
    return day;
}


QDate MainWindow::GetToday()
{
    QDate today = QDate::currentDate();
    return today;
}


double MainWindow::GetAccruedDepositPercent(QDate begin, double deposit, double percent, int duration)
{
    int daysToEndOfYear=begin.daysTo(QDate(begin.year(),12,31));
    double result=0;
    if(duration<=daysToEndOfYear)
    {
        result=Accrued_interest(deposit,percent,duration,begin.daysInYear());
    }
    else
    {
        result=Accrued_interest(deposit,percent,daysToEndOfYear,begin.daysInYear());
        duration -= daysToEndOfYear;
        begin = begin.addYears(1);
        while(duration>begin.daysInYear())
        {
            result+=Accrued_interest(deposit,percent,begin.daysInYear(),begin.daysInYear());
            duration -= begin.daysInYear();
            begin = begin.addYears(1);
        }
        result+=Accrued_interest(deposit,percent,duration,begin.daysInYear());
    }
    return result;
}


void MainWindow::VariableInit()
{
    _month_pay.clear();
    _month_perc.clear();
    _today = GetToday();
    _bodyCredit = ui->BodyCredit->text().toDouble();
    _percentCredit = ui->PercentCredit->text().toDouble();
    _durationCredit = (ui->PeriodValueCredit->currentText() == "лет" ? ui->DurationCredit->text().toDouble()*12 : ui->DurationCredit->text().toDouble());
    _bodyDepos = ui->BodyDepos->text().toDouble();
    _percentDepos = ui->PercentDepos->text().toDouble();
    _durationDepos = GetDuration(ui->BeginDepos->date());
    _titleCreditInfoLabel = "№\tмесяц\t\tСумма платежа, руб.\tПлатеж по основному долгу, руб\tПлатеж по процентам, руб\tОстаток долга, руб\n\n";
    _titleDeposInfoLabel="Дата\t\tНачислено процентов, руб.\tВклад пополнен, руб\tОстаток на вкладе, руб\n\n";

}

QString MainWindow::BuildStringDeposInfo(QDate date, double percent, double addValue, double totalValue)
{
    QString str1 = date.toString("dd.MM.yyyy");
    QString str2 = (percent ? QString::number(percent,'f', 2) : "");
    QString str3 = QString::number(addValue,'f', 2);
    QString str4 = QString::number(totalValue,'f', 2);

    return QString("%1\t%2\t%3\t%4\n\n").arg(str1,-3).arg(str2,-60).arg(str3,-40).arg(str4);
}


void MainWindow::on_pushButton_Depos_clicked()
{
    VariableInit();
    SortVectorDepos();

    if(_bodyDepos && _percentDepos && _durationDepos)
    {
        this->setFixedSize(850,1100);
    }
    QDate begin = ui->BeginDepos->date();
    QDate end = begin.addDays(_durationDepos);
    QDate tmp = begin;
    double accrued=0;

    while (_durationDepos>0)
    {
        tmp = GetPeriodOfPayment(tmp);
        tmp = (tmp<end ? tmp : end);

        double percentForPeriod = 0;
        double popolnenie=0;

        if(!_additionSum.isEmpty())
        {
            for (int i = 0; i < _additionSum.size(); i++)
            {
                if (_additionSum[i].date <=tmp && _additionSum[i].date > begin)
                {
                    int _days = begin.daysTo(_additionSum[i].date);
                    percentForPeriod+=round(GetAccruedDepositPercent(begin, _bodyDepos, _percentDepos, _days)*100)/100;
                    popolnenie = (_additionSum[i].action ? _additionSum[i].sum : -_additionSum[i].sum);
                    _bodyDepos+=popolnenie;
                    _durationDepos-=_days;
                    _titleDeposInfoLabel+= BuildStringDeposInfo(_additionSum[i].date, 0, popolnenie,_bodyDepos);
                    begin=_additionSum[i].date;
                    _additionSum.pop_front();
                    i--;
                    popolnenie=0;
                }
            }
        }
        int days = begin.daysTo(tmp);
        percentForPeriod += round(GetAccruedDepositPercent(begin, _bodyDepos, _percentDepos, days)*100)/100;
        accrued+=percentForPeriod;
        begin=tmp;
        _durationDepos-=days;

        if (ui->checkBox->isChecked())
        {
            _bodyDepos+=percentForPeriod;
            popolnenie=percentForPeriod;
        }

        _titleDeposInfoLabel+= BuildStringDeposInfo(tmp, percentForPeriod, popolnenie,_bodyDepos);
    }

    double tax = Tax(accrued, ui->CBR->text().toDouble(), ui->NDFL->text().toDouble()) ;
    ui->label_interestCharges->setText(QString::number(accrued,'f',2));
    ui->label_nalog->setText(QString::number(tax, 'f', 2));
    ui->label_itog->setText(QString::number((accrued-tax),'f',2));
    ui->label_recievedIncome->setText(QString::number(_bodyDepos,'f',2));
    ui->depos_info->setText(_titleDeposInfoLabel);
    _additionSum.clear();
}


void MainWindow::refreshDeposCalcWindow()
{
    this->setFixedSize(850,450);

    ui->CBR->setText("8.5");
    ui->NDFL->setText("13.0");
    ui->BeginDepos->setDate(GetToday());
    ui->BodyDepos->clear();
    ui->DurationDepos->clear();
    ui->PercentDepos->clear();
    ui->checkBox->setChecked(false);
    ui->AddDeposDate->setDate(GetToday());
    ui->AddDeposDate->hide();
    ui->AddDeposSum->clear();
    ui->AddDeposSum->hide();
    ui->TakeDeposDate->setDate(GetToday());
    ui->TakeDeposDate->hide();
    ui->TakeDeposSum->clear();
    ui->TakeDeposSum->hide();
    ui->PeriodValueDepos->setCurrentIndex(1);
    ui->periodOfPayment->setCurrentIndex(2);
    ui->pushButton_AddDepos->setText("+");
    ui->pushButton_TakeDepos->setText("-");
    ui->pushButton_AddDepos->setStyleSheet(calcDisignStyle::buttonWithBigFont());
    ui->pushButton_TakeDepos->setStyleSheet(calcDisignStyle::buttonWithBigFont());
    ui->pushButton_Depos->setStyleSheet(calcDisignStyle::buttonWithSmallFont());
    _additionSum.clear();
}



void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0){
        on_pushButton_Clear_clicked();
        this->setFixedSize(800,420);
    } else if (index==1){
        on_pushButton_Clear_clicked();
        this->setFixedSize(1000,880);
    }else if (index==2){
        refreshCreditCalcWindow();
    }else if (index==3){
        refreshDeposCalcWindow();
    }
}


void MainWindow::AddValueToVectorDepos(bool action)
{
    addToDepos node;
    if(action)
    {
        node.date = ui->AddDeposDate->date();
        node.sum = ui->AddDeposSum->text().toDouble();
        node.action = action;
        ui->AddDeposDate->setDate(GetToday());
        ui->AddDeposSum->clear();
    }
    else
    {
        node.date = ui->TakeDeposDate->date();
        node.sum = ui->TakeDeposSum->text().toDouble();
        node.action = action;
        ui->TakeDeposDate->setDate(GetToday());
        ui->TakeDeposSum->clear();
     }
     _additionSum.push_back(node);
}


void MainWindow::SortVectorDepos()
{
    std::sort(_additionSum.begin(),_additionSum.end(), [](const addToDepos& x1, const addToDepos& x2) -> bool
        {
            return x1.date < x2.date;
        }
    );
}


void MainWindow::on_pushButton_AddDepos_clicked()
{
    if(ui->pushButton_AddDepos->text()=="+")
    {
        ui->AddDeposDate->setVisible(true);
        ui->AddDeposSum->setVisible(true);
        ui->pushButton_AddDepos->setText("Добавить");
        ui->pushButton_AddDepos->setStyleSheet(calcDisignStyle::buttonWithSmallFont());
    }
    else
    {
        AddValueToVectorDepos(true);
    }
}


void MainWindow::on_pushButton_TakeDepos_clicked()
{
    if(ui->pushButton_TakeDepos->text()=="-")
    {
        ui->TakeDeposDate->setVisible(true);
        ui->TakeDeposSum->setVisible(true);
        ui->pushButton_TakeDepos->setText("Снять");
        ui->pushButton_TakeDepos->setStyleSheet(calcDisignStyle::buttonWithSmallFont());
    }
    else
    {
        AddValueToVectorDepos(false);
    }
}
