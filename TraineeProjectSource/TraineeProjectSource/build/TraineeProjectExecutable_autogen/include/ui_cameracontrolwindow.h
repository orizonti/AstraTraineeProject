/********************************************************************************
** Form generated from reading UI file 'cameracontrolwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONTROLWINDOW_H
#define UI_CAMERACONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraControlWindow
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *tmkuControlBox;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_15;
    QPushButton *ButSetROI;
    QSpinBox *SpinWidth3;
    QLabel *label_23;
    QSpinBox *SpinWidth2;
    QLabel *label_30;
    QSpinBox *SpinX3;
    QLabel *label_32;
    QSpinBox *SpinY1;
    QLabel *label_19;
    QLabel *label_31;
    QLabel *label_33;
    QLabel *label_22;
    QSpinBox *SpinX4;
    QSpinBox *SpinX2;
    QSpinBox *SpinWidth1;
    QSpinBox *SpinWidth4;
    QSpinBox *SpinX1;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QPushButton *ButSetParamToDevice;
    QSpinBox *SpinExposeTimeMs;
    QLabel *label_18;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *SpinAvarageBackground;
    QPushButton *ButAutoExpose;

    void setupUi(QWidget *CameraControlWindow)
    {
        if (CameraControlWindow->objectName().isEmpty())
            CameraControlWindow->setObjectName(QString::fromUtf8("CameraControlWindow"));
        CameraControlWindow->resize(699, 216);
        CameraControlWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"\n"
"	font: 14pt \"Sans Serif\";\n"
"}"));
        gridLayout_3 = new QGridLayout(CameraControlWindow);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        tmkuControlBox = new QGroupBox(CameraControlWindow);
        tmkuControlBox->setObjectName(QString::fromUtf8("tmkuControlBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tmkuControlBox->sizePolicy().hasHeightForWidth());
        tmkuControlBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        tmkuControlBox->setFont(font);
        tmkuControlBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(126, 125, 112);\n"
"}"));
        tmkuControlBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(tmkuControlBox);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 21, 2, 2);
        groupBox_4 = new QGroupBox(tmkuControlBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        groupBox_4->setMinimumSize(QSize(0, 0));
        groupBox_4->setFont(font);
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(170, 170, 127);\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"}"));
        gridLayout_15 = new QGridLayout(groupBox_4);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setHorizontalSpacing(7);
        gridLayout_15->setVerticalSpacing(1);
        gridLayout_15->setContentsMargins(3, 3, 3, 3);
        ButSetROI = new QPushButton(groupBox_4);
        ButSetROI->setObjectName(QString::fromUtf8("ButSetROI"));
        ButSetROI->setFont(font);
        ButSetROI->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"}"));

        gridLayout_15->addWidget(ButSetROI, 10, 0, 1, 4);

        SpinWidth3 = new QSpinBox(groupBox_4);
        SpinWidth3->setObjectName(QString::fromUtf8("SpinWidth3"));
        SpinWidth3->setFont(font);
        SpinWidth3->setMaximum(256);
        SpinWidth3->setValue(256);

        gridLayout_15->addWidget(SpinWidth3, 8, 3, 1, 1);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font);

        gridLayout_15->addWidget(label_23, 0, 3, 1, 1);

        SpinWidth2 = new QSpinBox(groupBox_4);
        SpinWidth2->setObjectName(QString::fromUtf8("SpinWidth2"));
        SpinWidth2->setFont(font);
        SpinWidth2->setMaximum(256);
        SpinWidth2->setValue(256);

        gridLayout_15->addWidget(SpinWidth2, 7, 3, 1, 1);

        label_30 = new QLabel(groupBox_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font);
        label_30->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(255, 214, 110);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_15->addWidget(label_30, 4, 0, 1, 1);

        SpinX3 = new QSpinBox(groupBox_4);
        SpinX3->setObjectName(QString::fromUtf8("SpinX3"));
        SpinX3->setFont(font);
        SpinX3->setMaximum(1700);
        SpinX3->setSingleStep(8);
        SpinX3->setValue(1152);

        gridLayout_15->addWidget(SpinX3, 8, 1, 1, 1);

        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy1.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy1);
        label_32->setFont(font);

        gridLayout_15->addWidget(label_32, 0, 2, 1, 1);

        SpinY1 = new QSpinBox(groupBox_4);
        SpinY1->setObjectName(QString::fromUtf8("SpinY1"));
        SpinY1->setFont(font);
        SpinY1->setMaximum(255);
        SpinY1->setValue(128);

        gridLayout_15->addWidget(SpinY1, 4, 2, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font);
        label_19->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(255, 214, 110);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_15->addWidget(label_19, 9, 0, 1, 1);

        label_31 = new QLabel(groupBox_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setFont(font);

        gridLayout_15->addWidget(label_31, 0, 1, 1, 1);

        label_33 = new QLabel(groupBox_4);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setFont(font);
        label_33->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(255, 214, 110);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_15->addWidget(label_33, 8, 0, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font);
        label_22->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(255, 214, 110);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_15->addWidget(label_22, 7, 0, 1, 1);

        SpinX4 = new QSpinBox(groupBox_4);
        SpinX4->setObjectName(QString::fromUtf8("SpinX4"));
        SpinX4->setFont(font);
        SpinX4->setMaximum(1700);
        SpinX4->setSingleStep(8);
        SpinX4->setValue(1664);

        gridLayout_15->addWidget(SpinX4, 9, 1, 1, 1);

        SpinX2 = new QSpinBox(groupBox_4);
        SpinX2->setObjectName(QString::fromUtf8("SpinX2"));
        SpinX2->setFont(font);
        SpinX2->setMaximum(1700);
        SpinX2->setSingleStep(8);
        SpinX2->setValue(640);

        gridLayout_15->addWidget(SpinX2, 7, 1, 1, 1);

        SpinWidth1 = new QSpinBox(groupBox_4);
        SpinWidth1->setObjectName(QString::fromUtf8("SpinWidth1"));
        SpinWidth1->setFont(font);
        SpinWidth1->setMaximum(256);
        SpinWidth1->setValue(256);

        gridLayout_15->addWidget(SpinWidth1, 4, 3, 1, 1);

        SpinWidth4 = new QSpinBox(groupBox_4);
        SpinWidth4->setObjectName(QString::fromUtf8("SpinWidth4"));
        SpinWidth4->setFont(font);
        SpinWidth4->setMaximum(256);
        SpinWidth4->setValue(256);

        gridLayout_15->addWidget(SpinWidth4, 9, 3, 1, 1);

        SpinX1 = new QSpinBox(groupBox_4);
        SpinX1->setObjectName(QString::fromUtf8("SpinX1"));
        SpinX1->setFont(font);
        SpinX1->setMaximum(1700);
        SpinX1->setSingleStep(8);
        SpinX1->setValue(128);

        gridLayout_15->addWidget(SpinX1, 4, 1, 1, 1);


        gridLayout->addWidget(groupBox_4, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(tmkuControlBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        groupBox_3->setMinimumSize(QSize(0, 0));
        groupBox_3->setFont(font);
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(90, 181, 134);\n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(4);
        gridLayout_2->setVerticalSpacing(2);
        gridLayout_2->setContentsMargins(8, 7, 8, 6);
        ButSetParamToDevice = new QPushButton(groupBox_3);
        ButSetParamToDevice->setObjectName(QString::fromUtf8("ButSetParamToDevice"));
        ButSetParamToDevice->setFont(font);
        ButSetParamToDevice->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(ButSetParamToDevice, 3, 0, 1, 1);

        SpinExposeTimeMs = new QSpinBox(groupBox_3);
        SpinExposeTimeMs->setObjectName(QString::fromUtf8("SpinExposeTimeMs"));
        sizePolicy2.setHeightForWidth(SpinExposeTimeMs->sizePolicy().hasHeightForWidth());
        SpinExposeTimeMs->setSizePolicy(sizePolicy2);
        SpinExposeTimeMs->setFont(font);
        SpinExposeTimeMs->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"}"));
        SpinExposeTimeMs->setMaximum(4000);
        SpinExposeTimeMs->setSingleStep(100);
        SpinExposeTimeMs->setValue(400);

        gridLayout_2->addWidget(SpinExposeTimeMs, 1, 1, 1, 1);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font);
        label_18->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(133, 200, 0);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_2->addWidget(label_18, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(255, 170, 0);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(170, 170, 0);\n"
"border: 1px solid line black;\n"
"}"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        SpinAvarageBackground = new QSpinBox(groupBox_3);
        SpinAvarageBackground->setObjectName(QString::fromUtf8("SpinAvarageBackground"));
        sizePolicy2.setHeightForWidth(SpinAvarageBackground->sizePolicy().hasHeightForWidth());
        SpinAvarageBackground->setSizePolicy(sizePolicy2);
        SpinAvarageBackground->setFont(font);
        SpinAvarageBackground->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"}"));
        SpinAvarageBackground->setMaximum(1000);
        SpinAvarageBackground->setSingleStep(5);
        SpinAvarageBackground->setValue(100);

        gridLayout_2->addWidget(SpinAvarageBackground, 2, 1, 1, 1);

        ButAutoExpose = new QPushButton(groupBox_3);
        ButAutoExpose->setObjectName(QString::fromUtf8("ButAutoExpose"));
        sizePolicy2.setHeightForWidth(ButAutoExpose->sizePolicy().hasHeightForWidth());
        ButAutoExpose->setSizePolicy(sizePolicy2);
        ButAutoExpose->setFont(font);
        ButAutoExpose->setCheckable(true);
        ButAutoExpose->setChecked(true);

        gridLayout_2->addWidget(ButAutoExpose, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 0, 1, 1);


        gridLayout_3->addWidget(tmkuControlBox, 0, 0, 1, 1);


        retranslateUi(CameraControlWindow);

        QMetaObject::connectSlotsByName(CameraControlWindow);
    } // setupUi

    void retranslateUi(QWidget *CameraControlWindow)
    {
        CameraControlWindow->setWindowTitle(QCoreApplication::translate("CameraControlWindow", "CameraControlWindow", nullptr));
        tmkuControlBox->setTitle(QCoreApplication::translate("CameraControlWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\232\320\260\320\274\320\265\321\200\320\260\320\274\320\270", nullptr));
        groupBox_4->setTitle(QString());
        ButSetROI->setText(QCoreApplication::translate("CameraControlWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_23->setText(QCoreApplication::translate("CameraControlWindow", "\320\250\320\270\321\200\320\270\320\275\320\260", nullptr));
        label_30->setText(QCoreApplication::translate("CameraControlWindow", "\320\236\320\272\320\275\320\276 1", nullptr));
        label_32->setText(QCoreApplication::translate("CameraControlWindow", "Y", nullptr));
        label_19->setText(QCoreApplication::translate("CameraControlWindow", "\320\236\320\272\320\275\320\276 4", nullptr));
        label_31->setText(QCoreApplication::translate("CameraControlWindow", "X", nullptr));
        label_33->setText(QCoreApplication::translate("CameraControlWindow", "\320\236\320\272\320\275\320\276 3", nullptr));
        label_22->setText(QCoreApplication::translate("CameraControlWindow", "\320\236\320\272\320\275\320\276 2", nullptr));
        groupBox_3->setTitle(QString());
        ButSetParamToDevice->setText(QCoreApplication::translate("CameraControlWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_18->setText(QCoreApplication::translate("CameraControlWindow", "\320\222\321\200\320\265\320\274\321\217 \321\215\320\272\321\201\320\277\320\276\320\267\320\270\321\206\320\270\320\270 \320\274\320\272\321\201", nullptr));
        label_6->setText(QCoreApplication::translate("CameraControlWindow", "\320\241\321\200\320\265\320\264\320\275\320\270\320\271 \321\204\320\276\320\275", nullptr));
        label_7->setText(QCoreApplication::translate("CameraControlWindow", "\320\220\320\262\321\202\320\276\321\215\320\272\321\201\320\277\320\276\320\267\320\270\321\206\320\270\321\217", nullptr));
        ButAutoExpose->setText(QCoreApplication::translate("CameraControlWindow", "\320\222\320\272\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraControlWindow: public Ui_CameraControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONTROLWINDOW_H
