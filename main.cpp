#include <iostream>
#include <vector>
#include <string>

#ifndef Run_TESTS

// основной код ===========

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}


// Функция для вывода студентов по специальности
void displayStudBySpec(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных студентов пуста.\n";
        return;
    }
    std::string major;
    std::cout << "Введите специальность для поиска: ";
    std::cin.ignore();
    std::getline(std::cin, major);
    
    int count = 0;
    std::cout << "Студенты специальности '" << major << "':\n";
    
    for (const Student& student : database) {
        if (student.major == major) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "Студенты по специальности '" << major << "' не найдены.\n";
    } else {
        std::cout << "Найдено студентов: " << count << "\n";
    }
}


int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Вывести студентов по специальности\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                displayStudBySpec(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}

#else
// код тесты ===========

#include <gtest/gtest.h>
#include <sstream>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void addStudent(std::vector<Student>& database);
void displayStudents(const std::vector<Student>& database);
void displayStudBySpec(const std::vector<Student>& database);

void addStudent(std::vector<Student>& database) {
    Student student;
    std::cin >> student.name >> student.age >> student.major >> student.gpa;
    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

void displayStudBySpec(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных студентов пуста.\n";
        return;
    }
    std::string major;
    std::getline(std::cin, major);

    int count = 0;
    std::cout << "Студенты специальности '" << major << "':\n";
    for (const Student& student : database) {
        if (student.major == major) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            count++;
        }
    }

    if (count == 0) {
        std::cout << "Студенты по специальности '" << major << "' не найдены.\n";
    } else {
        std::cout << "Найдено студентов: " << count << "\n";
    }
}

// сами тесты ===============

TEST(StudentIOTest, AddStudentInteractive) {
    std::vector<Student> db;

    std::istringstream input("Sset\n20\nMath\n4.0\n");
    std::ostringstream output;

    auto cinbuf = std::cin.rdbuf();
    auto coutbuf = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    addStudent(db);

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);

    ASSERT_EQ(db.size(), 1);
    EXPECT_EQ(db[0].name, "Sset");
    EXPECT_EQ(db[0].age, 20);
    EXPECT_EQ(db[0].major, "Math");
    EXPECT_DOUBLE_EQ(db[0].gpa, 4.0);
    EXPECT_NE(output.str().find("Студент добавлен в базу данных"), std::string::npos);
}

TEST(StudentIOTest, DisplayStudentsOutput) {
    std::vector<Student> db = {
        {"Anna", 22, "Physics", 3.7},
        {"Petra", 21, "Math", 3.9}
    };

    std::ostringstream output;
    auto coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    displayStudents(db);

    std::cout.rdbuf(coutbuf);
    std::string out = output.str();
    EXPECT_NE(out.find("Anna"), std::string::npos);
    EXPECT_NE(out.find("Petra"), std::string::npos);
    EXPECT_NE(out.find("Physics"), std::string::npos);
    EXPECT_NE(out.find("Math"), std::string::npos);
}

TEST(StudentIOTest, DisplayStudBySpecExisting) {
    std::vector<Student> db = {
        {"Ivan", 20, "Math", 4.0},
        {"Anna", 22, "Physics", 3.7},
        {"Petra", 21, "Math", 3.9}
    };

    std::istringstream input("Math\n");
    std::ostringstream output;

    auto cinbuf = std::cin.rdbuf();
    auto coutbuf = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    displayStudBySpec(db);

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);

    std::string out = output.str();
    EXPECT_NE(out.find("Ivan"), std::string::npos);
    EXPECT_NE(out.find("Petra"), std::string::npos);
    EXPECT_NE(out.find("Найдено студентов: 2"), std::string::npos);
}

TEST(StudentIOTest, DisplayStudBySpecNonExisting) {
    std::vector<Student> db = {
        {"Ivan", 20, "Math", 4.0},
        {"Anna", 22, "Physics", 3.7}
    };

    std::istringstream input("CS\n");
    std::ostringstream output;

    auto cinbuf = std::cin.rdbuf();
    auto coutbuf = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    displayStudBySpec(db);

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);

    std::string out = output.str();
    EXPECT_NE(out.find("не найдены"), std::string::npos);
}

TEST(StudentIOTest, DisplayStudBySpecEmptyDB) {
    std::vector<Student> db;

    std::ostringstream output;
    auto coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    displayStudBySpec(db);

    std::cout.rdbuf(coutbuf);
    std::string out = output.str();
    EXPECT_NE(out.find("База данных студентов пуста"), std::string::npos);
}

// main() для GoogleTest =====
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
