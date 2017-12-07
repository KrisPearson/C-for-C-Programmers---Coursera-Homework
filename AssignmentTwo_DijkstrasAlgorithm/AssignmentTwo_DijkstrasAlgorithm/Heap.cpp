#include "stdafx.h"
#include "Heap.h"

class Node;

template class Heap<Node*>;

/*

template<class HeapItem>
void Heap<HeapItem>::Add(HeapItem* item) {
	item.HeapIndex = currentItemCount;
	items[currentItemCount] = item;
	SortUp(item);
	currentItemCount++;
}


template<class HeapItem>
HeapItem Heap<HeapItem>::RemoveFirst() {
	HeapItem firstItem = items[0];
	currentItemCount--;
	items[0] = items[currentItemCount];
	items[0].HeapIndex = 0;
	SortDown(items[0]);
	return firstItem;
}

template<class HeapItem>
void Heap<HeapItem>::SortDown(HeapItem item) {
	while (true) {
		int childIndexLeft = item.HeapIndex * 2 + 1;
		int childIndexRight = item.HeapIndex * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < currentItemCount) {
			swapIndex = childIndexLeft;			

			if (childIndexRight < currentItemCount) {
				if (items[childIndexLeft].CompareTo(items[childIndexRight]) < 0) {
					swapIndex = childIndexRight;
				}
			}

			if (item.CompareTo(items[swapIndex]) < 0) {
				Swap(item, items[swapIndex]);
			}
			else {
				return;
			}
		}
		else {
			return;
		}
	}		
}

template<class HeapItem>
void Heap<HeapItem>::SortUp(HeapItem item) {
	int parentIndex = (item.HeapIndex - 1) / 2;

	while (true) {
		T parentItem = items[parentIndex];
		if (item.CompareTo(parentItem) > 0) {
			Swap(item, parentItem);
		}
		else {
			break;
		}

		parentIndex = (item.HeapIndex - 1) / 2;
	}
}

template<class HeapItem>
void Heap<HeapItem>::Swap(HeapItem itemA, HeapItem itemB) {
	items[itemA.HeapIndex] = itemB;
	items[itemB.HeapIndex] = itemA;
	int itemAIndex = itemA.HeapIndex;
	itemA.HeapIndex = itemB.HeapIndex;
	itemB.HeapIndex = itemAIndex;
}


*/
