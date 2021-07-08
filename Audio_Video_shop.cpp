
// Курсова робота семестр-1. СБУ-012 Серко Р.В. 



/*1. Предметна область - спеціалізований магазин із продажу аудіо-, відеотехніки і деталей до них. 

Розв'язувані задачі: облік товарів. Реалізувати наступні сервіси:

	Заповнення бази даних
	Перегляд даних про всі товари
	Доповнення бази даних товаром
	Видалення товару із бази даних
	Редагування запису про певний товар
	Упорядкування по полях: назва товару, ціна товару
	Пошук: наприклад, фірма ХХ і все, що з нею зв'язане; магнітофони УУ
	Вибірка: товари певного типу за ціною від X до Y
	Обчислення: середня ціна на товари певного типу (наприклад, телевізори)
	Корекція: видалення зведень про вказані товари; зміна ціни на товари вказаного типу (наприклад, телевізори фірми SONY на 5 %)
	Табличний звіт: інформація про телевізори (марка, ціна, назва), впорядкування по полю “назва”

Додаткові вимоги: перевірка на введення ціни товару (повинна бути більше 0 грн.).
Для обробки даних скористатися динамічним масивом покажчиків на структури відповідного типу
*/

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
using namespace std;



struct all_Items {

    char category[25];
    char type[25];
    char model[25];
    char producer[25];

    double kurs_USD = 27.3;

    double price_USD;

   
    
};

//-------- ЦІНА В ГРИВНЯХ ------------

double price_UAH(all_Items& obj) {

    return (obj.price_USD * obj.kurs_USD);
}


// =============================================  ФУНКЦІЇ ВИВЕДЕННЯ ТАБЛИЦЬ / ІНФОРМАЦІЇ ===============================

void print_head() { // верхній рядок таблиці

    cout << "\n================================================================================";
    cout << "\n N | " << "category: " << " | " << "Producer \t " << " | " << "Type: \t" << " | " << "Model \t " << " | " << "Price: \t ";
    cout << "\n================================================================================\n";


}

void print_item(all_Items& obj) {

    cout << " | " << obj.category << "\t|\t" << obj.producer << "\t|\t" << obj.type << "\t|\t" << obj.model << "\t|" << price_UAH(obj) << " UAH." << "|";

    cout << "\n--------------------------------------------------------------------------------\n";
}

//------ показ всіх товарів з масиву товарів

void show_All(all_Items*& arr, int& size, string out_file_path)

{
    print_head();

    for (size_t i = 0; i < size; i++)
    {
        cout << i << " | " << arr[i].category << "\t| " << arr[i].producer << "\t| " << arr[i].type << "\t| " << arr[i].model << "\t| " << price_UAH(arr[i]) << " UAH.";

        cout << "\n--------------------------------------------------------------------------------\n";
    }



}


//===============================================  ПЕРЕГЛЯД І ЗМІНА ЦІН  ===================================

void Change_USD_kurs(all_Items*& arr, int size)
{
    double n;

    cout << "\nVvedit aktualnyi kurs USD ->"; cin >> n;

    for (size_t i = 0; i < size; i++)
    {
        arr[i].kurs_USD = n;
    }


}


void Change_category_price(all_Items*& arr, int& length) {

    char cat[25], prod[25];
    double corect;


    cout << "What category price to change ?"; cin >> cat;
    cout << "What  producer ?"; cin >> prod;
    
    cout << "Change value in % "; cin >> corect;

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].category, cat) == 0 && strcmp(arr[i].producer, prod) == 0)

        {
            arr[i].price_USD += arr[i].price_USD * corect / 100;
        }


    }
}


void Change_item_price( all_Items* & arr,int & length )
{
    char cat[25], prod[25], mod[25];
    double corect;


    cout << "What category price to change ? "; cin >> cat;
    cout << "What  producer ? "; cin >> prod;
    cout << "What model ? "; cin >> mod;
    
    cout << "Set new price -> "; cin >> corect;

    while (corect<= 0)
    {
        cout << "\n error";
        cout << "\nInput correct price $ -> "; cin >> corect;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].category, cat) == 0 && strcmp(arr[i].producer, prod)==0 && strcmp(arr[i].model, mod) == 0)

        {
            arr[i].price_USD = corect;
        }

    }


}



void AVG_price(all_Items*& arr, int& length)

{
    char cat[25];
    int count=0;
    double pricesum = 0;
    cout << "\nWhat category AVG price to see ? "; cin >> cat;

    print_head();

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].category, cat) == 0)
        {
            print_item(arr[i]);
            
            pricesum += price_UAH(arr[i]);
            
            count++;
        }

    }

    cout << "\n AVERAGE PRICE : "<<pricesum/count;

}




//==============================================  ФУНКЦІЇ ЗАПОВНЕННЯ / ДОДАВАННЯ ТОВАРУ ================================== 

void fill_item(all_Items& obj) {

    cout << "\nInput category: \n \t player\n \t televisor\n \t microfon\n \t speaker etc. \n -> "; cin >> obj.category;
    cout << "\nInput type: -> "; cin >> obj.type;
    cout << "\nInput model -> "; cin>> obj.model;
    cout << "\nInput producer -> "; cin >> obj.producer;

    cout << "\nInput price $ ->"; cin >> obj.price_USD;
    while (obj.price_USD <= 0)
    {
        cout << "\n error";
        cout << "\nInput correct price $ ->"; cin >> obj.price_USD;
    }
}

void Add_new_item(string file_path ) {
    
    all_Items obj;

    int number;

    cout << "\nHow much items would you like to Add  -> "; cin >> number;

    fstream file;
    
    file.open(file_path, fstream::app | fstream::in | fstream::out);
    
    if (!file.is_open()) { cout << "error" << endl; }
    else {
        int i = 0;
        for (size_t i = 0; i < number; i++)
        {
           
            fill_item(obj);
            file.write((char*)&obj, sizeof(obj));

        }
    }
    file.close();

   
}


//==============================================  ФУНКЦІЇ ПОШУКУ В БАЗІ ==================================================

void Price_Search(all_Items*& arr, int& length) {

    int max, min;
   
    char cat[25];

    cout << "\n Input category for searching  ";

    cin >> cat;

    int count = 0;

    cout << "\n Set min price UAH : "; cin >> min;
    cout << "\n Set max price UAH : "; cin >> max;

    print_head(); 

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].category, cat) == 0 && price_UAH(arr[i]) >= min && price_UAH(arr[i]) <= max)

        {
            print_item(arr[i]);

        }

        else { count++; }

    }

    if (count == length)
    {
        cout << "nothing found ";
    }

}


void Category_Search (all_Items* & arr, int& length)
{
    char cat[25];

    cout<<"\n Input category for searching  ";
    
    cin >> cat;

    int count = 0;
    
    print_head();

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].category, cat)==0)

        {
            print_item(arr[i]);

        }

        else { count++; }
        
    }

    if (count==length)
    {
        cout << "nothing found";
    }
  
}


void Producer_Search(all_Items*& arr, int& length)
{
    char prod[25];

    cout << "\n Input producer for searching  ";

    cin >> prod;

    int count = 0;

    print_head();

    for (size_t i = 0; i < length; i++)
    {
        if (strcmp(arr[i].producer, prod) == 0)

        {
            print_item(arr[i]);

        }

        else { count++; }

    }

    if (count == length)
    {
        cout << "nothing found";
    }

}

//================================================  ДОПОМІЖНІ / ДОДАТКОВІ ФУНКЦІЇ ========================================

//---- сортування по категоріях

void category_Sort(all_Items* & arr,int&size) 
{

  int min_ind; // індек найменшого елементу, insertion sort;


    for (int j = 0; j < size - 1; j++)

    {
        int min_ind = j;

        for (int z = j + 1; z < size; z++)
        {

            if (strcmp(arr[z].category, arr[min_ind].category)==-1)
            {
                min_ind = z;
            }
        }
        
        all_Items tmp;

        tmp = arr[j];
        
        arr[j] = arr[min_ind];

        arr[min_ind] = tmp;

    }

}


//------ додавання нового елементу в масив із файлу  ---- 

void Push(all_Items*& arr, int& length, all_Items obj) {

    all_Items* mas = new all_Items[length + 1];

    for (size_t i = 0; i < length; i++)
    {
        mas[i] = arr[i];
    }

    mas[length] = obj;
    length++;
    delete[] arr;
    arr = mas;

}

//------- витягання з файлу бази в масив -----------

void take_base(all_Items* & arr, int& size, string out_file_path) {

    all_Items obj;

    fstream file;

    file.open(out_file_path, fstream::app | fstream::in | fstream::out);

    if (!file.is_open()) { cout << "error" << endl; }

    else {

        while (file.read((char*)&obj, sizeof(obj))) {

            Push(arr, size, obj);
        }

    }

    file.close();


}


//-- пошук потрібного індексу за НАЗВОЮ МОДЕЛІ ------ 

int find_index(all_Items*& arr, int& length,char* find) {

    int i;
    
    for (i = 0; i < length; i++)
    {
        if (strcmp(arr[i].model , find) == 0) { return i; }
    }
    
    return -1;

}


void Delete_item(all_Items* & arr, int& size, char* search) {


    size--;
    int index = find_index(arr, size, search);

    if (index == -1 || size == 0) { cout << "\n not found"; }
    if (size == 1 && index != -1) { delete[] arr; arr = nullptr; size=0; }
    else {
    

        all_Items* mas = new all_Items[size];

        for (size_t i = 0; i < size; i++)
        {
            if (i<index) {
            
                mas[i] = arr[i];
            }
            else { mas[i] = arr[i + 1]; }
        }
      
       delete[] arr;
       
       arr = mas;
        
    }

}


// оновлення - запис у файл:

void update_all(all_Items*& arr, int& size, string out_file_path) {

   fstream file;

    file.open(out_file_path, fstream::app | fstream::in | fstream::out);

    if (!file.is_open()) { cout << "error" << endl; }

    else {

        for (size_t i = 0; i < size; i++)
        {

            file.write((char*)&arr[i], sizeof(arr[i]));

        }

    }

    file.close();


}



//************************************************** ГОЛОВНА **********************************************************


int main()

{ 
    all_Items* item_arr = new all_Items[0];
    
    all_Items obj;
    
    int size = 0;
   
    string item_path = "tovary/all_item.txt";

    take_base(item_arr, size, item_path);


 //--------------------- Меню ----------------------------------------

    int chois=1;

    cout << "\n=======================================================================================";
    cout << "\n======================= WELCOME TO THE SHOP CHOOSE THE NEXT ACTION ====================";
    cout << "\n=======================================================================================";
   
    while (chois != 0) {
     
        cout << "\n\t\t input next action";

        cout << "\n\t\t 1 - to see items";
        cout << "\n\t\t 2 - to manage items";
        cout << "\n\t\t 0 - to exit" << endl;
        cin >> chois;

        switch (chois)
        {
        case 1: {
            int c = 1;
            while (c != 0)
            {

                cout << "\n\t\t\t 1 - to see all items";
                cout << "\n\t\t\t 2 - to search by category";
                cout << "\n\t\t\t 3 - to search by price";
                cout << "\n\t\t\t 4 - to search by producer";
                cout << "\n\t\t\t 5 - to see Aerage category price";
                cout << "\n\t\t\t 0 - return to previous menu" << endl;
                cin >> c;

                switch (c)
                {
                case 1: {

                    //take_base(item_arr, size, item_path);
                    show_All(item_arr, size, item_path); break; }

                case 2: {

                    Category_Search(item_arr, size); break; }
                case 3: {

                    Price_Search(item_arr, size); break; }
                case 4: {
                    Producer_Search(item_arr, size); break; }
                
                case 5: {
                    AVG_price(item_arr, size); break; }

                case 0: { break; }


                default:
                    break;
                }

            }
                break;
            
        }

        case 2: {

            int m = 1;
            while (m != 0)
            {
                cout << "\n\t\t\t 1 - To add more items";
                cout << "\n\t\t\t 2 - to sort by categoryies";
                cout << "\n\t\t\t 3 - to change USD kurs";
                cout << "\n\t\t\t 4 - to change category price";
                cout << "\n\t\t\t 5 - to delete item";
                cout << "\n\t\t\t 6 - to change item price";
                cout << "\n\t\t\t 7 - to save the changes";
                cout << "\n\t\t\t 0 - Return to previous menu" << endl;
                cin >> m;
                switch (m)
                {
                case 1: { Add_new_item(item_path); 
                                     
                    break;

                }

                case 2: { category_Sort(item_arr, size);
                    show_All(item_arr, size, item_path);
                    break; }

                case 3: {Change_USD_kurs(item_arr, size); remove("tovary/all_item.txt");
                    update_all(item_arr, size, item_path);      break; }


                case 4: {Change_category_price(item_arr, size); remove("tovary/all_item.txt");
                    update_all(item_arr, size, item_path); break;



                }
                case 5: {
                    char cl[25];
                    cout << "\n Enter model name to delete -> "; cin>>cl;

                    Delete_item(item_arr, size, cl);
                    
                    remove("tovary/all_item.txt");
                    update_all(item_arr, size, item_path);

                    cout << "\n Zminy onovleno";
                    break;
                }
                
                case 6: {
                    Change_item_price(item_arr, size);

                    remove("tovary/all_item.txt");
                    update_all(item_arr, size, item_path);
                    cout << "\n Zminy onovleno";

                    break;
                }

                case 7: {
                    //remove("tovary/all_item.txt");

                    update_all(item_arr, size, item_path);
                    cout << "\n Zminy onovleno";

                    break; }


                case 0: { break; }

                default:
                    break;
                }
            }

                break;
           
        }
              break;
        default: break;
        }

    }
//----------------------------------------------------------------------------
    

    cout << "\n";
    system("pause");
}

