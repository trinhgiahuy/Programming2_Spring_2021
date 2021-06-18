#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLineEdit>


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    std::string stringToUpper(std::string& s);
    std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false);
    void readfile(const std::string& file, std::string& word,std::string& string_out,  const bool& match_case_flag);
    ~MainWindow();

private slots:
    void on_fileLineEdit_editingFinished();

    void on_keyLineEdit_editingFinished();

    void on_matchCheckBox_stateChanged();

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string file2Find = "";
    std::string word2Find = "";
    std::string string_out = "";
    bool match_case_flag = false;
};
#endif // MAINWINDOW_HH
