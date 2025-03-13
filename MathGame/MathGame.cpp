#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Mud = 2, Hard = 3, MixLevel = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion {
	short Number1 = 0;
	short Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short RigthAnswer = 0;
	short UserAnswer = 0;
	bool IsRightResult;
};

struct stQuizz {
	stQuestion QuestionsList[100];
	short QuestionCount = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass;
};

void ResetScreen() {
	system("cls");
	system("color 0F");
}

short ReadQuestionCount() {
	short QuestionCount = 0;

	do
	{
		cout << "How many question do you want to answer ? ";
		cin >> QuestionCount;

	} while (QuestionCount < 1 || QuestionCount > 10);

	return QuestionCount;
}

enQuestionLevel ReadQuestionLevel() {
	short NumberOfQuestionLevel = 0;

	do
	{
		cout << "Enter Question level [1] Easy, [2] Mud, [3] Hard, [4] Mix : ";
		cin >> NumberOfQuestionLevel;

	} while (NumberOfQuestionLevel < 1 || NumberOfQuestionLevel > 4);

	return (enQuestionLevel)NumberOfQuestionLevel;
}

enOperationType ReadOperationType() {
	short NumberOfOperationType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix : ";
		cin >> NumberOfOperationType;

	} while (NumberOfOperationType < 1 || NumberOfOperationType > 5);

	return (enOperationType)NumberOfOperationType;
}

short RandomNumber(short From, short To) {
	return rand() % (To - From + 1) + From;
}

enQuestionLevel GetRandomQuestionLevel() {
	return (enQuestionLevel)RandomNumber(1, 3);
}

enOperationType GetRandomOperationType() {
	return (enOperationType)RandomNumber(1, 4);
}

short SimpleCalculater(short Number1, short Number2, enOperationType OperationType) {
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return 0;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType) {
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::MixLevel)
	{
		QuestionLevel = GetRandomQuestionLevel();
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}

	Question.QuestionLevel = QuestionLevel;
	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.RigthAnswer = SimpleCalculater(Question.Number1, Question.Number2, OperationType);
		return Question;
	case enQuestionLevel::Mud:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.RigthAnswer = SimpleCalculater(Question.Number1, Question.Number2, OperationType);
		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.RigthAnswer = SimpleCalculater(Question.Number1, Question.Number2, OperationType);
		return Question;
	default:
		return Question;
	}
}

void GenerateQuizzQuestions(stQuizz& Quizz) {
	for (short QuestionNumber = 0; QuestionNumber < Quizz.QuestionCount; QuestionNumber++)
	{
		Quizz.QuestionsList[QuestionNumber] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

string GetOperationTypeSymple(enOperationType OperationType) {
	string OperationTypesSymple[5] = { "+", "-", "*", "/", "Mix" };
	return OperationTypesSymple[OperationType - 1];
}

string GetQuestionLevelName(enQuestionLevel QuestionLevel) {
	string QuestionLevelsName[4] = { "Easy", "Mud", "Hard", "Mix" };
	return QuestionLevelsName[QuestionLevel - 1];
}

void PrintQuestion(stQuizz Quizz, short QuestionNumber) {
	printf("\nQuestion [%d/%d]\n\n", QuestionNumber + 1, Quizz.QuestionCount);
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << " " << GetOperationTypeSymple(Quizz.QuestionsList[QuestionNumber].OperationType) << endl;
	cout << "_________\n";
}

short ReadUserAnswer() {
	short UserAnswer = 0;
	cin >> UserAnswer;
	return UserAnswer;
}

void SetScreenColor(bool IsRight) {
	if (IsRight)
	{
		system("color 2F");
	}
	else
	{
		cout << "\a";
		system("color 4F");
	}
}

void CheckQuestionResultAndPrintResult(stQuizz& Quizz, short QuestionNumber) {
	if (Quizz.QuestionsList[QuestionNumber].UserAnswer == Quizz.QuestionsList[QuestionNumber].RigthAnswer)
	{
		Quizz.QuestionsList[QuestionNumber].IsRightResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n\n";
	}
	else
	{
		Quizz.QuestionsList[QuestionNumber].IsRightResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-(\n";
		cout << "The right answer is : " << Quizz.QuestionsList[QuestionNumber].RigthAnswer << "\n\n";
	}
	
	SetScreenColor(Quizz.QuestionsList[QuestionNumber].IsRightResult);
}

void AskAndCurrectQuestionAnswer(stQuizz& Quizz) {
	for (short QuestionNumber = 0; QuestionNumber < Quizz.QuestionCount; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionsList[QuestionNumber].UserAnswer = ReadUserAnswer();
		CheckQuestionResultAndPrintResult(Quizz, QuestionNumber);
	}
	
	// Set the final result to the quizz, is Pass or Fail ? Depending on total of right answer count compared to wrong answer count 
	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResult(bool IsPass) {
	return IsPass ? "Pass :-)" : "Fail :-(";
}

void PrintFinalQuizzResult(stQuizz Quizz) {
	cout << "\n____________________________\n\n";
	cout << " Final Result is " << GetFinalResult(Quizz.IsPass);
	cout << "\n____________________________\n\n";
	printf("Number of questions : %d\n", Quizz.QuestionCount);
	cout << "Questions level    : " << GetQuestionLevelName(Quizz.QuestionLevel) << endl;
	cout << "Operation type     : " << GetOperationTypeSymple(Quizz.OperationType) << endl;
	printf("Number of right answers : %d\n", Quizz.NumberOfRightAnswers);
	printf("Number of wrong answers : %d\n", Quizz.NumberOfWrongAnswers);
	cout << "\n____________________________\n\n";

	SetScreenColor(Quizz.IsPass);
}

void PlayMathGame() {
	stQuizz Quizz;

	Quizz.QuestionCount = ReadQuestionCount();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCurrectQuestionAnswer(Quizz);
	PrintFinalQuizzResult(Quizz);
}

void StartGame() {
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\nDo you want play again ? (Y/N) : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}