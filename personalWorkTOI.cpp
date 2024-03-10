#include <iostream>
#include <string>
#include <random>

using namespace std;

//
// 
// 
// ЗАДАНИЕ 1
// 
// 
//Основная структура - карточка товара
struct Product {
    int id; //идентификатор
    std::string name; //название товара
    int price; // цена товара
    int rate; // рейтинг товара (от 1 до 5)
};


//Для реализации индексирования создаю еще две структуры

//Индексация по полю цены
struct Price {
    int price;
    int index;
};

//Индексация по полю рейтинга товара
struct Rate {
    int rate;
    int index;
};

// Процедура для печати массива товаров
void PrintArray(Product products[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price << ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id << std::endl;
    }
}

//Генератор рандомных чисел


int Random(int start, int end) {
    int x = rand() % (end - start + 1) + start;
    return x;
}



// Процедура для заполнения рандомными значениями
void RandomInputData(Product products[], int amount) {
    std::string Names[11]{ "Ноутбук", "Фен", "Кофеварка", "Телевизор", "Компьютер", "Мышка", "Клавиатура", "Колонка", "Наушники", "Стол", "Проектор" };
    for (int i{ 0 }; i < amount; ++i) {
        products[i] = Product{ Random(1, 100), Names[Random(0, 10)], Random(1, 10000), Random(1, 5) };
    }
}



// Процедура для сортировки методом пузырька индексированного массива по цене массива 
void BubblePriceSort(Price products[], int n) {
    for (int i{ 0 }; i < n - 1; ++i) {
        for (int j{ 0 }; j < n - i - 1; ++j) {
            if (products[j].price < products[j + 1].price) {
                std::swap(products[j], products[j + 1]); //swap - меняет местами значения переменных
            }
        }
    }
}

// Процедура для сортировки методом пузырька индексированного массива по рейтингу массива 
void BubbleRateSort(Rate products[], int n) {
    for (int i{ 0 }; i < n - 1; ++i) {
        for (int j{ 0 }; j < n - i - 1; ++j) {
            if (products[j].rate < products[j + 1].rate) {
                std::swap(products[j], products[j + 1]);
            }
        }
    }
}

// Рекурсивная функция для бинарного поиска индекса в массиве индексов для цены
int BinarySearchRecursive (Price products[], int left, int right, int key) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (products[mid].price == key)
            return mid;

        if (products[mid].price > key)
            return BinarySearchRecursive(products, left, mid - 1, key);

        return BinarySearchRecursive(products, mid + 1, right, key);
    }

    return -1;
}

// Итеративная функция для бинарного поиска индекса в массиве индексов для рейтинга
int IterativeRateSearch(Rate products[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].rate == key)
            return mid;

        if (products[mid].rate < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;  // Не нашлось
}

// Процедура для изменения записи по индексу в массиве товаров и массиве индексов для цены
void EditPriceRecord(Product products[], Price priceIndex[], int n, int recordIndex, int newPrice) {
    products[recordIndex].price = newPrice;
    for (int i = 0; i < n; ++i) {
        if (priceIndex[i].index == recordIndex) {
            priceIndex[i].price = newPrice;
            break;
        }
    }
}

// Процедура для изменения записи по индексу в массиве товаров и в массиве индексов по рейтингу
void RateRecord(Product products[], Rate rateIndex[], int n, int recordIndex, int newRate) {
    products[recordIndex].rate = newRate;
    for (int i = 0; i < n; ++i) {
        if (rateIndex[i].index == recordIndex) {
            rateIndex[i].rate = newRate;
            break;
        }
    }
}

// Процедура для удаления записи по ключу из массива товаров и массива индексов для цены
void RemoveRecordByKey(Product* products, Price* powerIndex, int& size, int index) {
    for (int i = index; i < size - 1; ++i) {
        products[i] = products[i + 1];
        powerIndex[i] = powerIndex[i + 1];
    }
    --size;
}

// Процедура для удаления записи по ключу из массива товаров и массива индексов для рейтинга
void DeleteRateRecord(Product* products, Rate* rateIndex, int& size, int index) {
    for (int i = index; i < size - 1; ++i) {
        products[i] = products[i + 1];
        rateIndex[i] = rateIndex[i + 1];
    }
    --size;
}


int main() {
    //
    // 
    // 
    // ЗАДАНИЕ 1
    // 
    // 

    setlocale(LC_ALL, "Russian");
    int arraySize = 10; // Размер массива 
    Product* products = new Product[arraySize]; // Выделение памяти под массива
    RandomInputData(products, arraySize); // Заполнение массива случайными данными

    // Вывод индексированного массива по цене
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Индексирование №1. (По цене)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    Price* priceIndex = new Price[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        priceIndex[i].price = products[i].price;
        priceIndex[i].index = i;
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << priceIndex[i].index << std::endl;
    }

    // Рекурсивный поиск по цене: 
    std::cout << "Индекс:" << BinarySearchRecursive(priceIndex, 0, arraySize, 290);

    // Инндексирование по величине рейтинга
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Индексирование №2. (По рейтингу)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    Rate* rateIndex = new Rate[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        rateIndex[i].rate = products[i].rate;
        rateIndex[i].index = i;
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << rateIndex[i].index << std::endl;
    }
 
    // Поиск индекса по значению уровня (итеративный)
    std::cout << "Индекс:" << IterativeRateSearch(rateIndex, arraySize, 290);

    // Сортировка массива индексов для цены
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Сортировка массива для цены" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    BubblePriceSort(priceIndex, arraySize);
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << priceIndex[i].index << std::endl;
    }

    // Сортировка массива индексов для рейтинга
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Сортировка массива для рейтинга" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    BubbleRateSort(rateIndex, arraySize);
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << rateIndex[i].index << std::endl;
    }

    // Изменение значения силы и соответствующего индекса
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Изменение массива индексов для цены" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    EditPriceRecord(products, priceIndex, arraySize, 4, 324);
    PrintArray(products, arraySize);

    // Изменение значения уровня и соответствующего индекса
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Изменение массива индексов для рейтинга" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    RateRecord(products, rateIndex, arraySize, 4, 10000);
    PrintArray(products, arraySize);

    // Удаление записи по ключу из массива покемонов и массива индексов для силы
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Удаление массива индексов для цены" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    RemoveRecordByKey(products, priceIndex, arraySize, 0);
    PrintArray(products, arraySize);

    // Удаление записи по ключу из массива покемонов и массива индексов для уровня
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "Удаление массива индексов для рейтинга" << std::endl;
    std::cout << "****************************)" << std::endl;
    std::cout << "****************************)" << std::endl;
    DeleteRateRecord(products, rateIndex, arraySize, 2);
    PrintArray(products, arraySize);

    // Освобождение памяти, выделенной для массивов покемонов и индексов
    delete[] products;
    delete[] priceIndex;
    delete[] rateIndex;

    return 0;
}