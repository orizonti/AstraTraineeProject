/********************************************************************************
** Form generated from reading UI file 'mainblockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINBLOCKWINDOW_H
#define UI_MAINBLOCKWINDOW_H

#include <DigitalClock.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainBlockWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *butRotateCalibration;
    QPushButton *ButSetPowerSupplyCommutator;
    DigitalClock *currentDateTimeLCD;
    QPushButton *butStartMoveCircle;
    QPushButton *butResetAll;
    QPushButton *ButTurnToWorkMode;
    QLabel *label;
    QPushButton *ButSetAdjustMode;
    QLabel *label_2;
    QPushButton *butSaveEnginePos;
    QPushButton *butLoadPreference;

    void setupUi(QWidget *MainBlockWindow)
    {
        if (MainBlockWindow->objectName().isEmpty())
            MainBlockWindow->setObjectName(QString::fromUtf8("MainBlockWindow"));
        MainBlockWindow->resize(233, 373);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        MainBlockWindow->setFont(font);
        MainBlockWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
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
        gridLayout = new QGridLayout(MainBlockWindow);
        gridLayout->setSpacing(4);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(4, 4, 4, 4);
        butRotateCalibration = new QPushButton(MainBlockWindow);
        butRotateCalibration->setObjectName(QString::fromUtf8("butRotateCalibration"));
        butRotateCalibration->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(116, 116, 116, 255), stop:1 rgba(255, 255, 255, 255))\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.452726, y1:1, x2:0.408677, y2:0.102, stop:0 rgba(93, 93, 93, 251), stop:1 rgba(63, 63, 63, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(butRotateCalibration, 9, 0, 1, 2);

        ButSetPowerSupplyCommutator = new QPushButton(MainBlockWindow);
        ButSetPowerSupplyCommutator->setObjectName(QString::fromUtf8("ButSetPowerSupplyCommutator"));
        ButSetPowerSupplyCommutator->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        ButSetPowerSupplyCommutator->setCheckable(true);

        gridLayout->addWidget(ButSetPowerSupplyCommutator, 12, 0, 1, 2);

        currentDateTimeLCD = new DigitalClock(MainBlockWindow);
        currentDateTimeLCD->setObjectName(QString::fromUtf8("currentDateTimeLCD"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(currentDateTimeLCD->sizePolicy().hasHeightForWidth());
        currentDateTimeLCD->setSizePolicy(sizePolicy);
        currentDateTimeLCD->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"\n"
"	background-color: rgb(94, 94, 94);\n"
"}"));
        currentDateTimeLCD->setDigitCount(19);

        gridLayout->addWidget(currentDateTimeLCD, 0, 0, 1, 2);

        butStartMoveCircle = new QPushButton(MainBlockWindow);
        butStartMoveCircle->setObjectName(QString::fromUtf8("butStartMoveCircle"));
        butStartMoveCircle->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        butStartMoveCircle->setCheckable(true);

        gridLayout->addWidget(butStartMoveCircle, 6, 0, 1, 2);

        butResetAll = new QPushButton(MainBlockWindow);
        butResetAll->setObjectName(QString::fromUtf8("butResetAll"));
        butResetAll->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(116, 116, 116, 255), stop:1 rgba(255, 255, 255, 255))\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.452726, y1:1, x2:0.408677, y2:0.102, stop:0 rgba(93, 93, 93, 251), stop:1 rgba(63, 63, 63, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(butResetAll, 7, 0, 1, 2);

        ButTurnToWorkMode = new QPushButton(MainBlockWindow);
        ButTurnToWorkMode->setObjectName(QString::fromUtf8("ButTurnToWorkMode"));
        ButTurnToWorkMode->setFont(font);
        ButTurnToWorkMode->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        ButTurnToWorkMode->setCheckable(true);

        gridLayout->addWidget(ButTurnToWorkMode, 4, 0, 1, 2);

        label = new QLabel(MainBlockWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(300, 200));
        label->setPixmap(QPixmap(QString::fromUtf8("D:/\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\270/\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \320\261\320\273\320\276\320\2723.png")));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 2, 0, 2, 2);

        ButSetAdjustMode = new QPushButton(MainBlockWindow);
        ButSetAdjustMode->setObjectName(QString::fromUtf8("ButSetAdjustMode"));
        ButSetAdjustMode->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        ButSetAdjustMode->setCheckable(true);
        ButSetAdjustMode->setChecked(true);

        gridLayout->addWidget(ButSetAdjustMode, 11, 0, 1, 2);

        label_2 = new QLabel(MainBlockWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        butSaveEnginePos = new QPushButton(MainBlockWindow);
        butSaveEnginePos->setObjectName(QString::fromUtf8("butSaveEnginePos"));
        butSaveEnginePos->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(116, 116, 116, 255), stop:1 rgba(255, 255, 255, 255))\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.452726, y1:1, x2:0.408677, y2:0.102, stop:0 rgba(93, 93, 93, 251), stop:1 rgba(63, 63, 63, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(butSaveEnginePos, 10, 0, 1, 2);

        butLoadPreference = new QPushButton(MainBlockWindow);
        butLoadPreference->setObjectName(QString::fromUtf8("butLoadPreference"));
        butLoadPreference->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(116, 116, 116, 255), stop:1 rgba(255, 255, 255, 255))\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.452726, y1:1, x2:0.408677, y2:0.102, stop:0 rgba(93, 93, 93, 251), stop:1 rgba(63, 63, 63, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(butLoadPreference, 8, 0, 1, 2);


        retranslateUi(MainBlockWindow);

        QMetaObject::connectSlotsByName(MainBlockWindow);
    } // setupUi

    void retranslateUi(QWidget *MainBlockWindow)
    {
        MainBlockWindow->setWindowTitle(QCoreApplication::translate("MainBlockWindow", "MainBlockWindow", nullptr));
        butRotateCalibration->setText(QCoreApplication::translate("MainBlockWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260 \320\262\321\200\320\260\321\211\320\265\320\275\320\270\321\217", nullptr));
        ButSetPowerSupplyCommutator->setText(QCoreApplication::translate("MainBlockWindow", "\320\237\320\270\321\202\320\260\320\275\320\270\320\265 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", nullptr));
        butStartMoveCircle->setText(QCoreApplication::translate("MainBlockWindow", "\320\232\321\200\321\203\320\263", nullptr));
        butResetAll->setText(QCoreApplication::translate("MainBlockWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        ButTurnToWorkMode->setText(QCoreApplication::translate("MainBlockWindow", "\320\237\321\203\321\201\320\272", nullptr));
        label->setText(QString());
        ButSetAdjustMode->setText(QCoreApplication::translate("MainBlockWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\277\320\265\321\200\320\265\320\272\321\200\320\265\321\201\321\202\320\270\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainBlockWindow", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\273\320\265\321\200", nullptr));
        butSaveEnginePos->setText(QCoreApplication::translate("MainBlockWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", nullptr));
        butLoadPreference->setText(QCoreApplication::translate("MainBlockWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainBlockWindow: public Ui_MainBlockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINBLOCKWINDOW_H
