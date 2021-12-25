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
     * @brief Construct a new empty Mergeable Heap object
     */
    MergeableHeap(enum ListType);

    /**
     * @brief Instert a new value to the heap.
     *
     * @param value The value to be inserted.
     * @return True If the insertion was successful, false otherwise.
     */
    bool INSERT(T value);

    /**
     * @brief Returns the minimum value from the heap.
     *
     * @return T The minimum value.
     */
    T MINIMUM();

    /**
     * @brief Extracts the minimum value from the heap and returns it.
     *        Note: If the heap is empty an exception will be throwed.
     *
     * @return T The min value that has been extracted.
     */
    T EXCTRACT_MIN();

    /**
     * @brief Unions the two heaps.
     *
     * @param other The other heap to be merged
     * @return T this merged heap if the union was successful, the given heap otherwise.
     */
    T UNION(const MergeableHeap<T> &other);

private:
    enum ListType type;
};