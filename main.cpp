#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "faceverify.h"
#include<QMessageBox>
#include<QApplication>
#include <QtQml/QQmlContext>
#include <QQmlContext>
#include "showimage.h"
#include <QQuickStyle>


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);


    //类
    FaceVerify camera;
    // qml单实例注册
    qmlRegisterSingletonInstance("FaceVerify", 1, 0, "camera", &camera);



    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    //显示图片
    ShowImage *CodeImage = new ShowImage();
    engine.rootContext()->setContextProperty("CodeImage",CodeImage);
    engine.addImageProvider(QLatin1String("CodeImg"), CodeImage->m_pImgProvider);

    //显示图片信号与槽
    QObject::connect(&camera, SIGNAL(SetImage(QImage)), CodeImage, SLOT(setImage(QImage)));


    //上下文: 将类对象注册到QML的上下文背景中
    engine.rootContext()->setContextProperty("camera",&camera);

    //训练
    //cpp获取qml中的指定对象
    auto rootObj = engine.rootObjects();
    auto button = rootObj.first()->findChild<QObject*>("button_train");
    // 使用QT4的方式绑定信号和槽： qml的信号，cpp的槽
    QObject::connect(button, SIGNAL(clicked()), &camera, SLOT(on_pushButton_Train_clicked()));



    return app.exec();
}
