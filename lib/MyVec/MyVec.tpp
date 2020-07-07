
////////////////////////////////////////////////////////////
// Szablony metod szablonu klasy `MyVec`. 
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::MyVec(const int size) : current_size(0)
{
    LOG_MESSAGE("Konstruktor klsy MyVec (PARAMETRIZED)", __FILE__, __LINE__);
    // potencjalne miejsce błędów (jak powinno być: MyVec::size czy MyVec<Type>::size)
    this->size = static_cast<int>(size * SIZE_FACTOR); 
    head = new Type[this->size];
} 
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::MyVec() : size(INITIAL_NO_PARAM_SIZE), current_size(0)
{
    LOG_MESSAGE("Konstruktor klasy MyVec (NO PARAM)", __FILE__, __LINE__);
    head = new Type[INITIAL_NO_PARAM_SIZE];
}
////////////////////////////////////////////////////////////
template<class Type> MyVec<Type>::~MyVec() 
{
    LOG_MESSAGE("Destruktor klasy MyVec", __FILE__, __LINE__);
    delete head;
}
////////////////////////////////////////////////////////////
template<class Type> void MyVec<Type>::PushBack(const Type x)
{
    // Jeżeli w wektorze brakuje miejsca, to rezerwujemy większą przestrzeń, przepisujemy starą zawartość
    // zwalaniamy wcześniej wykorzystywaną przestrzeń
    if (current_size >= size)
    {
        LOG_MESSAGE("Zwiekszam rozmiar wektora", __FILE__, __LINE__);
        int new_size = static_cast<int>(size * EXT_FACTOR);
        Type * new_vec = new Type[new_size];

        for (int i = 0; i < size; ++i)
        {
            *(new_vec + i) = *(head + i);    
        }

        delete head;
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
        std::cout << __FILE__ << ": " << __LINE__ << ": " << "MyVec: operator[]: index poza poprawnym zakresem! index=" << index << " zakres: 0-" << size - 1 << "\n";
        std::cout << "Zakanczam dzialanie programu z kodem 1\n";
        exit(1);
    }
}
////////////////////////////////////////////////////////////