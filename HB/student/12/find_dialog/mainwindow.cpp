#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <QLineEdit>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::stringToUpper(std::string& s) {
    std::string temp = s;
    for (unsigned int i = 0; i < s.length(); i++) {
        temp.at(i) = toupper(s.at(i));
    }
    return temp;
}
// Split string with a delimiter and return in elements of a vector
std::vector<std::string> MainWindow::split(const std::string& s, const char delimiter, bool ignore_empty) {
    std::vector<std::string> result = {};
    std::string tmp = s;
    while (tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if (not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void MainWindow::readfile(const std::string& file, std::string& word, std::string& string_out, const bool& match_case_flag){

    std::ifstream file_object(file);
        if (not file_object) {
            string_out = "File not found";
            return;
        }
        if (word.empty()) {
            string_out = "File found";
            return;
        }
        std::string line_read_from_file = "";
        // get every line in file
        while (getline(file_object, line_read_from_file)) {
            std::vector<std::string> words_in_line = split(line_read_from_file, ' ');
            for (std::string s:words_in_line){

                    if((match_case_flag and word.compare(s) == 0) or (!match_case_flag and stringToUpper(word).compare(stringToUpper(s)) == 0 )){
                            file_object.close();
                            string_out = "Word found";
                            return;
                   }


            }

        }
        file_object.close();
        string_out = "Word not found";
}



void MainWindow::on_fileLineEdit_editingFinished()
{
    file2Find = ui->fileLineEdit->text().toStdString();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    word2Find = ui->keyLineEdit->text().toStdString();
}

void MainWindow::on_matchCheckBox_stateChanged()
{
    if (ui->matchCheckBox->isChecked()) match_case_flag = true;
    else match_case_flag = false;
}

void MainWindow::on_findPushButton_clicked()
{
    readfile(file2Find, word2Find, string_out, match_case_flag);
    QString output_in_qstring = QString::fromStdString(string_out);
    ui->textBrowser->setText(output_in_qstring  );
}
