#include <QtWidgets>
#include <iostream>
#include <QLabel>
#include <QLineEdit>


// Функция для расчета сухой массы тела по формуле #1
double calculateDryMassFormula1(double weight, double height)
{
    return weight - (0.25 * height);
}

// Функция для расчета сухой массы тела по формуле #2
double calculateDryMassFormula2(double weight, double height)
{
    return weight - (0.15 * height);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создание главного окна
    QMainWindow mainWindow;

    // Создание виджета формы
    QWidget *formWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(formWidget);

    // Создание компонентов формы
    QLabel *weightLabel = new QLabel("Вес (кг):", formWidget);
    QLineEdit *weightLineEdit = new QLineEdit(formWidget);

    QLabel *heightLabel = new QLabel("Рост (см):", formWidget);
    QLineEdit *heightLineEdit = new QLineEdit(formWidget);

    QPushButton *calculateButton = new QPushButton("Рассчитать", formWidget);
    QLabel *resultLabel = new QLabel("Результат:", formWidget);
    QLabel *averageResultLabel = new QLabel("Среднее значение:", formWidget);

    // Создание компонента для сохранения отчета
    QPushButton *saveReportButton = new QPushButton("Сохранить данные", formWidget);

    // Создание компонентов управления размещением
    QVBoxLayout *layout = new QVBoxLayout(formWidget);
    layout->addWidget(weightLabel);
    layout->addWidget(weightLineEdit);
    layout->addWidget(heightLabel);
    layout->addWidget(heightLineEdit);
    layout->addWidget(calculateButton);
    layout->addWidget(resultLabel);
    layout->addWidget(averageResultLabel);
    layout->addWidget(saveReportButton);

    // Соединение сигнала нажатия кнопки Calculate с обработчиком
    QObject::connect(calculateButton, &QPushButton::clicked, [&](){
        // Получение введенных данных
        double weight = weightLineEdit->text().toDouble();
        double height = heightLineEdit->text().toDouble();

        // Выполнение расчетов
        double resultFormula1 = calculateDryMassFormula1(weight, height);
        double resultFormula2 = calculateDryMassFormula2(weight, height);
        double averageResult = (resultFormula1 + resultFormula2) / 2.0;

        // Вывод результатов на экран
        resultLabel->setText("Результат: " + QString::number(resultFormula1) + " и " + QString::number(resultFormula2));
        averageResultLabel->setText("Среднее значение: " + QString::number(averageResult));
    });

    // Соединение сигнала нажатия кнопки Save Report с обработчиком
    QObject::connect(saveReportButton, &QPushButton::clicked, [&](){
        // Получение результатов расчета
        QString resultText = resultLabel->text();
        QString averageResultText = averageResultLabel->text();

        // Создание диалога сохранения файла
        QString filePath = QFileDialog::getSaveFileName(&mainWindow, "Сохранить данные", "", "Текстовой файл (*.txt)");
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                // Запись результатов в файл
                QTextStream stream(&file);
                stream << "| " << resultText << " ";
                stream << "| " << averageResultText << " |";

                file.close();
            } else {
                QMessageBox::critical(&mainWindow, "Ошибка!", "Не удалось сохранить данные.");
            }
        }
    });

    mainWindow.show();

    return app.exec();
}

