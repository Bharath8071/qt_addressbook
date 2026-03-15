#include "addcontactdialog.h"
#include "ui_addcontactdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AddContactDialog::AddContactDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddContactDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, [=]() {

        QString name = ui->nameLineEdit->text();
        QString mobile = ui->mobileLineEdit->text();
        QString email = ui->emailLineEdit->text();
        QString birthday = ui->birthdayDateEdit->date().toString("yyyy-MM-dd");

        QSqlQuery query;

        query.prepare("INSERT INTO contacts (name, mobile, email, birthday) "
                      "VALUES (?, ?, ?, ?)");

        query.addBindValue(name);
        query.addBindValue(mobile);
        query.addBindValue(email);
        query.addBindValue(birthday);

        if(!query.exec())
        {
            qDebug() << "Insert failed:" << query.lastError();
        }

        accept(); // closes dialog
    });

}

AddContactDialog::~AddContactDialog()
{
    delete ui;
}

