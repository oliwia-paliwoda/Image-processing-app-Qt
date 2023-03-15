#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QProgressBar>
#include <QTimer>
#include <opencv4/opencv2/opencv.hpp>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    cv::Mat okno;
    cv::Mat obraz_out;
    double a_Blue;
    double a_Green;
    double a_Red;
    int  b_Blue;
    int b_Green;
    int b_Red;

private slots:
        void on_JasnoscR_valueChanged(int value);

        void on_JasnoscG_valueChanged(int value);

        void on_JasnoscB_valueChanged(int value);

        void on_KontrastR_valueChanged(int value);

        void on_KontrastG_valueChanged(int value);

        void on_KontrastB_valueChanged(int value);

        void odswiez();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
