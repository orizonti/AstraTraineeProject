/********************************************************************************
** Form generated from reading UI file 'PilotLaserWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PILOTLASERWINDOW_H
#define UI_PILOTLASERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PilotLaserWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QListWidget *listCommandOutput;
    QLabel *label_5;
    QLabel *label_6;
    QListWidget *listAnswerInput;
    QLabel *label;
    QLabel *label_7;
    QLabel *labelPilotState2;
    QLabel *labelPilotState;
    QLabel *labelPilotState3;

    void setupUi(QWidget *PilotLaserWindow)
    {
        if (PilotLaserWindow->objectName().isEmpty())
            PilotLaserWindow->setObjectName(QString::fromUtf8("PilotLaserWindow"));
        PilotLaserWindow->resize(517, 628);
        PilotLaserWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(116, 116, 116);\n"
"	\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"background-color: rgb(82, 82, 82);\n"
"color: rgb(213, 199, 165);\n"
"	font: 75 12pt \"Arial\";\n"
"}\n"
"\n"
"QPushButton:checked \n"
"{ \n"
"background-color: green; \n"
"}\n"
"\n"
"QListWidget\n"
"{\n"
"	background-color: rgb(255, 233, 202);\n"
"	font: 12pt \"MS Shell Dlg 2\";\n"
"border:1px solid line black;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"border:1px solid line black;\n"
"	background-color: rgb(166, 134, 96);\n"
"	font: 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"	background-color: rgb(255, 233, 202);\n"
"	font: 12pt \"MS Shell Dlg 2\";\n"
"border:1px solid line black;\n"
"}"));
        gridLayout = new QGridLayout(PilotLaserWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(PilotLaserWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(144, 181, 104);\n"
"}"));

        gridLayout->addWidget(label_2, 2, 0, 1, 4);

        listCommandOutput = new QListWidget(PilotLaserWindow);
        listCommandOutput->setObjectName(QString::fromUtf8("listCommandOutput"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listCommandOutput->sizePolicy().hasHeightForWidth());
        listCommandOutput->setSizePolicy(sizePolicy1);
        listCommandOutput->setMinimumSize(QSize(400, 0));

        gridLayout->addWidget(listCommandOutput, 1, 0, 1, 4);

        label_5 = new QLabel(PilotLaserWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_6 = new QLabel(PilotLaserWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        listAnswerInput = new QListWidget(PilotLaserWindow);
        listAnswerInput->setObjectName(QString::fromUtf8("listAnswerInput"));
        sizePolicy1.setHeightForWidth(listAnswerInput->sizePolicy().hasHeightForWidth());
        listAnswerInput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(listAnswerInput, 3, 0, 1, 4);

        label = new QLabel(PilotLaserWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(144, 181, 104);\n"
"}"));

        gridLayout->addWidget(label, 0, 0, 1, 4);

        label_7 = new QLabel(PilotLaserWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}"));

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        labelPilotState2 = new QLabel(PilotLaserWindow);
        labelPilotState2->setObjectName(QString::fromUtf8("labelPilotState2"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelPilotState2->sizePolicy().hasHeightForWidth());
        labelPilotState2->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(labelPilotState2, 6, 1, 1, 3);

        labelPilotState = new QLabel(PilotLaserWindow);
        labelPilotState->setObjectName(QString::fromUtf8("labelPilotState"));

        gridLayout->addWidget(labelPilotState, 5, 1, 1, 3);

        labelPilotState3 = new QLabel(PilotLaserWindow);
        labelPilotState3->setObjectName(QString::fromUtf8("labelPilotState3"));

        gridLayout->addWidget(labelPilotState3, 7, 1, 1, 3);


        retranslateUi(PilotLaserWindow);

        QMetaObject::connectSlotsByName(PilotLaserWindow);
    } // setupUi

    void retranslateUi(QWidget *PilotLaserWindow)
    {
        PilotLaserWindow->setWindowTitle(QCoreApplication::translate("PilotLaserWindow", "PilotLaserWindow", nullptr));
        label_2->setText(QCoreApplication::translate("PilotLaserWindow", " \320\236\321\202\320\262\320\265\321\202", nullptr));
        label_5->setText(QCoreApplication::translate("PilotLaserWindow", "\320\237\320\270\320\273\320\276\321\2021", nullptr));
        label_6->setText(QCoreApplication::translate("PilotLaserWindow", "\320\237\320\270\320\273\320\276\321\2022", nullptr));
        label->setText(QCoreApplication::translate("PilotLaserWindow", "\320\232\320\276\320\274\320\260\320\275\320\264\320\260", nullptr));
        label_7->setText(QCoreApplication::translate("PilotLaserWindow", "\320\237\320\270\320\273\320\276\321\2023", nullptr));
        labelPilotState2->setText(QCoreApplication::translate("PilotLaserWindow", "\320\235\320\265\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        labelPilotState->setText(QCoreApplication::translate("PilotLaserWindow", "\320\235\320\265\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
        labelPilotState3->setText(QCoreApplication::translate("PilotLaserWindow", "\320\235\320\265\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PilotLaserWindow: public Ui_PilotLaserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PILOTLASERWINDOW_H
