#include "fulltext_tile.h"

fulltext_tile::fulltext_tile() : dash_tile()
{
    pure_text = new QLabel(this);
            pure_text->setObjectName(QString::fromUtf8("pure_text"));
            pure_text->setGeometry(QRect(10, 10, 191, 21));
            pure_text->setText("Plain text");
            //pure_text->setFont(font2);
            pure_text->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            scrollArea_5 = new QScrollArea(this);
            scrollArea_5->setObjectName(QString::fromUtf8("scrollArea_5"));
            scrollArea_5->setGeometry(QRect(10, 50, 331, 141));
            scrollArea_5->setWidgetResizable(true);
            scrollAreaWidgetContents_5 = new QWidget();
            scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
            scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 329, 139));
            value_text_2 = new QPlainTextEdit(scrollAreaWidgetContents_5);
            value_text_2->setObjectName(QString::fromUtf8("value_text_2"));
            value_text_2->setGeometry(QRect(0, 0, 331, 141));
            value_text_2->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "border-left:none;\n"
    "border-right:none;\n"
    "border-top:none;\n"
    "border-bottom:none;\n"
    "}"));
}
