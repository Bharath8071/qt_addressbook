#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>

#include <QLineEdit>

#include <addcontactdialog.h>

void MainWindow::loadContacts()
{
    ui->contactsTable->setRowCount(0);

    QSqlQuery query("SELECT name, mobile, email, birthday FROM contacts");

    int row = 0;

    while(query.next())
    {
        ui->contactsTable->insertRow(row);

        ui->contactsTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->contactsTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->contactsTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->contactsTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));

        row++;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->addButton, &QPushButton::clicked, this, [=]() {

        AddContactDialog dialog;

        if(dialog.exec() == QDialog::Accepted)
        {
            loadContacts(); // refresh table
        }

    });

    connect(ui->editButton, &QPushButton::clicked, this, [=]() {

        int row = ui->contactsTable->currentRow();

        if(row < 0)
            return;

        QString name = ui->contactsTable->item(row,0)->text();
        QString mobile = ui->contactsTable->item(row,1)->text();
        QString email = ui->contactsTable->item(row,2)->text();
        QString birthday = ui->contactsTable->item(row,3)->text();

        AddContactDialog dialog;

        dialog.editMode = true;
        dialog.originalMobile = mobile;


        dialog.findChild<QLineEdit*>("nameLineEdit")->setText(name);
        dialog.findChild<QLineEdit*>("mobileLineEdit")->setText(mobile);
        dialog.findChild<QLineEdit*>("emailLineEdit")->setText(email);

        if(dialog.exec() == QDialog::Accepted)
        {
            loadContacts();
        }

    });

    loadContacts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

