#ifndef  SHUTDOWNMANAGER_H
#define SHUTDOWNMANAGER_H
#include <QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>

#include "view/mainframe.h"
#include "dbus/dbussessionmanager.h"
#include "dbus/dbushotzone.h"
#include "../background/backgroundlabel.h"
#include "util_signalmanager.h"

class ShutdownManager : public QFrame
{
    Q_OBJECT
public:
    ShutdownManager(QWidget* parent = 0);
    ~ShutdownManager();

signals:
    void DirectKeyLeft();
    void DirectKeyRight();
    void pressEnter();

public slots:
    void powerAction(const ShutDownFrame::Actions action);
    void hideBtns(const QStringList &btnsName);
    void disableBtns(const QStringList &btnsName);
    void shutDownFramegrabKeyboard();

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void initUI();
    void initConnect();
    void initData();
    void switchToGreeter();

    QHBoxLayout* m_Layout;
    MainFrame* m_content;

    DBusSessionManagerInterface* m_sessionInterface;
    DBusHotzone* m_hotZoneInterface;
};

#endif // SessionManagerTool_H
