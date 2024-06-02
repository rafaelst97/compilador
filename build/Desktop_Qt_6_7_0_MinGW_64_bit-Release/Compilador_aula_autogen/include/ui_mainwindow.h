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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
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
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *Programa;
    QTextEdit *programa;
    QLabel *Resultado;
    QTextEdit *retornoGals;
    QLabel *TituloAssembly;
    QTextEdit *resultadoAssembly;
    QVBoxLayout *verticalLayout_2;
    QLabel *titulo_tabela;
    QTableView *tabela_simbolos;
    QPushButton *salvarAssembly;
    QPushButton *Verificar;
    QMenuBar *menubar;
    QMenu *menuArquivo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1757, 574);
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName("actionAbrir");
        actionSalvar = new QAction(MainWindow);
        actionSalvar->setObjectName("actionSalvar");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        Programa = new QLabel(centralwidget);
        Programa->setObjectName("Programa");
        QFont font;
        font.setPointSize(14);
        Programa->setFont(font);

        verticalLayout->addWidget(Programa);

        programa = new QTextEdit(centralwidget);
        programa->setObjectName("programa");
        programa->setFont(font);

        verticalLayout->addWidget(programa);

        Resultado = new QLabel(centralwidget);
        Resultado->setObjectName("Resultado");
        Resultado->setFont(font);

        verticalLayout->addWidget(Resultado);

        retornoGals = new QTextEdit(centralwidget);
        retornoGals->setObjectName("retornoGals");
        retornoGals->setEnabled(false);
        retornoGals->setFont(font);

        verticalLayout->addWidget(retornoGals);

        TituloAssembly = new QLabel(centralwidget);
        TituloAssembly->setObjectName("TituloAssembly");
        TituloAssembly->setFont(font);

        verticalLayout->addWidget(TituloAssembly);

        resultadoAssembly = new QTextEdit(centralwidget);
        resultadoAssembly->setObjectName("resultadoAssembly");
        resultadoAssembly->setEnabled(true);
        resultadoAssembly->setFont(font);

        verticalLayout->addWidget(resultadoAssembly);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        titulo_tabela = new QLabel(centralwidget);
        titulo_tabela->setObjectName("titulo_tabela");
        titulo_tabela->setFont(font);

        verticalLayout_2->addWidget(titulo_tabela);

        tabela_simbolos = new QTableView(centralwidget);
        tabela_simbolos->setObjectName("tabela_simbolos");
        tabela_simbolos->setShowGrid(true);

        verticalLayout_2->addWidget(tabela_simbolos);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        salvarAssembly = new QPushButton(centralwidget);
        salvarAssembly->setObjectName("salvarAssembly");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(salvarAssembly->sizePolicy().hasHeightForWidth());
        salvarAssembly->setSizePolicy(sizePolicy);
        salvarAssembly->setFont(font);

        verticalLayout_3->addWidget(salvarAssembly);

        Verificar = new QPushButton(centralwidget);
        Verificar->setObjectName("Verificar");
        Verificar->setEnabled(true);
        Verificar->setFont(font);

        verticalLayout_3->addWidget(Verificar);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1757, 22));
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
        Programa->setText(QCoreApplication::translate("MainWindow", "Programa", nullptr));
        Resultado->setText(QCoreApplication::translate("MainWindow", "Resultado", nullptr));
        TituloAssembly->setText(QCoreApplication::translate("MainWindow", "Assembly", nullptr));
        titulo_tabela->setText(QCoreApplication::translate("MainWindow", "Tabela de S\303\255mbolos", nullptr));
        salvarAssembly->setText(QCoreApplication::translate("MainWindow", "Salvar C\303\263digo Assembly", nullptr));
        Verificar->setText(QCoreApplication::translate("MainWindow", "Verificar", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
