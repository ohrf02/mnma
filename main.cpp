#include "List.hpp"
#include "MergeableHeap.hpp"

#include <iostream>

using namespace std;
using namespace MNMA;

template <typename T>
void PrintList(List<T> *list)
{
    auto *l{list};
    while (l != nullptr)
    {
        cout << l->GetValue() << " ";
        l = l->GetNext();
    }

    cout << endl;
}

int main()
{
    MergeableHeap<int> h{MergeableHeap<int>::ListType::disjoints};

    h.Insert(4);
    PrintList(h.list);

    h.Insert(-4);
    PrintList(h.list);

    h.Insert(1);
    PrintList(h.list);

    h.Insert(-1);
    PrintList(h.list);

    h.Insert(100);
    PrintList(h.list);

    auto min{h.Minimum()};

    cout << "min = " << min << endl;

    MergeableHeap<int> h1{MergeableHeap<int>::ListType::disjoints};
    h1.Insert(5);
    h1.Insert(-1);

    h.Union(std::move(h1));

    cout << "fml" << endl;

    PrintList(h.list);
    cout << "fml" << endl;

    PrintList(h1.list);

    return 0;
}
