#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QString sourceFileName, FileWithNoEmptyLines;
    QString pathname;

    
private slots:
    void on_risGenPushButton_clicked();

private:
    Ui::Widget *ui;

    void risGeneratorArticle(QString filename);
    void risGeneratorBookChapter(QString filename);


};

#endif // WIDGET_H
