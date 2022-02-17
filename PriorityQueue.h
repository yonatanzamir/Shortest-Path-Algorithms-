#pragma once



class PriorityQueue
{
	public:

		struct Key // data   ///// private??
		{
			float key_dValue;
			bool infinity; // =true if distance is inifinty
		};

		struct PqCell
		{
			Key key_dist; // key
			int data_vertex; // data
		};


	protected:
	PqCell* data;
	int* places;
	int MaxSize;
	int LogicalSize;
	int allocated;
public:
	PriorityQueue(int size);
	PriorityQueue();
	~PriorityQueue();
	virtual void Build(PqCell* arr, int n) = 0;
	virtual PqCell Min()=0;
	virtual void DecreaseKey(float newKey, int place)=0;
	virtual PqCell DeleteMin()=0;
	virtual void Insert(PqCell item)=0;
	bool IsEmpty() { return (LogicalSize == 0); }
	void InitPlacesArray();
	void swapInt(int& a, int& b);
	void swapPqCell(PqCell& a, PqCell& b);

};

