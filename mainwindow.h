#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Declare a função para inicializar a tabela de símbolos
    void inicializarTabelaSimbolos();

private slots:
    void on_actionSalvar_triggered();

    void on_actionAbrir_triggered();

    void on_Verificar_clicked();

    void on_salvarAssembly_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
