/********************************************************************************
** Form generated from reading UI file 'camerawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWINDOW_H
#define UI_CAMERAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *labelFrameRateROI;
    QLabel *label_2;
    QLabel *labelFrameRate;
    QCheckBox *checkWorkBlock;

    void setupUi(QWidget *CameraWindow)
    {
        if (CameraWindow->objectName().isEmpty())
            CameraWindow->setObjectName(QString::fromUtf8("CameraWindow"));
        CameraWindow->resize(185, 138);
        CameraWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"	font: 14pt \"Sans Serif\";\n"
"}\n"
"QLineEdit\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(227, 227, 227);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"border: 0px solid line black;\n"
"	\n"
"	background-color: rgb(148, 134, 115);\n"
"\n"
"}"));
        gridLayout = new QGridLayout(CameraWindow);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        label = new QLabel(CameraWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(130, 60));
        label->setPixmap(QPixmap(QString::fromUtf8("D:/\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\270/\320\232\320\260\320\274\320\265\321\200\320\260.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        labelFrameRateROI = new QLabel(CameraWindow);
        labelFrameRateROI->setObjectName(QString::fromUtf8("labelFrameRateROI"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        labelFrameRateROI->setFont(font);
        labelFrameRateROI->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(211, 211, 158);\n"
"}"));

        gridLayout->addWidget(labelFrameRateROI, 3, 0, 1, 1);

        label_2 = new QLabel(CameraWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        labelFrameRate = new QLabel(CameraWindow);
        labelFrameRate->setObjectName(QString::fromUtf8("labelFrameRate"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelFrameRate->sizePolicy().hasHeightForWidth());
        labelFrameRate->setSizePolicy(sizePolicy1);
        labelFrameRate->setMaximumSize(QSize(16777215, 16777213));
        labelFrameRate->setFont(font);
        labelFrameRate->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(211, 211, 158);\n"
"}"));

        gridLayout->addWidget(labelFrameRate, 2, 0, 1, 1);

        checkWorkBlock = new QCheckBox(CameraWindow);
        checkWorkBlock->setObjectName(QString::fromUtf8("checkWorkBlock"));
        checkWorkBlock->setFont(font);
        checkWorkBlock->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(208, 0, 0);\n"
"}\n"
"\n"
"QCheckBox::checked\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));

        gridLayout->addWidget(checkWorkBlock, 4, 0, 1, 1);


        retranslateUi(CameraWindow);

        QMetaObject::connectSlotsByName(CameraWindow);
    } // setupUi

    void retranslateUi(QWidget *CameraWindow)
    {
        CameraWindow->setWindowTitle(QCoreApplication::translate("CameraWindow", "CameraWindow", nullptr));
        label->setText(QString());
        labelFrameRateROI->setText(QCoreApplication::translate("CameraWindow", " \320\241\321\202\321\200\320\276\320\261  -  100 \320\274\321\201", nullptr));
        label_2->setText(QCoreApplication::translate("CameraWindow", "\320\232\320\260\320\274\320\265\321\200\320\260", nullptr));
        labelFrameRate->setText(QCoreApplication::translate("CameraWindow", "\320\232\320\260\320\264\321\200\321\213  - 100  \320\274\321\201", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("CameraWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraWindow: public Ui_CameraWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWINDOW_H
