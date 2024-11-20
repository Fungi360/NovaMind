#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include <QAction>
#include <QDebug>

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
  //  void onCalculusSelected(const QString &operation);  // Trigonometry slot
   // void onSymbolsSelected(const QString &operation);  // Trigonometry slot

private:
    Ui::MainWindow *ui;
    void setupConnections(); // Helper to connect signals to slots
    void setupDropdownMenus(); // Set up dropdown menus
};

#endif // MAINWINDOW_H
