
#ifndef MERGEABLE_HEAP_H
#define MERGEABLE_HEAP_H

#include "misc.h"
#include "List.hpp"

#include <iostream>

namespace MNMA
{
/**
 * @brief A mergeable heap.
 *
 * @tparam T An integer.
 */
template <typename T>
class MergeableHeap
{
public:
    enum class ListType
    {
        sorted,
        unsorted,
        disjoints // Lists are unsorted, and dynamic sets to be merged are disjoint.
    };

public:
    /**
     * @brief Construct a new empty Mergeable Heap object.
     *
     * @param list_type The type of list to based the heap on.
     */
    MergeableHeap(const enum ListType list_type);

    /**
     * @brief Destroy the Mergeable Heap object and its list.
     */
    ~MergeableHeap();

    /**
     * @brief Instert a new value to the heap.
     *
     * @param value The value to be inserted.
     * @return True If the insertion was successful, false otherwise.
     */
    bool Insert(const T value);

    /**
     * @brief Return the minimum value from the heap.
     *
     * @return T The minimum value of the heap.
     */
    T Minimum();

    /**
     * @brief Extract the minimum value from the heap and returns it.
     *        Note: If the heap is empty an exception will be throwed.
     *
     * @return T The min value that has been extracted.
     */
    T ExctractMin();

    /**
     * @brief Union the two heaps.
     *
     * @param other The other heap to be merged
     * @return T this merged heap if the union was successful, the given heap otherwise.
     */
    // T Union(const MergeableHeap<T> &other);

private:
    /**
     * @brief Insert a value to the heap's sorted linked list.
     *
     * @param value The value to insert.
     * @return True If the insertion was successful, false otherwise.
     */
    bool InsertSorted(const T value);

    /**
     * @brief Insert a value to the heap's unsorted linked list.
     *
     * @param value The value to insert.
     * @return True If the insertion was successful, false otherwise.
     */
    bool InsertUnSorted(const T value);

    /**
     * @brief Check if a given value is in the heap's list.
     *
     * @param value The value to check.
     * @return true If the value exists in the heap's list, false otherwise.
     */
    bool CheckIfIn(const T value);

    /**
     * @brief Get the node with the minimum value of the heap's sorted list.
     *
     * @return T The node with the minimum value;
     */
    T MinimumSorted();

    /**
     * @brief Get the node with the minimum value of the heap's unsorted list.
     *
     * @return T The node with the minimum value;
     */
    T MinimumUnSorted();

    /**
     * @brief Get the One Before Node object.
     *
     * @param value The value to search by.
     * @return List<T>* A pointer to the node before the node that contains the given value.
     */
    List<T>* GetOneBeforeNode(const T value);

public:
    List<T> *list;
    const enum ListType type;
};

template <typename T>
MergeableHeap<T>::MergeableHeap(const enum ListType list_type) : list{nullptr}, type{list_type}
{
    ForceInteger<T>();
}

template <typename T>
MergeableHeap<T>::~MergeableHeap()
{
    // Go over the list and free each of its nodes.
    if (this->list != nullptr)
    {
        while(this->list != nullptr)
        {
            auto *tmp{this->list};
            this->list = this->list->GetNext();
            delete tmp;
        }
    }
}

template <typename T>
bool MergeableHeap<T>::InsertSorted(const T value)
{
    // Handle the case of the first node is needed to be raplaced
    //  (the list is empty or the given value is the min).
    if (this->list == nullptr || this->list->GetValue() >= value)
    {
        auto *tmp{new List<T>{value, this->list}};
        CHECK_RET(tmp != nullptr);

        this->list = tmp;

        return true;
    }

    // Handle the case of insertion after the first node of the list.
    auto *l{this->list};
    while (l->GetNext() != nullptr && l->GetNext()->GetValue() <= value)
    {
        l = l->GetNext();
    }

    auto *tmp{new List<T>(value, l->GetNext())};
    CHECK_RET(tmp != nullptr);

    l->SetNext(tmp);

    return true;
}

template <typename T>
bool MergeableHeap<T>::InsertUnSorted(const T value)
{
    auto *tmp{new List<T>{value, this->list}};
    CHECK_RET(tmp != nullptr);

    this->list = tmp;

    return true;
}

template <typename T>
bool MergeableHeap<T>::CheckIfIn(const T value)
{
    auto *l{this->list};
    while (l != nullptr)
    {
        if (l->GetValue() == value)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
bool MergeableHeap<T>::Insert(const T value)
{
    switch (this->type)
    {
    case ListType::sorted:
    {
        return InsertSorted(value);
    }

    // The only different between disjoints and unsorted is that in disjoints lists the values are unique.
    case ListType::disjoints:
    {
        if (CheckIfIn(value))
        {
            return false;
        }
    }

    // From now the implementation for disjoints lists is the same as unsorted lists.
    case ListType::unsorted:
    {
        return InsertUnSorted(value);
    }
    default:
    {
        throw std::invalid_argument("unsupported");
    }
    }

    return false;
}

template <typename T>
T MergeableHeap<T>::MinimumSorted()
{
    return this->list->GetValue();
}

template <typename T>
T MergeableHeap<T>::MinimumUnSorted()
{
    auto *l{this->list};
    T min{this->list->GetValue()};

    while(l != nullptr)
    {
        if (l->GetValue() < min)
        {
            min = l->GetValue();
        }

        l = l->GetNext();
    }

    return min;
}

template <typename T>
T MergeableHeap<T>::Minimum()
{
    // Return 0 as the min value of an empty heap (as t is forced to be an integer).
    if (this->list == nullptr)
    {
        return 0;
    }

    switch (this->type)
    {
    case ListType::sorted:
    {
        return MinimumSorted();
    }
    case ListType::unsorted:
    case ListType::disjoints:
    {
        return MinimumUnSorted();
    }
    default:
    {
        throw std::invalid_argument("unsupported");
    }
    }
}

template <typename T>
List<T>* MergeableHeap<T>::GetOneBeforeNode(const T value)
{
    List<T> *prev{nullptr};
    auto *current{this->list};

    while (current != nullptr && current->GetValue() != value)
    {
        prev = current;
        current = current->GetNext();
    }

    return prev;
}

template <typename T>
T MergeableHeap<T>::ExctractMin()
{
    T min{Minimum()};
    switch (this->type)
    {
    case ListType::sorted:
    {
        auto *tmp{this->list};
        this->list = this->list->GetNext();
        delete tmp;
    }
    case ListType::unsorted:
    case ListType::disjoints:
    {
        auto *one_before_min{GetOneBeforeNode(min)};
        auto *min_node{one_before_min->GetNext()};

        one_before_min->SetNext(min_node->GetNext());

        delete min_node;
    }
    default:
    {
        throw std::invalid_argument("unsupported");
    }
    }

    return min;
}
} // namespace MNMA

#endif // MERGEABLE_HEAP_H