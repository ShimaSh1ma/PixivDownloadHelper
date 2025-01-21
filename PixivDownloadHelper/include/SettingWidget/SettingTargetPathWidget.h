#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

/*
    切换下载路径子窗口，具有一个显示路径的文本框，
    和一个切换路径按钮，切换路径按钮打开文件资源管理器选择路径
*/
class SettingTargetPathWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit SettingTargetPathWidget();
    ~SettingTargetPathWidget() = default;

    SettingTargetPathWidget(const SettingTargetPathWidget&) = delete;
    SettingTargetPathWidget& operator=(const SettingTargetPathWidget&) = delete;
    SettingTargetPathWidget(SettingTargetPathWidget&&) = delete;
    SettingTargetPathWidget& operator=(SettingTargetPathWidget&&) = delete;
  public slots:
    void chooseDownloadPath(); // 打开文件资源管理器选择下载路径，并将更改后的路径写入downloadPath.cfg文件
  private:
    TextLabel* title;
    // 路径显示栏
    DirEdit* pathEdit;
    // 路径切换按钮
    AnimationButton* changeButton;

    // 网格布局
    QGridLayout* layout;
};
