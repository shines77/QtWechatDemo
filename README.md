# QtWechatDemo

## 📚简介

本项目为 Qt Widget 实现的 Windows 微信界面，纯界面逻辑，不包含业务逻辑。主要用于学习 QWidget 的使用，包含控件自绘、布局、信号、事件、重写、多线程和 qss 等技术。

基于 [阿木大叔](https://gitee.com/hudejie/) 的 [https://gitee.com/hudejie/wecom-copy](https://gitee.com/hudejie/wecom-copy) 改写，做了大量修改。

改进列表：

1. 移除 `include`、`source` 目录，源代码移至 `./src/wechat` 目录，头文件和 cpp 文件放一起；
2. 文件名改为驼峰命名，看起来很直观，更改部分文件的文件名，例如：`navpane.cpp` 更改为 `NavPanel.cpp`；
3. 规范化头文件的 inculde 顺序，更规范；
4. qrc 资源文件目录和文件名重构，css 中的 name 和源代码中的引用名也都修改为驼峰命名；
5. 修正 IconHelper 的接口的定义，QChar 更改为 QString，更规范；
6. 移除了 ECharts 的示例代码；

## 📌本仓库 Git

- [https://gitee.com/shines77/QtWechatDemo](https://gitee.com/shines77/QtWechatDemo)
- [https://github.com/shines77/QtWechatDemo](https://github.com/shines77/QtWechatDemo)

## 📦编译环境

- Qt 5.6.2 + msvc 2015 - 64bit
- Qt 5.12.1 + msvc 2017 - 64bit
- Windows / Linux

## 🛠主要技术

| 模块                 |     介绍                                                                          |
| ---------------------|---------------------------------------------------------------------------------- |
| qss                  |     样式表，本程序所有窗体、控件的样式都由 qss 设计                               |
| signal\slot          |     控件、窗体间通信，事件处理                                                    |
| QThread              |     聊天消息处理线程                                                              |
| QNetworkAccessManager|     网络请求，主要用于聊天机器人的调用                                            |
| QPainter             |     部分窗口的绘制，例如：聊天历史记录的绘制                                      |
| iconfont             |     阿里巴巴矢量图标库，主要用于按钮及标签上图标等显示                            |
| WebEngineWidgets     |     实现嵌入 html，主要用于聊天界面                                               |
| WebChannel           |     和 js 进行通信，用于聊天界面交互                                              |

## 📝参考

- [📗qt官网](https://doc.qt.io/)

- [📘QTCN开发网](http://www.qtcn.org)

- [📙阿木大叔](https://gitee.com/hudejie/wecom-copy)

- [📙飞扬青云](https://gitee.com/feiyangqingyun)
