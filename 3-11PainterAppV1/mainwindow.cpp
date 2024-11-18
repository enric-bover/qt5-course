#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = new PaintCanvas(this);
    setCentralWidget(canvas);

    //Pen width
    QLabel * penWidthLabel = new QLabel("Pen Width", this);
    QSpinBox * penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setValue(2);
    penWidthSpinBox->setRange(1,15);

    //Pen Color
    QLabel * penColorLabel = new QLabel("Pen Color", this);
    penColorButton = new QPushButton(this);

    // Fill color
    QLabel * fillColorLabel = new QLabel("Fill Color", this);
    fillColorButton = new QPushButton(this);

    // Fill
    fillCheckBox = new QCheckBox("Fill Shape", this);

    // Tool Buttons
    QPushButton * rectButton = new QPushButton(this);
    rectButton->setIcon(QIcon(":/images/rectangle.png"));

    QPushButton * penButton = new QPushButton(this);
    penButton->setIcon(QIcon(":/images/pen.png"));

    QPushButton * ellipseButton = new QPushButton(this);
    ellipseButton->setIcon(QIcon(":/images/circle.png"));

    QPushButton * eraseButton = new QPushButton(this);
    eraseButton->setIcon(QIcon(":/images/eraser.png"));

    QObject::connect(penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::penWidthChanged);
    QObject::connect(penColorButton, &QPushButton::clicked, this, &MainWindow::changePenColor);
    QObject::connect(fillColorButton, &QPushButton::clicked, this, &MainWindow::changeFillColor);
    QObject::connect(fillCheckBox, &QCheckBox::clicked, this, &MainWindow::changeFillProperty);

    ui->mainToolBar->addWidget(penWidthLabel);
    ui->mainToolBar->addWidget(penWidthSpinBox);
    ui->mainToolBar->addWidget(penColorLabel);
    ui->mainToolBar->addWidget(penColorButton);
    ui->mainToolBar->addWidget(fillColorLabel);
    ui->mainToolBar->addWidget(fillColorButton);
    ui->mainToolBar->addWidget(fillCheckBox);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(penButton);
    ui->mainToolBar->addWidget(rectButton);
    ui->mainToolBar->addWidget(ellipseButton);
    ui->mainToolBar->addWidget(eraseButton);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::penWidthChanged(int width)
{

}

void MainWindow::changePenColor()
{

}

void MainWindow::changeFillColor()
{

}

void MainWindow::changeFillProperty()
{

}

