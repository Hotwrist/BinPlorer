#ifndef BINLOADER_H
#define BINLOADER_H

#include <QMainWindow>
#include <bfd.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class BinPlorer;
}
QT_END_NAMESPACE

class BinPlorer : public QMainWindow
{
    Q_OBJECT

public:
    BinPlorer(QWidget *parent = nullptr);
    ~BinPlorer();
    void about_binplorer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BinPlorer *ui;
    QString binary_file;
};
#endif // BINLOADER_H
