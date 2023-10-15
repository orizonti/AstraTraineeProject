/********************************************************************************
** Form generated from reading UI file 'pidwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIDWINDOW2_H
#define UI_PIDWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIDWindow2
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *ButSetPIDParam;
    QPushButton *butLoadPreference;
    QCheckBox *checkWorkBlock;
    QListWidget *listPIDPreference;

    void setupUi(QWidget *PIDWindow2)
    {
        if (PIDWindow2->objectName().isEmpty())
            PIDWindow2->setObjectName(QString::fromUtf8("PIDWindow2"));
        PIDWindow2->resize(291, 313);
        PIDWindow2->setMinimumSize(QSize(280, 300));
        PIDWindow2->setStyleSheet(QString::fromUtf8("QWidget\n"
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
"}"));
        gridLayout = new QGridLayout(PIDWindow2);
        gridLayout->setSpacing(4);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(4, 4, 4, -1);
        label = new QLabel(PIDWindow2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        ButSetPIDParam = new QPushButton(PIDWindow2);
        ButSetPIDParam->setObjectName(QString::fromUtf8("ButSetPIDParam"));
        sizePolicy.setHeightForWidth(ButSetPIDParam->sizePolicy().hasHeightForWidth());
        ButSetPIDParam->setSizePolicy(sizePolicy);
        ButSetPIDParam->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(ButSetPIDParam, 4, 0, 1, 1);

        butLoadPreference = new QPushButton(PIDWindow2);
        butLoadPreference->setObjectName(QString::fromUtf8("butLoadPreference"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(butLoadPreference->sizePolicy().hasHeightForWidth());
        butLoadPreference->setSizePolicy(sizePolicy1);
        butLoadPreference->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-color: rgb(168, 168, 168);\n"
"}\n"
"\n"
"\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"\n"
" \n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.025, y1:0.00568182, x2:1, y2:1, stop:0 rgba(0, 170, 18, 255), stop:1 rgba(255, 255, 255, 255));\n"
"\n"
"}"));

        gridLayout->addWidget(butLoadPreference, 3, 0, 1, 1);

        checkWorkBlock = new QCheckBox(PIDWindow2);
        checkWorkBlock->setObjectName(QString::fromUtf8("checkWorkBlock"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkWorkBlock->sizePolicy().hasHeightForWidth());
        checkWorkBlock->setSizePolicy(sizePolicy2);
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

        gridLayout->addWidget(checkWorkBlock, 5, 0, 1, 1);

        listPIDPreference = new QListWidget(PIDWindow2);
        new QListWidgetItem(listPIDPreference);
        new QListWidgetItem(listPIDPreference);
        new QListWidgetItem(listPIDPreference);
        listPIDPreference->setObjectName(QString::fromUtf8("listPIDPreference"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listPIDPreference->sizePolicy().hasHeightForWidth());
        listPIDPreference->setSizePolicy(sizePolicy3);
        listPIDPreference->setFont(font);
        listPIDPreference->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(193, 193, 145);\n"
"}"));

        gridLayout->addWidget(listPIDPreference, 2, 0, 1, 1);


        retranslateUi(PIDWindow2);

        QMetaObject::connectSlotsByName(PIDWindow2);
    } // setupUi

    void retranslateUi(QWidget *PIDWindow2)
    {
        PIDWindow2->setWindowTitle(QCoreApplication::translate("PIDWindow2", "PIDWindow2", nullptr));
        label->setText(QCoreApplication::translate("PIDWindow2", "\320\240\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        ButSetPIDParam->setText(QCoreApplication::translate("PIDWindow2", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        butLoadPreference->setText(QCoreApplication::translate("PIDWindow2", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        checkWorkBlock->setText(QCoreApplication::translate("PIDWindow2", "\320\240\320\260\320\261\320\276\321\202\320\260", nullptr));

        const bool __sortingEnabled = listPIDPreference->isSortingEnabled();
        listPIDPreference->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listPIDPreference->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("PIDWindow2", "100 100 100", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listPIDPreference->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("PIDWindow2", "200 200 200", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listPIDPreference->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("PIDWindow2", "300 300 300", nullptr));
        listPIDPreference->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class PIDWindow2: public Ui_PIDWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIDWINDOW2_H
