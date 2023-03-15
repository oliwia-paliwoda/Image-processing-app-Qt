#ifndef MOJEOBRAZKI_H
#define MOJEOBRAZKI_H

#include <QMainWindow>
#include <QApplication>
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
#include  <opencv4/opencv2/opencv.hpp>
#include <QSlider>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include "dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MojeObrazki; }
QT_END_NAMESPACE

class MojeObrazki : public QMainWindow
{
    Q_OBJECT

    QImage *Image;
    QGraphicsScene *GraphicsScene;
    QPixmap Pixmap;
    QGraphicsPixmapItem *GraphicsPixmapItem;
    QLabel StatusCzas;
    QLabel StatusInfo;
    QTimer *Timer;
    QTime Time;
    QProgressBar ProgressBar;
    QString WybranyObraz;
    QSlider Slider;

public:
    MojeObrazki(QWidget *parent = nullptr);
    ~MojeObrazki();
    cv::Mat zrodlo;
    cv::Mat wynik;
    cv::Mat src;
    cv::Mat grad_x, grad_y, grad, dst, kernel, detected_edges, dst_x, dst_y;
    cv::Point anchor;
    cv::Mat abs_grad_x, abs_grad_y;
    int druga_wielkosc=1;
    int ddepth = CV_16S;
    int ksize=3;
    int delta=0;
    int scale=1;
    int lowThreshold;
    int highThreshold;
    int kernel_size=3;
    int ratio=2;

    int prog;
    int typ;
    int kat_obrotu=0;
    int wielkosc_okna=0;
    int wsp_skali=100;
     void Progowanie();
        static void Prog_callback(int v, void* p)
        {
        MojeObrazki *img = (MojeObrazki*) p;
        img->Progowanie();
        }
        static void Rotacja_callback(int v, void* p)
        { MojeObrazki *img = (MojeObrazki*) p; img->Rotacja(); }

        static void Skaluj_callback(int v, void* p)
        { MojeObrazki *img = (MojeObrazki*) p; img->Skaluj(); }

        static void Mediana_callback ( int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Mediana(); }

        static void Usrednianie_callback(int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Usrednianie(); }

        static void Gauss_callback(int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Gauss(); }

        static void Canny_callback(int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Canny();}

        static void Erozja_callback(int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Erozja();}

        static void Dylatacja_callback(int value, void* pointer )
        { MojeObrazki *img = (MojeObrazki*) pointer; img->Dylatacja();}

         static void Otwarcie_callback(int value, void* pointer )
         { MojeObrazki *img = (MojeObrazki*) pointer; img->Otwarcie();}


        static void Zamkniecie_callback(int value, void* pointer )
          { MojeObrazki *img = (MojeObrazki*) pointer; img->Zamkniecie();}

         static void Gradient_Morfologiczny_callback(int value, void* pointer )
         { MojeObrazki *img = (MojeObrazki*) pointer; img->Gradient_Morfologiczny();}






private slots:
    void on_actionZamknij_triggered();
    void on_Timer();
    void on_actionOtworz_triggered();
    void on_actionZapisz_triggered();
    void on_actionPokaz_Obrazek_triggered();
    void on_actionRGB_triggered();
    void on_actionYCrCb_triggered();
    void on_actionHSV_triggered();
    void on_actionKontrast_triggered();
    void on_actionProgowanie_RGB_triggered();
    void Skaluj();
    void Rotacja();
    void Mediana();
    void Usrednianie();
    void Gauss();
    void Sobel();
    void Prewitt();
    void Canny();
    void Erozja();
    void Dylatacja();
    void Otwarcie();
    void Zamkniecie();
    void Gradient_Morfologiczny();


    void on_actionSkalowanie_triggered();

    void on_actionRotacja_triggered();

    void on_actionFiltracja_u_redniaj_ca_triggered();

    void on_actionFiltracja_gaussowska_triggered();

    void on_actionFiltracja_medianowa_triggered();

    void on_actionFiltr_Sobela_triggered();

    void on_actionFiltr_Prewitta_triggered();

    void on_actionFiltr_Canny_ego_triggered();

    void on_actionErozja_triggered();

    void on_actionDylatacja_triggered();

    void on_actionOtwarcie_triggered();

    void on_actionZamkniecie_triggered();

    void on_actionGradient_morfologiczny_triggered();

private:
    Ui::MojeObrazki *ui;
    Dialog Okno;





};
#endif // MOJEOBRAZKI_H
