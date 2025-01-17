#include "InitFunctions.h"
#include "PixivDownloadHelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    // 高分辨率支持
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);
    init(); // 全局设置初始化
    PixivDownloadHelper w;
    w.setWindowIcon(QIcon(ICON_PROGRAM_MAIN)); // 加载程序图标
    w.show();
    return a.exec();
}
