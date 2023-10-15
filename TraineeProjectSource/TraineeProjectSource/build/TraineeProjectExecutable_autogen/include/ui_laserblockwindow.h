/********************************************************************************
** Form generated from reading UI file 'laserblockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LASERBLOCKWINDOW_H
#define UI_LASERBLOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LaserBlockWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label_6;
    QPushButton *ButTurnToWorkPointer;
    QPushButton *ButTurnToWorkLaser3;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *ButTurnToWorkLaser2;
    QPushButton *ButTurnToWorkLaser1;
    QCheckBox *checkWorkBlock;
    QLabel *label_2;
    QLabel *label;
    QPushButton *butStartAllLasers;

    void setupUi(QWidget *LaserBlockWindow)
    {
        if (LaserBlockWindow->objectName().isEmpty())
            LaserBlockWindow->setObjectName(QString::fromUtf8("LaserBlockWindow"));
        LaserBlockWindow->resize(170, 278);
        LaserBlockWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
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
        gridLayout = new QGridLayout(LaserBlockWindow);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        label_6 = new QLabel(LaserBlockWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_6, 8, 0, 1, 1);

        ButTurnToWorkPointer = new QPushButton(LaserBlockWindow);
        ButTurnToWorkPointer->setObjectName(QString::fromUtf8("ButTurnToWorkPointer"));
        ButTurnToWorkPointer->setFont(font);
        ButTurnToWorkPointer->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(170, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"\n"
" \n"
"	background-color: rgb(85, 170, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));
        ButTurnToWorkPointer->setCheckable(true);

        gridLayout->addWidget(ButTurnToWorkPointer, 8, 1, 1, 1);

        ButTurnToWorkLaser3 = new QPushButton(LaserBlockWindow);
        ButTurnToWorkLaser3->setObjectName(QString::fromUtf8("ButTurnToWorkLaser3"));
        ButTurnToWorkLaser3->setFont(font);
        ButTurnToWorkLaser3->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(170, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"\n"
" \n"
"	background-color: rgb(85, 170, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));
        ButTurnToWorkLaser3->setCheckable(true);

        gridLayout->addWidget(ButTurnToWorkLaser3, 7, 1, 1, 1);

        label_5 = new QLabel(LaserBlockWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        label_3 = new QLabel(LaserBlockWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        label_4 = new QLabel(LaserBlockWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_4, 3, 0, 2, 1);

        ButTurnToWorkLaser2 = new QPushButton(LaserBlockWindow);
        ButTurnToWorkLaser2->setObjectName(QString::fromUtf8("ButTurnToWorkLaser2"));
        ButTurnToWorkLaser2->setFont(font);
        ButTurnToWorkLaser2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(170, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"\n"
" \n"
"	background-color: rgb(85, 170, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));
        ButTurnToWorkLaser2->setCheckable(true);

        gridLayout->addWidget(ButTurnToWorkLaser2, 5, 1, 1, 1);

        ButTurnToWorkLaser1 = new QPushButton(LaserBlockWindow);
        ButTurnToWorkLaser1->setObjectName(QString::fromUtf8("ButTurnToWorkLaser1"));
        ButTurnToWorkLaser1->setFont(font);
        ButTurnToWorkLaser1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(170, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"\n"
" \n"
"	background-color: rgb(85, 170, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));
        ButTurnToWorkLaser1->setCheckable(true);

        gridLayout->addWidget(ButTurnToWorkLaser1, 3, 1, 2, 1);

        checkWorkBlock = new QCheckBox(LaserBlockWindow);
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

        gridLayout->addWidget(checkWorkBlock, 1, 0, 1, 2);

        label_2 = new QLabel(LaserBlockWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        label = new QLabel(LaserBlockWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(240, 200));
        label->setPixmap(QPixmap(QString::fromUtf8("D:/\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\270/\320\233\320\260\320\267\320\265\321\200.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 2, 0, 1, 2);

        butStartAllLasers = new QPushButton(LaserBlockWindow);
        butStartAllLasers->setObjectName(QString::fromUtf8("butStartAllLasers"));
        butStartAllLasers->setFont(font);
        butStartAllLasers->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(170, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"\n"
" \n"
"	background-color: rgb(85, 170, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));
        butStartAllLasers->setCheckable(true);

        gridLayout->addWidget(butStartAllLasers, 9, 0, 1, 2);


        retranslateUi(LaserBlockWindow);

        QMetaObject::connectSlotsByName(LaserBlockWindow);
    } // setupUi

    void retranslateUi(QWidget *LaserBlockWindow)
    {
        LaserBlockWindow->setWindowTitle(QCoreApplication::translate("LaserBlockWindow", "LaserBlockWindow", nullptr));
        label_6->setText(QCoreApplication::translate("LaserBlockWindow", "\320\234\320\260\321\200\320\272\320\265\321\200", nullptr));
        ButTurnToWorkPointer->setText(QCoreApplication::translate("LaserBlockWindow", "\320\237\321\203\321\201\320\272", nullptr));
        ButTurnToWorkLaser3->setText(QCoreApplication::translate("LaserBlockWindow", "\320\237\321\203\321\201\320\272", nullptr));
        label_5->setText(QCoreApplication::translate("LaserBlockWindow", "\320\233\320\260\320\267\320\265\321\200 3", nullptr));
        label_3->setText(QCoreApplication::translate("LaserBlockWindow", "\320\233\320\260\320\267\320\265\321\200 2", nullptr));
        label_4->setText(QCoreApplication::translate("LaserBlockWindow", "\320\233\320\260\320\267\320\265\321\200 1", nullptr));
        ButTurnToWorkLaser2->setText(QCoreApplication::translate("LaserBlockWindow", "\320\237\321\203\321\201\320\272", nullptr));
        ButTurnToWorkLaser1->setText(QCoreApplication::translate("LaserBlockWindow", "\320\237\321\203\321\201\320\272", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("LaserBlockWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("LaserBlockWindow", "\320\233\320\260\320\267\320\265\321\200\320\275\321\213\320\271 \320\261\320\273\320\276\320\272", nullptr));
        label->setText(QString());
        butStartAllLasers->setText(QCoreApplication::translate("LaserBlockWindow", "\320\237\321\203\321\201\320\272 \320\262\321\201\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LaserBlockWindow: public Ui_LaserBlockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LASERBLOCKWINDOW_H
