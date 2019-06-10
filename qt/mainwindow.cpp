#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hitable *world;
    world = some_scene();
    int nx=1920;
    int ny=1080;
    resize(nx,ny);
    int ns=20;
    float factor = 1.2;
    vec3 lookfrom(-20/factor,8.0/factor,6.0/factor);
    vec3 lookat(0,0,0);
    float dist_to_focus = 12;
    float aperture = 0.06;
    camera cam(lookfrom, lookat, vec3(0,1,0),20, float(nx)/float(ny),aperture, dist_to_focus);
    s = new Scene(world, &cam,nx,ny,ns);


    //s->render_ppm("picqt.ppm");
    s->render_qimg();
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    //qDebug()<<"Paint event";
    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawImage(0,0,s->qimg);
    painter.end();
}

void MainWindow::update()
{
    paintEvent(nullptr);
}
