/********************************************************************************
** Form generated from reading UI file 'PIDWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIDWINDOW_H
#define UI_PIDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIDWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *PIDWindow)
    {
        if (PIDWindow->objectName().isEmpty())
            PIDWindow->setObjectName(QStringLiteral("PIDWindow"));
        PIDWindow->resize(120, 129);
        PIDWindow->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"}\n"
"QLineEdit\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(227, 227, 227);\n"
"}"));
        gridLayout = new QGridLayout(PIDWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PIDWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 0);\n"
"}"));

        gridLayout->addWidget(label, 0, 0, 1, 4);

        label_3 = new QLabel(PIDWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(PIDWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_2 = new QLabel(PIDWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(255, 170, 255);\n"
"}"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(PIDWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 3);

        lineEdit_3 = new QLineEdit(PIDWindow);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 4, 1, 1, 3);

        lineEdit_2 = new QLineEdit(PIDWindow);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 3);

        checkBox = new QCheckBox(PIDWindow);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setFont(font);
        checkBox->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"border: 2px solid line black;\n"
"	\n"
"	background-color: rgb(85, 170, 0);\n"
"}"));

        gridLayout->addWidget(checkBox, 5, 0, 1, 4);


        retranslateUi(PIDWindow);

        QMetaObject::connectSlotsByName(PIDWindow);
    } // setupUi

    void retranslateUi(QWidget *PIDWindow)
    {
        PIDWindow->setWindowTitle(QApplication::translate("PIDWindow", "\320\237\320\230\320\224 \320\240\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200", Q_NULLPTR));
        label->setText(QApplication::translate("PIDWindow", "\320\237\320\230\320\224 \321\200\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200", Q_NULLPTR));
        label_3->setText(QApplication::translate("PIDWindow", " \320\230", Q_NULLPTR));
        label_4->setText(QApplication::translate("PIDWindow", "\320\224", Q_NULLPTR));
        label_2->setText(QApplication::translate("PIDWindow", "\320\237", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("PIDWindow", "0.000", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("PIDWindow", "0.000", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("PIDWindow", "0.000", Q_NULLPTR));
        checkBox->setText(QApplication::translate("PIDWindow", "\320\240\320\260\320\261\320\276\321\202\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PIDWindow: public Ui_PIDWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIDWINDOW_H
