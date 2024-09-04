#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {}

void ChatServer::startServer(quint16 port) {
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start!";
    } else {
        qDebug() << "Server started on port" << port;
    }
}

void ChatServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::onClientDisconnected);

    clients[socketDescriptor] = clientSocket;
    qDebug() << "New client connected!";
}

void ChatServer::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = clientSocket->readAll();

    qDebug() << "Server received: " << data;

    // 연결된 모든 클라이언트에게 메시지 브로드캐스트
    for (auto &client : clients) {
        if (client != clientSocket) {  // 송신자를 제외하고 메시지를 전송
            client->write(data);
        }
    }
}

void ChatServer::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    clients.remove(clientSocket->socketDescriptor());
    clientSocket->deleteLater();
    qDebug() << "Client disconnected!";
}
