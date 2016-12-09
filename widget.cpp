#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QRegExp>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->articleRadioButton->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_risGenPushButton_clicked()
{
    QFile source;
    pathname = QDir::currentPath();
    sourceFileName = pathname + "/source.txt";
    source.setFileName(sourceFileName);
    source.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&source);

    out << ui->textEdit->toPlainText();
    source.close();

    QFile noEmptyLines;
    FileWithNoEmptyLines = pathname + "/sourceNoEmptyLines.txt";
    noEmptyLines.setFileName(FileWithNoEmptyLines);

    source.open(QIODevice::ReadOnly | QIODevice::Text);


    noEmptyLines.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream readFile(&source);
    QString sourceLine;
    QTextStream out2(&noEmptyLines);


    while(!readFile.atEnd()){
        sourceLine = readFile.readLine();
        if(!sourceLine.isEmpty())
            out2 << sourceLine + "\n";

    }


    source.close();
    noEmptyLines.close();

    if(ui->articleRadioButton->isChecked())
        risGeneratorArticle(FileWithNoEmptyLines);
    if(ui->chapterRadioButton->isChecked())
        risGeneratorBookChapter(FileWithNoEmptyLines);
}

void Widget::risGeneratorArticle(QString filename){

    QFile sourceFile(filename);
    QFile risFile;
    if(ui->custRisCheckBox->isChecked()){
        QString customName = QFileDialog::getSaveFileName(this);
        if (!customName.endsWith(".ris"))
            customName.append(".ris");
        risFile.setFileName(customName);
    }
    else
        risFile.setFileName(pathname + "/ghJour.ris");
    sourceFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream filestream(&sourceFile);

    QString line;
    QStringList language, authors, year, title, journal, volume, issue, firstPage, lastPage, doi;



    risFile.open(QIODevice::WriteOnly | QIODevice::Text);

    while(!filestream.atEnd()){

        line = filestream.readLine();

        language.append(line.split(" ").first());
        line.remove(0, line.split(" ").first().size()+1);

        authors.append(line.split(QRegExp("\\d+")).first().remove(-1,2));
        line.remove(0, line.split(QRegExp("\\d+")).first().size());

        year.append(line.split(")").first());
        line.remove(0, line.split(")").first().size()).remove(0,2);

        if(line.contains("? ")){
            title.append(line.split("? ").first() + "?");
            line.remove(0, line.split("? ").first().size()+2);
        }
        if(line.contains("! ")){
            title.append(line.split("! ").first() + "!");
            line.remove(0, line.split("! ").first().size()+2);
        }
        if(line.contains(". ")) {
            title.append(line.split(". ").first() + ".");
            line.remove(0, line.split(". ").first().size()+2);
        }


        journal.append(line.split(QRegExp("\\d")).first().remove(-1,1));
        line.remove(0, line.split(QRegExp("\\d")).first().size());

        if(line.contains("): ")){
            volume.append(line.split("(").first().remove(-1,1));
            line.remove(0, line.split("(").first().size()+1);


            issue.append(line.split(")").first());
            line.remove(0, line.split(")").first().size()+3);
        }

        else if(!line.contains("): ")){
            volume.append(line.split(": ").first());
            line.remove(0, line.split(": ").first().size()+2);


            issue.append("");
        }

        if (line.contains("-")){
            firstPage.append(line.split("-").first());
            line.remove(0, line.split("-").first().size()+1);
            lastPage.append(line.split(" ").first());
            line.remove(0, line.split(" ").first().size()+1);
        }

        else if(!line.contains("-") && line.contains("(")){
            firstPage.append(line.split("(").first().remove(-1,1));
            lastPage.append("");
        }
        else if(!line.contains("-") && !line.contains("(")){
            firstPage.append(line.remove(QRegExp("\\s")));
            lastPage.append("");
        }


        doi.append(line.split("doi:").last().remove(0,1). remove(-1,1));


    }
    sourceFile.close();

    QTextStream write(&risFile);

    int fileNum = authors.size();
    for (int i = 0; i < fileNum; i++){

        QStringList separateAuthor;
        QString actualAuthorFile = authors.at(i);
        while(actualAuthorFile.contains(",")){
            separateAuthor.append(actualAuthorFile.split(",").first());
            actualAuthorFile.remove(0, actualAuthorFile.split(",").first().size()+2);
        }
        separateAuthor.append(actualAuthorFile); //az utolsot is hozzaadjuk

        write << QString("TY") + "  - " << QString("JOUR") + "\n";
        write << QString("TI") + "  - " << title.at(i) + "\n";
        write << QString("T2") + "  - " << journal.at(i) + "\n";
        if(!volume.at(i).isEmpty())
            write << QString("VL") + "  - " << volume.at(i) + "\n";
        if(!issue.at(i).isEmpty())
            write << QString("IS") + "  - " << issue.at(i) + "\n";
        if(!firstPage.at(i).isEmpty())
            write << QString("SP") + "  - " << firstPage.at(i) + "\n";
        if(!lastPage.at(i).isEmpty())
            write << QString("EP") + "  - " << lastPage.at(i) + "\n";
        if(!year.at(i).isEmpty())
            write << QString("PY") + "  - " << year.at(i) + "\n";
        if(!doi.at(i).isEmpty())
            write << QString("DO") + "  - " << doi.at(i) + "\n";

        int authorSize = separateAuthor.size();

        for(int j = 0; j < authorSize; j++){
            write << QString("AU") + "  - " << separateAuthor.at(j) + "\n";
        }

        write << QString("ER") + "  - " << "\n\n";

    }


    risFile.close();


}

void Widget::risGeneratorBookChapter(QString filename)
{
    QFile sourceFile(filename);
    QFile risFile;
    if(ui->custRisCheckBox->isChecked()){
        QString customName = QFileDialog::getSaveFileName(this);
        if (!customName.endsWith(".ris"))
            customName.append(".ris");
        risFile.setFileName(customName);
    }
    else
        risFile.setFileName(pathname + "/ghChap.ris");
    sourceFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream filestream(&sourceFile);

    QString line;
    QStringList language, authors, year, title, book, series, firstPage, lastPage, publisher, doi, ssn;



    risFile.open(QIODevice::WriteOnly | QIODevice::Text);

    while(!filestream.atEnd()){

        line = filestream.readLine();

        language.append(line.split(" ").first());
        line.remove(0, line.split(" ").first().size()+1);

        authors.append(line.split(QRegExp("\\d+")).first().remove(-1,2));
        line.remove(0, line.split(QRegExp("\\d+")).first().size());

        year.append(line.split(")").first());
        line.remove(0, line.split(")").first().size()).remove(0,2);

        title.append(line.split("pp.").first().remove(-1,1));
        line.remove(0, line.split("pp.").first().size() + 4);

        if (line.contains("-")){
            firstPage.append(line.split("-").first());
            line.remove(0, line.split("-").first().size()+1);
            lastPage.append(line.split(" ").first());
            line.remove(0, line.split(" ").first().size()+1);
        }

        else if(!line.contains("-") && line.contains("(")){
            firstPage.append(line.split("(").first().remove(-1,1));
            lastPage.append("");
        }
        else if(!line.contains("-") && !line.contains("(")){
            firstPage.append(line.remove(QRegExp("\\s")));
            lastPage.append("");
        }

        line.remove(0, line.split("doi:").first().size() + 5);

        doi.append(line.split(")").first());
        line.remove(0, line.split(")").first().size() + 1);
        line.remove(0, line.split(QRegExp("\\d")).first().size());
        line.remove(0, line.split(")").first().size() + 2);

        book.append(line.split(")").first() + ")");
        line.remove(0, line.split(")").first().size() + 2);

        series.append(line.split(",").first());

        line.remove(0, line.split("Springer:").first().size());

        publisher.append(line.split("(").first().replace(", ", "-").remove(-1,1));

        line.remove(0, line.split("print-ISBN:").first().size() + QString("print-ISBN:").size() + 1);

        ssn.append(line.split(",").first());
    }
    sourceFile.close();

    QTextStream write(&risFile);

    int fileNum = authors.size();
    for (int i = 0; i < fileNum; i++){

        QStringList separateAuthor;
        QString actualAuthorFile = authors.at(i);
        while(actualAuthorFile.contains(",")){
            separateAuthor.append(actualAuthorFile.split(",").first());
            actualAuthorFile.remove(0, actualAuthorFile.split(",").first().size()+2);
        }
        separateAuthor.append(actualAuthorFile); //az utolsot is hozzaadjuk

        write << QString("TY") + "  - " << QString("CHAP") + "\n";
        write << QString("T1") + "  - " << title.at(i) + "\n";
        write << QString("T2") + "  - " << book.at(i) + "\n";
        if(!series.at(i).isEmpty())
            write << QString("T3") + "  - " << series.at(i) + "\n";
        if(!firstPage.at(i).isEmpty())
            write << QString("SP") + "  - " << firstPage.at(i) + "\n";
        if(!lastPage.at(i).isEmpty())
            write << QString("EP") + "  - " << lastPage.at(i) + "\n";
        if(!year.at(i).isEmpty())
            write << QString("PY") + "  - " << year.at(i) + "\n";
        write << QString("PB") + "  - " << publisher.at(i) + "\n";
        if(!doi.at(i).isEmpty())
            write << QString("DO") + "  - " << doi.at(i) + "\n";
        if(!doi.at(i).isEmpty())
            write << QString("SN") + "  - " << ssn.at(i) + "\n";

        int authorSize = separateAuthor.size();

        for(int j = 0; j < authorSize; j++){
            write << QString("AU") + "  - " << separateAuthor.at(j) + "\n";
        }

        write << QString("ER") + "  - " << "\n\n";

    }


    risFile.close();
}
