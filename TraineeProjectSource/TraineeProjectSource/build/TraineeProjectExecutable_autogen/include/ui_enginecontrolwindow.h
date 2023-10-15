/********************************************************************************
** Form generated from reading UI file 'enginecontrolwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGINECONTROLWINDOW_H
#define UI_ENGINECONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EngineControlWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_20;
    QGridLayout *gridLayout_8;
    QLabel *label_54;
    QPushButton *ButMovEng1Up;
    QLineEdit *lineXPos1;
    QSlider *SliderEngine1X;
    QSlider *SliderEngine1Y;
    QLineEdit *lineYPos1;
    QPushButton *ButMovEng1Right;
    QPushButton *ButEngineToNull1;
    QLabel *label_25;
    QLabel *LabelCurrentYPos1;
    QLabel *LabelCurrentXPos1;
    QLabel *label_24;
    QLabel *label_55;
    QPushButton *ButMovEng1Left;
    QPushButton *ButMovEng1Down;
    QLabel *label_2;
    QCheckBox *checkWorkBlock;
    QLabel *LabelNumberChannel;
    QHBoxLayout *horizontalLayout;
    QPushButton *butTurnOffHorizontal;
    QPushButton *butTurnOffVertical;
    QLineEdit *lineEditCommandDelay;
    QLabel *label;
    QLabel *label_3;

    void setupUi(QWidget *EngineControlWindow)
    {
        if (EngineControlWindow->objectName().isEmpty())
            EngineControlWindow->setObjectName(QString::fromUtf8("EngineControlWindow"));
        EngineControlWindow->resize(784, 186);
        EngineControlWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"\n"
"	font: 14pt \"Sans Serif\";\n"
"}"));
        gridLayout = new QGridLayout(EngineControlWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_20 = new QGroupBox(EngineControlWindow);
        groupBox_20->setObjectName(QString::fromUtf8("groupBox_20"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_20->sizePolicy().hasHeightForWidth());
        groupBox_20->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        groupBox_20->setFont(font);
        groupBox_20->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(126, 125, 112);\n"
"}\n"
"\n"
"QSlider\n"
"{\n"
"background-color: rgb(85, 85, 127);\n"
"border: 2px solid line black;\n"
"}"));
        groupBox_20->setAlignment(Qt::AlignCenter);
        gridLayout_8 = new QGridLayout(groupBox_20);
        gridLayout_8->setSpacing(2);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(2, 2, 2, 2);
        label_54 = new QLabel(groupBox_20);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_54->sizePolicy().hasHeightForWidth());
        label_54->setSizePolicy(sizePolicy1);
        label_54->setMinimumSize(QSize(50, 0));
        label_54->setFont(font);
        label_54->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(67, 136, 101);\n"
"\n"
"}"));
        label_54->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_54, 3, 0, 1, 1);

        ButMovEng1Up = new QPushButton(groupBox_20);
        ButMovEng1Up->setObjectName(QString::fromUtf8("ButMovEng1Up"));
        ButMovEng1Up->setMinimumSize(QSize(60, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainControllerQClass/TrainerPictures/\320\277\321\200\320\260\320\262\320\2761.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButMovEng1Up->setIcon(icon);
        ButMovEng1Up->setIconSize(QSize(40, 20));

        gridLayout_8->addWidget(ButMovEng1Up, 3, 6, 1, 1);

        lineXPos1 = new QLineEdit(groupBox_20);
        lineXPos1->setObjectName(QString::fromUtf8("lineXPos1"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineXPos1->sizePolicy().hasHeightForWidth());
        lineXPos1->setSizePolicy(sizePolicy2);
        lineXPos1->setMinimumSize(QSize(80, 0));
        lineXPos1->setMaximumSize(QSize(100, 16777215));
        lineXPos1->setFont(font);

        gridLayout_8->addWidget(lineXPos1, 2, 1, 1, 1);

        SliderEngine1X = new QSlider(groupBox_20);
        SliderEngine1X->setObjectName(QString::fromUtf8("SliderEngine1X"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SliderEngine1X->sizePolicy().hasHeightForWidth());
        SliderEngine1X->setSizePolicy(sizePolicy3);
        SliderEngine1X->setMinimum(-120000);
        SliderEngine1X->setMaximum(120000);
        SliderEngine1X->setOrientation(Qt::Horizontal);
        SliderEngine1X->setTickPosition(QSlider::TicksAbove);
        SliderEngine1X->setTickInterval(20000);

        gridLayout_8->addWidget(SliderEngine1X, 2, 5, 1, 1);

        SliderEngine1Y = new QSlider(groupBox_20);
        SliderEngine1Y->setObjectName(QString::fromUtf8("SliderEngine1Y"));
        sizePolicy3.setHeightForWidth(SliderEngine1Y->sizePolicy().hasHeightForWidth());
        SliderEngine1Y->setSizePolicy(sizePolicy3);
        SliderEngine1Y->setMinimum(-120000);
        SliderEngine1Y->setMaximum(120000);
        SliderEngine1Y->setOrientation(Qt::Horizontal);
        SliderEngine1Y->setTickPosition(QSlider::TicksAbove);
        SliderEngine1Y->setTickInterval(20000);

        gridLayout_8->addWidget(SliderEngine1Y, 3, 5, 1, 1);

        lineYPos1 = new QLineEdit(groupBox_20);
        lineYPos1->setObjectName(QString::fromUtf8("lineYPos1"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineYPos1->sizePolicy().hasHeightForWidth());
        lineYPos1->setSizePolicy(sizePolicy4);
        lineYPos1->setMinimumSize(QSize(80, 0));
        lineYPos1->setMaximumSize(QSize(100, 16777215));
        lineYPos1->setFont(font);

        gridLayout_8->addWidget(lineYPos1, 3, 1, 1, 1);

        ButMovEng1Right = new QPushButton(groupBox_20);
        ButMovEng1Right->setObjectName(QString::fromUtf8("ButMovEng1Right"));
        ButMovEng1Right->setMinimumSize(QSize(60, 0));
        ButMovEng1Right->setIcon(icon);
        ButMovEng1Right->setIconSize(QSize(40, 20));

        gridLayout_8->addWidget(ButMovEng1Right, 2, 6, 1, 1);

        ButEngineToNull1 = new QPushButton(groupBox_20);
        ButEngineToNull1->setObjectName(QString::fromUtf8("ButEngineToNull1"));
        ButEngineToNull1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"}"));

        gridLayout_8->addWidget(ButEngineToNull1, 4, 5, 1, 1);

        label_25 = new QLabel(groupBox_20);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMinimumSize(QSize(80, 0));
        label_25->setFont(font);
        label_25->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(170, 170, 0);\n"
"\n"
"}"));

        gridLayout_8->addWidget(label_25, 1, 2, 1, 1);

        LabelCurrentYPos1 = new QLabel(groupBox_20);
        LabelCurrentYPos1->setObjectName(QString::fromUtf8("LabelCurrentYPos1"));
        LabelCurrentYPos1->setMinimumSize(QSize(160, 0));
        LabelCurrentYPos1->setFont(font);
        LabelCurrentYPos1->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(186, 186, 186);\n"
"\n"
"}"));
        LabelCurrentYPos1->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(LabelCurrentYPos1, 3, 2, 1, 1);

        LabelCurrentXPos1 = new QLabel(groupBox_20);
        LabelCurrentXPos1->setObjectName(QString::fromUtf8("LabelCurrentXPos1"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(LabelCurrentXPos1->sizePolicy().hasHeightForWidth());
        LabelCurrentXPos1->setSizePolicy(sizePolicy5);
        LabelCurrentXPos1->setMinimumSize(QSize(160, 0));
        LabelCurrentXPos1->setFont(font);
        LabelCurrentXPos1->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(186, 186, 186);\n"
"\n"
"}"));
        LabelCurrentXPos1->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(LabelCurrentXPos1, 2, 2, 1, 1);

        label_24 = new QLabel(groupBox_20);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font);
        label_24->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(170, 170, 0);\n"
"\n"
"}"));

        gridLayout_8->addWidget(label_24, 1, 1, 1, 1);

        label_55 = new QLabel(groupBox_20);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        sizePolicy5.setHeightForWidth(label_55->sizePolicy().hasHeightForWidth());
        label_55->setSizePolicy(sizePolicy5);
        label_55->setMinimumSize(QSize(50, 0));
        label_55->setFont(font);
        label_55->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(67, 136, 101);\n"
"\n"
"}"));
        label_55->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_55, 2, 0, 1, 1);

        ButMovEng1Left = new QPushButton(groupBox_20);
        ButMovEng1Left->setObjectName(QString::fromUtf8("ButMovEng1Left"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(ButMovEng1Left->sizePolicy().hasHeightForWidth());
        ButMovEng1Left->setSizePolicy(sizePolicy6);
        ButMovEng1Left->setMinimumSize(QSize(60, 0));
        ButMovEng1Left->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MainControllerQClass/TrainerPictures/\320\273\320\265\320\262\320\2761.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButMovEng1Left->setIcon(icon1);
        ButMovEng1Left->setIconSize(QSize(40, 20));

        gridLayout_8->addWidget(ButMovEng1Left, 2, 4, 1, 1);

        ButMovEng1Down = new QPushButton(groupBox_20);
        ButMovEng1Down->setObjectName(QString::fromUtf8("ButMovEng1Down"));
        ButMovEng1Down->setMinimumSize(QSize(60, 0));
        ButMovEng1Down->setIcon(icon1);
        ButMovEng1Down->setIconSize(QSize(40, 20));

        gridLayout_8->addWidget(ButMovEng1Down, 3, 4, 1, 1);

        label_2 = new QLabel(groupBox_20);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout_8->addWidget(label_2, 1, 0, 1, 1);

        checkWorkBlock = new QCheckBox(groupBox_20);
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

        gridLayout_8->addWidget(checkWorkBlock, 1, 6, 1, 1);

        LabelNumberChannel = new QLabel(groupBox_20);
        LabelNumberChannel->setObjectName(QString::fromUtf8("LabelNumberChannel"));
        LabelNumberChannel->setFont(font);
        LabelNumberChannel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(LabelNumberChannel, 4, 6, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        butTurnOffHorizontal = new QPushButton(groupBox_20);
        butTurnOffHorizontal->setObjectName(QString::fromUtf8("butTurnOffHorizontal"));
        butTurnOffHorizontal->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	\n"
"	background-color: rgb(161, 36, 25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"		background-color: rgb(61, 121, 0);\n"
"	\n"
"}"));
        butTurnOffHorizontal->setCheckable(true);
        butTurnOffHorizontal->setChecked(true);

        horizontalLayout->addWidget(butTurnOffHorizontal);

        butTurnOffVertical = new QPushButton(groupBox_20);
        butTurnOffVertical->setObjectName(QString::fromUtf8("butTurnOffVertical"));
        butTurnOffVertical->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"		background-color: rgb(126, 0, 0);\n"
"\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"	\n"
"	background-color: rgb(61, 121, 0);\n"
"}"));
        butTurnOffVertical->setCheckable(true);
        butTurnOffVertical->setChecked(true);

        horizontalLayout->addWidget(butTurnOffVertical);


        gridLayout_8->addLayout(horizontalLayout, 1, 5, 1, 1);

        lineEditCommandDelay = new QLineEdit(groupBox_20);
        lineEditCommandDelay->setObjectName(QString::fromUtf8("lineEditCommandDelay"));

        gridLayout_8->addWidget(lineEditCommandDelay, 4, 1, 1, 1);

        label = new QLabel(groupBox_20);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_8->addWidget(label, 4, 0, 1, 1);

        label_3 = new QLabel(groupBox_20);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_8->addWidget(label_3, 4, 2, 1, 1);


        gridLayout->addWidget(groupBox_20, 1, 0, 1, 1);


        retranslateUi(EngineControlWindow);

        QMetaObject::connectSlotsByName(EngineControlWindow);
    } // setupUi

    void retranslateUi(QWidget *EngineControlWindow)
    {
        EngineControlWindow->setWindowTitle(QCoreApplication::translate("EngineControlWindow", "EngineControlWindow", nullptr));
        groupBox_20->setTitle(QString());
        label_54->setText(QCoreApplication::translate("EngineControlWindow", "Y", nullptr));
        ButMovEng1Up->setText(QString());
        lineXPos1->setText(QCoreApplication::translate("EngineControlWindow", "0.00", nullptr));
        lineYPos1->setText(QCoreApplication::translate("EngineControlWindow", "0.00", nullptr));
        ButMovEng1Right->setText(QString());
        ButEngineToNull1->setText(QCoreApplication::translate("EngineControlWindow", "\320\222 \320\275\321\203\320\273\321\214", nullptr));
        label_25->setText(QCoreApplication::translate("EngineControlWindow", "\321\201 \320\277\321\200\320\270\320\261\320\276\321\200\320\260", nullptr));
        LabelCurrentYPos1->setText(QCoreApplication::translate("EngineControlWindow", "0.00", nullptr));
        LabelCurrentXPos1->setText(QCoreApplication::translate("EngineControlWindow", "0.00", nullptr));
        label_24->setText(QCoreApplication::translate("EngineControlWindow", "\321\201\320\265\320\272\321\203\320\275\320\264\321\213", nullptr));
        label_55->setText(QCoreApplication::translate("EngineControlWindow", "X", nullptr));
        ButMovEng1Left->setText(QString());
        ButMovEng1Down->setText(QString());
        label_2->setText(QCoreApplication::translate("EngineControlWindow", "\320\237\321\200\320\270\320\262\320\276\320\264", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("EngineControlWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));
        LabelNumberChannel->setText(QCoreApplication::translate("EngineControlWindow", "1", nullptr));
        butTurnOffHorizontal->setText(QCoreApplication::translate("EngineControlWindow", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214", nullptr));
        butTurnOffVertical->setText(QCoreApplication::translate("EngineControlWindow", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214", nullptr));
        lineEditCommandDelay->setText(QCoreApplication::translate("EngineControlWindow", "50", nullptr));
        label->setText(QCoreApplication::translate("EngineControlWindow", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("EngineControlWindow", "\320\274\320\272\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EngineControlWindow: public Ui_EngineControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGINECONTROLWINDOW_H
