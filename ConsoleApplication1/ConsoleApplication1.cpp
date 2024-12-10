#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>

class Record {
public:
    std::string name;
    std::string surname;
    std::string phone;

    Record(std::string n, std::string s, std::string p)
        : name(std::move(n)), surname(std::move(s)), phone(std::move(p)) {}

    void print() const {
        std::cout << "Name: " << name << ", Surname: " << surname << ", Phone: " << phone << '\n';
    }
};

void uniquePointerDemo() {
    std::cout << "\n--- Unique Pointer Demo ---\n";
    std::unique_ptr<Record> ptr1 = std::make_unique<Record>("John", "Doe", "123456789");

    ptr1->print();

    // Przenoszenie wskaźnika unikalnego
    std::unique_ptr<Record> ptr2 = std::move(ptr1); 

    if (!ptr1) {
        std::cout << "ptr1 is null after move.\n";
    }
    ptr2->print();
}

void sharedWeakPointerDemo() {
    std::cout << "\n--- Shared and Weak Pointer Demo ---\n";

    std::vector<std::shared_ptr<Record>> addressBook = {
        std::make_shared<Record>("Alice", "Smith", "555-1234"),
        std::make_shared<Record>("Bob", "Brown", "555-5678"),
        std::make_shared<Record>("Alice", "Johnson", "555-8765")
    };

    // Słabe wskaźniki do wyników ostatniego wyszukiwania
    std::vector<std::weak_ptr<Record>> lastSearchResults;

    std::cout << "Searching for people named Alice:\n";
    for (const auto& record : addressBook) {
        if (record->name == "Alice") {
            lastSearchResults.push_back(record);
            record->print();
        }
    }

    // Usuwamy jeden wskaźnik współdzielony
    std::cout << "\nRemoving a shared pointer to the first Alice.\n";
    addressBook.erase(std::remove_if(addressBook.begin(), addressBook.end(),
        [](const std::shared_ptr<Record>& rec) {
            return rec->name == "Alice";
        }),
        addressBook.end());

    // Sprawdzamy dostępność pamięci przez słabe wskaźniki
    std::cout << "\nChecking weak pointers from the last search:\n";
    for (const auto& weakPtr : lastSearchResults) {
        if (auto sharedPtr = weakPtr.lock()) {
            sharedPtr->print();
        }
        else {
            std::cout << "Memory no longer accessible.\n";
        }
    }
}

int main() {
    uniquePointerDemo();
    sharedWeakPointerDemo();

    return 0;
}
