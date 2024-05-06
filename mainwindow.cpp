#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "Lexico.h"
#include "SemanticError.h"
#include "Semantico.h"
#include "Sintatico.h"
#include "SyntaticError.h"
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(800, 600);
    adjustSize();
    ui->tabela_simbolos->setVisible(false);
    ui->titulo_tabela->setVisible(false);
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

    std::istringstream textoConvertido(texto.toStdString());
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
    catch (LexicalError &e)
    {
        erro = true;
        ui->retornoGals->setPlainText(QString("Erro Léxico: ") + e.getMessage());
    }
    catch (SemanticError &e)
    {
        erro = true;
        ui->retornoGals->setPlainText(QString("Erro Semântico: ") + e.getMessage());
    }

    if (erro == false){
        ui->retornoGals->setPlainText(QString("Compilação bem sucedida!"));
        inicializarTabelaSimbolos();
        ui->tabela_simbolos->setVisible(true); // Torna a tabela de símbolos visível
        ui->titulo_tabela->setVisible(true); // Torna o título da tabela visível
    }
}


void MainWindow::inicializarTabelaSimbolos()
{
    QStringList titulos;
    titulos << "tipo" << "nome" << "iniciado" << "usado" << "escopo" << "parametro"
            << "posicao_do_parametro" << "vetor" << "matriz" << "ref" << "funcao" << "procedimento";

    // Criando um modelo para a tabela
    QStandardItemModel *modelo = new QStandardItemModel(0, titulos.size(), this);
    modelo->setHorizontalHeaderLabels(titulos);

    // Lendo o arquivo JSON de símbolos
    QFile file("simbolos.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Erro", "Não foi possível abrir o arquivo simbolos.json para leitura.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
    {
        QMessageBox::critical(this, "Erro", "O arquivo simbolos.json não contém um array de objetos JSON.");
        return;
    }

    QJsonArray jsonArray = doc.array();

    // Preenchendo a tabela com os dados dos símbolos
    for (int i = 0; i < jsonArray.size(); ++i)
    {
        QJsonObject jsonObject = jsonArray[i].toObject();

        // Extrair os valores do objeto JSON
        QString tipo = jsonObject["tipo"].toString();
        QString nome = jsonObject["nome"].toString();
        char iniciado = jsonObject["iniciado"].toString().toStdString()[0];
        char usado = jsonObject["usado"].toString().toStdString()[0];
        int escopo = jsonObject["escopo"].toInt();
        bool parametro = jsonObject["parametro"].toBool();
        int posicao_do_parametro = jsonObject["posicao_do_parametro"].toInt();
        bool vetor = jsonObject["vetor"].toBool();
        bool matriz = jsonObject["matriz"].toBool();
        bool ref = jsonObject["ref"].toBool();
        bool funcao = jsonObject["funcao"].toBool();
        bool procedimento = jsonObject["procedimento"].toBool();

        // Criando itens para cada célula da linha
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(tipo);
        rowItems << new QStandardItem(nome);
        rowItems << new QStandardItem(QString(iniciado));
        rowItems << new QStandardItem(QString(usado));
        rowItems << new QStandardItem(QString::number(escopo));
        rowItems << new QStandardItem(parametro ? "true" : "false");
        rowItems << new QStandardItem(QString::number(posicao_do_parametro));
        rowItems << new QStandardItem(vetor ? "true" : "false");
        rowItems << new QStandardItem(matriz ? "true" : "false");
        rowItems << new QStandardItem(ref ? "true" : "false");
        rowItems << new QStandardItem(funcao ? "true" : "false");
        rowItems << new QStandardItem(procedimento ? "true" : "false");

        // Inserindo a linha no modelo da tabela
        modelo->appendRow(rowItems);
    }

    // Definindo o modelo para a tabela
    ui->tabela_simbolos->setModel(modelo);
}
