#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>

// Базовый класс для печатных изданий
class Publication {
protected:
    std::string title;
    std::string author;
    int year;
    bool available;

public:
    Publication(std::string t, std::string a, int y) : title(t), author(a), year(y), available(true) {}
    virtual ~Publication() = default;

    virtual void displayInfo() const {
        std::cout << "Название: " << title << std::endl;
        std::cout << "Автор: " << author << std::endl;
        std::cout << "Год: " << year << std::endl;
        std::cout << "Доступность: " << (available ? "В наличии" : "Выдана") << std::endl;
    }

    virtual std::string getType() const { return "Издание"; }

    void setAvailability(bool status) {
        available = status;
    }

    bool isAvailable() const {
        return available;
    }

    std::string getTitle() const {
        return title;
    }
};

// Производный класс для книг
class Book : public Publication {
private:
    std::string genre;
    int pages;

public:
    Book(std::string t, std::string a, int y, std::string g, int p)
        : Publication(t, a, y), genre(g), pages(p) {
    }

    void displayInfo() const override {
        Publication::displayInfo();
        std::cout << "Жанр: " << genre << std::endl;
        std::cout << "Количество страниц: " << pages << std::endl;
    }

    std::string getType() const override { return "Книга"; }
};

// Класс управления библиотекой
class Library {
private:
    std::vector<Publication*> publications;

public:
    ~Library() {
        for (auto pub : publications) {
            delete pub;
        }
    }

    void addPublication(Publication* pub) {
        publications.push_back(pub);
    }

    void displayAllPublications() const {
        std::cout << "\nСписок всех изданий в библиотеке:" << std::endl;
        for (const auto pub : publications) {
            std::cout << "\n--- " << pub->getType() << " ---" << std::endl;
            pub->displayInfo();
        }
    }

    bool borrowPublication(std::string title) {
        for (auto pub : publications) {
            if (pub->getTitle() == title && pub->isAvailable()) {
                pub->setAvailability(false);
                std::cout << "Издание \"" << title << "\" успешно выдано." << std::endl;
                return true;
            }
        }
        std::cout << "Издание \"" << title << "\" недоступно или не найдено." << std::endl;
        return false;
    }

    bool returnPublication(std::string title) {
        for (auto pub : publications) {
            if (pub->getTitle() == title && !pub->isAvailable()) {
                pub->setAvailability(true);
                std::cout << "Издание \"" << title << "\" успешно возвращено." << std::endl;
                return true;
            }
        }
        std::cout << "Издание \"" << title << "\" не может быть возвращено." << std::endl;
        return false;
    }
};

#endif // LIBRARY_H
