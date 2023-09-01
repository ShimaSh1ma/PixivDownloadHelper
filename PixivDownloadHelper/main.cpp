#include "PixivDownloadHelper.h"
#include <QtWidgets/QApplication>
#include "InitFunctions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();//全局设置初始化
    PixivDownloadHelper w;
    w.setWindowIcon(QIcon(_icon_main_path.c_str()));//加载程序图标
    w.show();
    return a.exec();
}
