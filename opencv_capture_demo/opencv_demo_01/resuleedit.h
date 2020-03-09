#ifndef RESULEEDIT_H
#define RESULEEDIT_H

#include <QDialog>
#include <QWidget>
#include <QTextEdit>


class ResuleEdit : public QDialog
{
    Q_OBJECT
public:
    explicit ResuleEdit(QWidget *parent = nullptr);

signals:

public slots:

public:
    QTextEdit *mainEdit;
};

#endif // RESULEEDIT_H
