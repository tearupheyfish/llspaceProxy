#ifndef SPACE_H
#define SPACE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Space;
}
QT_END_NAMESPACE

class Space : public QMainWindow
{
    Q_OBJECT

public:
    Space(QWidget *parent = nullptr);
    ~Space();

private slots:
    void on_login_button_clicked();

private:
    Ui::Space *ui;
};
#endif // SPACE_H
