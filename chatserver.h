#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class ChatServer : public QTcpServer {
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);
    void startServer(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onClientDisconnected();

private:
    QMap<qintptr, QTcpSocket*> clients;  // 연결된 클라이언트 관리
};

#endif // CHATSERVER_H
