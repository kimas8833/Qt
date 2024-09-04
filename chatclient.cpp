#include "chatclient.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>

ChatClient::ChatClient(QWidget *parent) : QWidget(parent) {
    socket = new QTcpSocket(this);

    QVBoxLayout *layout = new QVBoxLayout;
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    messageInput = new QLineEdit(this);
    QPushButton *sendButton = new QPushButton("Send", this);

    layout->addWidget(chatDisplay);
    layout->addWidget(messageInput);
    layout->addWidget(sendButton);
    setLayout(layout);

    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(sendButton, &QPushButton::clicked, this, &ChatClient::onSendMessage);

    socket->connectToHost("127.0.0.1", 12345);  // 서버에 연결
}

void ChatClient::onReadyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Client received: " << data;
    chatDisplay->append(QString(data));
}

void ChatClient::onSendMessage() {
    QString message = messageInput->text();
    if (!message.isEmpty()) {
        qDebug() << "Client sending: " << message;
        socket->write(message.toUtf8());
        messageInput->clear();
    }
}
