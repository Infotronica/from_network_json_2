#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    folderHome=QDir::homePath()+"/";
    ui->progressBar->setVisible(false);
    fontUpper=font();
    fontUpper.setCapitalization(QFont::AllUppercase); // create upper case font
    ui->lineEdit->setFont(fontUpper); // set this font to lineEdit
    ui->btnUploadPicture->setEnabled(false);
    ui->btnDeletePicture->setEnabled(false);

    /*
        description for php files:
        urlWS - for sql queries like SELECT, INSERT INTO, UPDATE, DELETE FROM etc
        urlUploadSVG - for upload svg files to server
        urlDownloadSVG - for download svg file and show in the labelPixmap widget
        urlRemoveSVG - for remove svg files stored in the server
    */

    db_name="countries"; // the database name
    usr_db="your user"; // the user for this database
    pwd_db="your password"; // the password of user

    urlWS="http://mi-server-de-pruebas.com/for_Navjeet/from_network_json_2/webservice/webservice.php";
    urlUploadSVG="http://mi-server-de-pruebas.com/for_Navjeet/from_network_json_2/webservice/upload_svg.php";
    urlDownloadSVG="http://mi-server-de-pruebas.com/for_Navjeet/from_network_json_2/webservice/download_svg.php";
    urlRemoveSVG="http://mi-server-de-pruebas.com/for_Navjeet/from_network_json_2/webservice/remove_svg.php";
    remoteFolder="country_flags"; // remote folder for store the svg files

    listRecords();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listRecords()
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QJsonDocument jsonDocument;
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    QString sql,qString;
    QStringList stringList;
    QEventLoop qEventLoop; // make a loop for whait while the network request finish
    int j,rowCount;

    ui->tableWidget->clear(); // clear
    ui->tableWidget->setRowCount(0); // the
    ui->tableWidget->setColumnCount(0); // tableWidget
    sql="select * from `countries list`"; // query for the list of `countries list` table

    urlQuery.addQueryItem("sql",sql); // add sql parameter for urlQuery
    urlQuery.addQueryItem("db_name",db_name); // add database name parameter for urlQuery
    urlQuery.addQueryItem("usr_db",usr_db); // add usr parameter for the database for urlQuery
    urlQuery.addQueryItem("pwd_db",pwd_db); // add the pasword parameter for urlQuery
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(urlWS));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    // network request is finished
    // first part, the networkReply contains returned data from the server when the network request is finished
    postData=networkReply->readAll(); // put received QByteArray data into postData object
    networkReply->deleteLater();
    qString=QString::fromUtf8(postData); // copy to a QString
    ui->plainTextEdit->appendHtml(qString); // dump in a plain text for see the json returned

    // second part
    jsonDocument = QJsonDocument::fromJson(postData); // put the returned data in a jsonDocument object
    jsonArray=jsonDocument.array(); // parse to QJsonArray object
    if (jsonArray.isEmpty())
    {
        return;
    }

    ui->tableWidget->setColumnCount(2); // we need to columns
    stringList << "INDEX" << "COUNTRY"; // column headers
    ui->tableWidget->setHorizontalHeaderLabels(stringList); // set the column headers
    ui->tableWidget->setColumnWidth(0,50); // width of first column
    ui->tableWidget->setColumnWidth(1,250); // width of second column
    rowCount=jsonArray.count(); // number of elements in json array
    ui->tableWidget->setRowCount(rowCount); // create the items on tableWidget
    for (j=0; j<rowCount; j++)
    {
        jsonObject=jsonArray.at(j).toObject(); // json array element to json object
        qString=jsonObject.value("icountry").toString(); // get the request data
        ui->tableWidget->setItem(j,0,new QTableWidgetItem(qString)); // set the cell item

        qString=jsonObject.value("country").toString(); // get the request data
        ui->tableWidget->setItem(j,1,new QTableWidgetItem(qString)); // set the cell item
    }
}

void MainWindow::addRecord()
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QJsonDocument jsonDocument;
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    QString sql,str,fechaHoraRegistro,lastIndex;
    QEventLoop qEventLoop; // make a loop for whait while the network request finish

    str=ui->lineEdit->text().toUpper();
    sql="insert into `countries list` set " // query for insert element into `countries list` table
        "`country`='"+str+"'";

    urlQuery.addQueryItem("sql",sql); // add sql parameter for urlQuery
    urlQuery.addQueryItem("db_name",db_name); // add database name parameter for urlQuery
    urlQuery.addQueryItem("usr_db",usr_db); // add usr parameter for the database for urlQuery
    urlQuery.addQueryItem("pwd_db",pwd_db); // add the pasword parameter for urlQuery
    urlQuery.addQueryItem("imax","icountry"); // add the pasword parameter for urlQuery
    urlQuery.addQueryItem("table_max","countries list"); // add the pasword parameter for urlQuery
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(urlWS));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    // the networkReply contains returned data from the server when the network request is finished
    postData=networkReply->readAll(); // put received QByteArray data into postData object
    networkReply->deleteLater();
    iRecord=QString::fromUtf8(postData); // the recieved data is not a json, is just a string that contains the index of the new record
    QTimer::singleShot(200,this,SLOT(listRecords())); // trigger the listRecords slot
}
//----------------------------------------------------------------------------------------------------

void MainWindow::updateRecord()
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QJsonDocument jsonDocument;
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    QString sql,str,fechaHoraRegistro,lastIndex;
    QEventLoop qEventLoop; // make a loop for whait while the network request finish

    str=ui->lineEdit->text().toUpper();
    sql="update `countries list` set " // query for update an existing element into `countries list` table
        "`country`='"+str+"' "
        "where icountry="+iRecord;

    urlQuery.addQueryItem("sql",sql); // add sql parameter for urlQuery
    urlQuery.addQueryItem("db_name",db_name); // add database name parameter for urlQuery
    urlQuery.addQueryItem("usr_db",usr_db); // add usr parameter for the database for urlQuery
    urlQuery.addQueryItem("pwd_db",pwd_db); // add the pasword parameter for urlQuery
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(urlWS));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    // the networkReply is empty and is implemented just for use de qEventLoop object
    networkReply->deleteLater();
    QTimer::singleShot(200,this,SLOT(listRecords())); // trigger the listRecords slot
}
//----------------------------------------------------------------------------------------------------

int MainWindow::msgYesNo(QString msg)
{
    QMessageBox msgBox;
    int mb;

    /*
       this function is for implement a modal dialog using QMessageBox
       the reason is save code
    */
    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton(tr("No"),QMessageBox::NoRole); // return 0
    msgBox.addButton(tr("Si"),QMessageBox::YesRole); // return 1
    msgBox.setDefaultButton(QMessageBox::Yes);
    mb=msgBox.exec();
    return mb;
}

void MainWindow::downloadSVG(QString url, QString remoteFolder, QString remoteFile)
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QEventLoop qEventLoop; // make a loop for whait while the network request finish
    QPixmap pixmap;

    urlQuery.addQueryItem("remoteFolder",remoteFolder);  // add remoteFolder parameter for urlQuery
    urlQuery.addQueryItem("remoteFile",remoteFile);  // add remoteFile parameter for urlQuery
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(url));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    // the networkReply contains the svg file
    postData=networkReply->readAll(); // copy this content in the postData object
    networkReply->deleteLater();
    pixmap.loadFromData(postData);  // is loaded for pixmap object
    ui->labelPixmap->setPixmap(pixmap); // show the svg content in labelPixmap
}
//----------------------------------------------------------------------------------------------------

void MainWindow::uploadSVG(QString url, QString remoteFolder, QString localFile, QString remoteFile)
{
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData,fileContent; // postData contains data to send in the network request and fileContent store the svg file to upload
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QJsonDocument jsonDocument;
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    QStringList stringList;
    QFile uploadingFile;

    uploadingFile.setFileName(localFile);
    if(!uploadingFile.open(QIODevice::ReadOnly)) // open the svg file for read
    {
        return;
    }
    fileContent=uploadingFile.readAll(); // copy the content of svg file in fileContent object (QByteArray)
    uploadingFile.close(); // close the file

    ui->progressBar->setVisible(true);
    urlQuery.addQueryItem("remoteFolder",remoteFolder);  // add remoteFolder parameter for urlQuery
    urlQuery.addQueryItem("remoteFile",remoteFile);  // add remoteFile parameter for urlQuery
    urlQuery.addQueryItem("fileContent",fileContent.toBase64().toBase64()); // this parameter store the content of svg file and is sent to the server
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(url));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    /*
       in this case im not using an event loop object, im connecting to external slots
       the reason is the uploadProgress signal, is not supported for an event loop object
    */
    connect(networkReply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(replyProgress(qint64, qint64)));
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(uploadFinished(QNetworkReply*)));
}
//----------------------------------------------------------------------------------------------------

void MainWindow::replyProgress(qint64 bytesSent, qint64 bytesTotal)
{ // show the upload progress
    ui->progressBar->setMaximum(static_cast<int>(bytesTotal));
    ui->progressBar->setValue(static_cast<int>(bytesSent));
}
//----------------------------------------------------------------------------------------------------

void MainWindow::uploadFinished(QNetworkReply *networkReply)
{
    QByteArray postData;
    QPixmap pixmap;

    // the networkReply contains the svg file uploaded
    postData=networkReply->readAll(); // copy this content in the postData object
    pixmap.loadFromData(postData);  // is loaded for pixmap object
    ui->labelPixmap->setPixmap(pixmap); // show the svg content in labelPixmap

    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
    ui->tableWidget->setFocus();
}
//----------------------------------------------------------------------------------------------------

void MainWindow::removeSVG(QString url, QString remoteFolder, QString remoteFile)
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QEventLoop qEventLoop; // make a loop for whait while the network request finish

    urlQuery.addQueryItem("remoteFolder",remoteFolder);
    urlQuery.addQueryItem("remoteFile",remoteFile);
    postData.append(urlQuery.toString());

    networkRequest.setUrl(QUrl(url));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    // the networkReply is empty and is implemented just for use de qEventLoop object
    networkReply->deleteLater();
    // do nothing after it, we just remove a file in the server ;)
}
//----------------------------------------------------------------------------------------------------

void MainWindow::on_btnReloadList_clicked()
{
    listRecords();
}

void MainWindow::on_btnNew_clicked()
{
    iRecord="";
    ui->lineEdit->setText("");
    ui->lineEdit->setFocus();
}

void MainWindow::on_btnDelete_clicked()
{
    QNetworkAccessManager networkManager; // for make a request on the server using POST or GET method
    QNetworkReply *networkReply; // for recieve and store data after the network request is finished
    QNetworkRequest networkRequest; // contains the structure of the network request
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QUrlQuery urlQuery; // contains the parameters for add int postData
    QString str,indexStr,remoteFile;
    QPixmap pixmap;
    QEventLoop qEventLoop; // make a loop for whait while the network request finish
    int mb,row;

    row=ui->tableWidget->currentIndex().row();
    str=ui->tableWidget->item(row,1)->text();
    if (row==-1)
    {
        return;
    }
    mb=msgYesNo("["+str+"]. Delete this record?");
    if (mb==0)
    {
        return;
    }

    indexStr=ui->tableWidget->item(row,0)->text();
    ui->tableWidget->removeRow(row);

    sql="delete from `countries list` "  // query for delete a record on the list of `countries list` table
        "where icountry="+indexStr;
    urlQuery.addQueryItem("sql",sql); // add sql parameter for urlQuery
    postData.append(urlQuery.toString()); // add urlQuery to postData

    networkRequest.setUrl(QUrl(urlWS));  // url for webservice.php on the url of networkRequest
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=UTF-8"); // set ContentTypeHeader
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,postData.length()); // set the length of sent data
    networkReply = networkManager.post(networkRequest,postData); // make the request to server using the POST method

    connect(networkReply,SIGNAL(finished()),&qEventLoop,SLOT(quit())); // connect the networkReply to a qEventLoop object for whait while the network request finish
    qEventLoop.exec(); // i prefer use the loop instead connect to an external slot :)

    remoteFile=indexStr+".svg";
    removeSVG(urlRemoveSVG,remoteFolder, remoteFile); // remove the svg remote file
    ui->labelPixmap->setPixmap(pixmap); // show a empty pixmap saying to the user that the remote svg file is removed
}

void MainWindow::on_btnSave_clicked()
{
    if (ui->lineEdit->text()=="")
    {
        return;
    }
    if (iRecord=="")
        addRecord();
    else
        updateRecord();
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    QString indexStr,remoteFile;
    int row;

    // this slot is for show the svg file when the user clics one row

    row=index.row();
    if (row==-1)
    {  // disable this buttons is no selected record
        ui->btnUploadPicture->setEnabled(false);
        ui->btnDeletePicture->setEnabled(false);
        return;
    }

    // enable this buttons a record is selected
    ui->btnUploadPicture->setEnabled(true);
    ui->btnDeletePicture->setEnabled(true);
    indexStr=ui->tableWidget->item(row,0)->text();
    remoteFile=indexStr+".svg";
    downloadSVG(urlDownloadSVG, remoteFolder, remoteFile); // show the svg file
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    QString str;
    int row;

    // this slot is for open a record for editing
    row=index.row();
    if (row==-1)
    {
        return;
    }

    iRecord=ui->tableWidget->item(row,0)->text();
    str=ui->tableWidget->item(row,1)->text();
    ui->lineEdit->setText(str);
    ui->lineEdit->setFocus();
}

void MainWindow::on_btnUploadPicture_clicked()
{
    QString pictureFilters,indexStr,remoteFile;
    int row;

    // this slot is for select a local svg file for upload
    pictureFilters="Vectors (*.svg)";
    downloadingFile = QFileDialog::getOpenFileName(this, tr("Upload SVG Picture"), folderHome, pictureFilters);
    if (downloadingFile=="")
    {
        return;
    }

    row=ui->tableWidget->currentRow();
    if (row==-1)
    {
        return;
    }
    indexStr=ui->tableWidget->item(row,0)->text();
    remoteFile=indexStr+".svg";
    uploadSVG(urlUploadSVG, remoteFolder, downloadingFile, remoteFile); // upload th svg file
}

void MainWindow::on_btnDeletePicture_clicked()
{
    QPixmap pixmap;
    QString indexStr,remoteFile;
    int mb,row;

    // this slot is for remove a remote svg file
    row=ui->tableWidget->currentRow();
    if (row==-1)
    {
        return;
    }
    mb=msgYesNo("Do you want to delete the picture?"); // show a modal dialog
    if (mb)
    {
        indexStr=ui->tableWidget->item(row,0)->text();
        remoteFile=indexStr+".svg";
        removeSVG(urlRemoveSVG,remoteFolder, remoteFile); // remove the remote svg file
        ui->labelPixmap->setPixmap(pixmap);
    }
}
