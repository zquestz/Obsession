#include "dialogprivatemessaging.h"
#include "ui_dialogprivatemessaging.h"
#include <QSettings>


DialogPrivateMessaging::DialogPrivateMessaging(qint16 id, ConnectionController * c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrivateMessaging)
{
    ui->setupUi(this);

    connection = c;
    uid = id;

    user = connection->getUserByUid(uid);

    ui->label->setText(QString("Private messages with ") + QString(user->name));
    this->setWindowTitle(QString("Private messages with ") + QString(user->name));

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

    ui->lineEdit->setFocus();
}

DialogPrivateMessaging::~DialogPrivateMessaging()
{
    delete ui;
}

void DialogPrivateMessaging::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogPrivateMessaging::sendMessage() {
    if(!ui->lineEdit->text().isEmpty()) {
        QSettings settings("mir", "contra");
        connection->sendPMToUser(uid, ui->lineEdit->text());
        ui->textEdit->moveCursor(QTextCursor::End);
        QStringList words = ui->lineEdit->text().split(" ");
        QStringList newWords;
        for(qint32 i=0; i<words.size(); i++) {
            if(words.at(i).startsWith("www.")) {
                QString URL = "<a href=\"http://"+words.at(i)+"\">"+words.at(i)+"</a>";
                newWords.append(URL);
            } else {
                if(words.at(i).startsWith("http://")) {
                    QString URL = "<a href=\""+words.at(i)+"\">"+words.at(i)+"</a>";
                    newWords.append(URL);
                } else {
                    newWords.append(words.at(i));
                }
            }
        }
        QString formatted = newWords.join("&nbsp; ");
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->ensureCursorVisible();
        ui->lineEdit->setFocus();
        ui->textEdit->insertHtml(settings.value("nick", "unnamed").toString()+QString(": ")+formatted+QString("<p />"));
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->textEdit->ensureCursorVisible();
        ui->lineEdit->clear();
        emit sentPM();
    }
}

void DialogPrivateMessaging::gotMessage(QString m) {
    ui->textEdit->moveCursor(QTextCursor::End);
    QStringList words = m.split(" ");
    QStringList newWords;
    for(qint32 i=0; i<words.size(); i++) {
        if(words.at(i).startsWith("www.")) {
            QString URL = "<a href=\"http://"+words.at(i)+"\">"+words.at(i)+"</a>";
            newWords.append(URL);
        } else {
            if(words.at(i).startsWith("http://")) {
                QString URL = "<a href=\""+words.at(i)+"\">"+words.at(i)+"</a>";
                newWords.append(URL);
            } else {
                newWords.append(words.at(i));
            }
        }
    }
    QString formatted = newWords.join("&nbsp; ");
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->ensureCursorVisible();
    ui->lineEdit->setFocus();
    ui->textEdit->insertHtml(QString(user->name)+QString(": ")+formatted+QString("<p />"));
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->ensureCursorVisible();
}
