/********************************************************************************
** Form generated from reading UI file 'graphicswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSWINDOW_H
#define UI_GRAPHICSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_GraphicsWindow
{
public:
    QGridLayout *gridLayout_7;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_8;
    QDoubleSpinBox *spinEditMinValDown1;
    QCheckBox *checkXShow1;
    QCheckBox *checkYShow1;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *spinEditMaxValUp1;
    QSpacerItem *verticalSpacer_2;
    QCustomPlot *graphWidget1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QCheckBox *checkShowKalman1;
    QCheckBox *checkShowError1;
    QWidget *page_2;
    QGridLayout *gridLayout_12;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QCheckBox *checkShowKalman2;
    QCheckBox *checkShowError2;
    QCustomPlot *graphWidget2;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_14;
    QDoubleSpinBox *spinEditMinValDown2;
    QCheckBox *checkXShow2;
    QCheckBox *checkYShow2;
    QSpacerItem *verticalSpacer_5;
    QDoubleSpinBox *spinEditMaxValUp2;
    QSpacerItem *verticalSpacer_6;
    QWidget *page_3;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QCheckBox *checkShowError3;
    QCheckBox *checkShowKalman3;
    QCustomPlot *graphWidget3;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_15;
    QDoubleSpinBox *spinEditMinValDown3;
    QCheckBox *checkXShow3;
    QCheckBox *checkYShow3;
    QSpacerItem *verticalSpacer_7;
    QDoubleSpinBox *spinEditMaxValUp3;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout;
    QPushButton *ButGraphChannel1;
    QPushButton *ButGraphChannel2;
    QPushButton *ButGraphChannel3;
    QPushButton *ButStopGraph;

    void setupUi(QWidget *GraphicsWindow)
    {
        if (GraphicsWindow->objectName().isEmpty())
            GraphicsWindow->setObjectName(QString::fromUtf8("GraphicsWindow"));
        GraphicsWindow->resize(700, 550);
        GraphicsWindow->setMinimumSize(QSize(700, 550));
        GraphicsWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 0px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"	font: 14pt \"Sans Serif\";\n"
"}\n"
"\n"
"QDoubleSpinBox\n"
"{\n"
"	background-color: rgb(202, 200, 163);\n"
"	font: 12pt \"Sans Serif\";\n"
"}"));
        gridLayout_7 = new QGridLayout(GraphicsWindow);
        gridLayout_7->setSpacing(2);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(2, 2, 2, 2);
        stackedWidget = new QStackedWidget(GraphicsWindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"	\n"
"\n"
"}\n"
"\n"
"QDoubleSpinBox\n"
"{\n"
"	background-color: rgb(202, 200, 163);\n"
"	font: 75 18pt \"PT Serif\";\n"
"}"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_11 = new QGridLayout(page);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        groupBox->setFont(font);
        groupBox->setToolTipDuration(0);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}"));
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 23, 2, 2);
        groupBox_10 = new QGroupBox(groupBox);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy);
        groupBox_10->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"border: 1px solid line black;\n"
"	background-color: rgb(227, 227, 170);\n"
"}"));
        gridLayout_8 = new QGridLayout(groupBox_10);
        gridLayout_8->setSpacing(2);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(2, 2, 2, 2);
        spinEditMinValDown1 = new QDoubleSpinBox(groupBox_10);
        spinEditMinValDown1->setObjectName(QString::fromUtf8("spinEditMinValDown1"));
        sizePolicy.setHeightForWidth(spinEditMinValDown1->sizePolicy().hasHeightForWidth());
        spinEditMinValDown1->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        spinEditMinValDown1->setFont(font1);
        spinEditMinValDown1->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMinValDown1->setMinimum(-40.000000000000000);
        spinEditMinValDown1->setMaximum(0.000000000000000);
        spinEditMinValDown1->setSingleStep(0.200000000000000);
        spinEditMinValDown1->setValue(-1.200000000000000);

        gridLayout_8->addWidget(spinEditMinValDown1, 4, 0, 1, 1);

        checkXShow1 = new QCheckBox(groupBox_10);
        checkXShow1->setObjectName(QString::fromUtf8("checkXShow1"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkXShow1->sizePolicy().hasHeightForWidth());
        checkXShow1->setSizePolicy(sizePolicy1);
        checkXShow1->setMaximumSize(QSize(16777215, 16777215));
        checkXShow1->setFont(font);
        checkXShow1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(234, 0, 0);\n"
"}"));
        checkXShow1->setChecked(true);

        gridLayout_8->addWidget(checkXShow1, 2, 0, 1, 1);

        checkYShow1 = new QCheckBox(groupBox_10);
        checkYShow1->setObjectName(QString::fromUtf8("checkYShow1"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkYShow1->sizePolicy().hasHeightForWidth());
        checkYShow1->setSizePolicy(sizePolicy2);
        checkYShow1->setMaximumSize(QSize(16777215, 16777215));
        checkYShow1->setFont(font);
        checkYShow1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(0, 170, 255);\n"
"}"));
        checkYShow1->setChecked(true);

        gridLayout_8->addWidget(checkYShow1, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 5, 0, 1, 1);

        spinEditMaxValUp1 = new QDoubleSpinBox(groupBox_10);
        spinEditMaxValUp1->setObjectName(QString::fromUtf8("spinEditMaxValUp1"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(spinEditMaxValUp1->sizePolicy().hasHeightForWidth());
        spinEditMaxValUp1->setSizePolicy(sizePolicy3);
        spinEditMaxValUp1->setFont(font1);
        spinEditMaxValUp1->setStyleSheet(QString::fromUtf8("QDoubleSpinBox\n"
"{\n"
"	background-color: rgb(202, 200, 163);\n"
"	font: 18pt \"Sans Serif\";\n"
"}"));
        spinEditMaxValUp1->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMaxValUp1->setMaximum(40.000000000000000);
        spinEditMaxValUp1->setSingleStep(0.200000000000000);
        spinEditMaxValUp1->setValue(1.200000000000000);

        gridLayout_8->addWidget(spinEditMaxValUp1, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_10, 0, 1, 1, 1);

        graphWidget1 = new QCustomPlot(groupBox);
        graphWidget1->setObjectName(QString::fromUtf8("graphWidget1"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(44);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(graphWidget1->sizePolicy().hasHeightForWidth());
        graphWidget1->setSizePolicy(sizePolicy4);
        graphWidget1->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid rgb(110, 5, 136);\n"
"	background-color: rgb(199, 199, 199);\n"
"}"));

        gridLayout->addWidget(graphWidget1, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 2, 1, 2);
        checkShowKalman1 = new QCheckBox(groupBox_2);
        checkShowKalman1->setObjectName(QString::fromUtf8("checkShowKalman1"));
        checkShowKalman1->setFont(font);
        checkShowKalman1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgba(0, 170, 0, 200);\n"
"}"));

        gridLayout_2->addWidget(checkShowKalman1, 1, 1, 1, 1);

        checkShowError1 = new QCheckBox(groupBox_2);
        checkShowError1->setObjectName(QString::fromUtf8("checkShowError1"));
        sizePolicy3.setHeightForWidth(checkShowError1->sizePolicy().hasHeightForWidth());
        checkShowError1->setSizePolicy(sizePolicy3);
        checkShowError1->setFont(font);
        checkShowError1->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgba(170, 85, 255, 200);\n"
"}"));
        checkShowError1->setIconSize(QSize(30, 30));
        checkShowError1->setChecked(true);
        checkShowError1->setTristate(false);

        gridLayout_2->addWidget(checkShowError1, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);


        gridLayout_11->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_12 = new QGridLayout(page_2);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        groupBox_3 = new QGroupBox(page_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 23, 2, 2);
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"}"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        checkShowKalman2 = new QCheckBox(groupBox_4);
        checkShowKalman2->setObjectName(QString::fromUtf8("checkShowKalman2"));
        checkShowKalman2->setFont(font);
        checkShowKalman2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgba(0, 170, 0, 200);\n"
"}"));

        gridLayout_4->addWidget(checkShowKalman2, 1, 1, 1, 1);

        checkShowError2 = new QCheckBox(groupBox_4);
        checkShowError2->setObjectName(QString::fromUtf8("checkShowError2"));
        checkShowError2->setFont(font);
        checkShowError2->setAutoFillBackground(false);
        checkShowError2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgba(170, 85, 255, 200);\n"
"}"));
        checkShowError2->setIconSize(QSize(30, 30));
        checkShowError2->setChecked(true);
        checkShowError2->setTristate(false);

        gridLayout_4->addWidget(checkShowError2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 1, 0, 1, 1);

        graphWidget2 = new QCustomPlot(groupBox_3);
        graphWidget2->setObjectName(QString::fromUtf8("graphWidget2"));
        sizePolicy4.setHeightForWidth(graphWidget2->sizePolicy().hasHeightForWidth());
        graphWidget2->setSizePolicy(sizePolicy4);
        graphWidget2->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid rgb(110, 5, 136);\n"
"	background-color: rgb(199, 199, 199);\n"
"}"));

        gridLayout_3->addWidget(graphWidget2, 0, 0, 1, 1);

        groupBox_11 = new QGroupBox(groupBox_3);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        sizePolicy.setHeightForWidth(groupBox_11->sizePolicy().hasHeightForWidth());
        groupBox_11->setSizePolicy(sizePolicy);
        groupBox_11->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"border: 1px solid line black;\n"
"	background-color: rgb(227, 227, 170);\n"
"}"));
        gridLayout_14 = new QGridLayout(groupBox_11);
        gridLayout_14->setSpacing(2);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_14->setContentsMargins(2, 2, 2, 2);
        spinEditMinValDown2 = new QDoubleSpinBox(groupBox_11);
        spinEditMinValDown2->setObjectName(QString::fromUtf8("spinEditMinValDown2"));
        spinEditMinValDown2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMinValDown2->setMinimum(-40.000000000000000);
        spinEditMinValDown2->setMaximum(0.000000000000000);
        spinEditMinValDown2->setSingleStep(0.200000000000000);
        spinEditMinValDown2->setValue(-1.200000000000000);

        gridLayout_14->addWidget(spinEditMinValDown2, 4, 0, 1, 1);

        checkXShow2 = new QCheckBox(groupBox_11);
        checkXShow2->setObjectName(QString::fromUtf8("checkXShow2"));
        sizePolicy1.setHeightForWidth(checkXShow2->sizePolicy().hasHeightForWidth());
        checkXShow2->setSizePolicy(sizePolicy1);
        checkXShow2->setMaximumSize(QSize(16777215, 16777215));
        checkXShow2->setFont(font);
        checkXShow2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(234, 0, 0);\n"
"}"));
        checkXShow2->setChecked(true);

        gridLayout_14->addWidget(checkXShow2, 2, 0, 1, 1);

        checkYShow2 = new QCheckBox(groupBox_11);
        checkYShow2->setObjectName(QString::fromUtf8("checkYShow2"));
        sizePolicy2.setHeightForWidth(checkYShow2->sizePolicy().hasHeightForWidth());
        checkYShow2->setSizePolicy(sizePolicy2);
        checkYShow2->setMaximumSize(QSize(16777215, 16777215));
        checkYShow2->setFont(font);
        checkYShow2->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(0, 170, 255);\n"
"}"));
        checkYShow2->setChecked(true);

        gridLayout_14->addWidget(checkYShow2, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_14->addItem(verticalSpacer_5, 5, 0, 1, 1);

        spinEditMaxValUp2 = new QDoubleSpinBox(groupBox_11);
        spinEditMaxValUp2->setObjectName(QString::fromUtf8("spinEditMaxValUp2"));
        sizePolicy3.setHeightForWidth(spinEditMaxValUp2->sizePolicy().hasHeightForWidth());
        spinEditMaxValUp2->setSizePolicy(sizePolicy3);
        spinEditMaxValUp2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMaxValUp2->setMaximum(40.000000000000000);
        spinEditMaxValUp2->setSingleStep(0.200000000000000);
        spinEditMaxValUp2->setValue(1.200000000000000);

        gridLayout_14->addWidget(spinEditMaxValUp2, 1, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_14->addItem(verticalSpacer_6, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_11, 0, 1, 1, 1);


        gridLayout_12->addWidget(groupBox_3, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_13 = new QGridLayout(page_3);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        groupBox_5 = new QGroupBox(page_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font);
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}"));
        groupBox_5->setAlignment(Qt::AlignCenter);
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 23, 2, 2);
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"}"));
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setSpacing(1);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(1, 1, 1, 1);
        checkShowError3 = new QCheckBox(groupBox_6);
        checkShowError3->setObjectName(QString::fromUtf8("checkShowError3"));
        checkShowError3->setFont(font);
        checkShowError3->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgba(170, 85, 255, 200);\n"
"}"));
        checkShowError3->setIconSize(QSize(30, 30));
        checkShowError3->setChecked(true);
        checkShowError3->setTristate(false);

        gridLayout_6->addWidget(checkShowError3, 1, 0, 1, 1);

        checkShowKalman3 = new QCheckBox(groupBox_6);
        checkShowKalman3->setObjectName(QString::fromUtf8("checkShowKalman3"));
        checkShowKalman3->setFont(font);
        checkShowKalman3->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgba(0, 170, 0, 200);\n"
"}"));

        gridLayout_6->addWidget(checkShowKalman3, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_6, 1, 0, 1, 1);

        graphWidget3 = new QCustomPlot(groupBox_5);
        graphWidget3->setObjectName(QString::fromUtf8("graphWidget3"));
        sizePolicy4.setHeightForWidth(graphWidget3->sizePolicy().hasHeightForWidth());
        graphWidget3->setSizePolicy(sizePolicy4);
        graphWidget3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid rgb(110, 5, 136);\n"
"	background-color: rgb(199, 199, 199);\n"
"}"));

        gridLayout_5->addWidget(graphWidget3, 0, 0, 1, 1);

        groupBox_12 = new QGroupBox(groupBox_5);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        sizePolicy.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy);
        groupBox_12->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"border: 1px solid line black;\n"
"	background-color: rgb(227, 227, 170);\n"
"}"));
        gridLayout_15 = new QGridLayout(groupBox_12);
        gridLayout_15->setSpacing(2);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(2, 2, 2, 2);
        spinEditMinValDown3 = new QDoubleSpinBox(groupBox_12);
        spinEditMinValDown3->setObjectName(QString::fromUtf8("spinEditMinValDown3"));
        spinEditMinValDown3->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMinValDown3->setMinimum(-40.000000000000000);
        spinEditMinValDown3->setMaximum(0.000000000000000);
        spinEditMinValDown3->setSingleStep(0.200000000000000);
        spinEditMinValDown3->setValue(-1.200000000000000);

        gridLayout_15->addWidget(spinEditMinValDown3, 4, 0, 1, 1);

        checkXShow3 = new QCheckBox(groupBox_12);
        checkXShow3->setObjectName(QString::fromUtf8("checkXShow3"));
        sizePolicy1.setHeightForWidth(checkXShow3->sizePolicy().hasHeightForWidth());
        checkXShow3->setSizePolicy(sizePolicy1);
        checkXShow3->setMaximumSize(QSize(16777215, 16777215));
        checkXShow3->setFont(font);
        checkXShow3->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(234, 0, 0);\n"
"}"));
        checkXShow3->setChecked(true);

        gridLayout_15->addWidget(checkXShow3, 2, 0, 1, 1);

        checkYShow3 = new QCheckBox(groupBox_12);
        checkYShow3->setObjectName(QString::fromUtf8("checkYShow3"));
        sizePolicy2.setHeightForWidth(checkYShow3->sizePolicy().hasHeightForWidth());
        checkYShow3->setSizePolicy(sizePolicy2);
        checkYShow3->setMaximumSize(QSize(16777215, 16777215));
        checkYShow3->setFont(font);
        checkYShow3->setStyleSheet(QString::fromUtf8("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(0, 170, 255);\n"
"}"));
        checkYShow3->setChecked(true);

        gridLayout_15->addWidget(checkYShow3, 3, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_7, 5, 0, 1, 1);

        spinEditMaxValUp3 = new QDoubleSpinBox(groupBox_12);
        spinEditMaxValUp3->setObjectName(QString::fromUtf8("spinEditMaxValUp3"));
        sizePolicy3.setHeightForWidth(spinEditMaxValUp3->sizePolicy().hasHeightForWidth());
        spinEditMaxValUp3->setSizePolicy(sizePolicy3);
        spinEditMaxValUp3->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinEditMaxValUp3->setMaximum(40.000000000000000);
        spinEditMaxValUp3->setSingleStep(0.200000000000000);
        spinEditMaxValUp3->setValue(1.200000000000000);

        gridLayout_15->addWidget(spinEditMaxValUp3, 1, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_8, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_12, 0, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_5, 0, 0, 1, 1);

        stackedWidget->addWidget(page_3);

        gridLayout_7->addWidget(stackedWidget, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(GraphicsWindow);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        sizePolicy1.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy1);
        groupBox_8->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"\n"
"	\n"
"	background-color: rgb(137, 141, 132);\n"
"}"));
        horizontalLayout = new QHBoxLayout(groupBox_8);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 4, 2);
        ButGraphChannel1 = new QPushButton(groupBox_8);
        ButGraphChannel1->setObjectName(QString::fromUtf8("ButGraphChannel1"));
        ButGraphChannel1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(208, 0, 0);\n"
"}\n"
"\n"
"QPushButton::checked\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));
        ButGraphChannel1->setCheckable(true);
        ButGraphChannel1->setChecked(true);
        ButGraphChannel1->setAutoExclusive(true);

        horizontalLayout->addWidget(ButGraphChannel1);

        ButGraphChannel2 = new QPushButton(groupBox_8);
        ButGraphChannel2->setObjectName(QString::fromUtf8("ButGraphChannel2"));
        ButGraphChannel2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(208, 0, 0);\n"
"}\n"
"\n"
"QPushButton::checked\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));
        ButGraphChannel2->setCheckable(true);
        ButGraphChannel2->setAutoExclusive(true);

        horizontalLayout->addWidget(ButGraphChannel2);

        ButGraphChannel3 = new QPushButton(groupBox_8);
        ButGraphChannel3->setObjectName(QString::fromUtf8("ButGraphChannel3"));
        ButGraphChannel3->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(208, 0, 0);\n"
"}\n"
"\n"
"QPushButton::checked\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));
        ButGraphChannel3->setCheckable(true);
        ButGraphChannel3->setAutoExclusive(true);

        horizontalLayout->addWidget(ButGraphChannel3);

        ButStopGraph = new QPushButton(groupBox_8);
        ButStopGraph->setObjectName(QString::fromUtf8("ButStopGraph"));
        ButStopGraph->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	\n"
"	background-color: rgb(208, 0, 0);\n"
"}\n"
"\n"
"QPushButton::checked\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));
        ButStopGraph->setCheckable(true);
        ButStopGraph->setChecked(true);

        horizontalLayout->addWidget(ButStopGraph);


        gridLayout_7->addWidget(groupBox_8, 1, 0, 1, 1);


        retranslateUi(GraphicsWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GraphicsWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphicsWindow)
    {
        GraphicsWindow->setWindowTitle(QCoreApplication::translate("GraphicsWindow", "GraphicsWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        groupBox_10->setTitle(QString());
        checkXShow1->setText(QCoreApplication::translate("GraphicsWindow", "X", nullptr));
        checkYShow1->setText(QCoreApplication::translate("GraphicsWindow", "Y", nullptr));
        groupBox_2->setTitle(QString());
        checkShowKalman1->setText(QCoreApplication::translate("GraphicsWindow", "\320\244\320\270\320\273\321\214\321\202\321\200\320\276\320\262\320\260\320\275\320\275\320\260\321\217 \320\276\321\210\320\270\320\261\320\272\320\260", nullptr));
        checkShowError1->setText(QCoreApplication::translate("GraphicsWindow", "\320\236\321\210\320\270\320\261\320\272\320\260 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        groupBox_4->setTitle(QString());
        checkShowKalman2->setText(QCoreApplication::translate("GraphicsWindow", "\320\244\320\270\320\273\321\214\321\202\321\200\320\276\320\262\320\260\320\275\320\275\320\260\321\217 \320\276\321\210\320\270\320\261\320\272\320\260", nullptr));
        checkShowError2->setText(QCoreApplication::translate("GraphicsWindow", "\320\236\321\210\320\270\320\261\320\272\320\260 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        groupBox_11->setTitle(QString());
        checkXShow2->setText(QCoreApplication::translate("GraphicsWindow", "X", nullptr));
        checkYShow2->setText(QCoreApplication::translate("GraphicsWindow", "Y", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\273 3", nullptr));
        groupBox_6->setTitle(QString());
        checkShowError3->setText(QCoreApplication::translate("GraphicsWindow", "\320\236\321\210\320\270\320\261\320\272\320\260 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        checkShowKalman3->setText(QCoreApplication::translate("GraphicsWindow", "\320\244\320\270\320\273\321\214\321\202\321\200\320\276\320\262\320\260\320\275\320\275\320\260\321\217 \320\276\321\210\320\270\320\261\320\272\320\260", nullptr));
        groupBox_12->setTitle(QString());
        checkXShow3->setText(QCoreApplication::translate("GraphicsWindow", "X", nullptr));
        checkYShow3->setText(QCoreApplication::translate("GraphicsWindow", "Y", nullptr));
        groupBox_8->setTitle(QString());
        ButGraphChannel1->setText(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        ButGraphChannel2->setText(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        ButGraphChannel3->setText(QCoreApplication::translate("GraphicsWindow", "\320\232\320\260\320\275\320\260\320\2733", nullptr));
        ButStopGraph->setText(QCoreApplication::translate("GraphicsWindow", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphicsWindow: public Ui_GraphicsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSWINDOW_H
