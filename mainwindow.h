#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Constructor
    ~MainWindow(); // Destructor


private slots:
    void onDigitButtonClicked(); // Slot for digit buttons
    void onOperatorButtonClicked(); // Slot for operators
    void onArithmeticSelected(const QString &operation); // Slot for dropdown menu actions
    void onAlgebraSelected(const QString &operation); // Slot for dropdown menu actions
    void onTrigonometrySelected(const QString &operation);  // Trigonometry slot
    void onCalculusSelected(const QString &operation);  // Calculus slot
    void onGraphSelected(const QString &operation);  // Graph slot
    void onSymbolSelected(const QString &symbol);
    void onQueryResult(QNetworkReply *reply);  // Slot for handling API responses
    void onSubmitButtonclicked();// Slot for submitting queries
    void displayGraph(const QString &imageUrl); // Display the graph image

 private:
    Ui::MainWindow *ui;
    void setupConnections(); // Helper to connect signals to slots
    void setupDropdownMenus(); // Set up dropdown menus
    QNetworkAccessManager *networkManager;
    void sendQueryToAPI(const QString &query);
    void processApiResponse(const QJsonObject &jsonObj); // Method for processing API response

};
#endif // MAINWINDOW_H
