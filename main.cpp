#include <QApplication>
#include "chatserver.h"
#include "chatclient.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 서버 실행
    ChatServer server;
    server.startServer(12345);

    // 클라이언트 1 실행
    ChatClient client1;
    client1.setWindowTitle("Client 1");
    client1.show();

    // 클라이언트 2 실행
    ChatClient client2;
    client2.setWindowTitle("Client 2");
    client2.show();

    return a.exec();
}
