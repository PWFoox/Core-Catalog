#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <QString>

class Publication {
protected:
    QString title;
    QString author;
    int year;
    bool available;

public:
    Publication(QString t, QString a, int y) : title(t), author(a), year(y), available(true) {}
    virtual ~Publication() {}

    virtual QString getInfo() const {
        return QString("Название: %1\nАвтор: %2\nГод: %3\nДоступность: %4")
            .arg(title)
            .arg(author)
            .arg(year)
            .arg(available ? "В наличии" : "Выдана");
    }

    virtual QString getType() const { return "Издание"; }

    void setAvailability(bool status) {
        available = status;
    }

    bool isAvailable() const {
        return available;
    }

    QString getTitle() const {
        return title;
    }
};

class Book : public Publication {
private:
    QString genre;
    int pages;

public:
    Book(QString t, QString a, int y, QString g, int p)
        : Publication(t, a, y), genre(g), pages(p) {}

    QString getInfo() const override {
        return Publication::getInfo() + QString("\nЖанр: %1\nКоличество страниц: %2")
                                            .arg(genre)
                                            .arg(pages);
    }

    QString getType() const override { return "Книга"; }
};

#endif // PUBLICATION_H
