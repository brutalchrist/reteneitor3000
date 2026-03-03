#ifndef RETENEITOR3000_H
#define RETENEITOR3000_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QTextEdit>
#include <QRegularExpression>

namespace Ui {
    class reteneitor3000;
}

class reteneitor3000 : public QMainWindow
{
    Q_OBJECT

public:
    explicit reteneitor3000(QWidget *parent = nullptr);
    ~reteneitor3000();

private:
    Ui::reteneitor3000 *ui;
    QString nombreSalida, extensionSalida, nombreDirectorio, comando, comandoConversion;
    QProgressDialog *dialogoProgreso;
    QTimer *t;

private slots:
    void on_buscarDirectorioBoton_clicked();
    void on_oggRBoton_clicked();
    void on_nombreSalidaLineEdit_editingFinished();
    void on_nombreSalidaLineEdit_lostFocus();
    void on_mp3RBoton_clicked();
    void on_goBoton_clicked();
    void on_abrirArchivo_clicked();

    void error(QString mensaje);
    void crearTexto();
    void textoAvoz();
    void mesclarPistas();
    void normalizarSalida();
    void convertir();
};

#endif // RETENEITOR3000_H
