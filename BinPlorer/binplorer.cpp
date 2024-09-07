#include "binplorer.h"
#include "ui_binplorer.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QClipboard>

#include "binary.h"

BinPlorer::BinPlorer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BinPlorer)
{
    ui->setupUi(this);

    // initialize bfd
    bfd_init();

    // We need to display the 'about binplorer' to the user when the button under the Help menu is clicked
    // This sends a siggnal to the about_binplorer function to handle it.
    connect(ui->actionAbout_BinPlorer, &QAction::triggered, this, &BinPlorer::about_binplorer);
}

BinPlorer::~BinPlorer()
{
    delete ui;
}

void BinPlorer::about_binplorer()
{
    // Create a QMessageBox to display the About section
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About BinEx");

    // Set the icon for the QMessageBox (optional)
    aboutBox.setIcon(QMessageBox::Information);

    // Set the text content with rich text formatting
    aboutBox.setText(
        "<h3>About This Program</h3>"
        "<p><b>Program Name:</b> BinPlorer</p>"
        "<p><b>Version:</b> 1.0.0</p>"
        "<p><b>Purpose:</b><br>"
        "BinPlorer is designed to facilitate the loading and analysis of binary files. "
        "This program enables users to inspect, manipulate, and execute binary code, providing a versatile tool for reverse engineering, debugging, and performance analysis. "
        "It currently supports the Linnux ELF binary format, making it an essential utility for developers, security researchers, and enthusiasts who work with executable files.</p>"
        "<p><b>Key Features:</b></p>"
        "<ul>"
        "<li>Load and inspect the ELF binary format.</li>"
        "<li>Visualize binary sections and symbols for detailed analysis.</li>"
        "<li>Interactive interface for navigating through binary data.</li>"
        "</ul>"
        "<p><b>Version Details:</b></p>"
        "<ul>"
        "<li>1.0.0: Initial release with core binary loading and inspection capabilities.</li>"
        "</ul>"
        "<p><b>Acknowledgments:</b></p>"
        "<p><b>John Ebinyi Odey</b> a.k.a <b>Redhound</b></p>"
        "<ul>"
        "<li><b>Twitter</b>: @i_am_giannis</li>"
        "<li><b>Youtube</b>: https://www.youtube.com/@TheRedhound</li>"
        "<li><b>GitHub</b>: https://github.com/hotwrist</li>"
        "</ul>"
        );

    // Show the QMessageBox
    aboutBox.exec();
}


// When the 'Open Binary File' button is clicked, this displays a dialog
// enabling the user to select his/her specific binary file
void BinPlorer::on_pushButton_clicked()
{
    size_t i; // this is going to be used for iteration (for-loop)
    binary bin;
    section *sec;
    symbol *sym;
    std::string fname;

    QString filename = QFileDialog::getOpenFileName(this, "Open Binary File", " ", "Bin File (*.o, *);; All Files;;");
    if(filename.isEmpty()) return;

    // assign the binary filenamme to binary_file
    binary_file = filename;

    QFile file(filename);

    // if there was an error opening the binary file, treat it.
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Warning", "Binary File could not be opened: " + file.errorString());
    }

    // Set the value of fname to the binary file name selected by the user.
    fname.assign(binary_file.toStdString());

    if(bin.load_binary(fname, &bin) < 0 )
    {
        return;
    }

    QString fmted_string = QString("loaded binary '%1' %2/%3 (%4 bits) entry@0x%5").arg(bin.filename.c_str()).arg(bin.type_str.c_str()).arg(bin.arch_str.c_str()).arg(bin.bits).arg(QString::number(bin.entry, 16).toUpper().rightJustified(16, '0'));
    ui->lineEdit->setText(fmted_string);

    //======================================SECTIONS=================================================
    ui->tableWidget->setRowCount(bin.sections.size()); // Set number of rows
    ui->tableWidget->setColumnCount(4); // Set number of columns

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels({"Address (VMA)", "Size", "Name", "Type"});
        // Set the resize mode to stretch to fit the contents better
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Apply stylesheet to change the header colors
    ui->tableWidget->setStyleSheet(
        "QHeaderView::section {"
        "   background-color: #3498db;"  // Change to your desired color
        "   color: white;"               // Change the text color of the header
        "   padding: 4px;"               // Optional: Adjust padding for better spacing
        "   border: 1px solid #2c3e50;"  // Optional: Add border styling
        "}"
        );

    // Iterates over the section  and display the contentt of the section
    for(i = 0; i < bin.sections.size(); i++) {
        sec = &bin.sections[i];

        // Set the column width for the first column and the third column
        ui->tableWidget->setColumnWidth(0, 250);
        ui->tableWidget->setColumnWidth(2, 250);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString("0x%1").arg(QString::number(sec->vma, 16).toUpper().rightJustified(16, '0')));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(sec->size));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg(sec->name.c_str()));
        QTableWidgetItem *item4 = new QTableWidgetItem(QString("%1").arg(sec->type == section::SEC_TYPE_CODE ? "CODE" : "DATA"));

        // Add  the itemms to the table
        ui->tableWidget->setItem(i, 0, item1);
        ui->tableWidget->setItem(i, 1, item2);
        ui->tableWidget->setItem(i, 2, item3);
        ui->tableWidget->setItem(i, 3, item4);

        // We need the background of the address column only, to be set to green
        item1->setBackground(QBrush(Qt::green));

        // Set the full text as a tooltip, so it shows when hovered
        item1->setToolTip(item1->text());
        item2->setToolTip(item2->text());
        item3->setToolTip(item3->text());
        item4->setToolTip(item4->text());
    }
    //==============================================END OF SECTION=====================================================

    //============================================SYMBOLS==============================================================
    ui->tableWidget_2->setRowCount(bin.symbols.size()); // Set number of rows
    ui->tableWidget_2->setColumnCount(3); // Set number of columns

    // Set column headers
    ui->tableWidget_2->setHorizontalHeaderLabels({"Name", "Address", "Type"});
    // Set the resize mode to stretch to fit the contents better
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Apply stylesheet to change the header colors
    ui->tableWidget_2->setStyleSheet(
        "QHeaderView::section {"
        "   background-color: #3498db;"  // Change the background to the desired color
        "   color: white;"               // Change the text color of the header
        "   padding: 4px;"               // Optional: Adjust padding for better spacing
        "   border: 1px solid #2c3e50;"  // Optional: Add border styling
        "}"
        );

    //iterate over the symbols and retrieve its values
    if(bin.symbols.size() > 0) {
        for(i = 0; i < bin.symbols.size(); i++) {
            sym = &bin.symbols[i];
            QString sym_name = QString::fromStdString(sym->name.c_str());

            ui->tableWidget_2->setColumnWidth(0, 300);
            ui->tableWidget_2->setColumnWidth(1, 250);

            QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(sym_name));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("0x%1").arg(QString::number(sym->addr, 16).toUpper().rightJustified(16, '0')));
            QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg((sym->type & symbol::SYM_TYPE_FUNC) ? "FUNC" : " "));

            // Set the values retrieved into  the table
            ui->tableWidget_2->setItem(i, 0, item1);
            ui->tableWidget_2->setItem(i, 1, item2);
            ui->tableWidget_2->setItem(i, 2, item3);

            // We need to set the background color of the address column to green.
            item2->setBackground(QBrush(Qt::green));

            // Set the full text as a tooltip, so it shows when hovered
            item1->setToolTip(item1->text());
            item2->setToolTip(item2->text());
            item3->setToolTip(item3->text());
        }
    }
    //==========================================END OFF SYMBOL============================================================
    bin.unload_binary(&bin);
}
