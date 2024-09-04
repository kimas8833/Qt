#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QTcpSocket>
#include <QWidget>

class QTextEdit;
class QLineEdit;

class ChatClient : public QWidget {
    Q_OBJECT

public:
    explicit ChatClient(QWidget *parent = nullptr);

private slots:
    void onReadyRead();
    void onSendMessage();

private:
    QTcpSocket *socket;
    QTextEdit *chatDisplay;
    QLineEdit *messageInput;
};

#endif // CHATCLIENT_H
