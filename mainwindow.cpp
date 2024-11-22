#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QWidget>
#include <QWidgetAction>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_Add, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);

    // Connect the SubmitButton to the slot
    connect(ui->SubmitButton, &QPushButton::clicked, this, &MainWindow::onSubmitButtonclicked);

    // Initialize networkManager and connect to onQueryResult slot
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onQueryResult);

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
    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
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
    connect(DerivitiveAction, &QAction::triggered, this, [this]() {
        onTrigonometrySelected("f'(x)");
    });
    connect(LimitAction, &QAction::triggered, this, [this]() {
        onTrigonometrySelected("lim ");
    });

    ui->toolButton_Calculus->setMenu(CalculusMenu);
    ui->toolButton_Calculus->setPopupMode(QToolButton::InstantPopup);
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

void MainWindow::onSubmitButtonclicked()
{
    qDebug() << "Submit button clicked!";

    QString queryText = ui->EquationEdit->toPlainText();
    if (queryText.isEmpty()) {
        qDebug() << "Query is empty. Cannot process.";
        return;
    }

    qDebug() << "Query text: " << queryText;

    // Send the query to WolframAlpha API
    sendQueryToAPI(queryText);
}
/*
void MainWindow::onQuerySubmitted()
{
    QString queryText = ui->EquationEdit->toPlainText();

    if (queryText.isEmpty()) {
        qDebug() << "Query is empty. Cannot process.";
        return;
    }

    // For example, send the query to WolframAlpha API
    sendQueryToAPI(queryText);
}*/
void MainWindow::onQueryResult(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    // Parse the response
    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = doc.object();

    qDebug() << "Parsed JSON Document: " << doc.toJson(QJsonDocument::Indented);

    // Pass the response to the handler function
    processApiResponse(jsonObj);

    // Clean up
    reply->deleteLater();
}

void MainWindow::processApiResponse(const QJsonObject &jsonObj)
{
    // Debugging: Log the API response to check if it contains "pods"
    qDebug() << "API response contains 'pods': " << jsonObj.contains("pods");

    // Check if the WolframAlpha API returned results
    if (jsonObj.contains("queryresult") && jsonObj["queryresult"].isObject()) {
        QJsonObject queryResult = jsonObj["queryresult"].toObject();

        // Extract the result from the response
        if (queryResult.contains("pods")) {
            QJsonArray pods = queryResult["pods"].toArray();

            // Loop through each pod to find the result and the graph
            bool graphFound = false;
            for (const QJsonValue &podValue : pods) {
                QJsonObject pod = podValue.toObject();

                if (pod.contains("title") && pod["title"].toString() == "Result") {
                    if (pod.contains("subpods")) {
                        QJsonArray subpods = pod["subpods"].toArray();
                        if (!subpods.isEmpty()) {
                            QString result = subpods[0].toObject()["plaintext"].toString();
                            ui->ResultLabel->setText(result);  // Display the result
                            qDebug() << "Result: " << result;
                        }
                    }
                }

                // Check for the graph in the response
                if (pod.contains("title") && pod["title"].toString() == "Graph") {
                    graphFound = true;
                    if (pod.contains("subpods")) {
                        QJsonArray subpods = pod["subpods"].toArray();
                        if (!subpods.isEmpty()) {
                            QJsonObject imageSubpod = subpods[0].toObject();
                            QString imageUrl = imageSubpod["img"].toObject()["src"].toString();

                            // Load and display the image if a graph is found
                            displayGraph(imageUrl);
                        }
                    }
                }
            }

            // If no graph is found, hide the graph area
            if (!graphFound) {
                ui->ResultImageLabel->setVisible(false);  // Hide the graph widget if no graph is available
            }
        }
    }
}

void MainWindow::displayGraph(const QString &imageUrl) {
    QUrl url(imageUrl);
    QNetworkRequest request(url);

    QNetworkReply *imageReply = networkManager->get(request);

    connect(imageReply, &QNetworkReply::finished, this, [this, imageReply]() {
        if (imageReply->error() == QNetworkReply::NoError) {
            QByteArray imageData = imageReply->readAll();
            QImage image;
            if (image.loadFromData(imageData)) {
                ui->ResultImageLabel->setPixmap(QPixmap::fromImage(image));
                ui->ResultImageLabel->setVisible(true);  // Show image if it's loaded
            } else {
                qDebug() << "Error loading image.";
            }
        } else {
            qDebug() << "Error loading graph: " << imageReply->errorString();
        }
        imageReply->deleteLater();
    });
}
void MainWindow::sendQueryToAPI(const QString &query)
{
    // URL encode the query
    QString encodedQuery = QUrl::toPercentEncoding(query);

    // Construct the API URL
    QUrl apiUrl("https://api.wolframalpha.com/v2/query");

    // Set up query parameters
    QUrlQuery params;
    params.addQueryItem("input", encodedQuery);   // The query input (encoded)
    params.addQueryItem("appid", "3T3KQ7-9UT5PXLWH3");  // Your WolframAlpha App ID
    params.addQueryItem("format", "plaintext,image");  // Request plaintext and image formats
    params.addQueryItem("output", "JSON");  // Request JSON output

    // Set the query parameters on the URL
    apiUrl.setQuery(params);

    // Create a network request with the URL
    QNetworkRequest request(apiUrl);

    // Debugging: Log the request URL
    qDebug() << "Request URL: " << apiUrl.toString();

    // Send the request using networkManager
    networkManager->get(request);
}



