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
#include <QFile>
#include <QImageReader>
#include <QMovie>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    //connect(ui->pushButton_Add, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);

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

    // Graph Menu
    QMenu *GraphMenu = new QMenu(this);
    QAction *GraphAction = new QAction("Graph", this);

    GraphMenu->addAction(GraphAction);

    connect(GraphAction, &QAction::triggered, this, [this]() {
        onGraphSelected("Graph");
    });

    ui->toolButton_Graph->setMenu(GraphMenu);
    ui->toolButton_Graph->setPopupMode(QToolButton::InstantPopup);


    // Symbols Menu
    QMenu *SymbolMenu = new QMenu(this);
    QAction *πAction = new QAction("π", this);
    QAction *SquareRootAction = new QAction("√()", this);

    SymbolMenu->addAction(πAction);
    SymbolMenu->addAction(SquareRootAction);

    connect(πAction, &QAction::triggered, this, [this]() {
        onGraphSelected("π");
    });
    connect(SquareRootAction, &QAction::triggered, this, [this]() {
        onGraphSelected("√()");
    });

    ui->toolButton_Symbols->setMenu(SymbolMenu);
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
    params.addQueryItem("format", "plaintext,image,latex,raw");  // Request plaintext, image, latex, and raw formats
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


void MainWindow::onQueryResult(QNetworkReply *reply)
{
    // Check for errors in the reply
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    // Get the raw JSON response
    QByteArray responseData = reply->readAll();

    // Debugging: Log the raw response data
    qDebug() << "Raw API response data:" << responseData;

    // Parse the JSON response into a QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (!doc.isObject()) {
        qDebug() << "Failed to parse JSON response.";
        reply->deleteLater();
        return;
    }

    // Convert the parsed document to a QJsonObject
    QJsonObject jsonObj = doc.object();

    // Process the API response
    processApiResponse(jsonObj);

    // Clean up the network reply
    reply->deleteLater();
}


void MainWindow::processApiResponse(const QJsonObject &jsonObj)
{
    qDebug() << "Processing API response...";

    // Check if "queryresult" object is present
    if (jsonObj.contains("queryresult")) {
        QJsonObject queryResult = jsonObj["queryresult"].toObject();

        // Check if "pods" array is present
        if (queryResult.contains("pods")) {
            QJsonArray podsArray = queryResult["pods"].toArray();

            QString plainTextResult;

            QList<QString> graphImageUrls; // To store multiple graph images

            // Iterate through the pods
            for (const QJsonValue &podValue : podsArray) {
                QJsonObject podObject = podValue.toObject();

                // Log pod titles for debugging
                if (podObject.contains("title")) {
                    qDebug() << "Pod Title: " << podObject["title"].toString();
                }

                // Extract the "Result" pod for plain text
                if (podObject.contains("title") && podObject["title"].toString() == "Result") {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();
                            if (subpodObject.contains("plaintext")) {
                                plainTextResult = subpodObject["plaintext"].toString();
                                qDebug() << "Plaintext Result: " << plainTextResult;
                            }
                        }
                    }
                }

                // Extract the "Plot" or "Plots" pod for graph images
                if (podObject.contains("title") &&
                    (podObject["title"].toString() == "Plot" || podObject["title"].toString() == "Plots")) {

                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();
                            if (subpodObject.contains("img")) {
                                QJsonObject imgObject = subpodObject["img"].toObject();
                                QString graphImageUrl = imgObject["src"].toString();
                                graphImageUrls.append(graphImageUrl);
                                qDebug() << "Graph Image URL: " << graphImageUrl;
                            }
                        }
                    }
                }
            }

            // Display the plain text result if found
            if (!plainTextResult.isEmpty()) {
                ui->ResultLabel->setText("The solution is: "+plainTextResult);
            }

            // Display all graph images if found
            if (!graphImageUrls.isEmpty()) {
                for (const QString &url : graphImageUrls) {
                    displayGraph(url); // Assuming displayGraph handles showing images
                }
            }

            // If no results, show a message
            if (plainTextResult.isEmpty() && graphImageUrls.isEmpty()) {
                qDebug() << "No usable results found in response.";
                ui->ResultLabel->setText("No results found.");
            }
        } else {
            qDebug() << "No 'pods' found in response.";
            ui->ResultLabel->setText("No results found.");
        }
    } else {
        qDebug() << "No 'queryresult' found in response.";
        ui->ResultLabel->setText("No results found.");
    }
}




void MainWindow::displayGraph(const QString &imageUrl)
{
    // Check if the image URL is valid
    qDebug() << "Displaying image from URL:" << imageUrl;

    // Create a network request to fetch the image
    QNetworkRequest request(imageUrl);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    // Connect the finished signal to a lambda function to handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // If there is no error, read the data and load the image
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            if (pixmap.loadFromData(imageData)) {
                // Successfully loaded the image
                ui->ResultImageLabel->setPixmap(pixmap);
                ui->ResultImageLabel->setScaledContents(true);  // Optionally scale the image to fit the label
                qDebug() << "Image loaded successfully!";
            } else {
                // Failed to load the image data
                qDebug() << "Failed to load image from the received data";
            }
        } else {
            // Handle error if the image failed to load
            qDebug() << "Error loading image:" << reply->errorString();
        }

        // Clean up the reply object after use
        reply->deleteLater();
    });
}


