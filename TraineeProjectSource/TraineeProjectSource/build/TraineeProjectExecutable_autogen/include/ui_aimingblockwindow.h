/********************************************************************************
** Form generated from reading UI file 'aimingblockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIMINGBLOCKWINDOW_H
#define UI_AIMINGBLOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AimingBlockWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *labelPidParam;
    QCheckBox *checkMoveSlowPID;
    QCheckBox *checkMoveFastPID;
    QCheckBox *checkTuningMode;
    QLabel *label;
    QCheckBox *checkWorkBlock;
    QCheckBox *checkBoxFilterOnOff;

    void setupUi(QWidget *AimingBlockWindow)
    {
        if (AimingBlockWindow->objectName().isEmpty())
            AimingBlockWindow->setObjectName(QString::fromUtf8("AimingBlockWindow"));
        AimingBlockWindow->resize(228, 232);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AimingBlockWindow->sizePolicy().hasHeightForWidth());
        AimingBlockWindow->setSizePolicy(sizePolicy);
        AimingBlockWindow->setStyleSheet(QString::fromUtf8("QWidget{border: 2px solid line black; background-color: rgb(148, 134, 115); font: 13pt \"Sans Serif\";}\n"
"QLineEdit{border: 2px solid line black;background-color: rgb(227, 227, 227);}\n"
"QCheckBox{border: 2px solid line black;background-color: rgb(208, 0, 0);}\n"
"QCheckBox::checked{border: 2px solid line black; background-color: rgb(85, 170, 0);}\n"
"QLabel{background-color: rgb(218, 206, 161);}\n"
""));
        gridLayout = new QGridLayout(AimingBlockWindow);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(AimingBlockWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 1px solid line;\n"
"	color: rgb(148, 148, 148);\n"
"}\n"
"\n"
"\n"
"QPushButton\n"
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
"}\n"
""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        labelPidParam = new QLabel(groupBox);
        labelPidParam->setObjectName(QString::fromUtf8("labelPidParam"));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setItalic(false);
        labelPidParam->setFont(font);
        labelPidParam->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(labelPidParam);

        checkMoveSlowPID = new QCheckBox(groupBox);
        checkMoveSlowPID->setObjectName(QString::fromUtf8("checkMoveSlowPID"));
        checkMoveSlowPID->setFont(font);
        checkMoveSlowPID->setChecked(true);
        checkMoveSlowPID->setAutoExclusive(true);

        verticalLayout->addWidget(checkMoveSlowPID);

        checkMoveFastPID = new QCheckBox(groupBox);
        checkMoveFastPID->setObjectName(QString::fromUtf8("checkMoveFastPID"));
        checkMoveFastPID->setFont(font);
        checkMoveFastPID->setAutoExclusive(true);

        verticalLayout->addWidget(checkMoveFastPID);

        checkTuningMode = new QCheckBox(groupBox);
        checkTuningMode->setObjectName(QString::fromUtf8("checkTuningMode"));
        checkTuningMode->setAutoExclusive(true);

        verticalLayout->addWidget(checkTuningMode);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        label = new QLabel(AimingBlockWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        checkWorkBlock = new QCheckBox(AimingBlockWindow);
        checkWorkBlock->setObjectName(QString::fromUtf8("checkWorkBlock"));
        checkWorkBlock->setFont(font);

        gridLayout->addWidget(checkWorkBlock, 3, 0, 1, 1);

        checkBoxFilterOnOff = new QCheckBox(AimingBlockWindow);
        checkBoxFilterOnOff->setObjectName(QString::fromUtf8("checkBoxFilterOnOff"));
        checkBoxFilterOnOff->setChecked(false);

        gridLayout->addWidget(checkBoxFilterOnOff, 2, 0, 1, 1);


        retranslateUi(AimingBlockWindow);

        QMetaObject::connectSlotsByName(AimingBlockWindow);
    } // setupUi

    void retranslateUi(QWidget *AimingBlockWindow)
    {
        AimingBlockWindow->setWindowTitle(QCoreApplication::translate("AimingBlockWindow", "AimingBlockWindow", nullptr));
        groupBox->setTitle(QString());
        labelPidParam->setText(QCoreApplication::translate("AimingBlockWindow", "5.000 0.000 0.000", nullptr));
        checkMoveSlowPID->setText(QCoreApplication::translate("AimingBlockWindow", "\320\234\320\265\320\264\320\273\320\265\320\275\320\275\320\276", nullptr));
        checkMoveFastPID->setText(QCoreApplication::translate("AimingBlockWindow", "\320\221\321\213\321\201\321\202\321\200\320\276", nullptr));
        checkTuningMode->setText(QCoreApplication::translate("AimingBlockWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("AimingBlockWindow", "\320\221\320\273\320\276\320\272 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("AimingBlockWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
        checkBoxFilterOnOff->setText(QCoreApplication::translate("AimingBlockWindow", "\320\244\320\270\320\273\321\214\321\202\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AimingBlockWindow: public Ui_AimingBlockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIMINGBLOCKWINDOW_H
