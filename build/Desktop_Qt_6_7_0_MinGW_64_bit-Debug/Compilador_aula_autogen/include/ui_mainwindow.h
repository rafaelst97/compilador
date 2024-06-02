/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir;
    QAction *actionSalvar;
    QWidget *centralwidget;
    QPushButton *Verificar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *Programa;
    QTextEdit *programa;
    QLabel *Resultado;
    QTextEdit *retornoGals;
    QMenuBar *menubar;
    QMenu *menuArquivo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName("actionAbrir");
        actionSalvar = new QAction(MainWindow);
        actionSalvar->setObjectName("actionSalvar");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Verificar = new QPushButton(centralwidget);
        Verificar->setObjectName("Verificar");
        Verificar->setEnabled(true);
        Verificar->setGeometry(QRect(674, 510, 101, 31));
        QFont font;
        font.setPointSize(14);
        Verificar->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 781, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Programa = new QLabel(layoutWidget);
        Programa->setObjectName("Programa");
        Programa->setFont(font);

        verticalLayout->addWidget(Programa);

        programa = new QTextEdit(layoutWidget);
        programa->setObjectName("programa");
        programa->setFont(font);

        verticalLayout->addWidget(programa);

        Resultado = new QLabel(layoutWidget);
        Resultado->setObjectName("Resultado");
        Resultado->setFont(font);

        verticalLayout->addWidget(Resultado);

        retornoGals = new QTextEdit(layoutWidget);
        retornoGals->setObjectName("retornoGals");
        retornoGals->setEnabled(false);
        retornoGals->setFont(font);

        verticalLayout->addWidget(retornoGals);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuArquivo = new QMenu(menubar);
        menuArquivo->setObjectName("menuArquivo");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArquivo->menuAction());
        menuArquivo->addAction(actionAbrir);
        menuArquivo->addAction(actionSalvar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbrir->setText(QCoreApplication::translate("MainWindow", "Abrir...", nullptr));
        actionSalvar->setText(QCoreApplication::translate("MainWindow", "Salvar...", nullptr));
        Verificar->setText(QCoreApplication::translate("MainWindow", "Verificar", nullptr));
        Programa->setText(QCoreApplication::translate("MainWindow", "Programa", nullptr));
        Resultado->setText(QCoreApplication::translate("MainWindow", "Resultado", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
