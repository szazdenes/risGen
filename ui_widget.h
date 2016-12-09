/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *articleRadioButton;
    QRadioButton *chapterRadioButton;
    QSpacerItem *horizontalSpacer;
    QCheckBox *custRisCheckBox;
    QPushButton *risGenPushButton;
    QTextEdit *textEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(635, 596);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        articleRadioButton = new QRadioButton(groupBox);
        articleRadioButton->setObjectName(QStringLiteral("articleRadioButton"));

        horizontalLayout_3->addWidget(articleRadioButton);

        chapterRadioButton = new QRadioButton(groupBox);
        chapterRadioButton->setObjectName(QStringLiteral("chapterRadioButton"));

        horizontalLayout_3->addWidget(chapterRadioButton);


        horizontalLayout->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        custRisCheckBox = new QCheckBox(Widget);
        custRisCheckBox->setObjectName(QStringLiteral("custRisCheckBox"));

        horizontalLayout->addWidget(custRisCheckBox, 0, Qt::AlignRight);

        risGenPushButton = new QPushButton(Widget);
        risGenPushButton->setObjectName(QStringLiteral("risGenPushButton"));

        horizontalLayout->addWidget(risGenPushButton, 0, Qt::AlignRight);


        verticalLayout_2->addLayout(horizontalLayout);

        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_2->addWidget(textEdit);

        verticalLayout_2->setStretch(1, 9);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        groupBox->setTitle(QApplication::translate("Widget", "Choose type ", 0));
        articleRadioButton->setText(QApplication::translate("Widget", "Article", 0));
        chapterRadioButton->setText(QApplication::translate("Widget", "Book Chapter", 0));
        custRisCheckBox->setText(QApplication::translate("Widget", "Custom .ris file", 0));
        risGenPushButton->setText(QApplication::translate("Widget", "Generate .ris file", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
