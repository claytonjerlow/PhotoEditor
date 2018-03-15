#ifndef SAVEWIND_H
#define SAVEWIND_H

#include "image.h"
#include <QDialog>
#include <QString>

namespace Ui {
class savewind;
}

class savewind : public QDialog
{
    Q_OBJECT

public:
    explicit savewind(QWidget *_parent = 0, Image* _img = nullptr, const QString& path = "");
    ~savewind();

private slots:
    void on_back_clicked();

    void on_save_clicked();

private:
    Ui::savewind *ui;
    Image* img;
    QString filepath;
    QWidget* parent;
};

#endif // SAVEWIND_H
