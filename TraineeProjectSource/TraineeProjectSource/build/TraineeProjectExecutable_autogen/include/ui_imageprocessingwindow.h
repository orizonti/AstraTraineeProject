/********************************************************************************
** Form generated from reading UI file 'imageprocessingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSINGWINDOW_H
#define UI_IMAGEPROCESSINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingWindow
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkWorkBlock1;
    QLabel *label_2;
    QCheckBox *checkWorkBlock3;
    QLabel *label;
    QCheckBox *checkWorkBlock4;
    QCheckBox *checkWorkBlock2;
    QLabel *labelPeriodProcess;
    QLabel *labelPeriodReceive;

    void setupUi(QWidget *ImageProcessingWindow)
    {
        if (ImageProcessingWindow->objectName().isEmpty())
            ImageProcessingWindow->setObjectName(QString::fromUtf8("ImageProcessingWindow"));
        ImageProcessingWindow->resize(222, 293);
        ImageProcessingWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
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
"	background-color: rgb(170, 170, 127);\n"
"\n"
"}"));
        gridLayout = new QGridLayout(ImageProcessingWindow);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        checkWorkBlock1 = new QCheckBox(ImageProcessingWindow);
        checkWorkBlock1->setObjectName(QString::fromUtf8("checkWorkBlock1"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        checkWorkBlock1->setFont(font);
        checkWorkBlock1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkWorkBlock1->setChecked(false);

        gridLayout->addWidget(checkWorkBlock1, 2, 0, 1, 2);

        label_2 = new QLabel(ImageProcessingWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        checkWorkBlock3 = new QCheckBox(ImageProcessingWindow);
        checkWorkBlock3->setObjectName(QString::fromUtf8("checkWorkBlock3"));
        checkWorkBlock3->setFont(font);
        checkWorkBlock3->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkWorkBlock3->setChecked(false);

        gridLayout->addWidget(checkWorkBlock3, 5, 0, 1, 2);

        label = new QLabel(ImageProcessingWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(100, 80));
        label->setPixmap(QPixmap(QString::fromUtf8("D:/\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\270/ImageProcess.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 1, 0, 1, 2);

        checkWorkBlock4 = new QCheckBox(ImageProcessingWindow);
        checkWorkBlock4->setObjectName(QString::fromUtf8("checkWorkBlock4"));
        checkWorkBlock4->setFont(font);
        checkWorkBlock4->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkWorkBlock4->setChecked(false);

        gridLayout->addWidget(checkWorkBlock4, 6, 0, 1, 2);

        checkWorkBlock2 = new QCheckBox(ImageProcessingWindow);
        checkWorkBlock2->setObjectName(QString::fromUtf8("checkWorkBlock2"));
        checkWorkBlock2->setFont(font);
        checkWorkBlock2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkWorkBlock2->setChecked(false);

        gridLayout->addWidget(checkWorkBlock2, 3, 0, 1, 2);

        labelPeriodProcess = new QLabel(ImageProcessingWindow);
        labelPeriodProcess->setObjectName(QString::fromUtf8("labelPeriodProcess"));
        labelPeriodProcess->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(211, 211, 158);\n"
"}"));

        gridLayout->addWidget(labelPeriodProcess, 8, 0, 1, 2);

        labelPeriodReceive = new QLabel(ImageProcessingWindow);
        labelPeriodReceive->setObjectName(QString::fromUtf8("labelPeriodReceive"));
        labelPeriodReceive->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(211, 211, 158);\n"
"}"));

        gridLayout->addWidget(labelPeriodReceive, 7, 0, 1, 2);


        retranslateUi(ImageProcessingWindow);

        QMetaObject::connectSlotsByName(ImageProcessingWindow);
    } // setupUi

    void retranslateUi(QWidget *ImageProcessingWindow)
    {
        ImageProcessingWindow->setWindowTitle(QCoreApplication::translate("ImageProcessingWindow", "ImageProcessingWindow", nullptr));
        checkWorkBlock1->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        label_2->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\221\320\273\320\276\320\272 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270", nullptr));
        checkWorkBlock3->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\232\320\260\320\275\320\260\320\273 3", nullptr));
        label->setText(QString());
        checkWorkBlock4->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\232\320\260\320\275\320\260\320\273 4", nullptr));
        checkWorkBlock2->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        labelPeriodProcess->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\236\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\260   - 2.0 \320\274\321\201", nullptr));
        labelPeriodReceive->setText(QCoreApplication::translate("ImageProcessingWindow", "\320\237\321\200\320\270\320\265\320\274         - 2.0 \320\274\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingWindow: public Ui_ImageProcessingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSINGWINDOW_H
