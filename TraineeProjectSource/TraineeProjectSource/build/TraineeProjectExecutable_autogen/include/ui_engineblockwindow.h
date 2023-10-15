/********************************************************************************
** Form generated from reading UI file 'engineblockwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGINEBLOCKWINDOW_H
#define UI_ENGINEBLOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EngineBlockWindow
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *EngineBlockWindow)
    {
        if (EngineBlockWindow->objectName().isEmpty())
            EngineBlockWindow->setObjectName(QString::fromUtf8("EngineBlockWindow"));
        EngineBlockWindow->resize(215, 170);
        EngineBlockWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
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
        gridLayout = new QGridLayout(EngineBlockWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(EngineBlockWindow);

        QMetaObject::connectSlotsByName(EngineBlockWindow);
    } // setupUi

    void retranslateUi(QWidget *EngineBlockWindow)
    {
        EngineBlockWindow->setWindowTitle(QCoreApplication::translate("EngineBlockWindow", "EngineBlockWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EngineBlockWindow: public Ui_EngineBlockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGINEBLOCKWINDOW_H
