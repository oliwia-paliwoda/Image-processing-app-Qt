#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Zmiana kontrastu i jasności");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_JasnoscR_valueChanged(int value)
{
    b_Red = value/100;
    odswiez();
}

void Dialog::on_JasnoscG_valueChanged(int value)
{
    b_Green = value/100;
    odswiez();
}

void Dialog::on_JasnoscB_valueChanged(int value)
{
    b_Blue  = value/100;
    odswiez();
}

void Dialog::on_KontrastR_valueChanged(int value)
{
     a_Red = value/100;
     odswiez();
}

void Dialog::on_KontrastG_valueChanged(int value)
{
    a_Green = value/100;
    odswiez();
}

void Dialog::on_KontrastB_valueChanged(int value)
{
    a_Blue = value/100;
    odswiez();
}

void Dialog::odswiez()
{
    for(int y=0; y<okno.rows; y++)
    for(int x=0; x<okno.cols; x++)
    {
    obraz_out.at<cv::Vec3b>(y,x)[0] = cv::saturate_cast<uchar>( a_Blue*( okno.at<cv::Vec3b>(y,x)    [0] ) + b_Blue );
    obraz_out.at<cv::Vec3b>(y,x)[1] = cv::saturate_cast<uchar>( a_Green*( okno.at<cv::Vec3b>(y,x)[1] ) + b_Green );
    obraz_out.at<cv::Vec3b>(y,x)[2] = cv::saturate_cast<uchar>( a_Red*( okno.at<cv::Vec3b>(y,x)[2] ) + b_Red );
    }
    cv::imshow("Zmieniony obraz", obraz_out);
}
