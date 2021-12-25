#ifndef LIST_H
#define LIST_H

#include "misc.h"

namespace MNMA
{
template <typename T>
class List
{
public:
    /**
     * @brief Construct a new List object with the given value.
     *
     * @param value The given value to store in the new node.
     */
    List(T value);

    /**
     * @brief Construct a new List object with the given value and next node.
     *
     * @param value The given value to store in the new node.
     * @param next The next node of the list.
     */
    List(T value, List *next);

    /**
     * @brief Get the Next node of the list.
     *
     * @return List* A pointer to the next node.
     */
    List *GetNext();

    /**
     * @brief Set the Next node of the list.
     *
     * @param next A pointer to the next node to set.
     */
    void SetNext(List *next);

    /**
     * @brief Get the Value of the current node.
     *
     * @return const T The value from the current node.
     */
    const T GetValue();

private:
    T value;
    List *next;
};

template <typename T>
List<T>::List(T value) : value{value}
{
    ForceInteger<T>();
}

template <typename T>
List<T>::List(T value, List *next) : value {value}, next{next}
{
    ForceInteger<T>();
}

template <typename T>
List<T> *List<T>::GetNext()
{
    return this->next;
}

template <typename T>
void List<T>::SetNext(List<T> *next)
{
    this->next = next;
}

template <typename T>
const T List<T>::GetValue()
{
    return this->value;
}

} // namespace MNMA

#endif // LIST_H