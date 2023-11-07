#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    ui->setupUi(this);
}

SpriteView::~SpriteView()
{
    delete ui;
}

