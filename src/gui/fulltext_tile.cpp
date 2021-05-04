#include "fulltext_tile.h"

fulltext_tile::fulltext_tile(QWidget *parent, QString topic_src) : dash_tile(parent, topic_src)
{
    pure_text = new QLabel(this);
    pure_text->setGeometry(QRect(10, 10, 191, 21));
    pure_text->setText("Plain text");
    pure_text->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));

    topic_label = new QLabel(this);
    topic_label->setGeometry(QRect(10, 35, 191, 21));
    topic_label->setText(topic_src);
    topic_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));

    scrollArea_5 = new QScrollArea(this);
    scrollArea_5->setObjectName(QString::fromUtf8("scrollArea_5"));
    scrollArea_5->setGeometry(QRect(10, 60, 300, 130));
    scrollArea_5->setWidgetResizable(true);

    scrollAreaWidgetContents_5 = new QWidget(scrollArea_5);
    scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 300, 130));

    value_text_2 = new QPlainTextEdit(scrollAreaWidgetContents_5);
    value_text_2->setReadOnly(true);
    value_text_2->setGeometry(QRect(0, 0, 300, 130));
    value_text_2->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "}"));
}

void fulltext_tile::incoming_data(QString incoming_topic, QString payload)
{
    if(incoming_topic == topic){
        value_text_2->setPlainText(payload);
    }
}
