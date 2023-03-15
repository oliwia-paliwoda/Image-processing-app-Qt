#include "mojeobrazki.h"
#include "ui_mojeobrazki.h"

MojeObrazki::MojeObrazki(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MojeObrazki)
{
    ui->setupUi(this);
    setWindowTitle("Aplikacja");
    resize(1024,800);

    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(on_Timer()));
    Timer->start(1000);
    StatusCzas.setFixedWidth(150);
    ProgressBar.setValue(0);
    StatusCzas.setText(QTime::currentTime().toString("HH:mm:ss"));
    StatusInfo.setText("Dzień dobry");

    ui->statusBar->addPermanentWidget(&StatusCzas,1);
    ui->statusBar->addPermanentWidget(&ProgressBar,1);
    ui->statusBar->addPermanentWidget(&StatusInfo,2);
    ui->statusBar->addPermanentWidget(&Slider,1);
    ui->statusBar->addPermanentWidget(&Slider,2);

}

MojeObrazki::~MojeObrazki()
{
    Timer->stop();
    delete Timer;

    delete ui;
}


void MojeObrazki::on_actionZamknij_triggered()
{

    QMessageBox MessageBox(QMessageBox::Warning,"Wyjście z Programu","Czy chcesz wyjść z programu?",QMessageBox::Yes|QMessageBox::No);
        MessageBox.setButtonText(QMessageBox::Yes,"Tak");
        MessageBox.setButtonText(QMessageBox::No,"Nie");
        if (MessageBox.exec()==QMessageBox::Yes)
        {
        QApplication::quit();
        }

}

void MojeObrazki::on_Timer()
{
    StatusCzas.setText(QTime::currentTime().toString("HH:mm:ss"));
}

void MojeObrazki::on_actionOtworz_triggered()
{
    ProgressBar.setValue(0);
    QString imagePath = QFileDialog::getOpenFileName(this,tr("Otwórz Plik"),"",tr("JPEG(*.jpg *.jpeg);;PNG (*.png)"));
    ProgressBar.setValue(50);
    if (!imagePath.isEmpty())
    {
        Image = new QImage();
        Image->load(imagePath);

        Pixmap = QPixmap::fromImage(*Image);
        GraphicsScene = new QGraphicsScene(this);
        GraphicsPixmapItem = GraphicsScene->addPixmap(Pixmap);
        GraphicsScene->setSceneRect(Pixmap.rect());
        ui->graphicsView->setScene(GraphicsScene);
        delete (Image); // zabezpieczenie przed wyciekiem pamięci.
        StatusInfo.setText("Wybrany Plik:"+imagePath+"rozmiar:"+QString::number(Pixmap.width())+"x"+QString::number(Pixmap.height()));
        WybranyObraz=imagePath;
        ProgressBar.setValue(100);
    }
}

void MojeObrazki::on_actionZapisz_triggered(){

     ProgressBar.setValue(0);
     if (GraphicsScene!=NULL)
     {
     QString imagePath = QFileDialog::getSaveFileName(this,tr("Zapisz Plik"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
     ProgressBar.setValue(50);
     if (!imagePath.isEmpty())
     {
     QImage image = GraphicsPixmapItem->pixmap().toImage();
     if (image.size().isValid()==true) image.save(imagePath);
     }
     }
     else
     {
     QMessageBox(QMessageBox::Information,"Informacja","Nie załadowano pliku obrazu! Nie ma co zapisać",QMessageBox::Ok).exec();
     }
     ProgressBar.setValue(100);
    }

void MojeObrazki::on_actionPokaz_Obrazek_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
      cv::Mat obrazek_wejsciowy = cv::imread(WybranyObraz.toStdString().c_str());
      cv::imshow("Obrazek Przetwarzany",obrazek_wejsciowy);
    }
}


void MojeObrazki::on_actionRGB_triggered()
{
    cv::Mat pokaz_blue;
    cv::Mat pokaz_red;
    cv::Mat pokaz_green;

    if(!WybranyObraz.isEmpty())
    {
      cv::Mat obrazek_wejsciowy = cv::imread(WybranyObraz.toStdString().c_str());
      cv::Mat skladowa_blue[3];
      cv::split(obrazek_wejsciowy, skladowa_blue);
      skladowa_blue[1]= cv::Mat::zeros(skladowa_blue[1].size(), CV_8UC1);
      skladowa_blue[2]= cv::Mat::zeros(skladowa_blue[2].size(), CV_8UC1);
      cv::merge(skladowa_blue,3,pokaz_blue);
      cv::imshow("Składowa B", pokaz_blue);

      cv::Mat skladowa_red[3];
      cv::split(obrazek_wejsciowy, skladowa_red);
      skladowa_red[0]= cv::Mat::zeros(skladowa_red[0].size(), CV_8UC1);
      skladowa_red[1]= cv::Mat::zeros(skladowa_red[1].size(), CV_8UC1);
      cv::merge(skladowa_red,3,pokaz_red);
      cv::imshow("Składowa R", pokaz_red);

      cv::Mat skladowa_green[3];
      cv::split(obrazek_wejsciowy, skladowa_green);
      skladowa_green[0]= cv::Mat::zeros(skladowa_green[0].size(), CV_8UC1);
      skladowa_green[2]= cv::Mat::zeros(skladowa_green[2].size(), CV_8UC1);
      cv::merge(skladowa_green,3,pokaz_green);
      cv::imshow("Składowa G", pokaz_green);
    }
}

void MojeObrazki::on_actionYCrCb_triggered()
{
    cv::Mat obrazek_wejsciowy = cv::imread(WybranyObraz.toStdString().c_str());
    cv::Mat konwersja_YCrCb;
    cv::Mat skladowe_ycrcb[3];
    cv::cvtColor(obrazek_wejsciowy, konwersja_YCrCb, cv::COLOR_BGR2YCrCb);
    cv::split(konwersja_YCrCb,skladowe_ycrcb);
    cv::imshow("składowa Y",skladowe_ycrcb[0]);
    cv::imshow("składowa Cr",skladowe_ycrcb[1]);
    cv::imshow("składowa Cb",skladowe_ycrcb[2]);

 }

void MojeObrazki::on_actionHSV_triggered()
{
    cv::Mat obrazek_wejsciowy = cv::imread(WybranyObraz.toStdString().c_str());
    cv::Mat konwersja_HSV;
    cv::Mat skladowe_hsv[3];
    cv::cvtColor(obrazek_wejsciowy,konwersja_HSV,cv::COLOR_BGR2HSV);
    cv::split(konwersja_HSV,skladowe_hsv);
    cv::imshow("składowa H",skladowe_hsv[0]);
    cv::imshow("składowa S",skladowe_hsv[1]);
    cv::imshow("składowa V",skladowe_hsv[2]);
}



void MojeObrazki::on_actionKontrast_triggered()
{

    if(!WybranyObraz.isEmpty())
       {
          cv::Mat obrazek_wejsciowy = cv::imread(WybranyObraz.toStdString().c_str());
          Okno.okno = obrazek_wejsciowy;
          Okno.obraz_out = cv::Mat::zeros( obrazek_wejsciowy.size(), obrazek_wejsciowy.type() );
          Okno.show();
       }

}

void MojeObrazki::on_actionProgowanie_RGB_triggered()
{
    char trackbar_type[] = "Rodzaj progowania: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted"; // dostępne tryby progowania
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    cv::cvtColor( obrazek_wejsciowy, zrodlo, cv::COLOR_BGR2GRAY );
    cv::namedWindow("Progowanie",cv::WINDOW_AUTOSIZE);
    cv::createTrackbar( trackbar_type, "Progowanie", &typ, 4, &MojeObrazki::Prog_callback,this);
    cv::createTrackbar("Wartość progu","Progowanie",&prog,255,&MojeObrazki::Prog_callback,this);
    Progowanie();
    }
}


void MojeObrazki::Progowanie( )
{
cv::threshold(zrodlo, wynik, prog, 255, typ); cv::imshow( "Progowanie", wynik );
}

void MojeObrazki::Rotacja()
{
double angle = kat_obrotu;
cv::Size rozmiar;
rozmiar.width=zrodlo.cols;
rozmiar.height=zrodlo.rows;
cv::Point2f punkt_obrotu(rozmiar.width/2., rozmiar.height/2.);
cv::Mat macierz_obrotu = cv::getRotationMatrix2D(punkt_obrotu, angle, 1.0);
cv::warpAffine(zrodlo, wynik, macierz_obrotu, rozmiar);
cv::imshow("Rotacja", wynik );
}

void MojeObrazki::Skaluj()
{
double wspolczynnik=wsp_skali+1;
wspolczynnik/=100;
double Skala_x=wspolczynnik;
double Skala_y=wspolczynnik;
cv::Size rozmiar;
cv::resize(zrodlo, wynik, rozmiar, Skala_x, Skala_y, cv::INTER_LINEAR);
cv::imshow("Skalowanie", wynik);
}

void MojeObrazki::on_actionSkalowanie_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Skalowanie",cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Skalowanie",zrodlo.cols*2,zrodlo.rows*2);
    wsp_skali=100;
    cv::createTrackbar("Współczynnik Skali", "Skalowanie", &wsp_skali, 200,
    &MojeObrazki::Skaluj_callback, this);
    Skaluj();

}
}

void MojeObrazki::on_actionRotacja_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Rotacja",cv::WINDOW_AUTOSIZE);
    kat_obrotu=0;
    cv::createTrackbar("Kąt obrotu","Rotacja",&kat_obrotu,360,
    &MojeObrazki::Rotacja_callback,this);
    Rotacja();
    }
}

void MojeObrazki::Mediana()
{
int wymiar_okna=(2*wielkosc_okna)+1; // Współczynnik okna musi być nieparzysty
/* wywołujemy funkcje filtracji medianowej i aktualizujemy wynik operacji */
cv::medianBlur ( zrodlo, wynik, wymiar_okna );
cv::imshow("Filtr medianowy", wynik ); }

void MojeObrazki::Usrednianie()
{
int wymiar_okna=(2*wielkosc_okna)+1; // Współczynnik okna musi być nieparzysty
/* wywołujemy funkcje filtracji uśredniającej i aktualizujemy wynik operacji */
cv::blur( zrodlo, wynik, cv::Size(wymiar_okna, wymiar_okna) );
cv::imshow("Filtr uśredniający", wynik ); }

void MojeObrazki::Gauss()
{
 int wymiar_okna=(2*wielkosc_okna)+1; // Współczynnik okna musi być nieparzysty
/* wywołujemy funkcje filtracji gausowskiej i aktualizujemy wynik operacji */
cv::GaussianBlur( zrodlo, wynik, cv::Size(wymiar_okna, wymiar_okna) ,0 ,0);
cv::imshow("Filtr Gaussa", wynik ); }

void MojeObrazki::on_actionFiltracja_u_redniaj_ca_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Filtr uśredniający",cv::WINDOW_AUTOSIZE);
    wielkosc_okna=1;
    cv::createTrackbar("Wielkość okna", "Filtr uśredniający", &wielkosc_okna, 10,
    &MojeObrazki::Usrednianie_callback, this );
    Usrednianie();
    }
}

void MojeObrazki::on_actionFiltracja_gaussowska_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Filtr Gaussa",cv::WINDOW_AUTOSIZE);
    wielkosc_okna=1;
    cv::createTrackbar("Wielkość okna", "Filtr Gaussa", &wielkosc_okna, 10,
    &MojeObrazki::Gauss_callback, this );
    Gauss();
    }
}


void MojeObrazki::on_actionFiltracja_medianowa_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Filtr medianowy",cv::WINDOW_AUTOSIZE);
    wielkosc_okna=1;
    cv::createTrackbar("Wielkość okna", "Filtr medianowy", &wielkosc_okna, 10,
    &MojeObrazki::Mediana_callback, this );
    Mediana();
    }
}

void MojeObrazki::Sobel(){


    cv::GaussianBlur( zrodlo, src, cv::Size(3, 3) ,0 ,0);
    cv::imshow("a", src);
    cv::imshow("b", zrodlo);
    cv::Sobel(src, grad_x, ddepth, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT );
    cv::convertScaleAbs( grad_x, abs_grad_x );
    cv::imshow("c", abs_grad_x);
    cv::Sobel(src, grad_y, ddepth, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT );
    cv::convertScaleAbs( grad_y, abs_grad_y );
    cv::imshow("d",abs_grad_y);
    cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    cv::imshow("Filtr Sobela", grad);
}

void MojeObrazki::Prewitt(){

    cv::filter2D(zrodlo, zrodlo, CV_16S, 3, cv::Point(-1,-1), 0, cv::BORDER_DEFAULT);
            cv::Sobel(zrodlo, grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT );
            cv::convertScaleAbs( grad_x, abs_grad_x);
            cv::Sobel(zrodlo, grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT );
            cv::convertScaleAbs( grad_y, abs_grad_y );
            cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, zrodlo );
            cv::imshow("Filtr Prewitta", zrodlo);
}

void MojeObrazki::Canny(){
    cv::GaussianBlur( zrodlo, detected_edges,  cv::Size(3, 3) ,0 ,0);
    cv::Canny(detected_edges,detected_edges, lowThreshold, lowThreshold*ratio,
    kernel_size );
    cv::imshow("Filtr Canny'ego",detected_edges);
}

void MojeObrazki::on_actionFiltr_Sobela_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_GRAYSCALE);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Filtr Sobela",cv::WINDOW_AUTOSIZE);
    Sobel();
    }

}

void MojeObrazki::on_actionFiltr_Prewitta_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_GRAYSCALE);
    zrodlo = obrazek_wejsciowy;
    anchor = cv::Point(-1, -1);
    cv::namedWindow("Filtr Prewitta",cv::WINDOW_AUTOSIZE);
    Prewitt();
    }

}

void MojeObrazki::on_actionFiltr_Canny_ego_triggered()
{
    if(!WybranyObraz.isEmpty())
    {
    cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_GRAYSCALE);
    zrodlo = obrazek_wejsciowy;
    cv::namedWindow("Filtr Canny'ego",cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Próg T_min", "Filtr Canny'ego", &lowThreshold, 100,
    &MojeObrazki::Canny_callback, this );
    Canny();
    }

}


void MojeObrazki::on_actionErozja_triggered()
{
    if(!WybranyObraz.isEmpty())
        {
            cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
            zrodlo = obrazek_wejsciowy;
            cv::namedWindow("Erozja",cv::WINDOW_AUTOSIZE);
            wielkosc_okna=0;
            druga_wielkosc=0;
            cv::createTrackbar("Typ elementu strukturalnego", "Erozja", &wielkosc_okna, 2, &MojeObrazki::Erozja_callback, this);
            cv::createTrackbar("Wartość", "Erozja", &druga_wielkosc, 11, &MojeObrazki::Erozja_callback, this);

            Erozja();
        }


}

void MojeObrazki::on_actionDylatacja_triggered()
{
    if(!WybranyObraz.isEmpty())
        {
            cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
            zrodlo = obrazek_wejsciowy;
            cv::namedWindow("Dylatacja",cv::WINDOW_AUTOSIZE);
            wielkosc_okna=0;
            druga_wielkosc=0;
            cv::createTrackbar("Typ elementu strukturalnego", "Dylatacja", &wielkosc_okna, 2, &MojeObrazki::Dylatacja_callback, this);
            cv::createTrackbar("Wartość", "Dylatacja", &druga_wielkosc, 11, &MojeObrazki::Dylatacja_callback, this);

            Dylatacja();
        }
}

void MojeObrazki::on_actionOtwarcie_triggered()
{
    if(!WybranyObraz.isEmpty())
        {
            cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
            zrodlo = obrazek_wejsciowy;
            cv::namedWindow("Otwarcie",cv::WINDOW_AUTOSIZE);
            wielkosc_okna=0;
            druga_wielkosc=0;
            cv::createTrackbar("Typ elementu strukturalnego", "Otwarcie", &wielkosc_okna, 2, &MojeObrazki::Otwarcie_callback, this);
            cv::createTrackbar("Wartość", "Otwarcie", &druga_wielkosc, 11, &MojeObrazki::Otwarcie_callback, this);

            Otwarcie();
        }
}

void MojeObrazki::on_actionZamkniecie_triggered()
{
   if(!WybranyObraz.isEmpty())
        {
            cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
            zrodlo = obrazek_wejsciowy;
            cv::namedWindow("Zamkniecie",cv::WINDOW_AUTOSIZE);
            wielkosc_okna=0;
            druga_wielkosc=0;
            cv::createTrackbar("Typ elementu strukturalnego", "Zamkniecie", &wielkosc_okna, 2, &MojeObrazki::Zamkniecie_callback, this);
            cv::createTrackbar("Wartość", "Zamkniecie", &druga_wielkosc, 11, &MojeObrazki::Zamkniecie_callback, this);

            Zamkniecie();
        }
}

void MojeObrazki::on_actionGradient_morfologiczny_triggered()
{
    if(!WybranyObraz.isEmpty())
        {
            cv::Mat obrazek_wejsciowy=cv::imread(WybranyObraz.toStdString().c_str(),cv::IMREAD_COLOR);
            zrodlo = obrazek_wejsciowy;
            cv::namedWindow("Gradient",cv::WINDOW_AUTOSIZE);
            wielkosc_okna=0;
            druga_wielkosc=1;
            cv::createTrackbar("Typ elementu strukturalnego", "Gradient", &wielkosc_okna, 2, &MojeObrazki::Gradient_Morfologiczny_callback, this );
            cv::createTrackbar("Wartość", "Gradient", &druga_wielkosc, 12, &MojeObrazki::Gradient_Morfologiczny_callback, this);

            Gradient_Morfologiczny();
        }
}

void MojeObrazki::Erozja()
{

    cv::Mat kernel = cv::getStructuringElement(wielkosc_okna, cv::Size(2*druga_wielkosc + 1, 2*druga_wielkosc+1), cv::Point(druga_wielkosc, druga_wielkosc));
    cv::erode(zrodlo, wynik, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
    cv::imshow("Erozja", wynik);

}

void MojeObrazki::Dylatacja()
{
    cv::Mat kernel = cv::getStructuringElement(wielkosc_okna, cv::Size(2*druga_wielkosc + 1, 2*druga_wielkosc+1), cv::Point(druga_wielkosc, druga_wielkosc));
    cv::dilate(zrodlo, wynik, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
    cv::imshow("Dylatacja", wynik);
}

void MojeObrazki::Otwarcie()
{
    cv::Mat kernel = cv::getStructuringElement(wielkosc_okna, cv::Size(2*druga_wielkosc + 1, 2*druga_wielkosc+1), cv::Point(druga_wielkosc, druga_wielkosc));
    cv::Mat zmienna_morfo;

    cv::dilate(zrodlo, zmienna_morfo, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
    cv::erode(zmienna_morfo, wynik, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);

    cv::imshow("Otwarcie", wynik);
}

void MojeObrazki::Zamkniecie()
{
    cv::Mat kernel = cv::getStructuringElement(wielkosc_okna, cv::Size(2*druga_wielkosc + 1, 2*druga_wielkosc+1), cv::Point(druga_wielkosc, druga_wielkosc));
    cv::Mat zmienna_morfo;

    cv::erode(zrodlo, zmienna_morfo, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
    cv::dilate(zmienna_morfo, wynik, kernel, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);

    cv::imshow("Zamkniecie", wynik);
}

void MojeObrazki::Gradient_Morfologiczny(){

        cv::Mat kernel = cv::getStructuringElement(wielkosc_okna, cv::Size(2*druga_wielkosc + 1, 2*druga_wielkosc+1), cv::Point(druga_wielkosc, druga_wielkosc));
        cv::Mat zmienna_morfo;
        cv::Mat zmienna_morfo2;
        cv::erode(zrodlo, zmienna_morfo, kernel);//, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
        cv::dilate(zrodlo, zmienna_morfo2, kernel);//, cv::Point(-1,-1), 1, cv::BORDER_CONSTANT);
        cv::subtract(zmienna_morfo2, zmienna_morfo, wynik );
         cv::imshow("Gradient", cv::abs(wynik));


}
