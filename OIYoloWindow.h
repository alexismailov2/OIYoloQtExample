#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class OIYoloWindow : public QMainWindow
{
    Q_OBJECT

public:
    OIYoloWindow(bool isFullscreen = true,
                 QWidget *parent = nullptr);
    ~OIYoloWindow() = default;

private:
    void createActions();
    void createMenus();

    QMenu *fileMenu{};
    QMenu *helpMenu{};
    QAction *preferencesAct{};
    QAction *stationViewerAct{};
    QAction* eventsViewerAct{};
    QAction *exitAct{};
    QAction *aboutAct{};
    QAction *aboutQtAct{};

    bool _isFullscreen{};
};

