#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>

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


    loadContacts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

