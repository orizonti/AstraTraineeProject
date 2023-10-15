/********************************************************************************
** Form generated from reading UI file 'windowsinussource.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSINUSSOURCE_H
#define UI_WINDOWSINUSSOURCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowSinusSource
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QCheckBox *checkWorkBlock;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QSpinBox *SpinAmp;
    QDoubleSpinBox *SpinFreq;
    QLabel *label_3;
    QCheckBox *checkNoize;
    QLabel *label_4;
    QDoubleSpinBox *spinNoizeAmplitude;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkChannel1;
    QCheckBox *checkChannel2;

    void setupUi(QWidget *WindowSinusSource)
    {
        if (WindowSinusSource->objectName().isEmpty())
            WindowSinusSource->setObjectName(QString::fromUtf8("WindowSinusSource"));
        WindowSinusSource->resize(265, 307);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowSinusSource->sizePolicy().hasHeightForWidth());
        WindowSinusSource->setSizePolicy(sizePolicy);
        WindowSinusSource->setStyleSheet(QString::fromUtf8("QWidget\n"
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
"QDoubleSpinBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(227, 227, 227);\n"
"}\n"
"\n"
"QSpinBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(227, 227, 227);\n"
"}\n"
"\n"
""));
        gridLayout_2 = new QGridLayout(WindowSinusSource);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(WindowSinusSource);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(250, 70));
        label_2->setPixmap(QPixmap(QString::fromUtf8("D:/\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\270/Sinus3.png")));
        label_2->setScaledContents(true);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        checkWorkBlock = new QCheckBox(WindowSinusSource);
        checkWorkBlock->setObjectName(QString::fromUtf8("checkWorkBlock"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkWorkBlock->sizePolicy().hasHeightForWidth());
        checkWorkBlock->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
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

        gridLayout_2->addWidget(checkWorkBlock, 4, 0, 1, 1);

        groupBox = new QGroupBox(WindowSinusSource);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_5, 1, 1, 1, 1);

        SpinAmp = new QSpinBox(groupBox);
        SpinAmp->setObjectName(QString::fromUtf8("SpinAmp"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(SpinAmp->sizePolicy().hasHeightForWidth());
        SpinAmp->setSizePolicy(sizePolicy4);
        SpinAmp->setMinimumSize(QSize(70, 40));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        SpinAmp->setFont(font1);
        SpinAmp->setStyleSheet(QString::fromUtf8("QSpinBox\n"
"{\n"
"	font: 75 18pt \"PT Sans\";\n"
"}"));
        SpinAmp->setAlignment(Qt::AlignCenter);
        SpinAmp->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        SpinAmp->setMinimum(0);
        SpinAmp->setMaximum(400);
        SpinAmp->setSingleStep(5);
        SpinAmp->setValue(30);

        gridLayout->addWidget(SpinAmp, 3, 2, 1, 1);

        SpinFreq = new QDoubleSpinBox(groupBox);
        SpinFreq->setObjectName(QString::fromUtf8("SpinFreq"));
        sizePolicy3.setHeightForWidth(SpinFreq->sizePolicy().hasHeightForWidth());
        SpinFreq->setSizePolicy(sizePolicy3);
        SpinFreq->setFont(font1);
        SpinFreq->setStyleSheet(QString::fromUtf8("QDoubleSpinBox\n"
"{\n"
"	font: 75 18pt \"PT Sans\";\n"
"}"));
        SpinFreq->setAlignment(Qt::AlignCenter);
        SpinFreq->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        SpinFreq->setMinimum(0.200000000000000);
        SpinFreq->setMaximum(4.000000000000000);
        SpinFreq->setSingleStep(0.200000000000000);
        SpinFreq->setValue(1.600000000000000);

        gridLayout->addWidget(SpinFreq, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        checkNoize = new QCheckBox(groupBox);
        checkNoize->setObjectName(QString::fromUtf8("checkNoize"));
        checkNoize->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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

        gridLayout->addWidget(checkNoize, 0, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        spinNoizeAmplitude = new QDoubleSpinBox(groupBox);
        spinNoizeAmplitude->setObjectName(QString::fromUtf8("spinNoizeAmplitude"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(spinNoizeAmplitude->sizePolicy().hasHeightForWidth());
        spinNoizeAmplitude->setSizePolicy(sizePolicy6);
        spinNoizeAmplitude->setFont(font1);
        spinNoizeAmplitude->setStyleSheet(QString::fromUtf8("QDoubleSpinBox\n"
"{\n"
"	font: 75 18pt \"PT Sans\";\n"
"}"));
        spinNoizeAmplitude->setAlignment(Qt::AlignCenter);
        spinNoizeAmplitude->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinNoizeAmplitude->setMinimum(0.500000000000000);
        spinNoizeAmplitude->setMaximum(12.000000000000000);
        spinNoizeAmplitude->setSingleStep(0.500000000000000);
        spinNoizeAmplitude->setValue(1.600000000000000);

        gridLayout->addWidget(spinNoizeAmplitude, 1, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);

        label = new QLabel(WindowSinusSource);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy7);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        checkChannel1 = new QCheckBox(WindowSinusSource);
        checkChannel1->setObjectName(QString::fromUtf8("checkChannel1"));
        sizePolicy2.setHeightForWidth(checkChannel1->sizePolicy().hasHeightForWidth());
        checkChannel1->setSizePolicy(sizePolicy2);
        checkChannel1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkChannel1->setChecked(true);

        horizontalLayout->addWidget(checkChannel1);

        checkChannel2 = new QCheckBox(WindowSinusSource);
        checkChannel2->setObjectName(QString::fromUtf8("checkChannel2"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(checkChannel2->sizePolicy().hasHeightForWidth());
        checkChannel2->setSizePolicy(sizePolicy8);
        checkChannel2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
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
        checkChannel2->setChecked(true);

        horizontalLayout->addWidget(checkChannel2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(WindowSinusSource);

        QMetaObject::connectSlotsByName(WindowSinusSource);
    } // setupUi

    void retranslateUi(QWidget *WindowSinusSource)
    {
        WindowSinusSource->setWindowTitle(QCoreApplication::translate("WindowSinusSource", "WindowSinusSource", nullptr));
        label_2->setText(QString());
        checkWorkBlock->setText(QCoreApplication::translate("WindowSinusSource", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
        groupBox->setTitle(QString());
        label_5->setText(QCoreApplication::translate("WindowSinusSource", "\320\224\320\270\321\201\320\277\320\265\321\200\321\201\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("WindowSinusSource", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260", nullptr));
        checkNoize->setText(QCoreApplication::translate("WindowSinusSource", "\320\250\321\203\320\274", nullptr));
        label_4->setText(QCoreApplication::translate("WindowSinusSource", "\320\220\320\274\320\277\320\273\320\270\321\202\321\203\320\264\320\260", nullptr));
        label->setText(QCoreApplication::translate("WindowSinusSource", "\320\223\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200 \321\201\320\270\320\275\321\203\321\201\320\260", nullptr));
        checkChannel1->setText(QCoreApplication::translate("WindowSinusSource", "\320\232\320\260\320\275\320\260\320\2731", nullptr));
        checkChannel2->setText(QCoreApplication::translate("WindowSinusSource", "\320\232\320\260\320\275\320\260\320\2732", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowSinusSource: public Ui_WindowSinusSource {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSINUSSOURCE_H
