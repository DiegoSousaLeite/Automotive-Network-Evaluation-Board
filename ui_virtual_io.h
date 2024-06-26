#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QPixmap>

#ifndef UI_VIRTUAL_IO_H
#define UI_VIRTUAL_IO_H

QT_BEGIN_NAMESPACE

// Definition of the Ui_Virtual_IO class that constructs the UI for Virtual_IO widget
class Ui_Virtual_IO
{
public:
    //QFrame
    QFrame *line_11;
    QFrame *line_12;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;

    //QTextBrowser
    QTextBrowser *textBrowser_5;
    QTextBrowser *textBrowser_2;

    //Table Widget
    QTableWidget *tableWidget;

    //QLineEdit
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;

    //QTextBrowser
    QTextBrowser *textBrowser_3;
    QTextBrowser *textBrowser_4;

    //QPushButton
    QPushButton *ecu1Button;
    QPushButton *ecu2Button;
    QPushButton *ecu3Button;
    QPushButton *ecu4Button;
    QPushButton *sendAllButton;
    QPushButton *din1Button;
    QPushButton *din2Button;
    QPushButton *din4Button;
    QPushButton *din3Button;
    QPushButton *ain1Button;
    QPushButton *ain2Button;
    QPushButton *ain3Button;
    QPushButton *ain4Button;
    QPushButton *ecuConectButton;
    QPushButton *virtualInputButton;

    //QSlider
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;

    //QLabel
    QLabel *imagePlaca;
    QLabel *imageDin1;
    QLabel *imageDin2;
    QLabel *imageDin3;
    QLabel *imageDin4;
    QLabel *imageAin1;
    QLabel *imageAin2;
    QLabel *imageAin3;
    QLabel *imageAin4;


    // Function to setup the UI inside a given QWidget container
    void setupUi(QWidget *Virtual_IO)
    {
        if (Virtual_IO->objectName().isEmpty())
            Virtual_IO->setObjectName("Virtual_IO");


        // Configuration for vertical and horizontal lines to structure the layout
        line_11 = new QFrame(Virtual_IO);
        line_11->setObjectName("line_11");
        line_11->setGeometry(QRect(10, 70, 3, 380));
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);

        line_12 = new QFrame(Virtual_IO);
        line_12->setObjectName("line_12");
        line_12->setGeometry(QRect(550, 70, 3, 380));
        line_12->setFrameShape(QFrame::VLine);
        line_12->setFrameShadow(QFrame::Sunken);

        line_5 = new QFrame(Virtual_IO);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(10, 450, 540, 3));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        line_6 = new QFrame(Virtual_IO);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(10, 70, 540, 3));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        line_7 = new QFrame(Virtual_IO);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(575, 70, 3, 380));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        line_8 = new QFrame(Virtual_IO);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(1060, 70, 3, 380));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        line_9 = new QFrame(Virtual_IO);
        line_9->setObjectName("line_9");
        line_9->setGeometry(QRect(575, 70, 485, 3));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        line_10 = new QFrame(Virtual_IO);
        line_10->setObjectName("line_10");
        line_10->setGeometry(QRect(575, 450, 485, 3));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        imagePlaca = new QLabel(Virtual_IO);
        QPixmap pixmap("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/placa_remove_bg.png");
        imagePlaca->setPixmap(pixmap);
        imagePlaca->setGeometry(300, 85, 250, 250);
        imagePlaca->setScaledContents(true);

        imageDin1 = new QLabel(Virtual_IO);
        QPixmap pixmap1("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/botao.png");
        imageDin1->setPixmap(pixmap1);
        imageDin1->setGeometry(30, 80, 60, 60);
        imageDin1->setScaledContents(true);

        imageDin2 = new QLabel(Virtual_IO);
        QPixmap pixmap2("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/botao.png");
        imageDin2->setPixmap(pixmap2);
        imageDin2->setGeometry(100, 80, 60, 60);
        imageDin2->setScaledContents(true);

        imageDin3 = new QLabel(Virtual_IO);
        QPixmap pixmap3("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/botao.png");
        imageDin3->setPixmap(pixmap3);
        imageDin3->setGeometry(170, 80, 60, 60);
        imageDin3->setScaledContents(true);

        imageDin4 = new QLabel(Virtual_IO);
        QPixmap pixmap4("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/botao.png");
        imageDin4->setPixmap(pixmap4);
        imageDin4->setGeometry(240, 80, 60, 60);
        imageDin4->setScaledContents(true);

        imageAin1 = new QLabel(Virtual_IO);
        QPixmap pixmap5("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/potentiometer.png");
        imageAin1->setPixmap(pixmap5);
        imageAin1->setGeometry(30, 200, 60, 60);
        imageAin1->setScaledContents(true);

        imageAin2 = new QLabel(Virtual_IO);
        QPixmap pixmap6("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/potentiometer.png");
        imageAin2->setPixmap(pixmap6);
        imageAin2->setGeometry(100, 200, 60, 60);
        imageAin2->setScaledContents(true);

        imageAin3 = new QLabel(Virtual_IO);
        QPixmap pixmap7("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/potentiometer.png");
        imageAin3->setPixmap(pixmap7);
        imageAin3->setGeometry(170, 200, 60, 60);
        imageAin3->setScaledContents(true);

        imageAin4 = new QLabel(Virtual_IO);
        QPixmap pixmap8("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/potentiometer.png");
        imageAin4->setPixmap(pixmap8);
        imageAin4->setGeometry(240, 200, 60, 60);
        imageAin4->setScaledContents(true);


        // Configuration of QTextBrowsers for displaying static texts
        textBrowser_5 = new QTextBrowser(Virtual_IO);
        textBrowser_5->setObjectName("textBrowser");
        textBrowser_5->setGeometry(QRect(10, 50, 141, 31));
        textBrowser_5->setStyleSheet("background-color: transparent;");


        textBrowser_2 = new QTextBrowser(Virtual_IO);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(580, 50, 181, 31));
        textBrowser_2->setStyleSheet("background-color: transparent;");


        textBrowser_3 = new QTextBrowser(Virtual_IO);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(600, 300, 141, 31));
        textBrowser_3->setStyleSheet("background-color: transparent;");


        textBrowser_4 = new QTextBrowser(Virtual_IO);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(580, 70, 141, 31));
        textBrowser_4->setStyleSheet("background-color: transparent;");

        // Configuration of QLineEdits for user input
        lineEdit = new QLineEdit(Virtual_IO);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(600, 330, 260, 21));

        lineEdit_2 = new QLineEdit(Virtual_IO);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(600, 360, 260, 21));

        lineEdit_3 = new QLineEdit(Virtual_IO);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(600, 390, 260, 21));

        lineEdit_4 = new QLineEdit(Virtual_IO);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(600, 420, 260, 21));

        // Configuration of QTableWidget to display a table of items with checkable boxes
        tableWidget = new QTableWidget(Virtual_IO);
        int numRows = 4; // Define the number of rows in the table
        int numCols = 9; // Define the number of columns in the table
        tableWidget->setRowCount(numRows); // Set the total rows
        tableWidget->setColumnCount(numCols); // Set the total columns
        tableWidget->setObjectName("tableWidget"); // Set the name for object identification
        tableWidget->setGeometry(QRect(590, 100, 451, 145)); // Set the size and position of the table within the parent widget
        tableWidget->setSortingEnabled(false); // Disable sorting to maintain manual order
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false); // Prevent cascading size changes when adjusting one section

        QStringList horizontalHeaders{"N°", "DIN#1", "DIN#2", "DIN#3", "DIN#4", "AIN#1", "AIN#2", "AIN#3", "AIN#4"};
        QStringList verticalHeaders{"ECU#1", "ECU#2", "ECU#3", "ECU#4"};

        // Setting horizontal headers from predefined list
        for (int col = 0; col < numCols; ++col) {
            tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(horizontalHeaders[col]));
        }

        // Setting vertical headers from predefined list
        for (int row = 0; row < numRows; ++row) {
            tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(verticalHeaders[row]));
        }

        // Adding checkable items to each cell in the table
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setCheckState(Qt::Unchecked); // Initial state set to unchecked

                // Center align the checkbox within the cell for better visual appearance
                item->setTextAlignment(Qt::AlignCenter);

                // Make the item not editable but allow checkbox state change
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                tableWidget->setItem(row, col, item); // Place the item in the table at the specified row and column
            }
        }

        // Set custom styles for the table to enhance appearance
        tableWidget->setStyleSheet("QTableWidget { background: transparent; }"
                                   "QTableWidget::item { border-bottom: 1px solid white; border-right: 1px solid white; }"
                                   "QHeaderView::section { background-color: transparent; border: 1px solid white; }");

        // Enable horizontal stretching to ensure all columns resize evenly as the widget resizes
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


        // Configuration of QPushButtons for various user interactions
        ecu1Button = new QPushButton(Virtual_IO);
        ecu1Button->setObjectName("ecu1Button");
        ecu1Button->setGeometry(QRect(870, 330, 100, 21));

        ecu2Button = new QPushButton(Virtual_IO);
        ecu2Button->setObjectName("ecu2Button");
        ecu2Button->setGeometry(QRect(870, 360, 100, 21));

        ecu3Button = new QPushButton(Virtual_IO);
        ecu3Button->setObjectName("ecu3Button");
        ecu3Button->setGeometry(QRect(870, 390, 100, 21));

        ecu4Button = new QPushButton(Virtual_IO);
        ecu4Button->setObjectName("ecu4Button");
        ecu4Button->setGeometry(QRect(870, 420, 100, 21));

        sendAllButton = new QPushButton(Virtual_IO);
        sendAllButton->setObjectName("sendAllButton");
        sendAllButton->setGeometry(QRect(980, 330, 71, 111));

        din1Button = new QPushButton(Virtual_IO);
        din1Button->setObjectName("din1Button");
        din1Button->setGeometry(QRect(30, 130, 60, 32));

        din2Button = new QPushButton(Virtual_IO);
        din2Button->setObjectName("din2Button");
        din2Button->setGeometry(QRect(100, 130, 60, 32));

        din3Button = new QPushButton(Virtual_IO);
        din3Button->setObjectName("din3Button");
        din3Button->setGeometry(QRect(170, 130, 60, 32));

        din4Button = new QPushButton(Virtual_IO);
        din4Button->setObjectName("din4Button");
        din4Button->setGeometry(QRect(240, 130, 60, 32));

        ain1Button = new QPushButton(Virtual_IO);
        ain1Button->setObjectName("ain1Button");
        ain1Button->setGeometry(QRect(260, 280, 51, 32));

        ain2Button = new QPushButton(Virtual_IO);
        ain2Button->setObjectName("ain2Button");
        ain2Button->setGeometry(QRect(260, 360, 51, 32));

        ain3Button = new QPushButton(Virtual_IO);
        ain3Button->setObjectName("ain3Button");
        ain3Button->setGeometry(QRect(260, 320, 51, 32));

        ain4Button = new QPushButton(Virtual_IO);
        ain4Button->setObjectName("ain4Button");
        ain4Button->setGeometry(QRect(260, 400, 51, 32));

        ecuConectButton = new QPushButton(Virtual_IO);
        ecuConectButton->setObjectName("ecuConectButton");
        ecuConectButton->setGeometry(QRect(340, 330, 170, 32));

        virtualInputButton = new QPushButton(Virtual_IO);
        virtualInputButton->setObjectName("virtualInputButton");
        virtualInputButton->setGeometry(QRect(340, 370, 170, 32));

        // Configuration of QSliders for user-adjustable settings
        horizontalSlider = new QSlider(Virtual_IO);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(50, 280, 200, 25));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalSlider_2 = new QSlider(Virtual_IO);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(50, 320, 200, 25));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalSlider_3 = new QSlider(Virtual_IO);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(50, 360, 200, 25));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalSlider_4 = new QSlider(Virtual_IO);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(50, 400, 200, 25));
        horizontalSlider_4->setOrientation(Qt::Horizontal);



        retranslateUi(Virtual_IO);

        QMetaObject::connectSlotsByName(Virtual_IO);
    } // setupUi

    // Function to translate UI components' texts based on the application's current language settings
    void retranslateUi(QWidget *Virtual_IO)
    {
        // Set the HTML content for text browsers that include dynamic translations for text
        Virtual_IO->setWindowTitle(QCoreApplication::translate("Virtual_IO", "Form", nullptr));
        textBrowser_5->setHtml(QCoreApplication::translate("Virtual_IO", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                       "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                       "p, li { white-space: pre-wrap; }\n"
                                                                       "hr { height: 1px; border-width: 0; }\n"
                                                                       "li.unchecked::marker { content: \"\\2610\"; }\n"
                                                                       "li.checked::marker { content: \"\\2612\"; }\n"
                                                                       "</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                                                                       "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Virtual Input:</p></body></html>", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("Virtual_IO", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                         "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                         "p, li { white-space: pre-wrap; }\n"
                                                                         "hr { height: 1px; border-width: 0; }\n"
                                                                         "li.unchecked::marker { content: \"\\2610\"; }\n"
                                                                         "li.checked::marker { content: \"\\2612\"; }\n"
                                                                         "</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                                                                         "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Virtual I/O Configuration:</p></body></html>", nullptr));
        textBrowser_3->setHtml(QCoreApplication::translate("Virtual_IO", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                         "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                         "p, li { white-space: pre-wrap; }\n"
                                                                         "hr { height: 1px; border-width: 0; }\n"
                                                                         "li.unchecked::marker { content: \"\\2610\"; }\n"
                                                                         "li.checked::marker { content: \"\\2612\"; }\n"
                                                                         "</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                                                                         "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU# Send Data:</p></body></html>", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("Virtual_IO", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                         "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                         "p, li { white-space: pre-wrap; }\n"
                                                                         "hr { height: 1px; border-width: 0; }\n"
                                                                         "li.unchecked::marker { content: \"\\2610\"; }\n"
                                                                         "li.checked::marker { content: \"\\2612\"; }\n"
                                                                         "</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                                                                         "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU# Pin Mapping:</p></body></html>", nullptr));

        // Update table headers with translated text
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Virtual_IO", "N\302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Virtual_IO", "DIN#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Virtual_IO", "DIN#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Virtual_IO", "DIN#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Virtual_IO", "DIN#4", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Virtual_IO", "AIN#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Virtual_IO", "AIN#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Virtual_IO", "AIN#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Virtual_IO", "AIN#4", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("Virtual_IO", "ECU#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("Virtual_IO", "ECU#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("Virtual_IO", "ECU#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("Virtual_IO", "ECU#4", nullptr));

        // Update push buttons with translated text
        ecu1Button->setText(QCoreApplication::translate("Virtual_IO", "ECU#1 Send", nullptr));
        ecu2Button->setText(QCoreApplication::translate("Virtual_IO", "ECU#2 Send", nullptr));
        ecu3Button->setText(QCoreApplication::translate("Virtual_IO", "ECU#3 Send", nullptr));
        ecu4Button->setText(QCoreApplication::translate("Virtual_IO", "ECU#4 Send", nullptr));
        sendAllButton->setText(QCoreApplication::translate("Virtual_IO", "Send All", nullptr));
        din1Button->setText(QCoreApplication::translate("Virtual_IO", "DIN#1", nullptr));
        din2Button->setText(QCoreApplication::translate("Virtual_IO", "DIN#2", nullptr));
        din3Button->setText(QCoreApplication::translate("Virtual_IO", "DIN#3", nullptr));
        din4Button->setText(QCoreApplication::translate("Virtual_IO", "DIN#4", nullptr));
        ain1Button->setText(QCoreApplication::translate("Virtual_IO", "AIN#1", nullptr));
        ain2Button->setText(QCoreApplication::translate("Virtual_IO", "AIN#3", nullptr));
        ain3Button->setText(QCoreApplication::translate("Virtual_IO", "AIN#2", nullptr));
        ain4Button->setText(QCoreApplication::translate("Virtual_IO", "AIN#4", nullptr));
        ecuConectButton->setText(QCoreApplication::translate("Virtual_IO", "ECUs Connection", nullptr));
        virtualInputButton->setText(QCoreApplication::translate("Virtual_IO", "Virtual Input (Default Test)", nullptr));
    } // retranslateUi

};

namespace Ui {
class Virtual_IO: public Ui_Virtual_IO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUAL_IO_H
