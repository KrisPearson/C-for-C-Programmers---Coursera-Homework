#pragma once
#include <vector>
#include <iostream> // TODO: remove me

//template <class HeapItem>


template<typename HeapItem>
class IHeapItem {
	int HeapIndex;
		
	int GetHeapIndex() { return HeapIndex;  };		
	void SetHeapIndex(int value) { HeapIndex = value; };
};

/*
interface IHeapItem<HeapItem> : IComparable<HeapItem> {
	int HeapIndex{
		get;
	set;
	}
};
*/

template <typename HeapItem>
class Heap : public IHeapItem<HeapItem>  {
public:
	Heap(int maxHeapSize) {
		//itemsVector.resize(maxHeapSize);
		//items = vector<HeapItem> HeapItem(maxHeapSize); 
	}
	~Heap() { /*delete items[];*/ }

private:

	//std::vector<HeapItem> items;
	std::vector< std::pair<HeapItem, int> > itemsVector; // the item and its index

	//HeapItem[] items;

	int currentItemCount = 0;

public:


	void Add2(HeapItem item) {
		
		//item.HeapIndex = 0;

		//std::pair<HeapItem, int> newItem(item, currentItemCount); // ceate a new heap Item and set the index to the number of items
		//itemsVector.push_back(newItem); // add it to the end of the vector
										//std::cout << " Pre Sort = " << itemsVector[0].first << " - " << itemsVector[0].second << std::endl;
		//SortUp(newItem);
		//std::cout << " Post Sort = " << itemsVector[0].first << " - " << itemsVector[0].second << std::endl;

		//std::cout << "Add HeapItem = " << newItem.first << std::endl;
		//item.HeapIndex = currentItemCount; // Set the index to the number of items
		//items[currentItemCount] = item; // add it to the end of the vector
		//SortUp(item);
		//currentItemCount++;
	}


	void Add( HeapItem item)  {

		std::pair<HeapItem, int> newItem(item, currentItemCount); // ceate a new heap Item and set the index to the number of items
		itemsVector.push_back(newItem); // add it to the end of the vector
		//std::cout << " Pre Sort = " << itemsVector[0].first << " - " << itemsVector[0].second << std::endl;
		SortUp(newItem);
		//std::cout << " Post Sort = " << itemsVector[0].first << " - " << itemsVector[0].second << std::endl;

		//std::cout << "Add HeapItem = " << newItem.first << std::endl;
		//item.HeapIndex = currentItemCount; // Set the index to the number of items
		//items[currentItemCount] = item; // add it to the end of the vector
		//SortUp(item);
		currentItemCount++;
	}

	HeapItem RemoveFirst() {
		HeapItem firstItem = itemsVector[0].first;
		int p = itemsVector[0].second;

		std::cout << "RemoveFirst HeapItem = " << firstItem <<  ". priority = " << p << std::endl;

		currentItemCount--;
		itemsVector[0] = itemsVector[currentItemCount];
		itemsVector[0].second = 0;
		SortDown(itemsVector[0]);
		return firstItem;
	}

	inline void UpdateItem(std::pair<HeapItem, int> item) { SortUp(item); }

	inline int GetCurrentItemCount() { return currentItemCount; }

	inline bool Contains(HeapItem item) {
		for (std::vector<std::pair<Node*, int> >::iterator itemIt = itemsVector.begin(); itemIt != itemsVector.end(); ++itemIt) {
			if (itemIt->first == item) {
				return true;
			}
		}
		return false;
		//return Equals(items[item.second], item); 
	}

	void SortDown(std::pair<HeapItem, int> item) {

		int childIndexLeft = item.second * 2 + 1;
		int childIndexRight = item.second * 2 + 2;
		if (childIndexRight < currentItemCount) {
			if (item.second <= itemsVector[childIndexLeft].second && item.second <= itemsVector[childIndexRight].second) {
				return;
			}


			int smallerIndex = itemsVector[childIndexLeft].second < itemsVector[childIndexRight].second ? childIndexLeft : childIndexRight;

			Swap(item, itemsVector[smallerIndex]);
			SortDown(itemsVector[smallerIndex]);
		}
		else if (childIndexLeft < currentItemCount) {
			if (item.second <= itemsVector[childIndexLeft].second) {
				return;
			}
			Swap(item, itemsVector[childIndexLeft]);
			SortDown(itemsVector[childIndexLeft]);
		}
	}



		/*
		while (true) { // bug may have been in this loop??

		int swapIndex = 0;

		if (childIndexLeft < currentItemCount) {
			swapIndex = childIndexLeft;

			if (childIndexRight < currentItemCount) {

				if (Compare(childIndexLeft, childIndexRight) < 0) {
					swapIndex = childIndexRight;
				}

				//if (items[childIndexLeft].CompareTo(items[childIndexRight]) < 0) {
				//	swapIndex = childIndexRight;
				//}
			}
			if (Compare(item.second, itemsVector[swapIndex].second) < 0) {
				Swap(item, itemsVector[swapIndex]);
			}


			//if (item.CompareTo(items[swapIndex]) < 0) {
			//	Swap(item, items[swapIndex]);
			//}
			else {
				return;
			}
		}
		else {
			return;
		}

	}
	*/


	void SortUp(/*HeapItem item*/ std::pair< HeapItem, int> item ) {
		int parentIndex = (item.second - 1) / 2;

		if (item.second <= 0) {
			return;
		}
		if (item.second < itemsVector[parentIndex].second) {
			Swap(item, itemsVector[parentIndex]);
			SortUp(itemsVector[parentIndex]);
		}
		/*
		while (true) {
			std::pair< HeapItem, int> parentItem = itemsVector[parentIndex];
			if (Compare(item.second, parentIndex) > 0) {
				Swap(item, itemsVector[parentIndex]);			
			}
			//HeapItem parentItem = items[parentIndex];
			//if (item.CompareTo(parentItem) > 0) {
			//	Swap(item, parentItem);
			//}
			else {
				break;
			}
		}
		*/
	}

	void Swap(/*HeapItem itemA, HeapItem itemB*/ std::pair<HeapItem, int> itemA, std::pair<HeapItem, int> itemB) {
		itemsVector[itemA.second] = itemB;
		itemsVector[itemB.second] = itemA;
		int itemAIndex = itemA.second;
		itemA.second = itemB.second;
		itemB.second = itemAIndex;
		//items[itemA.HeapIndex] = itemB;
		//items[itemB.HeapIndex] = itemA;
		//int itemAIndex = itemA.HeapIndex;
		//itemA.HeapIndex = itemB.HeapIndex;
		//itemB.HeapIndex = itemAIndex;
	}

	int Compare(int a, int b) {

		if (a < b) return 1;
		else if (a > b) return -1;

		//if (a > b) return 1;
		//else if (a < b) return -1;
		else return 0;
	}



	

	

};


















template<typename HeapItem>
class Interface {
public:
	virtual void func(HeapItem& c) = 0;

	int index;


};

class Container {
public:
	Container() : dummy(10) {}
	int dummy;
};


template<typename HeapItem>
class Implementation : public Interface<HeapItem> {
public:
	void func(HeapItem& c) {
		

//		std::cout << "++c.dummy " << ++c.dummy << std::endl;
	}
};

/*
int main() {
	Container c;
	Implementation<Container> i;
	i.func(c);
	return 0;
}
*/


