#include "resuleedit.h"

ResuleEdit::ResuleEdit(QWidget *parent) : QDialog(parent)
{
    mainEdit = new QTextEdit(this);
    setMinimumSize(100, 200);
}
