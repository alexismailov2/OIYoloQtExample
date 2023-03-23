#include "OIYoloWindow.h"

#include <QtWidgets>

#include <OIYolo/V8.hpp>

#include <vector>
#include <sstream>

OIYoloWindow::OIYoloWindow(bool isFullscreen, QWidget *parent)
    : QMainWindow(parent)
    , _isFullscreen{isFullscreen}
{
    auto widget = new QWidget;
    setCentralWidget(widget);

    auto selectModelLabel = new QLabel();
    auto selectModelButton = new QPushButton(tr("Select NCNN model(*.param)"));
    connect(selectModelButton, &QPushButton::clicked, [=]() {
        QString file = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,
                                                     tr("Open model file"),
                                                     QDir::currentPath()));
        if (!file.isEmpty())
        {
            selectModelLabel->setText(file);
        }
    });

    auto selectWeightsLabel = new QLabel();
    auto selectWeightsButton = new QPushButton(tr("Select NCNN weights(*.bin)"));
    connect(selectWeightsButton, &QPushButton::clicked, [=]() {
        QString file = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,
                                                     tr("Open weights file"),
                                                     QDir::currentPath()));
        if (!file.isEmpty())
        {
            selectWeightsLabel->setText(file);
        }
    });

    auto selectClassesLabel = new QLabel();
    auto selectClassesButton = new QPushButton(tr("Select NCNN weights(*.classes)"));
    connect(selectClassesButton, &QPushButton::clicked, [=]() {
        QString file = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,
                                                                             tr("Open classes file"),
                                                                             QDir::currentPath()));
        if (!file.isEmpty())
        {
            selectClassesLabel->setText(file);
        }
    });

    auto selectPictureLabel = new QLabel();
    auto selectPictureButton = new QPushButton(tr("Select picture(*.jpg"));
    auto pictureLabel = new QLabel();
    connect(selectPictureButton, &QPushButton::clicked, [=]() {
        QString file = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Open picture file"), QDir::currentPath()));
        if (!file.isEmpty())
        {
            selectPictureLabel->setText(file);
            pictureLabel->setPixmap(QPixmap::fromImage(QImage(file)));
        }
    });
    auto runYoloButton = new QPushButton(tr("Run detection"));
    connect(runYoloButton, &QPushButton::clicked, [=]() {
        auto yoloV8 = OIYolo::V8(selectWeightsLabel->text().toStdString(),
                                 selectWeightsLabel->text().toStdString(),
                                 selectClassesLabel->text().toStdString(),
                                 OIYolo::Size{640, 640},
                                 0.3,
                                 0.3);
        auto predictions = yoloV8.performPrediction(
                (const char*)pictureLabel->pixmap()->toImage().bits(),
                pictureLabel->pixmap()->width(),
                pictureLabel->pixmap()->height(),
                [](std::string const&) { return true; },
                true);
        if (!predictions.empty())
        {
            std::stringstream ss;
            for (auto const& item : predictions)
            {
                ss << "class: " << item.className;
                ss << ", x: " << item.boundingBox.x;
                ss << ", y: " << item.boundingBox.y;
                ss << ", width: " << item.boundingBox.width;
                ss << ", height: " << item.boundingBox.height;
                ss << ", confidence: " << item.confidence << std::endl;
            }
            QMessageBox::about(this, tr("OIYolo detected"), QString::fromStdString(ss.str()));
        }
    });

    auto layout = new QVBoxLayout;
    layout->addWidget(selectModelButton);
    layout->addWidget(selectModelLabel);
    layout->addWidget(selectWeightsButton);
    layout->addWidget(selectWeightsLabel);
    layout->addWidget(selectClassesButton);
    layout->addWidget(selectClassesLabel);
    layout->addWidget(selectPictureButton);
    layout->addWidget(selectPictureLabel);
    layout->addWidget(pictureLabel);
    layout->addWidget(runYoloButton);

    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("OIYolo tool"));
    //setMinimumSize(160, 160);
}

void OIYoloWindow::createActions()
{
    preferencesAct = new QAction(tr("&Preferences..."), this);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, [this]() {
        QMessageBox::about(this, tr("About OIYolo"), tr("The <b>OIYolo</b> Demonstrates usage of OIYolo helpers."));
    });

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void OIYoloWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
