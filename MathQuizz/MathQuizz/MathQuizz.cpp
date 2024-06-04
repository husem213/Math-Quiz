#include <iostream>
#include <stdlib.h>
using namespace std;

enum enQuestionsLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5};
enum enAnswerType {Right = 1, Wrong = 2};
enum enQuizResult {Pass = 1, Fail = 2};

struct strQuestionInfo {

    short QuestionNumber = 0;
    short FirstNumber = 0;
    short SecondNumber = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType QuestionOperation;
};

struct strQuestionResults {

    int PlayerAnswer = 0;
    enAnswerType AnswerType = enAnswerType::Right;
    int QuestionAnswer = 0;
};

struct strQuizInfo {

    short NumberOfQuestions = 0;
    short QuestionsLevel = 0;
    short OperationType = 0;
};

struct strQuizResults {

    enQuizResult FinalResult = enQuizResult::Pass;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
};

short RandomNumber(int from, int to) {

    short RandNum = 0;

    RandNum = rand() % (to - from + 1) + from;

    return RandNum;
}

short ReadNumberOfQuestions() {
    
    short QuestionNumber = 0;

    do {
        cout << "How many questions do you want to answer? ";
        cin >> QuestionNumber;
    } while (QuestionNumber < 0);

    return QuestionNumber;
}

short ReadQuestionsLevel() {

    short QuestionsLevel = 0;

    do {
        cout << "\nEnter questions level: [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ";
        cin >> QuestionsLevel;
    } while (QuestionsLevel < 1 || QuestionsLevel > 4);

    return QuestionsLevel;
}

enQuestionsLevel DefineQuestionLevel(short QuestionLevel) {

    if (QuestionLevel == 5) {
        return (enQuestionsLevel)RandomNumber(1, 4);
    }
    return (enQuestionsLevel)QuestionLevel;
}

short ReadOperationType() {

    short OperationType = 0;

    do {
        cout << "\nEnter operation type: [1]:Addition, [2]:Subtraction, [3]:Multiplication, [4]:Division, [5]:Mix ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);

    return OperationType;
}

enOperationType DefineOperationType(short Operation) {

    if (Operation == enOperationType::MixOp) {
        return (enOperationType)RandomNumber(1, 4);
    }
    return (enOperationType)Operation;
}

short NumbersForQuestion(enQuestionsLevel QuestionLevel) {

    switch (QuestionLevel)
    {
    case Easy:
        return RandomNumber(1, 10);
        break;
    case Med:
        return RandomNumber(10, 50);
        break;
    case Hard:
        return RandomNumber(50, 100);
        break;
    case Mix:
        return RandomNumber(1, 100);
        break;
    }
}

int CalculateTheRightAnswer(enOperationType Operation, short FirstNumber, short SecondNumber) {

    switch (Operation)
    {
    case Add:
        return FirstNumber + SecondNumber;
        break;
    case Sub:
        return FirstNumber - SecondNumber;
        break;
    case Mult:
        return FirstNumber * SecondNumber;
        break;
    case Div:
        return FirstNumber / SecondNumber;
        break;
    }
}

int ReadPlayerAnswer() {
    
    int Answer;

    cin >> Answer;

    return Answer;
}

enAnswerType DefineAnswerType(int PlayerAnswer, int Answer) {

    if (PlayerAnswer == Answer) {
        return enAnswerType::Right;
    }
    return enAnswerType::Wrong;
}

strQuestionInfo FillQuestionInfo(short QuestionNumber, strQuizInfo QuizInfo) {

    strQuestionInfo QuestionInfo;

    QuestionInfo.QuestionNumber = QuestionNumber;
    QuestionInfo.QuestionLevel = DefineQuestionLevel(QuizInfo.QuestionsLevel);
    QuestionInfo.QuestionOperation = DefineOperationType(QuizInfo.OperationType);
    QuestionInfo.FirstNumber = NumbersForQuestion(QuestionInfo.QuestionLevel);
    QuestionInfo.SecondNumber = NumbersForQuestion(QuestionInfo.QuestionLevel);

    return QuestionInfo;
}

string OperationTypeToText(short OperationType) {

    string arrOperation[5] = { "+", "-", "x", "/", "Mix"};

    return arrOperation[OperationType - 1];
}

void DisplayQuestion(strQuestionInfo Question, short NumberOfQuestions) {

    cout << "\n\nQuestion [" << Question.QuestionNumber << "/" << NumberOfQuestions << "]\n\n";
    cout << Question.FirstNumber << endl;
    cout << Question.SecondNumber << "  " << OperationTypeToText(Question.QuestionOperation) << endl;
    cout << "____________________\n";
}

strQuestionResults FillQuestionResults(strQuestionInfo QuestionInfo) {

    strQuestionResults QuestionResults;

    QuestionResults.PlayerAnswer = ReadPlayerAnswer();
    QuestionResults.QuestionAnswer = CalculateTheRightAnswer(QuestionInfo.QuestionOperation, QuestionInfo.FirstNumber, QuestionInfo.SecondNumber);
    QuestionResults.AnswerType = DefineAnswerType(QuestionResults.PlayerAnswer, QuestionResults.QuestionAnswer);

    return QuestionResults;
}

string AnswerTypeToText(enAnswerType AnswerType) {

    string arrAnswer[2] = { "Right answer :-)", "Wrong answer :-(" };

    return arrAnswer[AnswerType - 1];
}

void SetScreenColor(enAnswerType AnswerType) {

    switch (AnswerType)
    {
    case Right:
        system("color 2F");
        break;
    case Wrong:
        system("color 4F");
        break;
    }
}

void ShowTheRightAnswer(enAnswerType AnswerType, int RightAnswer) {

    if (AnswerType == enAnswerType::Wrong) {
        cout << RightAnswer;
    }
}

void ShowQuestionResults(strQuestionResults QuestionResults) {

    cout << QuestionResults.PlayerAnswer << endl;
    cout << AnswerTypeToText(QuestionResults.AnswerType) << endl;
    SetScreenColor(QuestionResults.AnswerType);
    ShowTheRightAnswer(QuestionResults.AnswerType, QuestionResults.QuestionAnswer);
}

enAnswerType PlayQuestion(short QuestionNumber, strQuizInfo QuizInfo) {

    strQuestionInfo Question;
    strQuestionResults Results;

    Question = FillQuestionInfo(QuestionNumber, QuizInfo);
    DisplayQuestion(Question, QuizInfo.NumberOfQuestions);
    Results = FillQuestionResults(Question);
    ShowQuestionResults(Results);

    return Results.AnswerType;
}

string FinalResultToText(enQuizResult FinalResult) {

    string arrFinalResult[2] = { "Pass", "Fail" };

    return arrFinalResult[FinalResult - 1];
}

string QuestionsLevelToText(short QuestionsLevel) {

    string arrLevel[4] = { "Easy", "Med", "Hard", "Mix" };

    return arrLevel[QuestionsLevel - 1];
}

void GameBeginning(strQuizInfo& QuizInfo) {

    QuizInfo.NumberOfQuestions = ReadNumberOfQuestions();
    QuizInfo.QuestionsLevel = ReadQuestionsLevel();
    QuizInfo.OperationType = ReadOperationType();
}

enQuizResult DefineFinalResult(short NumberOfRightAnswers, short NumberOfWrongAnswers) {

    if (NumberOfRightAnswers >= NumberOfWrongAnswers) {
        return enQuizResult::Pass;
    }

    return enQuizResult::Fail;
}

void PlayGame(strQuizResults& Results, strQuizInfo QuizInfo) {

    enAnswerType AnswerType;

    for (short Question = 1; Question <= QuizInfo.NumberOfQuestions; Question++) {

        AnswerType = PlayQuestion(QuizInfo.NumberOfQuestions, QuizInfo);
        if (AnswerType == enAnswerType::Right) {
            Results.NumberOfRightAnswers++;
        }
        else {
            Results.NumberOfWrongAnswers++;
        }
    }

    Results.FinalResult = DefineFinalResult(Results.NumberOfRightAnswers, Results.NumberOfWrongAnswers);
}

void DisplayFinalResultScreen(enQuizResult FinalResutlt) {

    cout << "\n_____________________________________\n";
    cout << "\nThe Final Result is: " << FinalResultToText(FinalResutlt) << endl;
    cout << "_____________________________________\n";
}

void ShowQuizResults(strQuizInfo QuizInfo, strQuizResults QuizResults) {

    cout << "Number of questions    : " << QuizInfo.NumberOfQuestions << "\n";
    cout << "Questions level        : " << QuestionsLevelToText(QuizInfo.QuestionsLevel) << "\n";
    cout << "Operation type         : " << OperationTypeToText(QuizInfo.OperationType) << "\n";
    cout << "Number of right answers: " << QuizResults.NumberOfRightAnswers << "\n";
    cout << "Number of wrong answers: " << QuizResults.NumberOfWrongAnswers << "\n";
    cout << "________________________________________\n";
}

char AskToReplay() {

    char Replay;

    cout << "\nDo you want to play again? [Y / N}";
    cin >> Replay;

    return Replay;
}

void ResetScreen() {

    system("cls");
    system("color 0F");
}

void StartGame() {

    char Replay;
    strQuizResults Results;
    strQuizInfo QuizInfo;

    do {
        ResetScreen();
        GameBeginning(QuizInfo);
        PlayGame(Results, QuizInfo);
        DisplayFinalResultScreen(Results.FinalResult);
        ShowQuizResults(QuizInfo, Results);
        Replay = AskToReplay();
    } while (Replay == 'y' || Replay == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    
    return 0;
}