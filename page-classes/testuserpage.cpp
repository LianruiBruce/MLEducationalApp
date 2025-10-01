#include "testUserPage.h"
#include "ui_testuserpage.h"

testUserPage::testUserPage(QWidget *parent) : QWidget(parent),ui(new Ui::testUserPage), currentQuestionIndex(0), correctAnswers(0) {
    ui->setupUi(this);

    // Assign the button pointers from the UI file
    options[0] = ui->Option1;
    options[1] = ui->Option2;
    options[2] = ui->Option3;
    options[3] = ui->Option4;

    this->setStyleSheet(QString("QPushButton { border: none; }"));
    ui->congratsLabel->setStyleSheet(QString("color: white;"));

    ui->prevButton->setIcon(QIcon(":/resources/img/arrow-left.svg"));
    ui->nextButton->setIcon(QIcon(":/resources/img/arrow-right.svg"));

    // Connect buttons to the slot
    connect(options[0], &QPushButton::clicked, this, &testUserPage::onOptionSelected);
    connect(options[1], &QPushButton::clicked, this, &testUserPage::onOptionSelected);
    connect(options[2], &QPushButton::clicked, this, &testUserPage::onOptionSelected);
    connect(options[3], &QPushButton::clicked, this, &testUserPage::onOptionSelected);

    defaultButtonStyle = QString("QPushButton { background: #a7d6fa; border: 1px solid #3d7ba4; border-radius: 2px; } \
                                  QPushButton:hover { background: #c7f6ff; }");
    correctButtonStyle = QString("background: green");
    wrongButtonStyle = QString("background: red");

    ui->Option1->setStyleSheet(defaultButtonStyle);
    ui->Option2->setStyleSheet(defaultButtonStyle);
    ui->Option3->setStyleSheet(defaultButtonStyle);
    ui->Option4->setStyleSheet(defaultButtonStyle);

    timer = new QTimer(this);
    timer->setInterval(1000); // 1 second
    connect(timer, &QTimer::timeout, this, &testUserPage::onTimeOut);

    setupUI();
    loadQuestion(0);
}

void testUserPage::setupUI() {
    // Initialize questions and answers
    questions << "What does a Linear Regression model do?" << "In the physics simulation, what did the ball represent?"
              << "In the physics simulation, what did the height of the curved ground at a given point represent?";
    answers << (QStringList() << "Simulates ChatGPT but for numbers" << "Tells you the price of a house" << "Predicts outputs given an input" << "Creates images from a prompt")
            << (QStringList() << "The model's current value for the variable \"m\"" << "How bad the model was doing" << "Nothing in particular" << "The data being given to the model")
            << (QStringList() << "Nothing in particular" << "The data being given to the model" << "How good the model performs with the given \"m\"" << "How bad the model performs with the given \"m\"");
    correctAnswerIndex << 2 << 0 << 3; // Correct answers for the questions
}

void testUserPage::loadQuestion(int index) {
    // Set the question text
    ui->QuestionLabelText->setText(questions[index]);
    ui->Option1->setText(answers[index][0]);
    ui->Option2->setText(answers[index][1]);
    ui->Option3->setText(answers[index][2]);
    ui->Option4->setText(answers[index][3]);
}


void testUserPage::onOptionSelected() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return; // If the cast failed or the sender is not a QPushButton, exit the function

    // Find which button was clicked
    int selectedIndex = -1;
    for (int i = 0; i < 4; ++i) {
        if (options[i] == button) {
            selectedIndex = i;
            break;
        }
    }

    // If we didn't find the button in the options array, something went wrong
    if (selectedIndex == -1) return;

    // Check if the selected answer is correct
    bool isCorrect = selectedIndex == correctAnswerIndex[currentQuestionIndex];
    QString style = isCorrect ? correctButtonStyle : wrongButtonStyle;
    setButtonStyle(button, style);

    if (isCorrect) {
        // Increment correctAnswers and proceed to next question after 1 second
        correctAnswers++;
        ui->progressBar->setValue(correctAnswers);
        timer->singleShot(1000, [this]() {
            // Only increment the currentQuestionIndex if the answer was correct
            if (currentQuestionIndex < questions.size() - 1) {
                currentQuestionIndex++;
                loadQuestion(currentQuestionIndex);
            } else if (correctAnswers == questions.size()) {
                // If all answers are correct, show the completion message
                showCompletionMessage();
            }
            // Reset all buttons to default color for the next question
            for (int i = 0; i < 4; ++i) {
                setButtonStyle(options[i], defaultButtonStyle);
            }
        });
    } else {
        // If the answer is wrong, stay on the current question
        // Reset the button color after 1 second
        timer->singleShot(1000, [this, button]() {
            setButtonStyle(button, defaultButtonStyle);
        });
    }
}



void testUserPage::onTimeOut() {
    timer->stop();
    if (currentQuestionIndex < questions.size() - 1) {
        currentQuestionIndex++;
        loadQuestion(currentQuestionIndex);
        // Reset buttons color
        for (int i = 0; i < 4; ++i) {
            setButtonStyle(options[i], defaultButtonStyle);
        }
    }
}

void testUserPage::showCompletionMessage() {
    ui->congratsLabel->setStyleSheet(QString("color: black;"));
}

void testUserPage::setButtonStyle(QPushButton *button, QString style) {
    button->setStyleSheet(style);
}

QPushButton* testUserPage::getPrevButton() { return ui->prevButton; }
QPushButton* testUserPage::getNextButton() { return ui->nextButton; }
testUserPage::~testUserPage() { delete timer; }
