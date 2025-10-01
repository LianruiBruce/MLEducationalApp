#ifndef TESTUSERPAGE_H
#define TESTUSERPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class testUserPage;
}

class testUserPage : public QWidget {
    Q_OBJECT

public:
    explicit testUserPage(QWidget *parent = nullptr);
    ~testUserPage();
    QPushButton* getPrevButton();
    QPushButton* getNextButton();

private slots:
    void onOptionSelected();
    void onTimeOut();

private:
    Ui::testUserPage *ui;
    QLabel *questionLabel;
    QPushButton *options[4];
    QProgressBar *progressBar;
    QTimer *timer;
    int currentQuestionIndex;
    int correctAnswers;
    QStringList questions;
    QList<QStringList> answers;
    QList<int> correctAnswerIndex;

    QString defaultButtonStyle;
    QString correctButtonStyle;
    QString wrongButtonStyle;

    void setupUI();
    void loadQuestion(int index);
    void setButtonStyle(QPushButton *button, QString style);
    void showCompletionMessage();
};

#endif // TESTUSERPAGE_H
