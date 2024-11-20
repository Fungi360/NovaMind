#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QWidget>
#include <QWidgetAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_Add, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);

    setupConnections(); // Set up button connections
    setupDropdownMenus(); // Set up the dropdown menu
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Connect digit and feature buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    // Connect(ui->pushButton_Arithmetic, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    //connect(ui->pushButton_Algebra, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    //connect(ui->pushButton_Trig, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    //connect(ui->pushButton_Calculus, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    //connect(ui->pushButton_Graph, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
    //connect(ui->pushButton_Symbols, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
}

void MainWindow::setupDropdownMenus()
{
    // Arithmetic Menu
    QMenu *arithmeticMenu = new QMenu(this);
    QAction *addAction = new QAction("+", this);
    QAction *subtractAction = new QAction("-", this);
    QAction *multiplyAction = new QAction("*", this);
    QAction *divideAction = new QAction("/", this);

    arithmeticMenu->addAction(addAction);
    arithmeticMenu->addAction(subtractAction);
    arithmeticMenu->addAction(multiplyAction);
    arithmeticMenu->addAction(divideAction);

    connect(addAction, &QAction::triggered, this, [this]() {
        onArithmeticSelected("+");
    });
    connect(subtractAction, &QAction::triggered, this, [this]() {
        onArithmeticSelected("-");
    });
    connect(multiplyAction, &QAction::triggered, this, [this]() {
        onArithmeticSelected("*");
    });
    connect(divideAction, &QAction::triggered, this, [this]() {
        onArithmeticSelected("/");
    });

    ui->toolButton_Arithmetic->setMenu(arithmeticMenu);
    ui->toolButton_Arithmetic->setPopupMode(QToolButton::InstantPopup);
    qDebug() << "Menu attached to toolButton_Arithmetic!";

    // Algebra Menu
    QMenu *algebraMenu = new QMenu(this);
    QAction *solveEquationAction = new QAction("Solve Equation", this);
    QAction *factorAction = new QAction("Factor", this);
    QAction *expandAction = new QAction("Expand", this);
    QAction *simplifyAction = new QAction("Simplify", this);

    algebraMenu->addAction(solveEquationAction);
    algebraMenu->addAction(factorAction);
    algebraMenu->addAction(expandAction);
    algebraMenu->addAction(simplifyAction);

    connect(solveEquationAction, &QAction::triggered, this, [this]() {
        onAlgebraSelected("Solve Equation");
    });
    connect(factorAction, &QAction::triggered, this, [this]() {
        onAlgebraSelected("Factor");
    });
    connect(expandAction, &QAction::triggered, this, [this]() {
        onAlgebraSelected("Expand");
    });
    connect(simplifyAction, &QAction::triggered, this, [this]() {
        onAlgebraSelected("Simplify");
    });

    ui->toolButton_Algebra->setMenu(algebraMenu);
    ui->toolButton_Algebra->setPopupMode(QToolButton::InstantPopup);
    qDebug() << "Menu attached to toolButton_Algebra!";

    // Trigonometry Menu
    QMenu *trigonometryMenu = new QMenu(this);
    QAction *sinAction = new QAction("sin()", this);
    QAction *cosAction = new QAction("cos()", this);
    QAction *tanAction = new QAction("tan()", this);
    QAction *cotAction = new QAction("cot()", this);

    trigonometryMenu->addAction(sinAction);
    trigonometryMenu->addAction(cosAction);
    trigonometryMenu->addAction(tanAction);
    trigonometryMenu->addAction(cotAction);

            connect(sinAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("sin");
            });
            connect(cosAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("cos");
            });
            connect(tanAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("tan");
            });
            connect(cotAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("cot");
            });

            ui->toolButton_Trigonometry->setMenu(trigonometryMenu);
            ui->toolButton_Trigonometry->setPopupMode(QToolButton::InstantPopup);

            // Calculus Menu
            QMenu *CalculusMenu = new QMenu(this);
            QAction *IntegralAction = new QAction("∫() dx", this);
            QAction *DefiniteIntegralAction = new QAction("∫() from () to ()dx", this);
            QAction *SummationAction = new QAction("∑", this);
            QAction *DerivitiveAction = new QAction("f'(x)", this);
             QAction *LimitAction = new QAction("lim ", this);

            CalculusMenu->addAction(IntegralAction);
            CalculusMenu->addAction(DefiniteIntegralAction);
            CalculusMenu->addAction(SummationAction);
            CalculusMenu->addAction(DerivitiveAction);
            CalculusMenu->addAction(LimitAction);

            connect(IntegralAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("∫() dx");
            });
            connect(DefiniteIntegralAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("∫() from () to ()dx");
            });
            connect(SummationAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("∑");
            });
            connect(LimitAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("lim");
            });
            connect(DerivitiveAction, &QAction::triggered, this, [this]() {
                onTrigonometrySelected("f'(x)");});

            ui->toolButton_Calculus->setMenu(CalculusMenu);
            ui->toolButton_Calculus->setPopupMode(QToolButton::InstantPopup);

            // Graph Menu
            QMenu *graphMenu = new QMenu(this);
            QAction *graph2DAction = new QAction("2D Graph", this);
            QAction *graph3DAction = new QAction("3D Graph", this);

            graphMenu->addAction(graph2DAction);
            graphMenu->addAction(graph3DAction);


            connect(graph2DAction, &QAction::triggered, this, [this]() {
                onGraphSelected("2D Plot");
            });
            connect(graph3DAction, &QAction::triggered, this, [this]() {
                onGraphSelected("3D Plot"); });


            ui->toolButton_Graph->setMenu(graphMenu);
            ui->toolButton_Graph->setPopupMode(QToolButton::InstantPopup);

            QMenu *symbolMenu = new QMenu(this);

            // Create actions for common math symbols
            QAction *piAction = new QAction("π", this);
            QAction *sqrtAction = new QAction("√", this);
            QAction *infinityAction = new QAction("∞", this);
            QAction *plusMinusAction = new QAction("±", this);
            QAction *degreeAction = new QAction("°", this);

            // Add actions to the menu
            symbolMenu->addAction(piAction);
            symbolMenu->addAction(sqrtAction);
            symbolMenu->addAction(infinityAction);
            symbolMenu->addAction(plusMinusAction);
            symbolMenu->addAction(degreeAction);

            // Connect actions to the onSymbolSelected slot
            connect(piAction, &QAction::triggered, this, [this]() {
                onSymbolSelected("π");
            });
            connect(sqrtAction, &QAction::triggered, this, [this]() {
                onSymbolSelected("√");
            });
            connect(infinityAction, &QAction::triggered, this, [this]() {
                onSymbolSelected("∞");
            });
            connect(plusMinusAction, &QAction::triggered, this, [this]() {
                onSymbolSelected("±");
            });
            connect(degreeAction, &QAction::triggered, this, [this]() {
                onSymbolSelected("°");
            });

            // Attach the menu to a tool button (for math symbols)
            ui->toolButton_Symbols->setMenu(symbolMenu);
            ui->toolButton_Symbols->setPopupMode(QToolButton::InstantPopup);
}

void MainWindow::onDigitButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString currentText = ui->EquationEdit->toPlainText();
        currentText += button->text();
        ui->EquationEdit->setText(currentText);
    }
}

void MainWindow::onOperatorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString operatorSymbol = button->text();
        qDebug() << "Operator clicked:" << operatorSymbol;
        ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operatorSymbol + " ");
    }
}

void MainWindow::onArithmeticSelected(const QString &operation)
{
    qDebug() << "Arithmetic Selected operation: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
void MainWindow::onCalculusSelected(const QString &operation)
{
    qDebug() << "Arithmetic Selected operation: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
void MainWindow::onAlgebraSelected(const QString &operation)
{
    qDebug() << "Algebra operation selected: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
void MainWindow::onTrigonometrySelected(const QString &operation)
{
    qDebug() << "Trigonometry Selected operation: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
void MainWindow::onGraphSelected(const QString &operation)
{
    qDebug() << "Graph Selected operation: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
void MainWindow::onSymbolSelected(const QString &operation)
{
    qDebug() << "Symbol Selected operation: " << operation;
    ui->EquationEdit->setText(ui->EquationEdit->toPlainText() + " " + operation + " ");
}
