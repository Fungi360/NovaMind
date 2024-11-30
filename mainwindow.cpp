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


//test comment

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the SubmitButton to the slot
    connect(ui->SubmitButton, &QPushButton::clicked, this, &MainWindow::onSubmitButtonclicked);

    // Initialize networkManager and connect to onQueryResult slot
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onQueryResult);

    QFrame *Frame = ui->Frame; //Adds mouse tracking in .ui
    Frame->setMouseTracking(true);//enabled mouse tracking

    // Setup connections for buttons and dropdowns
    setupConnections();
    setupDropdownMenus();
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
    //qDebug() << "Menu attached to toolButton_Arithmetic!";

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
    //qDebug() << "Menu attached to toolButton_Algebra!";

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
    qDebug() << "Calculus Selected operation: " << operation;
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

void MainWindow::onSubmitButtonclicked() {
    qDebug() << "Submit button clicked!";

    QString queryText = ui->EquationEdit->toPlainText();
    if (queryText.isEmpty()) {
        qDebug() << "Query is empty. Cannot process.";
        return;
    }

    qDebug() << "Query text: " << queryText;

    // Send the query to WolframAlpha API
    sendQueryToAPI(queryText, 0); // Start from index 0 for the first query
}

// Function to send the query to the WolframAlpha API
void MainWindow::sendQueryToAPI(const QString &query, int index)
{
    // Split the query into parts based on commas
    QStringList queries = query.split(',');

    // Filter out any empty query parts (e.g., if there are consecutive commas)
    queries.removeAll("");

    // Check if the list is empty after removing empty parts
    if (queries.isEmpty()) {
        qDebug() << "No valid queries found.";
        return;
    }

    // If there's only one query, execute it once
    if (queries.size() == 1) {
        sendSingleQuery(queries.first());
    } else {
        // Otherwise, process each query in the list using the index
        for (int i = index; i < queries.size(); ++i) {
            sendSingleQuery(queries[i]);
        }
    }
}

void MainWindow::sendSingleQuery(const QString &query)
{

    QString processedQuery = query;
    processedQuery.replace("∫", "integral ");
    processedQuery.replace("∑", "sum ");
    processedQuery.replace("lim", "limit ");
    processedQuery.replace("dx", " dx");
    processedQuery.replace("f'(x)", "derivative ");

    // URL encode the query
    QString encodedQuery = QUrl::toPercentEncoding(query);

    // Construct the API URL
    QUrl apiUrl("https://api.wolframalpha.com/v2/query");

    // Set up query parameters with your API key
    QUrlQuery params;
    params.addQueryItem("input", encodedQuery);
    params.addQueryItem("appid", "3T3KQ7-9UT5PXLWH3");  // Wolfram Alpha App ID
    params.addQueryItem("format", "plaintext,image,latex,raw"); //Format to return from API
    params.addQueryItem("output", "JSON"); //Desired Output

    // Set the query parameters on the URL
    apiUrl.setQuery(params);

    // Create a network request with the URL
    QNetworkRequest request(apiUrl);

    // Debugging: Log the request URL
    qDebug() << "Request URL: " << apiUrl.toString();

    // Send the request using networkManager
    QNetworkReply *reply = networkManager->get(request);

    // Handle the reply once it's finished
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        // Print out the raw response data for debugging
        QByteArray rawData = reply->readAll();
        qDebug() << "Raw Response: " << rawData;

        // Parse the JSON response if it's valid
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(rawData);
            if (!doc.isNull()) {
                QJsonObject jsonObj = doc.object();
                this->processApiResponse(jsonObj);  // Process the valid JSON response
            } else {
                qDebug() << "Invalid JSON response.";
            }
        } else {
            qDebug() << "Error in network request: " << reply->errorString();
        }

        // Clean up the reply object
        reply->deleteLater();
    });
}


// Slot to handle the query result when finished
void MainWindow::onQueryResult() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) {
        qDebug() << "Failed to get QNetworkReply from sender!";
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (!doc.isObject()) {
        qDebug() << "Invalid JSON response.";
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObj = doc.object();
    processApiResponse(jsonObj);
    reply->deleteLater();
}


// Function to process the WolframAlpha API response
void MainWindow::processApiResponse(const QJsonObject &jsonObj)
{
    // Check if the response is valid and contains the expected 'queryresult' object
    if (jsonObj.isEmpty()) {
        qDebug() << "Invalid or empty JSON response!";
        ui->ResultLabel->setText("Invalid or empty response received.");
        return;
    }


    if (jsonObj.contains("queryresult")) {
        QJsonObject queryResult = jsonObj["queryresult"].toObject();

        if (queryResult.contains("pods")) {
            QJsonArray podsArray = queryResult["pods"].toArray();

            QString plainTextResult;
            QString derivativeResult;
            QString indefiniteIntegralResult;
            QString definiteIntegralResult;
            QString factoringResult;
            QList<QString> graphImageUrls; // To store graph images

            for (const QJsonValue &podValue : podsArray) {
                QJsonObject podObject = podValue.toObject();
                QString podTitle = podObject["title"].toString();
                QString podId = podObject["id"].toString();


                // Handle "Indefinite integral" pod
                if (podId == "IndefiniteIntegral" && indefiniteIntegralResult.isEmpty()) {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        if (!subpodsArray.isEmpty()) {
                            QJsonObject subpodObject = subpodsArray[0].toObject();
                            if (subpodObject.contains("plaintext")) {
                                indefiniteIntegralResult = subpodObject["plaintext"].toString();
                                qDebug() << "IndefiniteIntegral Result: " << indefiniteIntegralResult;
                            }
                        }
                    }
                }

                // Handle "Definite integral" pod
                if (podTitle == "Definite integral" && definiteIntegralResult.isEmpty()) {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        if (!subpodsArray.isEmpty()) {
                            QJsonObject subpodObject = subpodsArray[0].toObject();
                            if (subpodObject.contains("plaintext")) {
                                definiteIntegralResult = subpodObject["plaintext"].toString();
                                qDebug() << "DefiniteIntegral Result: " << definiteIntegralResult;
                            }
                        }
                    }
                }


                // Handle "Derivative" pod
                if (podId == "Derivative" && derivativeResult.isEmpty()) {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        if (!subpodsArray.isEmpty()) {
                            QJsonObject subpodObject = subpodsArray[0].toObject();
                            if (subpodObject.contains("plaintext")) {
                                QString resultText = subpodObject["plaintext"].toString();
                                qDebug() << "Raw Derivative Result: " << resultText;

                                // Cleanup logic for derivative result
                                if (resultText.contains("=")) {
                                    // Extract the portion after '='
                                    int equalsIndex = resultText.indexOf('=');
                                    QString rhs = resultText.mid(equalsIndex + 1).trimmed();

                                    // Remove unnecessary terms like "f''(x^2)"
                                    int unwantedIndex = rhs.indexOf("f''");
                                    if (unwantedIndex != -1) {
                                        rhs = rhs.left(unwantedIndex).trimmed(); // Take only the part before "f''"
                                    }

                                    resultText = rhs; // Update resultText with the cleaned RHS
                                }

                                qDebug() << "Cleaned Derivative Result: " << resultText;
                                derivativeResult = resultText; // Set the cleaned result
                            }
                        }
                    }
                }

                // Handle "Result" pod for factoring
                if (podTitle == "Result" && factoringResult.isEmpty()) {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        if (!subpodsArray.isEmpty()) {
                            QJsonObject subpodObject = subpodsArray[0].toObject();
                            if (subpodObject.contains("plaintext")) {
                                factoringResult = subpodObject["plaintext"].toString();
                                qDebug() << "Factoring Result: " << factoringResult;
                            }
                        }
                    }
                }


                // Handle graph images
                if (podTitle.contains("Plot") || podTitle.contains("Visual representation")) {
                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();
                            if (subpodObject.contains("img")) {
                                QString graphImageUrl = subpodObject["img"].toObject()["src"].toString();
                                graphImageUrls.append(graphImageUrl);
                                qDebug() << "Graph Image URL: " << graphImageUrl;
                            }
                        }
                    }
                }
            }

            // Display results based on priority
            if (!factoringResult.isEmpty()) {
                ui->ResultLabel->setText("The factored form is: " + factoringResult);
            } else if (!definiteIntegralResult.isEmpty()) {
                ui->ResultLabel->setText("The definite integral is: " + definiteIntegralResult);
            } else if (!indefiniteIntegralResult.isEmpty()) {
                ui->ResultLabel->setText("The indefinite integral is: " + indefiniteIntegralResult);
            } else if (!derivativeResult.isEmpty()) {
                ui->ResultLabel->setText("The derivative is: " + derivativeResult);
            } else {
                ui->ResultLabel->setText("No results found.");
                qDebug() << "No usable results found in response.";
            }

            // Display graph images if available
            if (!graphImageUrls.isEmpty()) {
                for (const QString &url : graphImageUrls) {
                    displayGraph(url);
                }
            }
        } else {
            qDebug() << "No 'pods' found in response.";
            ui->ResultLabel->setText("No results found.");

            if (!jsonObj.contains("queryresult")) {
                qDebug() << "No 'queryresult' found in the response.";
                ui->ResultLabel->setText("No results found.");
                return;
            }

            QJsonObject queryResult = jsonObj["queryresult"].toObject();

            // Check if "pods" array is present
            if (!queryResult.contains("pods")) {
                qDebug() << "No 'pods' found in response.";
                ui->ResultLabel->setText("No results found.");
                return;
            }

            QJsonArray podsArray = queryResult["pods"].toArray();

            QString plainTextResult;
            QList<QString> graphImageUrls; // To store multiple graph images
            QString trigResult; // For storing trigonometric results
            QString calcResult; // For storing calculus-related results

            // Iterate through the pods
            for (const QJsonValue &podValue : podsArray) {
                QJsonObject podObject = podValue.toObject();

                // Log pod titles for debugging
                if (podObject.contains("title")) {
                    qDebug() << "Pod Title: " << podObject["title"].toString();

                }

                // Extract the "Result" pod for plain text solution
                if (podObject.contains("title") && podObject["title"].toString().contains("Result", Qt::CaseInsensitive)) {
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

                // Extract graph images from plot-related pods only
                if (podObject.contains("title") && (
                        podObject["title"].toString().contains("Plot", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Implicit Plot", Qt::CaseInsensitive))) {

                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();

                            // Check if there is an image in the subpod
                            if (subpodObject.contains("img")) {
                                QJsonObject imgObject = subpodObject["img"].toObject();
                                QString graphImageUrl = imgObject["src"].toString();
                                QString graphTitle = imgObject["alt"].toString();

                                // Only add graphs related to the plot
                                if (!graphImageUrl.isEmpty() && graphTitle.contains("plot", Qt::CaseInsensitive)) {
                                    graphImageUrls.append(graphImageUrl);
                                    qDebug() << "Graph Image URL: " << graphImageUrl;
                                }
                            }
                        }
                    }
                }

                // Check for Trigonometric Results
                if (podObject.contains("title") && (
                        podObject["title"].toString().contains("Trig", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Sine", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Cosine", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Tangent", Qt::CaseInsensitive))) {

                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();
                            if (subpodObject.contains("plaintext")) {
                                trigResult = subpodObject["plaintext"].toString();
                                qDebug() << "Trigonometric Result: " << trigResult;
                            }
                        }
                    }
                }

                // Check for Calculus-related Results (Integrals, Derivatives, Limits, Summations)
                if (podObject.contains("title") && (
                        podObject["title"].toString().contains("Integral", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Derivative", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Summation", Qt::CaseInsensitive) ||
                        podObject["title"].toString().contains("Limit", Qt::CaseInsensitive))) {

                    if (podObject.contains("subpods")) {
                        QJsonArray subpodsArray = podObject["subpods"].toArray();
                        for (const QJsonValue &subpodValue : subpodsArray) {
                            QJsonObject subpodObject = subpodValue.toObject();
                            if (subpodObject.contains("plaintext")) {
                                calcResult = subpodObject["plaintext"].toString();
                                qDebug() << "Calculus Result: " << calcResult;
                            }
                        }
                    }
                }
            }

            // Display the plain text result if found
            if (!plainTextResult.isEmpty()) {
                ui->ResultLabel->setText("The solution is: " + plainTextResult);
            }

            // Display all relevant graph images if found
            if (!graphImageUrls.isEmpty()) {
                for (const QString &url : graphImageUrls) {
                    displayGraph(url); // Assuming displayGraph handles showing images
                }
            }

            // Display the trigonometric result if found
            if (!trigResult.isEmpty()) {
                ui->ResultLabel->setText("Trigonometric result: " + trigResult);
            }

            // Display the calculus result if found
            if (!calcResult.isEmpty()) {
                ui->ResultLabel->setText("Calculus result: " + calcResult);
            }

            // If no results, show a message
            if (plainTextResult.isEmpty() && graphImageUrls.isEmpty() && trigResult.isEmpty() && calcResult.isEmpty()) {
                qDebug() << "No usable results found in response.";
                ui->ResultLabel->setText("No results found.");
            }
        }
    }
}


void MainWindow::displayGraph(const QString &imageUrl)
{
    // Function to display the graph from a URL

    // Check if the image URL is valid
    qDebug() << "Displaying image from URL:" << imageUrl;

    // Create a network request to fetch the image
    QNetworkRequest request(imageUrl);

    // Create QNetworkAccessManager as a member of the MainWindow to avoid creating it repeatedly
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Send the request to fetch the image
    QNetworkReply *reply = manager->get(request);

    // Connect the finished signal to a lambda function to handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply, manager]() {
        // Ensure the network manager stays alive until the reply is finished
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

        // Clean up the manager object after use (optional, depends on your needs)
        manager->deleteLater();
    });
}


QString MainWindow::convertTextToNumber(const QString &text) {
    static const QMap<QString, QString> numberMap = {
        {"zero", "0"},
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"},
        {"ten", "10"}
    };

    return numberMap.value(text.toLower(), text);
}
