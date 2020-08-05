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

#define __LOGS_MYVEC__

////////////////////////////////////////////////////////////
// @brief Logger
// ≥ 3 - rezerwacja pamięci 
// ≥ 2 - info o konstrukorach/destruktorze
// ≥ 1 - powiększanie wektora, wyświetlanie adresów
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
#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Konstruktor klasy MyVec (PARAM), adres: ", this);
    // LOG_MESSAGE("Konstruktor klsy MyVec (PARAMETRIZED)", __FILE__, __LINE__);
#endif /* __LOGS_MYVEC__ */
    
    // potencjalne miejsce błędów (jak powinno być: MyVec::size czy MyVec<Type>::size)
    this->size = static_cast<int>(size * SIZE_FACTOR); 
    // head = new Type[this->size];
    // head = (Type *)(malloc(sizeof(Type) * SIZE_FACTOR));
    head = AllocVec_Malloc(sizeof(Type) * (this->size));

#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Wektor: ", head, " -- ", head + sizeof(Type) * (this->size));
#endif /* __LOGS_MYVEC__ */
} 
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::MyVec() : size(INITIAL_NO_PARAM_SIZE), current_size(0)
{
#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Konstruktor klasy MyVec (NO PARAM), adres: ", this);
    // LOG_MESSAGE("Konstruktor klasy MyVec (NO PARAM)", __FILE__, __LINE__);
#endif /* __LOGS_MYVEC__ */

    // head = new Type[INITIAL_NO_PARAM_SIZE];
    // head = (Type *)(malloc(sizeof(Type) * INITIAL_NO_PARAM_SIZE));
    head = AllocVec_Malloc(sizeof(Type) * INITIAL_NO_PARAM_SIZE);

#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Wektor: ", head, " -- ", head + sizeof(Type) * INITIAL_NO_PARAM_SIZE);
#endif /* __LOGS_MYVEC__ */
}
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::~MyVec() 
{
#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Destruktor klasy MyVec, adres: ", this);
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Adres poczatku zwalnianego obszaru: ", head);
    // LOG_MESSAGE("Destruktor klasy MyVec", __FILE__, __LINE__);
#endif /* __LOGS_MYVEC__ */
    
    // delete[] head;
    // free(head);
    FreeVec_Malloc(head);
}
////////////////////////////////////////////////////////////
template<class Type> void MyVec<Type>::PushBack(const Type x)   
{
#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "PushBack(", x.object, ", ", x.prior, "), adres: ", &x);
#endif /* __LOGS_MYVEC__ */

    // Jeżeli w wektorze brakuje miejsca, to rezerwujemy większą przestrzeń, przepisujemy starą zawartość,
    // zwalaniamy wcześniej wykorzystywaną przestrzeń
    if (current_size >= size)
    {
        int new_size = static_cast<int>(size * EXT_FACTOR);

#ifdef __LOGS_MYVEC__
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Zwiekszam rozmiar wektora do ", new_size,
        "\nDotychczasowa zawartosc wektora:");
        for (int i = 0; i < GetSize(); ++i)
        {
            std::cout << head + i << ":  " << (head + i)->object << "\n";
            std::cout.flush();
        }
        std::cout << "\n";
#endif /* __LOGS_MYVEC__ */


        // LogMessage(__FILE__, __LINE__, "Zwiekszam rozmiar wektora do ", new_size);
        // Type * new_vec = new Type[new_size];
        Type * new_vec = AllocVec_Malloc(sizeof(Type) * new_size);

#ifdef __LOGS_MYVEC__
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 3, "Nowy wektor: ", new_vec, " -- ", new_vec + sizeof(Type) * new_size);
#endif /* __LOGS_MYVEC__ */

        for (int i = 0; i < size; ++i)
            *(new_vec + i) = *(head + i);    
        
        // delete[] head;
        FreeVec_Malloc(head);
        size = new_size;
        head = new_vec;
    }

    *(head + current_size) = x;
    // (*(head + current_size)).obj
    ++current_size;

#ifdef __LOGS_MYVEC__
    myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Zawartosc wektora:");
    for (int i = 0; i < GetSize(); ++i)
    {
        std::cout << head + i << ":  " << (head + i)->object << "\n";
        std::cout.flush();
    }
    std::cout << "\n";
#endif /* __LOGS_MYVEC__ */
}
////////////////////////////////////////////////////////////
template<class Type> Type & MyVec<Type>::operator[](const int index) const
{
    if (index >= 0 && index < size)
        return *(head + index);
    else
    {
#ifdef __LOGS_MYVEC__
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::ERROR, 0, "MyVec: operator[]: index poza poprawnym zakresem! index=", index);
        // " zakres: 0-", size - 1, "\nZakanczam dzialanie programu z kodem 1");
        // std::cout << __FILE__ << ": " << __LINE__ << ": " << "MyVec: operator[]: index poza poprawnym zakresem! index=" << index << " zakres: 0-" << size - 1 << "\n";
        // std::cout << "Zakanczam dzialanie programu z kodem 1\n";
#endif /* __LOGS_MYVEC__ */
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

#ifdef __LOGS_MYVEC__
    else
        myvec_logger.Message(__FILE__, __LINE__, Log::MessageType::WARNING, 0, "Proba usuniecia z pustego wektora!");
        // LogMessage(__FILE__, __LINE__, "Proba usuniecia z pustego wektora!");
#endif /* __LOGS_MYVEC__ */
}
////////////////////////////////////////////////////////////
