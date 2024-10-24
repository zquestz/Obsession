#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectioncontroller.h"
#include "dialogopenconnection.h"
#include <QLabel>
#include <QTextCursor>
#include "dialogagreement.h"
#include "dialogfilebrowser.h"
#include "dialogerror.h"
#include <QSound>
#include "dialogiconviewer.h"
#include "dialoglinearnews.h"
#include <QFocusEvent>
#include "downloadmanager.h"
#include "uploadmanager.h"
#include "dialogdownloadqueue.h"
#include "dialoguploadsqueue.h"
#include "dialogabout.h"
#include <QListWidgetItem>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

#include "dialogbookmarks.h"
#include "widgetchat.h"
#include "widgetnews.h"
#include "widgetconsole.h"
#include "dialogprivatemessaging.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0, bool checkForUpdates = false);
    ~MainWindow();
    ConnectionController *connection;
    void log(QString);
    void autoConnect();

public slots:
    void openNewConnectionDialog();
    void openAboutDialog();
    void slotCloseWindow();
    void disconnect();
    void onGotServerName();
    void onGotChatMessage(QString message);
    void onGotBroadcast(QString message);
    void onGotPM(QString message, qint16 uid);
    void onOpenMessagingWindow(quint16);
    void onOpenUserInfo(QString username, QString info, quint16);
    void kickUser(quint16);
    void onUserListChanged();
    void openPreferencesDialog();
    void showServerAgreement();
    void openTrackersDialog();
    void openNewWindow();
    void openFileBrowser();
    void onError(QString);
    void openIconViewer();
    void clearChat();
    void clearUserList();
    void openLinearNews();
    void openConsole();
    void openChat();
    void onConnecting();
    void openDownloads();
    void openUploads();
    void removeTab(int);
    void slotCloseTab();
    void onCloseTabRequested(int index);
    void onDownloadQueueUpdated();
    void openThreadedNews();
    void changedTab();
    void playChatSound();
    void playPMSound();
    void onPreferencesSaved();
    void onConnected();
    void onVersionReady();
    void openBookmarksDialog();
    void requestUserInfo(quint16 id);
    void openRequestPermissions();
    void gotPermissions(QString login, QString password, quint8, quint8, quint8, quint8, quint8, quint8, quint8, quint8);
    void onClickCreateAccount();
    void onClickBroadcast();
    void onUserChangedName(QString old_name, QString new_name);
    void onUserLeft(s_user * user);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent*);

private:
    bool altPressed;

    void setStatus(QString s);
    DialogPrivateMessaging * getUserPrivateChat(s_user * user);

    QNetworkReply * pUpdateCheckReply;
    QNetworkAccessManager * pNetworkAccessManager;
    QNetworkRequest * pUpdateCheckRequest;

    Ui::MainWindow *ui;
    DialogOpenConnection * openConnectionDialog;
    QLabel * statusLabel;
    DialogAgreement * agreementDialog;
    DialogFileBrowser * fileBrowserDialog;
    QSound * chatSound;
    QSound * pmSound;
    DialogIconViewer * iconViewer;
    DialogLinearNews * linearNews;
    DownloadManager * downloadManager;
    UploadManager * uploadManager;
    DialogDownloadQueue * downloadsDialog;
    DialogUploadsQueue * uploadsDialog;
    DialogAbout * aboutDialog;
    DialogBookmarks * bookmarksDialog;

    QTimer keepAliveTimer;

    WidgetChat * chatWidget;
    WidgetNews * threadedNewsWidget;
    WidgetConsole * debugConsole;

    std::map<std::string, DialogPrivateMessaging *> pPrivateChats;
};

#endif // MAINWINDOW_H
