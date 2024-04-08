#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

QString local = "C:/Users/Rafael/Downloads/";
QString nome = "programa.eas";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalvar_triggered()
{
    QString filtro = "Arquivos eas (*.eas)";
    QString salvarArquivo = QFileDialog::getSaveFileName(this, "Salvar arquivo", QDir::homePath(), filtro);
    QFile arquivo(salvarArquivo);

    if (!arquivo.open(QFile::WriteOnly|QFile::Text)){
        //QMessageBox::warning(this, "ERRO", "erro ao salvar o arquivo");
    }else{
        QTextStream saida(&arquivo);
        QString texto = ui->programa->toPlainText();
        saida << texto;
        arquivo.close();
    }
}


void MainWindow::on_actionAbrir_triggered()
{
    QString filtro = "Arquivos eas (*.eas)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this, "Abrir arquivo", QDir::homePath(), filtro);
    QFile arquivo(abrirArquivo);

    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){
        //QMessageBox::warning(this, "ERRO", "Erro ao abrir arquivo");
    }else{
        QTextStream entrada(&arquivo);
        QString texto = entrada.readAll();
        ui->programa->setPlainText(texto);
        arquivo.close();
    }

   /* QFile arquivo (local+nome);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "Erro ao abrir arquivo");
    }

    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->programa->clear();
    ui->programa->setPlainText(texto);
    arquivo.close();*/
}

