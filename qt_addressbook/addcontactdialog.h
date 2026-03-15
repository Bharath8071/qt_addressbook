#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class AddContactDialog;
}

class AddContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDialog(QWidget *parent = nullptr);
    ~AddContactDialog();

    bool editMode = false;
    QString originalMobile;

    void setName(QString name);
    void setMobile(QString mobile);
    void setEmail(QString email);
    void setBirthday(QString birthday);

private:
    Ui::AddContactDialog *ui;
};

#endif // ADDCONTACTDIALOG_H
