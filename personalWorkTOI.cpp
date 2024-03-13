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
// Основная структура - карточка товара
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

//процедура для ввода с клавиатуры
void InputData(Product products[], int amount) {

    for (int i{ 0 }; i < amount; ++i) {
        std::cout << "Введите ID товара \n";
        std::cin >> products -> id;
        std::cout << "Введите название товара \n";
        std::cin >> products -> name;
        std::cout << "Введите цену товара \n";
        std::cin >> products -> price;
        std::cout << "Введите рейтинг товара \n";
        std::cin >> products -> rate;
    }
}

// Процедура для сортировки методом пузырька индексированного массива по цене массива 
void BubblePriceSort(Price products[], int n) {
    for (int i{ 0 }; i < n - 1; ++i) {
        for (int j{ 0 }; j < n - i - 1; ++j) {
            if (products[j].price < products[j + 1].price) {
                Price temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
                
            }
        }
    }
}

// Процедура для сортировки методом пузырька индексированного массива по рейтингу массива 
void BubbleRateSort(Rate products[], int n) {
    for (int i{ 0 }; i < n - 1; ++i) {
        for (int j{ 0 }; j < n - i - 1; ++j) {
            if (products[j].rate >  products[j + 1].rate) {
                Rate temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
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

//
// 
// 
// ЗАДАНИЕ 2
// 
// 
// 

// Структура для узла дерева индексов по цене
struct PriceNode {
    int price;
    int index; // Индекс в массиве товаров
    PriceNode* left; // Левый наследник
    PriceNode* right; // Правый наследник
};


// Функция для вставки узла в дерево индексов по цене
PriceNode* insertPriceTree(PriceNode* root, int price, int index) {
    if (root == nullptr) {
        return new PriceNode { price, index, nullptr, nullptr };
    }
    else if (price < root->price) {//Стрелка указывает на поле price объекта PriceNode
        root->left = insertPriceTree(root->left, price, index);
    }
    else if (price > root->price) {
        root->right = insertPriceTree(root->right, price, index);
    }
    else {
        // Если цена уже есть в дереве, обновляем индекс
        root->index = index;
    }
    return root;
}

// Функция для поиска узла в дереве индексов по цене
PriceNode* searchPriceTree(PriceNode* root, int price) {
    if (root == nullptr) {
        return nullptr;
    }
    else if (root->price == price) {
        return root;
    }
    else if (price < root->price) {
        return searchPriceTree(root->left, price);
    }
    else {
        return searchPriceTree(root->right, price);
    }
}

// Функция для вывода товаров по цене в порядке возрастания
void printProductsByPrice(Product products[], int size, PriceNode* root) {
    if (root != nullptr) {
        printProductsByPrice(products, size, root->left);
        std::cout << "Название: " << products[root->index].name << ", Цена: " << products[root->index].price << ", Рейтинг: " << products[root->index].rate << ", ID: " << products[root->index].id << std::endl;
        printProductsByPrice(products, size, root->right);
    }
}


// Функция для удаления узла из дерева индексов по силе
PriceNode* deletePriceNode(PriceNode* root, int price) {
    if (root == nullptr) {
        return nullptr;
    }
    else if (price < root->price) {
        root->left = deletePriceNode(root->left, price);
    }
    else if (price > root->price) {
        root->right = deletePriceNode(root->right, price);
    }
    else {
        // Если узел является листом
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // Если узел имеет только один дочерний узел
        else if (root->left == nullptr) {
            PriceNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            PriceNode* temp = root;
            root = root->left;
            delete temp;
        }
        // Если узел имеет два дочерних узла
        else {
            PriceNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->price = temp->price;
            root->index = temp->index;
            root->right = deletePriceNode(root->right, temp->price);
        }
    }
    //Возвращает указатель на измененное дерево
    return root;
}
//
// 
// 
// ЗАДАНИЕ 3
// 
// 

struct Node { // Определяем структуру Node
    Product data; // Поле data - структура Person
    Node* next; // Поле next - указатель на следующий узел
};

// Функция для вставки данных в отсортированный по ID связанный список
void insertSorted(Node*& head, const Product& newData) {
    Node* newNode = new Node;   // Создание нового узла
    newNode->data = newData;    // Присвоение новым данным
    newNode->next = nullptr;    // Новый узел пока не связан с другими

    // Если список пуст или первый элемент имеет ID больше или равный новому, вставляем новый элемент в начало списка
    if (head == nullptr || head->data.id >= newData.id) {
        newNode->next = head; // Связываем новый узел со старым началом списка
        head = newNode;       // Новый узел становится началом списка
        return;               // Завершаем функцию
    }

    // Поиск места для вставки нового узла
    Node* current = head;
    while (current->next != nullptr && current->next->data.id < newData.id) {
        current = current->next;
    }

    // Вставка нового узла
    newNode->next = current->next;
    current->next = newNode;
}



// Функция для поиска и вывода товаров по ID
void searchAndDisplayByAttributeValue(Node* head, int targetId) {
    Node* current = head;
    bool found = false;

    // Поиск товаров по ID и вывод 
    while (current != nullptr) {
        if (current->data.id == targetId) {
            found = true;
            std::cout << "Найден товар с ID " << targetId << ":" << std::endl;
            std::cout << "Название: " << current->data.name << ", Цена: " << current->data.price << ", Рейтинг: "
                << current->data.rate << ", ID: " << current->data.id << std::endl;
        }
        current = current->next;
    }

    // Если товар с указанным ID не найден
    if (!found) {
        std::cout << "Товар с ID " << targetId << " не найден." << std::endl;
    }
}

//Удаление элемента
void removeNodeByID(Node*& head, int id) {
    if (head == nullptr) {
        return;
    }
    Node* current = head;
    while (current != nullptr && current->data.id != id) {
        current = current->next;
    }
    if (current != nullptr) {
        Node* prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next;
    }
}

// Функция для вывода всего списка товаров
void printList(Node* head) {
    Node* current = head;

    // Вывод данных каждого узла списка
    while (current != nullptr) {
        std::cout << "Название: " << current->data.name << ", Цена: " << current->data.price << ", Рейтинг: " << current->data.rate << ", ID: " << current->data.id << std::endl;
        current = current->next;
    }
}

//функция для рандомного заполнения линейного списка товаров 
void randomInputData(Node*& head, int amount) {
    std::string Names[11] = { "Ноутбук", "Фен", "Кофеварка", "Телевизор", "Компьютер", "Мышка", "Клавиатура", "Колонка", "Наушники", "Стол", "Проектор" };

    // Генерация и вставка случайных товаров
    for (int i = 0; i < amount; ++i) {
        Product productsList = { Random(100, 1000), Names[Random(0, 10)], Random(1, 10000), Random(1, 5) };
        insertSorted(head, productsList);
    }
}

//// Сортировка по ID и вывод каждого узла
//void printSorted(Node* head) {
//    if (head == nullptr) {
//        return;
//    }
//    Node* current = head;
//    while (current != nullptr) {
//        Node* next = current->next;
//        while (next != nullptr && next->data.id < current->data.id) {
//            next = next->next;
//        }
//        current->next = next;
//        current = next;
//    }
//    current = head;
//    while (current != nullptr) {
//        std::cout << "Название: " << current->data.name << ", Цена: " << current->data.price << ", Рейтинг: " << current->data.rate << ", ID: " << current->data.id << std::endl;
//        current = current->next;
//    }
//}
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
    //InputData(products, arraySize); //заполнение массива вручную

    // Вывод индексированного массива по цене
    std::cout << "\n****************************" << std::endl;
    std::cout << "Индексирование №1. (По цене)" << std::endl;
    std::cout << "**************************** \n" << std::endl;
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
    std::cout << "\n****************************" << std::endl;
    std::cout << "Индексирование №2. (По рейтингу)" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    Rate* rateIndex = new Rate[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        rateIndex[i].rate = products[i].rate;
        rateIndex[i].index = i;
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << rateIndex[i].index << std::endl;
    }
 
    // Поиск индекса по значению рейтинга (итеративный)
    std::cout << "Индекс:" << IterativeRateSearch(rateIndex, arraySize, 3);

    // Сортировка массива индексов для цены
    std::cout << "\n****************************" << std::endl;
    std::cout << "Сортировка массива для цены" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    BubblePriceSort(priceIndex, arraySize);
    Product* tempProducts = new Product[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        tempProducts[i] = products[priceIndex[i].index];
    }

    for (int i = 0; i < arraySize; ++i) {
        products[i].price = priceIndex[i].price;
        priceIndex[i].index = i;
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id
            << ", Index: " << priceIndex[i].index << std::endl;
    }

    // Сортировка массива индексов для рейтинга
    std::cout << "\n****************************" << std::endl;
    std::cout << "Сортировка массива для рейтинга" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    BubbleRateSort(rateIndex, arraySize);

    for (int i = 0; i < arraySize; ++i) {
        tempProducts[i] = products[rateIndex[i].index];
    }

    for (int i = 0; i < arraySize; ++i) {

        products[i] = tempProducts[i];
        rateIndex[i].index = i;
        priceIndex[i].index = i;
        rateIndex[i].rate = products[i].rate;
        
        std::cout << "Название: " << products[i].name << ", Цена: " << products[i].price <<
            ", Рейтинг: " << products[i].rate << ", ID: " << products[i].id << std::endl;
    }

    // Изменение значения цены и соответствующего индекса
    std::cout << "\n****************************" << std::endl;
    std::cout << "Изменение массива индексов для цены" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    EditPriceRecord(products, priceIndex, arraySize, 4, 324);
    PrintArray(products, arraySize);

    // Изменение значения рейтинга и соответствующего индекса
    std::cout << "\n****************************" << std::endl;
    std::cout << "Изменение массива индексов для рейтинга" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    RateRecord(products, rateIndex, arraySize, 4, 10000);
    PrintArray(products, arraySize);

    // Удаление записи по ключу из массива товаров и массива индексов для цены
    std::cout << "\n****************************" << std::endl;
    std::cout << "Удаление массива индексов для цены" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    RemoveRecordByKey(products, priceIndex, arraySize, 0);
    PrintArray(products, arraySize);

    // Удаление записи по ключу из массива товаров и массива индексов для рейтинга

    std::cout << "\n****************************" << std::endl;
    std::cout << "Удаление массива индексов для рейтинга" << std::endl;
    std::cout << "**************************** \n" << std::endl;
    DeleteRateRecord(products, rateIndex, arraySize, 2);
    PrintArray(products, arraySize);

    // Освобождение памяти, выделенной для массивов товаров и индексов
    delete[] products;
    delete[] priceIndex;
    delete[] rateIndex;
    std::cout << "ЗАДАНИЕ 2 \n" << std::endl;

    //
    // 
    // 
    // ЗАДАНИЕ 2
    // 
    // 

    Product products1[50];
    int size = 10; // ???????????
    RandomInputData(products1, size);

    //Создаем индекс по цене
    PriceNode* root = nullptr; 
    for (int i = 0; i < size; ++i)
    {
        root = insertPriceTree(root, products1[i].price, i);
    }

    
    // Выводим товары по цене в порядке возрастания
    std::cout << "Товары по цене в порядке возрастания:" << std::endl;
    printProductsByPrice(products1, size, root);

    // Ищем товар по цене
    int searchPrice;
    std::cout << "Введите цену товара поиска: ";
    std::cin >> searchPrice;
    PriceNode* foundNode = searchPriceTree(root, searchPrice);
    if (foundNode != nullptr) {
        std::cout << "Найден товар:" << std::endl;
        std::cout << "Название: " << products1[foundNode->index].name << ", Цена: " << products1[foundNode->index].price << ", Рейтинг: " << products1[foundNode->index].rate << ", ID: " << products1[foundNode->index].id << std::endl;
    }
    else {
        std::cout << "Товар с такой ценой не найден" << std::endl;
    }


    // Редактируем товар по цене
    int editPrice;
    std::cout << "Введите цену товара для редактирования: ";
    std::cin >> editPrice;
    foundNode = searchPriceTree(root, editPrice);
    if (foundNode != nullptr) {
        std::cout << "Текущие данные товара:" << std::endl;
        std::cout << "Название: " << products1[foundNode->index].name << ", Цена: " << products1[foundNode->index].price << ", Рейтинг: " << products1[foundNode->index].rate << ", ID: " << products1[foundNode->index].id << std::endl;

        std::string newName;
        int newPrice;
        int newRate;
        int newId;
        std::cout << "Введите новые данные товара:" << std::endl;
        std::cout << "Название: ";
        std::cin >> newName;
        std::cout << "Цена: ";
        std::cin >> newPrice;
        std::cout << "Рейтинг: ";
        std::cin >> newRate;
        std::cout << "ID: ";
        std::cin >> newId;

        products1[foundNode->index].name = newName;
        products1[foundNode->index].price = newPrice;
        products1[foundNode->index].rate = newRate;
        products1[foundNode->index].id = newId;

        // Обновляем индекс
        root = insertPriceTree(root, newPrice, foundNode->index);
        root = deletePriceNode(root, editPrice);
    }
    else {
        std::cout << "Товар с такой ценой не найден." << std::endl;
    }

    // Удаляем товар по id
    int deletePower;
    std::cout << "Введите цену товара для удаления: ";
    std::cin >> deletePower;
    foundNode = searchPriceTree(root, deletePower);
    if (foundNode != nullptr) {
        // Удаляем из массива
        for (int i = foundNode->index; i < size - 1; ++i) {
            products1[i] = products1[i + 1];
        }
        --size;

        // Удаляем из индекса
        root = deletePriceNode(root, deletePower);
    }
    else {
        std::cout << "Товар с таким ID не найден." << std::endl;
    }
    std::cout << "Товары по цене в порядке возрастания:" << std::endl;
    printProductsByPrice(products1, size, root);


    //
    // 
    // 
    // ЗАДАНИЕ 3
    // 
    // 

    std::cout << "ЗАДАНИЕ 3 \n" << std::endl;

    Node* head = nullptr; // Указатель на начало списка
    int amount;
    std::cout << "Введите количество товаров: ";
    std::cin >> amount;

    randomInputData(head, amount); // Генерация случайных данных

    std::cout << "Список всех товаров:" << std::endl;
    printList(head); // Вывод списка товаров

    int searchId;
    std::cout << "Введите ID для поиска товара: ";
    std::cin >> searchId;
    searchAndDisplayByAttributeValue(head, searchId); // Поиск и вывод товара по ID

    int choiceDel;
    std::cout << "Введите ID элемента, который хотите удалить (3 задание)";
    std::cin >> choiceDel;
    removeNodeByID(head, choiceDel);
    std::cout << "\nМассив после удаления элемента";
    printList(head); // Вывод списка товаров

    //Выывод отсортированного списка 
    std::cout << "\nМассив отсортированный по ID ";
    //printSorted(head);
    // Освобождение памяти, выделенной под список
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}