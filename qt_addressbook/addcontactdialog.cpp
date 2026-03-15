#include "addcontactdialog.h"
#include "ui_addcontactdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QDate>

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

        if (!editMode)
        {
            query.prepare("INSERT INTO contacts (name, mobile, email, birthday) "
                          "VALUES (?, ?, ?, ?)");

            query.addBindValue(name);
            query.addBindValue(mobile);
            query.addBindValue(email);
            query.addBindValue(birthday);
        }

        else
        {
            query.prepare("UPDATE contacts SET name=?, mobile=?, email=?, birthday=? WHERE mobile=?");

            query.addBindValue(name);
            query.addBindValue(mobile);
            query.addBindValue(email);
            query.addBindValue(birthday);
            query.addBindValue(originalMobile);

        }
        if(!query.exec())
        {
            qDebug() << "Insert failed:" << query.lastError();
        }

        accept(); // closes dialog
    });

}

void AddContactDialog::setName(QString name)
{
    ui->nameLineEdit->setText(name);
}

void AddContactDialog::setMobile(QString mobile)
{
    ui->mobileLineEdit->setText(mobile);
}

void AddContactDialog::setEmail(QString email)
{
    ui->emailLineEdit->setText(email);
}

void AddContactDialog::setBirthday(QString birthday)
{
    ui->birthdayDateEdit->setDate(QDate::fromString(birthday,"yyyy-MM-dd"));
}


AddContactDialog::~AddContactDialog()
{
    delete ui;
}

