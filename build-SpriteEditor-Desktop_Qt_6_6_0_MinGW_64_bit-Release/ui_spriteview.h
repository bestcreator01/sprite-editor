/********************************************************************************
** Form generated from reading UI file 'spriteview.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITEVIEW_H
#define UI_SPRITEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteView
{
public:
    QWidget *centralwidget;
    QLabel *pixelCanvas;
    QPushButton *penButton;
    QPushButton *eraserButton;
    QPushButton *sprayButton;
    QSlider *fpsSlider;
    QPushButton *addFrame;
    QPushButton *deleteFrame;
    QLabel *fpsLabel;
    QListWidget *listWidget;
    QPushButton *colorRed;
    QPushButton *colorOrange;
    QPushButton *colorYellow;
    QPushButton *colorGreen;
    QPushButton *newFile;
    QPushButton *saveFile;
    QPushButton *loadFile;
    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *colorPurple;
    QPushButton *colorWhite;
    QPushButton *colorBlack;
    QPushButton *colorBlue;
    QLabel *previewLabel;
    QPushButton *colorButton;
    QLabel *coordinates;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SpriteView)
    {
        if (SpriteView->objectName().isEmpty())
            SpriteView->setObjectName("SpriteView");
        SpriteView->resize(1100, 800);
        SpriteView->setMouseTracking(false);
        SpriteView->setAutoFillBackground(false);
        SpriteView->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(SpriteView);
        centralwidget->setObjectName("centralwidget");
        pixelCanvas = new QLabel(centralwidget);
        pixelCanvas->setObjectName("pixelCanvas");
        pixelCanvas->setGeometry(QRect(180, 30, 601, 601));
        pixelCanvas->setMouseTracking(true);
        penButton = new QPushButton(centralwidget);
        penButton->setObjectName("penButton");
        penButton->setGeometry(QRect(70, 80, 61, 61));
        penButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        penButton->setIconSize(QSize(64, 64));
        eraserButton = new QPushButton(centralwidget);
        eraserButton->setObjectName("eraserButton");
        eraserButton->setGeometry(QRect(70, 140, 61, 61));
        eraserButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        eraserButton->setIconSize(QSize(60, 60));
        sprayButton = new QPushButton(centralwidget);
        sprayButton->setObjectName("sprayButton");
        sprayButton->setGeometry(QRect(70, 200, 61, 61));
        sprayButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        sprayButton->setIconSize(QSize(58, 58));
        fpsSlider = new QSlider(centralwidget);
        fpsSlider->setObjectName("fpsSlider");
        fpsSlider->setGeometry(QRect(860, 270, 181, 25));
        fpsSlider->setMinimum(0);
        fpsSlider->setMaximum(30);
        fpsSlider->setOrientation(Qt::Horizontal);
        addFrame = new QPushButton(centralwidget);
        addFrame->setObjectName("addFrame");
        addFrame->setGeometry(QRect(870, 660, 81, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tempus Sans ITC")});
        addFrame->setFont(font);
        addFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        deleteFrame = new QPushButton(centralwidget);
        deleteFrame->setObjectName("deleteFrame");
        deleteFrame->setGeometry(QRect(960, 660, 81, 61));
        deleteFrame->setFont(font);
        deleteFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        fpsLabel = new QLabel(centralwidget);
        fpsLabel->setObjectName("fpsLabel");
        fpsLabel->setGeometry(QRect(820, 270, 41, 20));
        fpsLabel->setFont(font);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(870, 300, 171, 351));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        colorRed = new QPushButton(centralwidget);
        colorRed->setObjectName("colorRed");
        colorRed->setGeometry(QRect(80, 280, 21, 21));
        colorOrange = new QPushButton(centralwidget);
        colorOrange->setObjectName("colorOrange");
        colorOrange->setGeometry(QRect(110, 280, 21, 21));
        colorYellow = new QPushButton(centralwidget);
        colorYellow->setObjectName("colorYellow");
        colorYellow->setGeometry(QRect(80, 310, 21, 21));
        colorGreen = new QPushButton(centralwidget);
        colorGreen->setObjectName("colorGreen");
        colorGreen->setGeometry(QRect(110, 310, 21, 21));
        newFile = new QPushButton(centralwidget);
        newFile->setObjectName("newFile");
        newFile->setGeometry(QRect(600, 660, 61, 61));
        newFile->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        newFile->setIconSize(QSize(50, 50));
        saveFile = new QPushButton(centralwidget);
        saveFile->setObjectName("saveFile");
        saveFile->setGeometry(QRect(660, 660, 61, 61));
        saveFile->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        saveFile->setIconSize(QSize(50, 50));
        loadFile = new QPushButton(centralwidget);
        loadFile->setObjectName("loadFile");
        loadFile->setGeometry(QRect(720, 660, 61, 61));
        loadFile->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        loadFile->setIconSize(QSize(50, 50));
        undoButton = new QPushButton(centralwidget);
        undoButton->setObjectName("undoButton");
        undoButton->setGeometry(QRect(50, 30, 51, 31));
        undoButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        undoButton->setIconSize(QSize(20, 20));
        redoButton = new QPushButton(centralwidget);
        redoButton->setObjectName("redoButton");
        redoButton->setGeometry(QRect(100, 30, 51, 31));
        redoButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        redoButton->setIconSize(QSize(20, 20));
        colorPurple = new QPushButton(centralwidget);
        colorPurple->setObjectName("colorPurple");
        colorPurple->setGeometry(QRect(110, 340, 21, 21));
        colorWhite = new QPushButton(centralwidget);
        colorWhite->setObjectName("colorWhite");
        colorWhite->setGeometry(QRect(110, 370, 21, 21));
        colorBlack = new QPushButton(centralwidget);
        colorBlack->setObjectName("colorBlack");
        colorBlack->setGeometry(QRect(80, 370, 21, 21));
        colorBlue = new QPushButton(centralwidget);
        colorBlue->setObjectName("colorBlue");
        colorBlue->setGeometry(QRect(80, 340, 21, 21));
        previewLabel = new QLabel(centralwidget);
        previewLabel->setObjectName("previewLabel");
        previewLabel->setGeometry(QRect(870, 60, 171, 171));
        colorButton = new QPushButton(centralwidget);
        colorButton->setObjectName("colorButton");
        colorButton->setGeometry(QRect(70, 410, 61, 61));
        colorButton->setFont(font);
        colorButton->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        colorButton->setIconSize(QSize(50, 50));
        coordinates = new QLabel(centralwidget);
        coordinates->setObjectName("coordinates");
        coordinates->setGeometry(QRect(180, 660, 51, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Tempus Sans ITC")});
        font1.setPointSize(11);
        coordinates->setFont(font1);
        coordinates->setStyleSheet(QString::fromUtf8("background-color: rgb(254, 255, 206);"));
        SpriteView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpriteView);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1100, 21));
        SpriteView->setMenuBar(menubar);
        statusbar = new QStatusBar(SpriteView);
        statusbar->setObjectName("statusbar");
        SpriteView->setStatusBar(statusbar);

        retranslateUi(SpriteView);

        QMetaObject::connectSlotsByName(SpriteView);
    } // setupUi

    void retranslateUi(QMainWindow *SpriteView)
    {
        SpriteView->setWindowTitle(QCoreApplication::translate("SpriteView", "SpriteView", nullptr));
        pixelCanvas->setText(QString());
        penButton->setText(QString());
        eraserButton->setText(QString());
        sprayButton->setText(QString());
        addFrame->setText(QCoreApplication::translate("SpriteView", "Add Frame", nullptr));
        deleteFrame->setText(QCoreApplication::translate("SpriteView", "Delete Frame", nullptr));
        fpsLabel->setText(QCoreApplication::translate("SpriteView", "0 FPS", nullptr));
        colorRed->setText(QString());
        colorOrange->setText(QString());
        colorYellow->setText(QString());
        colorGreen->setText(QString());
        newFile->setText(QString());
        saveFile->setText(QString());
        loadFile->setText(QString());
        undoButton->setText(QString());
        redoButton->setText(QString());
        colorPurple->setText(QString());
        colorWhite->setText(QString());
        colorBlack->setText(QString());
        colorBlue->setText(QString());
        previewLabel->setText(QString());
        colorButton->setText(QString());
        coordinates->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SpriteView: public Ui_SpriteView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITEVIEW_H
