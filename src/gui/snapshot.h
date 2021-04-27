#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QDialog>
#include <QDir>

namespace Ui {
class Snapshot;
}

class Snapshot : public QDialog
{
    Q_OBJECT

public:
    explicit Snapshot(QWidget *parent = nullptr);
    ~Snapshot();

signals:

    void save_tree_structure(QDir);

private slots:
    void on_print_save_clicked();

    void on_directory_button_clicked();

private:
    Ui::Snapshot *ui;
};

#endif // DIALOG_H