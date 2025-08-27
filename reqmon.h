#ifndef REQMON_H
#define REQMON_H

#include <QWidget>

namespace Ui {
class ReqMon;
}

class ReqMon : public QWidget
{
    Q_OBJECT

public:
    explicit ReqMon(QWidget *parent = nullptr);
    ~ReqMon();

private:
    Ui::ReqMon *ui;
};

#endif // REQMON_H
