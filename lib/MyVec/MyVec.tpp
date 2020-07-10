// K. Kafara

////////////////////////////////////////////////////////////
// Zdecydowałem się na dokonywnie alokacji pamięci poprzez 
// malloc, ponieważ nie powoduje on tworzenia instancji obiektów
// (nie wywołuje konstruktorów poszczególnych obiektów w 
// rezerwowanym obszarze).
// Ku mojemu zaskoczeniu - przeładownie operatora new na:
// void * operator new (size_t alloc_size) { return malloc(alloc_size); }
// nie skutkuje zaprzestaniem wywoływania konstruktorów. 
// Analogicznie z delete i free. 
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// @brief Logger
// ≥ 2 - info o konstrukorach/destruktorze
// ≥ 1 - powiększanie wektora
// ≥ 0 - usuwanie z pustego wektora
////////////////////////////////////////////////////////////
Log myvec_logger;
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Szablony metod szablonu klasy `MyVec`. 
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] Type * MyVec<Type>::AllocVec_Malloc(size_t alloc_size)
{
    return (Type *)(malloc(sizeof(alloc_size)));
}
////////////////////////////////////////////////////////////
template<class Type> void MyVec<Type>::FreeVec_Malloc(Type * head)
{
    free(head);
}
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::MyVec(const int size) : current_size(0)
{
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Konstruktor klasy MyVec (PARAM)");
    // LOG_MESSAGE("Konstruktor klsy MyVec (PARAMETRIZED)", __FILE__, __LINE__);
    // potencjalne miejsce błędów (jak powinno być: MyVec::size czy MyVec<Type>::size)
    this->size = static_cast<int>(size * SIZE_FACTOR); 
    // head = new Type[this->size];
    // head = (Type *)(malloc(sizeof(Type) * SIZE_FACTOR));
    head = AllocVec_Malloc(sizeof(Type) * (this->size));
} 
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::MyVec() : size(INITIAL_NO_PARAM_SIZE), current_size(0)
{
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Konstruktor klasy MyVec (NO PARAM)");
    // LOG_MESSAGE("Konstruktor klasy MyVec (NO PARAM)", __FILE__, __LINE__);
    // head = new Type[INITIAL_NO_PARAM_SIZE];
    // head = (Type *)(malloc(sizeof(Type) * INITIAL_NO_PARAM_SIZE));
    head = AllocVec_Malloc(sizeof(Type) * INITIAL_NO_PARAM_SIZE);
}
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::~MyVec() 
{
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Destruktor klasy MyVec");
    // LOG_MESSAGE("Destruktor klasy MyVec", __FILE__, __LINE__);
    // delete[] head;
    // free(head);
    FreeVec_Malloc(head);
}
////////////////////////////////////////////////////////////
template<class Type> void MyVec<Type>::PushBack(const Type x)
{
    // Jeżeli w wektorze brakuje miejsca, to rezerwujemy większą przestrzeń, przepisujemy starą zawartość
    // zwalaniamy wcześniej wykorzystywaną przestrzeń
    if (current_size >= size)
    {
        int new_size = static_cast<int>(size * EXT_FACTOR);
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Zwiekszam rozmiar wektora do ", new_size);
        // LogMessage(__FILE__, __LINE__, "Zwiekszam rozmiar wektora do ", new_size);
        // Type * new_vec = new Type[new_size];
        Type * new_vec = AllocVec_Malloc(sizeof(Type) * new_size);

        for (int i = 0; i < size; ++i)
        {
            *(new_vec + i) = *(head + i);    
        }
        // delete[] head;
        FreeVec_Malloc(head);
        size = new_size;
        head = new_vec;
    }

    *(head + current_size) = x;
    ++current_size;
}
////////////////////////////////////////////////////////////
template<class Type> Type & MyVec<Type>::operator[](const int index) const
{
    if (index >= 0 && index < size)
        return *(head + index);
    else
    {
        // myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::ERROR, 0, "MyVec: operator[]: index poza poprawnym zakresem! index=", index,
        // " zakres: 0-", size - 1, "\nZakanczam dzialanie programu z kodem 1");
        // std::cout << __FILE__ << ": " << __LINE__ << ": " << "MyVec: operator[]: index poza poprawnym zakresem! index=" << index << " zakres: 0-" << size - 1 << "\n";
        // std::cout << "Zakanczam dzialanie programu z kodem 1\n";
        exit(1);
    }
}
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] int MyVec<Type>::GetSize() const
{
    return current_size;
}
////////////////////////////////////////////////////////////
template<class Type> void MyVec<Type>::PopBack()
{
    if (current_size > 0) 
        --current_size;

    else
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::WARNING, 0, "Proba usuniecia z pustego wektora!");
        // LogMessage(__FILE__, __LINE__, "Proba usuniecia z pustego wektora!");
}
////////////////////////////////////////////////////////////
