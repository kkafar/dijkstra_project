// K. Kafara

/**
 * Teraz idea jest taka, że stworzymy sobie coś na zasadzie wektora ze standardowej biblioteki, co pozwoli na linearyzację `podstawy`
 * kolejki i łatwe przeliczanie indeksów (adresów w pamięci)
 */


////////////////////////////////////////////////////////////
// Szablony metod klasy `QueueNode`
////////////////////////////////////////////////////////////
template<class Type> QueueNode<Type>::QueueNode(Type& object, int prior) : object(object), prior(prior)
{
    LogMessage(__FILE__, __LINE__, "Konstruktor klasy QueueNode<Type> (PARAM), adres: ", this);
}
////////////////////////////////////////////////////////////
template<class Type> QueueNode<Type>::QueueNode()
{
    LogMessage(__FILE__, __LINE__, "Konstruktor klasy QueueNode<Type> (NO_PARAM), adres: ", this);
} 
////////////////////////////////////////////////////////////
template<class Type> QueueNode<Type>::~QueueNode()
{
    LogMessage(__FILE__, __LINE__, "Destruktor klasy QueueNode<Type>, adres: ", this);
}
////////////////////////////////////////////////////////////
template<class Type> QueueNode<Type>& QueueNode<Type>::operator=(const QueueNode<Type>& obj)
{
    this->object = obj.object;
    this->prior = obj.prior;
    return (*this);
} 
////////////////////////////////////////////////////////////
template<class Type> QueueNode<Type>::QueueNode(QueueNode<Type>& obj)
{
    *(this) = obj;
}
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Szablony metod klasy `MinPriorQueue`
////////////////////////////////////////////////////////////
template<class Type> MinPriorQueue<Type>::MinPriorQueue()
{
    LogMessage(__FILE__, __LINE__, "Konstruktor klasy MinPriorQueue, adres obiektu: ", this);
}
////////////////////////////////////////////////////////////
template<class Type> MinPriorQueue<Type>::~MinPriorQueue()
{
    LogMessage(__FILE__, __LINE__, "Destruktor klasy MinPriorQueue, adres obiektu: ", this);
}
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] int MinPriorQueue<Type>::Parent(const int index) const
{
    if (index == 0) return -1;
    else            return (index - 1) / 2;
}
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] int MinPriorQueue<Type>::Left(const int index) const
{
    return (2 * index) + 1;
}
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] int MinPriorQueue<Type>::Right(const int index) const
{
    return (2 * index) + 2;
}
////////////////////////////////////////////////////////////
template<class Type> void MinPriorQueue<Type>::Heapify(int index)
{
    int smallest_prior_index = index, left, right, size = vec.GetSize();

    while (index < size)
    {
        left = Left(index);
        right = Right(index);

        if (left < size && vec[left].prior < vec[smallest_prior_index].prior)
            smallest_prior_index = left;

        if (right < size && vec[right].prior < vec[smallest_prior_index].prior)
            smallest_prior_index = right;

        if (smallest_prior_index != index)
        {
            QueueNode<Type> buff(vec[smallest_prior_index]);
            vec[smallest_prior_index] = vec[index];
            vec[index] = buff;
            index = smallest_prior_index;
        }

        else
            break;
    }
}
//////////////////////////////////////////////////////////// 
template<class Type> void MinPriorQueue<Type>::Push(Type& obj, const int priority)
{
    vec.PushBack(QueueNode<Type>(obj, priority));

    // jedziemy w górę drzewa, przywracając własność kopca
    int index = vec.GetSize() - 1;

    while (Parent(index) >= 0 && vec[Parent(index)].prior < vec[index].prior)
    {
        QueueNode<Type> buff(vec[Parent(index)]);
        vec[Parent(index)] = vec[index];
        vec[index] = buff;
        index = Parent(index);
    }
}
////////////////////////////////////////////////////////////
template<class Type> [[nodiscard]] Type& MinPriorQueue<Type>::Front() const
{
    if (vec.GetSize() > 0)
        return vec[0].object;

    else
        LogMessage(__FILE__, __LINE__, "Proba odczytu z pustej kolejki");
}
////////////////////////////////////////////////////////////
template<class Type> void MinPriorQueue<Type>::Pop()
{
    if (vec.GetSize() > 0)
    {
        vec[0] = vec[vec.GetSize() - 1];
        vec.PopBack();

        Heapify(0);
    }

    else 
        LogMessage(__FILE__, __LINE__, "Proba usuniecia elementu z pustej kolejki");
}
////////////////////////////////////////////////////////////