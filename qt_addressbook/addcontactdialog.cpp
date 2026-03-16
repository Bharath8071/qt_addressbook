#include "addcontactdialog.h"
#include "ui_addcontactdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QDate>

#include <QRegularExpression>
#include <QMessageBox>

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

        if(name.isEmpty())
        {
            QMessageBox::warning(this,"Error","Name cannot be empty");
            return;
        }

        QRegularExpression mobileRegex("^[0-9]+$");

        if(!mobileRegex.match(mobile).hasMatch())
        {
            QMessageBox::warning(this,"Error","Mobile number must contain digits only");
            return;
        }

        QRegularExpression emailRegex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");

        if(!emailRegex.match(email).hasMatch())
        {
            QMessageBox::warning(this,"Error","Invalid email address");
            return;
        }

        if (!(mobile.length()==10)) {
            QMessageBox::warning(this,"Error","Invalid mobile number");
            return;
        }

        QSqlQuery query;

        if (!editMode)
        {
            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT COUNT(*) FROM contacts WHERE mobile=?");
            checkQuery.addBindValue(mobile);
            checkQuery.exec();

            if(checkQuery.next() && checkQuery.value(0).toInt() > 0)
            {
                QMessageBox::warning(this,"Error","Mobile number already exists");
                return;
            }

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

