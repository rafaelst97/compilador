#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "Lexico.h"
#include "Semantico.h"
#include "Sintatico.h"

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
        ui->retornoGals->clear();
    }
}


void MainWindow::on_Verificar_clicked()
{
    QString texto = ui->programa->toPlainText();
    Lexico lexico;
    Sintatico sintatico;
    Semantico semantico;
    bool erro = false;

    std::istringstream textoConvertido (texto.toStdString());
    lexico.setInput(textoConvertido);

    try
    {
        sintatico.parse(&lexico, &semantico);
    }
    catch ( SyntaticError &e )
    {
        erro = true;
        ui->retornoGals->setPlainText(QString("Erro Sintático: ") + e.getMessage());
    }

    if (erro == false){
        ui->retornoGals->setPlainText(QString("Compilação bem sucedida!"));
    }
}

