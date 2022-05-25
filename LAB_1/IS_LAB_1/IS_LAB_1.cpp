#include <iostream>
#include <string>

using namespace std;

//Бизнес логика
class Offer {

    int bank = 0;
    double interestRate = 0;

public:
    long amountOfCredit = 0;
    int timeOfCredit = 0;
    string typeOfCredit, pledge;

    Offer(long amountOfCredit, int timeOfCredit, string typeOfCredit, string pledge){

        this->amountOfCredit = amountOfCredit;
        this->timeOfCredit = timeOfCredit;
        this->typeOfCredit = typeOfCredit;
        this->pledge = pledge;
    }

    void CalculationOfCredit() {
        if (typeOfCredit == "refinancing" and timeOfCredit <= 3 and amountOfCredit <= 100000) {
            bank = 0; interestRate = 14.90;
        }
        if (typeOfCredit == "refinancing" and timeOfCredit > 3 and timeOfCredit <= 18 and amountOfCredit <= 100000) {
            bank = 1; interestRate = 9.90;
        }
        if (typeOfCredit == "refinancing" and timeOfCredit > 18 and amountOfCredit <= 100000) {
            bank = 2; interestRate = 8.90;
        }
        if (typeOfCredit == "refinancing" and timeOfCredit <= 24 and amountOfCredit > 100000 and amountOfCredit <= 1000000) {
            bank = 1; interestRate = 9.90;
        }
        if (typeOfCredit == "refinancing" and timeOfCredit > 3 and timeOfCredit > 24 and amountOfCredit > 100000 and amountOfCredit <= 1000000) {
            bank = 1; interestRate = 9.90;
        }
        if (typeOfCredit == "refinancing" and timeOfCredit > 36 and amountOfCredit > 100000 and amountOfCredit <= 10000000) {
            bank = 2; interestRate = 8.90;
        }
        if (typeOfCredit == "car" and timeOfCredit <= 12 and amountOfCredit <= 5000000) {
            bank = 3; interestRate = 11.90;
        }
        if (typeOfCredit == "car" and timeOfCredit > 12 and amountOfCredit <= 5000000) {
            bank = 2; interestRate = 10.90;
        }
        if (pledge == "yes" and timeOfCredit <= 9 and amountOfCredit <= 100000) {
            bank = 0; interestRate = 14.90;
        }
        if (pledge == "yes" and timeOfCredit > 9 and amountOfCredit <= 100000) {
            bank = 1; interestRate = 12.40;
        }
        if (pledge == "yes" and timeOfCredit > 9 and amountOfCredit > 100000 and amountOfCredit <= 1000000) {
            bank = 4; interestRate = 9.90;
        }
        if (pledge == "yes" and timeOfCredit > 9 and amountOfCredit > 1000000) {
            bank = 0; interestRate = 14.90;
        }
        if (typeOfCredit == "other" and timeOfCredit <= 60 and amountOfCredit <= 100000) {
            bank = 5; interestRate = 8.40;
        }
        if (typeOfCredit == "other" and timeOfCredit <= 12 and amountOfCredit > 100000 and amountOfCredit <= 5000000) {
            bank = 1; interestRate = 9.90;
        }
        if (typeOfCredit == "other" and timeOfCredit > 12 and timeOfCredit < 60 and amountOfCredit > 100000 and amountOfCredit <= 5000000) {
            bank = 5; interestRate = 8.90;
        }
        if (typeOfCredit == "mortgage" and amountOfCredit <= 10000000) {
            bank = 6; interestRate = 5.50;
        }
        if (typeOfCredit == "mortgage" and amountOfCredit > 10000000) {
            bank = 7; interestRate = 12.20;
        }

    }

    friend ostream& operator << (ostream& stream, Offer& request) {
        string banks[8] = { "Тинькофф", "ВТБ", "Альфа банк", "HOME CREDIT BANK", "СОВКОМБАНК", "ПСБ", "ГАЗПРОМБАНК", "РОСБАНК" };
        if (request.interestRate != 0) {
            stream << "\nНаиболее подходящий вам банк - " << banks[request.bank] << ", процентная ставка которую он предлагает - " << request.interestRate << "%\n";
        }
        else {
            stream << "\n По введенным парамарам не удалось подобрать кредит, попробуйте изменить параметры";
        }
        return stream;
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    long amountOfCredit = 0;
    int timeOfCredit = 0, bank;
    double interestRate = 0;
    string typeOfCredit, pledge, answer;
    bool flag=true;

    while (true) {
        if (flag) {
            cout << "\n-Здравствуйте! Данное консольное приложение поможет вам подобрать банк\n";
            cout << "с наиболее выгодными для вас условиями по необходимому для вас кредиту.\n";
            flag = false;
        }

        cout << "\nДавайте начнем с того, какая сумма кредита вам необходима?\nВведите сумму (в рублях)\n->";
        cin >> amountOfCredit;
        cout << "\nНа какое количество месяцев вы хотели бы взять кредит?\nВведите количество месяцев (до 60)\n->";
        cin >> timeOfCredit;
        cout << "\nС какой целью вы берете кредит?\nВведите \"car\" - если берете кредит с целью покупки машины,\n";
        cout << "        \"mortgage\" - если хотите взять ипотечный кредит,\n";
        cout << "        \"refinancing\" - с целью рефинансирования кредита,\n";
        cout << "        \"other\" - если берете кредит по прочим нуждам.\n->";
        cin >> typeOfCredit;
        cout << "\nГотовы ли вы предоставить залог?\nВведите \"yes\" если готовы и \"no\" - если нет\n->";
        cin >> pledge;

        Offer request(amountOfCredit, timeOfCredit, typeOfCredit, pledge);
        request.CalculationOfCredit();
        cout << request << endl;

        cout << "Попробуем с другими параметрами?\n(Введите \"yes\" если хотите продолжить)\n->";
        cin >> answer;

        if (answer != "yes") {
            break;
        }
    }
}

