/********************************************************************************
** Form generated from reading UI file 'kalmanwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KALMANWINDOW_H
#define UI_KALMANWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KalmanWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineVarE;
    QLabel *label_3;
    QLineEdit *lineVarM;
    QCheckBox *checkWorkBlock;
    QLabel *label_4;
    QLineEdit *lineVarVM;

    void setupUi(QWidget *KalmanWindow)
    {
        if (KalmanWindow->objectName().isEmpty())
            KalmanWindow->setObjectName(QString::fromUtf8("KalmanWindow"));
        KalmanWindow->resize(120, 165);
        KalmanWindow->setMaximumSize(QSize(120, 16777215));
        KalmanWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"}\n"
"QLineEdit\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(227, 227, 227);\n"
"}"));
        gridLayout = new QGridLayout(KalmanWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(KalmanWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label, 0, 0, 1, 3);

        label_2 = new QLabel(KalmanWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineVarE = new QLineEdit(KalmanWindow);
        lineVarE->setObjectName(QString::fromUtf8("lineVarE"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineVarE->sizePolicy().hasHeightForWidth());
        lineVarE->setSizePolicy(sizePolicy1);
        lineVarE->setMaximumSize(QSize(60, 16777215));
        lineVarE->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lineVarE, 1, 1, 1, 2);

        label_3 = new QLabel(KalmanWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineVarM = new QLineEdit(KalmanWindow);
        lineVarM->setObjectName(QString::fromUtf8("lineVarM"));
        sizePolicy1.setHeightForWidth(lineVarM->sizePolicy().hasHeightForWidth());
        lineVarM->setSizePolicy(sizePolicy1);
        lineVarM->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(lineVarM, 2, 1, 1, 2);

        checkWorkBlock = new QCheckBox(KalmanWindow);
        checkWorkBlock->setObjectName(QString::fromUtf8("checkWorkBlock"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkWorkBlock->sizePolicy().hasHeightForWidth());
        checkWorkBlock->setSizePolicy(sizePolicy2);
        checkWorkBlock->setMaximumSize(QSize(100, 16777215));
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
        checkWorkBlock->setChecked(true);

        gridLayout->addWidget(checkWorkBlock, 4, 0, 1, 3);

        label_4 = new QLabel(KalmanWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineVarVM = new QLineEdit(KalmanWindow);
        lineVarVM->setObjectName(QString::fromUtf8("lineVarVM"));
        sizePolicy1.setHeightForWidth(lineVarVM->sizePolicy().hasHeightForWidth());
        lineVarVM->setSizePolicy(sizePolicy1);
        lineVarVM->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(lineVarVM, 3, 1, 1, 2);


        retranslateUi(KalmanWindow);

        QMetaObject::connectSlotsByName(KalmanWindow);
    } // setupUi

    void retranslateUi(QWidget *KalmanWindow)
    {
        KalmanWindow->setWindowTitle(QCoreApplication::translate("KalmanWindow", "KalmanWindow", nullptr));
        label->setText(QCoreApplication::translate("KalmanWindow", "\320\232\320\260\320\273\320\274\320\260\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("KalmanWindow", "\317\203e", nullptr));
        lineVarE->setText(QCoreApplication::translate("KalmanWindow", "0.000", nullptr));
        label_3->setText(QCoreApplication::translate("KalmanWindow", "\317\203n", nullptr));
        lineVarM->setText(QCoreApplication::translate("KalmanWindow", "0.000", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("KalmanWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("KalmanWindow", "\317\203vn", nullptr));
        lineVarVM->setText(QCoreApplication::translate("KalmanWindow", "0.000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KalmanWindow: public Ui_KalmanWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KALMANWINDOW_H
