#include <iostream>

struct node
{
	unsigned int key;
	int index;
	int minIndex;
	int maxIndex;
};


int leftChild(int i)
{
	return 2 * i;
}

int rightChild(int i)
{
	return 2 * i + 1;
}

void swap(node* &first, node* &second)
{
	node* tmp = first;
	first = second;
	second = tmp;
}

void swapMaxIndexes(node* &first, node* &second)
{
	int tmp = first->maxIndex;
	first->maxIndex = second->maxIndex;
	second->maxIndex = tmp;
}

void swapMinIndexes(node* &first, node* &second)
{
	int tmp = first->minIndex;
	first->minIndex = second->minIndex;
	second->minIndex = tmp;
}

void maxHeapify(node** tab, int i, int size)
{
	int right = rightChild(i);
	int left = leftChild(i);
	int max = i;

	if (left <= size && tab[left]->key > tab[max]->key)
	{
		max = left;
	}
	if (left <= size && tab[left]->key == tab[max]->key && tab[left]->index < tab[max]->index)
	{
		max = left;
	}
	if (right <= size && tab[right]->key > tab[max]->key)
	{
		max = right;
	}
	if (right <= size && tab[right]->key == tab[max]->key && tab[right]->index < tab[max]->index)
	{
		max = right;
	}

	if (max != i)
	{
		swap(tab[i], tab[max]);
		swapMaxIndexes(tab[i], tab[max]);
		maxHeapify(tab, max, size);
	}
}

void minHeapify(node** tab, int i, int size)
{
	int right = rightChild(i);
	int left = leftChild(i);
	int min = i;

	if (left <= size && tab[left]->key < tab[min]->key)
	{
		min = left;
	}
	if (left <= size && tab[left]->key == tab[min]->key  && tab[left]->index < tab[min]->index)
	{
		min = left;
	}
	if (right <= size && tab[right]->key < tab[min]->key)
	{
		min = right;
	}
	if (right <= size && tab[right]->key == tab[min]->key && tab[right]->index < tab[min]->index)
	{
		min = right;
	}

	if (min != i)
	{
		swap(tab[i], tab[min]);
		swapMinIndexes(tab[i], tab[min]);
		minHeapify(tab, min, size);
	}
}

void bubbleUpMin(node** minTab, int i, int minSize)
{
	if (i > 1)
	{
		int parent = i / 2;
		if (minTab[parent]->key > minTab[i]->key || 
			(minTab[parent]->key == minTab[i]->key && minTab[parent]->index > minTab[i]->index))
		{
			swap(minTab[i], minTab[parent]);
			swapMinIndexes(minTab[i], minTab[parent]);
			bubbleUpMin(minTab, parent, minSize);
		}
	}
}

void bubbleUpMax(node** maxTab, int i, int maxSize)
{
	if (i > 1)
	{
		int parent = i / 2;
		if (maxTab[parent]->key < maxTab[i]->key || 
			(maxTab[parent]->key == maxTab[i]->key && maxTab[parent]->index > maxTab[i]->index))
		{
			swap(maxTab[i], maxTab[parent]);
			swapMaxIndexes(maxTab[i], maxTab[parent]);
			bubbleUpMax(maxTab, parent, maxSize);
		}
	}
}

void buildMaxHeap(node** maxTab, int size)
{
	for (int i = size / 2; i > 0; --i)
	{
		maxHeapify(maxTab, i, size);
	}
}

void buildMinHeap(node** minTab, int size)
{
	for (int i = size / 2; i > 0; --i)
	{
		minHeapify(minTab, i, size);
	}
}

void removeMax(node** maxTab, int &maxSize)
{
	swap(maxTab[1], maxTab[maxSize]);
	swapMaxIndexes(maxTab[1], maxTab[maxSize]);
	maxSize--;
	maxHeapify(maxTab, 1, maxSize);	
}

void removeMin(node** minTab, int &minSize)
{
	swap(minTab[1], minTab[minSize]);
	swapMinIndexes(minTab[1], minTab[minSize]);
	minSize--;
	minHeapify(minTab, 1, minSize);	
}

void changeKeyInMax(node** maxTab, node** minTab, int maxSize, int minSize, int newValue)
{
	int oldValue = maxTab[1]->key;
	maxTab[1]->key = newValue;
	bubbleUpMin(minTab, maxTab[1]->minIndex, minSize);
	maxHeapify(maxTab, 1, maxSize);
}

void changeKeyInMin(node** maxTab, node** minTab, int maxSize, int minSize, int newValue)
{
	int oldValue = minTab[1]->key;
	minTab[1]->key = newValue;
	bubbleUpMax(maxTab, minTab[1]->maxIndex, maxSize);
	minHeapify(minTab, 1, minSize);
}

unsigned int peekMin(node** minTab)
{
	return minTab[1]->key;
}

unsigned int peekMax(node** maxTab)
{
	return maxTab[1]->key;
}


void collatzFunction(unsigned int &number)
{
	if (number % 2 == 0)
	{
		number /= 2;
		return;
	}
	if (number % 2 == 1)
	{
		if (number > 0xFFFFFFFF / 3 - 1)
		{
			number = 0;
			return;
		}
		number = 3 * number + 1;
		return;
	}
}



int main()
{

	int numberOfCommands = 0;

	int size = 0;
	int minSize = 0;
	int maxSize = 0;

	node *heap = nullptr;
	node **maxheap = nullptr;
	node **minheap = nullptr;

	char command;
	int howManyCollatz;

	std::cin >> size;
	if (size > 60000)
	{
		return 0;
	}

	maxSize = size;
	minSize = size;

	heap = new node[size + 1];
	maxheap = new node*[size + 1];
	minheap = new node*[size + 1];

	for (int i = 1; i < size + 1; i++)
	{
		std::cin >> heap[i].key;

		heap[i].index = i;
		heap[i].minIndex = i;
		heap[i].maxIndex = i;

		maxheap[i] = &heap[i];
		minheap[i] = &heap[i];
	}

	buildMaxHeap(maxheap, maxSize);
	buildMinHeap(minheap, minSize);

	std::cin >> numberOfCommands;

	if (numberOfCommands > 2000)
	{
		delete[] heap;
		delete[] minheap;
		delete[] maxheap;
		return 0;
	}

	for (int i = 0; i < numberOfCommands; i++)
	{
		std::cin >> howManyCollatz;
		if (howManyCollatz > 2000)
		{
			std::cin >> command;
			continue;
		}
		std::cin >> command;

		for (int j = 0; j < howManyCollatz; j++)
		{
			if (command == 's')
			{
				//deleting spare 0 and 1 from min heap
				while (minSize > 0 && (peekMin(minheap) == 0 || peekMin(minheap) == 1))
				{
					removeMin(minheap, minSize);
				}
				if (minSize > 0)
				{
					unsigned int oldValue = peekMin(minheap);
					collatzFunction(oldValue); // old value becomes new value
					changeKeyInMin(maxheap, minheap, maxSize, minSize, oldValue);
				}
			}
			else if (command == 'l')
			{
				if (maxSize > 0)
				{
					unsigned int max = peekMax(maxheap);
					if (max == 1 || max == 0)
					{
						continue;
					}
					else
					{
						unsigned int oldValue = max;
						collatzFunction(oldValue); // old value becomes new value
						changeKeyInMax(maxheap, minheap, maxSize, minSize, oldValue);
					}
				}
			}
		}
	}
	

	for (int i = 1; i < size + 1; i++)
	{
		if (heap[i].key == 0)
		{
			putchar('m');
		}
		else
		{
			printf("%u", heap[i].key);
		}
		putchar(' ');
	}


	delete[] heap;
	delete[] minheap;
	delete[] maxheap;

	return 0;
}
