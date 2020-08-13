#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkConfigurationManager>
#include <QJsonObject>
#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>
#include <QProgressBar>
#include <QPixmap>
#include <QFileDialog>
#include <QEventLoop>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply;
    QNetworkRequest networkRequest;
    QString sql,folderHome,iRecord,downloadingFile;
    QString urlWS,urlUploadSVG,urlDownloadSVG,urlRemoveSVG,remoteFolder;
    QString db_name,usr_db,pwd_db;
    QFont fontUpper;

public slots:
    void listRecords();
    void addRecord();
    void updateRecord();
    int msgYesNo(QString msg);
    void downloadSVG(QString url, QString remoteFolder, QString remoteFile);
    void uploadSVG(QString url, QString remoteFolder, QString downloadingFile, QString remoteFile);
    void replyProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadFinished(QNetworkReply *networkReply);
    void removeSVG(QString url, QString remoteFolder, QString remoteFile);

private slots:
    void on_btnReloadList_clicked();

    void on_btnNew_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_btnUploadPicture_clicked();

    void on_btnDeletePicture_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
