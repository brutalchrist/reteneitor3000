#include "reteneitor3000.h"
#include "ui_reteneitor3000.h"

#include <QtGui>

reteneitor3000::reteneitor3000(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reteneitor3000)
{
  /*Inicializando variables*/
  extensionSalida = ".ogg";
  nombreSalida = "Sin_titulo";
  nombreDirectorio = QDir::homePath();


  /*Validador*/
  QRegExp re("[A-z0-9_]+");
  QRegExpValidator *validador = new QRegExpValidator( re, 0 );

  /*Progressdialog*/
  dialogoProgreso.setCancelButton(0);
  dialogoProgreso.setMinimum(0);
  dialogoProgreso.setMaximum(100);
  dialogoProgreso.setWindowModality(Qt::WindowModal);
  dialogoProgreso.setBackgroundRole(QPalette::Midlight);
  dialogoProgreso.setWindowTitle("Trabajando");

  /*Inicializando UI*/
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());
  ui->directorioSalidaLineEdit->setText(QDir::homePath());
  ui->nombreSalidaLineEdit->setText(nombreSalida);
  ui->nombreSalidaLineEdit->setValidator(validador);
  if(!QFile("/usr/bin/lame").exists("/usr/bin/lame")){
    ui->mp3RBoton->setEnabled(false);
    ui->mp3RBoton->setStatusTip("Primero debes instalar lame");
  }
  if(!QFile("/usr/bin/oggdec").exists("/usr/bin/oggdec")){
    ui->oggRBoton->setEnabled(false);
    ui->oggRBoton->setStatusTip("Primero debes instalar oggdec");
  }
}

reteneitor3000::~reteneitor3000()
{
  delete ui;
}

void reteneitor3000::on_abrirArchivo_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Abrir"),
                                                  QDir::homePath(),
                                                  tr("(*.mp3 *.wav *.ogg)"));

  if(!fileName.isEmpty()){
    ui->nombreArchivo->setText(fileName);
  }
}

void reteneitor3000::on_mp3RBoton_clicked()
{
  extensionSalida = ".mp3";
}

void reteneitor3000::on_oggRBoton_clicked()
{
  extensionSalida = ".ogg";
}

void reteneitor3000::on_nombreSalidaLineEdit_lostFocus()
{
  nombreSalida = ui->nombreSalidaLineEdit->text();
}

void reteneitor3000::on_nombreSalidaLineEdit_editingFinished()
{
  nombreSalida = ui->nombreSalidaLineEdit->text();
}

void reteneitor3000::on_buscarDirectorioBoton_clicked()
{
  nombreDirectorio = QFileDialog::getExistingDirectory(this,
                                                       "Abrir directorio",
                                                       QDir::homePath());
  ui->directorioSalidaLineEdit->setText(nombreDirectorio);
}

void reteneitor3000::on_goBoton_clicked()
{
  if(!ui->nombreArchivo->text().isEmpty()){
    if(!ui->texto->toPlainText().isEmpty()){
      t = new QTimer(this);
      t->start(0);
      dialogoProgreso.show();

      dialogoProgreso.setLabelText("Creando texto");
      dialogoProgreso.setValue(10);
      QApplication::processEvents();
      crearTexto();

      dialogoProgreso.setLabelText("Convirtiendo texto a voz");
      dialogoProgreso.setValue(20);
      QApplication::processEvents();
      textoAvoz();

      dialogoProgreso.setLabelText("Normalizando salida");
      dialogoProgreso.setValue(30);
      QApplication::processEvents();
      normalizarSalida();

      dialogoProgreso.setLabelText("Mezclando las pistas");
      dialogoProgreso.setValue(55);
      QApplication::processEvents();
      mesclarPistas();

      dialogoProgreso.setLabelText("Convirtiendo pista, paciencia");
      dialogoProgreso.setValue(80);
      QApplication::processEvents();
      convertir();

      dialogoProgreso.setLabelText("Listo");
      dialogoProgreso.setValue(100);
      QApplication::processEvents();

      dialogoProgreso.close();
      t->stop();

    }
    else
      error("Debe escribir texto");
  }
  else
    error("Debe seleccionar un archivo");
}

void reteneitor3000::crearTexto(){
  QFile text_file("/tmp/reteneitor3000");

  qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
  if (text_file.open(QIODevice::WriteOnly)){
    QTextStream text_stream(&text_file);
    text_stream << ui->texto->toPlainText();
  }
  else
    error("No se pudo crear archivo temporal");
  text_file.close();
}

void reteneitor3000::textoAvoz(){
  comando = "cat /tmp/reteneitor3000|iconv -f utf-8 -t iso-8859-1|text2wave -eval \"(voice_el_diphone)\" -scale 5.0 -o /tmp/salida.wav";
  qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
  system(comando.toLatin1());
}

void reteneitor3000::normalizarSalida(){
  comando = " sox --norm /tmp/salida.wav -b 16 /tmp/salidaMejorada.wav rate 44100 dither -s";
  qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
  system(comando.toLatin1());
}

void reteneitor3000::mesclarPistas(){
  comando = "sox -m "+ui->nombreArchivo->text().toUtf8().replace(" ", "\\ ")+" /tmp/salidaMejorada.wav /tmp/"+nombreSalida+".wav";
  qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
  system(comando.toLatin1());

}

void reteneitor3000::convertir(){
  if(extensionSalida == ".mp3")
    comandoConversion = "lame -m s /tmp/"+nombreSalida+".wav "+nombreDirectorio+"/"+nombreSalida+extensionSalida;
  else if(extensionSalida == ".ogg")
    comandoConversion = "oggenc /tmp/"+nombreSalida+".wav -o "+nombreDirectorio+"/"+nombreSalida+extensionSalida;

  qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
  system(comandoConversion.toLatin1());
}

void reteneitor3000::error(QString mensaje){
  QMessageBox::critical(this,
                        "Error",
                        mensaje
                        );
}

