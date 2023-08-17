/********************************************************************************
** Form generated from reading UI file 'PixivDownloadHelper.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXIVDOWNLOADHELPER_H
#define UI_PIXIVDOWNLOADHELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PixivDownloadHelperClass
{
public:

    void setupUi(QWidget *PixivDownloadHelperClass)
    {
        if (PixivDownloadHelperClass->objectName().isEmpty())
            PixivDownloadHelperClass->setObjectName(QString::fromUtf8("PixivDownloadHelperClass"));
        PixivDownloadHelperClass->resize(600, 400);

        retranslateUi(PixivDownloadHelperClass);

        QMetaObject::connectSlotsByName(PixivDownloadHelperClass);
    } // setupUi

    void retranslateUi(QWidget *PixivDownloadHelperClass)
    {
        PixivDownloadHelperClass->setWindowTitle(QCoreApplication::translate("PixivDownloadHelperClass", "PixivDownloadHelper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PixivDownloadHelperClass: public Ui_PixivDownloadHelperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXIVDOWNLOADHELPER_H
