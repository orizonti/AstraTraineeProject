/********************************************************************************
** Form generated from reading UI file 'RemoteAimingWindowControl.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEAIMINGWINDOWCONTROL_H
#define UI_REMOTEAIMINGWINDOWCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteAimingWindowControl
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QPushButton *butDirectErrorToChannel1;
    QPushButton *butDirectErrorToChannel2;
    QPushButton *butDirectErrorToChannel3;
    QPushButton *butDirectErrorToAll;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QLabel *labelAxisRotate1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *butSetRegistrationMode;
    QLabel *label_5;
    QPushButton *butSetAimingMode;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *butLoadRotateFromFile;
    QPushButton *butResetRotationModules;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_9;

    void setupUi(QWidget *RemoteAimingWindowControl)
    {
        if (RemoteAimingWindowControl->objectName().isEmpty())
            RemoteAimingWindowControl->setObjectName(QString::fromUtf8("RemoteAimingWindowControl"));
        RemoteAimingWindowControl->resize(246, 262);
        RemoteAimingWindowControl->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"	font: 14pt \"Sans Serif\";\n"
"}\n"
"\n"
"\n"
"QLabel\n"
"{\n"
"border: 0px solid line black;\n"
"	\n"
"	background-color: rgb(148, 134, 115);\n"
"\n"
"}"));
        gridLayout_5 = new QGridLayout(RemoteAimingWindowControl);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(1, 6, 1, 1);
        groupBox = new QGroupBox(RemoteAimingWindowControl);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}\n"
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
"\n"
"QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"}"));
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 0, 1);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 0, 0, 1, 2);

        butDirectErrorToChannel1 = new QPushButton(groupBox);
        butDirectErrorToChannel1->setObjectName(QString::fromUtf8("butDirectErrorToChannel1"));
        butDirectErrorToChannel1->setCheckable(true);
        butDirectErrorToChannel1->setChecked(true);
        butDirectErrorToChannel1->setAutoExclusive(true);

        gridLayout->addWidget(butDirectErrorToChannel1, 1, 0, 1, 2);

        butDirectErrorToChannel2 = new QPushButton(groupBox);
        butDirectErrorToChannel2->setObjectName(QString::fromUtf8("butDirectErrorToChannel2"));
        butDirectErrorToChannel2->setCheckable(true);
        butDirectErrorToChannel2->setAutoExclusive(true);

        gridLayout->addWidget(butDirectErrorToChannel2, 2, 0, 1, 2);

        butDirectErrorToChannel3 = new QPushButton(groupBox);
        butDirectErrorToChannel3->setObjectName(QString::fromUtf8("butDirectErrorToChannel3"));
        butDirectErrorToChannel3->setCheckable(true);
        butDirectErrorToChannel3->setAutoExclusive(true);

        gridLayout->addWidget(butDirectErrorToChannel3, 3, 0, 1, 2);

        butDirectErrorToAll = new QPushButton(groupBox);
        butDirectErrorToAll->setObjectName(QString::fromUtf8("butDirectErrorToAll"));
        butDirectErrorToAll->setCheckable(true);
        butDirectErrorToAll->setAutoExclusive(true);

        gridLayout->addWidget(butDirectErrorToAll, 4, 0, 1, 2);


        gridLayout_5->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(RemoteAimingWindowControl);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}\n"
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
"\n"
"QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"}"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 1, 1, 1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font);

        gridLayout_3->addWidget(label_4, 0, 0, 1, 2);

        labelAxisRotate1 = new QLabel(groupBox_3);
        labelAxisRotate1->setObjectName(QString::fromUtf8("labelAxisRotate1"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelAxisRotate1->sizePolicy().hasHeightForWidth());
        labelAxisRotate1->setSizePolicy(sizePolicy2);
        labelAxisRotate1->setFont(font);

        gridLayout_3->addWidget(labelAxisRotate1, 1, 0, 1, 2);


        gridLayout_5->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(RemoteAimingWindowControl);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}\n"
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
"\n"
"QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"}"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 0, 1);
        butSetRegistrationMode = new QPushButton(groupBox_2);
        butSetRegistrationMode->setObjectName(QString::fromUtf8("butSetRegistrationMode"));
        butSetRegistrationMode->setCheckable(true);
        butSetRegistrationMode->setAutoExclusive(true);

        gridLayout_2->addWidget(butSetRegistrationMode, 2, 0, 1, 2);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 2);

        butSetAimingMode = new QPushButton(groupBox_2);
        butSetAimingMode->setObjectName(QString::fromUtf8("butSetAimingMode"));
        butSetAimingMode->setCheckable(true);
        butSetAimingMode->setChecked(true);
        butSetAimingMode->setAutoExclusive(true);

        gridLayout_2->addWidget(butSetAimingMode, 1, 0, 1, 2);


        gridLayout_5->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(RemoteAimingWindowControl);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 127);\n"
"}\n"
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
"\n"
"QGroupBox\n"
"{\n"
"border: 0px solid line black;\n"
"}"));
        groupBox_4->setAlignment(Qt::AlignCenter);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 1, 1, 1);
        butLoadRotateFromFile = new QPushButton(groupBox_4);
        butLoadRotateFromFile->setObjectName(QString::fromUtf8("butLoadRotateFromFile"));
        butLoadRotateFromFile->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(130, 130, 130, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"border: 1px solid line black;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.625, y1:0.142, x2:0.994318, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}"));

        gridLayout_4->addWidget(butLoadRotateFromFile, 0, 0, 1, 1);

        butResetRotationModules = new QPushButton(groupBox_4);
        butResetRotationModules->setObjectName(QString::fromUtf8("butResetRotationModules"));
        butResetRotationModules->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(130, 130, 130, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"border: 1px solid line black;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.625, y1:0.142, x2:0.994318, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}"));

        gridLayout_4->addWidget(butResetRotationModules, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 3, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 2, 1, 1, 1);

        label_9 = new QLabel(RemoteAimingWindowControl);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_9, 0, 0, 1, 2);


        retranslateUi(RemoteAimingWindowControl);

        QMetaObject::connectSlotsByName(RemoteAimingWindowControl);
    } // setupUi

    void retranslateUi(QWidget *RemoteAimingWindowControl)
    {
        RemoteAimingWindowControl->setWindowTitle(QCoreApplication::translate("RemoteAimingWindowControl", "RemoteAimingWindowControl", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        butDirectErrorToChannel1->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\232\320\260\320\275\320\260\320\273 1", nullptr));
        butDirectErrorToChannel2->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\232\320\260\320\275\320\260\320\273 2", nullptr));
        butDirectErrorToChannel3->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\232\320\260\320\275\320\260\320\273 3", nullptr));
        butDirectErrorToAll->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\222\321\201\320\265", nullptr));
        groupBox_3->setTitle(QString());
        label_4->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        labelAxisRotate1->setText(QCoreApplication::translate("RemoteAimingWindowControl", "<html><head/><body><p>X0.0 </p><p>Y0.0</p><p>Z0.0</p></body></html>", nullptr));
        groupBox_2->setTitle(QString());
        butSetRegistrationMode->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\240\320\265\320\266\320\270\320\274", nullptr));
        butSetAimingMode->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\243\320\264\320\265\321\200\320\266\320\260\320\275\320\270\320\265", nullptr));
        groupBox_4->setTitle(QString());
        butLoadRotateFromFile->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\244\320\260\320\271\320\273", nullptr));
        butResetRotationModules->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        label_9->setText(QCoreApplication::translate("RemoteAimingWindowControl", "\320\222\320\275\320\265\321\210\320\275\321\217\321\217 \320\272\320\260\320\274\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteAimingWindowControl: public Ui_RemoteAimingWindowControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEAIMINGWINDOWCONTROL_H
