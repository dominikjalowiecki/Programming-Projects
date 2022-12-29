def quick_sort(tab):
    if len(tab) < 2:
        return tab
    else:
        pivot = tab[0]
        less = [i for i in tab[1:] if i <= pivot]
        greater = [i for i in tab[1:] if i > pivot]
        return quick_sort(less) + [pivot] + quick_sort(greater)

print(quick_sort([10, 5, 2, 3, 4]))