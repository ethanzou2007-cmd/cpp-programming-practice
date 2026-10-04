#include <iostream>
#include <string>

int main() {
    int money;
    char code;

    std::cout << "Insert money (cents): ";
    std::cin >> money;
    std::cout << "Item code (A/B/C): ";
    std::cin >> code;

    if (!std::cin || money < 0) {
        std::cout << "Invalid money amount." << '\n';
        return 1;
    }

    int price;
    std::string itemName;

    switch (code) {
    case 'A':
        price = 150;
        itemName = "Water";
        break;
    case 'B':
        price = 200;
        itemName = "Juice";
        break;
    case 'C':
        price = 250;
        itemName = "Cola";
        break;
    default:
        std::cout << "Invalid item code." << '\n';
        return 1;
    }

    if (money < price) {
        std::cout << "Insufficient money. Please insert more." << '\n';
    } else if (money == price) {
        std::cout << "Purchased " << itemName << ". No change." << '\n';
    } else {
        int change = money - price;
        std::cout << "Purchased " << itemName << ". Your change is " << change << " cents." << '\n';
    }

    return 0;
}
