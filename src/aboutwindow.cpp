#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "memory.h"
#include <QPixmap>
#include <QImage>
#include <iostream>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow),
    m_iconPath( "./icon/Anwalic_icon_1.png" )
{
    ui->setupUi(this);
    this->setFixedSize( this->width(), this->height() );

    // show red cross in top right corner of window
    setWindowFlags( Qt::Dialog | Qt::WindowCloseButtonHint );

    // Icon
    QImage iconImage( m_iconPath );
    iconImage.scaled( 128, 128 );
    ui->labelIcon->setPixmap( QPixmap::fromImage( iconImage.scaled( 128, 128 ) ) );
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_btnOk_clicked()
{
    this->accept();
    emit sendGuiFinished();
}

void AboutWindow::reject()
{
    emit sendGuiFinished();
}
