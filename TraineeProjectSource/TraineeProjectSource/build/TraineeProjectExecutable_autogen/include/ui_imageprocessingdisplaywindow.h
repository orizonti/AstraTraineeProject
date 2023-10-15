/********************************************************************************
** Form generated from reading UI file 'imageprocessingdisplaywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSINGDISPLAYWINDOW_H
#define UI_IMAGEPROCESSINGDISPLAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "labelimage.h"

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingDisplayWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label_16;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_21;
    LabelImage *ROI_2_Label;
    LabelImage *ROI_1_Label;
    LabelImage *ROI_3_Label;
    LabelImage *ROI_Long_Label;
    QSpinBox *spinThresImage_2;
    QSpinBox *spinThresImage_3;
    QSpinBox *spinThresImage_4;
    QSpinBox *spinThresImage;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBoxThresManual;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditFilterProcentage;

    void setupUi(QWidget *ImageProcessingDisplayWindow)
    {
        if (ImageProcessingDisplayWindow->objectName().isEmpty())
            ImageProcessingDisplayWindow->setObjectName(QString::fromUtf8("ImageProcessingDisplayWindow"));
        ImageProcessingDisplayWindow->resize(537, 360);
        ImageProcessingDisplayWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"border: 2px solid line black;\n"
"	background-color: rgb(148, 134, 115);\n"
"	font: 8pt \"Sans Serif\";\n"
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
        gridLayout = new QGridLayout(ImageProcessingDisplayWindow);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        label_16 = new QLabel(ImageProcessingDisplayWindow);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setMinimumSize(QSize(512, 128));
        label_16->setMaximumSize(QSize(540, 128));
        label_16->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(69, 75, 70);\n"
"	color: rgb(170, 85, 255);\n"
"border: 2px solid line black;\n"
"}"));

        gridLayout->addWidget(label_16, 0, 0, 1, 2);

        groupBox = new QGroupBox(ImageProcessingDisplayWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(540, 300));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border: 2px solid line black;\n"
"background-color: rgb(94, 94, 94);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"}"));
        gridLayout_21 = new QGridLayout(groupBox);
        gridLayout_21->setSpacing(3);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        gridLayout_21->setContentsMargins(3, 3, 3, 3);
        ROI_2_Label = new LabelImage(groupBox);
        ROI_2_Label->setObjectName(QString::fromUtf8("ROI_2_Label"));
        ROI_2_Label->setMinimumSize(QSize(128, 128));
        ROI_2_Label->setMaximumSize(QSize(128, 128));
        ROI_2_Label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"}"));
        ROI_2_Label->setScaledContents(true);
        ROI_2_Label->setAlignment(Qt::AlignCenter);

        gridLayout_21->addWidget(ROI_2_Label, 1, 1, 1, 1);

        ROI_1_Label = new LabelImage(groupBox);
        ROI_1_Label->setObjectName(QString::fromUtf8("ROI_1_Label"));
        ROI_1_Label->setMinimumSize(QSize(128, 128));
        ROI_1_Label->setMaximumSize(QSize(128, 128));
        ROI_1_Label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"}"));
        ROI_1_Label->setScaledContents(true);
        ROI_1_Label->setAlignment(Qt::AlignCenter);

        gridLayout_21->addWidget(ROI_1_Label, 1, 0, 1, 1);

        ROI_3_Label = new LabelImage(groupBox);
        ROI_3_Label->setObjectName(QString::fromUtf8("ROI_3_Label"));
        ROI_3_Label->setMinimumSize(QSize(128, 128));
        ROI_3_Label->setMaximumSize(QSize(128, 128));
        ROI_3_Label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"}"));
        ROI_3_Label->setScaledContents(true);
        ROI_3_Label->setAlignment(Qt::AlignCenter);

        gridLayout_21->addWidget(ROI_3_Label, 1, 2, 1, 1);

        ROI_Long_Label = new LabelImage(groupBox);
        ROI_Long_Label->setObjectName(QString::fromUtf8("ROI_Long_Label"));
        ROI_Long_Label->setMinimumSize(QSize(128, 128));
        ROI_Long_Label->setMaximumSize(QSize(128, 128));
        ROI_Long_Label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"border: 2px solid line black;\n"
"}"));
        ROI_Long_Label->setScaledContents(true);
        ROI_Long_Label->setAlignment(Qt::AlignCenter);

        gridLayout_21->addWidget(ROI_Long_Label, 1, 3, 1, 1);

        spinThresImage_2 = new QSpinBox(groupBox);
        spinThresImage_2->setObjectName(QString::fromUtf8("spinThresImage_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinThresImage_2->sizePolicy().hasHeightForWidth());
        spinThresImage_2->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        spinThresImage_2->setFont(font);
        spinThresImage_2->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"	font: 75 12pt \"MS Shell Dlg 2\";\n"
"}"));
        spinThresImage_2->setMinimum(1);
        spinThresImage_2->setMaximum(1024);
        spinThresImage_2->setValue(130);

        gridLayout_21->addWidget(spinThresImage_2, 2, 1, 1, 1);

        spinThresImage_3 = new QSpinBox(groupBox);
        spinThresImage_3->setObjectName(QString::fromUtf8("spinThresImage_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinThresImage_3->sizePolicy().hasHeightForWidth());
        spinThresImage_3->setSizePolicy(sizePolicy2);
        spinThresImage_3->setFont(font);
        spinThresImage_3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"	font: 75 12pt \"MS Shell Dlg 2\";\n"
"}"));
        spinThresImage_3->setMinimum(1);
        spinThresImage_3->setMaximum(1024);
        spinThresImage_3->setValue(130);

        gridLayout_21->addWidget(spinThresImage_3, 2, 2, 1, 1);

        spinThresImage_4 = new QSpinBox(groupBox);
        spinThresImage_4->setObjectName(QString::fromUtf8("spinThresImage_4"));
        sizePolicy2.setHeightForWidth(spinThresImage_4->sizePolicy().hasHeightForWidth());
        spinThresImage_4->setSizePolicy(sizePolicy2);
        spinThresImage_4->setFont(font);
        spinThresImage_4->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"	font: 75 12pt \"MS Shell Dlg 2\";\n"
"}"));
        spinThresImage_4->setMinimum(1);
        spinThresImage_4->setMaximum(1024);
        spinThresImage_4->setValue(130);

        gridLayout_21->addWidget(spinThresImage_4, 2, 3, 1, 1);

        spinThresImage = new QSpinBox(groupBox);
        spinThresImage->setObjectName(QString::fromUtf8("spinThresImage"));
        sizePolicy1.setHeightForWidth(spinThresImage->sizePolicy().hasHeightForWidth());
        spinThresImage->setSizePolicy(sizePolicy1);
        spinThresImage->setFont(font);
        spinThresImage->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color: rgb(200, 200, 200);\n"
"	font: 75 12pt \"MS Shell Dlg 2\";\n"
"}"));
        spinThresImage->setMinimum(1);
        spinThresImage->setMaximum(1024);
        spinThresImage->setValue(100);

        gridLayout_21->addWidget(spinThresImage, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(ImageProcessingDisplayWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(170, 170, 0);\n"
"border: 1px solid line black;\n"
"}"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBoxThresManual = new QCheckBox(ImageProcessingDisplayWindow);
        checkBoxThresManual->setObjectName(QString::fromUtf8("checkBoxThresManual"));
        checkBoxThresManual->setChecked(false);

        horizontalLayout_2->addWidget(checkBoxThresManual);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(ImageProcessingDisplayWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"background-color: rgb(170, 170, 0);\n"
"border: 1px solid line black;\n"
"}"));

        horizontalLayout_3->addWidget(label_2);

        lineEditFilterProcentage = new QLineEdit(ImageProcessingDisplayWindow);
        lineEditFilterProcentage->setObjectName(QString::fromUtf8("lineEditFilterProcentage"));
        lineEditFilterProcentage->setFont(font1);

        horizontalLayout_3->addWidget(lineEditFilterProcentage);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);


        retranslateUi(ImageProcessingDisplayWindow);

        QMetaObject::connectSlotsByName(ImageProcessingDisplayWindow);
    } // setupUi

    void retranslateUi(QWidget *ImageProcessingDisplayWindow)
    {
        ImageProcessingDisplayWindow->setWindowTitle(QCoreApplication::translate("ImageProcessingDisplayWindow", "ImageProcessingDisplayWindow", nullptr));
        label_16->setText(QString());
        ROI_2_Label->setText(QString());
        ROI_1_Label->setText(QString());
        ROI_3_Label->setText(QString());
        ROI_Long_Label->setText(QString());
        label->setText(QCoreApplication::translate("ImageProcessingDisplayWindow", "\320\237\320\276\321\200\320\276\320\263", nullptr));
        checkBoxThresManual->setText(QCoreApplication::translate("ImageProcessingDisplayWindow", "\320\240\321\203\321\207\320\275\320\276\320\265 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("ImageProcessingDisplayWindow", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202 \320\276\321\202\320\261\321\200\320\276\321\201\320\260 \320\272\320\260\320\264\321\200\320\276\320\262", nullptr));
        lineEditFilterProcentage->setText(QCoreApplication::translate("ImageProcessingDisplayWindow", "10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingDisplayWindow: public Ui_ImageProcessingDisplayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSINGDISPLAYWINDOW_H
